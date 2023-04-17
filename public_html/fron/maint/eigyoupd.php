<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "営業所区分メンテナンス";
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
			$hkbn = "１回目";
		if  (strcmp($kbn,"2") == 0)
			$hkbn = "２回目";
		if  (strcmp($kbn,"9") == 0)
			$hkbn = "通常分";

		if ($cul == 0)
			{
			printf("<center><P>営業所コード:%s(%s)の報告区分初期値を<FONT color=red>[%s]</FONT>に変更しました。</P></center>\n",
				$ecode,$name,$hkbn);
			}
		else
			{
			printf("<center><P>営業所コード:%s(%s)の報告区分を<FONT color=red>[%s]</FONT>に変更しました。</P></center>\n",
				$ecode,$name,$hkbn);
			}
		
		printf("<center><P>次回依頼展開起動時より反映されます。</P></center>\n");
		NsfrLogOut(sprintf("営業所コード[%s]の報告区分を[%s]に変更",$ecode,$hkbn));
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
printf("<center><A href=maint.php?SDATE=%s>メンテナンス処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
