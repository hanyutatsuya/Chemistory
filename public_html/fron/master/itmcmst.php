<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�h�s�d�l�R�[�h�}�X�^");
NsfrLogOut("�h�s�d�l�R�[�h�}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�h�s�d�l�R�[�h�}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th nowrap>ITEM�R�[�h</th>
<th nowrap>ARACK���</th>
<th nowrap>�d�����h�c</th>
<th nowrap>�d��������</th>
<th nowrap>ITEM�R�[�h��</th>
<th nowrap>ITEM�R�[�h����</th>
<th nowrap>���b�N�{��</th>
<th nowrap>�J�n��</th>
<th nowrap>�I����</th>
<th nowrap>�쐬����</th>
<th nowrap>�X�V����</th>
<th nowrap>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from fitmcmst where ukflg = '1' order by itmcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row['ITMCD']);
		printf("<td nowrap>%s</td>\n",$row['ARKSH']);
		printf("<td nowrap>%s</td>\n",$row['SWKLCKID']);
		printf("<td nowrap>%s</td>\n",$row['ZRLCKNM']);
		printf("<td nowrap>%s</td>\n",$row['ITMNM']);
		printf("<td nowrap>%s</td>\n",$row['ITMNMR']);
		printf("<td nowrap>%s</td>\n",$row['LCKPCNT']);
		printf("<td nowrap>%s</td>\n",$row['STYMD']);
		printf("<td nowrap>%s</td>\n",$row['EDYMD']);
		printf("<td nowrap>%10.10s</td>\n",$row['SAKHM']);
		printf("<td nowrap>%10.10s</td>\n",$row['KOUHM']);
		printf("<td nowrap>%s</td>\n",$row['SAGYOID']);
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
