<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("���������b�N�`�F�b�N");
NsfrLogOut("���������b�N�`�F�b�N");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>���������b�N�`�F�b�N</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select count(distinct lckid) from nfktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and sskflg != '1' ";
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
	printf("<center>���������b�N�͂���܂���</center>\n");
	}
else
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th></th>\n");
	printf("<th>����</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mrackmap.php?SDATE=%s>���������b�N</A></td>\n",$sdate);
	printf("<td align=right><A href=mrackmap.php?SDATE=%s>%s</A></td>\n",$sdate,number_format($cnt_t));
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
