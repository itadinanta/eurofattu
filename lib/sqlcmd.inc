<?php // $Id: sqlcmd.inc,v 1.13 2002/01/18 00:03:50 nicola Exp $

    include_once("debug.inc");
include_once("config.inc");
include_once("db.inc");
include_once("records.inc");

function ef_q_menu() {
    if (func_num_args()) {
	$arg=func_get_arg(0);
	if ($arg == (int)$arg)
	    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM MENU WHERE MENUID=$arg");
	else
	    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM MENU WHERE NODEID='$arg'");
    }
    else
	return ef_db_get_result(DB_MULTIROW,"SELECT * FROM MENU WHERE ENABLED ORDER BY ORDER_NUM");
}

function ef_sql_update_clause($REC,$fields,$format="%s") {
    foreach ($fields as $field) {
	$value=$REC[sprintf($format,$field)];
	if ($value!="")
	    $updates[]="$field='$value'";
	else
	    $updates[]="$field=NULL";
    }
    return join(",",$updates);
}

function ef_sql_insert_clause($REC,$fields,$format="%s") {
    foreach ($fields as $field)
	$values[]="'".$REC[sprintf($format,$field)]."'";

    return join(",",$fields)." VALUES ".join(",".$values);
}

function ef_q_user_auth($USERNAME,$PASSWORD) {
    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM UTENTI WHERE USERNAME='$USERNAME' AND PASSWORD='$PASSWORD'");
}

function ef_q_user($USERID) {
    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM UTENTI WHERE USERID=$USERID");
}

function ef_q_user_exists($USERNAME) {
    $result=ef_db_get_result(DB_SINGLEROW,"SELECT USERID FROM UTENTI WHERE USERNAME='$USERNAME'");
    return $result["userid"];
}

function ef_q_banca($CODICE) {
    if (!$CODICE) return;
    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM VIEW_BANCHE WHERE CODICE=$CODICE");
} 

function ef_q_bank_list() {
    return ef_db_get_result(DB_LIST,"SELECT BANCHE.CODICE, BANCHE.RAGSOC || ' - ' || INDIRIZZO.LOCALITA ".
			    "FROM BANCHE,INDIRIZZO WHERE BANCHE.FILIALE=INDIRIZZO.CODICE ORDER BY BANCHE.RAGSOC");
}

function ef_q_list_categorie() {
    return ef_db_get_result(DB_LIST,"SELECT CODICE, CATEGORIA from CATEGORIE order by CATEGORIA");
}

function ef_q_categorie() {
    return ef_db_get_result(DB_LIST,"SELECT CODICE, CATEGORIA from CATEGORIE order by CODICE");
}

function ef_q_save_categorie($new_categorie) {
    $old_categorie=ef_q_categorie();
    foreach ($new_categorie as $nuovo_codice=>$nuova_categoria) {
	if (!isset($old_categorie[$nuovo_codice]))
	    $add_list[$nuovo_codice]=$nuova_categoria;
	else if ($old_categorie[$nuovo_codice]!=$nuova_categoria)
	    $modify_list[$nuovo_codice]=$nuova_categoria;
    }
    foreach ($old_categorie as $vecchio_codice=>$vecchia_categoria)
	if (!isset($new_categorie[$vecchio_codice]))
	    $delete_list[]=$vecchio_codice;

    $cmds[]="BEGIN";
    if (is_array($add_list)) foreach($add_list as $nuovo_codice=>$nuova_categoria) $cmds[]="INSERT INTO CATEGORIE (CODICE, CATEGORIA) VALUES($nuovo_codice,'$nuova_categoria')";
    if (is_array($modify_list)) foreach($modify_list as $nuovo_codice=>$nuova_categoria) $cmds[]="UPDATE CATEGORIE SET CATEGORIA='$nuova_categoria' WHERE CODICE=$nuovo_codice";
    if (is_array($delete_list)) $cmds[]="DELETE FROM CATEGORIE WHERE CODICE IN (".join(",",$delete_list).")";
    $cmds[]="COMMIT";
    if (count($cmds)>2) return ef_db_run($cmds);
}

