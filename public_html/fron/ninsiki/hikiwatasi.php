<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�������n���g���[�`�F�b�N");
NsfrLogOut("�������n���g���[�`�F�b�N");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�������n���g���[�`�F�b�N</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

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
	printf("<center>�������n�����b�N�͂���܂���</center>\n");
	}
else
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th></th>\n");
	printf("<th>����</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hikitray.php?SDATE=%s>�������n���g���[</A></td>\n",$sdate);
	printf("<td align=right><A href=hikitray.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($cnt_t));
	printf("</tr>\n");

	printf("</table>\n");
	}

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
