<?php
    include_once ("main.inc");
include_once("page.inc");
include_once("form.inc");

ef_begin();

$form=new ef_form(new ef_theme());
for ($k=11; $k<20; $k++) {
    $form->begin_form($k);
    $form->title(1,"width: $k");
    for ($i=2; $i<10; $i++) {
	$form->input($i,"Label","name",$i,"20","20");
	if ($i==13) $form->title(2,"separator at $i");
	//	$form->button($i+1,"name","value");
    }
    $form->blank(-1);
    $form->button(1,"Ciao","Mamma");
    $form->end_form();
    $acc.=$form->get_accumulator();
    DEBUG($form,"FORM");
}


ef_put_page($acc);

ef_end();

?>
