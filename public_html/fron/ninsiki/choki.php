<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�������̖{���Ɖ�");
NsfrLogOut("�������̖{���Ɖ�");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�������̖{���Ɖ�</h2></center>


<A href=/~nsfr/csv/aaa.csv>�b�r�u�t�@�C��</A>


<?php
$sdate = $_GET[SDATE];
$conn = Get_DBConn();

if  ($conn){
	printf("<center><h2>�������F%s</h2></center>\n",$sdate);

//	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,4) = 'EEEE' for read only";
//	$pdst = $conn->prepare($sql);
//	$pdst->execute();
//	$row = $pdst->fetch();
//	$cnt_e = $row[1];
//	$pdst->closeCursor();

//	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,4) = 'KKKK' for read only";
//	$pdst = $conn->prepare($sql);
//	$pdst->execute();
//	$row = $pdst->fetch();
//	$cnt_k = $row[1];
//	$pdst->closeCursor();

//	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and lckid between 'TTTT0001' and 'TTTT7999' for read only";
//	$pdst = $conn->prepare($sql);
//	$pdst->execute();
//	$row = $pdst->fetch();
//	$cnt_t = $row[1];
//	$pdst->closeCursor();

//	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,5) = 'TTTT8' for read only";
//	$pdst = $conn->prepare($sql);
//	$pdst->execute();
//	$row = $pdst->fetch();
//	$cnt_b = $row[1];
//	$pdst->closeCursor();

//	$sql = "select count(*) from nfktbl where sriymd = '$sdate' and char(lckid,5) = 'TTTT9' for read only";
//	$pdst = $conn->prepare($sql);
//	$pdst->execute();
//	$row = $pdst->fetch();
//	$cnt_h = $row[1];
//	$pdst->closeCursor();

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
printf("<th>���b�N���</th>\n");
printf("<th>�{��</th>\n");
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=2>�s�s�s�s</A></td>\n",$sdate);
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=2>%5.5d</A></td>\n",$sdate,$cnt_t);
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=4>�a�m�o�@</A></td>\n",$sdate);
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=4>%5.5d</A></td>\n",$sdate,$cnt_b);
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=3>�g�b�u�@</A></td>\n",$sdate);
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=3>%5.5d</A></td>\n",$sdate,$cnt_h);
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=1>�j�j�j�j</A></td>\n",$sdate);
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=1>%5.5d</A></td>\n",$sdate,$cnt_k);
printf("</tr>\n");

printf("<tr>\n");
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=0>�d�d�d�d</A></td>\n",$sdate);
printf("<td><A href=tk1ran.php?SDATE=%s&TYPE=0>%5.5d</A></td>\n",$sdate,$cnt_e);
printf("</tr>\n");

printf("</table>\n");

?>

<HR>

<?php
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>���̔F���V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
