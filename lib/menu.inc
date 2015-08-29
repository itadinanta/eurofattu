<?php // $Id: menu.inc,v 1.8 2001/12/31 17:27:34 nicola Exp $
    include_once("debug.inc");
include_once("sqlcmd.inc");

function ef_menu_load() {
    $MENULIST=ef_q_menu();
    foreach($MENULIST as $KEY=>$VALUE)
	$MENULIST[$KEY]["index"]=$KEY;
    return $MENULIST;
}

function ef_menu_load_item($MENUID) {
    return ef_q_menu($MENUID);
}

function ef_menu_hash(&$MENULIST) {
    foreach($MENULIST as $key=>$menuitem) {
	$MENUHASH[$menuitem["menuid"]]=$key;
    }
    return $MENUHASH;
}

function ef_node_hash(&$MENULIST) {
    foreach($MENULIST as $key=>$menuitem) {
	$NODEHASH[$menuitem["nodeid"]]=$key;
    }
    return $NODEHASH;
}

function ef_menu_mark(&$MENULIST, $MENUITEM) {
    $menuindex=$MENUITEM["index"];
    for ($i=$menuindex; $i>=0; $i--) {
	$menuitem=&$MENULIST[$i];
	if (!$marked[$menuitem["level"]] && 
	    $menuitem["level"]<=$MENUITEM["level"])
	    $marked[$menuitem["level"]]=$i;
    }
    return $marked;
}

function ef_menu_marklevel($marks,$MENUROOT,$MENUITEM) {
    if ($MENUROOT["menuid"]==$MENUITEM["menuid"]) return 2;
    if ($marks[$MENUROOT["level"]]==$MENUROOT["index"]) return 1;
    return "";
}

function ef_menu_menubar(&$MENULIST, $MENUHASH, $MENUITEM) {
    $menuindex=$MENUITEM["index"];
    $marks=ef_menu_mark($MENULIST, $MENUITEM);

    if (isset($menuindex) && $menuindex<count($MENULIST) && 
	$MENULIST[$menuindex+1]["level"]>$MENUITEM["level"])
	$menuroot=$menuindex;
    else
	$menuroot=$marks[$MENUITEM["level"]-1];

    $MENUROOT=$MENULIST[$menuroot];

    $menuroot_level=$MENUROOT["level"];
    $menu_string.=ef_msg("M_MENUBAR_ROOT_FORMAT",
			 ef_menu_marklevel($marks,$MENUROOT,$MENUITEM),
			 $MENUROOT["menuid"].$MENUROOT["extra_link"],
			 $MENUROOT["link"]);	  
    
    $submenuindex=$menuroot+1;
    while (1) {
	$SUBMENU=$MENULIST[$submenuindex];

	if (!$SUBMENU || $SUBMENU["level"]<=$menuroot_level) break;
	if ($SUBMENU["level"]==$menuroot_level+1)
	    $menu_string.=ef_msg("M_MENUBAR_ITEM_FORMAT",
				 ef_menu_marklevel($marks,$SUBMENU,$MENUITEM),
				 $SUBMENU["menuid"].$SUBMENU["extra_link"],
				 $SUBMENU["shortlink"]?$SUBMENU["shortlink"]:$SUBMENU["link"]);
	$submenuindex++;
    }
    $submenuindex=$marks[$MENUROOT["level"]-1];
    if (isset($submenuindex)) {
	$SUBMENU=$MENULIST[$submenuindex];
	$menu_string.=ef_msg("M_MENUBAR_ITEM_FORMAT",
			     ef_menu_marklevel($marks,$SUBMENU,$MENUITEM),
			     $SUBMENU["menuid"].$SUBMENU["extra_link"],
			     $SUBMENU["link"]);
    }
    
    return  ef_msg("M_MENUBAR_FORMAT",
		   $menu_string);
}

function ef_menu_sidebar_item($menuitem,$MENUITEM,$mark) {
    $maxlevel=CONFIG(MENU_LEVEL);
    return ef_msg("M_SIDEBAR_ITEM_FORMAT",
		  $menuitem["level"],
		  $mark,
		  $menuitem["menuid"].$menuitem["extra_link"],
		  $menuitem["shortlink"]?$menuitem["shortlink"]:$menuitem["link"]);	  
}

function ef_menu_sidebar(&$MENULIST, $MENUHASH, $MENUITEM) {
    $menuindex=$MENUITEM["index"];
    $marks=ef_menu_mark($MENULIST, $MENUITEM,$menuindex);
    $maxlevel=CONFIG(MENU_LEVEL);

    foreach($MENULIST as $menuitem)
	if ($menuitem["level"]<=$maxlevel)
	    $menu_string.=ef_menu_sidebar_item($menuitem,
					       $MENUITEM,
					       ef_menu_marklevel($marks,$menuitem,$MENUITEM));
    return ef_msg("M_SIDEBAR_FORMAT",
		  $menu_string);
}

function ef_menu_get_id() {
    return $GLOBALS["MENUID"];
}

function ef_menu_get_item() {
    return $GLOBALS["MENUITEM"];
}

function ef_menu_get_nodeid() {
    return $GLOBALS["MENUITEM"]["nodeid"];
}

function ef_menu_append_nodeid($NODEID, $EXTRA) {
    GLOBAL $MENULIST, $NODEHASH;

    $MENULIST[$NODEHASH[$NODEID]]["extra_link"]=$EXTRA;
}

function ef_menu_get_menuid_by_nodeid($NODEID) {
    GLOBAL $MENULIST, $NODEHASH;

    return $MENULIST[$NODEHASH[$NODEID]]["menuid"];
}

function ef_menu_get_nodeid_by_menuid($MENUID) {
    GLOBAL $MENULIST, $MENUHASH;
    
    return $MENULIST[$MENUHASH[$MENUID]]["nodeid"];
}

function ef_menu_extract_doc_class($NODEID) {
    if (eregi("^ID_([A-Z]+)_([A-Z]+)",$NODEID,$MATCHES)) {

	$DOCACTIONS=array(CONFIG("DOC_".$MATCHES[1]),
		     $MATCHES[2],
		     $MATCHES[1]);
	DEBUG($DOCACTIONS,"DOCACTIONS");
	return $DOCACTIONS;
    }
}

function ef_menu_extract_table_class($NODEID) {
    if (eregi("^ID_([A-Z]+)_([A-Z]+)",$NODEID,$MATCHES)) {
	return array($MATCHES[2], $MATCHES[1]);
    }
}

function ef_statusbar($items) {
    GLOBAL $STATUSBAR;
    if (!is_array($items)) $STATUSBAR.=$items;
    else $STATUSBAR.=join(ef_msg("M_ELEMENT_BR"),$items);
}

function ef_printerfriendly($parameters="_") {
    GLOBAL $MENUICON;
    $MENUICON=ef_msg("M_PRINTERFRIENDLY",ef_menu_get_id(),$parameters);
}

function ef_menuicon_get() {
    GLOBAL $MENUICON;
    return $MENUICON;
}


?>
