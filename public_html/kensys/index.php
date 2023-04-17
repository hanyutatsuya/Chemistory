<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>サテライト照会TOP</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY>

<?php
$type = $_SERVER['HTTP_USER_AGENT'];

if  (stristr($type,"docomo") == FALSE)
	{
	printf("<center><h1>サテライト照会TOP(Mobile)</h1></center>\n");
	printf("<center><h2><A href=stl/satellite.php>サテライト照会</A></h2></center>\n");
	printf("<center><h2><A href=stl/maint.html>メンテナンス</A></h2></center>\n");
	printf("<HR>\n");
	printf("<center><A href=mailto:hanyu@bml.co.jp>mail</A></center>\n");
	}
else
	{
	printf("サテライト照会TOP\n");
	printf("<UL>\n");
	printf("<LI><A href=mobile/satellite.php>サテライト照会</A>\n");
	printf("<LI><A href=mobile/maint.html>メンテナンス</A>\n");
	printf("</UL>\n");
	printf("<HR>\n");
	printf("<A href=mailto:hanyu@bml.co.jp>mail</A>\n");
	}
?>

</BODY>
</HTML>
