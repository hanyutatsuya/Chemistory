<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�p�L�p�L�������ꗗ");
NsfrLogOut("�p�L�p�L�������ꗗ");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�p�L�p�L�������ꗗ</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>���b�N�h�c</th>\n");
	printf("<th>���uNo.</th>\n");
	printf("<th>���W���[��</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct aslckid,devno,bcmodno from fbncjtbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and char(aslckid,1) in ('A','B') ";
	$sql = $sql . "order by aslckid for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("<td>%s</td>\n",trim($row[1]));
		printf("<td>%s</td>\n",trim($row[2]));
		printf("</tr>\n");
		}
	printf("</table>\n");
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
