<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�c�Ə��}�X�^");
NsfrLogOut("�c�Ə��}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�c�Ə��}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>�c�Ə��R�[�h</th>
<th>�W�z�R�[�h(FROM)</th>
<th>�W�z�R�[�h(TO)</th>
<th>�V�c�Ə��R�[�h</th>
<th>�c�Ə���</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfegsmst where ukflg = '1' order by ecd,shcdfr,shcdto for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['ECD']);
		printf("<td>%s</td>\n",$row['SHCDFR']);
		printf("<td>%s</td>\n",$row['SHCDTO']);
		printf("<td>%s</td>\n",$row['ECD2']);
		printf("<td>%s</td>\n",$row['EGSNM']);
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
