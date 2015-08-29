<?php
    include_once("debug.inc");
include_once("sqlcmd.inc");

function ef_rec_fields($TABLE,$OPTIONS="") {
    switch ($TABLE) {
    case "DOCUMENTI":return array("codiceiso","dataemissione","datacompilazione",
				  "datascadenza","datasaldo","cliente","fornitore",
				  "descrizione","tipopagamento","oneri","note",
				  "opzionistampa","costo","imponibile","iva","totale",
				  "totalepagato","npezzi");
    case "INDIRIZZO":return array("tipocontatto", "cognome", "nome",
				  "titolo", "indirizzo", "localita", "stato", 
				  "cap", "prov", "tel", "fax", "cellulare",
				  "web", "email"); 
    case "ANAGRAFICA":return array("ragsoc","tipo","partitaiva","codicefiscale",
				   "numeroconto","banca","logo","ritenuta","ricarico");

    case "UTENTI":return array("username","password","descrizione","permessi");
	
    case "ARTICOLI":return array("categoria","articolo","um","consumabile","fornitore",
				 "codicefornitore","costounitario","iva","sconto","descrizione");

    case "BANCHE":return array("ragsoc","abi","cab","cin");
    }
}

class ef_record {
    function ef_record($codice) {$this->CODICE=$codice;}
    function save() {}
    function delete() {}
    function create() {}
    function load() {}
    function err($err) {$this->errlist[]=$err;}
    function errors() {return $this->errlist;}
    function good() {return !is_array($this->errlist);}
    function check() {return 1;}
    function collect_form_data($variables) {}
}

class ef_anagrafica extends ef_record {
    function save() {
	if ($this->REC["codice"]=="")
	    $this->REC["codice"]=$this->CODICE;
	ef_q_save_anagrafica($this->REC);
    }

    function check() {
	return 1;
    }

    function collect_form_data($variables) {
	$new_rec=$variables["fd_anagraf"];
	foreach ($new_rec as $key=>$value)
	    $this->REC[$key]=$value;
	DEBUG($this->REC,"COLLECT_ANAGRAFICA");
    }

    function delete() {
	ef_q_delete_anagrafica($this->CODICE);
    }

    function create() {
	$this->CODICE=ef_q_create_anagrafica($this->CODICE);
    }

    function load() {
	$this->REC=ef_q_contact($this->CODICE);
    }
}

class ef_banche extends ef_record {
    function save() {
	if ($this->REC["codice"]=="")
	    $this->REC["codice"]=$this->CODICE;
	ef_q_save_banca($this->REC);
    }

    function check() {
	return 1;
    }

    function collect_form_data($variables) {
	$new_rec=$variables["fd_banca"];
	foreach ($new_rec as $key=>$value) $this->REC[$key]=$value;
	DEBUG($this->REC,"COLLECT_BANCA");
    }

    function delete() {
	ef_q_delete_banca($this->CODICE);
    }

    function create() {
	$this->CODICE=ef_q_create_banca($this->CODICE);
    }

    function load() {
	$this->REC=ef_q_banca($this->CODICE);
    }
}

class ef_articoli extends ef_record {
    function save() {
	if ($this->REC["codice"]=="") $this->REC["codice"]=$this->CODICE;
	ef_q_save_articolo($this->REC);
    }

    function check() {return 1;}

    function collect_form_data($variables) {
	$new_rec=$variables["fd_articolo"];
	foreach ($new_rec as $key=>$value)
	    $this->REC[$key]=$value;
	$this->REC["consumabile"]=$new_rec["consumabile"];
	DEBUG($new_rec,"COLLECT_ARTICOLO");
    }

    function delete() {
	ef_q_delete_articolo($this->CODICE);
    }

    function create() {
	$this->CODICE=ef_q_create_articolo($this->CODICE);
    }

    function load() {
	$this->REC=ef_q_articolo($this->CODICE);
    }
}

class ef_utenti extends ef_record {

    function save() {
	if ($this->REC["userid"]=="") $this->REC["userid"]=$this->CODICE;
	ef_q_save_utente($this->REC);
    }

    function collect_form_data($variables) {
	$rec=$variables["fd_utente"];
	foreach ($rec as $key=>$value) $this->REC[$key]=$value;
	if ($rec["PERM_R_FATTURE"]) $perms[]=PERM_R_FATTURE;
	if ($rec["PERM_W_FATTURE"]) $perms[]=PERM_W_FATTURE;
	if ($rec["PERM_R_PREVENTIVI"]) $perms[]=PERM_R_PREVENTIVI;
	if ($rec["PERM_W_PREVENTIVI"]) $perms[]=PERM_W_PREVENTIVI;
	if ($rec["PERM_R_ANAGRAFICA"]) $perms[]=PERM_R_ANAGRAFICA;
	if ($rec["PERM_W_ANAGRAFICA"]) $perms[]=PERM_W_ANAGRAFICA;
	if ($rec["PERM_R_UTENTI"]) $perms[]=PERM_R_UTENTI;
	if ($rec["PERM_W_UTENTI"]) $perms[]=PERM_W_UTENTI;	
	
	if (is_array($perms))
	    $this->REC["permessi"]=join(",",$perms);
	else
	    $this->REC["permessi"]="-";

	DEBUG($this->REC,"COLLECT_UTENTE");
    }

    function delete() {
	ef_q_delete_utente($this->CODICE);
    }

    function create() {
	$this->CODICE=ef_q_create_utente();
    }

    function load() {
	$this->REC=ef_q_user($this->CODICE);
    }

    function check() {
	if (!$this->REC["userid"] && ef_auth_user_exists($this->REC["username"])) $this->err(ef_msg("ERR_USEREXISTS",$this->REC["username"]));
	if ($this->REC["password"]=="") $this->err(ef_msg("ERR_PASSWORDEMPTY"));
	if ($this->REC["password"]!=$this->REC["c_password"]) $this->err(ef_msg("ERR_PASSWORDCONFIRM"));
    }
}

?>
