<?php // $Id: banks.php,v 1.1 2001/12/31 17:21:05 nicola Exp $
    include_once("debug.inc");    
include_once("form.inc");
include_once("generic_table.inc");
include_once("records.inc");

class ef_form_banche extends ef_form {
    function ef_form_banche() {
	$this->ef_form();
    }
    
    function sede($TIPO,$fd_banca) {
	$this->input(3,ef_msg("M_COGNOME"),"fd_banca[cognome{$TIPO}]",$fd_banca["cognome{$TIPO}"],25,50);
	$this->input(3,ef_msg("M_NOME"),"fd_banca[nome{$TIPO}]",$fd_banca["nome{$TIPO}"],25,50);

	$this->input(6,ef_msg("M_INDIRIZZO"),"fd_banca[indirizzo{$TIPO}]]",$fd_banca["indirizzo{$TIPO}"],50,50);

	$this->input(2,ef_msg("M_CAP"),"fd_banca[cap{$TIPO}]]",$fd_banca["cap$TIPO"],5,5);
	$this->input(2,ef_msg("M_LOCALITA"),"fd_banca[localita{$TIPO}]]",$fd_banca["localita$TIPO"],20,30);
	$this->input(2,ef_msg("M_PROV"),"fd_banca[prov{$TIPO}]]",$fd_banca["prov$TIPO"],2,2);

	$this->input(2,ef_msg("M_TEL"),"fd_banca[tel{$TIPO}]]",$fd_banca["tel$TIPO"],20,32);
	$this->input(2,ef_msg("M_FAX"),"fd_banca[fax{$TIPO}]]",$fd_banca["fax$TIPO"],20,32);
	$this->input(2,ef_msg("M_CELLULARE"),"fd_banca[cellulare{$TIPO}]]",$fd_banca["cellulare$TIPO"],20,32);

	$this->input(2,ef_msg("M_WEB"),"fd_banca[web{$TIPO}]",$fd_banca["web$TIPO"],25,255);
	$this->input(2,ef_msg("M_EMAIL"),"fd_banca[email{$TIPO}]",$fd_banca["email$TIPO"],25,100);
	$this->fill();
    }

    function html($fd_banca) {
	$bank_list=ef_q_bank_list();

	$this->begin_form(6);
	if ($this->read_only())
	    $this->title(1,$fd_banca["ragsoc"]);

	if ($fd_banca["codice"])
	    $this->statictext(2,ef_msg("M_CODICE"),"fd_banca[codice]",$fd_banca[codice],12,12);
	else
	    $this->input(2,ef_msg("M_CODICE"),"fd_banca[codice]",$fd_banca[codice],12,12);

	if (!$this->read_only())
	    $this->input(4,ef_msg("M_RAGSOC"),"fd_banca[ragsoc]",$fd_banca[ragsoc],30,50);
	else
	    $this->fill();

	$this->input(2,ef_msg("M_ABI"),"fd_banca[abi]",$fd_banca["abi"],5,5);
	$this->input(2,ef_msg("M_CAB"),"fd_banca[cab]",$fd_banca["cab"],5,5);
	$this->input(2,ef_msg("M_CIN"),"fd_banca[cin]",$fd_banca["cin"],5,5);

	$this->title(2,ef_msg("M_FILIALE"));
	$this->sede("legale",$fd_banca); 

	$this->fill();
	if (!$this->read_only()) $this->buttonbar(6,"C");
	$this->end_form();

	return $this->get_accumulator();
    }
}

class ef_banche_runner extends ef_table_runner {
    function create_form() {
	return new ef_form_banche();
    }
    function create_object() {
	return new ef_banche($this->codice);
    }
}

function ef_main($variables) {

    $codice_banche=$variables["cod_BANCHE"];
    if (!$codice_banche) $codice_banche=$variables["fd_banca"]["codice"];
    list($tableaction,$tabletag)=ef_menu_extract_table_class(ef_menu_get_nodeid());
    $table_runner=new ef_banche_runner($tableaction,$tabletag,$codice_banche,$variables["fd_banca"],isset($variables["B_CONFIRM_x"]));

    return $table_runner->run();
}

?>