function ef_q_docclass($DOCCLASS) {
    return ef_db_get_result(DB_SINGLEROW,"SELECT D.CODICE as CODICE, D.MODDOC as MODDOC, D.ANNO as ANNO, D.TIPODOC as TIPODOC,".
			    "T.DESCRIZIONE as DESCRIZIONE, T.MOSTRACLIENTE as MOSTRACLIENTE, T.MOSTRAFORNITORE as MOSTRAFORNITORE,".
			    "T.RITENUTA as RITENUTA ".
			    "FROM DOCCLASS D,TIPIDOCUMENTI T ".
			    "WHERE D.TIPODOC=T.CODICE ".
			    "AND D.CODICE=$DOCCLASS");
}

function ef_q_contact($CONTACT) {
    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM VIEW_ANAGRAFICA WHERE CODICE='$CONTACT'");
}

function ef_q_contact_list() {
    return ef_db_get_result(DB_LIST,"SELECT CODICE, CODICE || ' - ' || substr(RAGSOC,1,30) FROM ANAGRAFICA order by RAGSOC");
}

function ef_q_document_list($DOCCLASS, $SORTORDER="", $SORTDIR=0) {
    if (!$SORTORDER) $SORTORDER="NPROG, SUBNUM";
    $docclass=ef_q_docclass($DOCCLASS);
    $SORTMODE=($SORTDIR?"ASC":"DESC");
    if ($docclass["mostracliente"]=='t') $FLDCLIENTI="CLIENTE";
    if ($docclass["mostrafornitore"]=='t') $FLDCLIENTI="FORNITORE";
    return ef_db_get_result(DB_TABLEHEADINGS,"SELECT D.DOCPOINTER, D.NPROG, D.SUBNUM, D.DATAEMISSIONE, C.RAGSOC as $FLDCLIENTI, D.DESCRIZIONE, TOTALE ".
			    "FROM DOCUMENTI D, ANAGRAFICA C WHERE C.CODICE=D.$FLDCLIENTI and DOCCLASS=$DOCCLASS ORDER BY $SORTORDER $SORTMODE");
}

function ef_q_table_list($TABLE, $SORTORDER, $SORTDIR=0) {
    $SORTMODE=($SORTDIR?"DESC":"ASC");
    if ($SORTORDER)
	return ef_db_get_result(DB_TABLEHEADINGS,"SELECT * FROM $TABLE ORDER BY $SORTORDER $SORTMODE");
    else
	return ef_db_get_result(DB_TABLEHEADINGS,"SELECT * FROM $TABLE");
}

function ef_q_get_document($docpointer) {
    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM VIEW_DOCUMENTI WHERE DOCPOINTER=$docpointer");
}

function ef_q_get_document_rows($docpointer) {
    return ef_db_get_result(DB_MULTIROW,"SELECT * FROM VIEW_RIGHE WHERE DOCPOINTER=$docpointer");
}

function ef_q_create_indirizzo() {
    ef_db_run("BEGIN");
    $result=ef_db_get_result(DB_SINGLEROW,"SELECT INDIRIZZO_NEW() as CODICE");
    if ($result["codice"]) ef_db_run("COMMIT");
    else ef_db_run("ROLLBACK");
    return $result;
}

function ef_q_save_indirizzo($REC) {
    $codice=$REC["codice"];
    if (!$codice) $codice=ef_q_crea_indirizzo();
    
    ef_db_run("UPDATE INDIRIZZO SET ".
	      ef_sql_update_clause($REC,ef_rec_fields("INDIRIZZO")).
	      " WHERE CODICE=$codice");
    return $codice;
}

function ef_q_create_anagrafica($CODICE="") {
    ef_db_run(array("BEGIN",
		    "INSERT INTO ANAGRAFICA (CODICE, RAGSOC, SEDELEGALE, SEDEAMMINISTRATIVA, SEDEOPERATIVA) ".
		    "VALUES('$CODICE','<New>',INDIRIZZO_NEW(),INDIRIZZO_NEW(),INDIRIZZO_NEW())",
		    "COMMIT"));
    $data=ef_db_get_result(DB_SINGLEROW,"SELECT CODICE FROM ANAGRAFICA WHERE CODICE='$CODICE'");
    return $data["codice"];
}

function ef_q_create_banca($CODICE) {
    if (!$CODICE) {
	$codice=ef_db_get_result(DB_SINGLEROW,"SELECT NEXTVAL('BANCHESEQ') as CODICE");
	$CODICE=$codice["codice"];
    }

    ef_db_run(array("BEGIN",
		    "INSERT INTO BANCHE (CODICE, RAGSOC, FILIALE) VALUES($CODICE,'<New>',INDIRIZZO_NEW())",
		    "COMMIT"));
    $data=ef_db_get_result(DB_SINGLEROW,"SELECT CODICE FROM BANCHE WHERE CODICE=$CODICE");
    return $data["codice"];
}

