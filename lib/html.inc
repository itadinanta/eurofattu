<?php //$Id: html.inc,v 1.6 2001/12/31 17:26:52 nicola Exp $
    include_once("text.inc");
include_once("debug.inc");

function ef_html_format_table($body, $headings=null) {
    $btr=ef_msg("M_TABLE_ROW_FORMAT");
    $btd=ef_msg("M_TABLE_DIV_FORMAT");
    $htr=ef_msg("M_TABLE_HROW_FORMAT");
    $htd=ef_msg("M_TABLE_HDIV_FORMAT");
    $result.=ef_msg("M_TABLE_BEGIN");
    
    if (is_array($headings)) {
	foreach ($headings as $heading) $row.=sprintf($htd,$heading);
	$result.=sprintf($htr,$row);
    }

    if (is_array($body)) {
	foreach ($body as $bodyrow) {
	    $row="";
 	    if (is_array($bodyrow)) {
		foreach ($bodyrow as $element) $row.=sprintf($btd,$element);
		$result.=sprintf($btr,$row);
	    } else {
		$result.=sprintf($btr,sprintf($btd,$bodyrow));
	    }
	}
    }

    $result.=ef_msg("M_TABLE_END");
    return $result;
}

function ef_html_link($NODE,$TEXT,$PARAMETERS="") {
    if (!$PARAMETERS)
	return ef_msg("M_ELEMENT_LINK_NOPAR",$NODE,$TEXT);
    if (!is_array($PARAMETERS)) 
	$PARAMETERS=array($PARAMETERS);
    $parstring=join("&",$PARAMETERS);
    return ef_msg("M_ELEMENT_LINK",$NODE,$parstring,$TEXT);
}

function ef_html_format_address($contact) {
    return ef_msg("M_MAIL_ADDRESS",
		  $contact["ragsoc"],
		  $contact["indirizzolegale"],
		  $contact["caplegale"],
		  $contact["localitalegale"],
		  $contact["provlegale"],
		  $contact["statolegale"],
		  ($contact["partitaiva"]?ef_msg("M_PARTITAIVA")." ".$contact["partitaiva"]:""),
		  ($contact["codicefiscale"]?ef_msg("M_CODICEFISCALE")." ".$contact["codicefiscale"]:"")
		  );
}

?>
