<?php
    include_once("debug.inc");
include_once("sqlcmd.inc");
include_once("config.inc");

define (PERM_R_FATTURE,"Rf");
define (PERM_W_FATTURE,"Wf");
define (PERM_R_PREVENTIVI,"Rp");
define (PERM_W_PREVENTIVI,"Wp");
define (PERM_R_ANAGRAFICA,"Ra");
define (PERM_W_ANAGRAFICA,"Wa");
define (PERM_R_UTENTI,"Ru");
define (PERM_W_UTENTI,"Wu");

function ef_auth($USERNAME, $PASSWORD) {
    return ef_q_user_auth($USERNAME,$PASSWORD);
}

function ef_auth_logout() {
    unset($GLOBALS["S_USERNAME"]);
    unset($GLOBALS["S_PASSWORD"]);
    unset($GLOBALS["USERID"]);
}

function ef_auth_userdata_string() {
    $userid=$GLOBALS[USERID];
    if ($userid["userid"])
	return ef_msg("M_USERDATA",$userid["username"],$userid["descrizione"]);
}

function ef_userid() {
    return $GLOBALS[USERID]["userid"];
}

function ef_auth_user_exists($username) {
    return ef_q_user_exists($username);
}

function ef_userfirm() {
    $firm=$GLOBALS[USERID]["firm"];
    if (!$firm) $firm=CONFIG(CURRENT_FIRM);
}

function ef_perm($PERM) {
    $permstr=$GLOBALS[USERID]["permessi"];
    return ef_permstr($permstr,$PERM);
}

function ef_permstr($STR,$PERM) {
    return eregi($PERM,$STR);
}

?>
