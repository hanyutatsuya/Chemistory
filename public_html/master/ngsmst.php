<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("分注ＮＧ処理マスタ");
NsfrLogOut("分注ＮＧ処理マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>分注ＮＧ処理マスタ</h2></center>
<table align="center" bgcolor = "white" border>

<tr>
<th>NG処理コード</th>
<th>詳細コード</th>
<th>分注NG処理名</th>
<th>分注NG詳細処理名</th>
<th>復旧処理送信FLG</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from fngsmst where bcngsscd != '00' and ukflg = '1' order by bcngscd,bcngsscd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['BCNGSCD']);
		printf("<td>%s</td>\n",$row['BCNGSSCD']);
		printf("<td>%s</td>\n",$row['BCNGSNM']);
		printf("<td>%s</td>\n",$row['BCNGSSNM']);
		printf("<td>%s</td>\n",$row['FKSSFLG']);
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
