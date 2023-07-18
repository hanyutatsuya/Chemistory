<?php
function kekka_row($conn,$utkymd,$irino)
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
			printf("<th nowrap>検体No</th>\n");
			printf("<th nowrap>検体No桁数F</th>\n");
			printf("<th nowrap>検査G</th>\n");
			printf("<th nowrap>項目CD</th>\n");
			printf("<th nowrap>検査回数</th>\n");
			printf("<th nowrap>検査回数枝番</th>\n");
			printf("<th nowrap>依頼発生元区分</th>\n");
			printf("<th nowrap>依頼区分</th>\n");
			printf("<th nowrap>検査工程区分</th>\n");
			printf("<th nowrap>BML受付年月日</th>\n");
			printf("<th nowrap>依頼書No</th>\n");
			printf("<th nowrap>依頼書No桁数F</th>\n");
			printf("<th nowrap>属性世代No</th>\n");
			printf("<th nowrap>施設CD</th>\n");
			printf("<th nowrap>トレーID</th>\n");
			printf("<th nowrap>トレーPOS</th>\n");
			printf("<th nowrap>ARACKID</th>\n");
			printf("<th nowrap>ARACKPOS</th>\n");
			printf("<th nowrap>親項目CD</th>\n");
			printf("<th nowrap>SECCD</th>\n");
			printf("<th nowrap>分画負荷区分</th>\n");
			printf("<th nowrap>SMPCD</th>\n");
			printf("<th nowrap>分析機区分</th>\n");
			printf("<th nowrap>分析機ライン</th>\n");
			printf("<th nowrap>分析機号機</th>\n");
			printf("<th nowrap>分析機ＳＥＱ</th>\n");
			printf("<th nowrap>分析機エラーSTS</th>\n");
			printf("<th nowrap>測定日時</th>\n");
			printf("<th nowrap>内部項目CD</th>\n");
			printf("<th nowrap>定性・定量F</th>\n");
			printf("<th nowrap>材料CD</th>\n");
			printf("<th nowrap>優先レベル</th>\n");
			printf("<th nowrap>基準値No</th>\n");
			printf("<th nowrap>負荷報告No表示区分</th>\n");
			printf("<th nowrap>特別基準値No</th>\n");
			printf("<th nowrap>特別基準値F</th>\n");
			printf("<th nowrap>非定型負荷時間</th>\n");
			printf("<th nowrap>集検F</th>\n");
			printf("<th nowrap>透析F</th>\n");
			printf("<th nowrap>凍結F</th>\n");
			printf("<th nowrap>実施希釈倍率</th>\n");
			printf("<th nowrap>緊急報告F</th>\n");
			printf("<th nowrap>緊急依頼F</th>\n");
			printf("<th nowrap>緊急依頼ロットNo</th>\n");
			printf("<th nowrap>非照会F</th>\n");
			printf("<th nowrap>非請求F</th>\n");
			printf("<th nowrap>非報告F</th>\n");
			printf("<th nowrap>生データ</th>\n");
			printf("<th nowrap>検査結果１</th>\n");
			printf("<th nowrap>検査結果２</th>\n");
			printf("<th nowrap>検査結果２区分</th>\n");
			printf("<th nowrap>検査結果補足</th>\n");
			printf("<th nowrap>表示結果</th>\n");
			printf("<th nowrap>指数(ＳＤＩ)</th>\n");
			printf("<th nowrap>結果CMT１</th>\n");
			printf("<th nowrap>結果CMT２</th>\n");
			printf("<th nowrap>結果状況CD</th>\n");
			printf("<th nowrap>パニックレンジF</th>\n");
			printf("<th nowrap>検査室パニックレンジF</th>\n");
			printf("<th nowrap>結果換算F</th>\n");
			printf("<th nowrap>結果修正F</th>\n");
			printf("<th nowrap>異常値区分(男)</th>\n");
			printf("<th nowrap>異常値区分(女)</th>\n");
			printf("<th nowrap>異常値区分(不明)</th>\n");
			printf("<th nowrap>特別異常値区分(男)</th>\n");
			printf("<th nowrap>特別異常値区分(女)</th>\n");
			printf("<th nowrap>特別異常値区分(不明)</th>\n");
			printf("<th nowrap>血清情報(乳び）レベル</th>\n");
			printf("<th nowrap>血清情報(乳び）エラーSTS</th>\n");
			printf("<th nowrap>血清情報(溶血) レベル</th>\n");
			printf("<th nowrap>血清情報(溶血) エラーSTS</th>\n");
			printf("<th nowrap>血清情報(etc)  レベル</th>\n");
			printf("<th nowrap>血清情報(etc)  エラーSTS</th>\n");
			printf("<th nowrap>コントロールNo</th>\n");
			printf("<th nowrap>検査ＳＥＱ</th>\n");
			printf("<th nowrap>検査バッチNo</th>\n");
			printf("<th nowrap>プロットNo</th>\n");
			printf("<th nowrap>プロットＳＥＱ</th>\n");
			printf("<th nowrap>データ入力担当者</th>\n");
			printf("<th nowrap>データ入力日時</th>\n");
			printf("<th nowrap>検査完了日時</th>\n");
			printf("<th nowrap>報告日時</th>\n");
			printf("<th nowrap>報告希望時間</th>\n");
			printf("<th nowrap>次回報告予定日</th>\n");
			printf("<th nowrap>次回報告予定時刻</th>\n");
			printf("<th nowrap>フリー結果F</th>\n");
			printf("<th nowrap>画像別紙F</th>\n");
			printf("<th nowrap>補正F</th>\n");
			printf("<th nowrap>結果優先F</th>\n");
			printf("<th nowrap>手入力F</th>\n");
			printf("<th nowrap>採用F</th>\n");
			printf("<th nowrap>検査F</th>\n");
			printf("<th nowrap>レンジチェック</th>\n");
			printf("<th nowrap>相関チェック(WS内)</th>\n");
			printf("<th nowrap>関連チェック</th>\n");
			printf("<th nowrap>分画チェック</th>\n");
			printf("<th nowrap>乳び・溶血チェック</th>\n");
			printf("<th nowrap>履歴チェック</th>\n");
			printf("<th nowrap>照合チェック</th>\n");
			printf("<th nowrap>計算チェック</th>\n");
			printf("<th nowrap>100%チェック</th>\n");
			printf("<th nowrap>透析前後チェック</th>\n");
			printf("<th nowrap>希釈再検チェック</th>\n");
			printf("<th nowrap>校正処理</th>\n");
			printf("<th nowrap>照合NG確定処理</th>\n");
			printf("<th nowrap>相関チェック(WS間)</th>\n");
			printf("<th nowrap>負荷パターンチェック</th>\n");
			printf("<th nowrap>チェック状態F</th>\n");
			printf("<th nowrap>再検F17</th>\n");
			printf("<th nowrap>再検F18</th>\n");
			printf("<th nowrap>再検F19</th>\n");
			printf("<th nowrap>再検F20</th>\n");
			printf("<th nowrap>再検理由CDＡ</th>\n");
			printf("<th nowrap>再検理由CDＢ</th>\n");
			printf("<th nowrap>再検理由CDＣ</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
			printf("<th nowrap>情報登録日時</th>\n");
			printf("<th nowrap>照会結果</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kekka where ";
		$sql = $sql . "utkymd = '$udate' and ";
		$sql = $sql . "irino = '$ino' ";
		$sql = $sql . "knsgrp,oyakmkcd,kmkcd for read only";
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
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKLNE']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKGOK']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKSEQ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKERRSTS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKTDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NBKMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TSTRFLG']));
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
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['JISKSBR']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKIRIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKIRILOTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HSYKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HSKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HHKKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RAWDATA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKKA1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKKA2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKKA2KBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAHSKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HJKKA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SDI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKACMT1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKACMT2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAJKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['PNCRGFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSPNCRGFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAKSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKASSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IJKBNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IJKBNF']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IJKBNN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TBIJKBNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TBIJKBNF']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TBIJKBNN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NBDOLBL']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NBDOERR']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YKDOLBL']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YKDOERR']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ETCLBL']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ETCERR']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CTRLNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSEQ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BTHNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['PLTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['PLTSEQ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['DTNRTTS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['DTNRDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKRDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKKDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKKKBDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZKHKKYYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZKHKKYTME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FRKKAFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['GZBSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HSIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAYSNFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNYRKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SIYFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RENJICFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SOUKN1FLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KANRENFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BUNKKUFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KESSEIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RIREKIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SYOUGOFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KEISANFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['PER100FLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TOUSEKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KISYAKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KOUSEIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SYOUNGFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SOUKN2FLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FUKAPTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIFLG01']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TOBIFLG02']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIFLG03']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIFLG04']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIFLG05']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKRYCDA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKRYCDB']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKRYCDC']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['KSNDH']));
				printf("<td nowrap>%20.20s</td>\n",SjToUtfConv($row['TRKDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKKKA']));
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
