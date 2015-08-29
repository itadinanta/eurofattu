<?php // $Id: format.inc,v 1.2 2001/12/25 01:24:29 nicola Exp $


    function ef_format_currency($amount) {
    return ef_msg("M_FMT_CURR",ef_currency_round($amount));
}

function ef_format_vat($vat) {
    return ef_msg("M_FMT_VAT",$vat);
}

function ef_format_date($date) {
    if (is_int($date)) $time=$date;
    else {
	if (eregi("^([12][0-9][0-9][0-9]).([0-9][0-9]).([0-9][0-9])$",$date,$match))
	    list($string,$year,$month,$day)=$match;
	else if (eregi("^([0-9][0-9]).([0-9][0-9]).([0-9][0-9])$",$date,$match))
	    {list($string,$day,$month,$year)=$match; $year+=1900;}
	else if (eregi("^([0-9][0-9]).([0-9][0-9]).([12][0-9][0-9][0-9])$",$date,$match))
	    list($string,$day,$month,$year)=$match;

	if ($year)
	    $time=mktime(0,0,0,$month,$day,$year);
	else 
	    $time=time();
    }
    return date(ef_msg("M_FMT_DATE"),$time);
}

function ef_currency_round($amount) {
    $round_factor=CONFIG(CURRENCY_ROUND);
    if (!$round_factor) return $amount;
    return round($amount*$round_factor)/$round_factor;
}
?>
