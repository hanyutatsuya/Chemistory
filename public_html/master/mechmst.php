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
		<th>分析機区分</th>
		<th>内部項目CD</th>
		<th>チャネル名称</th>
		<th>項目CD</th>
		<th>開始年月日</th>
		<th>廃止年月日</th>
		<th>変更担当者ＩＤ</th>
		<th>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if  ($conn){

	try {
		$sql = "select * from mechmst order by bskkbn,kmkcd,kaiymd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td>%s</td>\n",SjToUtfConv($row[0]));
				printf("<td>%s</td>\n",SjToUtfConv($row[1]));
				printf("<td>%s</td>\n",SjToUtfConv($row[2]));
				printf("<td>%s</td>\n",SjToUtfConv($row[3]));
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
