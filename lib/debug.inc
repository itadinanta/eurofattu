<?php //$Id: debug.inc,v 1.2 2001/12/10 00:13:41 nicola Exp $
    include_once("config.inc");

function ef_debug_begin() {
    if (!CONFIG(DEBUG_ENABLED)) return;
    GLOBAL $REMOTE_ADDR;
    GLOBAL $debug_file;
    $path=CONFIG(DEBUG_PATH);
    $debug_file=@fopen("$path/debug.$REMOTE_ADDR.htm","wt");
    ef_debug_put("<HTML><HEAD><TITLE>$REMOTE_ADDR</TITLE></HEAD>\n<BODY>\n<H1>$path/debug.$REMOTE_ADDR.htm</H1>\n");
}

function ef_debug_end() {
    GLOBAL $debug_file;

    if ($debug_file) {
	fputs($debug_file,"</BODY></HTML>\n");
	fclose($debug_file);    
	unset($debug_file);
    }
}

function ef_debug_put($string) {
    GLOBAL $debug_file;
    if ($debug_file) fputs($debug_file,$string);
}

function ef_debug_string($structure,$level) {
    if (is_object($structure))
	$structure=get_object_vars($structure);
    
    $color_=255-$level*5;
    $color=sprintf("#%02x%02x%02x",$color_,$color_,$color_);
    
    if ($level>10) { 
	$retval="...";
    } 
    else if (is_array($structure)) {
	$retval="<TABLE BORDER=0 CELLPADDING=2 CELLSPACING=2>";
	foreach($structure as $key=>$value)
	    $retval.="<TR><TD VALIGN=TOP BGCOLOR=$color>$key</TD><TD VALIGN=TOP BGCOLOR=$color>".ef_debug_string($value,$level+1)."</TD></TR>\n";
	$retval.="</TABLE>";
    }
    else {
	$retval=htmlentities($structure);
    }
    return $retval;
}

function DEBUG($structure,$label) {
    $retval="<TABLE BORDER=1 CELLPADDING=2 CELLSPACING=2><TR><TD VALIGN=TOP>$label</TD><TD VALIGN=TOP>".ef_debug_string($structure,1)."</TD></TABLE>\n";
    ef_debug_put($retval);
}
    
?>
