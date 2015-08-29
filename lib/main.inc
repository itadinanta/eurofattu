<?php //$Id: main.inc,v 1.3 2001/12/12 23:44:53 nicola Exp $
    include_once("debug.inc");
include_once("config.inc");
include_once("text.inc");
include_once("auth.inc");

function ef_begin() {

    session_register("S_DOCPOINTER");
    session_register("S_PAGEPOINTER");
    session_register("S_LANGUAGE");
    session_register("S_FORNITORE");
    session_register("S_CLIENTE");
    session_register("S_USERNAME");
    session_register("S_PASSWORD");

    ef_config_read();
    if (CONFIG(DEBUG_ENABLED)) ef_debug_begin();
    ef_text_init();
    
    // Authentication ------------------------------
    GLOBAL
	$USERNAME, $S_USERNAME,
	$PASSWORD, $S_PASSWORD,
	$USERID;

    if (!$USERNAME) $USERNAME=$S_USERNAME;
    if (!$PASSWORD) $PASSWORD=$S_PASSWORD;

    ef_db_init();

    if ($USERID=ef_auth($USERNAME, $PASSWORD)) {
	$S_USERNAME=$USERNAME;
	$S_PASSWORD=$PASSWORD;
    }
}

function ef_end() {

    ef_db_close();
    ef_text_close();
    ef_debug_end();
    
}
    
?>
