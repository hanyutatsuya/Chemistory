<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�{�݃}�X�^");
NsfrLogOut("�{�݃}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�{�݃}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>�{�݃R�[�h</th>
<th>���Җ��h�c�t���O</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfsismst where ukflg = '1' order by sstcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['SSTCD']);
		printf("<td>%s</td>\n",$row['KNJNMIDF']);
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
