<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�V�X�e���ݒ���");
NsfrLogOut("�V�X�e���ݒ���");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�V�X�e���ݒ���</h2></center>

<table align="center" bgcolor = "white" border=2>
<tr>
<th>�ݒ�敪</th>
<th>���ڋ敪</th>
<th>�ݒ���e</th>
<th>�X�V����</th>
<th>��Ǝ�ID</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nsetuptbl order by setkbn,kmkkbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['SETKBN']);
		printf("<td>%s</td>\n",$row['KMKKBN']);
		printf("<td>%s</td>\n",$row['SETKBNNM']);
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
