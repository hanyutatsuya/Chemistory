<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");

$title = "データーベース選択";
LaboHeadOutput($title);
LaboLogOut($title);

printf("<BODY>\n");
LaboTimeStamp();

print <<<__DBSELOUT__

<center><h2>$title</h2></center>

<FORM ACTION="dbselgo.php" METHOD="POST">
<P>
<center>
<INPUT TYPE=RADIO NAME=KUBUN VALUE="0" checked><TT>KEA00DB1(本番ＤＢ)</TT><BR>
<INPUT TYPE=RADIO NAME=KUBUN VALUE="1"><TT>KEA00DB0(開発ＤＢ)</TT><BR>
</center>
<BR>
<center><BUTTON type=submit name=submit value="submit">選択
</BUTTON></center>
</P>
</FORM>
__DBSELOUT__;

?>

<BR CLEAR=ALL>
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
