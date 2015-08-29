<?php // $Id: index.php,v 1.10 2002/01/18 00:07:14 nicola Exp $
    include_once ("main.inc");
include_once("page.inc");
include_once("form.inc");
include_once("menu.inc");
include_once("html.inc");
include_once("sqlcmd.inc");
include_once("format.inc");
if (!$MENUID) $MENUID=0;
ef_begin();

$MENULIST=ef_menu_load();
$MENUHASH=ef_menu_hash($MENULIST);
$NODEHASH=ef_node_hash($MENULIST);
if (isset($MENUID)) $MENUITEM=$MENULIST[$MENUHASH[$MENUID]];
if (ef_perm($MENUITEM["requires"])) {
    @include("base/$MENUITEM[dynamic].php");
    $authorized=1;
}

DEBUG($MENUITEM,"MENU");
DEBUG($SORTORDER,"SORTORDER");
DEBUG($REQUEST_URI,"REQUEST_URI");
DEBUG($QUERY_STRING,"QUERY_STRING");
DEBUG($SPATH,"SPATH");
if (ef_userid() && $authorized) {
    if (function_exists('ef_main'))
	$page_main=ef_main($GLOBALS);
    else if ($MENUITEM["static"]!="") {
	$page_main=ef_msg($MENUITEM["static"]);
	ef_printerfriendly();
    }
    else
	$page_main=ef_msg(".courtesy");
}
else {
    include_once("forms.inc");
    $form=new ef_form_login();
    $page_main=$form->html();
}

$page_parameters=array("MENULIST"=>$MENULIST,
		       "PRINTABLE"=>isset($PR),
		       "<!--PAGETITLE-->"=>$MENUITEM["link"],
		       "<!--PAGESUBTITLE-->"=>$MENUITEM["description"],
		       "<!--STATUSBAR-->"=>$STATUSBAR,
		       "<!--MENUBAR-->"=>ef_menu_menubar($MENULIST,$MENUHASH,$MENUITEM),
		       "<!--MENUICON-->"=>ef_menuicon_get(),
		       "<!--USERDATA-->"=>ef_auth_userdata_string(),
		       "<!--DATEINFO-->"=>ef_format_date(time()),
		       "<!--SIDEBAR-->"=>ef_menu_sidebar($MENULIST,$MENUHASH,$MENUITEM));

ef_put_page($page_main,$page_parameters);
ef_end();

?>
