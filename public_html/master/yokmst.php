<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�e��}�X�^");
NsfrLogOut("�e��}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�e��}�X�^</h2></center>
<table align="center" bgcolor = "white" border>

<tr>
<th>�e��敪</th>
<th>�e�햼</th>
<th>����</th>
<th>�`���[�u�`����No.</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfyokmst where ukflg = '1' order by ykkbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['YKKBN']);
		printf("<td>%s</td>\n",$row['YKNM']);
		printf("<td>%s</td>\n",$row['YKNMR']);
		printf("<td>%s</td>\n",$row['TBKJNO']);
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
