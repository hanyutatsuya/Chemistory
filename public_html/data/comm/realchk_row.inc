<?php
function realchk_row($conn,$utkymd,$irino)
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
			printf("<th nowrap>ＢＭＬ受付年月日</th>\n");
			printf("<th nowrap>依頼書Ｎｏ</th>\n");
			printf("<th nowrap>依頼書Ｎｏ桁数フラグ</th>\n");
			printf("<th nowrap>属性世代Ｎｏ</th>\n");
			printf("<th nowrap>トレーＩＤ</th>\n");
			printf("<th nowrap>トレーポジション</th>\n");
			printf("<th nowrap>アッセイラックＩＤ</th>\n");
			printf("<th nowrap>アッセイラックポジション</th>\n");
			printf("<th nowrap>分析機区分</th>\n");
			printf("<th nowrap>内部項目コード</th>\n");
			printf("<th nowrap>レンジチェックフラグ</th>\n");
			printf("<th nowrap>相関チェック(WS内)フラグ</th>\n");
			printf("<th nowrap>関連チェックフラグ</th>\n");
			printf("<th nowrap>分画チェックフラグ</th>\n");
			printf("<th nowrap>乳び・溶血チェックフラグ</th>\n");
			printf("<th nowrap>履歴チェックフラグ</th>\n");
			printf("<th nowrap>照合チェックフラグ</th>\n");
			printf("<th nowrap>計算チェックフラグ</th>\n");
			printf("<th nowrap>１００％チェックフラグ</th>\n");
			printf("<th nowrap>透析前後チェックフラグ</th>\n");
			printf("<th nowrap>希釈再検チェックフラグ</th>\n");
			printf("<th nowrap>校正処理フラグ</th>\n");
			printf("<th nowrap>照合NG確定処理フラグ</th>\n");
			printf("<th nowrap>相関チェック(WS間)フラグ</th>\n");
			printf("<th nowrap>負荷パターンチェックフラグ</th>\n");
			printf("<th nowrap>チェック有無フラグ16</th>\n");
			printf("<th nowrap>チェック有無フラグ17</th>\n");
			printf("<th nowrap>チェック有無フラグ18</th>\n");
			printf("<th nowrap>チェック有無フラグ19</th>\n");
			printf("<th nowrap>チェック有無フラグ20</th>\n");
			printf("<th nowrap>レンジチェックパラメータ</th>\n");
			printf("<th nowrap>相関チェック(WS内)パラメータ</th>\n");
			printf("<th nowrap>関連チェックパラメータ</th>\n");
			printf("<th nowrap>分画チェックパラメータ</th>\n");
			printf("<th nowrap>乳び・溶血チェックパラメータ</th>\n");
			printf("<th nowrap>履歴チェックパラメータ</th>\n");
			printf("<th nowrap>照合チェックパラメータ</th>\n");
			printf("<th nowrap>計算チェックパラメータ</th>\n");
			printf("<th nowrap>１００％チェックパラメータ</th>\n");
			printf("<th nowrap>透析前後チェックパラメータ</th>\n");
			printf("<th nowrap>希釈再検チェックパラメータ</th>\n");
			printf("<th nowrap>校正処理パラメータ</th>\n");
			printf("<th nowrap>照合NG確定処理パラメータ</th>\n");
			printf("<th nowrap>相関チェック(WS間)パラメータ</th>\n");
			printf("<th nowrap>負荷パターンチェックパラメータ</th>\n");
			printf("<th nowrap>パラメータ１６</th>\n");
			printf("<th nowrap>パラメータ１７</th>\n");
			printf("<th nowrap>パラメータ１８</th>\n");
			printf("<th nowrap>パラメータ１９</th>\n");
			printf("<th nowrap>パラメータ２０</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from realchk where ";
		$sql = $sql . "utkymd = '$udate' and ";
		$sql = $sql . "irino = '$ino' ";
		$sql = $sql . "order by smpcd,kmkcd for read only";
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
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZSSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TRID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TRPOS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKPOS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NBKMKCD']));
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
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RENJICPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SOUKN1PARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KANRENPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BUNKKUPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KESSEIPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RIREKIPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SYOUGOPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KEISANPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['PER100PARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TOUSEKPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KISYAKPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KOUSEIPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SYOUNGPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SOUKN2PARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FUKAPTPARA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIPARA01']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIPARA02']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIPARA03']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIPARA04']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YOBIPARA05']));
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
