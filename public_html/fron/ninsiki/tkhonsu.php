<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("“€Œ‹ŒŸ‘Ì–{”Æ‰ï");
NsfrLogOut("“€Œ‹ŒŸ‘Ì–{”Æ‰ï");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>“€Œ‹ŒŸ‘Ì–{”Æ‰ï</h2></center>

<?php
$sdate = $_GET[SDATE];
$conn = Get_DBConn();

if  ($conn){
	printf("<center><h2>ˆ—“úF%s</h2></center>\n",$sdate);

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,4) = 'EEEE' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_e = $row[0];
	$pdst->closeCursor();

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,4) = 'KKKK' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_k = $row[0];
	$pdst->closeCursor();

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and lckid between 'TTTT0001' and 'TTTT7999' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,5) = 'TTTT8' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_b = $row[0];
	$pdst->closeCursor();

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,5) = 'TTTT9' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_h = $row[0];
	$pdst->closeCursor();

	$sql = "select count(*) from nfktbl where sriymd = '$sdate' ";
	$sql = $sql . " and  (lckid between 'VVVV5001' and 'VVVV8999' or ";
	$sql = $sql .  "     lckid between 'VVVV9501' and 'VVVV9999' or ";
	$sql = $sql . "      char(lckid,4) in ('PPPP','QQQQ','WWWW') ) for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_s = $row[0];
	$pdst->closeCursor();

	}
	else
	{
	echo "Connection failed";
	}
$conn = null;
?>

<?php

printf("<table align=\"center\" border>\n");

printf("<tr>\n");
printf("<th>ƒ‰ƒbƒNí—Ş</th>\n");
printf("<th>–{”</th>\n");
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=2>‚s‚s‚s‚s</A></td>\n",$sdate);
printf("<td align=right><A href=tk1ran.php?SDATE=%s&TYPE=2>%s</A></td>\n",$sdate,number_format($cnt_t));
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=4>‚a‚m‚o@</A></td>\n",$sdate);
printf("<td align=right><A href=tk1ran.php?SDATE=%s&TYPE=4>%s</A></td>\n",$sdate,number_format($cnt_b));
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=3>‚g‚b‚u@</A></td>\n",$sdate);
printf("<td align=right><A href=tk1ran.php?SDATE=%s&TYPE=3>%s</A></td>\n",$sdate,number_format($cnt_h));
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=1>‚j‚j‚j‚j</A></td>\n",$sdate);
printf("<td align=right><A href=tk1ran.php?SDATE=%s&TYPE=1>%s</A></td>\n",$sdate,number_format($cnt_k));
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=0>‚d‚d‚d‚d</A></td>\n",$sdate);
printf("<td align=right><A href=tk1ran.php?SDATE=%s&TYPE=0>%s</A></td>\n",$sdate,number_format($cnt_e));
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=5>‚»‚Ì‘¼@</A></td>\n",$sdate);
printf("<td align=right><A href=tk1ran.php?SDATE=%s&TYPE=5>%s</A></td>\n",$sdate,number_format($cnt_s));
printf("</tr>\n");

printf("</table>\n");

?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>ŒŸ‘Ì”F¯ƒVƒXƒeƒ€Æ‰ïˆ—ˆê——‚É–ß‚é</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>ƒgƒbƒv‚É–ß‚é</A></center>
</P>
<HR>
</BODY>
</HTML>
