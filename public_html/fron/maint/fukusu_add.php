<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_class.inc");
require_once("../comm/ssmst_class.inc");

$title = "�����{��茟�̓o�^����";
NsfrHeadOutput($title);
NsfrLogOut($title);

$type   = $_POST['TYPE'];
$sdate  = $_POST['SDATE'];
$kenno  = $_POST['KENNO'];
$sskbn  = trim($_POST['SSKBN']);
$kenseq = (int)trim($_POST['KENSEQ']);
$kenno1 = $_POST['KENNO1'];
$kenno2 = $_POST['KENNO2'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<P>������ �F%s</P>\n",ymd_edit($sdate));
printf("<P>����No.�F%s</P>\n",kenno_edit(barcode_conv($kenno)));

if  (Input_Check() == TRUE)
	{
	$conn = Get_DBConn();
	$nsfr = new Nsfr($conn);
	$nsfr->Clear();
	$nsfr->SetSdate($sdate);
	$nsfr->SetKenno($kenno);

	switch ($type)
		{
		case "0":
			//	���G�n�����o�^�ς݂ɒǉ��o�^
			$ret = Fukuzatsu_Add($nsfr);
			break;
		case "1":
			//	�P���n�F���ς݌��̂ɕ������̂�ǉ��o�^
			$ret = Tanjun_Add($nsfr);
			break;
		case "2":
			//	�P���n���F�����̂ɕ����o�^����
			$ret = Tanjun_2Hon($nsfr);
			break;
		}

	if  ($ret == TRUE)
		{
		printf("<P><FONT color=blue>�����{���o�^���s���܂����B</FONT></P>\n");
		}
	else
		{
		printf("<P><FONT color=red>�����{���o�^���ł��܂���ł����B</FONT></P>\n");
		}
	}

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=fukusu.php?SDATE=%s>�����{��茟�̓o�^�����ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
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

<?php

//	���͒l�`�F�b�N
function Input_Check()
{
	global $type,$sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;

	if  (ymd_check($sdate) != TRUE)
		{
		printf("<P><FONT color=red>���������̓G���[�ł��B</FONT></P>\n");
		return(FALSE);
		}

	if  ($type == 0 || $type == 1)
		{
		if (strlen(barcode_conv($kenno1)) < 9 ||
			strncmp(barcode_conv($kenno),barcode_conv($kenno1),9) != 0)
			{
			printf("<P>���̃i���o�[ [%s][%s]</P>\n",$kenno ,barcode_conv($kenno));
			printf("<P>���̃i���o�[1[%s][%s]</P>\n",$kenno1,barcode_conv($kenno1));
			printf("<P><FONT color=red>���̃i���o�[���̓G���[�ł��B</FONT></P>\n");
			return(FALSE);
			}
		}
	else
		{
		if (strlen(barcode_conv($kenno1)) < 9 ||
			strlen(barcode_conv($kenno2)) < 9 ||
			strncmp(barcode_conv($kenno),barcode_conv($kenno1),9) != 0 ||
			strncmp(barcode_conv($kenno),barcode_conv($kenno2),9) != 0)
			{
			printf("<P>���̃i���o�[ [%s][%s]</P>\n",$kenno ,barcode_conv($kenno));
			printf("<P>���̃i���o�[1[%s][%s]</P>\n",$kenno1,barcode_conv($kenno1));
			printf("<P>���̃i���o�[2[%s][%s]</P>\n",$kenno2,barcode_conv($kenno2));
			printf("<P><FONT color=red>���̃i���o�[���̓G���[�ł��B</FONT></P>\n");
			return(FALSE);
			}
		}

	return(TRUE);
}

//	���G�n�����o�^�ς݂ɒǉ��o�^
function Fukuzatsu_Add($nsfr)
{
	global $conn;
	global $sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;


	printf("���G�n����<BR>\n");
	printf("������ �F%s<BR>\n",ymd_edit($sdate));
	printf("����No.�F%s<BR>\n",kenno_edit(barcode_conv($kenno)));

	printf("����No.�F%s �𕡐��{�o�^<BR>\n",kenno_edit(barcode_conv($kenno1)));

	return(TRUE);
}

//	�P���n�F���ς݌��̂ɕ������̂�ǉ��o�^
function Tanjun_Add($nsfr)
{
	global $conn;
	global $sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;

	printf("�P���n����<BR>\n");
	printf("������ �F%s<BR>\n",ymd_edit($sdate));
	printf("����No.�F%s<BR>\n",kenno_edit(barcode_conv($kenno)));

	printf("����No.�F%s �𕡐��{�ǉ�<BR>\n",kenno_edit(barcode_conv($kenno1)));

	return(TRUE);
}

//	�P���n���F�����̂ɕ����o�^����
function Tanjun_2Hon($nsfr)
{
	global $conn;
	global $sdate,$kenno,$sskbn,$kenseq,$kenno1,$kenno2;

	printf("�P���n����<BR>\n");
	printf("������ �F%s<BR>\n",ymd_edit($sdate));
	printf("����No.�F%s<BR>\n",kenno_edit(barcode_conv($kenno)));

	printf("����No.�F%s �𕡐��{�o�^<BR>\n",kenno_edit(barcode_conv($kenno1)));
	printf("����No.�F%s �𕡐��{�o�^<BR>\n",kenno_edit(barcode_conv($kenno2)));

	return(TRUE);
}



?>

