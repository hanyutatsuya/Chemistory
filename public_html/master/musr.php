<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("���[�U�[�Ǘ��}�X�^");
NsfrLogOut("���[�U�[�Ǘ��}�X�^");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>���[�U�[�Ǘ��}�X�^</h2></center>

<table align="center" bgcolor = "white" border>
<tr>
<th nowrap>�Ј�No.</th>
<th nowrap>�J�[�hID</th>
<th nowrap>�p�X���[�h</th>
<th nowrap>���[�U�[��</th>
<th nowrap>��PW1</th>
<th nowrap>��PW2</th>
<th nowrap>PW�L������</th>
<th nowrap>�ŏI���O�C������</th>
<th nowrap>���O�C���L������</th>
<th nowrap>�g�p�֎~�敪</th>
<th nowrap>�E��CD</th>
<th nowrap>�Z���^�[CD</th>
<th nowrap>�c�Ə�CD</th>
<th nowrap>���{CD</th>
<th nowrap>SECCD</th>
<th nowrap>�g�p�֎~����</th>
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
	$sql = "select * from m_usr order by usrid for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row['USRID']);
		printf("<td nowrap>%s</td>\n",$row['CDID']);
		printf("<td nowrap>********</td>\n");
		printf("<td nowrap>%s</td>\n",$row['USRNM']);
		printf("<td nowrap>********</td>\n");
		printf("<td nowrap>********</td>\n");
		printf("<td nowrap>%s</td>\n",$row['PWYKKGN']);
		printf("<td nowrap>%19.19s</td>\n",$row['SSLGINDH']);
		printf("<td nowrap>%s</td>\n",$row['LGINYKKGN']);
		printf("<td nowrap>%s</td>\n",$row['SYKNSKBN']);
		printf("<td nowrap>%s</td>\n",$row['SKSCD']);
		printf("<td nowrap>%s</td>\n",$row['CTCD']);
		printf("<td nowrap>%s</td>\n",$row['EGSCD']);
		printf("<td nowrap>%s</td>\n",$row['LBCD']);
		printf("<td nowrap>%s</td>\n",$row['SECCD']);
		printf("<td nowrap>%10.10s</td>\n",$row['SYKNSDH']);
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
