<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
?>

<?php
$sdate = $_GET['SDATE'];
$ngcd  = $_GET['NGCD'];
$ngscd = $_GET['NGSCD'];

$conn = Get_DBConn();

if  ($conn)
	{
	$title = "ＮＧ復旧処理検体一覧";
	if  ($ngcd != "00")
		{
		$sql = "select bcngsnm from fngsmst where bcngscd = '$ngcd' and bcngsscd = '00' and ukflg = '1' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch();
		$title = $title . "(" . $row[0] ;
		$pdst->closeCursor();
		if  ($ngscd != "00")
			{
			$sql = "select bcngssnm from fngsmst where bcngscd = '$ngcd' and bcngsscd = '$ngscd' and ukflg = '1' for read only";
			$pdst = $conn->prepare($sql);
			$pdst->execute();
			$row = $pdst->fetch();
			$title = $title . "-" . $row[0];
			$pdst->closeCursor();
			}
		$title = $title . ")";
		}
	}

NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

if  ($conn)
	{
	printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>処理日</th>\n");
	printf("<th>検体ナンバー</th>\n");
	printf("<th>ＮＧ処理名</th>\n");
	printf("<th>NG処理詳細</th>\n");
	printf("<th>作業者ID</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct bn.sriymd,bn.barcd,ng.bcngsnm,ng.bcngssnm,bn.yosagid ";
	$sql = $sql . "from fbncjtbl bn,fngsmst ng ";
	$sql = $sql . "where bn.sriymd = '$sdate'  ";
	if  ($ngcd == "00")
		{
		$sql = $sql . "and bn.bcngscd != '  ' ";
		}
	else
		{
		$sql = $sql . "and bn.bcngscd = '$ngcd' ";
		if  ($ngscd != "00")
			{
			$sql = $sql . "and bn.bcngsscd = '$ngscd' ";
			}
		}
	$sql = $sql . "and ng.bcngscd = bn.bcngscd and ng.bcngsscd = bn.bcngsscd ";
	$sql = $sql . "order by bn.barcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",ymd_edit($row[0]));
		printf("<td><A href=bunshosai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",$sdate,substr($row[1],2,9),barcode_edit($row[1]));
		printf("<td>%s</td>\n",$row[2]);
		printf("<td>%s</td>\n",$row[3]);
		printf("<td>%s</td>\n",$row[4]);
		printf("</tr>\n");
		}

printf("</table>\n");
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=ngshori.php?SDATE=%s>ＮＧ復旧処理検体照会に戻る</A></center>\n",$sdate);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>フロンティアシステム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
