<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�F���ό����Ɖ�",1800);
NsfrLogOut("�F���ό����Ɖ�");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�F���ό����Ɖ�</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

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
printf("<th>����</th>\n");
printf("</tr>\n");

printf("<tr>\n");
printf("<td>�F���ό���(����)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_t-$cnt_k-$cnt_v));
printf("</tr>\n");
printf("<tr>\n");
printf("<td>�F���ό���(����)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_k));
printf("</tr>\n");
printf("<tr>\n");
printf("<td>�F���ό���(����)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_v));
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
<DIV align=right>
���̉�ʂ͂R�O�����ƂɎ����X�V����܂�
</DIV>
</BODY>
</HTML>
