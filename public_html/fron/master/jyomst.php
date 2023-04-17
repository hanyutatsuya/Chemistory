<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("状態マスタ");
NsfrLogOut("状態マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>状態マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>状態区分</th>
<th>状態名</th>
<th>略称</th>
<th>ラック本数</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = new PDO('odbc:NSFRDB1','nsfr','nsfr');

if  ($conn){
	$sql = "select * from nfjyomst where ukflg = '1' order by jtkbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['JTKBN']);
		printf("<td>%s</td>\n",$row['JTNM']);
		printf("<td>%s</td>\n",$row['JTNMR']);
		printf("<td>%s</td>\n",$row['LCKPCNT']);
		printf("<td>%s</td>\n",$row['STYMD']);
		printf("<td>%s</td>\n",$row['EDYMD']);
		printf("<td>%10.10s</td>\n",$row['SAKHM']);
		printf("<td>%10.10s</td>\n",$row['KOUHM']);
		printf("<td>%s</td>\n",$row['SAGYOID']);
		printf("</tr>\n");
		}
	}
	else
	{
	echo "Connection failed";
	}
$conn = null;

?>

</table>

<?php
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
