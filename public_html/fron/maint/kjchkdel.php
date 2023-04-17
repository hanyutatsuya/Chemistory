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
	$title = "ラボ受付分検体番号範囲追加";
	}
else
	{
	$kbn = "U";
	$title = "埼玉受付分検体番号範囲追加";
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

$tuika = $mandai . " 万台 " . " 番号範囲：" . $kenfr . " ～ " . $kento;

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
		printf("%s の削除に失敗しました。\n",$tuika);
		printf("</FONT></h3></center>\n");
		$errinfo = $pdst->errorInfo();
		$conn->rollBack();
		NsfrDBErrorMsg($sql,$errinfo);
		}
	else
		{
		$conn->commit();
		printf("<center><h3><FONT COLOR=BLUE>\n");
		printf("%s を削除しました。\n",$tuika);
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
