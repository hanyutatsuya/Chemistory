<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$sdate  = $_REQUEST['SDATE'];
$kubun  = $_POST['KUBUN'];
$mandai = trim($_POST['MANDAI']);
$kenfr  = trim($_POST['KENFR']);
$kento  = trim($_POST['KENTO']);

if ($kubun == 0)
	{
	$kbn = "L";
	$title = "���{��t�����̔ԍ��͈͒ǉ�";
	}
else
	{
	$kbn = "U";
	$title = "��ʎ�t�����̔ԍ��͈͒ǉ�";
	}

NsfrHeadOutput($title);
NsfrLogOut($title);


printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);
printf("<BR>\n");

if (strlen($mandai) < 3)
	{
	$mandai = "000" . $mandai;
	$mandai = substr($mandai,-3,3);
	}

if (strlen($kenfr) < 4)
	{
	$kenfr = "0000" . $kenfr;
	$kenfr = substr($kenfr,-4,4);
	}

if (strlen($kento) < 4)
	{
	$kento = "0000" . $kento;
	$kento = substr($kento,-4,4);
	}

$kennofr = "00" . $mandai . $kenfr . "00";
$kennoto = "00" . $mandai . $kento . "99";

$tuika = $mandai . " ���� " . " �ԍ��͈́F" . $kenfr . " �` " . $kento;

printf("<BR>\n");

$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select count(*) from nfknjmmst ";
	$sql = $sql . "where sykmkbn = '$kbn' ";
	$sql = $sql . "and  ( '$kennofr' between barcdfr and barcdto ";
	$sql = $sql . "or '$kennoto' between barcdfr and barcdto )";
	$sql = $sql . "for read only";
	$pdst = $conn->prepare($sql);
	$pdst->execute();
	$row = $pdst->fetch(PDO::FETCH_NUM);
	$cnt = $row[0];
	$pdst->closeCursor();

	if  ($cnt > 0)
		{
		printf("<center><h3><FONT COLOR=RED>\n");
		printf("%s �͂��łɓo�^�ς݂ł��B\n",$tuika);
		printf("</FONT></h3></center>\n");
		}
	else
		{
		$conn->beginTransaction();
		$sql = "";
		$sql = $sql . "insert into nfknjmmst ";
		$sql = $sql . "values ('$kbn','$kennofr','$kennoto',";
		$sql = $sql . "current timestamp,current timestamp,'NSFRINIT')";
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();

		if  ($res == FALSE)
			{
			printf("<center><h3><FONT COLOR=RED>\n");
			printf("%s �̓o�^�Ɏ��s���܂����B\n",$tuika);
			printf("</FONT></h3></center>\n");
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			$errflg = 1;
			break;
			}
		else
			{
			$conn->commit();
			printf("<center><h3><FONT COLOR=BLUE>\n");
			printf("%s ��o�^���܂����B\n",$tuika);
			printf("</FONT></h3></center>\n");
			}
		}
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

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
