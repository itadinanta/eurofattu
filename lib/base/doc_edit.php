<?php // $Id: doc_edit.php,v 1.9 2002/01/17 23:56:53 nicola Exp $
    include_once("debug.inc");
include_once("document.inc");
include_once("format.inc");

class ef_download_documento  {
    function ef_download_documento() {}
    
    function html($doc) {
	$form = new ef_form();
	$form->begin_table(2);
	$form->label(2,
		     ef_msg("M_CLICK_TO_DOWNLOAD_PDF"),
		     ef_html_link(ef_menu_get_id(),
				  ef_msg("M_NUMBERDOC",
					 $doc->DOC_HEADER["tipodescr"],
					 $doc->DOC_HEADER["nprog"],
					 $doc->DOC_HEADER["anno"]),
				  "docpointer=".$doc->DOC_HEADER["docpointer"].
				  "&download=PDF"
				  )
		     );
	$form->label(2,
		     ef_msg("M_CLICK_TO_DOWNLOAD_PS"),
		     ef_html_link(ef_menu_get_id(),
				  ef_msg("M_NUMBERDOC",
					 $doc->DOC_HEADER["tipodescr"],
					 $doc->DOC_HEADER["nprog"],
					 $doc->DOC_HEADER["anno"]),
				  "docpointer=".$doc->DOC_HEADER["docpointer"].
				  "&download=PS"
				  )
		     );
	$form->end_table(2);
	return $form->get_accumulator();
    }
}

class ef_show_documento  {
    function ef_show_documento() {}
    function html_static_row($row) {
	return ef_msg("M_DOC_ROW_PATTERN",
		      $row["riga"],
		      $row["rifarticolo"] ." - ". $row["articolo"],
		      $row["descrizione"],
		      $row["quantita"],
		      $row["um"],
		      ef_format_currency($row["prezzou"]),
		      ef_format_currency($row["imponibile"]),
		      ef_format_vat($row["iva"]),
		      ef_format_currency($row["totale"])
		      );
    }

    function html_static_rows($rows) {
	if (is_array($rows)) 
	    foreach ($rows as $row)
		$result.=$this->html_static_row($row);
	return $result;
    }

    function html($doc) {
	if ($doc->DOC_HEADER["cliente"]) $cli=ef_q_contact($doc->DOC_HEADER["cliente"]);
	if ($doc->DOC_HEADER["fornitore"]) $for=ef_q_contact($doc->DOC_HEADER["fornitore"]);
	$browser=ef_q_get_document_browse($doc->DOC_HEADER["docclass"],$doc->DOC_HEADER["nprog"]);
	$next=$browser[$doc->DOC_HEADER["nprog"]+1];
	$prev=$browser[$doc->DOC_HEADER["nprog"]-1];
	$fields=array("<!--DOCID-->"=>ef_msg("M_NUMBERDOC",
					     $doc->DOC_HEADER["tipodescr"],
					     $doc->DOC_HEADER["nprog"],
					     $doc->DOC_HEADER["anno"]),
		      "<!--SUBJECT-->"=>$doc->DOC_HEADER["descrizione"],
		      "<!--DOCDATE-->"=>ef_format_date($doc->DOC_HEADER["dataemissione"]),
		      "<!--CLIID-->"=>($doc->DOC_HEADER["cliente"]?ef_html_format_address($cli):""),
		      "<!--FORID-->"=>($doc->DOC_HEADER["fornitore"]?ef_html_format_address($for):""),
		      "<!--ROWS-->"=>$this->html_static_rows($doc->DOC_ROWS),
		      "<!--DESCRIPTION-->"=>$doc->DOC_HEADER["descrizione"],
		      "<!--TAXABLE-->"=>ef_format_currency($doc->DOC_HEADER["imponibile"]),
		      "<!--VAT-->"=>ef_format_currency($doc->DOC_HEADER["iva"]),
		      "<!--TOTAL-->"=>ef_format_currency($doc->DOC_HEADER["totale"]),
		      "<!--NOTES-->"=>$doc->DOC_HEADER["note"],
		      "<!--CHARGES-->"=>$doc->DOC_HEADER["oneri"],
		      "<!--NEXTDOC-->"=>($next?ef_html_link(ef_menu_get_id(),ef_msg("M_NEXTDOC"),"docpointer=$next"):""),
		      "<!--PREVDOC-->"=>($prev?ef_html_link(ef_menu_get_id(),ef_msg("M_PREVDOC"),"docpointer=$prev"):"")
		      );
	return ef_strmsg(".showdocument",$fields);
    }
}

