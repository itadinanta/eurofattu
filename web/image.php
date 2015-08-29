<?php // $Id: image.php,v 1.1 2001/12/16 00:05:32 nicola Exp $
    include_once("debug.inc");
include_once("config.inc");
include_once("db.inc");
include_once("sqlcmd.inc");

ef_config_read();


if ($BUTTONID) {
    $filename=CONFIG(INSTALL_DIR)."/web/img/button_$BUTTONID.png";
    if (!($im=@imagecreatefrompng($filename))) {
	//    putenv("T1LIB_CONFIG=".CONFIG(INSTALL_DIR)."/font/t1lib.config");
	$im = imagecreatefrompng(CONFIG(INSTALL_DIR)."/web/img/template_button.png");
	$black = imagecolorresolve ($im, 0, 0, 0);
	$bground =imagecolorresolve ($im, 166,214,170);

	$fontname=CONFIG(INSTALL_DIR)."/font/a010015l.pfb";
	$font=imagepsloadfont($fontname);
	if (is_array(imagepstext($im, "$BUTTONID",$font, 14, $black, $bground, 20, 20)) &&
	    CONFIG(CACHE_BUTTONS)) imagepng ($im,$filename);
	imagepsfreefont($font); 
	// image is cached!
    }
}
else if ($MENUID) {
    $filename=CONFIG(INSTALL_DIR)."/web/img/menu_$MENUID.png";
    if (!($im=@imagecreatefrompng($filename))) {
	//    putenv("T1LIB_CONFIG=".CONFIG(INSTALL_DIR)."/font/t1lib.config");
	$im = imagecreate(130,20);
	$black = imagecolorallocate ($im, 0, 0, 0);
	$bground =imagecolorallocate ($im, 166,214,170);
	$white = imagecolorallocate ($im, 255, 255, 255);
	$fontname=CONFIG(INSTALL_DIR)."/font/a010015l.pfb";
	$font=imagepsloadfont($fontname);
	if (is_array(imagepstext($im, "$BUTTONID",$font, 14, $black, $bground, 20, 20)) &&
	    CONFIG(CACHE_BUTTONS)) imagepng ($im,$filename);
	imagepsfreefont($font); 
	// image is cached!
    }
}
header ("Content-type: image/png");
imagepng($im);
imagedestroy ($im);
?>

