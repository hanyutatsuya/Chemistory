<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�d������ރ}�X�^");
NsfrLogOut("�d������ރ}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�d������ރ}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>�d������ދ敪</th>
<th>�d������ޖ�</th>
<th>����</th>
<th>����ޗ�CD</th>
<th>���b�N�{��</th>
<th>����F</th>
<th>�s���˗��Ώ�F</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ�ID</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfssmst where ukflg = '1' order by sskbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['SSKBN']);
		printf("<td>%s</td>\n",$row['ZRNM']);
		printf("<td>%s</td>\n",$row['ZRNMR']);
		printf("<td>%s</td>\n",$row['STZRCD']);
		printf("<td>%s</td>\n",$row['LCKPCNT']);
		printf("<td>%s</td>\n",$row['TKFLG']);
		printf("<td>%s</td>\n",$row['FITFLG']);
		printf("<td>%s</td>\n",$row['STYMD']);
		printf("<td>%s</td>\n",$row['EDYMD']);
		printf("<td>%10.10s</td>\n",$row['SAKHM']);
		printf("<td>%10.10s</td>\n",$row['KOUHM']);
		printf("<td>%s</td>\n",$row['SAGYOID']);
		printf("</tr>\n");
		}
	}
	else
	{
	echo "Connection failed";
	}
$conn = null;

?>

</table>

<?php
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
