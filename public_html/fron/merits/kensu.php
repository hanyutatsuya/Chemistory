<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "検体認識件数照会処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_REQUEST['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$cur = mktime(22,0,0,6,8,2008);
for ($i=0;$i<10;$i++)
	{
	$frtbl[$i] = $cur;
	$totbl[$i] = $cur + 3599;
	$cur += 3600;
	}

//printf("<P>\n");
//printf("<center>\n");
//printf("<P>処理日：%s</P>\n",ymd_edit($sdate));
//printf("</center>\n");

printf("<HR>\n");

$conn = Get_DBConn();
if  ($conn)
	{
	for ($i=0;$i<10;$i++)
		{
		$ftime = date("Y-m-d H:i:s",$frtbl[$i]);
		$ttime = date("Y-m-d H:i:s",$totbl[$i]);
		$sql = "";
		$sql = $sql . "select count(*) from nfktbl ";
		$sql = $sql . "where sriymd = '20080601' ";
		$sql = $sql . "and sskbn = '01' ";
		$sql = $sql . "and devno like '21%' ";
		$sql = $sql . "and sakhm between '$ftime' and '$ttime' ";
		$sql = $sql . "for read only ";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[$i][0] = $row[0];
		$pdst->closeCursor();

		$sql = "";
		$sql = $sql . "select count(*) from nfktbl ";
		$sql = $sql . "where sriymd = '20080601' ";
		$sql = $sql . "and sskbn = '01' ";
		$sql = $sql . "and devno like '22%' ";
		$sql = $sql . "and sakhm between '$ftime' and '$ttime' ";
		$sql = $sql . "for read only ";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[$i][1] = $row[0];
		$pdst->closeCursor();

		$sql = "";
		$sql = $sql . "select count(*) from nfktbl ";
		$sql = $sql . "where sriymd = '20080601' ";
		$sql = $sql . "and sskbn = '01' ";
		$sql = $sql . "and devno like '23%' ";
		$sql = $sql . "and sakhm between '$ftime' and '$ttime' ";
		$sql = $sql . "for read only ";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[$i][2] = $row[0];
		$pdst->closeCursor();

		$sql = "";
		$sql = $sql . "select count(*) from nfktbl ";
		$sql = $sql . "where sriymd = '20080601' ";
		$sql = $sql . "and devno like '9%' ";
		$sql = $sql . "and sakhm between '$ftime' and '$ttime' ";
		$sql = $sql . "for read only ";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[$i][3] = $row[0];
		$pdst->closeCursor();

		$sql = "";
		$sql = $sql . "select count(*) from nfktbl ";
		$sql = $sql . "where sriymd = '20080601' ";
		$sql = $sql . "and devno like '3%' ";
		$sql = $sql . "and sakhm between '$ftime' and '$ttime' ";
		$sql = $sql . "for read only ";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$cnt[$i][4] = $row[0];
		$pdst->closeCursor();

		}
	$conn = NULL;

	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>装置</th>\n");
	for ($i=0;$i<10;$i++)
		{
		printf("<th>%s</th>\n",date("H:i",$frtbl[$i]));
		}
	printf("</tr>\n");

	printf("<tr>\n");

	$soti[0] = "全自動";
	$soti[1] = "半自動";
	$soti[2] = "手動";
	$soti[3] = "用手";
	$soti[4] = "凍結";

	for ($i=0;$i<5;$i++)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$soti[$i]);
		for ($j=0;$j<10;$j++)
			{
			printf("<td>%d</td>\n",$cnt[$j][$i]);
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
