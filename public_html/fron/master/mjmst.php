<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("���W���[�����}�X�^");
NsfrLogOut("���W���[�����}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>���W���[�����}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>�Z��No.</th>
<th>���W���[��No.</th>
<th>���W���[�����</th>
<th>ITEM�R�[�h�QNo.</th>
<th>�v���g�R��No.</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from fmjmst where ukflg = '1' order by bccelno,bcmodno for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['BCCELNO']);
		printf("<td>%s</td>\n",$row['BCMODNO']);
		printf("<td>%s</td>\n",$row['BCMODSH']);
		printf("<td>%s</td>\n",$row['ITMCDGNO']);
		printf("<td>%s</td>\n",$row['PROTOCOL']);
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
