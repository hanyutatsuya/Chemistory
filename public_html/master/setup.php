<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("システム設定情報");
NsfrLogOut("システム設定情報");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>システム設定情報</h2></center>

<table align="center" bgcolor = "white" border=2>
<tr>
<th>設定区分</th>
<th>項目区分</th>
<th>設定内容</th>
<th>更新時刻</th>
<th>作業者ID</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nsetuptbl order by setkbn,kmkkbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['SETKBN']);
		printf("<td>%s</td>\n",$row['KMKKBN']);
		printf("<td>%s</td>\n",$row['SETKBNNM']);
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
