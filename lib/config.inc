<?php //$Id: config.inc,v 1.7 2001/12/25 01:24:29 nicola Exp $
    include_once("config.inc");

function CONFIG($config_option) {

    return $GLOBALS["CONFIG_$config_option"];
}

function ef_config_get_option($config_option) {

    return $GLOBALS["CONFIG_$config_option"];
}

function ef_config_set_option($config_option, $value) {
    $wasset=isset($GLOBALS["CONFIG_$config_option"]);
    $GLOBALS["CONFIG_$config_option"]=$value;
    return $wasset;
}

function ef_config_read() {
    GLOBAL
	$SERVER_NAME;

    GLOBAL
	$CONFIG_INSTALL_DIR,
	$CONFIG_HTTP_ROOT_PATH,
	$CONFIG_HTTP_DEFAULT_SERVER,
	$CONFIG_FIRM,
	$CONFIG_CURRENT_FIRM,
	$CONFIG_DB_NAME,
	$CONFIG_DB_TYPE,
	$CONFIG_DB_HOST,
	$CONFIG_DB_PORT,
	$CONFIG_DB_USER,
	$CONFIG_DB_PASSWORD,
	$CONFIG_LANGUAGE,
	$CONFIG_MESSAGE_PATH,
	$CONFIG_DEBUG_PATH,
	$CONFIG_DEBUG_ENABLED,
	$CONFIG_CACHE_BUTTONS,
	$CONFIG_MENU_LEVEL,
	$CONFIG_CONFIG_PATH,
	$CONFIG_CURRENCY,
	$CONFIG_CURRENCY_ROUND,
	$CONFIG_OVERPRICE,
	$CONFIG_DOC_CONTRATTI,
	$CONFIG_DOC_FATTURE,
	$CONFIG_DOC_PREVENTIVI;
	
	$CONFIG_INSTALL_DIR="/home/fattu";
	$CONFIG_HTTP_ROOT_PATH="";
	$CONFIG_HTTP_DEFAULT_SERVER="";
	$CONFIG_FIRM=1;
	$CONFIG_LANGUAGE="";
	$CONFIG_MESSAGE_PATH="$CONFIG_INSTALL_DIR/text";
	$CONFIG_DEBUG_PATH="$CONFIG_INSTALL_DIR/debug";
	$CONFIG_DEBUG_ENABLED=1;
	$CONFIG_CURRENCY="EUR";
	$CONFIG_CURRENCY_ROUND=100;
	$CONFIG_DB_NAME="eurofattu";
	$CONFIG_DB_TYPE="postgresql";
	$CONFIG_DB_HOST="localhost";
	$CONFIG_DB_PORT=5432;
	$CONFIG_CURRENT_FIRM="1";
	$CONFIG_CACHE_BUTTONS=0;
	$CONFIG_DB_USER="eurofattu";
	$CONFIG_MENU_LEVEL=2;
	$CONFIG_OVERPRICE=10;
	$CONFIG_DB_PASSWORD="eurofattu";
	$CONFIG_DOC_CONTRATTI=120020002;
	$CONFIG_DOC_FATTURE=120020001;
	$CONFIG_DOC_PREVENTIVI=120020003;
	
	if (!$CONFIG_CONFIG_PATH) $CONFIG_CONFIG_PATH="/etc/httpd/php";
	@include "$CONFIG_CONFIG_PATH/eurofattu.conf";
	@include "$CONFIG_CONFIG_PATH/eurofattu.$SERVER_NAME.conf";
}
  
?>
