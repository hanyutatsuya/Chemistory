<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$sdate  = $_REQUEST['SDATE'];
$kubun  = $_POST['KUBUN'];
$kennofr  = $_POST['KENFR'];
$kennoto  = $_POST['KENTO'];
$delbu = $_POST['DELBU'];

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

$cnt = count($kennofr);
for ($i=0;$i<$cnt;$i++)
	{
	if  (!empty($delbu[$i]))
		{
		$target = $i;
		break;
		}
	}

$mandai = substr($kennofr[$target],2,3);
$kenfr = substr($kennofr[$target],5,4);
$kento = substr($kennoto[$target],5,4);
$ken1 = $kennofr[$target];
$ken2 = $kennoto[$target];

$tuika = $mandai . " ���� " . " �ԍ��͈́F" . $kenfr . " �` " . $kento;

printf("<BR>\n");

$conn = Get_DBConn();

if  ($conn)
	{
	$conn->beginTransaction();
	$sql = "";
	$sql = $sql . "delete from nfknjmmst ";
	$sql = $sql . "where sykmkbn = '$kbn' ";
	$sql = $sql . "and  barcdfr = '$ken1' ";
	$sql = $sql . "and  barcdto = '$ken2' ";
	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();

	if  ($res == FALSE)
		{
		printf("<center><h3><FONT COLOR=RED>\n");
		printf("%s �̍폜�Ɏ��s���܂����B\n",$tuika);
		printf("</FONT></h3></center>\n");
		$errinfo = $pdst->errorInfo();
		$conn->rollBack();
		NsfrDBErrorMsg($sql,$errinfo);
		}
	else
		{
		$conn->commit();
		printf("<center><h3><FONT COLOR=BLUE>\n");
		printf("%s ���폜���܂����B\n",$tuika);
		printf("</FONT></h3></center>\n");
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
