<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("依頼件数照会",1800);
NsfrLogOut("依頼件数照会");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>依頼件数照会</h2></center>

<?php
$sdate = $_GET[SDATE];
printf("<center><h2>処理日：%s</h2></center>\n",$sdate);

$conn = Get_DBConn();
if  ($conn)
	{

	$sql = "select count(*) from nfztbl where utkymd = '$sdate' for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_z = $row[0];
		break;
		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_k = $row[0];
		break;
		}
	$sql = "select count(*) from nfitbl where sriymd = '$sdate' for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_i = $row[0];
		break;
		}
//	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and swkkbn in (' ','01') for read only";
//	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
//		{
//		$cnt_s = $row[0];
//		break;
//		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and brkbn = '06' and swkkbn in (' ','01') for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_s1 = $row[0];
		break;
		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and brkbn = '09' and swkkbn in (' ','01') for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_s2 = $row[0];
		break;
		}
	$sql = "select count(*) from nkktbl where sriymd = '$sdate' and sskbn = '01' and brkbn != '06' and brkbn != '09' and swkkbn in (' ','01') for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$cnt_s3 = $row[0];
		break;
		}
	}
else
	{
	echo "Connection failed";
	}
$conn = null;
?>

<?php
printf("<table align=center bgcolor=white border>\n");

printf("<tr>\n");
printf("<th></th>\n");
printf("<th>件数</th>\n");
printf("</tr>\n");

printf("<tr>\n");
printf("<td>患者情報</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_z));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>仮検体</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_k));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>依頼項目</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_i));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>冷蔵血清検体</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s1+$cnt_s2+$cnt_s3));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>冷蔵血清検体(翌日１回目)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s1));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>冷蔵血清検体(翌日２回目)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s2));
printf("</tr>\n");

printf("<tr>\n");
printf("<td>冷蔵血清検体(通常分)</td>\n");
printf("<td align=right>%s</td>\n",number_format($cnt_s3));
printf("</tr>\n");

printf("</table>\n");
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
<DIV align=right>
この画面は３０分ごとに自動更新されます
</DIV>
</BODY>
</HTML>
