<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�����ۊǋ敪�}�X�^");
NsfrLogOut("�����ۊǋ敪�}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�����ۊǋ敪�}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>�{�݃R�[�h</th>
<th>�ۑ��ޗ��R�[�h</th>
<th>�ۊǓ���</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfchkmst order by sstcd,hznzrcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['SSTCD']);
		if  (trim($row['HZNZRCD']) == "")
			{
			printf("<td>�S��</td>\n");
			}
		else
			{
			printf("<td>%s</td>\n",$row['HZNZRCD']);
			}
		printf("<td>%s</td>\n",$row['HKNDAY']);
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
