<?php // $Id: users.php,v 1.2 2001/12/31 17:21:29 nicola Exp $
    include_once("debug.inc");    
include_once("form.inc");
include_once("generic_table.inc");
include_once("records.inc");
include_once("auth.inc");

class ef_form_utenti extends ef_form {
    function ef_form_utenti() {
	$this->ef_form();
    }

    function html_new_password($fd_utente) {
	$this->begin_form(4);
	$this->title(1,ef_msg("M_USERID",$fd_utente["userid"]));
	$this->statictext(4,ef_msg("M_USERNAME"),"fd_utente[username]",$fd_utente["username"]);
	$this->statictext(4,ef_msg("M_USERDESCRIPTION"),"fd_utente[descrizione]",$fd_utente["descrizione"]);
	if (!$fd_utente["userid"]) {
	    $this->password(2,ef_msg("M_USERPASSWORD"),"fd_utente[password]","",16,16);
	    $this->password(2,ef_msg("M_USERCONFIRMPASSWORD"),"fd_utente[c_password]","",16,16);
	}

	$this->buttonbar(9,"C");
	return $this->get_accumulator();

    }

    function html($fd_utente) {
	$this->begin_form(4);
	if ($fd_utente["userid"])
	    $this->title(1,ef_msg("M_USERID",$fd_utente["userid"]));
	else
	    $this->title(1,ef_msg("M_USERNEW"));
	$this->input(4,ef_msg("M_USERNAME"),"fd_utente[username]",$fd_utente["username"],32,32);
	$this->input(4,ef_msg("M_USERDESCRIPTION"),"fd_utente[descrizione]",$fd_utente["descrizione"],50,50);

	if (!$fd_utente["userid"]) {
	    $this->password(2,ef_msg("M_USERPASSWORD"),"fd_utente[password]","",32,32);
	    $this->password(2,ef_msg("M_USERCONFIRMPASSWORD"),"fd_utente[c_password]","",32,32);
	}
	$permstr=$fd_utente["permessi"];
	$this->title(2,ef_msg("M_USERPERMISSIONS"));
	$this->checkbox(2,ef_msg("M_USERPERM_W_FATTURE"),"fd_utente[PERM_W_FATTURE]",ef_permstr($permstr,PERM_W_FATTURE));
	$this->checkbox(2,ef_msg("M_USERPERM_R_FATTURE"),"fd_utente[PERM_R_FATTURE]",ef_permstr($permstr,PERM_R_FATTURE));
	$this->checkbox(2,ef_msg("M_USERPERM_W_PREVENTIVI"),"fd_utente[PERM_W_PREVENTIVI]",ef_permstr($permstr,PERM_W_PREVENTIVI));
	$this->checkbox(2,ef_msg("M_USERPERM_R_PREVENTIVI"),"fd_utente[PERM_R_PREVENTIVI]",ef_permstr($permstr,PERM_R_PREVENTIVI));
	$this->checkbox(2,ef_msg("M_USERPERM_W_ANAGRAFICA"),"fd_utente[PERM_W_ANAGRAFICA]",ef_permstr($permstr,PERM_W_ANAGRAFICA));
	$this->checkbox(2,ef_msg("M_USERPERM_R_ANAGRAFICA"),"fd_utente[PERM_R_ANAGRAFICA]",ef_permstr($permstr,PERM_R_ANAGRAFICA));
	$this->checkbox(2,ef_msg("M_USERPERM_W_UTENTI"),"fd_utente[PERM_W_UTENTI]",ef_permstr($permstr,PERM_W_UTENTI));
	$this->checkbox(2,ef_msg("M_USERPERM_R_UTENTI"),"fd_utente[PERM_R_UTENTI]",ef_permstr($permstr,PERM_R_UTENTI)); 

	if (!$this->read_only()) $this->buttonbar(9,"C");

	$this->end_form();

	return $this->get_accumulator();
    }
}

class ef_utenti_runner extends ef_table_runner {
    function create_form() {
	return new ef_form_utenti();
    }
    function create_object() {
	return new ef_utenti($this->codice);
    }
}

function ef_main($variables) {
    $codice_utente=$variables["cod_UTENTI"];
    if (!$codice_utente) $codice_utente=$variables["fd_utente"]["userid"];
    if (!$codice_utente) $codice_utente=0;
    list($tableaction,$tabletag)=ef_menu_extract_table_class(ef_menu_get_nodeid());

    $table_runner=new ef_utenti_runner($tableaction,$tabletag,$codice_utente,$variables["fd_utente"],isset($variables["B_CONFIRM_x"]));

    return $table_runner->run();
}
?>
