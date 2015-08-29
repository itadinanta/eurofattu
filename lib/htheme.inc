<?php //$Id: htheme.inc,v 1.9 2001/12/31 17:26:24 nicola Exp $
    
    include_once("debug.inc");

define (ELEMENT_BLANK,   1);
define (ELEMENT_INPUT,   2);
define (ELEMENT_LISTBOX ,3);
define (ELEMENT_RADIOBOX,4);
define (ELEMENT_CHECKBOX,5);
define (ELEMENT_TEXTAREA,6);
define (ELEMENT_STATIC,  7);
define (ELEMENT_TITLE,   8);
define (ELEMENT_BUTTON,  9);
define (ELEMENT_HIDDEN, 10);
define (ELEMENT_SEPARATOR,11);
define (ELEMENT_SELECT,12);
define (ELEMENT_SELECT_OPTIONS,13);
define (ELEMENT_GBUTTON,14);
define (SELECT_OPTIONAL,1);

class ef_theme {
    function ef_theme() {}
    function begin_form($cols,$action,$method) {return ef_msg(M_FORM_BEGIN,$action,$method);}
    function end_form() {return ef_msg(M_FORM_END);}
    function begin_table($cols) {return ef_msg(M_TABLE_BEGIN);}
    function end_table() {return ef_msg(M_TABLE_END);}


    function begin_row($cols) {return ef_msg(M_FORM_ROW_BEGIN);}
    function end_row() {return ef_msg(M_FORM_ROW_END);}
    function begin_span($cols) {}
    function end_span() {}
    
    function raw_element($ELEMENT_TYPE,$PARAMETERS=null) {
	switch ($ELEMENT_TYPE) {
	case ELEMENT_BUTTON:
	    $retval.=ef_msg("M_ELEMENT_RAW_BUTTON",$PARAMETERS[NAME],$PARAMETERS[VALUE]);
	    break;
	case ELEMENT_GBUTTON:
	    $retval.=ef_msg("M_ELEMENT_RAW_GBUTTON",$PARAMETERS[IMAGE],$PARAMETERS[NAME],$PARAMETERS[VALUE]);
	    break;
	case ELEMENT_SELECT: 
	    $retval.=ef_msg("M_ELEMENT_RAW_SELECT",
			    $PARAMETERS["NAME"],
			    $this->raw_element(ELEMENT_SELECT_OPTIONS,
					       $PARAMETERS));
	    break;
	case ELEMENT_SELECT_OPTIONS: {
	    $values=$PARAMETERS["VALUES"];
	    $value=$PARAMETERS["VALUE"];
	    $optional=($PARAMETERS["OPTIONS"] & SELECT_OPTIONAL) > 0;
	    if (!is_array($values)) $values=array($value => $value);
	    if (!isset($values[$value])) {
		if (!$optional) {
		    $value_list=array_keys($values);
		    $value=$value_list[0];
		}
		else $value="";
	    }

	    if ($optional) $optionlist.=ef_msg("M_ELEMENT_OPTION",
					       "",
					       ef_msg("M_ELEMENT_UNSELECTED"),
					       ef_msg("M_ELEMENT_NULLOPTION"));
	    foreach ($values as $current_key=>$current_value) {
		$current_selection=
		    ($current_key == $value)
		    ?ef_msg("M_ELEMENT_SELECTED")
		    :ef_msg("M_ELEMENT_UNSELECTED");
		$optionlist.=
		    ef_msg("M_ELEMENT_OPTION",
			   $current_key,
			   $current_selection,
			   $current_value);		
	    }
	    $retval=$optionlist;
	}	    
	    break;
	}
	return $retval;
    }

    function element($COL_SPAN, $ELEMENT_TYPE, $PARAMETERS=null) {
	if (isset($PARAMETERS[LABEL]) && $PARAMETERS[LABEL]!="<!null>") {
	    $COL_SPAN--;
	    $retval.=ef_msg(M_ELEMENT_LABEL,$PARAMETERS[LABEL]);
	}
	
	switch ($ELEMENT_TYPE) {
	case ELEMENT_SEPARATOR:
	    $retval.=ef_msg("M_ELEMENT_TITLE{$PARAMETERS[LEVEL]}",$COL_SPAN,$PARAMETERS["TITLE"]);
	    break;
	case ELEMENT_HIDDEN:
	    $retval.=ef_msg("M_ELEMENT_HIDDEN",$PARAMETERS["NAME"],$PARAMETERS["VALUE"]);
	    break;
	case ELEMENT_STATIC:
	    $retval.=ef_msg("M_ELEMENT_STATIC",$COL_SPAN,$PARAMETERS["VALUE"]);
	    break;
	case ELEMENT_SELECT:
	    $retval.=ef_msg("M_ELEMENT_SELECT",
			    $COL_SPAN,
			    $PARAMETERS["NAME"],
			    $this->raw_element(ELEMENT_SELECT_OPTIONS,$PARAMETERS));
	    break;
	case ELEMENT_CHECKBOX:
	    $retval.=ef_msg(M_ELEMENT_CHECKBOX,$COL_SPAN,$PARAMETERS[NAME],$PARAMETERS[VALUE],$PARAMETERS[CHECKED]?ef_msg(M_ELEMENT_CHECKED):ef_msg(M_ELEMENT_UNCHECKED),$PARAMETERS[EXTRALABEL]);
	    break;
	case ELEMENT_BLANK:
	    $retval.=ef_msg(M_ELEMENT_BLANK,$COL_SPAN);
	    break;
	case ELEMENT_BUTTON:
	    $retval.=ef_msg(M_ELEMENT_BUTTON,$COL_SPAN,$PARAMETERS[NAME],$PARAMETERS[VALUE]);
	    break;
	case ELEMENT_GBUTTON:
	    $retval.=ef_msg(M_ELEMENT_GBUTTON,$COL_SPAN,$PARAMETERS[IMAGE],$PARAMETERS[NAME],$PARAMETERS[VALUE]);
	    break;
	case ELEMENT_INPUT:
	    if ($PARAMETERS["PASSWORD"])
		$retval.=ef_msg(M_ELEMENT_PASSWORD,$COL_SPAN,$PARAMETERS[NAME],$PARAMETERS[VALUE],$PARAMETERS[SIZE],$PARAMETERS[MAXLENGTH]);
	    else
		$retval.=ef_msg(M_ELEMENT_INPUT,$COL_SPAN,$PARAMETERS[NAME],$PARAMETERS[VALUE],$PARAMETERS[SIZE],$PARAMETERS[MAXLENGTH]);
	    break;
	case ELEMENT_TEXTAREA:
	    $retval.=ef_msg(M_ELEMENT_TEXTAREA,$COL_SPAN,$PARAMETERS[NAME],$PARAMETERS[ROWS],$PARAMETERS[COLS],$PARAMETERS[VALUE]);
	    break;
	case ELEMENT_LABEL:
	    $retval.=ef_msg(M_ELEMENT_LABEL,$PARAMETERS[CONTENT]);
	    break;
	case ELEMENT_GENERIC:
	    $retval.=ef_msg(M_ELEMENT_GENERIC,$COL_SPAN,$PARAMETERS[STYLE],$PARAMETERS[CONTENT]);
	    break;
	default:
	    $retval.=ef_msg(M_ELEMENT_GENERIC,$COL_SPAN,$PARAMETERS[NAME]);
	    break;
	}
	return $retval;
    }
}
?>
