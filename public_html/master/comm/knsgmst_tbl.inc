<?php
function knsgmst_table($conn,$wscode)
{
	if (!is_numeric($wscode)) {
		if (strlen($wscode) == 0) {
			return 0;
		} else {
			printf("<center>\n");
			printf("<h2>検査グループ入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
			return -1;
		}
	} else {
		if (strlen($wscode) < 5) {
			$wscd = sprintf("%04d",$wscode);
		} else {
			$wscd = sprintf("%d",$wscode);
		}
		printf("<table align=\"left\" bgcolor = \"white\" border>\n");
			printf("<tr>\n");
				printf("<th>項目</th>\n");
				printf("<th>内容</th>\n");
				printf("<th>備考</th>\n");
			printf("</tr>\n");

		$sql = "select * from knsgmst where knsgrp = '$wscd' for read only";
		foreach ($conn->query($sql) as $row) {

			printf("<tr>");
				printf("<td>%s</td>",'検査グループ');
				printf("<td>%s</td>",SjToUtfConv($row['KNSGRP']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'検査グループ名称');
				printf("<td>%s</td>",SjToUtfConv($row['KNSGRPNM']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'検査グループ略称');
				printf("<td>%s</td>",SjToUtfConv($row['KNSGRPRS']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'セクションコード');
				printf("<td>%s</td>",SjToUtfConv($row['SECCD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'検査法区分');
				printf("<td>%s</td>",SjToUtfConv($row['KNSHOKBN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'検査グループ種別');
				printf("<td>%s</td>",SjToUtfConv($row['KNSSBT']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'分注グループ');
				printf("<td>%s</td>",SjToUtfConv($row['BGROUP']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'運用区分');
				printf("<td>%s</td>",SjToUtfConv($row['UNYOKBN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'WS内規定本数(分注NG以外)');
				printf("<td>%s</td>",SjToUtfConv($row['SEQKTHSOK']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'WS内規定本数(分注NG)');
				printf("<td>%s</td>",SjToUtfConv($row['SEQKTHSNG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'WS作成規則(分注OK)');
				printf("<td>%s</td>",SjToUtfConv($row['WSSSKSOK']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'WS作成規則(分注OK以外)');
				printf("<td>%s</td>",SjToUtfConv($row['WSSSKSNG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'分注量MIN');
				printf("<td>%s</td>",SjToUtfConv($row['MINRYO']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'分注量MAX');
				printf("<td>%s</td>",SjToUtfConv($row['MAXRYO']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'使用トレイ(初回)');
				printf("<td>%s</td>",SjToUtfConv($row['SKITRAY']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'使用トレイ(分注NG)');
				printf("<td>%s</td>",SjToUtfConv($row['MBTTRAY']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'使用トレイ(再検)');
				printf("<td>%s</td>",SjToUtfConv($row['SKNTRAY']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'使用トレイ(再測定)');
				printf("<td>%s</td>",SjToUtfConv($row['SSTTRAY']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'曜日指定');
				printf("<td>%s</td>",SjToUtfConv($row['KNSYB']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'容器コード');
				printf("<td>%s</td>",SjToUtfConv($row['YKCD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'初回用WS出力形式');
				printf("<td>%s</td>",SjToUtfConv($row['SKIWSID']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'再検・再測定用WS出力形式');
				printf("<td>%s</td>",SjToUtfConv($row['SKNWSID']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'結果リスト出力形式');
				printf("<td>%s</td>",SjToUtfConv($row['KKALSTID']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'ラベル出力ID');
				printf("<td>%s</td>",SjToUtfConv($row['SPLBLID']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'分注NG用WS出力形式');
				printf("<td>%s</td>",SjToUtfConv($row['LSTYB1']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'再検履歴用WS出力形式');
				printf("<td>%s</td>",SjToUtfConv($row['LSTYB2']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'開始年月日');
				printf("<td>%10.10s</td>",$row['KAIYMD']);
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'廃止年月日');
				printf("<td>%10.10s</td>",$row['HAIYMD']);
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'変更担当者ＩＤ');
				printf("<td>%s</td>",$row['HNKTNTID']);
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');
			printf("<tr>");
				printf("<td>%s</td>",'情報更新日時');
				printf("<td>%20.20s</td>",$row['KSNDH']);
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

		}
		printf("</table>\n");
	}
	return 0;
}

?>
