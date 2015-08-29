<?php //$Id: docprint.inc,v 1.3 2002/01/18 00:01:42 nicola Exp $
    include_once("document.inc");
include_once("debug.inc");
include_once("sqlcmd.inc");
include_once("config.inc");

function ef_p_curr($amount) {
    $round=CONFIG(CURRENCY_ROUND);
    $ndec=ceil(log($round)/log(10));
    $amount_round=sprintf("%s",round($amount*$round));
    $frac_part=substr($amount_round,-$ndec,$ndec);
    $int_part=substr($amount_round,0,-$ndec);
    $cnt=0;
    for ($i=strlen($int_part)-1; $i>=0; $i--) {
	$ch=$int_part[$i];
	$cnt++;
	if ($cnt==4) {
	    $out_int_part=$ch."\\ ".$out_int_part;
	    $cnt=1;
	}
	else
	    $out_int_part=$ch.$out_int_part;
    }
    if ($out_int_part=="") $out_int_part="0";
    return "$out_int_part\\efzero{.$frac_part}";
}

function ltx($string) {
    static $subst=array("à"=>"\\`a\\ ",
			"è"=>"\\`e\\ ",
			"é"=>"\\'e\\ ",
			"ì"=>"\\`i\\ ",
			"ò"=>"\\`o\\ ",
			"ù"=>"\\`u\\ ",
			"{"=>"\\{",
			"}"=>"\\}",
			"%"=>"\%",
			"-"=>"|",
			"|"=>"\\par ",
			"\n"=>"\\par ",
			"\\"=>"\\backslash");

    return strtr($string,$subst);
}

