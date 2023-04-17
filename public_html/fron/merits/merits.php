<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN">
<HTML lang="ja">

<?php
require_once("../comm/nsfr_html.inc");

NsfrHeadOutput("メリッツ処理一覧");
NsfrLogOut("メリッツ処理一覧");
?>

<BODY>
<?php
NsfrTimeStamp();
?>
<center><h2>メリッツ処理一覧</h2></center>

<?php

	printf("<center><P>検索処理</P></center>\n");
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=sel_ino.php>依頼書ナンバー検索</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=krackmap.php>検体ラックマップ照会</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=arackmap.php>アッセイラックマップ照会</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=kensu.php>検体認識数照会</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>新規データ作成</P></center>\n");
	printf("<table align=\"center\" border>\n");

	printf("<tr>\n");
	printf("<th>処理名称</th>\n");
	printf("</tr>\n");



	printf("<tr>\n");
	printf("<td><A href=zokusei.php>新規属性登録処理</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=iraiins.php>新規項目登録処理</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>分注機ダウン時対応</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>分注機ダウン時対応処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=rackanryo.php>ラック完了強制登録</A></td>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=traykanryo.php>トレー完了強制登録</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");

	printf("<HR>\n");

	printf("<center><P>システム照会処理</P></center>\n");
	printf("<table align=\"center\" border>\n");
	printf("<tr>\n");
	printf("<th>処理名称</th>\n");
	printf("</tr>\n");

	printf("<tr>\n");
	printf("<td><A href=weblog.php>Ｗｅｂログファイル照会</A></td>\n");
	printf("</tr>\n");

	printf("</table>\n");
?>

<HR>
<P>
<center><A href=../index.php>トップに戻る</A></center>
</P>
</BODY>
</HTML>
