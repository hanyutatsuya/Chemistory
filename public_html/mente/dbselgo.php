<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");

$kubun = $_REQUEST['KUBUN'];

$title = "データーベース選択";

if ($kubun == 0) {
	$dbname = "KEA00DB1";
	$name = "(本番ＤＢ)";
}
if ($kubun == 1) {
	$dbname = "KEA00DB0";
	$name = "(開発ＤＢ)";
}

LaboHeadOutput($title);
LaboLogOut($title);

printf("<BODY>\n");
LaboTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);
printf("<BR>\n");

printf("<P>\n");
printf("<center>データーベースを(%s)%sへ変更します</center>\n",$dbname,$name);
printf("</P>\n");

$_SESSION['dbname'] = $dbname;
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
