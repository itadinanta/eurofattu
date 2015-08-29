<?php // $Id: forms.inc,v 1.3 2002/01/18 00:03:32 nicola Exp $
    include_once("debug.inc");
    include_once("form.inc");

class ef_form_login extends ef_form {
    function ef_form_login() {
	$this->ef_form();
    }
    function html() {
	$this->begin_form(2);
	$this->input(2,ef_msg("M_USERNAME"),"USERNAME","",16,16);
	$this->password(2,ef_msg("M_PASSWORD"),"PASSWORD","",16,16);
	$this->buttonbar(2,"L");
	$this->end_form();

	return $this->get_accumulator();
    }
}

?>
