<?php
function wskmk_table($conn,$wscode)
{
	if (!is_numeric($wscode)) {
		if (strlen($wscode) == 0) {
			return 0;
		} else {
			printf("<center>\n");
			printf("<h2>検査G入力エラー</h2>\n");
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

		printf("<table align=left  border=0>\n");
		printf("<tr valign=top>\n");
	
		printf("<td>\n");

			printf("<table align=\"left\" bgcolor = \"white\" border>\n");
				printf("<tr>\n");
					printf("<th nowarp>項目</th>\n");
					printf("<th nowarp>内容</th>\n");
					printf("<th nowarp>備考</th>\n");
				printf("</tr>\n");
	
			$sql = "select * from knsgmst where knsgrp = '$wscd' for read only";
			foreach ($conn->query($sql) as $row) {
	
				printf("<tr>");
					printf("<td nowarp>%s</td>",'検査G');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['KNSGRP']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
	
				printf("<tr>");
					printf("<td nowarp>%s</td>",'検査G名称');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['KNSGRPNM']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'検査G略称');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['KNSGRPRS']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'SECCD');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SECCD']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'検査法区分');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['KNSHOKBN']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'検査G種別');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['KNSSBT']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'分注G');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['BGROUP']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'運用区分');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['UNYOKBN']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'WS内規定本数(分注NG以外)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SEQKTHSOK']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'WS内規定本数(分注NG)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SEQKTHSNG']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'WS作成規則(分注OK)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['WSSSKSOK']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'WS作成規則(分注OK以外)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['WSSSKSNG']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'分注量MIN');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['MINRYO']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'分注量MAX');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['MAXRYO']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'使用トレイ(初回)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SKITRAY']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'使用トレイ(分注NG)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['MBTTRAY']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'使用トレイ(再検)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SKNTRAY']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'使用トレイ(再測定)');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SSTTRAY']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'曜日指定');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['KNSYB']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'容器CD');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['YKCD']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'初回用WS出力形式');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SKIWSID']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'再検・再測定用WS出力形式');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SKNWSID']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'結果リスト出力形式');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['KKALSTID']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'ラベル出力ID');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['SPLBLID']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'分注NG用WS出力形式');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['LSTYB1']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'再検履歴用WS出力形式');
					printf("<td nowarp>%s</td>",SjToUtfConv($row['LSTYB2']));
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'開始年月日');
					printf("<td nowarp>%10.10s</td>",$row['KAIYMD']);
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'廃止年月日');
					printf("<td nowarp>%10.10s</td>",$row['HAIYMD']);
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'変更担当者ＩＤ');
					printf("<td nowarp>%s</td>",$row['HNKTNTID']);
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
				printf("<tr>");
					printf("<td nowarp>%s</td>",'情報更新日時');
					printf("<td nowarp>%10.10s</td>",$row['KSNDH']);
					printf("<td nowarp>%s</td>",' ');
				printf("</tr>\n",' ');
	
			}
			printf("</table>\n");
		printf("</td>\n");

		printf("<td>\n");
			printf("<table bgcolor = white border>\n");
				printf("<tr>\n");
					printf("<th nowrap>親CD</th>\n");
					printf("<th nowrap>項目CD</th>\n");
					printf("<th nowrap>項目名カナ</th>\n");
					printf("<th nowrap>項目名漢字</th>\n");
					printf("<th nowrap>負荷分画区分</th>\n");
				printf("</tr>\n");
		
				$sql = "";
				$sql = $sql . "select oyakmkcd,kmkcd,kmkrs,kmkrsj,fkbnkkb ";
				$sql = $sql . "from kmkmst where knsgrp = '$wscd' ";
				$sql = $sql . "order by oyakmkcd,kmkcd for read only";
				foreach ($conn->query($sql,PDO::FETCH_NUM) as $row) {
					printf("<tr>\n");
						printf("<td nowrap><A href=kmkmst.php?KMKCD=%s>%s</A></td>\n",$row[0],$row[0]);
						printf("<td nowrap><A href=kmkmst.php?KMKCD=%s>%s</A></td>\n",$row[1],$row[1]);
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[2]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[3]));
						printf("<td nowrap>%s</td>\n",SjToUtfConv($row[4]));
					printf("</tr>\n");
				}
			printf("</table>\n");

		printf("</td>\n");
		
	printf("</table>\n");

	}
	return 0;
}
?>
