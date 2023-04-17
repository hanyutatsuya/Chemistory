<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "アッセイラックマップ照会処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_REQUEST['SDATE'];
$rack  = $_REQUEST['RACK'];
$tray  = $_REQUEST['TRAY'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

//printf("<P>\n");
//printf("<center>\n");
//printf("<P>処理日：%s</P>\n",ymd_edit($sdate));
//printf("</center>\n");

printf("<FORM ACTION=\"krackmap.php\" METHOD=GET>\n");
printf("<center>\n");
printf("<TT>処　理　日</TT>\n");
printf("<INPUT TYPE=text NAME=SDATE SIZE=12 MAXLENGTH=8 value=\"%s\">\n",$sdate);
printf("</center>\n");
printf("<BR>\n");
printf("<center>\n");
printf("<TT>ラックＩＤ</TT>\n");
printf("<INPUT TYPE=text NAME=RACK SIZE=12 MAXLENGTH=10 value=\"%s\">\n",$rack);
printf("</center>\n");
printf("<BR>\n");
printf("<center>\n");
printf("<TT>トレイＩＤ</TT>\n");
printf("<INPUT TYPE=text NAME=TRAY SIZE=12 MAXLENGTH=10 value=\"%s\">\n",$tray);
printf("</center>\n");
printf("<BR>\n");
printf("<center>\n");
printf("<BUTTON type=submit name=submit value=\"submit\">検　索</BUTTON>\n");
printf("</center>\n");
printf("</FORM>\n");
printf("</P>\n");
printf("<HR>\n");

if  ($rack != NULL || $tray != NULL)
	{
	$conn = Get_DBConn();
	if  ($conn)
		{
//		ラック本数取得
		$sql = "";
		$sql = $sql . "select it.lckpcnt from fitmcmst it,nfsmpmst ws,fbncjtbl bn "
		$sql = $sql . "where bn.sriymd = '$sdate' ";
		if  ($rack != NULL)
			{
			$sql = $sql . "and bn.aslckid = '$rack' ";
			}
		else
			{
			$sql = $sql . "and bn.astrayid = '$tray' ";
			}
		$sql = $sql . "and ws.smpcd = bn.smpcd and it.itmcd = ws.itmcd fetch first 1 row only for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch();
		$honsu = $row[0];
		$pdst->closeCursor();

		for ($i=0;$i<100;$i++)
			{
			for ($j=0;$j<8;$j++)
				$rackmap[$i][$j] = "";
			}

		$sql = "select bn.aslckid,bn.barcd,kn.ktichkmj,bn.astraypos,bn.aslckhno,bn.smpcd,bn.stid,bn.bnckka ";
		$sql = $sql . "from fbncjtbl bn,nfktbl kn ";
		$sql = $sql . "where bn.sriymd = '$sdate' ";
		if  ($rack != NULL)
			{
			$sql = $sql . "and bn.aslckid = '$rack' ";

			}
		else
			{
			$sql = $sql . "and bn.astrayid = '$tray' ";
			}

		$sql = $sql . "and kn.sriymd = bn.sriymd and kn.barcd = bn.barcd ";
		$sql = $sql . "and kn.kntkbn = bn.kntkbn for read only";

		foreach ($conn->query($sql) as $row)
			{
			if  ($rack != NULL)
				$pos = $row[4] - 1;
			else
				$pos = ($row[3]-1)*$honsu + $row[4] - 1;

			for ($j=0;$j<8;$j++)
				$rackmap[$pos][$j] = $row[$j];
			}
		}
	$conn = NULL;

	printf("<table align=\"center\" border>\n");

	//printf("<tr>\n");
	//for ($i=0;$i<10;$i++) {printf("<th>ラックＩＤ</th>\n");}
	//printf("</tr>\n");

	for ($i=0;$i<10;$i++)
		{
		printf("<tr>\n");
		for ($j=0;$j<5;$j++)
			{
			printf("<td>%02d</td>\n",$j*10+$i+1);
			if  ($rackmap[$i+$j*10][0] == "")
				{
				printf("<td>__________</td>\n");
				printf("<td>___</td>\n");
				}
			else
				{
				printf("<td><A href=../comm/nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
						$sdate,substr($rackmap[$i+$j*10][0],2,9),barcode_edit($rackmap[$i+$j*10][0]));
				printf("<td><A href=../comm/nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
						$sdate,substr($rackmap[$i+$j*10][0],2,9),$rackmap[$i+$j*10][1]);
				}
			}
		printf("</tr>\n");
		}

	printf("</table>\n");
	}

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=merits.php>メリッツ処理一覧に戻る</A></center>\n");
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
