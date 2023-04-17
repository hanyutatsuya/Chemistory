<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("未受け取りトレー一覧");
NsfrLogOut("未受け取りトレー一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>未受け取りトレー一覧</h2></center>

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
	printf("<th>装置No.</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct kn.trayid,kn.traypos,kn.lckid,kn.devno ";
	$sql = $sql . "from nfktbl kn, nknthktbl h ";
	$sql = $sql . "where h.sriymd = '$sdate' ";
	$sql = $sql . "and char(h.trayid,4) != 'VVVV' ";
	$sql = $sql . "and not exists ";
	$sql = $sql . "(select * from fkntuktbl b where b.sriymd = h.sriymd and b.trayid = h.trayid) ";
	$sql = $sql . "and kn.sriymd = h.sriymd ";
	$sql = $sql . "and kn.trayid = h.trayid ";
	$sql = $sql . "order by kn.trayid,kn.traypos,kn.lckid for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("<td>%d</td>\n",trim($row[1]));
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
