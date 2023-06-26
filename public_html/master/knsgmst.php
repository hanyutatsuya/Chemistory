<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/labo_html.inc");
require_once("../comm/labo_db.inc");
LaboHeadOutput("検査グループマスタ");
LaboLogOut("検査グループマスタ");
?>

<BODY background="../img/mstback.gif">
<?php
LaboTimeStamp();
?>
<center><h2>検査グループマスタ</h2></center>

<table align="center" bgcolor = "white" border>
	<tr>
		<th>検査グループ</th>
		<th>検査グループ名称</th>
		<th>検査グループ略称</th>
		<th>セクションコード</th>
		<th>検査法区分</th>
		<th>検査グループ種別</th>
		<th>赤伝フラグ</th>
		<th>異常値マーク</th>
		<th>分注グループ</th>
		<th>運用区分</th>
		<th>WS内規定本数（分注NG以外）</th>
		<th>WS内規定本数（分注NG）</th>
		<th>WS作成規則（分注OK）</th>
		<th>WS作成規則（分注OK以外）</th>
		<th>分注量MIN</th>
		<th>分注量MAX</th>
		<th>使用トレイ（初回）</th>
		<th>使用トレイ（分注NG）</th>
		<th>使用トレイ（再検）</th>
		<th>使用トレイ（再測定）</th>
		<th>曜日指定</th>
		<th>容器コード</th>
		<th>初回用WS出力形式</th>
		<th>再検・再測定用WS出力形式</th>
		<th>結果リスト出力形式</th>
		<th>ラベル出力ID</th>
		<th>分注NG用WS出力形式</th>
		<th>再検履歴用WS出力形式</th>
		<th>開始年月日</th>
		<th>廃止年月日</th>
		<th>変更担当者ＩＤ</th>
		<th>情報更新日時</th>
	</tr>

<?php

$conn = GetDBConn();

if  ($conn){

try {
	$sql = "select * from knsgmst order by knsgrp for read only";
	foreach ($conn->query($sql) as $row) {
		printf("<tr>\n");
			printf("<td>%s</td>\n",$row['KNSGRP']);
			printf("<td>%s</td>\n",SjToUtfConv($row['KNSGRPNM']));
			printf("<td>%s</td>\n",SjToUtfConv($row['KNSGRPRS']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SECCD']));
			printf("<td>%s</td>\n",SjToUtfConv($row['KNSHOKBN']));
			printf("<td>%s</td>\n",SjToUtfConv($row['KNSSBT']));
			printf("<td>%s</td>\n",SjToUtfConv($row['BGROUP']));
			printf("<td>%s</td>\n",SjToUtfConv($row['UNYOKBN']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SEQKTHSOK']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SEQKTHSNG']));
			printf("<td>%s</td>\n",SjToUtfConv($row['WSSSKSOK']));
			printf("<td>%s</td>\n",SjToUtfConv($row['WSSSKSNG']));
			printf("<td>%s</td>\n",SjToUtfConv($row['MINRYO']));
			printf("<td>%s</td>\n",SjToUtfConv($row['MAXRYO']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SKITRAY']));
			printf("<td>%s</td>\n",SjToUtfConv($row['MBTTRAY']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SKNTRAY']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SSTTRAY']));
			printf("<td>%s</td>\n",SjToUtfConv($row['KNSYB']));
			printf("<td>%s</td>\n",SjToUtfConv($row['YKCD']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SKIWSID']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SKNWSID']));
			printf("<td>%s</td>\n",SjToUtfConv($row['KKALSTID']));
			printf("<td>%s</td>\n",SjToUtfConv($row['SPLBLID']));
			printf("<td>%s</td>\n",SjToUtfConv($row['LSTYB1']));
			printf("<td>%s</td>\n",SjToUtfConv($row['LSTYB2']));
			printf("<td>%10.10s</td>\n",$row['KAIYMD']);
			printf("<td>%10.10s</td>\n",$row['HAIYMD']);
			printf("<td>%s</td>\n",$row['HNKTNTID']);
			printf("<td>%20.20s</td>\n",$row['KSNDH']);
		printf("</tr>\n");
	}
}
	catch (Exception $ex) {
		LaboLogOut(sprintf("ERRMSG  [%s]",$ex->getMessage()));
		LaboLogOut(sprintf("ERRCODE [%s]",$ex->getCode()));
		printf("ERRMSG  [%s]<BR>",$ex->getMessage());
		printf("ERRCODE [%s]<BR>",$ex->getCode());
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
