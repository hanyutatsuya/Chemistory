<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("�t�@�C�����M����",30);
NsfrLogOut("�t�@�C�����M����");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>�t�@�C�����M����</h2></center>

<?php
$sdate = $_REQUEST['SDATE'];
$send1 = $_REQUEST['SEND1'];
$send2 = $_REQUEST['SEND2'];
$send3 = $_REQUEST['SEND3'];
$send4 = $_REQUEST['SEND4'];
$send5 = $_REQUEST['SEND5'];
$send6 = $_REQUEST['SEND6'];

$msg = array(" �����M�@ ",
			 "���M�w���@",
			 " �������@ ",
			 "<FONT COLOR=SKYBLUE>���M�I���@</FONT>",
			 "<FONT COLOR=PINK>���M�G���[</FONT>");
$msg1 = array(" ���쐬�@ ",
			 "�쐬�w���@",
			 " �������@ ",
			 "<FONT COLOR=SKYBLUE>�쐬�I���@</FONT>",
			 "<FONT COLOR=PINK>�쐬�G���[</FONT>");

$conn = Get_DBConn();

$updflg = 0;
if  (!empty($send1))
	{
	$kbn = "31";
	$kmk = "02";
	$fsend = "�a�t�m�o�n�r�P���";
	$updflg = 1;
	}
if  (!empty($send2))
	{
	$kbn = "31";
	$kmk = "03";
	$fsend = "�a�t�m�o�n�r�Q���";
	$updflg = 1;
	}
if  (!empty($send3))
	{
	$kbn = "32";
	$kmk = "02";
	$fsend = "�������̏��";
	$updflg = 1;
	}
if  (!empty($send4))
	{
	$kbn = "33";
	$kmk = "02";
	$fsend = "���茟�̏��";
	$updflg = 1;
	}
if  (!empty($send5))
	{
	$kbn = "34";
	$kmk = "03";
	$fsend = "�������쐬";
	$updflg = 1;
	}
if  (!empty($send6))
	{
	$kbn = "34";
	$kmk = "02";
	$fsend = "�������̏��";
	$updflg = 1;
	}

if  ($conn)
	{
//	printf("<center><h2>�������F%s</h2></center>\n",$sdate);

	if ($updflg != 0)
		{
		$sql = "";
		$sql = $sql . "update nsetuptbl set setkbnnm = '1',kouhm = current timestamp ";
		$sql = $sql . "where setkbn = '$kbn' and kmkkbn = '$kmk' and setkbnnm = '0' " ;
		$conn->beginTransaction();
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();
		if  ($res == TRUE)
			{
			$conn->commit();
			if  (!empty($send5))
				{
				printf("<center><P><FONT color=red>%s�̎w�������܂����B</FONT></P></center>\n",$fsend);
				NsfrLogOut(sprintf("[%s]�w��",$fsend));
				}
			else
				{
				printf("<center><P><FONT color=red>%s�̑��M�w�������܂����B</FONT></P></center>\n",$fsend);
				NsfrLogOut(sprintf("[%s]���M�w��",$fsend));
				}
			}
		else
			{
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			}
		}
	else
		{
		printf("<center><P>������I�����Ă��������B</P></center>\n",$fsend);
		}

	$sql = "";
	$sql = $sql . "select setkbn,kmkkbn,setkbnnm,kouhm from nsetuptbl ";
	$sql = $sql . "where setkbn in ('31','32','33','34') ";
	$sql = $sql . "and kmkkbn in ('01','02','03') ";
	$sql = $sql . "order by setkbn,kmkkbn for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$setup[$row[0]-31][$row[1]-1][0] = $row[2];
		$setup[$row[0]-31][$row[1]-1][1] = $row[3];
		}

//printf("[%d][%d]<BR>\n",$setup[3][2][0],$setup[3][2][0]);
	if ($setup[3][2][0] == 3 || $setup[3][2][0] == 9)
		{
		$cnt[0] = 0;
		$cnt[1] = 0;

		$sql = "";
		$sql = $sql . "select count(distinct kntno) from nfmitbl ";
		$sql = $sql . "where sriymd = '$sdate' ";
		$sql = $sql . "for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[0] = $row[0];
		$pdst->closeCursor();
//printf("[%s][%d][%d]<BR>\n",$sql,$cnt[0],$row[0]);

		$sql = "";
		$sql = $sql . "select count(*) from nfmitbl ";
		$sql = $sql . "where sriymd = '$sdate' ";
		$sql = $sql . "for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[1] = $row[0];
		$pdst->closeCursor();
//printf("[%s][%d][%d]<BR>\n",$sql,$cnt[1],$row[0]);

		}
