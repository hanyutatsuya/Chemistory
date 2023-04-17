<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "�c�Ə��敪�ǉ�";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_POST['SDATE'];
$ekbn  = $_POST['EKBN'];
$ecd   = $_POST['ECD'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$cnt = count($ecd);

$conn = Get_DBConn();

if  ($conn)
	{
	$conn->beginTransaction();
	$errflg = 0;
	for ($i=0;$i<$cnt;$i++)
		{
		$kbn = $ekbn[$i];
		$ecode = $ecd[$i];

		$sql = "insert into nfegkmst select ecd,egsnm,'$kbn','$kbn',sakhm,current timestamp,sagyoid from nfegsmst where ecd = '$ecode' ";
		$pdst = $conn->prepare($sql);
		$res = $pdst->execute();

		if  ($res == FALSE)
			{
			$errinfo = $pdst->errorInfo();
			$conn->rollBack();
			NsfrDBErrorMsg($sql,$errinfo);
			$errflg = 1;
			break;
			}
		}

	if  ($errflg == 0)
		{
		$conn->commit();
		if  (strcmp($ekbn[$i],"1") == 0)
			$hkbn = "�P���";
		if  (strcmp($ekbn,"2") == 0)
			$hkbn = "�Q���";
		if  (strcmp($ekbn,"9") == 0)
			$hkbn = "�ʏ핪";

		for ($i=0;$i<$cnt;$i++)
			{
			if  (strcmp($ekbn[$i],"1") == 0)
				$hkbn = "�P���";
			if  (strcmp($ekbn[$i],"2") == 0)
				$hkbn = "�Q���";
			if  (strcmp($ekbn[$i],"9") == 0)
				$hkbn = "�ʏ핪";
			printf("<center><P>�c�Ə��R�[�h:%s��񍐋敪<FONT color=red>[%s]</FONT>�œo�^���܂����B</P></center>\n",
				$ecd[$i],$hkbn);
			}
		printf("<center><P>����˗��W�J�N������蔽�f����܂��B</P></center>\n");
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