function ef_q_create_articolo($CODICE) {
    if (!$CODICE) {
	$codice=ef_db_get_result(DB_SINGLEROW,"SELECT NEXTVAL('ARTICOLISEQ') as CODICE");
	$CODICE=$codice["codice"];
    }

    return ef_db_run("INSERT INTO ARTICOLI (CODICE) VALUES ($CODICE)");
}

function ef_q_save_articolo($REC) {
    return ef_db_run("UPDATE ARTICOLI SET ".
		     ef_sql_update_clause($REC,ef_rec_fields("ARTICOLI")).
		     " WHERE CODICE=".$REC["codice"]);
}

function ef_q_articolo($CODICE) {
    return ef_db_get_result(DB_SINGLEROW,"SELECT * from ARTICOLI where CODICE=$CODICE");
}

function ef_q_delete_articolo($CODICE) {
    return ef_db_run("DELETE FROM ARTICOLI WHERE CODICE=$CODICE");
}

function ef_q_delete_anagrafica($CODICE) {
    $sedi=ef_db_get_result(DB_SINGLEROW,"SELECT SEDELEGALE,SEDEAMMINISTRATIVA,SEDEOPERATIVA from ANAGRAFICA where CODICE='$CODICE'");
    $cmds[]="BEGIN";
    $cmds[]="DELETE FROM ANAGRAFICA WHERE CODICE='$CODICE'";
    if ($sedi["sedelegale"]) $cmds[]="DELETE FROM INDIRIZZO WHERE CODICE=$sedi[sedelegale]";
    if ($sedi["sedeamministrativa"]) $cmds[]="DELETE FROM INDIRIZZO WHERE CODICE=$sedi[sedeamministrativa]";
    if ($sedi["sedeoperativa"]) $cmds[]="DELETE FROM INDIRIZZO WHERE CODICE=$sedi[sedeoperativa]";
    $cmds[]="COMMIT";
    ef_db_run($cmds);
}

function ef_q_extract_sede($REC,$sede,$codice) {
    $fields=ef_rec_fields("INDIRIZZO");
    foreach ($fields as $field)
	$sede_rec[$field]=$REC[$field.$sede];
    $sede_rec["codice"]=$codice;
    return $sede_rec;
}

function ef_q_save_anagrafica($REC) {
    ef_db_run("BEGIN");
    $CODICE=$REC["codice"];
    $sedi=ef_db_get_result(DB_SINGLEROW,"SELECT SEDELEGALE,SEDEAMMINISTRATIVA from ANAGRAFICA where CODICE='$CODICE'");
    if ($sedi["sedelegale"]) {
	$sede=ef_q_extract_sede($REC,"legale",$sedi["sedelegale"]);
	ef_q_save_indirizzo($sede);
    }
    if ($sedi["sedeamministrativa"]) {
	$sede=ef_q_extract_sede($REC,"amm",$sedi["sedeamministrativa"]);
	ef_q_save_indirizzo($sede);
    }
    if ($sedi["sedeoperativa"]) {
	$sede=ef_q_extract_sede($REC,"op",$sedi["sedeoperativa"]);
	ef_q_save_indirizzo($sede);
    }
    ef_db_run(array("UPDATE ANAGRAFICA SET ".ef_sql_update_clause($REC,ef_rec_fields("ANAGRAFICA"))." WHERE CODICE='$CODICE'",
		    "UPDATE DOCUMENTI SET DATAMODIFICA=CURRENT_TIMESTAMP WHERE CLIENTE='$CODICE' or FORNITORE='$CODICE'",
		    "COMMIT"));
};


function ef_q_save_banca($REC) {
    ef_db_run("BEGIN");
    $CODICE=$REC["codice"];
    $sede=ef_db_get_result(DB_SINGLEROW,"SELECT FILIALE from BANCHE where CODICE=$CODICE");
    if ($sede["filiale"]) {
	$sede=ef_q_extract_sede($REC,"legale",$sede["filiale"]);
	ef_q_save_indirizzo($sede);
    }
    ef_db_run("UPDATE BANCHE SET ".
	       ef_sql_update_clause($REC,ef_rec_fields("BANCHE")).
	       " WHERE CODICE=$CODICE");

    ef_db_run("COMMIT");
}

