<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("�𓀃��b�N���̈ꗗ");
NsfrLogOut("�𓀃��b�N���̈ꗗ");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�𓀃��b�N���̈ꗗ</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>���b�N�h�c</th>\n");
	printf("<th>POS</th>\n");
	printf("<th>����No.</th>\n");
	printf("<th>CH</th>\n");
	printf("<th>���uNo.</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select kn.lckid,kn.lckpos,kn.barcd,kn.ktichkmj,kn.devno from nfktbl kn ";
	$sql = $sql . "where kn.sriymd = '$sdate' ";
	$sql = $sql . "and substr(kn.lckid,1,4) in ('EEEE','MMBB','CCBB') ";
	$sql = $sql . "order by kn.lckid,kn.lckpos for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row[0]);
		printf("<td align=right>%d</td>\n",$row[1]);
		printf("<td><A href=../comm/nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$sdate,substr($row[2],2,9),barcode_edit(trim($row[2])));
		printf("<td>%s</td>\n",$row[3]);
		printf("<td>%s</td>\n",$row[4]);
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
