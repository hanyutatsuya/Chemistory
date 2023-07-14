<?php
function kenorder_row($conn,$utkymd,$irino)
{
	if (!is_numeric($utkymd)) {
		printf("<center>\n");
		printf("<h2>受付日入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
		}
	} else {
		if (strlen($utkymd) != 8) {
			printf("<center>\n");
			printf("<h2>受付日入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
			return -1;
		} else {
			if (ymd_check($utkymd) == false) {
				printf("<center>\n");
				printf("<h2>受付日フォーマットエラー</h2>\n");
				printf("</center>\n");
				printf("<HR>\n");
				return -1;
			} else {
				$udate ymd_edit($utkymd);
			}
		}
	}

	if (!is_numeric($irino)) {
		if (strlen($irino) == 0) {
			return 0;
		} else {
			printf("<center>\n");
			printf("<h2>依頼書№入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
			return -1;
		}
	} else {
		$ino = sprintf("00%07d00",$irino);
	}

	printf("<table align=\"left\" bgcolor = \"white\" border>\n");
		printf("<tr>\n");
			printf("<th nowrap>検査開始日</th>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>検体Ｎｏ</th>\n");
			printf("<th nowrap>検体Ｎｏ桁数フラグ</th>\n");
			printf("<th nowrap>検査グループ</th>\n");
			printf("<th nowrap>項目コード</th>\n");
			printf("<th nowrap>検査回数</th>\n");
			printf("<th nowrap>検査回数枝番</th>\n");
			printf("<th nowrap>依頼発生元区分</th>\n");
			printf("<th nowrap>依頼区分</th>\n");
			printf("<th nowrap>検査工程区分</th>\n");
			printf("<th nowrap>ＢＭＬ受付年月日</th>\n");
			printf("<th nowrap>依頼書Ｎｏ</th>\n");
			printf("<th nowrap>依頼書Ｎｏ桁数フラグ</th>\n");
			printf("<th nowrap>属性世代Ｎｏ</th>\n");
			printf("<th nowrap>施設コード</th>\n");
			printf("<th nowrap>トレーＩＤ</th>\n");
			printf("<th nowrap>トレーポジション</th>\n");
			printf("<th nowrap>アッセイラックＩＤ</th>\n");
			printf("<th nowrap>アッセイラックポジション</th>\n");
			printf("<th nowrap>親項目コード</th>\n");
			printf("<th nowrap>セクションコード</th>\n");
			printf("<th nowrap>分画負荷区分</th>\n");
			printf("<th nowrap>サンプリングコード</th>\n");
			printf("<th nowrap>分析機区分</th>\n");
			printf("<th nowrap>内部項目コード</th>\n");
			printf("<th nowrap>材料コード</th>\n");
			printf("<th nowrap>優先レベル</th>\n");
			printf("<th nowrap>基準値ＮＯ</th>\n");
			printf("<th nowrap>負荷報告ＮＯ表示区分</th>\n");
			printf("<th nowrap>特別基準値ＮＯ</th>\n");
			printf("<th nowrap>特別基準値フラグ</th>\n");
			printf("<th nowrap>非定型負荷時間</th>\n");
			printf("<th nowrap>集検フラグ</th>\n");
			printf("<th nowrap>透析フラグ</th>\n");
			printf("<th nowrap>凍結フラグ</th>\n");
			printf("<th nowrap>予定希釈倍率</th>\n");
			printf("<th nowrap>緊急報告フラグ</th>\n");
			printf("<th nowrap>緊急依頼フラグ</th>\n");
			printf("<th nowrap>緊急依頼ロットＮｏ</th>\n");
			printf("<th nowrap>身長</th>\n");
			printf("<th nowrap>体重</th>\n");
			printf("<th nowrap>体重区分</th>\n");
			printf("<th nowrap>性別区分</th>\n");
			printf("<th nowrap>生年月日</th>\n");
			printf("<th nowrap>生年月日区分</th>\n");
			printf("<th nowrap>年齢</th>\n");
			printf("<th nowrap>年齢区分</th>\n");
			printf("<th nowrap>採取時間</th>\n");
			printf("<th nowrap>採取年月日</th>\n");
			printf("<th nowrap>蓄尿時間</th>\n");
			printf("<th nowrap>蓄尿時間区分</th>\n");
			printf("<th nowrap>蓄尿量</th>\n");
			printf("<th nowrap>蓄尿量区分</th>\n");
			printf("<th nowrap>検査ＳＥＱ</th>\n");
			printf("<th nowrap>検査バッチＮｏ</th>\n");
			printf("<th nowrap>検査状況フラグ</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kenorder where ";
		$sql = $sql . "utkymd = '$udate' and ";
		$sql = $sql . "irino = '$ino' ";
		$sql = $sql . "order by knsgrp,kmkcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKISYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRIYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSUEDA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIHSMKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KSKTKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZSSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TRID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TRPOS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKPOS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['OYAKMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SECCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BKFKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SMPCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NBKMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZRCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YSNLBL']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FKHKKNOHJKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TBKJNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TBKJFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HTKFKHMS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TSKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TKTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YTIKSBR']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKIRIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKIRILOTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SC']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TJTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SBTKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BIRTHDAY']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BIRTHDAYKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AGE']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AGEKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNTME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNRYO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNRYOTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSEQ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BTHNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSJKFLG']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['KSNDH']));
			printf("</tr>\n");
		}
		printf("</table>\n");
	}
	catch (Exception $ex) {
		GetDBErrMsg($ex);
	}

	return 0;
}

?>
