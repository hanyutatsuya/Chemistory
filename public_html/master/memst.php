<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("分析機マスタ");
LaboLogOut("分析機マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>分析機マスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th>分析機区分</th>
		<th>分析機ライン</th>
		<th>分析機号機</th>
		<th>分析機名称</th>
		<th>分析機略称</th>
		<th>号機別名称</th>
		<th>最大測定数</th>
		<th>開始年月日</th>
		<th>廃止年月日</th>
		<th>変更担当者ＩＤ</th>
		<th>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if  ($conn){

try {
	$sql = "select * from memst order by bskkbn,sbklne,bskgok for read only";
	foreach ($conn->query($sql) as $row) {
		printf("<tr>\n");
			printf("<td>%s</td>\n",SjToUtfConv($row[0]));
			printf("<td>%s</td>\n",SjToUtfConv($row[1]));
			printf("<td>%s</td>\n",SjToUtfConv($row[2]));
			printf("<td>%s</td>\n",SjToUtfConv($row[3]));
			printf("<td>%s</td>\n",SjToUtfConv($row[4]));
			printf("<td>%s</td>\n",SjToUtfConv($row[5]));
			printf("<td>%s</td>\n",SjToUtfConv($row[6]));
			printf("<td>%10.10s</td>\n",$row['KAIYMD']);
			printf("<td>%10.10s</td>\n",$row['HAIYMD']);
			printf("<td>%s</td>\n",$row['HNKTNTID']);
			printf("<td>%20.20s</td>\n",$row['KSNDH']);
		printf("</tr>\n");
	}
}
	catch (Exception $ex) {
		LaboLogOut(sprintf("ERRMSG  [%s]",$ex->getMessage()));
		LaboLogOut(sprintf("ERRCODE [%s]",$ex->getCode()));
		printf("ERRMSG  [%s]<BR>",$ex->getMessage());
		printf("ERRCODE [%s]<BR>",$ex->getCode());
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
