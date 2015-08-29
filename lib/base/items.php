<?php // $Id: items.php,v 1.3 2001/12/31 17:23:23 nicola Exp $
    include_once("debug.inc");    
include_once("form.inc");
include_once("generic_table.inc");
include_once("records.inc");

class ef_form_articoli extends ef_form {
    function ef_form_articoli() {
	$this->ef_form();
    }
    function html($fd_articolo) {
	$this->cat_list=ef_q_list_categorie();
	$this->anag_list=ef_q_contact_list();

	$this->begin_form(9);
	if ($fd_articolo["codice"])
	    $this->statictext(2,ef_msg("M_CODICE"),"fd_articolo[codice]",$fd_articolo["codice"]);
	else
	    $this->input(2,ef_msg("M_CODICE"),"fd_articolo[codice]",$fd_articolo["codice"],5,5);
	$this->input(5,ef_msg("M_ITEMNAME"),"fd_articolo[articolo]",$fd_articolo["articolo"],30,50);
	$this->select(2,ef_msg("M_ITEMCATEGORY"),"fd_articolo[categoria]",$fd_articolo["categoria"],$this->cat_list);

 	$this->textarea(9,ef_msg("M_ITEMDESCRIPTION"),"fd_articolo[descrizione]",$fd_articolo["descrizione"],70,5);

	$this->input(2,ef_msg("M_ITEMUNIT"),"fd_articolo[um]",$fd_articolo["um"],15,15);
	$this->input(3,ef_msg("M_ITEMPRICEUNIT"),"fd_articolo[costounitario]",$fd_articolo["costounitario"],16,16);
	$this->input(2,ef_msg("M_ITEMVAT"),"fd_articolo[iva]",$fd_articolo["iva"],4,4);
	$this->checkbox(2,ef_msg("M_ITEMCONSUMABLE"),"fd_articolo[consumabile]",$fd_articolo["consumabile"]=='t');

	$this->select(2,ef_msg("M_ITEMPROVIDER"),"fd_articolo[fornitore]",$fd_articolo["fornitore"],$this->anag_list,SELECT_OPTIONAL);
	$this->input(3,ef_msg("M_ITEMPROVIDERCODE"),"fd_articolo[codicefornitore]",$fd_articolo["codicefornitore"],20,20);
	$this->input(2,ef_msg("M_ITEMPROVIDERDISCOUNT"),"fd_articolo[sconto]",$fd_articolo["sconto"],4,4);
	$this->fill();
	if (!$this->read_only()) $this->buttonbar(9,"C");

	$this->end_form();

	return $this->get_accumulator();
    }
}

class ef_articoli_runner extends ef_table_runner {
    function create_form() {
	return new ef_form_articoli();
    }
    function create_object() {
	return new ef_articoli($this->codice);
    }
}

function ef_main($variables) {
    $codice_articolo=$variables["cod_ARTICOLI"];
    if (!$codice_articolo) $codice_articolo=$variables["fd_articolo"]["codice"];
    list($tableaction,$tabletag)=ef_menu_extract_table_class(ef_menu_get_nodeid());

    $table_runner=new ef_articoli_runner($tableaction,$tabletag,$codice_articolo,$variables["fd_articolo"],isset($variables["B_CONFIRM_x"]));

    return $table_runner->run();
}
?>
