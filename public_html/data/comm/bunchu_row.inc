<?php
function bunchu_row($conn,$utkymd,$irino)
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
			printf("<th nowrap>BML受付年月日</th>\n");
			printf("<th nowrap>依頼書No</th>\n");
			printf("<th nowrap>依頼書No桁数F</th>\n");
			printf("<th nowrap>属性世代No</th>\n");
			printf("<th nowrap>処理日</th>\n");
			printf("<th nowrap>検体No</th>\n");
			printf("<th nowrap>検体No桁数F</th>\n");
			printf("<th nowrap>SMPCD</th>\n");
			printf("<th nowrap>項目CD</th>\n");
			printf("<th nowrap>SMPCD内位置No</th>\n");
			printf("<th nowrap>チェック文字</th>\n");
			printf("<th nowrap>トレーID</th>\n");
			printf("<th nowrap>トレーPOS</th>\n");
			printf("<th nowrap>ARACKID</th>\n");
			printf("<th nowrap>ARACKPOS</th>\n");
			printf("<th nowrap>元検体ラックID</th>\n");
			printf("<th nowrap>元検体POS</th>\n");
			printf("<th nowrap>性別区分</th>\n");
			printf("<th nowrap>年齢</th>\n");
			printf("<th nowrap>年齢区分</th>\n");
			printf("<th nowrap>蓄尿時間</th>\n");
			printf("<th nowrap>蓄尿時間区分</th>\n");
			printf("<th nowrap>蓄尿量</th>\n");
			printf("<th nowrap>蓄尿量区分</th>\n");
			printf("<th nowrap>施設CD</th>\n");
			printf("<th nowrap>営業所CD</th>\n");
			printf("<th nowrap>分注機ID</th>\n");
			printf("<th nowrap>状態F</th>\n");
			printf("<th nowrap>検査種類</th>\n");
			printf("<th nowrap>治験F</th>\n");
			printf("<th nowrap>特定・緊急F</th>\n");
			printf("<th nowrap>分注結果</th>\n");
			printf("<th nowrap>ソートキー</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
			printf("<th nowrap>情報登録日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from bunchu where ";
		$sql = $sql . "utkymd = '$udate' and ";
		$sql = $sql . "irino = '$ino' ";
		$sql = $sql . "order by smpcd,kmkcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRIKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZSSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRIYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNTKETFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SMPCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SMPCDITNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CHKMJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TRID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TRPOS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKPOS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID2POS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SBTKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AGE']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AGEKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNTME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNRYO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNRYOTNI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ECD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BCKID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['JTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSYR']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TKNFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TTKKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BNCKKA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SRTKEY']));
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
