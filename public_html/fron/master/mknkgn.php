<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�@�\�����}�X�^");
NsfrLogOut("�@�\�����}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>�@�\�����}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th nowrap>�Ј�No.</th>
<th nowrap>�V�X�e��ID</th>
<th nowrap>���샌�x��</th>
<th nowrap>�e�WF</th>
<th nowrap>���Җ�F</th>
<th nowrap>�ėp�t���O</th>
<th nowrap>�ŏI���O�C������</th>
<th nowrap>�����ݒ�F</th>
<th nowrap>�����敪</th>
<th nowrap>�ύX�敪</th>
<th nowrap>�z�M�ς�FLG</th>
<th nowrap>�J�n�N����</th>
<th nowrap>�I���N����</th>
<th nowrap>�o�^�N����</th>
<th nowrap>�ύX�N����</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn){
	$sql = "select * from m_knkgn order by usrid for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row['USRID']);
		printf("<td nowrap>%s</td>\n",$row['STMID']);
		printf("<td nowrap>%d</td>\n",$row['SUSLBL']);
		printf("<td nowrap>%s</td>\n",$row['STERKGFLG']);
		printf("<td nowrap>%s</td>\n",$row['KNJSSKGFLG']);
		printf("<td nowrap>%s</td>\n",$row['HNYFLG']);
		printf("<td nowrap>%19.19s</td>\n",$row['SSLGINDH']);
		printf("<td nowrap>%s</td>\n",$row['KGSTFLG']);
		printf("<td nowrap>%s</td>\n",$row['RRKKBN']);
		printf("<td nowrap>%s</td>\n",$row['HKKBN']);
		printf("<td nowrap>%s</td>\n",$row['HSSFLG']);
		printf("<td nowrap>%s</td>\n",$row['KISYMD']);
		printf("<td nowrap>%s</td>\n",$row['ENDYMD']);
		printf("<td nowrap>%s</td>\n",$row['TRKYMD']);
		printf("<td nowrap>%s</td>\n",$row['HKYMD']);
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
