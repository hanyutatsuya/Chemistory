<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("検査Gマスタ");
LaboLogOut("検査Gマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>検査Gマスタ</h2></center>

<?php
$knsgrp = trim($_REQUEST['KNSGRP']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"knsgmst.php\" METHOD=POST>\n");
printf("検査G\n");
printf("<INPUT TYPE=text NAME=KNSGRP SIZE=6 MAXLENGTH=5 value=\"%s\">\n",$knsgrp);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/knsgmst_tbl.inc");

if (strlen($knsgrp) != 0) {
	$conn = GetDBConn();

	if ($conn) {
		printf("<HR>\n");
		knsgmst_table($conn,$knsgrp);
	} else {
		printf("Connection failed\n");
	}
	$conn = null;
	printf("<br clear=all>\n");

	printf("<HR>\n");
	LaboBackPage();
} else {

}
MasterTailOut();

?>

<HR>
</BODY>
</HTML>
