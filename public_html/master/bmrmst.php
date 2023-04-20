<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("分類マスタ");
NsfrLogOut("分類マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>分類マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>分類区分</th>
<th>プライオリティ</th>
<th>分類名</th>
<th>略称</th>
<th>ラック本数</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfbmrmst where ukflg = '1' order by brkbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['BRKBN']);
		printf("<td>%s</td>\n",$row['PRIORITY']);
		printf("<td>%s</td>\n",$row['BRNM']);
		printf("<td>%s</td>\n",$row['BRNMR']);
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
