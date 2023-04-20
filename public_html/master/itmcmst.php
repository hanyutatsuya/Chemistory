<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("ＩＴＥＭコードマスタ");
NsfrLogOut("ＩＴＥＭコードマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>ＩＴＥＭコードマスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th nowrap>ITEMコード</th>
<th nowrap>ARACK種類</th>
<th nowrap>仕分けＩＤ</th>
<th nowrap>仕分け識別</th>
<th nowrap>ITEMコード名</th>
<th nowrap>ITEMコード略称</th>
<th nowrap>ラック本数</th>
<th nowrap>開始日</th>
<th nowrap>終了日</th>
<th nowrap>作成時刻</th>
<th nowrap>更新時刻</th>
<th nowrap>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from fitmcmst where ukflg = '1' order by itmcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row['ITMCD']);
		printf("<td nowrap>%s</td>\n",$row['ARKSH']);
		printf("<td nowrap>%s</td>\n",$row['SWKLCKID']);
		printf("<td nowrap>%s</td>\n",$row['ZRLCKNM']);
		printf("<td nowrap>%s</td>\n",$row['ITMNM']);
		printf("<td nowrap>%s</td>\n",$row['ITMNMR']);
		printf("<td nowrap>%s</td>\n",$row['LCKPCNT']);
		printf("<td nowrap>%s</td>\n",$row['STYMD']);
		printf("<td nowrap>%s</td>\n",$row['EDYMD']);
		printf("<td nowrap>%10.10s</td>\n",$row['SAKHM']);
		printf("<td nowrap>%10.10s</td>\n",$row['KOUHM']);
		printf("<td nowrap>%s</td>\n",$row['SAGYOID']);
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