function ef_q_save_menuitem($MENUITEM) {
    
}

function ef_q_save_document($DOC_HEADER, $DOC_ROWS) {
    $DOCPOINTER=$DOC_HEADER["docpointer"]; 
    if (!$DOCPOINTER) return; 
    $fields=ef_rec_fields("DOCUMENTI");
    foreach  ($fields as $field)  
	$update.=", $field=".(($DOC_HEADER[$field]=="")?"NULL":"'".$DOC_HEADER[$field]."'");
	
    $riga=1;

    $cmds[]="BEGIN";
    $cmds[]="UPDATE DOCUMENTI SET DATAMODIFICA=CURRENT_TIMESTAMP$update".
	"WHERE DOCPOINTER=$DOCPOINTER";
    $cmds[]="DELETE FROM RIGHEDOCUMENTI WHERE DOCPOINTER=$DOCPOINTER"; 
    if (is_array($DOC_ROWS)) foreach($DOC_ROWS as $ROW) {
	if ($ROW["iva"]=="") $ROW["iva"]=$ROW["a_iva"];
	if ($ROW["descrizione"]=="") $ROW["descrizione"]=$ROW["a_descrizione"];
	if ($ROW["costo"]=="") $ROW["costo"]=$ROW["a_costo"];
	$cmds[]="INSERT INTO RIGHEDOCUMENTI ".
	    "(DOCPOINTER, RIGA, RIFARTICOLO, COSTO, QUANTITA, PREZZOU, IMPONIBILE, IVA, TOTALE, NPEZZI, DESCRIZIONE, NOTE) VALUES".
	    "($DOCPOINTER,$riga,'$ROW[rifarticolo]','$ROW[costo]','$ROW[quantita]','$ROW[prezzou]','$ROW[imponibile]','$ROW[iva]','$ROW[totale]','$ROW[npezzi]','$ROW[descrizione]','$ROW[note]')";
	$riga++;
    }
    $cmds[]="UPDATE DOCUMENTI SET DATAMODIFICA=CURRENT_TIMESTAMP WHERE DOCPOINTER=$DOCPOINTER";
  
    $cmds[]="COMMIT";
    ef_db_run($cmds);
}

function ef_q_create_document($DOCCLASS) {
    ef_db_run("BEGIN");
    $result=ef_db_get_result(DB_SINGLEROW,"SELECT DOC_NEW($DOCCLASS) as DOCPOINTER");
    if ($result["docpointer"]) ef_db_run("COMMIT");
    else ef_db_run("ROLLBACK");
    return $result;
}

function ef_q_get_document_browse($DOCCLASS,$NPROG) {
    $PREV=$NPROG-1;
    $NEXT=$NPROG+1;

    return ef_db_get_result(DB_LIST,"SELECT NPROG,DOCPOINTER FROM DOCUMENTI ".
			    "WHERE NPROG in ($NEXT, $PREV) and DOCCLASS=$DOCCLASS");
}

function ef_q_item_list() {
    return ef_db_get_result(DB_LIST,"SELECT CODICE, CODICE || ' - ' || ARTICOLO as ARTICOLO FROM ARTICOLI");
}

function ef_q_item($CODICE) {
    return ef_db_get_result(DB_SINGLEROW,"SELECT * FROM ARTICOLI WHERE CODICE=$CODICE");
}

function ef_q_table_utenti() {
    return ef_db_get_result(DB_TABLE,"SELECT USERID, USERNAME, DESCRIZIONE from UTENTI order by USERID");
}

function ef_q_create_utente() {
    $result=ef_db_get_result(DB_SINGLEROW,"SELECT UTENTE_NEW() as NUOVO_UTENTE");
    return $result["nuovo_utente"];
}

function ef_q_delete_utente($userid) {
    return ef_db_run("DELETE FROM UTENTI WHERE USERID=$userid");
}

function ef_q_save_utente($REC) {
    $codice=$REC["userid"];
    if (!$codice) $codice=ef_q_create_utente();
    
    ef_db_run("UPDATE UTENTI SET ".ef_sql_update_clause($REC,ef_rec_fields("UTENTI"))." WHERE USERID=$codice");
    return $codice;
}
    
?>
