<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("項目マスタ");
LaboLogOut("項目マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>項目マスタ</h2></center>

<?php
$kcode = trim($_REQUEST['KMKCD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"kmkmst.php\" METHOD=POST>\n");
printf("項目CD\n");
printf("<INPUT TYPE=text NAME=KMKCD SIZE=9 MAXLENGTH=7 value=\"%s\">\n",$kcode);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/kmkmst_tbl.inc");

if (strlen($kcode) != 0) {
	$conn = GetDBConn();

	if ($conn) {
		kmkmst_table($conn,$kcode);
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

