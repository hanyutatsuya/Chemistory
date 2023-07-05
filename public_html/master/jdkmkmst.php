<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("自動発生項目マスタ");
LaboLogOut("自動発生項目マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>自動発生項目マスタ</h2></center>

<?php
$kcode = trim($_REQUEST['KMKCD']);
$knsgrp = trim($_REQUEST['KNSGRP']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"jdkmkmst.php\" METHOD=POST>\n");
printf("検査G\n");
printf("<INPUT TYPE=text NAME=KNSGRP SIZE=6 MAXLENGTH=4 value=\"%s\">\n",$knsgrp);
printf("　項目CD\n");
printf("<INPUT TYPE=text NAME=KMKCD SIZE=9 MAXLENGTH=7 value=\"%s\">\n",$kcode);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/jdkmkmst_row.inc");

if (strlen($kcode) != 0) {
	$conn = GetDBConn();

	if ($conn) {
		jdkmkmst_row($conn,$knsgrp,$kcode);
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