class ef_form_documento extends ef_form {
    function ef_form_documento($DOCCLASS) {
	$this->ef_form();
	$this->DOCCLASS_INFO=ef_q_docclass($DOCCLASS);
	DEBUG($this->DOCCLASS_INFO,"DOCCLASS_INFO");
    }

    function html_row($row,$nrows) {
	for($i=1;$i<=$nrows+1;$i++) $fd_doc_rowlist[$i]=$i;
	$fd_doc_rowlist[""]=ef_msg("M_ITEM_DELETE");
 	if ($row)
	    $this->title(2,ef_msg("M_DOC_ITEM",$row["riga"]));
	else
	    $this->title(2,ef_msg("M_DOC_NEWITEM"));

	$this->hidden("fd_doc_row[]","1");
	$this->select(2,ef_msg("M_ITEMREF"),"fd_doc_row_item_rifarticolo[]",$row["rifarticolo"],$this->item_list,SELECT_OPTIONAL);
	$this->input(2,ef_msg("M_ITEMQUANTITY"),"fd_doc_row_item_quantita[]",$row["quantita"],8,8);
	$this->statictext(1,"<!null>","",$row["um"]);
	$this->input(2,ef_msg("M_ITEMPRICEUNIT"),"fd_doc_row_item_prezzou[]",$row["prezzou"],16,16);
	$this->input(2,ef_msg("M_ITEMVAT"),"fd_doc_row_item_iva[]",$row["iva"],3,3);
	$this->textarea(9,ef_msg("M_ITEMDESCRIPTION"),"fd_doc_row_item_descrizione[]",$row["descrizione"],70,2);
 	$this->hidden("fd_doc_row_oldpos[]",$row?$row["riga"]:$nrows+1);
	$this->select(2,ef_msg("M_ITEM_MOVETO"),"fd_doc_row_newpos[]",$row?$row["riga"]:$nrows+1,$fd_doc_rowlist);
 	$this->statictext(2,ef_msg("M_ITEM_TAXABLE"),"",ef_format_currency($row["imponibile"]));
	$this->statictext(2,ef_msg("M_ITEM_TAX"),"",ef_format_currency(($row["iva"]/100.0)*$row["imponibile"]));
	$this->statictext(3,ef_msg("M_ITEM_TOTAL"),"",ef_format_currency($row["totale"]));
    }
    
