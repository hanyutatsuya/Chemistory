<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("移載未処理ラックチェック");
NsfrLogOut("移載未処理ラックチェック");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>移載未処理ラックチェック</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select count(distinct b.aslckid) ";
	$sql = $sql . "from fbncjtbl b,firkkmst i,nfsmpmst ws ";
	$sql = $sql . "where b.sriymd = '$sdate' ";
	$sql = $sql . "and b.smpcd = ws.smpcd ";
	$sql = $sql . "and ws.itmcd = i.itmcd ";
	$sql = $sql . "and b.bnckka in ('01','11') ";
	$sql = $sql . "and b.isiflg = '0' ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	if ($cnt_t == 0)
		{
		printf("<center>移載未処理ラックはありません</center>\n");
		}
	else
		{
		printf("<table align=center bgcolor=white border>\n");

		printf("<tr>\n");
		printf("<th></th>\n");
		printf("<th>件数</th>\n");
		printf("</tr>\n");

		printf("<tr>\n");
		printf("<td><A href=miisairack.php?SDATE=%s>移載未処理ラック</A></td>\n",$sdate);
		printf("<td><A href=miisairack.php?SDATE=%s>%5.5d</A></td>\n",$sdate,$cnt_t);
		printf("</tr>\n");

		printf("</table>\n");
		}
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
