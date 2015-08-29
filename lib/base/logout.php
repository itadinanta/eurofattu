<?php //$Id: logout.php,v 1.2 2001/12/31 17:22:08 nicola Exp $
  
function ef_main($glb) {
    $submit=isset($glb["B_CONFIRM_x"]);
    $form=new ef_form();
    $form->begin_form(2);

    if (!$submit) {
	$form->title(1,ef_msg("M_CONFIRMLOGOUT"));
	$form->buttonbar(2,"C");
    } else {
	ef_auth_logout();
	$form->title(1,ef_msg("M_LOGGEDOUT"));
    }
    $form->end_form();
    return $form->get_accumulator();

}
  
?>
