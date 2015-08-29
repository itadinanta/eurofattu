 <?php //$Id: generic_table.inc,v 1.2 2001/12/31 17:25:59 nicola Exp $
     
     include_once("debug.inc");

function ef_html_table_list($TABLELIST,$TABLEPOINTERFIELD,$SORTORDER,$SORTDIR) {
    
    list($table,$headings)=$TABLELIST;
    $edit_menu_id=ef_menu_get_id();
    foreach ($headings as $col_name) {
	if ($SORTORDER==$col_name) $SORTDIR=1-$SORTDIR;
	$new_headings[]=ef_html_link($edit_menu_id,ef_msg("M_HT_".strtoupper($col_name)),"SORTORDER=$col_name&SORTDIR=$SORTDIR");
	$empty_row[]="-";
    }
    
    if (is_array($table)) {
	$tlength=count($table);
	for ($i=0; $i<$tlength; $i++) {
	    $table[$i][0]=ef_html_link($edit_menu_id,$table[$i][0],"$TABLEPOINTERFIELD=".$table[$i][0]);
	}
    }
    
    return ef_html_format_table($table, $new_headings);
}

function ef_get_table_list($LIST, $SORTORDER, $SORTDIR) {
    if (!$SORTDIR) $SORTDIR=0;
    $default_sortorders=array("LIST_ANAGRAFICA"=>"ragsoc","LIST_ARTICOLI"=>"codice");
    if (!$SORTORDER) $SORTORDER=$default_sortorders[$LIST];
    return ef_q_table_list($LIST, $SORTORDER, $SORTDIR);
}


class ef_table_runner {

    function ef_table_runner($TABLEACTION, $TABLETAG, $CODICE, $FD, $SUBMIT) {
	$this->tableaction=$TABLEACTION;
	$this->tabletag=$TABLETAG;
	$this->codice=$CODICE;
	$this->fd=$FD;
	$this->submit=$SUBMIT;


    }
    
    function create_form() {}
    function create_object($codice) {}
    
    function run() {
	$codice=$this->codice;
	$tableaction=$this->tableaction;
	$tabletag=$this->tabletag;
	
	if ($codice!="" || $tableaction=="CREA") {
	    if ($codice!="") {
		ef_menu_append_nodeid("ID_{$tabletag}_CAMBIA","_cod_$tabletag=".$codice);
		ef_menu_append_nodeid("ID_{$tabletag}_VISUALIZZA","_cod_$tabletag=".$codice);
		ef_menu_append_nodeid("ID_{$tabletag}_ELIMINA","_cod_$tabletag=".$codice);
	    }
	    
	    if ($this->codice=="" && !$this->submit) {
		$form=$this->create_form();
		return $form->html($this->fd);
	    }
	    else if ($tableaction=="ELIMINA") {
		$submit=$this->submit;
		
		$record=$this->create_object();
		$record->load();
		
		$form=new ef_form();
		
		if ($submit) {
		    $record->delete();
		    $form->begin_form(2);
		    $form->title(1,ef_msg("M_DELETED"));
		    $form->end_form();
		    ef_menu_append_nodeid("ID_{$tabletag}_CAMBIA","");
		    ef_menu_append_nodeid("ID_{$tabletag}_VISUALIZZA","");
		    ef_menu_append_nodeid("ID_{$tabletag}_ELIMINA","");
		    
		}
		else {
		    $record=$this->create_object($codice);
		    $record->load();
		    $this->fd=$record->REC;
		    
		    $form->begin_form(2);
		    $form->title(1,ef_msg("M_CONFIRM_DELETION"));
		    $form->statictext(2,ef_msg("M_CODICE"),"fd[codice]",$this->codice,12,12);
		    $form->buttonbar(2,"C");
		    $form->end_form();
		}
		return $form->get_accumulator();
	    }
	    else {
		$submit=$this->submit;
		$record=$this->create_object();

		if ($submit) {
		    $record->load();
		    
		    $record->collect_form_data($GLOBALS);
		    $record->check();
		    if ($record->good()) {
			if ($tableaction=="CREA" && $GLOBALS["cod_{$tabletag}"]=="")
			    $this->codice=$codice=$record->create();
			
			$record->save();
			ef_statusbar(ef_msg("M_DOC_SAVED"));
		    }
		    else
			ef_statusbar($record->errors());

		    ef_menu_append_nodeid("ID_{$tabletag}_CREA","_cod_{$tabletag}=".$record->CODICE);
		} 
		else 
		    $record->load();
		
		ef_menu_append_nodeid("ID_{$tabletag}_CAMBIA","_cod_{$tabletag}=".$record->CODICE);
		ef_menu_append_nodeid("ID_{$tabletag}_VISUALIZZA","_cod_{$tabletag}=".$record->CODICE);
		ef_menu_append_nodeid("ID_{$tabletag}_ELIMINA","_cod_{$tabletag}=".$record->CODICE);
		
		$form=$this->create_form();
		if ($tableaction!="CAMBIA" && $record->good()) {
		    $form->read_only(true);
		    ef_printerfriendly("_cod_{$tabletag}=".$record->CODICE."&");
		}
		return $form->html($record->REC);
	    }
	}
	else {
	    $table_list=ef_get_table_list("LIST_{$tabletag}",$GLOBALS["SORTORDER"],$GLOBALS["SORTDIR"]);
	    ef_printerfriendly();
	    return ef_html_table_list($table_list,"cod_$tabletag",$GLOBALS["SORTORDER"],$GLOBALS["SORTDIR"]);
	}
    }
}

?>
