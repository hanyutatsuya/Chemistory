<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("仕分け種類マスタ");
NsfrLogOut("仕分け種類マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>仕分け種類マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>仕分け種類区分</th>
<th>仕分け種類名</th>
<th>略称</th>
<th>推定材料CD</th>
<th>ラック本数</th>
<th>凍結F</th>
<th>不明依頼対象F</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ID</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfssmst where ukflg = '1' order by sskbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['SSKBN']);
		printf("<td>%s</td>\n",$row['ZRNM']);
		printf("<td>%s</td>\n",$row['ZRNMR']);
		printf("<td>%s</td>\n",$row['STZRCD']);
		printf("<td>%s</td>\n",$row['LCKPCNT']);
		printf("<td>%s</td>\n",$row['TKFLG']);
		printf("<td>%s</td>\n",$row['FITFLG']);
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
