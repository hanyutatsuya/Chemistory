<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "�c�Ə��敪�����e�i���X";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_POST['SDATE'];
$ekbn  = $_POST['EKBN'];
$ecd   = $_POST['ECD'];
$egsnm = $_POST['EGSNM'];
$updbu = $_POST['UPDBU'];
$sekbn  = $_POST['SEKBN'];
$supdbu = $_POST['SUPDBU'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$cnt = count($ecd);
for ($i=0;$i<$cnt;$i++)
	{
printf("[%d][%s][%s][%s]<BR>\n",$i,$ecd[$i],$updbu[$i],$supdbu[$i]);
	}
for ($i=0;$i<$cnt;$i++)
	{
	if  (!empty($supdbu[$i]))
		{
		$target = $i;
		$cul = 0;
		break;
		}
	if  (!empty($updbu[$i]))
		{
		$target = $i;
		$cul = 1;
		break;
		}
	}

$conn = Get_DBConn();

if  ($conn)
	{
	if ($cul == 0)
		$kbn = $sekbn[$target];
	else
		$kbn = $ekbn[$target];
	$name = $egsnm[$target];
	$ecode = $ecd[$target];

	if ($cul == 0)
		$sql = "update nfegkmst set egkbn = '$kbn',egskbn = '$kbn',kouhm = current timestamp where ecd = '$ecode' ";
	else
		$sql = "update nfegkmst set egkbn = '$kbn',kouhm = current timestamp where ecd = '$ecode' ";

	$conn->beginTransaction();
	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();
	if  ($res == TRUE)
		{
		$conn->commit();
		if  (strcmp($kbn,"1") == 0)
			$hkbn = "�P���";
		if  (strcmp($kbn,"2") == 0)
			$hkbn = "�Q���";
		if  (strcmp($kbn,"9") == 0)
			$hkbn = "�ʏ핪";

		if ($cul == 0)
			{
			printf("<center><P>�c�Ə��R�[�h:%s(%s)�̕񍐋敪�����l��<FONT color=red>[%s]</FONT>�ɕύX���܂����B</P></center>\n",
				$ecode,$name,$hkbn);
			}
		else
			{
			printf("<center><P>�c�Ə��R�[�h:%s(%s)�̕񍐋敪��<FONT color=red>[%s]</FONT>�ɕύX���܂����B</P></center>\n",
				$ecode,$name,$hkbn);
			}
		
		printf("<center><P>����˗��W�J�N������蔽�f����܂��B</P></center>\n");
		NsfrLogOut(sprintf("�c�Ə��R�[�h[%s]�̕񍐋敪��[%s]�ɕύX",$ecode,$hkbn));
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
	echo "Connection failed";
	}
$conn = null;

printf("<HR>\n");
NsfrBackPage();
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
