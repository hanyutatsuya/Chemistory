<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�s�K���o�^���ꌟ�̃`�F�b�N");
NsfrLogOut("�s�K���o�^���ꌟ�̃`�F�b�N");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�s�K���o�^���ꌟ�̃`�F�b�N</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select count(distinct m.barcd) from fbncmktbl m ";
	$sql = $sql . "where m.sriymd = '$sdate' ";
	$sql = $sql . "and char(m.knbnid,1) not in ('V','S') ";
	$sql = $sql . "and exists ( select * from fbncmktbl f ";
	$sql = $sql . "where f.sriymd = m.sriymd ";
	$sql = $sql . "and char(f.barcd,9) = char(m.barcd,9) ";
	$sql = $sql . "and f.bcngcd = '6') ";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt_t = $row[0];
	$pdst->closeCursor();

	if ($cnt_t == 0)
		{
		printf("<center>�s�K���o�^���ꌟ�̂͂���܂���</center>\n");
		}
	else
		{
		printf("<table align=center bgcolor=white border>\n");

		printf("<tr>\n");
		printf("<th></th>\n");
		printf("<th>����</th>\n");
		printf("</tr>\n");

		printf("<tr>\n");
		printf("<td><A href=futekiken.php?SDATE=%s>�s�K���o�^���ꌟ��</A></td>\n",$sdate);
		printf("<td align=right><A href=futekiken.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($cnt_t));
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
