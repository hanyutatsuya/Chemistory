<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("看板ID未設定ラック一覧");
NsfrLogOut("看板ID未設定ラック一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>看板ID未設定ラック一覧</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>トレーＩＤ</th>\n");
	printf("<th>POS</th>\n");
	printf("<th>ラックＩＤ</th>\n");
	printf("<th>セルNo.</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct trayid,traypos,lckid,tncelno from fbncmktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and knbnid = ' ' ";
	$sql = $sql . "and bcngcd != '6' ";
	$sql = $sql . "order by trayid,traypos,lckid for read only";

	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("<td align=right>%d</td>\n",trim($row[1]));
		printf("<td>%s</td>\n",trim($row[2]));
		printf("<td>%s</td>\n",trim($row[3]));
		printf("</tr>\n");
		}
	printf("</table>\n");
	}
else
	{
	printf("Connection failed");
	}
$conn = null;
?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>フロンティアシステム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
