<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">
<HEAD>
<TITLE>認識・フロンティア照会TOP</TITLE>
<META http-equiv="Content-Type" content="text/html; charset=SHIFT_JIS">
</HEAD>
<BODY background="img/a014bcg.gif">

<DIV align=right><A href=merits/merits.php STYLE="text-decoration:none;">　</A></DIV>

<?php

	$dbname = $_SESSION['dbname'];
	if (empty($dbname))
		{
		$_SESSION['dbname'] = 'NSFRDB1';
		$dbname = $_SESSION['dbname'];
		}

	printf("<center><h1>認識・フロンティア照会TOP</h1></center>\n");
	printf("<center><h2><A href=master/master.php>マスタ照会</A></h2></center>\n");
	printf("<center><h2><A href=comm/nsfrshokai.php>Ｎｏ．対応照会</A></h2></center>\n");
	printf("<center><h2><A href=comm/posshokai.php>検体ポジション照会</A></h2></center>\n");
	printf("<center><h2><A href=ninsiki/ninsiki.php>認識システム照会</A></h2></center>\n");
	printf("<center><h2><A href=bunchu/bunchu.php>フロンティアシステム照会</A></h2></center>\n");
	printf("<center><h2><A href=maint/maintlogin.php>メンテナンス</A></h2></center>\n");
	printf("<HR>\n");
	printf("<center><h2><A href=mailto:nsfr-info@bml.co.jp>メール</A></h2>\n");
	printf("<center><h2><A href=php/index.php>phpinfo</A></h2>\n");

	printf("<DIV align=right>\n");
	printf("[%s] %s\n",$dbname,date("Y-m-d H:i:s"));
	printf("</DIV>\n");

?>

</BODY>
</HTML>