    function html($doc) {
	$contact_list=ef_q_contact_list();
	$this->item_list=ef_q_item_list();

	$this->begin_form(9);

	if ($doc->DOC_HEADER["docpointer"]>0) {
	    $this->hidden("fd_doc[docpointer]",$doc->DOC_HEADER["docpointer"]);
	    $this->hidden("docpointer",$doc->DOC_HEADER["docpointer"]);
	}
	if ($doc->DOC_HEADER["nprog"])
	    $this->title(1,ef_msg("M_NUMBERDOC",
				  $doc->DOC_HEADER["tipodescr"],
				  $doc->DOC_HEADER["nprog"],
				  $doc->DOC_HEADER["anno"]));
	else {
	    $this->title(1,ef_msg("M_NEWDOC",$this->DOCCLASS_INFO["descrizione"]));
	}

	$this->input(2,ef_msg("M_DOC_DATA"),"fd_doc[dataemissione]",ef_format_date($doc->DOC_HEADER["dataemissione"]),10,10);
	if ($this->DOCCLASS_INFO["mostracliente"]=='t')
	    $this->select(7,ef_msg("M_DOC_CLIENTE"),"fd_doc[cliente]",$doc->DOC_HEADER["cliente"],$contact_list);
	if ($this->DOCCLASS_INFO["mostrafornitore"]=='t')
	    $this->select(7,ef_msg("M_DOC_FORNITORE"),"fd_doc[fornitore]",$doc->DOC_HEADER["fornitore"],$contact_list);
	$this->fill();

	$this->textarea(9,ef_msg("M_DOC_DESCRIZIONE"),"fd_doc[descrizione]",$doc->DOC_HEADER["descrizione"],70,3);

	// $this->title(2,ef_msg("M_DOC_ROWS"));

	$rows=$doc->DOC_ROWS;
	$nrows=@count($rows);
	if (is_array($rows)) foreach ($rows as $row) {
	    $this->html_row($row,$nrows);
	}
	$this->html_row(0,$nrows);

	$this->title(2,ef_msg("M_DOC_SUMMARY"));
	$this->statictext(3,ef_msg("M_DOC_TAXABLE"),"",ef_format_currency($doc->DOC_HEADER["imponibile"]));
	$this->statictext(3,ef_msg("M_DOC_TAX"),"",ef_format_currency($doc->DOC_HEADER["iva"]));
	$this->statictext(3,ef_msg("M_DOC_TOTAL"),"",ef_format_currency($doc->DOC_HEADER["totale"]));


	$this->title(2,ef_msg("M_DOC_NOTES"));
	$this->textarea(5,ef_msg("M_DOC_NOTES"),"fd_doc[note]",$doc->DOC_HEADER["note"],25,3);
	$this->textarea(4,ef_msg("M_DOC_CHARGES"),"fd_doc[oneri]",$doc->DOC_HEADER["oneri"],25,3);
	$this->buttonbar(9,"C");
	$this->end_form();	
	return $this->get_accumulator();
    }
}

function ef_get_document_list($DOCCLASS, $SORTORDER, $SORTDIR) {
    return ef_q_document_list($DOCCLASS, $SORTORDER,$SORTDIR);
}

function ef_html_doc_list($DOCLIST,$SORTORDER,$SORTDIR) {
    
    list($table,$headings)=$DOCLIST;

    foreach ($headings as $col_name) {

	if ($SORTORDER==$col_name) $SORTDIR=1-$SORTDIR;
	$new_headings[]=ef_html_link(ef_menu_get_id(),ef_msg("M_DOCH_".strtoupper($col_name)),"SORTORDER=$col_name&SORTDIR=$SORTDIR");
	$empty_row[]="-";
    }
    list($docclass,$docaction,$doctag)=ef_menu_extract_doc_class(ef_menu_get_nodeid());
    if (is_array($table)) {
	$tlength=count($table);
	if ($docaction=="CAMBIA" || $docaction=="DOWNLOAD") 
	    $edit_menu_id=ef_menu_get_id();
	else
	    $edit_menu_id=ef_menu_get_menuid_by_nodeid("ID_{$doctag}_VISUALIZZA");
	for ($i=0; $i<$tlength; $i++) {
	    $table[$i][0]=ef_html_link($edit_menu_id,ef_msg("M_DOCOPEN"),"docpointer=".$table[$i][0]);
	    $table[$i][3]=ef_format_date($table[$i][3]);
	}
    }
    $empty_row[6]=ef_html_link(ef_menu_get_menuid_by_nodeid("ID_{$doctag}_CREA"),ef_msg("M_DOCNEW"));
    $table[]=$empty_row;

    DEBUG($new_headings,"doc headings");
    
    return ef_html_format_table($table, $new_headings);
}

