<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
require_once("../comm/labo_comm.inc");
LaboHeadOutput("ログ情報照会");
LaboLogOut("ログ情報照会");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>ログ情報照会</h2></center>

<?php
$sydate = trim($_REQUEST['SYDATE']);

printf("<P>\n");
printf("<center>\n");
printf("<FORM ACTION=\"apllog.php\" METHOD=POST>\n");
printf("日付\n");
printf("<INPUT TYPE=text NAME=SYDATE SIZE=10 MAXLENGTH=8 value=\"%s\">\n",$sydate);
printf("　<BUTTON TYPE=submit name=submit value=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</center>\n");
printf("</P>\n");

if (strlen($sydate) != 0) {

	$udate = "";

	if (!is_numeric($sydate)) {
		printf("<center>\n");
		printf("<h2>日付入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
	} else {
		if (strlen($sydate) != 8) {
			printf("<center>\n");
			printf("<h2>日付入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
		} else {
			if (ymd_check($sydate) == false) {
				printf("<center>\n");
				printf("<h2>日付フォーマットエラー</h2>\n");
				printf("</center>\n");
				printf("<HR>\n");
			} else {
				$udate = ymd_edit($sydate);
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
					printf("<th nowrap>日付</th>\n");
					printf("<th nowrap>時刻</th>\n");
					printf("<th nowrap>TR種別</th>\n");
					printf("<th nowrap>SV名/PC名</th>\n");
					printf("<th nowrap>プロセスID</th>\n");
					printf("<th nowrap>ログインID</th>\n");
					printf("<th nowrap>起動アプリ名</th>\n");
					printf("<th nowrap>ソース名</th>\n");
					printf("<th nowrap>関数名</th>\n");
					printf("<th nowrap>出力行</th>\n");
					printf("<th nowrap>実行F</th>\n");
					printf("<th nowrap>エラーCD</th>\n");
					printf("<th nowrap>メッセージ</th>\n");
				printf("</tr>\n");

				$sql = "";
				$sql = $sql . "select * ";
				$sql = $sql . "from apllog ";
				$sql = $sql . "where sydate = '$udate' ";
				$sql = $sql . "order by sydate,sytime ";
				$sql = $sql . "for read only with ur ";
	
				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					printf("<tr>\n");
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[0]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[1]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[2]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[3]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[4]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[5]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[6]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[7]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[8]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[9]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[10]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[11]));
						printf("<td nowarp>%s</td>\n",SjToUtfConv($row[12]));
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

