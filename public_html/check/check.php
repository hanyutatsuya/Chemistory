<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
LaboHeadOutput("チェック処理");
LaboLogOut("チェック処理");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>チェック処理</h2></center>

<HR>

<table align="center" bgcolor = white border>

	<tr>
		<th nowarp>処理名</th>
		<th nowarp>処理名称</th>
	</tr>

	<tr>
		<td nowarp><A href=knsflg.php>KNSFLG</A></td>
		<td nowarp><A href=knsflg.php>検査結果フラグ異常確認</A></td>
	</tr>

	<tr>
		<td nowarp><A href=pg12.php>PG12</A></td>
		<td nowarp><A href=pg12.php>PG1/PG2比チェック</A></td>
	</tr>

</table>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
