<?php //$Id: db.inc,v 1.6 2001/12/25 01:24:29 nicola Exp $

    include_once("config.inc");
include_once("debug.inc");

define (DB_SINGLETON,      1);
define (DB_ASSOC,          2);
define (DB_NUM,            4);
define (DB_ROWASSOC,       8);
define (DB_HEADINGS,      16);
define (DB_SKIPFIRSTCOL,  32);
define (DB_JOIN,          64);

define (DB_LIST,         104); 
define (DB_TABLE,          0);
define (DB_TABLEHEADINGS, 16);
define (DB_SINGLEROW,      3);
define (DB_MULTIROW,       2);
define (DB_HASHTABLE,     10);

function ef_db_init() {
    global $db;
    $connect_string=
	"host=".CONFIG("DB_HOST").
	" port=".CONFIG("DB_PORT").
	" dbname=".CONFIG("DB_NAME").
	" user=".CONFIG("DB_USER").
	" password=".CONFIG("DB_PASSWORD");


    $db=pg_connect($connect_string);
    DEBUG($connect_string,"pg_connect");
    if (!$db) DEBUG(pg_errormessage($db),"pg_connect");
    return $db;
}

function ef_db_get() {
    global $db;
    return $db;
}

function ef_db_run($queries) {
    $db=ef_db_get();
    if (!$db) return;

    if (!is_array($queries)) $queries=array($queries);
    foreach ($queries as $query) {
	$result=pg_exec($query);
	if (!$result) {
	    $err=pg_errormessage($db);
	    DEBUG($err,"ef_db_run");
	    $results[]=$err;
	}
	else {
	    pg_freeresult($result);
	    $results[]="OK";
	}
	DEBUG($query,"ef_db_run");
    }

    return $results;
}

function ef_db_get_result($MODE, $query) {
    $db=ef_db_get();
    if (!$db) return;
    $result=pg_exec($query);
    if ($result) {
	if (($MODE & DB_ASSOC) && ($MODE & DB_NUM)) 
	    $QUERY_MODE=PGSQL_BOTH;
	else 
	    if ($MODE & DB_ASSOC) $QUERY_MODE=PGSQL_ASSOC;
	else 
	    $QUERY_MODE=PGSQL_NUM;
	
	if (($MODE & DB_HEADINGS)) {
 	    $fn=pg_numfields($result);
	    for ($i=0;$i<$fn;$i++) $colnames[$i]=pg_fieldname($result,$i);
	}
	$nrows=pg_numrows($result);
	for ($irow=0; $irow < $nrows; $irow++) {
	    $row=pg_fetch_array($result, $irow, $QUERY_MODE);
	    if ($row === false) break;
	    if ($MODE & DB_ROWASSOC) {
		reset($row);
		$row_key=current($row);
	    }
	    if ($MODE & DB_SKIPFIRSTCOL) $row=array_slice($row,1);
	    if ($MODE & DB_JOIN) $row=join("",$row);
	    if ($MODE & DB_SINGLETON) {
		$table=$row;
		break;
	    } 
	    else if ($MODE & DB_ROWASSOC) {
		$table[$row_key]=$row;
	    }
	    else 
		$table[]=$row;
	}
	pg_freeresult($result);
    }
    else 
	DEBUG(pg_errormessage($db),sprintf("ef_db_get_result_err[%04x]",$MODE));
    DEBUG($query,sprintf("ef_db_get_result[%04x]",$MODE));

    if (($MODE & DB_HEADINGS)) 
	return array ($table, $colnames);
    else
	return $table;
}

function ef_db_close() {
    global $db;
    if ($db) @pg_close($db);
}
    
?>
