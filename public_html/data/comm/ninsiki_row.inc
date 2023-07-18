<?php
function ninsiki_row($conn,$utkymd,$irino)
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
			printf("<th nowrap>チェック文字</th>\n");
			printf("<th nowrap>ARACKID</th>\n");
			printf("<th nowrap>ARACKPOS</th>\n");
			printf("<th nowrap>元検体ラックID</th>\n");
			printf("<th nowrap>元検体ラックPOS</th>\n");
			printf("<th nowrap>３IDラック</th>\n");
			printf("<th nowrap>３IDラックPOS</th>\n");
			printf("<th nowrap>複数本取り</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
			printf("<th nowrap>情報登録日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from ninsiki where ";
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
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CHKMJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKID']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ASYRCKPOS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID2POS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID3']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ID3POS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FUKSUHN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KSNDH']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TRKDH']));
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
