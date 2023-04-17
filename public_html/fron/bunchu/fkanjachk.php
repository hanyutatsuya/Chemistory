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
				array("SSSS0001","SSSS0500","","",""),
				array("SSSS0501","SSSS1000","","",""),
				array("SSSS1001","SSSS1500","","",""),
				array("SSSS1501","SSSS2000","","",""),
				array("SSSS2001","SSSS2500","","",""),
				array("SSSS2501","SSSS3000","","",""),
				array("SSSS3001","SSSS3500","","",""),
				array("SSSS3501","SSSS4000","","",""),
				array("SSSS4001","SSSS4500","","",""),
				array("SSSS4501","SSSS5000","","",""),
				array("SSSS5001","SSSS6000","","",""),
				array("SSSS6001","SSSS7000","","",""),
				array("SSSS7001","SSSS8000","","",""),
				array("SSSS8001","SSSS9000","","",""),
				array("SSSS9001","SSSS9999","","",""),
				array("CCCC9001","CCCC9999","","",""),
				array("MMMM9001","MMMM9999","","",""),
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
		$sql = $sql . "select max(knbnid) from fbncmktbl mk where sriymd = '$sdate' ";
		$sql = $sql . "and knbnid between '$rack1' and '$rack2' for read only";
		$pdst = $conn->prepare($sql);
		$pdst->execute();
		$row = $pdst->fetch(PDO::FETCH_NUM);
		$hani[$i][2] = $row[0];
		$pdst->closeCursor();

		$sql = "";
		$sql = $sql . "select max(mk.knbnid) from nfktbl kn,fbncmktbl mk ";
		$sql = $sql . "where mk.sriymd = '$sdate' and kn.sriymd = '$sdate' ";
		$sql = $sql . "and mk.barcd = kn.barcd and mk.kntkbn = kn.kntkbn ";
		$sql = $sql . "and mk.knbnid between '$rack1' and '$rack2' ";
		$sql = $sql . "and kn.sakhm < kn.kjmckdh for read only";
//		$sql = $sql . "and kn.kjmckid != '0' and kn.kjmckid != ' ' for read only";
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
			$sql = $sql . "select distinct mk.knbnid from nfktbl kn,fbncmktbl mk ";
			$sql = $sql . "where mk.sriymd = '$sdate' and kn.sriymd = '$sdate' ";
			$sql = $sql . "and mk.barcd = kn.barcd and mk.kntkbn = kn.kntkbn ";
			$sql = $sql . "and mk.knbnid between '$rack1' and '$rack2' ";
			$sql = $sql . "and kn.sakhm >= kn.kjmckdh ";
//			$sql = $sql . "and (kn.kjmckid = '0' or kn.kjmckid = ' ')  ";
			$sql = $sql . "order by mk.knbnid for read only";
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
