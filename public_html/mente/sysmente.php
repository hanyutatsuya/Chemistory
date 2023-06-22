<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
	require_once("../comm/labo_html.inc");

	LaboHeadOutput("メンテナンス処理");
	LaboLogOut("メンテナンス処理");
?>

<BODY background="/~kea00sys/img/blue_p8b.gif">

<?php
	LaboTimeStamp();
print <<<__MIDASHI__
	<center><h2>メンテナンス処理一覧</h2></center>
__MIDASHI__;


print <<<__MENTE__

	<HR>

	<center><P>データーベース選択</P></center>
	<table align="center" border>
		<tr>
			<th>処理名称</th>
		</tr>

		<tr>
			<td><A href=dbselect.php>データーベース選択</A></td>
		</tr>
	</table>

	<HR>

	<center><P>システム照会処理</P></center>
	<table align="center" border>
		<tr>
			<th>処理名称</th>
		</tr>
		<tr>
			<td><A href=weblog.php>Ｗｅｂログファイル照会</A></td>
		</tr>
	</table>

__MENTE__;

?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>

</BODY>
</HTML>
