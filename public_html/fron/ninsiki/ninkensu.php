<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("認識済件数照会",1800);
NsfrLogOut("認識済件数照会");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>認識済件数照会</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$sql = "select count(*) from nfktbl where sriymd = '$sdate' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,1) in ('T','K','P','Q','W') for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_k = $row[0];
	$pdst->closeCursor();

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and lckid like 'V%' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_v = $row[0];
	$pdst->closeCursor();

	}
else
	{
	echo "Connection failed";
	}
$conn = null;
?>

<?php
printf("<table align=center bgcolor=white border>\n");

printf("<tr>\n");
printf("<th></th>\n");
printf("<th>件数</th>\n");
printf("</tr>\n");

printf("<tr>\n");
printf("<td>認識済検体(血清)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_t-$cnt_k-$cnt_v));
printf("</tr>\n");
printf("<tr>\n");
printf("<td>認識済検体(凍結)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_k));
printf("</tr>\n");
printf("<tr>\n");
printf("<td>認識済検体(扱い)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_v));
printf("</tr>\n");

printf("</table>\n");
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
<DIV align=right>
この画面は３０分ごとに自動更新されます
</DIV>
</BODY>
</HTML>
