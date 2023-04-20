<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("装置管理マスタ");
NsfrLogOut("装置管理マスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>装置管理マスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>装置No.</th>
<th>装置種類区分</th>
<th>装置名</th>
<th>装置略称</th>
<th>IPアドレス</th>
<th>PORT１</th>
<th>PORT２</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfsotmst where ukflg = '1' order by devno for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['DEVNO']);
		printf("<td>%s</td>\n",$row['DEVKBN']);
		printf("<td>%s</td>\n",$row['DEVNM']);
		printf("<td>%s</td>\n",$row['DEVNMR']);
		printf("<td>%s</td>\n",$row['IPADD']);
		printf("<td>%s</td>\n",$row['PORT1']);
		printf("<td>%s</td>\n",$row['PORT2']);
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
