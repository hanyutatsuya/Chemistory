<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("パキパキパターンマスタ");
NsfrLogOut("パキパキパターンマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>パキパキパターンマスタ</h2></center>

<?php
$item = trim($_GET['ITEM']);
$saki = trim($_GET['SAKI']);
?>

<table align = left border=0>
<tr valign=top>
<td>
<table bgcolor = white border>
<tr>
<th>RACK</th>
<th>表示</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "";
	$sql = $sql . "select itmcd,itmnm,zrlcknm ";
	$sql = $sql . "from fitmcmst ";
	$sql = $sql . "where itmcd between '61' and '79' and ukflg = '1' ";
	$sql = $sql . "order by itmcd for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td><A href=zpatarn.php?SDATE=%s&ITEM=%s>%s</A></td>\n",$sdate,$row[0],substr($row[1],0,4));
		printf("<td align=center><A href=zpatarn.php?SDATE=%s&ITEM=%s>%s</A></td>\n",$sdate,$row[0],$row[2]);
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
		printf("<th>WSCD</th>\n");
		printf("<th>ＷＳ名</th>\n");
		printf("</tr>\n");

		$sql = "";
		$sql = $sql . "select it.itmnm,ws.swkskid,ws.smpcd,ws.smpcdnm ";
		$sql = $sql . "from nfsmpmst ws,fitmcmst it ";
		$sql = $sql . "where it.itmcd = '$item' ";
		$sql = $sql . "and it.ukflg = '1' ";
		$sql = $sql . "and ws.itmcd = it.itmcd ";
		$sql = $sql . "and ws.ukflg = '1' ";
		$sql = $sql . "order by ws.swkskid,ws.smpcd for read only";
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			printf("<tr>\n");
			printf("<td>%s</td>\n",substr($row[0],0,4));
			printf("<td align=center>%s</td>\n",$row[1]);
			printf("<td><A href=zpatarn.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,$row[1],$row[2]);
			printf("<td><A href=zpatarn.php?SDATE=%s&ITEM=%s&SAKI=%s>%s</A></td>\n",$sdate,$item,$row[1],$row[3]);
			printf("</tr>\n");
			$rack = substr(trim($row[0]),0,4);
			}
		printf("</table>\n");
		printf("</td>\n");

		if  ($saki != "")
			{
			$sql = "";
			$sql = $sql . "select swkskpos,krnkflg ";
			$sql = $sql . "from fsiptmst ";
			$sql = $sql . "where itmcd = '$item' ";
			$sql = $sql . "and swkskid = '$saki' ";
			$sql = $sql . "order by swkskpos for read only";
			foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
				{
				$i = (int)$row[0];
				$pat[$i] = $row[1];
				}

			printf("<td>\n");
			printf("<table bgcolor = white border>\n");
			printf("<tr>\n");
			printf("<th>%s-%s</th>\n",$rack,$saki);
			printf("</tr>\n");
			printf("<tr>\n");
			printf("<th></th>\n");
			printf("<th>50</th>\n");
			printf("<th>40</th>\n");
			printf("<th>30</th>\n");
			printf("<th>20</th>\n");
			printf("<th>10</th>\n");
			printf("</tr>\n");

			for ($j=10;$j>0;$j--)
				{
				printf("<tr>\n");
				printf("<td align=center>%d</td>\n",$j);
				for ($i=5;$i>0;$i--)
					{
					if ($pat[($i-1)*10+$j] == '1')
						$mark = "＊";
					else
						$mark = "　";
					printf("<td align=center>%s</td>\n",$mark);
					}
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
