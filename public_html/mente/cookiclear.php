<?php
	$lbcode = $_REQUEST['LBCODEA'];
	$udate  = $_REQUEST['UDATEA'];
	$hokoku = $_REQUEST['HOKOKUA'];
	$bunya  = $_REQUEST['BUNYAA'];
	$btn    = $_REQUEST['SUBMIT'];

	if ($btn == "submit") {
		if ($lbcode == "1") {
			$flag = setcookie('LBCODE', '',time() - 3600,'/');
			unset($_COOKIE['LBCODE']);
		}
		if ($udate == "1") {
			$flag = setcookie('UDATE', '',time() - 3600,'/');
			unset($_COOKIE['UDATE']);
		}
		if ($hokoku == "1") {
			$flag = setcookie('DHOKOKU', '',time() - 3600,'/');
			unset($_COOKIE['DHOKOKU']);
		}
		if ($bunya == "1") {
			$flag = setcookie('DBUNYA', '',time() - 3600,'/');
			unset($_COOKIE['DBUNYA']);
		}
	}

	require_once("../comm/labo_html.inc");
	require_once("../comm/labo_db.inc");
?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php

	$title = "Ｃｏｏｋｉクリア処理";
	LaboHeadOutput($title);
	LaboLogOut($title);

	printf("<BODY background=\"../img/blue_p8b.gif\">\n");
	LaboTimeStamp();

?>

<?php
	printf("<center><h2>メンテナンス処理</h2></center>\n");
	printf("<center><P>Ｃｏｏｋｉクリア処理</P></center>\n");

	printf("<FORM name=\"hkbunya\" ACTION=\"cookiclear.php\" METHOD=POST>\n");

	printf("<center>\n");

//	printf("<DIV style=\"width: 1200px; padding: 10px; margin: 10px; border: 1px solid; border-radius: 10px;\">\n");
	printf("<DIV style=\"width: 400px; padding: 10px; margin: 10px; \">\n");
//	printf("<div style=\"text-align: left; float: left;\">\n");
	printf("<div style=\"text-align: left; float: center;\">\n");

	printf("<INPUT TYPE=checkbox NAME=LBCODEA value=1");
	if ($lbcode == "1") {
		printf(" checked");
	}
	printf(">\n");
	printf("ラボコード\n");
	printf("<BR>\n");
	printf("<INPUT TYPE=checkbox NAME=UDATEA value=1");
	if ($udate == "1") {
		printf(" checked");
	}
	printf(">\n");
	printf("受付日\n");
	printf("<BR>\n");
	printf("<INPUT TYPE=checkbox NAME=HOKOKUA value=1");
	if ($hokoku == "1") {
		printf(" checked");
	}
	printf(">\n");
	printf("報告区分\n");
	printf("<BR>\n");
	printf("<INPUT TYPE=checkbox NAME=BUNYAA value=1");
	if ($bunya == "1") {
		printf(" checked");
	}
	printf(">\n");
	printf("検査分野\n");
	printf("<BR>\n");

	printf("</DIV>\n");
	printf("</DIV>\n");
	printf("</center>\n");

?>

	<center>
	<BUTTON type=submit name=SUBMIT value="submit">クリア</BUTTON>
	</center>
	</FORM>

<?php
	if ($btn == "submit") {
		printf("<center><P>\n");
		printf("クリアしました\n");
		printf("</P></center>\n");
	}

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>

</BODY>
</HTML>

