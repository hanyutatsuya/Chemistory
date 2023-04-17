<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("患者名チェック未出力ラック一覧");
NsfrLogOut("患者名チェック未出力ラック一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>患者名チェック未出力ラック一覧</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>ラックＩＤ</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct lckid from nfktbl ";
	$sql = $sql . "where sriymd = '$sdate' ";
	$sql = $sql . "and substr(lckid,1,1) in ('T','K','V','Q','P','W') ";
	$sql = $sql . "and  (sakhm >= kjmckdh or kjmckdh is null) ";
	$sql = $sql . "order by lckid for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("</tr>\n");
		}

	$sql = "";
	$sql = $sql . "select distinct mk.knbnid from nfktbl kn,fbncmktbl mk ";
	$sql = $sql . "where mk.sriymd = '$sdate' and kn.sriymd = '$sdate' ";
	$sql = $sql . "and mk.barcd = kn.barcd and mk.kntkbn = kn.kntkbn ";
	$sql = $sql . "and mk.knbnid != ' ' ";
	$sql = $sql . "and kn.sakhm >= kn.kjmckdh ";
	$sql = $sql . "order by mk.knbnid for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",trim($row[0]));
		printf("</tr>\n");
		}

	printf("</table>\n");
	}
else
	{
	printf("Connection failed");
	}
$conn = null;

?>

<HR>

<?php
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