//printf("[%d][%d]<BR>\n",$cnt[0],$cnt[1]);
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<P><TT>\n");
printf("�@\n");
printf("</TT></P>\n");


printf("<FORM ACTION=\"fsend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("�a�t�m�o�n�r�P��� [%s]\n",$msg[$setup[0][1][0]]);
if ($setup[0][1][0] == 0)
	{
	printf("�@<BUTTON type=submit name=SEND1 value=\"submit\"><BIG>���@�M</BIG>\n");
	printf("</BUTTON>\n");
	}
if ($setup[0][1][0] == 3 || $setup[0][1][0] == 9)
	printf("�@���M���� [%s]\n",substr($setup[0][1][1],0,19));
printf("</TT></P>\n");
printf("</FORM>\n");
printf("<BR>\n");

printf("<FORM ACTION=\"fsend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("�a�t�m�o�n�r�Q��� [%s]\n",$msg[$setup[0][2][0]]);
if ($setup[0][1][0] == 3 && $setup[0][2][0] == 0)
	{
	printf("�@<BUTTON type=submit name=SEND2 value=\"submit\"><BIG>���@�M</BIG>\n");
	printf("</BUTTON>\n");
	}
if ($setup[0][2][0] == 3 || $setup[0][2][0] == 9)
	printf("�@���M���� [%s]\n",substr($setup[0][2][1],0,19));
printf("</TT></P>\n");
printf("</FORM>\n");
printf("<BR>\n");

printf("<FORM ACTION=\"fsend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("�������̏��@�@�@ [%s]\n",$msg[$setup[1][1][0]]);
if ($setup[1][1][0] == 0)
	{
	printf("�@<BUTTON type=submit name=SEND3 value=\"submit\"><BIG>���@�M</BIG>\n");
	printf("</BUTTON>\n");
	}
if ($setup[1][1][0] == 3 || $setup[1][1][0] == 9)
	printf("�@���M���� [%s]\n",substr($setup[1][1][1],0,19));
printf("</TT></P>\n");
printf("</FORM>\n");
printf("<BR>\n");

printf("<FORM ACTION=\"fsend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("���茟�̏��@�@�@ [%s]\n",$msg[$setup[2][1][0]]);
if ($setup[2][1][0] == 0)
	{
	printf("�@<BUTTON type=submit name=SEND4 value=\"submit\"><BIG>���@�M</BIG>\n");
	printf("</BUTTON>\n");
	}
if ($setup[2][1][0] == 3 || $setup[2][1][0] == 9)
	printf("�@���M���� [%s]\n",substr($setup[2][1][1],0,19));
printf("</TT></P>\n");
printf("</FORM>\n");
printf("<BR>\n");

printf("<FORM ACTION=\"fsend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("�������̏��쐬�@ [%s]\n",$msg1[$setup[3][2][0]]);
if ($setup[3][1][0] == 0)
	{
	printf("�@<BUTTON type=submit name=SEND5 value=\"submit\"><BIG>��@��</BIG>\n");
	printf("</BUTTON>\n");
	}
if ($setup[3][2][0] == 3 || $setup[3][2][0] == 9)
	{
	printf("�@�쐬���� [%s]\n",substr($setup[3][2][1],0,19));
	printf("�@[%d] ���́@[%d] ����\n",$cnt[0],$cnt[1]);
	}
printf("</TT></P>\n");
printf("</FORM>\n");
printf("<BR>\n");

printf("<FORM ACTION=\"fsend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("�������̏��@�@�@ [%s]\n",$msg[$setup[3][1][0]]);
if ($setup[3][2][0] == 3 && $setup[3][1][0] == 0)
	{
	printf("�@<BUTTON type=submit name=SEND6 value=\"submit\"><BIG>���@�M</BIG>\n");
	printf("</BUTTON>\n");
	}
if ($setup[3][1][0] == 3 || $setup[3][2][0] == 9)
	printf("�@���M���� [%s]\n",substr($setup[3][1][1],0,19));
printf("</TT></P>\n");
printf("</FORM>\n");
printf("<BR>\n");

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>�t�����e�B�A�V�X�e���Ɖ���ꗗ�ɖ߂�</A></center>\n",$sdate);
printf("</P>\n");
?>

<HR>
<P>
<center><A href=../index.php>�g�b�v�ɖ߂�</A></center>
</P>
<HR>
</BODY>
</HTML>
