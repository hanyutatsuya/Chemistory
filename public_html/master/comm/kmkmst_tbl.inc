<?php
function kmkmst_table($conn,$kcode)
{
	if (!is_numeric($kcode)) {
		if (strlen($kcode) == 0) {
			return 0;
		} else {
			printf("<center>\n");
			printf("<h2>項目コード入力エラー</h2>\n");
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
				printf("<th>項目</th>\n");
				printf("<th>内容</th>\n");
				printf("<th>備考</th>\n");
			printf("</tr>\n");
	
		$sql = "select * from kmkmst where kmkcd = '$kmcd' order by knsgrp fetch first 1 rows only for read only";
		foreach ($conn->query($sql) as $row) {

			printf("<tr>");
				printf("<td>%s</td>",'検査グループ');
				printf("<td>%s</td>",SjToUtfConv($row['KNSGRP']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目コード');
				printf("<td>%s</td>",SjToUtfConv($row['KMKCD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目正式名称(カナ)');
				printf("<td>%s</td>",SjToUtfConv($row['KMKNM']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目正式名称(漢字)');
				printf("<td>%s</td>",SjToUtfConv($row['KMKNMJ']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目略称(カナ)');
				printf("<td>%s</td>",SjToUtfConv($row['KMKRS']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目略称(漢字)');
				printf("<td>%s</td>",SjToUtfConv($row['KMKRSJ']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目名(英語)');
				printf("<td>%s</td>",SjToUtfConv($row['KMKNME']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目補足名(漢字)');
				printf("<td>%s</td>",SjToUtfConv($row['KMKHSKNMJ']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'負荷項目名(カナ)');
				printf("<td>%s</td>",SjToUtfConv($row['FKKMKNM']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'負荷項目名(漢字)');
				printf("<td>%s</td>",SjToUtfConv($row['FKKMKNMJ']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'サンプリングコード');
				printf("<td>%s</td>",SjToUtfConv($row['SMPCD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'親項目コード');
				printf("<td>%s</td>",SjToUtfConv($row['OYAKMKCD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'子ＲＲＮ');
				printf("<td>%s</td>",SjToUtfConv($row['KORRN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'セクションコード');
				printf("<td>%s</td>",SjToUtfConv($row['SECCD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'親展フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['STNFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'小数点桁数');
				printf("<td>%s</td>",SjToUtfConv($row['SSTNKSU']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'測定方法');
				printf("<td>%s</td>",SjToUtfConv($row['ASSAY']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'負荷順番');
				printf("<td>%s</td>",SjToUtfConv($row['FKJBN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'負荷分画区分');
				printf("<td>%s</td>",SjToUtfConv($row['FKBNKKB']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'凍結フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['TSKFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'透析フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['TKTFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'ＬＴ未満フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['LTMMNFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'材料区分');
				printf("<td>%s</td>",SjToUtfConv($row['ZRKBN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'分注量(通常)');
				printf("<td>%s</td>",SjToUtfConv($row['BCRTJ']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'分注量(少量)');
				printf("<td>%s</td>",SjToUtfConv($row['BCRSR']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'分注量(小児)');
				printf("<td>%s</td>",SjToUtfConv($row['BCRSN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'夜間検査フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['YKNKNSFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'保留日数');
				printf("<td>%s</td>",SjToUtfConv($row['HRYNSU']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'自動発生結果');
				printf("<td>%s</td>",SjToUtfConv($row['JDHSKKA']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'表示順');
				printf("<td>%s</td>",SjToUtfConv($row['HYJIJN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'計算項目フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['KSNKMKFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'補正有無フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['HSIUMFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'Ｘ軸最小値');
				printf("<td>%s</td>",SjToUtfConv($row['GMIN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'Ｘ軸刻み幅');
				printf("<td>%s</td>",SjToUtfConv($row['GHABA']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'履歴情報保存日数');
				printf("<td>%s</td>",SjToUtfConv($row['RRKHZN']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'乳び溶血優先フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['NYUYOUFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'定性・定量フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['TSTRFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'項目種別');
				printf("<td>%s</td>",SjToUtfConv($row['KMKSBT']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'照合チェック採用フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['SGCHKFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'血清情報影響フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['KSJHFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'希釈測定結果照合フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['KSSGFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'XbarM集計フラグ');
				printf("<td>%s</td>",SjToUtfConv($row['XMSKFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'XbarMチェックフラグ');
				printf("<td>%s</td>",SjToUtfConv($row['XMCHKFLG']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'XbarMカウント数');
				printf("<td>%s</td>",SjToUtfConv($row['XMCOUNT']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'開始年月日');
				printf("<td>%10.10s</td>",SjToUtfConv($row['KAIYMD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'廃止年月日');
				printf("<td>%10.10s</td>",SjToUtfConv($row['HAIYMD']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'変更担当者ＩＤ');
				printf("<td>%s</td>",SjToUtfConv($row['HNKTNTID']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

			printf("<tr>");
				printf("<td>%s</td>",'情報更新日時');
				printf("<td>%10.10s</td>",SjToUtfConv($row['KSNDH']));
				printf("<td>%s</td>",' ');
			printf("</tr>\n",' ');

		}
		printf("</table>\n");
	}
	return 0;
}

?>
