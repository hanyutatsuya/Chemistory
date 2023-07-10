<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("分析機チャネルマスタ");
LaboLogOut("分析機チャネルマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>分析機チャネルマスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th nowarp>分析機区分</th>
		<th nowarp>内部項目CD</th>
		<th nowarp>チャネル名称</th>
		<th nowarp>項目CD</th>
		<th nowarp>開始年月日</th>
		<th nowarp>廃止年月日</th>
		<th nowarp>変更担当者ＩＤ</th>
		<th nowarp>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if  ($conn){

	try {
		$sql = "select * from mechmst order by bskkbn,kmkcd,kaiymd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row[0]));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row[1]));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row[2]));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row[3]));
				printf("<td nowarp>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td nowarp>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td nowarp>%s</td>\n",$row['HNKTNTID']);
				printf("<td nowarp>%10.10s</td>\n",$row['KSNDH']);
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
