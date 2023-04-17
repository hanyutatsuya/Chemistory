<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("未引き渡しトレーチェック");
NsfrLogOut("未引き渡しトレーチェック");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>未引き渡しトレーチェック</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select count(distinct kn.trayid) from nfktbl kn ";
	$sql = $sql . "where kn.sriymd = '$sdate' ";
	$sql = $sql . "and kn.sskbn = '01' ";
	$sql = $sql . "and char(trayid,1) < 'A' ";
	$sql = $sql . "and not exists ";
	$sql = $sql . "(select * from nknthktbl h where h.sriymd = kn.sriymd and h.trayid = kn.trayid) ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();
	}
else
	{
	printf("Connection failed");
	}
$conn = null;

if ($cnt_t == 0)
	{
	printf("<center>未引き渡しラックはありません</center>\n");
	}
else
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th></th>\n");
	printf("<th>件数</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hikitray.php?SDATE=%s>未引き渡しトレー</A></td>\n",$sdate);
	printf("<td align=right><A href=hikitray.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($cnt_t));
	printf("</tr>\n");

	printf("</table>\n");
	}

?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>検体認識システム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
