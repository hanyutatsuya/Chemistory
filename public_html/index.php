<?php

	require_once("comm/labo_html.inc");

	$dbname = $_SESSION['dbname'];
	if (empty($dbname)) {
		$_SESSION['dbname'] = 'KEA00DB1';
		$dbname = $_SESSION['dbname'];
	}

?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
	LaboHeadOutput("ケミストリー");
	LaboLogOut("ケミストリー");
?>

<BODY background="img/blue_p8b1.gif">

<DIV align=right><A href=mente/sysmente.php STYLE="text-decoration:none;">　</A></DIV>

<?php
	printf("<center><h1>ケミストリー照会</h1></center>\n");

	printf("<center><h2><A href=master/master.php>マスタ照会</A></h2></center>\n");
	printf("<center><h2><A href=data/data.php>データ照会</A></h2></center>\n");
	printf("<center><h2><A href=mente/sysmente.php>メンテナンス</A></h2></center>\n");
//	printf("<DIV align=right><A href=php/phpinfo.php>phpinfo</A></DIV>\n");
	printf("<HR>\n");

//	printf("<HR>\n");
	printf("<DIV align=right><A href=php/phpinfo.php>phpinfo</A></DIV>\n");

	LaboTimeStamp();

?>

</BODY>
</HTML>

