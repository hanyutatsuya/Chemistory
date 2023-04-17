<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");
require_once("../comm/nsfr_db.inc");
NsfrHeadOutput("血型・エンドトキシン検体リスト出力処理");
NsfrLogOut("血型・エンドトキシン検体リスト出力処理");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>血型・エンドトキシン検体リスト出力処理</h2></center>

<?php
//$sdate = $_REQUEST['SDATE'];
$send1 = $_REQUEST['SEND1'];
$send2 = $_REQUEST['SEND2'];

$updflg = 0;
if  (!empty($send1))
	{
	$msg = "　　　　　血型検体リスト";
	$app = "/home/nsfr/bin/lst_abo.php";
	$updflg = 1;
	}
if  (!empty($send2))
	{
	$msg = "エンドトキシン検体リスト";
	$app = "/home/nsfr/bin/lst_end.php";
	$updflg = 2;
	}

if ($updflg != 0)
	{
	$sret = shell_exec($app);
	printf("<P>\n");
	printf("%sを出力しました。\n",$msg);
	printf("</P>\n");
	printf("<HR>\n");
	}


printf("<FORM ACTION=\"aboend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("　　　　　血型検体リスト\n");
printf("　<BUTTON type=submit name=SEND1 value=\"submit\">出　力\n");
printf("</BUTTON>\n");
printf("</FORM>\n");

printf("<FORM ACTION=\"aboend.php\" METHOD=\"POST\">\n");
printf("<INPUT TYPE=hidden NAME=SDATE VALUE=\"%s\">\n",$sdate);
printf("<P><TT>\n");
printf("エンドトキシン検体リスト\n");
	printf("　<BUTTON type=submit name=SEND2 value=\"submit\">出　力\n");
	printf("</BUTTON>\n");
printf("</FORM>\n");

printf("<HR>\n");
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
