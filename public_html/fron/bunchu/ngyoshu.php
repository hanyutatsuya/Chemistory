<?php
//	�p�蕜�������q���̐��ꗗ
//	$Author: Hanyu $
//	$Date: 09/04/14 9:25 $
//	$Revision: 4 $
//	$Workfile: ngyoshu.php $
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
?>

<?php
$sdate = $_GET['SDATE'];
$ngcd  = "03";

$title = "�p�蕜�������q���̐��ꗗ";

NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<center><h2>�������F%s</h2></center>\n",$sdate);

	printf("<table align=center  border=0>\n");
	printf("<tr valign=top>\n");

	printf("<td>\n");
	printf("<table bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>ITEMCD</th>\n");
	printf("<th nowrap>�d��</th>\n");
	printf("<th nowrap>SMPCD</th>\n");
	printf("<th nowrap>SMP����</th>\n");
	printf("<th nowrap>�{��</th>\n");
	printf("</tr>\n");

	$total = 0;
	$sql = "";
	$sql = $sql . "select ws.itmcdgno,ws.itmcd,ws.swklckid,b.smpcd,ws.swkskid,ws.smpcdnm,count(*) ";
	$sql = $sql . "from fbncjtbl b,nfsmpmst ws ";
	$sql = $sql . "where b.sriymd = '$sdate' ";
	$sql = $sql . "and b.devno like '9%' and b.bnckka in ('01','11') ";
	$sql = $sql . "and ws.smpcd  = b.smpcd and ws.ukflg = '1' ";
	$sql = $sql . "and exists (select * from fbncjtbl b2 where b2.sriymd = '$sdate' ";
	$sql = $sql . "and b2.barcd = b.barcd and b2.bcngscd = '03') ";
	$sql = $sql . "group by ws.itmcdgno,ws.itmcd,ws.swklckid,b.smpcd,ws.swkskid,ws.smpcdnm ";
	$sql = $sql . "order by ws.itmcdgno,ws.itmcd,ws.swkskid,b.smpcd ";
	$sql = $sql . "for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row[2]);
		printf("<td nowrap>%s</td>\n",$row[4]);
		printf("<td nowrap>%s</td>\n",$row[3]);
		printf("<td nowrap>%s</td>\n",$row[5]);
		printf("<td nowrap align=right>%s</td>\n",number_format($row[6]));
		$total+=$row[6];
		printf("</tr>\n");
		}

	printf("<tr>\n");
	printf("<td nowrap colspan=4>���v</td>\n");
	printf("<td nowrap align=right>%s</td>\n",number_format($total));
	printf("</tr>\n");
	printf("</table>\n");
	printf("</td>\n");

	printf("<td>\n");
	printf("<table bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>ITEMCD</th>\n");
	printf("<th nowrap>�{��</th>\n");
	printf("</tr>\n");

	$total = 0;
	$sql = "";
	$sql = $sql . "select ws.itmcdgno,ws.itmcd,ws.swklckid,count(*) ";
	$sql = $sql . "from fbncjtbl b,nfsmpmst ws ";
	$sql = $sql . "where b.sriymd = '$sdate' ";
	$sql = $sql . "and b.devno like '9%' and b.bnckka in ('01','11') ";
	$sql = $sql . "and ws.smpcd  = b.smpcd and ws.ukflg = '1' ";
	$sql = $sql . "and exists (select * from fbncjtbl b2 where b2.sriymd = '$sdate' ";
	$sql = $sql . "and b2.barcd = b.barcd and b2.bcngscd = '03') ";
	$sql = $sql . "group by ws.itmcdgno,ws.itmcd,ws.swklckid ";
	$sql = $sql . "order by ws.itmcdgno,ws.itmcd ";
	$sql = $sql . "for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row[2]);
		printf("<td nowrap align=right>%s</td>\n",number_format($row[3]));
		$total+=$row[3];
		printf("</tr>\n");
		}
	printf("<td nowrap>���v</td>\n");
	printf("<td nowrap align=right>%s</td>\n",number_format($total));
	printf("</table>\n");
	printf("</td>\n");

	printf("</table>\n");
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<BR all>\n");
printf("<HR>\n");

printf("<P>\n");
printf("<center><A href=ngshori.php?SDATE=%s>�m�f�����������̏Ɖ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
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
