<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("検査Gマスタ");
LaboLogOut("検査Gマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>検査Gマスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th nowarp>検査G</th>
		<th nowarp>検査G名称</th>
		<th nowarp>検査G略称</th>
		<th nowarp>SECCD</th>
		<th nowarp>検査法区分</th>
		<th nowarp>検査G種別</th>
		<th nowarp>分注G</th>
		<th nowarp>運用区分</th>
		<th nowarp>WS内規定本数（分注NG以外）</th>
		<th nowarp>WS内規定本数（分注NG）</th>
		<th nowarp>WS作成規則（分注OK）</th>
		<th nowarp>WS作成規則（分注OK以外）</th>
		<th nowarp>分注量MIN</th>
		<th nowarp>分注量MAX</th>
		<th nowarp>使用トレイ（初回）</th>
		<th nowarp>使用トレイ（分注NG）</th>
		<th nowarp>使用トレイ（再検）</th>
		<th nowarp>使用トレイ（再測定）</th>
		<th nowarp>曜日指定</th>
		<th nowarp>容器CD</th>
		<th nowarp>初回用WS出力形式</th>
		<th nowarp>再検・再測定用WS出力形式</th>
		<th nowarp>結果リスト出力形式</th>
		<th nowarp>ラベル出力ID</th>
		<th nowarp>分注NG用WS出力形式</th>
		<th nowarp>再検履歴用WS出力形式</th>
		<th nowarp>開始年月日</th>
		<th nowarp>廃止年月日</th>
		<th nowarp>変更担当者ＩＤ</th>
		<th nowarp>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if ($conn) {

	try {
		$sql = "select * from knsgmst order by knsgrp for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowarp>%s</td>\n",$row['KNSGRP']);
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSGRPNM']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSGRPRS']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SECCD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSHOKBN']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSSBT']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BGROUP']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['UNYOKBN']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SEQKTHSOK']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SEQKTHSNG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['WSSSKSOK']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['WSSSKSNG']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['MINRYO']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['MAXRYO']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SKITRAY']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['MBTTRAY']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SKNTRAY']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SSTTRAY']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSYB']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['YKCD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SKIWSID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SKNWSID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KKALSTID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['SPLBLID']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['LSTYB1']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['LSTYB2']));
				printf("<td nowarp>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td nowarp>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td nowarp>%s</td>\n",$row['HNKTNTID']);
				printf("<td nowarp>%10.10s</td>\n",$row['KSNDH']);
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
