<?php //$Id: text.inc,v 1.3 2001/12/16 00:07:24 nicola Exp $
    include_once("debug.inc");
include_once("config.inc");

function ef_text_init() {
    global $dbm;
    $path=CONFIG(MESSAGE_PATH);
    $lang=CONFIG(LANGUAGE);
    $message_file="$path/{$lang}messages.db";
    DEBUG($message_file,"MESSAGE_FILE");
    $dbm=@dba_open($message_file,"r","gdbm");
}

function ef_text_close() {
    global $dbm;
    if ($dbm) dba_close($dbm);
}

function ef_lmsg($msgid) {
    $path=CONFIG(MESSAGE_PATH);
    return @join("\n",file("$path/{$lang}{$msgid}.htm"));
}

function ef_smsg($msgid) {
    global $dbm;
    if (!$dbm) return $msgid;
    if (!dba_exists($msgid,$dbm)) return $msgid;
    return dba_fetch($msgid,$dbm);
}

function ef_raw_msg($msgid) {
    if ($msgid[0]==".") 
	return ef_lmsg(substr($msgid,1));
    else 
	return ef_smsg($msgid);
}

function ef_msg($msgid) {
    $numargs=func_num_args();
    $args=func_get_args();
    $rawmsg=ef_raw_msg($msgid);
    switch ($numargs) {
    case 1: return $rawmsg;
    case 2: return sprintf($rawmsg,$args[1]);
    case 3: return sprintf($rawmsg,$args[1],$args[2]);
    case 4: return sprintf($rawmsg,$args[1],$args[2],$args[3]);
    case 5: return sprintf($rawmsg,$args[1],$args[2],$args[3],$args[4]);
    case 6: return sprintf($rawmsg,$args[1],$args[2],$args[3],$args[4],$args[5]);
    case 7: return sprintf($rawmsg,$args[1],$args[2],$args[3],$args[4],$args[5],$args[6]);
    case 8: return sprintf($rawmsg,$args[1],$args[2],$args[3],$args[4],$args[5],$args[6],$args[7]);
    case 9: return sprintf($rawmsg,$args[1],$args[2],$args[3],$args[4],$args[5],$args[6],$args[7],$args[8]);
    default: return sprintf($rawmsg,$args[1],$args[2],$args[3],$args[4],$args[5],$args[6],$args[7],$args[8],$args[9]);
    }
}

function ef_strmsg($msgid,$repl) {
    $rawmsg=ef_raw_msg($msgid);
    return strtr($rawmsg,$repl);
}

?>
