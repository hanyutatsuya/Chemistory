<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");

$title = "Ｗｅｂログファイル一覧";
LaboHeadOutput($title);
LaboLogOut($title);

printf("<BODY>\n");
LaboTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

$dir = opendir ("/home/data/log");
rewinddir($dir);
$i = 0;
while($fname = readdir($dir))
	{
	if  (strncmp($fname,"php_log",7) == 0)
		{
		$logname[$i] = $fname;
		$i++;
		}
	}

sort($logname,SORT_STRING);

printf("<table align=\"center\" border>\n");

printf("<tr>\n");
printf("<th>ファイル名</th>\n");
printf("<th>更新時刻</th>\n");
printf("</tr>\n");

for ($i=0;$i<count($logname);$i++) {
	printf("<tr>\n");
	printf("<td><A href=weblog1.php?FNAME=%s>%s</A></td>\n",$logname[$i],$logname[$i]);
	$logpath = "/home/data/log/" . $logname[$i];
	printf("<td><A href=weblog1.php?FNAME=%s>%s</A></td>\n",$logname[$i],date("Y/m/d H:i:s",filectime($logpath)));
	printf("</tr>\n");
}

printf("</table>\n");
?>

<HR>
<P>
<center><A href=sysmente.php>メンテナンス処理一覧に戻る</A></center>
</P>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>


