<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("分注機マスタ設定");
NsfrLogOut("分注機マスタ設定");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>分注機マスタ設定</h2></center>

<?php
$item = trim($_GET['ITEM']);
$wscd = trim($_GET['WSCD']);
?>

<table align = left border=0>
<tr valign=top>
<td>
<table bgcolor = white border>
<tr>
<th>ITEMCD</th>
<th>ITEMCD名</th>
<th>ラック表示</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select itmcd,itmnm,zrlcknm ";
	$sql = $sql . "from fitmcmst ";
	$sql = $sql . "where ukflg = '1' ";
	$sql = $sql . "order by itmcd for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row[0]);
		printf("<td><A href=bunmst.php?ITEM=%s>%s</A></td>\n",$row[0],$row[1]);
		printf("<td><A href=bunmst.php?ITEM=%s>%s</A></td>\n",$row[0],$row[2]);
		printf("<td>%s</td>\n",$row[3]);
		printf("</tr>\n");
		}
	printf("</table>\n");

	if  ($item != "")
		{
		printf("<td>\n");
		printf("<table bgcolor = white border>\n");
		printf("<tr>\n");
		printf("<th>ITEMCD名</th>\n");
		printf("<th>仕分け先</th>\n");
		printf("<th>ＷＳコード</th>\n");
		printf("<th>ＷＳ名</th>\n");
		printf("<th>サテライト</th>\n");
		printf("</tr>\n");

		$sql = "";
		$sql = $sql . "select it.itmnm,ws.swkskid,ws.smpcd,ws.smpcdnm,ws.stid ";
		$sql = $sql . "from nfsmpmst ws,fitmcmst it ";
		$sql = $sql . "where it.itmcd = '$item' ";
		$sql = $sql . "and it.ukflg = '1' ";
		$sql = $sql . "and ws.itmcd = it.itmcd ";
		$sql = $sql . "and ws.ukflg = '1' ";
		$sql = $sql . "order by ws.swkskid,ws.smpcd for read only";
		foreach ($conn->query($sql) as $row)
			{
			printf("<tr>\n");
			printf("<td>%s</td>\n",$row[0]);
			printf("<td>%s</td>\n",$row[1]);
			printf("<td><A href=bunmst.php?ITEM=%s&WSCD=%s>%s</A></td>\n",$item,$row[2],$row[2]);
			printf("<td><A href=bunmst.php?ITEM=%s&WSCD=%s>%s</A></td>\n",$item,$row[2],$row[3]);
			printf("<td>%s</td>\n",$row[4]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("</td>\n");

		if  ($wscd != "")
			{
			printf("<td>\n");
			printf("<table bgcolor = white border>\n");
			printf("<tr>\n");
			printf("<th>WSコード</th>\n");
			printf("<th>親コード</th>\n");
			printf("<th>項目コード</th>\n");
			printf("<th>項目名</th>\n");
			printf("<th>TBF</th>\n");
			printf("</tr>\n");

			$sql = "";
			$sql = $sql . "select smpcd,oyakmkcd,kmkcd,kmknmr,bkfkkbn ";
			$sql = $sql . "from nfkmkmst ";
			$sql = $sql . "where smpcd = '$wscd' ";
			$sql = $sql . "and ukflg = '1' ";
			$sql = $sql . "order by oyakmkcd,kmkcd for read only";
			foreach ($conn->query($sql) as $row)
				{
				printf("<tr>\n");
				printf("<td>%s</td>\n",$row[0]);
				printf("<td>%s</td>\n",$row[1]);
				printf("<td>%s</td>\n",$row[2]);
				printf("<td>%s</td>\n",$row[3]);
				printf("<td>%s</td>\n",$row[4]);
				printf("</tr>\n");
				}
			printf("</table>\n");
			printf("</td>\n");
			}
		}
	}
	else
	{
	echo "Connection failed";
	}

$conn = null;

?>
</td>
</table>

<br clear=all>

<?php
MasterTailOut();
?>

<HR>
</BODY>
</HTML>
