<?php
//	�m�f�����������̏Ɖ�
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
?>

<?php
$sdate = $_GET['SDATE'];
$ngcd  = $_GET['NGCD'];

$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "select bcngsnm from fngsmst where bcngscd = '$ngcd' and bcngsscd = '00' and ukflg = '1' for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch();
	$title = "�m�f�����������̏Ɖ�(" . $row[0] . ")";
	$pdst->closeCursor();
	}

NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

if  ($conn)
	{
	printf("<center><h2>�������F%s</h2></center>\n",$sdate);

	$sql = "select bcngsscd,bcngssnm from fngsmst where bcngscd = '$ngcd' and bcngsscd != '00' and ukflg = '1' order by bcngscd for read only";
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
		$ngscd = $ngs[0][$i];
		$sql = "select count(distinct barcd) from fbncjtbl where sriymd = '$sdate' and bcngscd = '$ngcd' and bcngsscd = '$ngscd' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[$i] = $row[0];
		$total += $row[0];
		$pdst->closeCursor();
		}

	for ($i=0;$i<$mst_cnt;$i++)
		{
		$ngscd = $ngs[0][$i];
		$sql = "select count(*) from fbncjtbl where sriymd = '$sdate' and bcngscd = '$ngcd' and bcngsscd = '$ngscd' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt2[$i] = $row[0];
		$total2 += $row[0];
		$pdst->closeCursor();
		}

	if ($ngcd == '03')
		{
		for ($i=0;$i<$mst_cnt;$i++)
			{
			$ngscd = $ngs[0][$i];
			$sql = "";
			$sql = $sql . "select count(*) from fbncjtbl b1 where b1.sriymd = '$sdate' ";
			$sql = $sql . "and b1.devno like '9%' and b1.bnckka in ('01','11') ";
			$sql = $sql . "and exists (select * from fbncjtbl b2 where b2.sriymd = '$sdate' ";
			$sql = $sql . "and b2.barcd = b1.barcd and b2.bcngscd = '$ngcd' and b2.bcngsscd = '$ngscd')";
			$sql = $sql . "for read only";
			$pdst = $conn->prepare($sql);
			$pdst->execute();
			$row = $pdst->fetch(PDO::FETCH_NUM);
			$cnt3[$i] = $row[0];
			$total3 += $row[0];
			$pdst->closeCursor();
			}
		}
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<table align=\"center\" border>\n");

printf("<tr>\n");
printf("<th>NG�ڍ�CD</th>\n");
printf("<th>NG�ڍ׏�����</th>\n");
printf("<th>�{��</th>\n");
printf("<th>SMPCD��</th>\n");
if ($ngcd == '03')
	printf("<th>����SMP��</th>\n");
printf("</tr>\n");

for ($i=0;$i<$mst_cnt;$i++)
	{
	printf("<tr>\n");
	printf("<td>%s</td>\n",$ngs[0][$i]);
	printf("<td><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=%s>%s</A></td>\n",$sdate,$ngcd,$ngs[0][$i],$ngs[1][$i]);
	printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=%s>%d</A></td>\n",$sdate,$ngcd,$ngs[0][$i],number_format($cnt[$i]));
	printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=%s>%d</A></td>\n",$sdate,$ngcd,$ngs[0][$i],number_format($cnt2[$i]));
	if ($ngcd == '03')
		printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=%s>%d</A></td>\n",$sdate,$ngcd,$ngs[0][$i],number_format($cnt3[$i]));
	printf("</tr>\n");
	}

printf("<tr>\n");
printf("<td>00</td>\n");
printf("<td><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=00>���v</A></td>\n",$sdate,$ngcd);
printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=00>%s</A></td>\n",$sdate,$ngcd,number_format($total));
printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=00>%s</A></td>\n",$sdate,$ngcd,number_format($total2));
if ($ngcd == '03')
	printf("<td align=right><A href=ng1ran.php?SDATE=%s&NGCD=%s&NGSCD=00>%s</A></td>\n",$sdate,$ngcd,number_format($total3));
printf("</tr>\n");

printf("</table>\n");
printf("<HR>\n");

if ($ngcd == '03')
	{
	printf("<P>\n");
	printf("<center><A href=ngyoshu.php?SDATE=%s>�p�蕜�������q���̐��ꗗ</A></center>\n",$sdate);
	printf("</P>\n");
	printf("<HR>\n");
	}

printf("<P>\n");
printf("<center><A href=ngshori.php?SDATE=%s>�m�f�����������̏Ɖ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>�t�����e�B�A�V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
