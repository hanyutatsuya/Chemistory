<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("コントロール情報照会");
LaboLogOut("コントロール情報照会");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>コントロール情報照会</h2></center>

<?php
$sjdate = trim($_REQUEST['SJDATE']);
$bsklne = trim($_REQUEST['BSKLNE']);
$kmkcd = trim($_REQUEST['KMKCD']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"control.php\" METHOD=POST>\n");
printf("検査開始日\n");
printf("<INPUT TYPE=text NAME=SJDATE SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$sjdate);
printf("　分析機ライン\n");
printf("<INPUT TYPE=text NAME=BSKLNE SIZE=4 MAXLENGTH=2 value=\"%s\">\n",$bsklne);
printf("　項目コード\n");
printf("<INPUT TYPE=text NAME=KMKCD SIZE=8 MAXLENGTH=5 value=\"%s\">\n",$kmkcd);
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

$meline = "";
if (strlen($bsklne) != 0) {
	$meline = sprintf("%02d",$bsklne);

}

$kcode = "";
if (strlen($kmkcd) != 0) {
	$kcode = sprintf("%07d",$kmkcd);
}


printf("<HR>\n");

if (strlen($udate) != 0) {

	$conn = GetDBConn();

	if ($conn) {

		try {
			printf("<table align=\"center\" bgcolor = white border>\n");
				printf("<tr>\n");
					printf("<th nowrap>検査開始日</th>\n");
					printf("<th nowrap>分析機区分</th>\n");
					printf("<th nowrap>分析機LINE</th>\n");
					printf("<th nowrap>分析機号機</th>\n");
//					printf("<th nowrap>検査G</th>\n");
					printf("<th nowrap>項目CD</th>\n");
					printf("<th nowrap>内部項目CD</th>\n");
					printf("<th nowrap>CtrlNo</th>\n");
					printf("<th nowrap>Ctrl種別</th>\n");
//					printf("<th nowrap>Ctrl種別枝番</th>\n");
					printf("<th nowrap>CtrlLevel</th>\n");
					printf("<th nowrap>QL・QTフラグ</th>\n");
//					printf("<th nowrap>ARACKID</th>\n");
//					printf("<th nowrap>ARACKPOS</th>\n");
					printf("<th nowrap>検査SEQ</th>\n");
					printf("<th nowrap>分析機SEQ</th>\n");
//					printf("<th nowrap>検査BatNo</th>\n");
//					printf("<th nowrap>検査BatSeq</th>\n");
					printf("<th nowrap>試薬LotNo</th>\n");
					printf("<th nowrap>測定値</th>\n");
					printf("<th nowrap>換算値</th>\n");
					printf("<th nowrap>換算値設定F</th>\n");
					printf("<th nowrap>測定日時</th>\n");
					printf("<th nowrap>Ctrl状態</th>\n");
					printf("<th nowrap>チェック済みF</th>\n");
					printf("<th nowrap>Factor</th>\n");
					printf("<th nowrap>Base</th>\n");
					printf("<th nowrap>校正状態</th>\n");
					printf("<th nowrap>校正担当者</th>\n");
					printf("<th nowrap>校正日時</th>\n");
					printf("<th nowrap>情報更新日時</th>\n");
				printf("</tr>\n");

				$sql = "";
				$sql = $sql . "select * ";
				$sql = $sql . "from ctrlkka ";
				$sql = $sql . "where knskisymd >= '$udate' ";
				if (strlen($meline) != 0) {
					$sql = $sql . "and bsklne = '$meline' ";
				}
				if (strlen($kcode) != 0) {
					$sql = $sql . "and kmkcd = '$kcode' ";
				}
				$sql = $sql . "order by bsklne,bskgok,ctrlno,kmkcd ";
				$sql = $sql . "for read only with ur ";

				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					printf("<tr>\n");
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[0]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[1]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[2]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[3]));
//						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[4]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[5]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[6]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[7]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[8]));
//						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[9]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[10]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[11]));
//						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[12]));
//						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[13]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[14]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[15]));
//						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[16]));
//						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[17]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[18]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[19]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[20]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[21]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[22]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[23]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[24]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[25]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[26]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[27]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[28]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[29]));
						printf("<td nowrap>%19.19s</td>\n",SjToUtfConv($row[30]));
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

