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
		printf("<center><P>報告区分を初期設定に戻しました。</P></center>\n");
		printf("<center><P>次回依頼展開起動時より反映されます。</P></center>\n");
		NsfrLogOut("営業所コードの報告区分を初期設定に復元");
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
