<?php
//	ＮＧ復旧処理検体照会処理
//	$Author: $
//	$Date:  $
//	$Revision:  $
//	$Workfile:  $
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("ＮＧ復旧処理検体照会");
NsfrLogOut("ＮＧ復旧処理検体照会");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>ＮＧ復旧処理検体照会</h2></center>

<?php
$sdate = $_GET['SDATE'];

$conn = Get_DBConn();

if  ($conn)
	{
	printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

	$sql = "select bcngscd,bcngsnm from fngsmst where bcngsscd = '00' and ukflg = '1' order by bcngscd for read only";
	$i = 0;
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$ngs[0][$i] = $row[0];
		$ngs[1][$i] = $row[1];
		$i++;
		}

	$mst_cnt = $i;
	$total = 0;
	$total2 = 0;
	$total3 = 0;

	for ($i=0;$i<$mst_cnt;$i++)
		{
		$ngcd = $ngs[0][$i];
		$sql = "select count(distinct barcd) from fbncjtbl where sriymd = '$sdate' and bcngscd = '$ngcd' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[$i] = $row[0];
		$total += $row[0];
		$pdst->closeCursor();
		}

	for ($i=0;$i<$mst_cnt;$i++)
		{
		$ngcd = $ngs[0][$i];
		$sql = "select count(*) from fbncjtbl where sriymd = '$sdate' and bcngscd = '$ngcd' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt2[$i] = $row[0];
		$total2 += $row[0];
		$pdst->closeCursor();
		}

//	$ngcd = $ngs[0][0];
//	$sql = "";
//	$sql = $sql . "select count(*) from fbncjtbl b1 where b1.sriymd = '$sdate' and b1.seq != 1 ";
//	$sql = $sql . "and b1.devno not like '9%' and b1.bnckka in ('01','11') ";
////	$sql = $sql . "and exists (select * from fbncjtbl b2 where b2.sriymd = b1.sriymd and b2.barcd = b1.barcd ";
////	$sql = $sql . "and b2.bcngscd = '$ngcd' ) ";
//	$sql = $sql . "for read only";
//	$pdst = $conn->prepare($sql);
//	$pdst->execute();
//	$row = $pdst->fetch(PDO::FETCH_NUM);
//	$cnt3[0] = $row[0];
//	$total3 += $row[0];
//	$pdst->closeCursor();

	$ngcd = $ngs[0][2];
	$sql = "";
	$sql = $sql . "select count(*) from fbncjtbl b1 where b1.sriymd = '$sdate' ";
	$sql = $sql . "and b1.devno like '9%' and b1.bnckka in ('01','11') ";
	$sql = $sql . "and exists (select * from fbncjtbl b2 where b2.sriymd = '$sdate' ";
	$sql = $sql . "and b2.barcd = b1.barcd and b2.bcngscd = '03') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt3[2] = $row[0];
	$total3 += $row[0];
	$pdst->closeCursor();


	$cnt3[0] = 0;
	$cnt3[1] = 0;
	$cnt3[3] = 0;
	$cnt3[4] = 0;

	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<table align=\"center\" border>\n");

printf("<tr>\n");
printf("<th>NG処理CD</th>\n");
printf("<th>NG処理名</th>\n");
printf("<th>本数</th>\n");
printf("<th>SMPCD数</th>\n");
printf("<th>復旧SMP数</th>\n");
printf("</tr>\n");

for ($i=0;$i<$mst_cnt;$i++)
	{
	printf("<tr>\n");
	printf("<td>%s</td>\n",$ngs[0][$i]);
	printf("<td><A href=ngkobetu.php?SDATE=%s&NGCD=%s>%s</A></td>\n",$sdate,$ngs[0][$i],$ngs[1][$i]);
	printf("<td align=right><A href=ngkobetu.php?SDATE=%s&NGCD=%s>%s</A></td>\n",$sdate,$ngs[0][$i],number_format($cnt[$i]));
	printf("<td align=right><A href=ngkobetu.php?SDATE=%s&NGCD=%s>%s</A></td>\n",$sdate,$ngs[0][$i],number_format($cnt2[$i]));
	printf("<td align=right><A href=ngkobetu.php?SDATE=%s&NGCD=%s>%s</A></td>\n",$sdate,$ngs[0][$i],number_format($cnt3[$i]));
	printf("</tr>\n");
	}

printf("<tr>\n");
printf("<td>00</td>\n");
printf("<td><A href=ng1ran.php?SDATE=%s&NGCD=00&NGSCD=00>合計</A></td>\n",$sdate);
printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=00&NGSCD=00>%s</A></td>\n",$sdate,number_format($total));
printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=00&NGSCD=00>%s</A></td>\n",$sdate,number_format($total2));
printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=00&NGSCD=00>%s</A></td>\n",$sdate,number_format($total3));
printf("</tr>\n");

printf("</table>\n");

printf("<HR>\n");
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
