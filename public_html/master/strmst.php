<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�T�e���C�g�}�X�^");
NsfrLogOut("�T�e���C�g�}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�T�e���C�g�}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th>STLID</th>
<th>�V���敪</th>
<th>�T�e���C�g����</th>
<th>����</th>
<th>IP�A�h���X</th>
<th>PORT1</th>
<th>�o�̓^�C�~���O</th>
<th>�J�n��</th>
<th>�I����</th>
<th>�쐬����</th>
<th>�X�V����</th>
<th>��Ǝ҂h�c</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from nfstrmst where ukflg = '1' order by stid for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row['STID']);
		printf("<td>%s</td>\n",$row['SKKBN']);
		printf("<td>%s</td>\n",$row['STNM']);
		printf("<td>%s</td>\n",$row['STNMR']);
		printf("<td>%s</td>\n",$row['IPADD']);
		printf("<td>%s</td>\n",$row['PORT1']);
		printf("<td>%s</td>\n",$row['OUTTMG']);
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
