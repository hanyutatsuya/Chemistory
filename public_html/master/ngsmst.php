<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�����m�f�����}�X�^");
NsfrLogOut("�����m�f�����}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�����m�f�����}�X�^</h2></center>
<table align="center" bgcolor = "white" border>

<tr>
<th>NG�����R�[�h</th>
<th>�ڍ׃R�[�h</th>
<th>����NG������</th>
<th>����NG�ڍ׏�����</th>
<th>�����������MFLG</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from fngsmst where bcngsscd != '00' and ukflg = '1' order by bcngscd,bcngsscd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['BCNGSCD']);
		printf("<td>%s</td>\n",$row['BCNGSSCD']);
		printf("<td>%s</td>\n",$row['BCNGSNM']);
		printf("<td>%s</td>\n",$row['BCNGSSNM']);
		printf("<td>%s</td>\n",$row['FKSSFLG']);
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
