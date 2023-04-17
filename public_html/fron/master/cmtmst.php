<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("検体コメントマスタ");
NsfrLogOut("検体コメントマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>検体コメントマスタ</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>コメントコード</th>
<th>コメント内容</th>
<th>コメント種類</th>
<th>コメント区分</th>
<th>認識システム保留フラグ</th>
<th>開始日</th>
<th>終了日</th>
<th>作成時刻</th>
<th>更新時刻</th>
<th>作業者ＩＤ</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfcmtmst where ukflg = '1' order by cmtcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['CMTCD']);
		printf("<td>%s</td>\n",$row['CMTNM']);
		printf("<td>%s</td>\n",$row['COMSYURU']);
		printf("<td>%s</td>\n",$row['COMKUBUN']);
		printf("<td>%s</td>\n",$row['NINSHOF']);
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