function ef_print_doc($doc,$FOUT,$mode) {
    $doch=$doc->DOC_HEADER;
    $docr=$doc->DOC_ROWS;
    $docf=ef_q_contact(CONFIG(CURRENT_FIRM));

    if ($doch["mostracliente"]=='t')   $docd=ef_q_contact($doch["cliente"]);
    if ($doch["mostrafornitore"]=='t') $docd=ef_q_contact($doch["fornitore"]);

    fputs($FOUT,sprintf("\\newcommand\\efcurr{(%s)}\n",CONFIG(CURRENCY)));
    fputs($FOUT,sprintf("\\newcommand\\efzero[1]{\footnotesize#1}\n"));
    fputs($FOUT,sprintf("\\newcommand\\efcontinue{\\nextpageset| prosegue nella pagina successiva...}\n"));
    fputs($FOUT,sprintf("\\newcommand\\efcontinued{\\nextpageset| continua dalla pagina precedente...}\n"));
    fputs($FOUT,sprintf("\\newcommand\\effirm{%s}\n",ltx($docf["ragsoc"])));
    fputs($FOUT,sprintf("\\newcommand\\efaddress{%s \\\\ %s %s (%s)\\par %s \\\\ %s %s (%s)}\n",
			ltx($docf["indirizzolegale"]),ltx($docf["caplegale"]),ltx($docf["localitalegale"]),ltx($docf["provlegale"]),
			ltx($docf["indirizzoamm"]),ltx($docf["capamm"]),ltx($docf["localitaamm"]),ltx($docf["provamm"])));
    fputs($FOUT,sprintf("\\newcommand\\efaddresshort{%s | %s %s (%s)}\n",	    
			ltx($docf["indirizzolegale"]),ltx($docf["caplegale"]),ltx($docf["localitalegale"]),ltx($docf["provlegale"])));
    if ($docf["partitaiva"]) fputs($FOUT,sprintf("\\newcommand\\efvatcode{%s %s}\n",ltx(ef_msg("M_PVATCODE")),ltx($docf["partitaiva"])));
    else fputs($FOUT,"\\newcommand\\efvatcode{}");
  
    if ($docf["codicefiscale"]) fputs($FOUT,sprintf("\\newcommand\\eftaxpayer{%s %s}\n",ltx(ef_msg("M_PTAXPAYERCODE")),ltx($docf["codicefiscale"])));
    else fputs($FOUT,"\\newcommand\\eftaxpayer{}");

    fputs($FOUT,sprintf("\\newcommand\\efaddressA{%s}\n",ltx($docf["indirizzolegale"])));
    fputs($FOUT,sprintf("\\newcommand\\efaddressB{%s %s (%s)}\n",ltx($docf["caplegale"]),ltx($docf["localitalegale"]),ltx($docf["provlegale"])));
    fputs($FOUT,sprintf("\\newcommand\\eflegaladdress{}\n"));
    fputs($FOUT,sprintf("\\newcommand\\eflocation{}\n"));
    fputs($FOUT,sprintf("\\newcommand\\efoperatingaddress{}\n"));
    fputs($FOUT,sprintf("\\newcommand\\efwebaddress{%s}\n",ltx($docf["webamm"])));
    fputs($FOUT,sprintf("\\newcommand\\efmailaddress{%s}\n",ltx($docf["emailamm"])));
    fputs($FOUT,sprintf("\\newcommand\\efphone{%s}\n",ltx($docf["telefonoamm"])));
    fputs($FOUT,sprintf("\\newcommand\\effax{%s}\n",ltx($docf["faxamm"])));
    fputs($FOUT,sprintf("\\newcommand\\efheaddescription{%s}\n",ef_msg("M_PITEMDESCR")));
    fputs($FOUT,sprintf("\\newcommand\\efheadquantity{%s}\n",ef_msg("M_PITEMQUANTITY")));
    fputs($FOUT,sprintf("\\newcommand\\efheadunit{%s}\n",ef_msg("M_PITEMUNIT")));
    fputs($FOUT,sprintf("\\newcommand\\efheadunitprice{%s}\n",ef_msg("M_PITEMPRICEUNIT")));
    fputs($FOUT,sprintf("\\newcommand\\efheadtaxable{%s}\n",ef_msg("M_PITEMTAXABLE")));
    fputs($FOUT,sprintf("\\newcommand\\efheadvat{%s}\n",ef_msg("M_PITEMVAT")));
    fputs($FOUT,sprintf("\\newcommand\\efheadnotes{%s}\n",ef_msg("M_PITEMNOTES")));
    fputs($FOUT,sprintf("\\newcommand\\efheadtotal{%s}\n",ef_msg("M_PITEMTOTAL")));
    fputs($FOUT,sprintf("\\newcommand\\effoottotal{%s}\n",ef_msg("M_PTOTAL")));
    fputs($FOUT,sprintf("\\newcommand\\efdestination{%s \\\\ %s \\\\ %s \\\\ %s %s (%s) \\\\ %s \\\\ %s }\n",
			ltx(ef_msg("M_COURTESYTITLE")),
			ltx($docd["ragsoc"]),ltx($docd["indirizzolegale"]),
			ltx($docd["caplegale"]),ltx($docd["localitalegale"]),
			ltx($docd["provlegale"]),
			($docd["partitaiva"]?ef_msg("M_PVATCODE")." ".$docd["partitaiva"]:""),
			($docd["codicefiscale"]?ef_msg("M_PTAXPAYERCODE")." ".$docd["codicefiscale"]:"")
			));
    fputs($FOUT,sprintf("\\newcommand\\efdocnumber{%s n. %s/%s}\n",ltx($doch["tipodescr"]),ltx($doch["nprog"]),ltx($doch["anno"])));
    fputs($FOUT,sprintf("\\newcommand\\efdocheading{\\textbf{\efdocnumber} \\\\ del %s}\n",ef_format_date($doch["dataemissione"])));
    
    if ($doch["descrizione"]) fputs($FOUT,sprintf("\\newcommand\\efsubject{\\textbf{Oggetto:} %s}\n",ltx($doch["descrizione"])));
    else fputs($FOUT,sprintf("\\newcommand\\efsubject{}\n"));

    if ($doch["note"]) fputs($FOUT,sprintf("\\newcommand\\efnotes{\\textbf{Note:} %s}\n",ltx($doch["note"])));
    else fputs($FOUT,"\\newcommand\\efnotes{}\n");
			     
    if ($doch["tipopagamento"]) fputs($FOUT,sprintf("\\newcommand\\efpayments{\\textbf{Pagamenti:} %s}\n",ltx($doch["pagamenti"])));
    else fputs($FOUT,"\\newcommand\\efpayments{}\n");
    
    fputs($FOUT,"\\input{efstyle}\n\\efbegindoc\n");
    
    fputs($FOUT,sprintf("\\eftablebegin{%s}{%s}{%s}\n",
			ef_p_curr($doch["imponibile"]),
			ef_p_curr($doch["iva"]),
			ef_p_curr($doch["totale"])
			));
    
    foreach($docr as $row) {
	$S=sprintf("\\eftablerow{%s}{%s}{%s}{%s}{%s}{%s}{%s}{%s}{%s}\n",
		   ($row["articolo"]?ltx($row["rifarticolo"]." - ".$row["articolo"]):""),
		   ltx($row["quantita"]),
		   ltx($row["um"]),
		   ef_p_curr($row["prezzou"]),
		   ef_p_curr($row["imponibile"]),
		   ($row["iva"]?$row["iva"]."\\%":""),
		   ef_p_curr($row["ivaimporto"]),
		   ef_p_curr($row["totale"]),
		   ($row["descrizione"]?"\\footnotesize\\smallskip\\par ".ltx($row["descrizione"]):""));

	fputs($FOUT,$S);
    }
    
    fputs($FOUT,"\\eftableend\n\\efenddoc\n");
}

?>
