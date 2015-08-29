<?php

    include_once("text.inc");
include_once("menu.inc");

function ef_is_custom_page() {
    GLOBAL $CUSTOM_PAGE;
    return $CUSTOM_PAGE;
}

function ef_custom_page() {
    GLOBAL $CUSTOM_PAGE;
    $CUSTOM_PAGE=1;
}

function ef_put_page($page_body,$page_options="") {
    if (ef_is_custom_page()) return;
    $page_options["<!--TXT-BODY-->"]=$page_body;
    if ($page_options["PRINTABLE"])
	echo ef_strmsg(".printerfriendly",$page_options);
    else
	echo ef_strmsg(".skeleton",$page_options);
}

?>
