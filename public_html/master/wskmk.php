<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("WS・項目マスタ");
LaboLogOut("WS・項目マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>サンプリング・項目マスタ</h2></center>

<?php
$kmkcd = trim($_REQUEST['SMPCD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"wskmk.php\" METHOD=POST>\n");
printf("項目コード\n");
printf("<INPUT TYPE=text NAME=KMKCD SIZE=9 MAXLENGTH=7 value=\"%s\">\n",$kmkcd);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/wskmk_tbl.inc");

if (strlen($kmkcd) != 0) {
	$conn = GetDBConn();

	if ($conn) {
		wskmk_table($conn,$kmkcd);
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
