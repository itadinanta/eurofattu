<?php // $Id: categories.php,v 1.1 2001/12/31 17:22:35 nicola Exp $
    include_once("debug.inc");    
include_once("form.inc");

class ef_form_categorie extends ef_form {
    function ef_form_categorie() {
	$this->ef_form();
    }
   
    function collect_data($glb) {
	$codici=$glb["fd_categoria_codice"];
	$categorie=$glb["fd_categoria_categoria"];
	$n=count($codici);
	for ($i=0;$i<$n;$i++)
	    if ($codici[$i]!="")
		$fd_categorie[$codici[$i]]=$categorie[$i];
	return $fd_categorie;
    }

    function save($fd_categorie) {
	ef_q_save_categorie($fd_categorie);
    }
    
    function html($fd_categorie) {
	$this->begin_form(2);
	$this->labels(ef_msg("M_HT_CODICECATEGORIA"),ef_msg("M_HT_CATEGORIA"));
	foreach ($fd_categorie as $codice=>$categoria) {
	    $this->input(1,"<!null>","fd_categoria_codice[]",$codice,10,10);
	    $this->input(1,"<!null>","fd_categoria_categoria[]",$categoria,35,35);
	}
	$this->input(1,"<!null>","fd_categoria_codice[]","",10,10);
	$this->input(1,"<!null>","fd_categoria_categoria[]","",35,35);
	$this->buttonbar(2,"C");

	$this->end_form();
	return $this->get_accumulator();
    }
}

function ef_main($glb) {
    $form=new ef_form_categorie();
    $submit=isset($glb["B_CONFIRM_x"]);
    if ($submit) {
	$categorie=$form->collect_data($glb);
	$form->save($categorie);
	ef_statusbar(ef_msg("M_DOC_SAVED"));
    }
    $categorie=ef_q_categorie();
    return $form->html($categorie);
}

?>
