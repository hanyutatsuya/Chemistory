<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("検査結果フラグ異常確認");
LaboLogOut("検査結果フラグ異常確認");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>検査結果フラグ異常確認</h2></center>

<?php
$utkymd = trim($_REQUEST['UTKYMD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"pg12.php\" METHOD=POST>\n");
printf("受付日\n");
printf("<INPUT TYPE=text NAME=UTKYMD SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$utkymd);
printf("　<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");

if (strlen($utkymd) != 0) {

	$udate = "";

	if (!is_numeric($utkymd)) {
		printf("<center>\n");
		printf("<h2>受付日入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
	} else {
		if (strlen($utkymd) != 8) {
			printf("<center>\n");
			printf("<h2>受付日入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
		} else {
			if (ymd_check($utkymd) == false) {
				printf("<center>\n");
				printf("<h2>受付日フォーマットエラー</h2>\n");
				printf("</center>\n");
				printf("<HR>\n");
			} else {
				$udate = ymd_edit($utkymd);
			}
		}
	}
}

printf("<HR>\n");

if (strlen($udate) != 0) {

	$conn = GetDBConn();

	if ($conn) {

		try {
			printf("<table align=\"center\" bgcolor = white border>\n");
				printf("<tr>\n");
					printf("<th nowarp>BML受付年月日</th>\n");
					printf("<th nowarp>依頼書No</th>\n");
					printf("<th nowarp>項目CD</th>\n");
				printf("</tr>\n");
	
				$sql = "";
				$sql = $sql . "select * ";
				$sql = $sql . "from knsgmst ";
				$sql = $sql . "for read only with ur ";

				$stnt = $conn->query($sql);
				$colnum = $stmt->columnCount;
				while ($row = $stmt->fetch(PDO::FETCH_NUM)) {
					printf("<tr>\n");
					for ($colcnt=0;$colcnt<$colnum;$colcnt++) {
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[$colcnt]));
					}
					printf("</tr>\n");
				}
	
			printf("</table>\n");
	
			printf("<BR clear=all>\n");
		}
		catch (Exception $ex) {
			GetDBErrMsg($ex);
		}

	} else {
		echo "Connection failed";
	}
	$conn = null;
	printf("<br clear=all>\n");
}

printf("<HR>\n");
LaboBackPage();
printf("<HR>\n");
CheckTailOut();

?>

<HR>
</BODY>
</HTML>

