<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("結果補足マスタ");
LaboLogOut("結果補足マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>結果補足マスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th>結果補足CD</th>
		<th>結果補足名称カナ</th>
		<th>結果補足名称漢字</th>
		<th>開始年月日</th>
		<th>廃止年月日</th>
		<th>変更担当者ＩＤ</th>
		<th>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from kkahskmst order by kkahskcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td>%s</td>\n",$row['KKAHSKCD']);
				printf("<td>%s</td>\n",SjToUtfConv($row['KKAHSKNM']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KKAHSKNMJ']));
				printf("<td>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td>%s</td>\n",$row['HNKTNTID']);
				printf("<td>%20.20s</td>\n",$row['KSNDH']);
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
