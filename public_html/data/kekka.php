<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("結果照会");
LaboLogOut("結果照会");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>結果照会</h2></center>

<?php
$utkymd = trim($_REQUEST['UTKYMD']);
$irino = trim($_REQUEST['IRINO']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"kekka.php\" METHOD=POST>\n");
printf("受付日\n");
printf("<INPUT TYPE=text NAME=UTKYMD SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$utkymd);
printf("　依頼書№\n");
printf("<INPUT TYPE=text NAME=IRINO SIZE=9 MAXLENGTH=7 value=\"%s\">\n",$irino);
printf("　<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");

require_once("comm/kekka_data.inc");

if (strlen($irino) != 0) {
	printf("<HR>\n");
	$conn = GetDBConn();

	if ($conn) {
		printf("検査結果情報\n");
		printf("<BR>\n");

		kekka_data($conn,$utkymd,$irino);

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

