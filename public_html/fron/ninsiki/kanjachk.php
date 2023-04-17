<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("患者名チェックリスト出力確認");
NsfrLogOut("患者名チェックリスト出力確認");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>患者名チェックリスト出力確認</h2></center>

<?php
$sdate = $_GET['SDATE'];

$hani = array(
				array("TTTT0001","TTTT0200","","",""),
				array("TTTT0201","TTTT0500","","",""),
				array("TTTT0501","TTTT1000","","",""),
				array("TTTT1001","TTTT8000","","",""),
				array("TTTT8001","TTTT9000","","",""),
				array("TTTT9001","TTTT9999","","",""),
				array("KKKK0001","KKKK0200","","",""),
				array("KKKK0201","KKKK0500","","",""),
				array("KKKK0501","KKKK1000","","",""),
				array("KKKK1001","KKKK9999","","",""),
				array("PPPP0001","PPPP9999","","",""),
				array("QQQQ0001","QQQQ9999","","",""),
				array("WWWW0001","WWWW9999","","",""),
				array("VVVV0001","VVVV1000","","",""),
				array("VVVV1001","VVVV2000","","",""),
				array("VVVV2001","VVVV3000","","",""),
				array("VVVV3001","VVVV4000","","",""),
				array("VVVV4001","VVVV5000","","",""),
				array("VVVV5001","VVVV6000","","",""),
				array("VVVV6001","VVVV7000","","",""),
				array("VVVV7001","VVVV7300","","",""),
				array("VVVV7301","VVVV7500","","",""),
				array("VVVV7501","VVVV8000","","",""),
				array("VVVV8001","VVVV8300","","",""),
				array("VVVV8301","VVVV8400","","",""),
				array("VVVV8401","VVVV8500","","",""),
				array("VVVV8501","VVVV9000","","",""),
				array("VVVV9001","VVVV9999","","",""),
			);

$ix = count($hani);

$conn = Get_DBConn();

if  ($conn)
	{
	printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

	for ($i=0;$i<$ix;$i++)
		{
		$rack1 = $hani[$i][0];
		$rack2 = $hani[$i][1];
		$sql = "";
		$sql = $sql . "select max(lckid) from nfktbl where sriymd = '$sdate' ";
		$sql = $sql . "and lckid between '$rack1' and '$rack2' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$hani[$i][2] = $row[0];
		$pdst->closeCursor();

		$sql = "";
		$sql = $sql . "select max(lckid) from nfktbl ";
		$sql = $sql . "where sriymd = '$sdate' ";
		$sql = $sql . "and lckid between '$rack1' and '$rack2' ";
		$sql = $sql . "and (sakhm < kjmckdh and kjmckdh is not null) for read only";
//		$sql = $sql . "and (sakhm < kjmckdh or kjmckdh is not null) for read only";
//		$sql = $sql . "and kjmckid != '0' and kjmckid != ' ' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$hani[$i][3] = $row[0];
		$pdst->closeCursor();

		$hani[$i][4] = "";
		if  (trim($hani[$i][2]) != "" && trim($hani[$i][3]) != "")
			{
			$rack1 = $hani[$i][0];
			$rack2 = $hani[$i][3];
			$sql = "";
			$sql = $sql . "select distinct lckid from nfktbl ";
			$sql = $sql . "where sriymd = '$sdate' ";
			$sql = $sql . "and lckid between '$rack1' and '$rack2' ";
			$sql = $sql . "and  (sakhm >= kjmckdh or kjmckdh is null) order by lckid for read only";
//			$sql = $sql . "and (kjmckid = '0' or kjmckid = ' ') order by lckid for read only";
			foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
				{
				$hani[$i][4] = $hani[$i][4] . trim($row[0]) . ",";
				}
			}
		}
	}
else
	{
	echo "Connection failed";
	}

$conn = null;

printf("<table align=\"center\" border>\n");

printf("<tr>\n");
printf("<th nowrap>ラック範囲</th>\n");
printf("<th nowrap>登録済み</th>\n");
printf("<th nowrap>出力済み</th>\n");
printf("<th nowrap align=left>出力もれラック</th>\n");
printf("</tr>\n");

for ($i=0;$i<$ix;$i++)
	{
	printf("<tr>\n");
	printf("<td nowrap");
	if  (strcmp($hani[$i][2],$hani[$i][3]) == 0 && $hani[$i][3] != "" && $hani[$i][4] == "")
		printf(" bgcolor=skyblue");
	if  ((strcmp($hani[$i][2],$hani[$i][3]) != 0 && $hani[$i][2] != "") || $hani[$i][4] != "")
		printf(" bgcolor=pink");
	printf("><TT><BIG>%s ～ %s</BIG></TT></td>\n",$hani[$i][0],$hani[$i][1]);
	printf("<td nowrap");
	if  (strcmp($hani[$i][2],$hani[$i][3]) == 0 && $hani[$i][3] != "" && $hani[$i][4] == "")
		printf(" bgcolor=skyblue");
	if  ((strcmp($hani[$i][2],$hani[$i][3]) != 0 && $hani[$i][2] != "") || $hani[$i][4] != "")
		printf(" bgcolor=pink");
	printf("><TT><BIG>%s</BIG></TT></td>\n",$hani[$i][2]);
	printf("<td nowrap");
	if  (strcmp($hani[$i][2],$hani[$i][3]) == 0 && $hani[$i][3] != "" && $hani[$i][4] == "")
		printf(" bgcolor=skyblue");
	if  ((strcmp($hani[$i][2],$hani[$i][3]) != 0 && $hani[$i][2] != "") || $hani[$i][4] != "")
		printf(" bgcolor=pink");
	printf("><TT><BIG>%s</BIG></TT></td>\n",$hani[$i][3]);
	printf("<td nowrap><TT><BIG>%s</BIG></TT></td>\n",$hani[$i][4]);
	printf("</tr>\n");
	}
printf("</table>\n");

printf("<HR>\n");
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
