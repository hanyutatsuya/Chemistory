<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("パキパキ→ＲＦＩＤ照会");
NsfrLogOut("パキパキ→ＲＦＩＤ照会");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>パキパキ→ＲＦＩＤ照会</h2></center>

<?php
$sdate = trim($_REQUEST['SDATE']);
$item = trim($_REQUEST['ITEM']);
$rackid = trim($_REQUEST['RACKID']);

printf("<center><P>処理日：%s</P></center>\n",$sdate);

?>

<table align = left border=0>
<tr valign=top>
<td>
<table bgcolor = white border>
<tr>
<th>RACK</th>
<th>表示</th>
<th>件数</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn)
	{
	$paki_cnt = 0;
	$sql = "";
	$sql = $sql . "select itmcd,itmnm,zrlcknm ";
	$sql = $sql . "from fitmcmst ";
	$sql = $sql . "where itmcd between '61' and '79' and ukflg = '1' ";
	$sql = $sql . "order by itmcd for read only";

	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$paki[$paki_cnt][0] = $row[0];
		$paki[$paki_cnt][1] = $row[1];
		$paki[$paki_cnt][2] = $row[2];
		$paki[$paki_cnt][3] = 0;
		$paki_cnt++;
		}

	for ($i=0;$i<$paki_cnt;$i++)
		{
		printf("<tr>\n");

		$pakicd = $paki[$i][0];
		$sql = "";
		$sql = $sql . "select count(distinct rckseq) ";
		$sql = $sql . "from fpkptbl ";
		$sql = $sql . "where sriymd = '$sdate' ";
		$sql = $sql . "and itmcd = '$pakicd' ";
		$sql = $sql . "for read only";

		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$paki[$i][3] = $row[0];
		$pdst->closeCursor();

//		printf("<td>%s</td>\n",$row[0]);
		printf("<td><A href=rfid1ran.php?SDATE=%s&ITEM=%s>%s</A></td>\n",
				$sdate,$paki[$i][0],substr($paki[$i][1],0,4));
		printf("<td align=center><A href=rfid1ran.php?SDATE=%s&ITEM=%s>%s</A></td>\n",
				$sdate,$paki[$i][0],$paki[$i][2]);
		printf("<td align = right>%d</td>\n",$paki[$i][3]);
		printf("</tr>\n");
		}

	printf("</table>\n");

	if  ($item != "")
		{
		printf("<td>\n");
		printf("<table bgcolor = white border>\n");
		printf("<tr>\n");
		printf("<th>RACK</th>\n");
		printf("<th>記号</th>\n");
		printf("<th>RFID</th>\n");
		printf("</tr>\n");

		$ws_cnt = 0;
		$sql = "";
		$sql = $sql . "select distinct it.itmnm,pk.rckseq,it.zrlcknm,rf.rfid ";
		$sql = $sql . "from fpkptbl pk,fitmcmst it,frlpjtbl rf ";
		$sql = $sql . "where pk.sriymd = '$sdate' ";
		$sql = $sql . "and pk.itmcd = '$item' ";
		$sql = $sql . "and it.itmcd = pk.itmcd ";
		$sql = $sql . "and rf.sriymd = pk.sriymd ";
		$sql = $sql . "and rf.zrlcknm = it.zrlcknm ";
		$sql = $sql . "and rf.rckseq = pk.rckseq ";
		$sql = $sql . "order by pk.rckseq for read only";
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			$ws[$ws_cnt][0] = $row[0];
			$ws[$ws_cnt][1] = $row[1];
			$ws[$ws_cnt][2] = $row[2];
			$ws[$ws_cnt][3] = $row[3];
			$ws_cnt++;
			}

		for ($i=0;$i<$ws_cnt;$i++)
			{
			printf("<tr>\n");
			printf("<td><A href=rfid1ran.php?SDATE=%s&ITEM=%s&RACKID=%s%04d>%s%04d</A></td>\n",
					$sdate,$item,substr($ws[$i][0],0,4),$ws[$i][1],substr($ws[$i][0],0,4),$ws[$i][1]);
			printf("<td align=center>%s</td>\n",$ws[$i][2]);
			printf("<td><A href=rfid1ran.php?SDATE=%s&ITEM=%s&RACKID=%s%04d>%s</A></td>\n",
					$sdate,$item,substr($ws[$i][0],0,4),$ws[$i][1],$ws[$i][3]);
			printf("</tr>\n");
			$rack = substr(trim($ws[$i][0]),0,4);
			}
		printf("</table>\n");
		printf("</td>\n");

		if  ($rackid != "")
			{
			printf("<td>\n");
			printf("<table bgcolor = white border>\n");
			printf("<tr>\n");
			printf("<th>ARACKID</th>\n");
			printf("<th>POS</th>\n");
			printf("<th>検体No</th>\n");
			printf("<th>CH</th>\n");
			printf("<th>WSCD</th>\n");
			printf("<th>分注量</th>\n");
			printf("<th>サテライト</th>\n");
			printf("<th>分注No</th>\n");
			printf("<th>仕分けNo</th>\n");
			printf("<th>DEV-MOD</th>\n");
			printf("</tr>\n");

			$sql = "";
			$sql = $sql . "select j.aslckid,j.aslckhno,j.barcd,p.chkchr,";
			$sql = $sql . "j.smpcd,b.bcryo,j.stid,p.itmseq,p.ssseq,j.devno,j.bcmodno ";
			$sql = $sql . "from fbncjtbl j,fpkptbl p,fbnctbl b ";
			$sql = $sql . "where j.sriymd = '$sdate' ";
			$sql = $sql . "and j.aslckid = '$rackid' ";
			$sql = $sql . "and p.sriymd = j.sriymd ";
			$sql = $sql . "and p.barcd = j.barcd ";
			$sql = $sql . "and p.kntkbn = j.kntkbn ";
			$sql = $sql . "and p.smpcd = j.smpcd ";
			$sql = $sql . "and b.sriymd = j.sriymd ";
			$sql = $sql . "and b.barcd = j.barcd ";
			$sql = $sql . "and b.kntkbn = j.kntkbn ";
			$sql = $sql . "and b.smpcd = j.smpcd ";
			$sql = $sql . "order by j.aslckhno for read only";
			foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
				{
				printf("<tr>\n");
				printf("<td>%s</td>\n",$row[0]);
				printf("<td align=right>%d</td>\n",$row[1]);
				printf("<td>%s</td>\n",barcode_edit($row[2]));
				printf("<td>%s</td>\n",$row[3]);
				printf("<td align=right>%s</td>\n",$row[4]);
				printf("<td align=right>%d</td>\n",$row[5]);
				printf("<td>%s</td>\n",$row[6]);
				printf("<td align=right>%d</td>\n",$row[7]);
				printf("<td align=right>%d</td>\n",$row[8]);
				printf("<td>%s-%s</td>\n",$row[9],$row[10]);
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
NsfrBackPage();

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=bunchu.php?SDATE=%s>フロンティアシステム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>

</BODY>
</HTML>
