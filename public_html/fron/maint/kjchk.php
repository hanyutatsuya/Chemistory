<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
//require_once("../comm/nsfr_db.inc");

$sdate  = $_REQUEST['SDATE'];

$title = "���Җ��`�F�b�N���X�g�����e�i���X";
NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<FORM ACTION=\"kjchkupd.php\" METHOD=\"POST\">\n");
printf("<P>\n");
printf("<center>\n");
printf("<INPUT TYPE=RADIO NAME=KUBUN VALUE=\"0\" checked><TT>���{��t���i�Ԋ|���@�@�@�@�j</TT><BR>\n");
printf("<INPUT TYPE=RADIO NAME=KUBUN VALUE=\"1\"><TT>��ʎ�t���i�A���_�[���C���j</TT><BR>\n");
printf("</center>\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<BR>\n");
printf("<center><BUTTON type=submit name=submit value=\"submit\">�I��\n");
printf("</BUTTON></center>\n");
printf("</P>\n");
printf("</FORM>\n");

printf("<BR CLEAR=ALL>\n");
printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=maint.php?SDATE=%s>�����e�i���X�����ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
