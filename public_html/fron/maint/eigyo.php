<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "営業所区分メンテナンス";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_GET['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<FORM ACTION=\"eigyoback.php\" METHOD=\"POST\">\n");
printf("<P>\n");
printf("<center>初期設定に戻す</center>\n");
printf("<BR>\n");
printf("<center><BUTTON type=submit name=submit value=\"submit\">初 期 設 定\n");
printf("</BUTTON></center>\n");
printf("</P>\n");
printf("</FORM>\n");


$conn = Get_DBConn();

if  ($conn)
	{
	printf("<P>\n");
	printf("<FORM ACTION=\"eigyoupd.php\" METHOD=\"POST\">\n");
	printf("<table align=center bgcolor = white border>\n");
	printf("<tr>\n");
	printf("<th nowrap>営業所コード</th>\n");
	printf("<th nowrap>営業所名</th>\n");
	printf("<th nowrap>報告区分</th>\n");
	printf("<th nowrap>初期値</th>\n");
	printf("<th nowrap>作成時刻</th>\n");
	printf("<th nowrap>更新時刻</th>\n");
	printf("<th nowrap>作業者ＩＤ</th>\n");
	printf("</tr>\n");

	$sql = "";
	$sql = $sql . "select * ";
	$sql = $sql . "from nfegkmst ";
	$sql = $sql . "order by ecd for read only";
	$i=0;
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td nowrap>%s</td>\n",$row[0]);
		printf("<td nowrap>%s</td>\n",$row[1]);
		if  (strcmp($row[2],"1") == 0)
			{
			$kbn[0] = "selected";
			$kbn[1] = "";
			$kbn[2] = "";
			}
		if  (strcmp($row[2],"2") == 0)
			{
			$kbn[0] = "";
			$kbn[1] = "selected";
			$kbn[2] = "";
			}
		if  (strcmp($row[2],"9") == 0)
			{
			$kbn[0] = "";
			$kbn[1] = "";
			$kbn[2] = "selected";
			}
		printf("<td nowrap>\n");
		printf("<SELECT NAME=EKBN[$i]>\n");
		printf("<OPTION value=1 %s>１回目\n",$kbn[0]);
		printf("<OPTION value=2 %s>２回目\n",$kbn[1]);
		printf("<OPTION value=9 %s>通常分\n",$kbn[2]);
		printf("</SELECT>\n");
		printf("<INPUT TYPE=hidden NAME=ECD[%d] VALUE=\"%s\">\n",$i,$row[0]);
		printf("<INPUT TYPE=hidden NAME=EGSNM[%d] VALUE=\"%s\">\n",$i,$row[1]);
		printf(" <BUTTON type=submit name=UPDBU[%d] value=\"submit\">変更\n",$i);
		printf("</BUTTON>\n");
		printf("</td>\n");

		if  (strcmp($row[3],"1") == 0)
			{
			$skbn[0] = "selected";
			$skbn[1] = "";
			$skbn[2] = "";
			}
		if  (strcmp($row[3],"2") == 0)
			{
			$skbn[0] = "";
			$skbn[1] = "selected";
			$skbn[2] = "";
			}
		if  (strcmp($row[3],"9") == 0)
			{
			$skbn[0] = "";
			$skbn[1] = "";
			$skbn[2] = "selected";
			}

		printf("<td");
		if ($row[2] != $row[3])
			printf(" bgcolor=cyan");
		printf(" nowrap>\n");
		printf("<SELECT NAME=SEKBN[$i]>\n");
		printf("<OPTION value=1 %s>１回目\n",$skbn[0]);
		printf("<OPTION value=2 %s>２回目\n",$skbn[1]);
		printf("<OPTION value=9 %s>通常分\n",$skbn[2]);
		printf("</SELECT>\n");
//		printf("<INPUT TYPE=hidden NAME=ECD[%d] VALUE=\"%s\">\n",$i,$row[0]);
//		printf("<INPUT TYPE=hidden NAME=EGSNM[%d] VALUE=\"%s\">\n",$i,$row[1]);
		printf(" <BUTTON type=submit name=SUPDBU[%d] value=\"submit\">変更\n",$i);
		printf("</BUTTON>\n");
		printf("</td>\n");

		printf("<td nowrap>%s</td>\n",substr($row[4],0,19));
		printf("<td nowrap>%s</td>\n",substr($row[5],0,19));
		printf("<td nowrap>%s</td>\n",$row[6]);
		printf("</tr>\n");
		$i++;
		}
	printf("</table>\n");
	printf("</FORM>\n");
	printf("<P>\n");
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<BR CLEAR=ALL>\n");
printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=maint.php?SDATE=%s>メンテナンス処理一覧に戻る</A></center>\n",$sdate);
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>
