<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�˗������Ɖ�",1800);
NsfrLogOut("�˗������Ɖ�");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�˗������Ɖ�</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>�������F%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{

	$sql = "select count(*) from nfztbl where utkymd = '$sdate' for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_z = $row[0];
		break;
		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_k = $row[0];
		break;
		}
	$sql = "select count(*) from nfitbl where sriymd = '$sdate' for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_i = $row[0];
		break;
		}
//	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and swkkbn in (' ','01') for read only";
//	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
//		{
//		$cnt_s = $row[0];
//		break;
//		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and brkbn = '06' and swkkbn in (' ','01') for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_s1 = $row[0];
		break;
		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and brkbn = '09' and swkkbn in (' ','01') for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_s2 = $row[0];
		break;
		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and brkbn != '06' and brkbn != '09' and swkkbn in (' ','01') for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_s3 = $row[0];
		break;
		}
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
printf("<td>���ҏ��</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_z));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>������</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_k));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>�˗�����</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_i));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>�①��������</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s1+$cnt_s2+$cnt_s3));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>�①��������(�����P���)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s1));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>�①��������(�����Q���)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s2));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>�①��������(�ʏ핪)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s3));
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
