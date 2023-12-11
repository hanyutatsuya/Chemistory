<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("WS-SEQ管理情報");
LaboLogOut("WS-SEQ管理情報");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>WS-SEQ管理情報</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th nowarp>WS管理通番</th>
		<th nowarp>検査開始日</th>
		<th nowarp>検査G</th>
		<th nowarp>WS種別</th>
		<th nowarp>WS番号</th>
		<th nowarp>検査SEQ(開始)</th>
		<th nowarp>検査SEQ(終了)</th>
		<th nowarp>検査SEQ数(検体数)</th>
		<th nowarp>検査工程区分</th>
		<th nowarp>データ入力担当者</th>
		<th nowarp>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from wsseqknri order by wstbnknr for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['WSTBNKNR']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSKISYMD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['WSSBT']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['WSNO']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSSEQST']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSSEQED']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSSEQSU']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KSKTKBN']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['DTNRTTS']));
				printf("<td nowarp>%10.10s</td>\n",SjToUtfConv($row['KSNDH']));
			printf("</tr>\n");
		}
	}
	catch (Exception $ex) {
		GetDBErrMsg($ex);
	}

} else {
	echo "Connection failed";
}

$conn = null;

?>

</table>

<HR>
<P>
<center><A href=../master/master.php>マスター一覧に戻る</A></center>
</P>

<HR>
</BODY>
</HTML>
