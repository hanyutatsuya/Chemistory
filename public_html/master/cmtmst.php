<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("コメントマスタ");
LaboLogOut("コメントマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>コメントマスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th nowrap>コメントCD</th>
		<th nowrap>コメント記号</th>
		<th nowrap>コメント名カナ</th>
		<th nowrap>コメント名漢字</th>
		<th nowrap>検査結果１</th>
		<th nowrap>検査結果補足</th>
		<th nowrap>赤伝F</th>
		<th nowrap>異常値マーク</th>
		<th nowrap>開始年月日</th>
		<th nowrap>廃止年月日</th>
		<th nowrap>変更担当者ＩＤ</th>
		<th nowrap>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from cmtmst order by cmcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",$row['CMCD']);
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CMTKG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CMTNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CMTNMJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKKA1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAHSKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AKADEN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IJOUCHI']));
				printf("<td nowrap>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td nowrap>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td nowrap>%s</td>\n",$row['HNKTNTID']);
				printf("<td nowrap>%10.10s</td>\n",$row['KSNDH']);
			printf("</tr>\n");
		}
	}
	catch (Exception $ex) {
		GetDBErrMsg($ex);
	}

} else {
	echo "Connection failed";
}

$conn = null;

?>

</table>

<HR>
<P>
<center><A href=../master/master.php>マスター一覧に戻る</A></center>
</P>

<HR>
</BODY>
</HTML>
