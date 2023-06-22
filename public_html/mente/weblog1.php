<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");

$fname = trim($_GET['FNAME']);

$title = sprintf("Ｗｅｂログ照会処理(%s)",$fname);
LaboHeadOutput($title);
LaboLogOut($title);

printf("<BODY>\n");
LaboTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);
printf("<HR>\n");

$path = "/home/data/log/" . $fname;
$fp = fopen($path,"r");
while ($buff = fgets($fp,1024)) {
	printf("%s<BR>\n",$buff);
}
fclose($fp);

?>

<HR>
<P>
<center><A href=weblog.php>Ｗｅｂログファイル一覧に戻る</A></center>
</P>

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


