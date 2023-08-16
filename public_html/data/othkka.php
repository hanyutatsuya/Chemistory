<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("他サテライト結果一覧");
LaboLogOut("他サテライト結果一覧");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>他サテライト結果一覧</h2></center>

<?php
$utkymd = trim($_REQUEST['UTKYMD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"othkka.php\" METHOD=POST>\n");
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
					printf("<th nowarp>処理日</th>\n");
					printf("<th nowarp>検体No</th>\n");
					printf("<th nowarp>CH文字</th>\n");
					printf("<th nowarp>推定材料CD</th>\n");
					printf("<th nowarp>項目略称</th>\n");
					printf("<th nowarp>親項目CD</th>\n");
					printf("<th nowarp>SEC</th>\n");
					printf("<th nowarp>TBF</th>\n");
					printf("<th nowarp>検査実施LBCD</th>\n");
					printf("<th nowarp>結果状況CD</th>\n");
					printf("<th nowarp>パニックF</th>\n");
					printf("<th nowarp>結果換算F</th>\n");
					printf("<th nowarp>結果修正F</th>\n");
					printf("<th nowarp>検査結果1</th>\n");
					printf("<th nowarp>検査結果2</th>\n");
					printf("<th nowarp>検査結果2区分</th>\n");
					printf("<th nowarp>検査結果補足</th>\n");
					printf("<th nowarp>結果CMT1</th>\n");
					printf("<th nowarp>結果CMT2</th>\n");
					printf("<th nowarp>異常値区分M</th>\n");
					printf("<th nowarp>異常値区分F</th>\n");
					printf("<th nowarp>異常値区分O</th>\n");
					printf("<th nowarp>SDI</th>\n");
					printf("<th nowarp>報告書表記結果</th>\n");
					printf("<th nowarp>報告書表記結果(漢字)</th>\n");
					printf("<th nowarp>基準値No</th>\n");
					printf("<th nowarp>WSCD</th>\n");
					printf("<th nowarp>SEQ</th>\n");
					printf("<th nowarp>情報更新日時</th>\n");
					printf("<th nowarp>情報登録日時</th>\n");
				printf("</tr>\n");

				$sql = "";
				$sql = $sql . "select * from otherkka ";
				$sql = $sql . "where utkymd = '$udate' ";
				$sql = $sql . "order by utkymd,irino ";
				$sql = $sql . "for read only with ur ";
	
				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					printf("<tr>\n");
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[0]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[1]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[2]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[3]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[4]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[5]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[6]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[7]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[8]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[9]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[10]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[11]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[12]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[13]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[14]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[15]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[16]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[17]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[18]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[19]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[20]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[21]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[22]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[23]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[24]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[25]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[26]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[27]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[28]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[29]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[30]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[31]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[32]));
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
DataTailOut();

?>

<HR>
</BODY>
</HTML>

