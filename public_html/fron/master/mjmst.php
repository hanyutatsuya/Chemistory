<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("モジュール情報マスタ");
NsfrLogOut("モジュール情報マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>モジュール情報マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>セルNo.</th>
<th>モジュールNo.</th>
<th>モジュール種別</th>
<th>ITEMコード群No.</th>
<th>プロトコルNo.</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from fmjmst where ukflg = '1' order by bccelno,bcmodno for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['BCCELNO']);
		printf("<td>%s</td>\n",$row['BCMODNO']);
		printf("<td>%s</td>\n",$row['BCMODSH']);
		printf("<td>%s</td>\n",$row['ITMCDGNO']);
		printf("<td>%s</td>\n",$row['PROTOCOL']);
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
