<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("凍結検体ラック照会");
NsfrLogOut("凍結検体ラック照会");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>凍結検体ラック照会</h2></center>

<?php
$sdate = $_GET['SDATE'];
$type  = $_GET['TYPE'];

$conn = Get_DBConn();

if  ($conn)
	{
	printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

	$sql = "select distinct lckid from nfktbl where sriymd = '$sdate' ";
	switch ($type)
		{
		case 0:
			$rack = "EEEE";
			$sql = $sql . "and  char(lckid,4) in ('EEEE','MMBB','CCBB') ";
			break;
		case 1:
			$rack = "KKKK";
			$sql = $sql . "and  lckid like 'KKKK%' ";
			break;
		case 2:
			$sql = $sql . "and  lckid between 'TTTT0001' and 'TTTT7999' ";
			$rack = "TTTT";
			break;
		case 3:
			$sql = $sql . "and  lckid like 'TTTT9%' ";
			$rack = "HCV1";
			break;
		case 4:
			$sql = $sql . "and  lckid like 'TTTT8%' ";
			break;
		case 5:
		default:
			$sql = $sql . "and  (lckid between 'VVVV5001' and 'VVVV8999' or ";
			$sql = $sql .  "     lckid between 'VVVV9501' and 'VVVV9999' or ";
			$sql = $sql . "      char(lckid,4) in ('PPPP','QQQQ','WWWW') ) ";
			$rack = "VVVV";
			break;
		default:
			$rack = "";
			break;
		}

	$sql = $sql . " order by lckid for read only";
	$ix = 0;$iy = 0;
	if  ($rack != "")
		{
		foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
			{
			$rackid[$ix][$iy] = $row[0];
			$iy ++;
			if  ($iy > 10)
				{
				$iy = 0;
				$ix ++;
				}
			}
		}
	}
else
	{
	echo "Connection failed";
	}
$conn = null;


if  ($ix == 0 && $iy == 0)
	{
	printf("<center><h2>凍結検体の認識が行われていません</h2></center>\n");
	}
else
	{
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	for ($i=0;$i<10;$i++) {printf("<th>ラックＩＤ</th>\n");}
	printf("</tr>\n");

	for ($i=0;$i<=$ix;$i++)
		{
		printf("<tr>\n");
		for ($j=0;$j<10;$j++)
			{
			if  ($rackid[$i][$j] == "")
				{
				printf("<td>__________</td>\n");
				}
			else
				{
				printf("<td><A href=tkmap.php?SDATE=%s&TYPE=%d&RACK=%s>%8.8s</A></td>\n",
						$sdate,$type,$rackid[$i][$j],$rackid[$i][$j]);
				}
			}
		printf("</tr>\n");
		}

	printf("</table>\n");
	}

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=tkhonsu.php?SDATE=%s>凍結検体本数照会に戻る</A></center>\n",$sdate);
printf("</P>\n");
printf("<P>\n");
printf("<center><A href=ninsiki.php?SDATE=%s>検体認識システム照会処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");
?>
<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
