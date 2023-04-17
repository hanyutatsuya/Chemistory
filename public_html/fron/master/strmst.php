<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("サテライトマスタ");
NsfrLogOut("サテライトマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>サテライトマスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>STLID</th>
<th>新旧区分</th>
<th>サテライト名称</th>
<th>略称</th>
<th>IPアドレス</th>
<th>PORT1</th>
<th>出力タイミング</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfstrmst where ukflg = '1' order by stid for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['STID']);
		printf("<td>%s</td>\n",$row['SKKBN']);
		printf("<td>%s</td>\n",$row['STNM']);
		printf("<td>%s</td>\n",$row['STNMR']);
		printf("<td>%s</td>\n",$row['IPADD']);
		printf("<td>%s</td>\n",$row['PORT1']);
		printf("<td>%s</td>\n",$row['OUTTMG']);
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
