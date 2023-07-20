<?php
function realchk_row($conn,$utkymd,$irino)
{
	if (!is_numeric($utkymd)) {
		printf("<center>\n");
		printf("<h2>受付日入力エラー</h2>\n");
		printf("</center>\n");
		printf("<HR>\n");
		return -1;
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
				$udate = ymd_edit($utkymd);
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
			printf("<th nowrap>BML受付年月日</th>\n");
			printf("<th nowrap>依頼書No</th>\n");
			printf("<th nowrap>依頼書No桁数F</th>\n");
			printf("<th nowrap>属性世代No</th>\n");
			printf("<th nowrap>トレーID</th>\n");
			printf("<th nowrap>トレーPOS</th>\n");
			printf("<th nowrap>ARACKID</th>\n");
			printf("<th nowrap>ARACKPOS</th>\n");
			printf("<th nowrap>分析機区分</th>\n");
			printf("<th nowrap>内部項目CD</th>\n");
			printf("<th nowrap>レンジチェックF</th>\n");
			printf("<th nowrap>相関チェック(WS内)F</th>\n");
			printf("<th nowrap>関連チェックF</th>\n");
			printf("<th nowrap>分画チェックF</th>\n");
			printf("<th nowrap>乳び・溶血チェックF</th>\n");
			printf("<th nowrap>履歴チェックF</th>\n");
			printf("<th nowrap>照合チェックF</th>\n");
			printf("<th nowrap>計算チェックF</th>\n");
			printf("<th nowrap>100%%チェックF</th>\n");
			printf("<th nowrap>透析前後チェックF</th>\n");
			printf("<th nowrap>希釈再検チェックF</th>\n");
			printf("<th nowrap>校正処理F</th>\n");
			printf("<th nowrap>照合NG確定処理F</th>\n");
			printf("<th nowrap>相関チェック(WS間)F</th>\n");
			printf("<th nowrap>負荷パターンチェックF</th>\n");
			printf("<th nowrap>チェック有無F16</th>\n");
			printf("<th nowrap>チェック有無F17</th>\n");
			printf("<th nowrap>チェック有無F18</th>\n");
			printf("<th nowrap>チェック有無F19</th>\n");
			printf("<th nowrap>チェック有無F20</th>\n");
			printf("<th nowrap>レンジチェックパラメータ</th>\n");
			printf("<th nowrap>相関チェック(WS内)パラメータ</th>\n");
			printf("<th nowrap>関連チェックパラメータ</th>\n");
			printf("<th nowrap>分画チェックパラメータ</th>\n");
			printf("<th nowrap>乳び・溶血チェックパラメータ</th>\n");
			printf("<th nowrap>履歴チェックパラメータ</th>\n");
			printf("<th nowrap>照合チェックパラメータ</th>\n");
			printf("<th nowrap>計算チェックパラメータ</th>\n");
			printf("<th nowrap>100%%チェックパラメータ</th>\n");
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
		$sql = $sql . "order by knssu,knsgrp,kmkcd for read only";
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