function ef_doc_rebuild($doc) {
    $filename=$doc->DOC_HEADER["docpointer"];

    $FOUT=fopen(CONFIG(INSTALL_DIR)."/out/$filename.tex","wt");
    if ($FOUT) {
	include_once("docprint.inc");
	ef_print_doc($doc,$FOUT,"tex");
	fclose($FOUT);
    }

    $cmdline=CONFIG(INSTALL_DIR)."/bin/builddoc.sh $filename ".CONFIG(INSTALL_DIR);
    exec($cmdline,$debug,$result);
    DEBUG($cmdline,"exec");
    DEBUG($debug,"debug");
    DEBUG($result,"result");
}

function ef_main_download($variables) {
    $filename="test";
    $docpointer=$variables["docpointer"];
    $filename=$docpointer;
    $doc=new ef_document($docpointer);
    $doc->load();
    $format=$variables["download"];
    switch ($format) {
    case "PS": $ext=".ps";
	header("Content-type: application/postscript");
	header("Content-Disposition: attachment; filename=$filename.ps");
	
	break;
    case "PDF": $ext=".pdf";
	header("Content-type: application/pdf");
	header("Content-Disposition: attachment; filename=$filename.pdf");

	break;
    }
    clearstatcache();
    $fileinfo=stat(CONFIG(INSTALL_DIR)."/out/$filename$ext");
    if ($fileinfo) {
	DEBUG($fileinfo,"STAT");
	$file_time=$fileinfo["mtime"];
	$record_time_as_string=substr($doc->DOC_HEADER["datamodifica"],0,-3);

	$record_time=strtotime($record_time_as_string);
	DEBUG(date("H:i:s d-m-Y",$record_time),"record_time");
	DEBUG(date("H:i:s d-m-Y",$file_time),"file_time");
    }
    if (!$file_time || $file_time<=$record_time)
	ef_doc_rebuild($doc);

    readfile(CONFIG(INSTALL_DIR)."/out/$filename$ext");
}

function ef_main($variables) {

    if ($variables["download"]) {
	ef_custom_page();
	return ef_main_download($variables);
    }

    $docpointer=$variables["docpointer"];
    $submit=isset($variables["B_CONFIRM_x"]);
    list($docclass,$docaction,$doctag)=ef_menu_extract_doc_class(ef_menu_get_nodeid());

    if (isset($docpointer) && $docpointer>0) {
	$document=new ef_document($docpointer);
	$document->load();
	if ($document->DOC_HEADER["docclass"] && $document->DOC_HEADER["docclass"] != $docclass) return;
	if ($submit) {
	    $document->collect_form_data($variables);
	    $document->compute();
	    $document->save();
	    ef_statusbar(ef_msg("M_DOC_SAVED"));
	}
	ef_menu_append_nodeid("ID_{$doctag}_CAMBIA","_docpointer=$docpointer");
	ef_menu_append_nodeid("ID_{$doctag}_VISUALIZZA","_docpointer=$docpointer");
	ef_menu_append_nodeid("ID_{$doctag}_DOWNLOAD","_docpointer=$docpointer");
	switch ($docaction) {
	case "CAMBIA":
	    $form=new ef_form_documento($docclass);
	    break;
	case "DOWNLOAD":
	    $form=new ef_download_documento();
	    break;
	default:
	    $form=new ef_show_documento();
	    ef_printerfriendly("_docpointer=$docpointer&");
	    break;
	}
	return $form->html($document);
    }
    else if ($docaction=="CREA") {
	$document=new ef_document(0);
	if ($submit) {
	    $document->create($docclass);
	    $document->load();
	    $document->collect_form_data($variables);
	    $document->compute();
	    $document->save();
	    ef_statusbar(ef_msg("M_DOC_SAVED"));
	} 
	else {
	    $document=new ef_document(0);
	}
	
	$form=new ef_form_documento($docclass);
	return $form->html($document);
    }
    else {
	$doc_list=ef_get_document_list($docclass,$variables["SORTORDER"],$variables["SORTDIR"]);
	ef_printerfriendly();
	return ef_html_doc_list($doc_list,$variables["SORTORDER"],$variables["SORTDIR"]);
    }
} 

?>
