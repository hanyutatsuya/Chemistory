<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");

$title = "�����{��茟�̓o�^����";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_GET['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<P>�������F%s</P>\n",ymd_edit($sdate));

printf("<P>\n");
printf("�����{�o�^���錟��No.����͂��Ă�������\n");

printf("<FORM ACTION=\"fukusu1.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=text NAME=\"KENNO\" SIZE=14 MAXLENGTH=13>\n");

printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">����\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</P></center>\n");

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
