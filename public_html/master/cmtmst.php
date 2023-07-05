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
		<th>コメントCD</th>
		<th>コメント記号</th>
		<th>コメント名カナ</th>
		<th>コメント名漢字</th>
		<th>検査結果１</th>
		<th>検査結果補足</th>
		<th>赤伝F</th>
		<th>異常値マーク</th>
		<th>開始年月日</th>
		<th>廃止年月日</th>
		<th>変更担当者ＩＤ</th>
		<th>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from cmtmst order by cmcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td>%s</td>\n",$row['CMCD']);
				printf("<td>%s</td>\n",SjToUtfConv($row['CMTKG']));
				printf("<td>%s</td>\n",SjToUtfConv($row['CMTNM']));
				printf("<td>%s</td>\n",SjToUtfConv($row['CMTNMJ']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KNSKKA1']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KKAHSKCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['AKADEN']));
				printf("<td>%s</td>\n",SjToUtfConv($row['IJOUCHI']));
				printf("<td>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td>%s</td>\n",$row['HNKTNTID']);
				printf("<td>%10.10s</td>\n",$row['KSNDH']);
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
