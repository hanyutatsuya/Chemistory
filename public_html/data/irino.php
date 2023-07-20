<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("№対応照会");
LaboLogOut("№対応照会");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>№対応照会</h2></center>

<?php
$utkymd = trim($_REQUEST['UTKYMD']);
$irino = trim($_REQUEST['IRINO']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"irino.php\" METHOD=POST>\n");
printf("受付日\n");
printf("<INPUT TYPE=text NAME=UTKYMD SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$utkymd);
printf("　依頼書№\n");
printf("<INPUT TYPE=text NAME=IRINO SIZE=9 MAXLENGTH=7 value=\"%s\">\n",$irino);
printf("　<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");

require_once("comm/kanjya_row.inc");
require_once("comm/irai_row.inc");
require_once("comm/bunchu_row.inc");
require_once("comm/kenzok_row.inc");
require_once("comm/kenorder_row.inc");
require_once("comm/ninsiki_row.inc");
require_once("comm/kenpos_row.inc");
require_once("comm/realchk_row.inc");
require_once("comm/kekka_row.inc");

if (strlen($irino) != 0) {
	printf("<HR>\n");
	$conn = GetDBConn();

	if ($conn) {
		printf("患者情報\n");
		printf("<BR>\n");
		kanjya_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("依頼情報\n");
		printf("<BR>\n");
		irai_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("分注情報\n");
		printf("<BR>\n");
		bunchu_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("検体属性情報\n");
		printf("<BR>\n");
		kenzok_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("検査オーダー情報\n");
		printf("<BR>\n");
		kenorder_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("認識情報\n");
		printf("<BR>\n");
		ninsiki_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("検体ポジション情報\n");
		printf("<BR>\n");
		kenpos_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("リアルチェック情報\n");
		printf("<BR>\n");
		realchk_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

		printf("検査結果情報\n");
		printf("<BR>\n");
		kekka_row($conn,$utkymd,$irino);
		printf("<BR clear=all>\n");

	} else {
		echo "Connection failed";
	}
	$conn = null;
	printf("<br clear=all>\n");
}

printf("<HR>\n");
LaboBackPage();
printf("<HR>\n");
DataTailOut();

?>

<HR>
</BODY>
</HTML>

