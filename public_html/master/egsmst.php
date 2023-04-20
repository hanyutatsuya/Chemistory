<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("営業所マスタ");
NsfrLogOut("営業所マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>営業所マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>営業所コード</th>
<th>集配コード(FROM)</th>
<th>集配コード(TO)</th>
<th>新営業所コード</th>
<th>営業所名</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfegsmst where ukflg = '1' order by ecd,shcdfr,shcdto for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['ECD']);
		printf("<td>%s</td>\n",$row['SHCDFR']);
		printf("<td>%s</td>\n",$row['SHCDTO']);
		printf("<td>%s</td>\n",$row['ECD2']);
		printf("<td>%s</td>\n",$row['EGSNM']);
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
