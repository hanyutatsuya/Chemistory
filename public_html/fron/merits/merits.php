<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");

NsfrHeadOutput("�����b�c�����ꗗ");
NsfrLogOut("�����b�c�����ꗗ");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�����b�c�����ꗗ</h2></center>

<?php

	printf("<center><P>��������</P></center>\n");
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>��������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=sel_ino.php>�˗����i���o�[����</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=krackmap.php>���̃��b�N�}�b�v�Ɖ�</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=arackmap.php>�A�b�Z�C���b�N�}�b�v�Ɖ�</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kensu.php>���̔F�����Ɖ�</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>�V�K�f�[�^�쐬</P></center>\n");
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>��������</th>\n");
	printf("</tr>\n");



	printf("<tr>\n");
	printf("<td><A href=zokusei.php>�V�K�����o�^����</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=iraiins.php>�V�K���ړo�^����</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>�����@�_�E�����Ή�</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>�����@�_�E�����Ή���������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=rackanryo.php>���b�N���������o�^</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=traykanryo.php>�g���[���������o�^</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>�V�X�e���Ɖ��</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>��������</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=weblog.php>�v�������O�t�@�C���Ɖ�</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");
?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
</BODY>
</HTML>
