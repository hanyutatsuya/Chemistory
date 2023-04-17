<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "仕分けラベル出力済みフラグリセット";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_POST['SDATE'];
$item  = $_POST['ITEM'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);


$conn = Get_DBConn();

if  ($conn)
	{

	if  ($item != '00')
		{
		$sql = "";
		$sql = $sql . "select itmnm,zrlcknm ";
		$sql = $sql . "from fitmcmst ";
		$sql = $sql . "where itmcd = '$item' and ukflg = '1' ";
		$sql = $sql . "order by itmcd for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch();
		$itemname = substr(trim($row[0]),0,4) . "(" . trim($row[1]) . ")";
		$pdst->closeCursor();
		}
	else
		$itemname = "";


	$sql = "update fpkptbl set outflg = '0' where sriymd = '$sdate' ";
	if  ($item != '00')
		{
		$sql = $sql . "and itmcd = '$item' ";
		}

	$conn->beginTransaction();
	$pdst = $conn->prepare($sql);
	$res = $pdst->execute();
	if  ($res == TRUE)
		{
		$conn->commit();
		printf("<center><P>処理日：%s %sの仕分けラベルの出力済みフラグをリセットしました</P></center>\n",
				ymd_edit($sdate),$itemname);
		NsfrLogOut(sprintf("[%s]-%sの仕分けラベルの出力済みフラグをリセット",ymd_edit($sdate),$itemname));
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
