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

<table bgcolor = white border>

	<tr>
		<th nowarp>テーブル名</th>
		<th nowarp>データ名称</th>
	</tr>

	<tr>
		<td nowarp><A href=irino.php>IRINO</A></td>
		<td nowarp><A href=irino.php>№対応照会</A></td>
	</tr>
	<tr>
		<td nowarp><A href=cmtmst.php>CMTMST</A></td>
		<td nowarp><A href=cmtmst.php>コメントマスタ</A></td>
	</tr>
	<tr>
		<td nowarp><A href=kkahskmst.php>KKAHSKMST</A></td>
		<td nowarp><A href=kkahskmst.php>結果補足マスタ</A></td>
	</tr>
</table>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
