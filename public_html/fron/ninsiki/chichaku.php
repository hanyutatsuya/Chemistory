<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");
NsfrHeadOutput("遅着検体照会");
NsfrLogOut("遅着検体照会");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>遅着検体照会</h2></center>

<?php
$sdate = $_REQUEST[SDATE];
$send1 = $_REQUEST['SEND1'];

$updflg = 0;
if  (!empty($send1))
	{
	$msg = "遅着登録検体一覧リスト";
	$app = "/home/nsfr/bin/lst_chichaku.php $sdate";
	$updflg = 1;
	}

if ($updflg != 0)
	{
	$sret = shell_exec($app);
	printf("<P><center>\n");
	printf("%sを出力しました。\n",$msg);
	printf("</center></P>\n");
	printf("<HR>\n");
	}

printf("<h2>\n");
printf("<center>処理日：%s</center>\n",$sdate);
printf("<DIV align=right>\n");
printf("<FORM ACTION=\"chichaku.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<BUTTON type=submit name=SEND1 value=\"submit\">印　刷\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</DIV>\n");
printf("</h2>\n");

$conn = Get_DBConn();
if  ($conn)
	{
	printf("<table align=center bgcolor=white border>\n");
	printf("<tr>\n");
	printf("<th>処理日</th>\n");
	printf("<th>検体番号</th>\n");
	printf("<th>コメント</th>\n");
	printf("<th>保管場所</th>\n");
	printf("</tr>\n");

	$del = array(",","、","､","，","　"," ",";",":","/");

	$sql = "select distinct sriymd,char(kntno,9),freecmt  from nccktbl where sriymd = '$sdate' order by char(kntno,9) for read only";
	foreach ($conn->query($sql,PDO::FETCH_NUM) as $row)
		{
		printf("<tr>\n");
		printf("<td>%s</td>\n",$row[0]);
		printf("<td>%s</td>\n",ino_edit($row[1]));

		$len = mb_strlen($row[2]);
		$idx = 0;
		$pos = 0;
		for ($i=0;$i<count($del);$i++)
			{
			$pos = mb_strpos($row[2],$del[$i]);
			if ($pos != 0)
				{
				$idx = $i;
				break;
				}
			}
		if ($pos > 0)
			{
			$str1 = mb_substr($row[2],0,$pos);
			$str2 = mb_substr($row[2],$pos+1,$len-$pos-1);
			}
		else
			{
			$str1 = $row[2];
			$str2 = "";
			}
		printf("<td>%s</td>\n",$str1);
		printf("<td>%s</td>\n",$str2);
		printf("</tr>\n");
		}
	printf("</table>\n");

	}
else
	{
	echo "Connection failed";
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
