<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�������n�����b�N�ꗗ");
NsfrLogOut("�������n�����b�N�ꗗ");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�������n�����b�N�ꗗ</h2></center>

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
	printf("<th>���W���[��</th>\n");
	printf("<th>���b�N���</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct b.astrayid,b.astraypos,b.aslckid,";
	$sql = $sql . "b.devno,b.bcmodno,ws.swklckid,ws.itmcd ";
	$sql = $sql . "from fbncjtbl b,nfsmpmst ws ";
	$sql = $sql . "where b.sriymd = '$sdate' ";
	$sql = $sql . "and b.aslckid != ' ' ";
	$sql = $sql . "and b.bnckka in ('01','11') ";
	$sql = $sql . "and b.hkwzflg = '0' ";
	$sql = $sql . "and ws.smpcd = b.smpcd ";
	$sql = $sql . "and char(ws.itmcd,1) not in ('6','7') ";
	$sql = $sql . "order by ws.itmcd,b.astrayid,b.astraypos,b.aslckid for read only;";

	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("<td align=right>%d</td>\n",trim($row[1]));
		printf("<td>%s</td>\n",trim($row[2]));
		printf("<td>%s</td>\n",trim($row[3]));
		printf("<td>%s</td>\n",trim($row[4]));
		printf("<td>%s</td>\n",trim($row[5]));
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
