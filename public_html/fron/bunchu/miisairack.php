<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("移載未処理ラック一覧");
NsfrLogOut("移載未処理ラック一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>移載未処理ラック一覧</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>ラックＩＤ</th>\n");
	printf("<th>装置No.</th>\n");
	printf("<th>モジュール</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct b.aslckid,b.devno,b.bcmodno ";
	$sql = $sql . "from fbncjtbl b,firkkmst i,nfsmpmst ws ";
	$sql = $sql . "where b.sriymd = '$sdate' ";
	$sql = $sql . "and b.smpcd = ws.smpcd ";
	$sql = $sql . "and ws.itmcd = i.itmcd ";
	$sql = $sql . "and b.bnckka in ('01','11') ";
	$sql = $sql . "and b.isiflg = '0' ";
	$sql = $sql . "for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("<td>%s</td>\n",trim($row[1]));
		printf("<td>%s</td>\n",trim($row[2]));
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
