<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
	require_once("../comm/labo_html.inc");

	if (isset($_COOKIE["LBCODE"])){
		$lbcode = $_COOKIE["LBCODE"];
	} else {
		$lbcode = -1;
	}


//    $flag = setcookie("LBCODE", $lbcode);

	LaboHeadOutput("メンテナンス処理");
	LaboLogOut("メンテナンス処理");
?>

<BODY background="/~labo/img/blue_p8b.gif">

<?php
	LaboTimeStamp();
print <<<__MIDASHI__
	<center><h2>メンテナンス処理</h2></center>
__MIDASHI__;

	if ($lbcode < 0) {
print <<<__NOLBCODE__
	<P><center>ラボコードが設定されていません</center></P>
	<P><center>トップページからやり直してください</center></P>
__NOLBCODE__;
	} else {
print <<<__LBCODEOK__

<p><center>
<A href=mnt_info.php>お知らせ情報メンテナンス</A>
</center></P>

__LBCODEOK__;
	}

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>

</BODY>
</HTML>
