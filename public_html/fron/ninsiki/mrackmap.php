<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("���������b�N�ꗗ");
NsfrLogOut("���������b�N�ꗗ");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>���������b�N�ꗗ</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>�g���[�h�c</th>\n");
	printf("<th>POS</th>\n");
	printf("<th>���b�N�h�c</th>\n");
	printf("<th>���uNo.</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct kn.trayid,kn.traypos,kn.lckid,kn.devno from nfktbl kn ";
	$sql = $sql . "where kn.sriymd = '$sdate' ";
	$sql = $sql . "and kn.sskflg != '1' ";
	$sql = $sql . "order by kn.trayid,kn.traypos,kn.lckid for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("<td>%d</td>\n",trim($row[1]));
		printf("<td>%s</td>\n",trim($row[2]));
		printf("<td>%s</td>\n",trim($row[3]));
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
