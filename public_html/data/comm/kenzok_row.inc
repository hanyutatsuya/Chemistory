<?php
function kenzok_row($conn,$utkymd,$irino)
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
			printf("<th nowrap>BML受付年月日</th>\n");
			printf("<th nowrap>依頼書No</th>\n");
			printf("<th nowrap>依頼書No桁数F</th>\n");
			printf("<th nowrap>属性世代No</th>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>検体No</th>\n");
			printf("<th nowrap>検体No桁数F</th>\n");
			printf("<th nowrap>検査実施ラボCD</th>\n");
			printf("<th nowrap>検体属性世代No</th>\n");
			printf("<th nowrap>検体到着予定日</th>\n");
			printf("<th nowrap>複数材料グループ</th>\n");
			printf("<th nowrap>依頼検体量</th>\n");
			printf("<th nowrap>依頼検体量単位</th>\n");
			printf("<th nowrap>現検体量</th>\n");
			printf("<th nowrap>現検体量単位</th>\n");
			printf("<th nowrap>チェック文字</th>\n");
			printf("<th nowrap>理由CD</th>\n");
			printf("<th nowrap>容器CD</th>\n");
			printf("<th nowrap>非定型負荷依頼</th>\n");
			printf("<th nowrap>優先F</th>\n");
			printf("<th nowrap>検体フリーCMT改めF</th>\n");
			printf("<th nowrap>容器材料CD</th>\n");
			printf("<th nowrap>紐付け材料CD</th>\n");
			printf("<th nowrap>検体状態F</th>\n");
			printf("<th nowrap>検体凍結区分</th>\n");
			printf("<th nowrap>非分注F</th>\n");
			printf("<th nowrap>検体属性修正F</th>\n");
			printf("<th nowrap>検体属性登録日時</th>\n");
			printf("<th nowrap>検体属性修正日時</th>\n");
			printf("<th nowrap>サテライト内検体属性修正日時</th>\n");
			printf("<th nowrap>サテライト内検体属性修正端末IP</th>\n");
			printf("<th nowrap>サテライト内検体属性修正入力者</th>\n");
			printf("<th nowrap>新旧ラベルF</th>\n");
			printf("<th nowrap>材料CD</th>\n");
			printf("<th nowrap>採取時間</th>\n");
			printf("<th nowrap>採取年月日</th>\n");
			printf("<th nowrap>蓄尿時間</th>\n");
			printf("<th nowrap>蓄尿時間区分</th>\n");
			printf("<th nowrap>蓄尿量</th>\n");
			printf("<th nowrap>蓄尿量区分</th>\n");
			printf("<th nowrap>採取部位</th>\n");
			printf("<th nowrap>採取方法</th>\n");
			printf("<th nowrap>返却F</th>\n");
			printf("<th nowrap>元処理日</th>\n");
			printf("<th nowrap>元検体No</th>\n");
			printf("<th nowrap>２次ID</th>\n");
			printf("<th nowrap>２次POS</th>\n");
			printf("<th nowrap>３次ID</th>\n");
			printf("<th nowrap>３次POS</th>\n");
			printf("<th nowrap>収納トレーNo</th>\n");
			printf("<th nowrap>収納棚No</th>\n");
			printf("<th nowrap>認識対象外F</th>\n");
			printf("<th nowrap>保管状況</th>\n");
			printf("<th nowrap>保管状況更新日時</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
			printf("<th nowrap>情報登録日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kenzok where ";
		$sql = $sql . "utkymd = '$udate' and ";
		$sql = $sql . "irino = '$ino' ";
		$sql = $sql . "order by sriymd,kntno for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZSSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRIYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSGSLBCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTZSSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTTCYYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FSZRGRP']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKNTRYO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKNTRYOTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['GNKNTRYO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['GNKNTRYOTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CHKMJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RUCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HTKFKIRI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YSNFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTFRFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YKZRCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HZZRCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTJTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTTKTKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HBNCFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTZSSSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTZSTRDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTZSSSDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['STLKNTZSSSDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['STLKNTZSSSIP']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['STLKNTZSSSSYAID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKLBLFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZRCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNTME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNRYO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNRYOTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSBI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSHHU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['MSRIYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['MKNTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID2POS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID3']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID3POS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SNTRNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SNTNNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NSTSGFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKNJK']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HKNJKKSNDH']));
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
