<?php //$Id: form.inc,v 1.11 2002/01/18 00:03:14 nicola Exp $

    include_once("debug.inc");
include_once("htheme.inc");

class ef_form {
    var
	$MAX_COL,
	$COL_POINTER,
	$ROW_POINTER,
	$ROW_BEGIN,
	$ROW_END;
    
    var
	$ACCUMULATOR;

    var
	$ACTION, $METHOD, $READONLY;
    var
	$THEME;
    
    function ef_form($theme=null) {
	if (is_object($theme)) $this->THEME=$theme;
	else $this->THEME=$this->create_theme();
	$this->ACTION=$GLOBALS["SCRIPT_NAME"];
	$this->METHOD="post";
    }
    
    function create_theme() {
	return new ef_theme();
    }

    function accumulate($string) {
	$this->ACCUMULATOR.=$string;
    }
    
    function set_action($ACTION) {
	$this->ACTION=$ACTION;
    }
    
    function set_method($METHOD) {
	$this->METHOD=$METHOD;
    }

    function read_only() {
	if (func_num_args())
	    $this->READONLY=func_get_arg(0);
	else
	    return $this->READONLY;
    }
    
    function append($string) {
	    if ($this->ROW_END) {
		$this->accumulate($this->THEME->end_row());
		$this->ROW_END=false;
	    }
	    if ($this->ROW_BEGIN) {
		$this->accumulate($this->THEME->begin_row($this->MAX_COL));
		$this->ROW_BEGIN=false;
	    }
	    $this->accumulate($string);
    }
    
    function init_counters($max_col) {
	$this->MAX_COL=$max_col;
	$this->COL_POINTER=0;
	$this->ROW_POINTER=0;
	$this->ROW_BEGIN=true;
	$this->ROW_END=false;
    }

    function begin_form($max_col) {
	$this->init_counters($max_col);
	$this->ACCUMULATOR=$this->THEME->begin_form($this->MAX_COL, $this->ACTION, $this->METHOD);
    }

    function begin_table($max_col) {
	$this->init_counters($max_col);
	$this->ACCUMULATOR=$this->THEME->begin_table($this->MAX_COL, $this->ACTION, $this->METHOD);
    }
    
    function end_form() {
	$this->fill();
	$this->ROW_BEGIN=false;
	$this->append($this->THEME->end_form());
    }

    function end_table() {
	$this->fill();
	$this->ROW_BEGIN=false;
	$this->append($this->THEME->end_table());
    }
    
    function row_spaceleft() {
	return $this->MAX_COL - $this->COL_POINTER;
    }
    
    function blank($NCOL) {
	if ($NCOL<0) $NCOL=$this->row_spaceleft()+$NCOL;
	if ($NCOL<0) $NCOL+=$this->MAX_COL;
	$COL_SPAN=min($NCOL,$this->MAX_COL);
	if ($NCOL)
	    $this->add_element($NCOL,
			       $this->THEME->element($NCOL, ELEMENT_BLANK,null));
    }
    
    function fill() {
	if ($this->COL_POINTER)
	    $this->blank($this->row_spaceleft());
    }
    
    function advance($NCOL) {
	if (!$NCOL) $NCOL=$this->row_spaceleft();
	if ($NCOL<0) $NCOL=$this->row_spaceleft()+$NCOL;
	$NCOL=min($NCOL,$this->row_spaceleft());

	$this->COL_POINTER+=$NCOL;
	if ($this->COL_POINTER==$this->MAX_COL) {
	    $this->ROW_END=true;
	    $this->ROW_BEGIN=true;
	    $this->ROW_POINTER++;
	    $this->COL_POINTER=0;
	}
    }

    function userelement($COL_SPAN,$label,$content) {
	$this->add_span($COL_SPAN,ELEMENT_GENERIC,array("LABEL"=>$label,"CONTENT"=>$content));
    }

    function labels() {
	$labels=func_get_args();
	$COL_SPAN=count($labels);
	foreach ($labels as $label) 
	    $this->add_element(1,
			       $this->THEME->element(1,ELEMENT_SEPARATOR,
						     array("LEVEL"=>1,
							   "TITLE"=>$label)));

    }

    function buttonbar($COL_SPAN,$button_string) {
	$button_hash=array("C"=>"B_CONFIRM",
			   "D"=>"B_DELETE",
			   "c"=>"B_CANCEL",
			   "L"=>"B_LOGIN",
			   ">"=>"B_NEXT",
			   "<"=>"B_PREV");

	$COL_SPAN=min($COL_SPAN,$this->MAX_COL);
	$n=strlen($button_string);
	for ($i=0;$i<$n;$i++) {
	    $button_descr=$button_hash[$button_string[$i]];
	    if ($button_descr) 
		$content.=$this->THEME->raw_element(ELEMENT_GBUTTON,
						    array("NAME"=>$button_descr,
							  "IMAGE"=>"btn_".ef_msg($button_descr).".png",
							  "VALUE"=>$button_descr));
	}
	
	$this->add_element($COL_SPAN,
			   $this->THEME->element($COL_SPAN,ELEMENT_GENERIC,
						 array("CONTENT"=>$content,
						       "STYLE"=>"buttonbar")));
    }

