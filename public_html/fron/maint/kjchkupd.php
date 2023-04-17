<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$sdate = $_REQUEST['SDATE'];
$kubun = $_REQUEST['KUBUN'];

if ($kubun == 0)
	{
	$kbn = "L";
	$title = "ラボ受付分検体番号範囲メンテナンス";
	}
else
	{
	$kbn = "U";
	$title = "埼玉受付分検体番号範囲メンテナンス";
	}

NsfrHeadOutput($title);
NsfrLogOut($title);


printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);
printf("<BR>\n");

printf("<FORM ACTION=\"kjchkadd.php\" METHOD=\"POST\">\n");
printf("<center>\n");
printf("万台：<INPUT TYPE=TEXT NAME=MANDAI size=4 maxlength=3>\n");
printf("　開始番号：<INPUT TYPE=TEXT NAME=KENFR  size=5 maxlength=4>\n");
printf("　終了番号：<INPUT TYPE=TEXT NAME=KENTO  size=5 maxlength=4>\n");
printf("</center>\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<INPUT TYPE=hidden NAME=KUBUN VALUE=\"%s\">\n",$kubun);
printf("<BR>\n");
printf("<center><BUTTON NAME=\"submit\" value=\"submit\" type=\"submit\">追加\n");
printf("</BUTTON></center>\n");
printf("</FORM>\n");

printf("<BR>\n");

$conn = Get_DBConn();

if  ($conn)
	{
	$i = 0;
	$sql = "";
	$sql = $sql . "select * from nfknjmmst ";
	$sql = $sql . "where sykmkbn = '$kbn' ";
	$sql = $sql . "order by barcdfr,barcdto for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		$kenno[$i][0] = $row[0];
		$kenno[$i][1] = $row[1];
		$kenno[$i][2] = $row[2];
		$kenno[$i][3] = $row[3];
		$kenno[$i][4] = $row[4];
		$kenno[$i][5] = $row[5];
		$i++;
		}
	}
else
	{
	echo "Connection failed";
	}
$conn = null;

printf("<table align=center bgcolor = white border>\n");
printf("<tr>\n");
printf("<th nowrap>万台</th>\n");
printf("<th nowrap>開始番号</th>\n");
printf("<th nowrap>終了番号</th>\n");
printf("<th nowrap>登録日</th>\n");
printf("<th nowrap>更新日</th>\n");
printf("</tr>\n");

printf("<FORM ACTION=\"kjchkdel.php\" METHOD=\"POST\">\n");
for ($i=0;$i<count($kenno);$i++)
	{
	printf("<tr>\n");
	printf("<td align=right nowrap>%s</td>\n",substr($kenno[$i][1],2,3));
	printf("<td align=right nowrap>%s</td>\n",substr($kenno[$i][1],5,4));
	printf("<td align=right nowrap>%s</td>\n",substr($kenno[$i][2],5,4));
	printf("<td align=right nowrap>%s</td>\n",substr($kenno[$i][3],0,19));
	printf("<td align=right nowrap>%s</td>\n",substr($kenno[$i][4],0,19));
	printf("<td nowrap>\n");
	printf("<BUTTON type=submit name=DELBU[%d] value=\"submit\">削除\n",$i);
	printf("</BUTTON>\n");
	printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
	printf("<INPUT TYPE=hidden NAME=KUBUN VALUE=\"%s\">\n",$kubun);
	printf("<INPUT TYPE=hidden NAME=KENFR[%d] VALUE=\"%s\">\n",$i,$kenno[$i][1]);
	printf("<INPUT TYPE=hidden NAME=KENTO[%d] VALUE=\"%s\">\n",$i,$kenno[$i][2]);
	printf("</td>\n");
	}
printf("</table>\n");
printf("</FORM>\n");
printf("<BR CLEAR=ALL>\n");


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
