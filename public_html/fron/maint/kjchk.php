<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
//require_once("../comm/nsfr_db.inc");

$sdate  = $_REQUEST['SDATE'];

$title = "患者名チェックリストメンテナンス";
NsfrHeadOutput($title);
NsfrLogOut($title);

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<FORM ACTION=\"kjchkupd.php\" METHOD=\"POST\">\n");
printf("<P>\n");
printf("<center>\n");
printf("<INPUT TYPE=RADIO NAME=KUBUN VALUE=\"0\" checked><TT>ラボ受付分（網掛け　　　　）</TT><BR>\n");
printf("<INPUT TYPE=RADIO NAME=KUBUN VALUE=\"1\"><TT>埼玉受付分（アンダーライン）</TT><BR>\n");
printf("</center>\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<BR>\n");
printf("<center><BUTTON type=submit name=submit value=\"submit\">選択\n");
printf("</BUTTON></center>\n");
printf("</P>\n");
printf("</FORM>\n");

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
