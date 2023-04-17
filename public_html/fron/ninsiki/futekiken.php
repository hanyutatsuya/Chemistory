<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("不適合登録もれ検体一覧");
NsfrLogOut("不適合登録もれ検体一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>不適合登録もれ検体一覧</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");

	printf("<tr>\n");
	printf("<th>検体ナンバー</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select distinct m.barcd from fbncmktbl m ";
	$sql = $sql . "where m.sriymd = '$sdate' ";
	$sql = $sql . "and char(m.knbnid,1) not in ('V','S') ";
	$sql = $sql . "and exists ( select * from fbncmktbl f ";
	$sql = $sql . "where f.sriymd = m.sriymd ";
	$sql = $sql . "and char(f.barcd,9) = char(m.barcd,9) ";
	$sql = $sql . "and f.bcngcd = '6') ";
	$sql = $sql . "for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
//		printf("<td>%s</td>\n",barcode_edit(trim($row[0])));
		printf("<td><A href=../comm/nsfrshokai.php?SDATE=%s&BARCD=%s>%s</A></td>\n",
					$sdate,substr($row[0],2,9),barcode_edit(trim($row[0])));

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
