<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");

$title = "複数本取り検体登録処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_GET['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<P>処理日：%s</P>\n",ymd_edit($sdate));

printf("<P>\n");
printf("複数本登録する検体No.を入力してください\n");

printf("<FORM ACTION=\"fukusu1.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=text NAME=\"KENNO\" SIZE=14 MAXLENGTH=13>\n");

printf("<INPUT TYPE=hidden NAME=\"SDATE\" value=\"%s\">\n",$sdate);
printf("<BUTTON name=\"submit\" value=\"submit\" type=\"submit\">検索\n");
printf("</BUTTON>\n");
printf("</FORM>\n");
printf("</P></center>\n");

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
