<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�t�����e�B�A�V�X�e���Ɖ���ꗗ");
NsfrLogOut("�t�����e�B�A�V�X�e���Ɖ���ꗗ");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�t�����e�B�A�V�X�e���Ɖ���ꗗ</h2></center>

<?php
$shoribi = trim($_REQUEST['SDATE']);

if  (!is_numeric($shoribi) || strlen($shoribi) == 0)
	{
	$conn = Get_DBConn();
	$sdate = Get_Shoribi($conn);

	$conn = null;
	}
else
	{
	$sdate = $shoribi;
	}

printf("<center><h2>�������F%s</h2></center>\n",$sdate);

?>

<P>
<center>
<FORM ACTION="bunchu.php" METHOD="POST">
�������ύX
<INPUT TYPE=text NAME="SDATE" SIZE=10 MAXLENGTH=8>
<BUTTON name="submit" value="submit" type="submit">�ύX
</BUTTON>
</FORM>
</center>
</P>

<?php
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>�Ɖ������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mishori.php?SDATE=%s>�������`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=uketori.php?SDATE=%s>���󂯎��g���[�`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hibunchu.php?SDATE=%s>�񕪒����ʑ��M����</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td bgcolor=white><A href=ngshori.php?SDATE=%s>�m�f�����������̏Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=miisai.php?SDATE=%s>�ڍږ��������b�N�`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=milabel.php?SDATE=%s>�����C�g���x�����o�̓`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mipaki.php?SDATE=%s>�p�L�p�L���x�����o�̓`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td bgcolor=white><A href=pakishokai.php?SDATE=%s>�p�L�p�L�d�������̏Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td bgcolor=yellow><A href=pakishokai2.php?SDATE=%s>�p�L�p�L�d�������̏Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=rfid1ran.php?SDATE=%s>�p�L�p�L���q�e�h�c�Ɖ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fkanjachk.php?SDATE=%s>���Җ��`�F�b�N���X�g�o�͊m�F</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fsend.php?SDATE=%s>�t�@�C�����M����</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kanban.php?SDATE=%s>�Ŕ�ID���ݒ胉�b�N�`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=hikiwatasi.php?SDATE=%s>�������n�����b�N�`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");
?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
</BODY>
</HTML>
