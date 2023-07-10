<?php
function kmkmst_table($conn,$kcode)
{
	if (!is_numeric($kcode)) {
		if (strlen($kcode) == 0) {
			return 0;
		} else {
			printf("<center>\n");
			printf("<h2>項目CD入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
			return -1;
		}
	} else {
		if (strlen($wscode) < 8) {
			$kmcd = sprintf("%07d",$kcode);
		} else {
			$kmcd = sprintf("%d",$kcode);
		}
		printf("<table align=\"left\" bgcolor = \"white\" border>\n");
			printf("<tr>\n");
				printf("<th nowarp>項目</th>\n");
				printf("<th nowarp>内容</th>\n");
				printf("<th nowarp>備考</th>\n");
			printf("</tr>\n");
	
		$sql = "select * from kmkmst where kmkcd = '$kmcd' order by knsgrp fetch first 1 rows only for read only";
		foreach ($conn->query($sql) as $row) {

			printf("<tr>");
				printf("<td nowarp>%s</td>",'検査G');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KNSGRP']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目CD');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKCD']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目正式名称(カナ)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKNM']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目正式名称(漢字)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKNMJ']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目略称(カナ)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKRS']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目略称(漢字)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKRSJ']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目名(英語)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKNME']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目補足名(漢字)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKHSKNMJ']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'負荷項目名(カナ)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['FKKMKNM']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'負荷項目名(漢字)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['FKKMKNMJ']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'サンプリングCD');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['SMPCD']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'親項目CD');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['OYAKMKCD']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'子ＲＲＮ');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KORRN']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'SECCD');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['SECCD']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'親展F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['STNFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'小数点桁数');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['SSTNKSU']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'測定方法');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['ASSAY']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'負荷順番');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['FKJBN']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'負荷分画区分');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['FKBNKKB']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'凍結F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['TSKFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'透析F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['TKTFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'ＬＴ未満F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['LTMMNFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'材料区分');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['ZRKBN']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'分注量(通常)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['BCRTJ']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'分注量(少量)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['BCRSR']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'分注量(小児)');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['BCRSN']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'夜間検査F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['YKNKNSFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'保留日数');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['HRYNSU']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'自動発生結果');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['JDHSKKA']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'表示順');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['HYJIJN']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'計算項目F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KSNKMKFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'補正有無F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['HSIUMFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'Ｘ軸最小値');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['GMIN']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'Ｘ軸刻み幅');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['GHABA']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'履歴情報保存日数');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['RRKHZN']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'乳び溶血優先F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['NYUYOUFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'定性・定量F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['TSTRFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'項目種別');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KMKSBT']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'照合チェック採用F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['SGCHKFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'血清情報影響F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KSJHFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'希釈測定結果照合F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['KSSGFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'XbarM集計F');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['XMSKFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'XbarMチェックF');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['XMCHKFLG']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'XbarMカウント数');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['XMCOUNT']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'開始年月日');
				printf("<td nowarp>%10.10s</td>",SjToUtfConv($row['KAIYMD']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'廃止年月日');
				printf("<td nowarp>%10.10s</td>",SjToUtfConv($row['HAIYMD']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'変更担当者ＩＤ');
				printf("<td nowarp>%s</td>",SjToUtfConv($row['HNKTNTID']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td nowarp>%s</td>",'情報更新日時');
				printf("<td nowarp>%10.10s</td>",SjToUtfConv($row['KSNDH']));
				printf("<td nowarp>%s</td>",' ');
			printf("</tr>\n",' ');

		}
		printf("</table>\n");
	}
	return 0;
}

?>
