<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("���^�E�G���h�g�L�V�����̃��X�g�o�͏���");
NsfrLogOut("���^�E�G���h�g�L�V�����̃��X�g�o�͏���");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>���^�E�G���h�g�L�V�����̃��X�g�o�͏���</h2></center>

<?php
//$sdate = $_REQUEST['SDATE'];
$send1 = $_REQUEST['SEND1'];
$send2 = $_REQUEST['SEND2'];

$updflg = 0;
if  (!empty($send1))
	{
	$msg = "�@�@�@�@�@���^���̃��X�g";
	$app = "/home/nsfr/bin/lst_abo.php";
	$updflg = 1;
	}
if  (!empty($send2))
	{
	$msg = "�G���h�g�L�V�����̃��X�g";
	$app = "/home/nsfr/bin/lst_end.php";
	$updflg = 2;
	}

if ($updflg != 0)
	{
	$sret = shell_exec($app);
	printf("<P>\n");
	printf("%s���o�͂��܂����B\n",$msg);
	printf("</P>\n");
	printf("<HR>\n");
	}


printf("<FORM ACTION=\"aboend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("�@�@�@�@�@���^���̃��X�g\n");
printf("�@<BUTTON type=submit name=SEND1 value=\"submit\">�o�@��\n");
printf("</BUTTON>\n");
printf("</FORM>\n");

printf("<FORM ACTION=\"aboend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("�G���h�g�L�V�����̃��X�g\n");
	printf("�@<BUTTON type=submit name=SEND2 value=\"submit\">�o�@��\n");
	printf("</BUTTON>\n");
printf("</FORM>\n");

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>���̔F���V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
