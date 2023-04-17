<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
require_once("../comm/nsfr_comm.inc");

$fname = trim($_GET['FNAME']);

$title = sprintf("Ｗｅｂログ照会処理(%s)",$fname);
NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);
printf("<HR>\n");

$path = "/home/data/log/" . $fname;
$fp = fopen($path,"r");
while($buff = fgets($fp,1024))
	{
	printf("%s<BR>\n",$buff);
	}
fclose($fp);

printf("<HR>\n");
printf("<P>\n");
printf("<center><A href=weblog.php>Ｗｅｂログファイル一覧に戻る</A></center>\n");
printf("</P>\n");

printf("<P>\n");
printf("<center><A href=merits.php>メリッツ処理一覧に戻る</A></center>\n");
printf("</P>\n");

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
<HR>
</BODY>
</HTML>


