<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
LaboHeadOutput("データ照会");
LaboLogOut("データ照会");
?>

<BODY background="/~kea00sys/img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>データ照会</h2></center>

<HR>

<table align="center" bgcolor = white border>

	<tr>
		<th nowarp>処理名</th>
		<th nowarp>処理名称</th>
	</tr>

	<tr>
		<td nowarp><A href=irino.php>IRINO</A></td>
		<td nowarp><A href=irino.php>依頼書№対応照会</A></td>
	</tr>
	<tr>
		<td nowarp><A href=kekka.php>KEKKA</A></td>
		<td nowarp><A href=kekka.php>結果照会</A></td>
	</tr>
</table>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
