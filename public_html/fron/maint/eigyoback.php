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

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$conn = Get_DBConn();

if  ($conn)
	{
	$kbn = $ekbn[$target];
	$name = $egsnm[$target];
	$ecode = $ecd[$target];

	$sql = "update nfegkmst set egkbn = egskbn,kouhm = current timestamp where egkbn != egskbn";

	$conn->beginTransaction();
	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();
	if  ($res == TRUE)
		{
		$conn->commit();
		printf("<center><P>�񍐋敪�������ݒ�ɖ߂��܂����B</P></center>\n");
		printf("<center><P>����˗��W�J�N������蔽�f����܂��B</P></center>\n");
		NsfrLogOut("�c�Ə��R�[�h�̕񍐋敪�������ݒ�ɕ���");
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
