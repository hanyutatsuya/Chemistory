<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>�T�e���C�g�Ɖ�TOP</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY>

<?php
$type = $_SERVER['HTTP_USER_AGENT'];

if  (stristr($type,"docomo") == FALSE)
	{
	printf("<center><h1>�T�e���C�g�Ɖ�TOP(Mobile)</h1></center>\n");
	printf("<center><h2><A href=stl/satellite.php>�T�e���C�g�Ɖ�</A></h2></center>\n");
	printf("<center><h2><A href=stl/maint.html>�����e�i���X</A></h2></center>\n");
	printf("<HR>\n");
	printf("<center><A href=mailto:hanyu@bml.co.jp>mail</A></center>\n");
	}
else
	{
	printf("�T�e���C�g�Ɖ�TOP\n");
	printf("<UL>\n");
	printf("<LI><A href=mobile/satellite.php>�T�e���C�g�Ɖ�</A>\n");
	printf("<LI><A href=mobile/maint.html>�����e�i���X</A>\n");
	printf("</UL>\n");
	printf("<HR>\n");
	printf("<A href=mailto:hanyu@bml.co.jp>mail</A>\n");
	}
?>

</BODY>
</HTML>
