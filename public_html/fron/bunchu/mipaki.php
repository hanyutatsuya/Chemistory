<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�p�L�p�L���x�����o�̓`�F�b�N");
NsfrLogOut("�p�L�p�L���x�����o�̓`�F�b�N");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�p�L�p�L���x�����o�̓`�F�b�N</h2></center>

<?php
$sdate = $_REQUEST[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select count(distinct b.aslckid) ";
	$sql = $sql . "from fpkptbl pk,fbncjtbl b ";
	$sql = $sql . "where pk.sriymd = '$sdate' ";
	$sql = $sql . "and pk.outflg = '0' ";
	$sql = $sql . "and b.sriymd = pk.sriymd ";
	$sql = $sql . "and b.barcd  = pk.barcd ";
	$sql = $sql . "and b.kntkbn = pk.kntkbn ";
	$sql = $sql . "and b.smpcd  = pk.smpcd ";
	$sql = $sql . "and b.bnckka in ('01','11') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	if ($cnt_t == 0)
		{
		printf("<center>�p�L�p�L���x�����o�͂͂���܂���</center>\n");
		}
	else
		{
		printf("<table align=center bgcolor=white border>\n");

		printf("<tr>\n");
		printf("<th></th>\n");
		printf("<th>����</th>\n");
		printf("</tr>\n");

		printf("<tr>\n");
		printf("<td><A href=mipakirack.php?SDATE=%s>�p�L�p�L���x�����o�̓��b�N</A></td>\n",$sdate);
		printf("<td align=right><A href=mipakirack.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($cnt_t));
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
