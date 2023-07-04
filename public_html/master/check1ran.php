<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("チェックマスタ一覧");
LaboLogOut("チェックマスタ一覧");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>チェックマスタ一覧</h2></center>

<?php
$kcode = trim($_REQUEST['KMKCD']);
$knsgrp = trim($_REQUEST['KNSGRP']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"check1ran.php\" METHOD=POST>\n");
printf("検査グループ\n");
printf("<INPUT TYPE=text NAME=KNSGRP SIZE=6 MAXLENGTH=4 value=\"%s\">\n",$knsgrp);
printf("　項目コード\n");
printf("<INPUT TYPE=text NAME=KMKCD SIZE=9 MAXLENGTH=7 value=\"%s\">\n",$kcode);
printf("<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");
printf("<HR>\n");

require_once("comm/kmkmst_row.inc");
require_once("comm/rngchkmst_row.inc");
require_once("comm/calckmkmst_row.inc");
require_once("comm/kkafltmst_row.inc");
require_once("comm/krkmkmst_row.inc");
require_once("comm/skchkmst_row.inc");

if (strlen($kcode) != 0) {
	$conn = GetDBConn();

	if ($conn) {
		printf("<P>\n");
		printf("項目マスタ\n");
		kmkmst_row($conn,$knsgrp,$kcode);
		printf("</P>\n");

		printf("<P>\n");
		printf("レンジチェックマスタ\n");
		rngchkmst_row($conn,$knsgrp,$kcode);
		printf("</P>\n");

		printf("<P>\n");
		printf("計算項目マスタ\n");
		calckmkmst_row($conn,$knsgrp,$kcode);
		printf("</P>\n");

		printf("<P>\n");
		printf("結果フィルタマスタ\n");
		kkafltmst_row($conn,$knsgrp,$kcode);
		printf("</P>\n");

		printf("<P>\n");
		printf("関連項目マスタ\n");
		krkmkmst_row($conn,$knsgrp,$kcode);
		printf("</P>\n");

		printf("<P>\n");
		printf("相関項目マスタ\n");
		skchkmst_row($conn,$knsgrp,$kcode);
		printf("</P>\n");

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
