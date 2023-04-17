<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "営業所区分追加";
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
			$hkbn = "１回目";
		if  (strcmp($ekbn,"2") == 0)
			$hkbn = "２回目";
		if  (strcmp($ekbn,"9") == 0)
			$hkbn = "通常分";

		for ($i=0;$i<$cnt;$i++)
			{
			if  (strcmp($ekbn[$i],"1") == 0)
				$hkbn = "１回目";
			if  (strcmp($ekbn[$i],"2") == 0)
				$hkbn = "２回目";
			if  (strcmp($ekbn[$i],"9") == 0)
				$hkbn = "通常分";
			printf("<center><P>営業所コード:%sを報告区分<FONT color=red>[%s]</FONT>で登録しました。</P></center>\n",
				$ecd[$i],$hkbn);
			}
		printf("<center><P>次回依頼展開起動時より反映されます。</P></center>\n");
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
