<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("報告管理情報照会");
LaboLogOut("報告管理情報照会");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>報告管理情報照会</h2></center>

<?php
$sjdate = trim($_REQUEST['SJDATE']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"hokoku.php\" METHOD=POST>\n");
printf("報告指示日\n");
printf("<INPUT TYPE=text NAME=SJDATE SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$sjdate);
printf("　<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");

if (strlen($sjdate) != 0) {

	$udate = "";

	if (!is_numeric($sjdate)) {
		printf("<center>\n");
		printf("<h2>日付入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
	} else {
		if (strlen($sjdate) != 8) {
			printf("<center>\n");
			printf("<h2>日付入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
		} else {
			if (ymd_check($sjdate) == false) {
				printf("<center>\n");
				printf("<h2>日付フォーマットエラー</h2>\n");
				printf("</center>\n");
				printf("<HR>\n");
			} else {
				$udate = ymd_edit($sjdate);
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
					printf("<th nowrap>報告指示日</th>\n");
					printf("<th nowrap>報告指示No</th>\n");
					printf("<th nowrap>報告区分</th>\n");
					printf("<th nowrap>報告条件</th>\n");
					printf("<th nowrap>BML受付年月日</th>\n");
					printf("<th nowrap>処理日</th>\n");
					printf("<th nowrap>検査開始日</th>\n");
					printf("<th nowrap>検査G</th>\n");
					printf("<th nowrap>項目CD</th>\n");
					printf("<th nowrap>分析機区分</th>\n");
					printf("<th nowrap>分析機号機</th>\n");
					printf("<th nowrap>開始SEQ</th>\n");
					printf("<th nowrap>終了SEQ</th>\n");
					printf("<th nowrap>再転送元ファイル名</th>\n");
					printf("<th nowrap>SEC</th>\n");
					printf("<th nowrap>報告ファイル名</th>\n");
					printf("<th nowrap>報告指示担当者</th>\n");
					printf("<th nowrap>報告指示日時</th>\n");
					printf("<th nowrap>作成開始日時</th>\n");
					printf("<th nowrap>作成完了日時</th>\n");
					printf("<th nowrap>転送開始日時</th>\n");
					printf("<th nowrap>転送終了日時</th>\n");
					printf("<th nowrap>作成件数</th>\n");
					printf("<th nowrap>報告保留件数</th>\n");
					printf("<th nowrap>送信元ファイルID</th>\n");
					printf("<th nowrap>報告状況F</th>\n");
					printf("<th nowrap>報告エラーCD</th>\n");
					printf("<th nowrap>緊急依頼LotNo</th>\n");
					printf("<th nowrap>情報更新日時</th>\n");
				printf("</tr>\n");

				$sql = "";
				$sql = $sql . "select * ";
				$sql = $sql . "from hkkknri ";
				$sql = $sql . "where hkksjymd >= '$udate' ";
				$sql = $sql . "order by hkksjymd,hkksjno ";
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
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[17]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[18]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[19]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[20]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[21]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[22]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[23]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[24]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[25]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[26]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[27]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[28]));
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

