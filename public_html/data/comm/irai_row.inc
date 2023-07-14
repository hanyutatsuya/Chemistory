<?php
function irai_row($conn,$utkymd,$irino)
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
			printf("<th nowrap>ＢＭＬ受付年月日</th>\n");
			printf("<th nowrap>依頼書Ｎｏ</th>\n");
			printf("<th nowrap>依頼書Ｎｏ桁数フラグ</th>\n");
			printf("<th nowrap>属性世代Ｎｏ</th>\n");
			printf("<th nowrap>検査グループ</th>\n");
			printf("<th nowrap>項目コード</th>\n");
			printf("<th nowrap>依頼発生元区分</th>\n");
			printf("<th nowrap>依頼区分</th>\n");
			printf("<th nowrap>検査工程区分</th>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>検体Ｎｏ</th>\n");
			printf("<th nowrap>検体Ｎｏ桁数フラグ</th>\n");
			printf("<th nowrap>チェック文字</th>\n");
			printf("<th nowrap>推定材料コード</th>\n");
			printf("<th nowrap>項目略称</th>\n");
			printf("<th nowrap>親項目コード</th>\n");
			printf("<th nowrap>サンプリングコード</th>\n");
			printf("<th nowrap>セット項目コード</th>\n");
			printf("<th nowrap>処理内容コード</th>\n");
			printf("<th nowrap>セクションコード</th>\n");
			printf("<th nowrap>出荷チェックフラグ</th>\n");
			printf("<th nowrap>分画負荷区分</th>\n");
			printf("<th nowrap>優先レベル</th>\n");
			printf("<th nowrap>集検フラグ</th>\n");
			printf("<th nowrap>追加フラグ</th>\n");
			printf("<th nowrap>削除フラグ</th>\n");
			printf("<th nowrap>条件追加フラグ</th>\n");
			printf("<th nowrap>基準値ＮＯ</th>\n");
			printf("<th nowrap>負荷報告ＮＯ表示区分</th>\n");
			printf("<th nowrap>特別基準値ＮＯ</th>\n");
			printf("<th nowrap>特別基準値フラグ</th>\n");
			printf("<th nowrap>非定型負荷時間</th>\n");
			printf("<th nowrap>透析フラグ</th>\n");
			printf("<th nowrap>凍結フラグ</th>\n");
			printf("<th nowrap>分注区分</th>\n");
			printf("<th nowrap>尿分注区分</th>\n");
			printf("<th nowrap>検査開始予定日</th>\n");
			printf("<th nowrap>検査完了予定日</th>\n");
			printf("<th nowrap>検査完了予定時間</th>\n");
			printf("<th nowrap>緊急報告フラグ</th>\n");
			printf("<th nowrap>緊急依頼フラグ</th>\n");
			printf("<th nowrap>緊急依頼ロットＮｏ</th>\n");
			printf("<th nowrap>緊急対応受付ＩＤ</th>\n");
			printf("<th nowrap>検査回数</th>\n");
			printf("<th nowrap>オーダ作成フラグ</th>\n");
			printf("<th nowrap>予定希釈倍率</th>\n");
			printf("<th nowrap>報告状況フラグ</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
			printf("<th nowrap>情報登録日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from irai where ";
		$sql = $sql . "utkymd = '$udate' and ";
		$sql = $sql . "irino = '$ino' ";
		$sql = $sql . "knsgrp,oyakmkcd,kmkcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZSSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIHSMKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KSKTKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRIYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CHKMJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['STSRCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKRS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['OYAKMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SMPCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SETKMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRINYCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SECCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKCHKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BKFKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YSNLBL']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SJFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['JKTKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FKHKKNOHJKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TBKJNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TBKJFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HTKFKHMS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TSKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TKTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BNCKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NBNCKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKISYYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKRYYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKRYTME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKHKKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKIRIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKIRILOTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKTOUTKID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ODRSSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YTIKSBR']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HHKJKFLG']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['KSNDH']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['TRKDH']));
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
