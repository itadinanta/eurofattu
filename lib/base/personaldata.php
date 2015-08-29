<?php // $Id: personaldata.php,v 1.7 2002/01/17 23:57:44 nicola Exp $
    include_once("debug.inc");    
include_once("form.inc");
include_once("generic_table.inc");
include_once("records.inc");

class ef_form_anagrafica extends ef_form {
    function ef_form_anagrafica() {
	$this->ef_form();
    }
    
    function sede($TIPO,$fd_anagraf) {
	$this->input(3,ef_msg("M_COGNOME"),"fd_anagraf[cognome{$TIPO}]",$fd_anagraf["cognome{$TIPO}"],25,50);
	$this->input(3,ef_msg("M_NOME"),"fd_anagraf[nome{$TIPO}]",$fd_anagraf["nome{$TIPO}"],25,50);

	$this->input(6,ef_msg("M_INDIRIZZO"),"fd_anagraf[indirizzo{$TIPO}]]",$fd_anagraf["indirizzo{$TIPO}"],50,50);

	$this->input(2,ef_msg("M_CAP"),"fd_anagraf[cap{$TIPO}]]",$fd_anagraf["cap$TIPO"],5,5);
	$this->input(2,ef_msg("M_LOCALITA"),"fd_anagraf[localita{$TIPO}]]",$fd_anagraf["localita$TIPO"],20,30);
	$this->input(2,ef_msg("M_PROV"),"fd_anagraf[prov{$TIPO}]]",$fd_anagraf["prov$TIPO"],2,2);

	$this->input(2,ef_msg("M_TEL"),"fd_anagraf[tel{$TIPO}]]",$fd_anagraf["tel$TIPO"],20,32);
	$this->input(2,ef_msg("M_FAX"),"fd_anagraf[fax{$TIPO}]]",$fd_anagraf["fax$TIPO"],20,32);
	$this->input(2,ef_msg("M_CELLULARE"),"fd_anagraf[cellulare{$TIPO}]]",$fd_anagraf["cellulare$TIPO"],20,32);

	$this->input(2,ef_msg("M_WEB"),"fd_anagraf[web{$TIPO}]",$fd_anagraf["web$TIPO"],25,255);
	$this->input(2,ef_msg("M_EMAIL"),"fd_anagraf[email{$TIPO}]",$fd_anagraf["email$TIPO"],25,100);
	$this->fill();
    }

    function html($fd_anagraf) {
	$bank_list=ef_q_bank_list();

	$this->begin_form(6);
	if ($this->read_only())
	    $this->title(1,$fd_anagraf["ragsoc"]);

	if ($fd_anagraf["codice"])
	    $this->statictext(2,ef_msg("M_CODICE"),"fd_anagraf[codice]",$fd_anagraf[codice],12,12);
	else
	    $this->input(2,ef_msg("M_CODICE"),"fd_anagraf[codice]",$fd_anagraf[codice],12,12);

	if (!$this->read_only())
	    $this->input(4,ef_msg("M_RAGSOC"),"fd_anagraf[ragsoc]",$fd_anagraf[ragsoc],40,150);
	else
	    $this->fill();

	$this->input(2,ef_msg("M_PARTITAIVA"),"fd_anagraf[partitaiva]",$fd_anagraf[partitaiva],11,11);
	$this->input(2,ef_msg("M_CODICEFISCALE"),"fd_anagraf[codicefiscale]",$fd_anagraf[codicefiscale],16,16);
	$this->fill();

	$this->title(2,ef_msg("M_SEDELEGALE"));
	$this->sede("legale",$fd_anagraf); 

	$this->title(2,ef_msg("M_SEDEAMMINISTRATIVA")); 
	$this->sede("amm",$fd_anagraf); 

	$this->title(2,ef_msg("M_DATIBANCA"));

	$this->input(2,ef_msg("M_CONTO"),"fd_anagraf[numeroconto]",$fd_anagraf["numeroconto"],16,16);
	$this->select(2,ef_msg("M_BANCA"),"fd_anagraf[banca]",$fd_anagraf["banca"],$bank_list,SELECT_OPTIONAL);
	$this->fill();
	if (!$this->read_only()) $this->buttonbar(6,"C");
	$this->end_form();

	return $this->get_accumulator();
    }
}

class ef_anagrafica_runner extends ef_table_runner {
    function create_form() {
	return new ef_form_anagrafica();
    }
    function create_object() {
	return new ef_anagrafica($this->codice);
    }
}

function ef_main($variables) {

    $codice_anagrafica=$variables["cod_ANAGRAFICA"];
    if (!$codice_anagrafica) $codice_anagrafica=$variables["fd_anagraf"]["codice"];
    list($tableaction,$tabletag)=ef_menu_extract_table_class(ef_menu_get_nodeid());
    $table_runner=new ef_anagrafica_runner($tableaction,$tabletag,$codice_anagrafica,$variables["fd_anagraf"],isset($variables["B_CONFIRM_x"]));

    return $table_runner->run();
}

?>
