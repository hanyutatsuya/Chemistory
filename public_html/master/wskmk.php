<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("検査G・項目マスタ");
LaboLogOut("検査G・項目マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>検査G・項目マスタ</h2></center>

<?php
$knsgrp = trim($_REQUEST['KNSGRP']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"wskmk.php\" METHOD=POST>\n");
printf("検査G\n");
printf("<INPUT TYPE=text NAME=KNSGRP SIZE=6 MAXLENGTH=5 value=\"%s\">\n",$knsgrp);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/wskmk_tbl.inc");

if (strlen($knsgrp) != 0) {
	$conn = GetDBConn();

	if ($conn) {
		wskmk_table($conn,$knsgrp);
	} else {
		echo "Connection failed";
	}
	$conn = null;
	printf("<br clear=all>\n");
}

printf("<HR>\n");
LaboBackPage();
printf("<HR>\n");
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
