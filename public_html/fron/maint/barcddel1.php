<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "���b�N�E�o�[�R�[�h���폜";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_REQUEST['SDATE'];
$rack  = $_REQUEST['RACK'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);


$conn = Get_DBConn();

if  ($conn)
	{
	$conn->beginTransaction();

	$sql = "delete from nbcdtbl where lckid = '$rack' ";

	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();
	if  ($res == TRUE)
		{
		$sql = "delete from nfkidctbl where lckid = '$rack' ";
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();
		if  ($res == TRUE)
			{
			$conn->commit();
			printf("<center><P>�h�c[%s]�̃��b�N�E�o�[�R�[�h�����폜���܂���</P></center>\n",$rack);
			NsfrLogOut(sprintf("[%s]�̃��b�N�E�o�[�R�[�h�����폜",$rack));
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

