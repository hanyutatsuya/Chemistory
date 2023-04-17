<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "検体ラックマップ照会処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_REQUEST['SDATE'];
$rack  = $_REQUEST['RACK'];

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
printf("<BUTTON type=submit name=submit value=\"submit\">検　索</BUTTON>\n");
printf("</center>\n");
printf("</FORM>\n");
printf("</P>\n");
printf("<HR>\n");

if  ($rack != NULL)
	{
	$conn = Get_DBConn();
	if  ($conn)
		{
		for ($i=0;$i<50;$i++) {$rackmap[$i][0] = "";$rackmap[$i][1] = "";}
		if  (substr($rack,0,1) != "S")
			{
			$sql = "select barcd,ktichkmj,lckpos from nfktbl where sriymd = '$sdate' and lckid = '$rack' for read only";
			foreach ($conn->query($sql) as $row)
				{
				$rackmap[$row[2]-1][0] = $row[0];
				$rackmap[$row[2]-1][1] = $row[1];
				}
			}
		else
			{
			$sql = "select mk.barcd,kn.ktichkmj,mk.traypos,mk.lckpos from fbncmktbl mk,nfktbl kn ";
			$sql = $sql . "where mk.sriymd = '$sdate' and mk.knbnid = '$rack' ";
			$sql = $sql . "and kn.sriymd = mk.sriymd and kn.barcd = mk.barcd ";
			$sql = $sql . "and kn.kntkbn = mk.kntkbn for read only";
			foreach ($conn->query($sql) as $row)
				{
//				printf("[%d][%s][%s][%d][%d]<BR>\n",(($row[2]-1) % 5)*10 + $row[3] - 1,$row[0],$row[1],$row[2],$row[3]);
				$rackmap[(($row[2]-1) % 5)*10 + $row[3] - 1][0] = $row[0];
				$rackmap[(($row[2]-1) % 5)*10 + $row[3] - 1][1] = $row[1];
				}
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