    function hidden($varname, $value) {
	$this->append($this->THEME->element(0,ELEMENT_HIDDEN,
					    array("NAME"=>$varname,						       
						  "VALUE"=>$value)));
    }

    function label($COL_SPAN,$label,$value) {
	$this->add_span($COL_SPAN,ELEMENT_STATIC,array("LABEL"=>$label,
						       "VALUE"=>($value?$value:ef_msg("M_BLANK_ENTITY"))));
    }

    function statictext($COL_SPAN,$label,$varname="",$value="") {
	$COL_SPAN=min($COL_SPAN,$this->MAX_COL);
	$this->add_element($COL_SPAN,
			   $this->THEME->element($COL_SPAN,ELEMENT_STATIC,
						 array("LABEL"=>$label,
						       "VALUE"=>($value
								 ?nl2br(htmlentities($value)):
								 ef_msg("M_BLANK_ENTITY")))).
			   $this->THEME->element(0,ELEMENT_HIDDEN,
						 array("NAME"=>$varname,
						       "VALUE"=>$value))
			   );
    }

    function add_span($COL_SPAN,$ELEMENT,$PARAMETERS) {
	$COL_SPAN=min($COL_SPAN,$this->MAX_COL);
	$this->add_element($COL_SPAN, $this->THEME->element($COL_SPAN,$ELEMENT,$PARAMETERS));
    }

    function input($COL_SPAN,$label,$varname,$value,$size,$maxlen) {
	if ($this->READONLY) return $this->statictext($COL_SPAN,$label,$varname,$value);
	$this->add_span($COL_SPAN,ELEMENT_INPUT,array("LABEL"=>$label,
						      "NAME"=>$varname,
						      "VALUE"=>$value,
						      "SIZE"=>$size,
						      "MAXLENGTH"=>$maxlen));
    }

    function password($COL_SPAN,$label,$varname,$value,$size,$maxlen) {
	if ($this->READONLY) return $this->statictext($COL_SPAN,$label,$varname,$value);
	$this->add_span($COL_SPAN,ELEMENT_INPUT,array("LABEL"=>$label,
						       "NAME"=>$varname,
						       "VALUE"=>$value,
						       "SIZE"=>$size,
						       "PASSWORD"=>1,
						       "MAXLENGTH"=>$maxlen));
    }

    function textarea($COL_SPAN,$label,$varname,$value,$nrows,$ncols) {
	if ($this->READONLY) return $this->statictext($COL_SPAN,$label,$varname,$value);
	$this->add_span($COL_SPAN,ELEMENT_TEXTAREA,array("LABEL"=>$label,
							 "NAME"=>$varname,
							 "VALUE"=>stripslashes($value),
							 "ROWS"=>$nrows,
							 "COLS"=>$ncols));
    }

    function select($COL_SPAN, $label, $varname, $value, $values, $options=0) {
	if ($this->READONLY) return $this->statictext($COL_SPAN,$label,$varname,$values[$value]);
	$this->add_span($COL_SPAN,ELEMENT_SELECT,array("OPTIONS"=>$options,
						       "LABEL"=>$label,
						       "NAME"=>$varname,
						       "VALUE"=>$value,
						       "VALUES"=>$values));
    }

    function checkbox($COL_SPAN, $label, $varname, $value,$extra_label="") {
	if ($this->READONLY) return $this->statictext($COL_SPAN,$label,$varname,$value?ef_msg("M_YES"):ef_msg("M_NO"));
	$this->add_span($COL_SPAN,ELEMENT_CHECKBOX,array("LABEL"=>$label,
							 "NAME"=>$varname,
							 "VALUE"=>"t",
							 "EXTRALABEL"=>$extra_label,
							 "CHECKED"=>($value!="")));
    }
    
    function button($COL_SPAN,$name,$value) {
	$this->add_span($COL_SPAN,ELEMENT_BUTTON,array("NAME"=>$name,
						       "VALUE"=>$value));
    }

    function title($level,$label) {
	$this->fill();
	$this->add_element($this->MAX_COL,
			   $this->THEME->element($this->MAX_COL, ELEMENT_SEPARATOR,
						 array("LEVEL"=>$level,
						       "TITLE"=>$label)));
    }
    
    function add_element($COL_SPAN,$el_string) {
	$COL_SPAN=min($COL_SPAN,$this->MAX_COL);
	if ($COL_SPAN>$this->row_spaceleft()) $this->fill();

	$this->append($el_string);
	$this->advance($COL_SPAN);
    }

    function get_accumulator() {
	return $this->ACCUMULATOR;
    }
}

function ef_button_pressed($BUTTON) {
    return isset($GLOBALS["$BUTTON"."_x"]);
}

?>
