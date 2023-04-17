<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_comm.inc");
require_once("../comm/nsfr_db.inc");

$title = "検体ラック完了強制登録処理";
NsfrHeadOutput($title);
NsfrLogOut($title);

$sdate = $_REQUEST['SDATE'];

printf("<BODY>\n");
NsfrTimeStamp();
printf("<center><h2>%s</h2></center>\n",$title);

printf("<P>\n");
printf("<center>\n");
printf("<P>処理日：%s</P>\n",ymd_edit($sdate));
printf("</center>\n");

printf("<FORM ACTION=\"krackend1.php\" METHOD=GET>\n");
printf("<INPUT TYPE=hidden NAME=SDATE value=\"%s\">\n",$sdate);
printf("<center>\n");
printf("ラックＩＤ\n");
printf("<INPUT TYPE=text NAME=RACK SIZE=12 MAXLENGTH=10>\n");
printf("</center>\n");
printf("<BR>\n");
printf("<center>\n");
printf("<BUTTON type=submit name=submit value=\"submit\">登　録</BUTTON>\n");
printf("</center>\n");
printf("</FORM>\n");
printf("</P>\n");

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
