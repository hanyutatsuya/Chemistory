<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("仕分け種類チェック");
NsfrLogOut("仕分け種類チェック");
?>

<BODY background="../img/mstback.gif">
<?php
NsfrTimeStamp();
?>
<center><h2>仕分け種類チェック</h2></center>

<?php
$wsflg = trim($_GET['WS999']);
$sscd = trim($_GET['SSCD']);
$wscd = trim($_GET['WSCD']);
?>

<P>
<FORM ACTION="chk_ss.php" METHOD="GET">
<?php
if  ($wsflg == "")
	printf("<INPUT TYPE=checkbox NAME=WS999 value=1>\n");
else
	printf("<INPUT TYPE=checkbox NAME=WS999 value=1 checked>\n");

printf("WS998,999を含めない　\n");
printf("<BUTTON name=submit value=submit type=submit>設定\n");
printf("</BUTTON>\n");
if  ($sscd != "")
	printf("<INPUT TYPE=hidden name=SSCD value=%s\n",$sscd);
if  ($wscd != "")
	printf("<INPUT TYPE=hidden name=WSCD value=%s\n",$wscd);
?>

</FORM>
</P>

<table align = left border=0>
<tr valign=top>
<td>
<table bgcolor = white border>
<tr>
<th>区分</th>
<th>仕分け種類名</th>
</tr>

<?php

$conn = Get_DBConn();

if  ($conn)
	{
	$sql = "select sskbn,zrnmr from nfssmst where ukflg = '1' order by sskbn for read only";
	foreach ($conn->query($sql) as $row)
		{
		printf("<tr>\n");
		printf("<td><A href=chk_ss.php?WS999=%s&SSCD=%s>%s</A></td>\n",$wsflg,$row[0],$row[0]);
		printf("<td><A href=chk_ss.php?WS999=%s&SSCD=%s>%s</A></td>\n",$wsflg,$row[0],$row[1]);
		printf("</tr>\n");
		}
	printf("</table>\n");

	if  ($sscd != "")
		{
		printf("<td>\n");
		printf("<table bgcolor = white border>\n");
		printf("<tr>\n");
		printf("<th>仕分け</th>\n");
		printf("<th>ＷＳコード</th>\n");
		printf("<th>ＷＳ名</th>\n");
		printf("<th>サテライト</th>\n");
		printf("<th>分注区分</th>\n");
		printf("<th>Ｓ凍結Ｆ</th>\n");
		printf("</tr>\n");

		$sql = "";
		$sql = $sql . "select distinct ws.smpcd,ws.smpcdnm,ws.stid,ws.bckbn,ws.supuruztkflg ";
		$sql = $sql . "from nfsmpmst ws,nfkmkmst km ";
		$sql = $sql . "where km.sskbn = '$sscd' ";
		$sql = $sql . "and km.ukflg = '1' ";
		$sql = $sql . "and ws.smpcd = km.smpcd ";
		if  ($wsflg != "")
			$sql = $sql . "and ws.smpcd not in ('0998','0999') ";
		$sql = $sql . "and ws.ukflg = '1' ";
		$sql = $sql . "order by ws.smpcd for read only";
		foreach ($conn->query($sql) as $row)
			{
			printf("<tr>\n");
			printf("<td>%s</td>\n",$sscd);
			printf("<td><A href=chk_ss.php?WS999=%s&SSCD=%s&WSCD=%s>%s</A></td>\n",$wsflg,$sscd,$row[0],$row[0]);
			printf("<td><A href=chk_ss.php?WS999=%s&SSCD=%s&WSCD=%s>%s</A></td>\n",$wsflg,$sscd,$row[0],$row[1]);
			printf("<td>%s</td>\n",$row[2]);
			printf("<td>%s</td>\n",$row[3]);
			printf("</tr>\n");
			}
		printf("</table>\n");
		printf("</td>\n");


		if  ($wscd != "")
			{
			printf("<td>\n");
			printf("<table bgcolor = white border>\n");
			printf("<tr>\n");
			printf("<th>WSコード</th>\n");
			printf("<th>親コード</th>\n");
			printf("<th>項目コード</th>\n");
			printf("<th>項目名</th>\n");
			printf("<th>TBF</th>\n");
			printf("<th>仕分け</th>\n");
			printf("<th>分注区分</th>\n");
			printf("</tr>\n");

			$sql = "";
			$sql = $sql . "select smpcd,oyakmkcd,kmkcd,kmknmr,bkfkkbn,sskbn,bckbn ";
			$sql = $sql . "from nfkmkmst ";
			$sql = $sql . "where smpcd = '$wscd' ";
			$sql = $sql . "and ukflg = '1' ";
			$sql = $sql . "order by oyakmkcd,kmkcd for read only";
			foreach ($conn->query($sql) as $row)
				{
				printf("<tr>\n");
				printf("<td>%s</td>\n",$row[0]);
				printf("<td>%s</td>\n",$row[1]);
				printf("<td>%s</td>\n",$row[2]);
				printf("<td>%s</td>\n",$row[3]);
				printf("<td>%s</td>\n",$row[4]);
				if  ($row[5] != $sscd)
					printf("<td bgcolor=red>%s</td>\n",$row[5]);
				else
					printf("<td>%s</td>\n",$row[5]);
				printf("<td>%s</td>\n",$row[6]);
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
require_once("../comm/mstchk_tail.inc");
?>

<HR>
</BODY>
</HTML>
