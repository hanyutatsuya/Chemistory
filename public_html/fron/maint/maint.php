<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");

NsfrHeadOutput("�����e�i���X�����ꗗ");
NsfrLogOut("�����e�i���X�����ꗗ");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�����e�i���X�����ꗗ</h2></center>

<?php
//$usrname = trim($_POST['UNAME']);
$shoribi = trim($_POST['sriymd']);

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
<FORM ACTION="maint.php" METHOD="POST">
�������ύX
<INPUT TYPE=text NAME="sriymd" SIZE=10 MAXLENGTH=8>
<BUTTON name="submit" value="submit" type="submit">�ύX
</BUTTON>

</FORM>
</center>
</P>

<?php

//	printf("<center><P>�S���ҁF%s</P></center>\n",$usrname);
	printf("<HR>\n");

	printf("<center><P>���G�n��t�Ή�</P></center>\n");
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>���G�n��t�Ή���������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=fukusu.php?SDATE=%s>�������̓o�^����</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tkhimo.php?SDATE=%s>�������̕R�t������</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>�F�����u�_�E�����Ή�</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>�F�����u�_�E����������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tkbardel.php?SDATE=%s>���b�N�E�o�[�R�[�h���폜�i�T�O�{���b�N�j</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=tjbardel.php?SDATE=%s>���b�N�E�o�[�R�[�h���폜�i�P�O�{���b�N�j</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=mrack.php?SDATE=%s>���������b�N�`�F�b�N</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=krackend.php?SDATE=%s>���b�N���������o�^</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");


	printf("<center><P>�����@�_�E�����Ή�</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>�����@�_�E����������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=rackanryo.php?SDATE=%s>���b�N���������o�^</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=traykanryo.php?SDATE=%s>�g���[���������o�^</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>�����e�i���X����</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>�����e�i���X��������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=pakisai.php?SDATE=%s>�d�������x���ďo��</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=zpatmnt.php?SDATE=%s>�d�������x���y�p�^�[�������e�i���X</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>���Җ��`�F�b�N���X�g����</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>�ێ珈������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kjchk.php>���̃i���o�[�͈͐ݒ�</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>�񍐋敪�ێ珈��</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>�ێ珈������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=eigyo.php?SDATE=%s>�c�Ə��敪�ύX</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=eigyoadd.php?SDATE=%s>�c�Ə��敪�ǉ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=shuken.php?SDATE=%s>�W������ێ�</A></td>\n",$sdate);
	printf("</tr>\n");

	printf("</table>\n");

?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
</BODY>
</HTML>
