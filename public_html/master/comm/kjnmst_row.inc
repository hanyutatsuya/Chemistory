<?php
function kjnmst_row($conn,$wscode,$kcode)
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
	}

	printf("<table align=\"left\" bgcolor = \"white\" border>\n");
		printf("<tr>\n");
			printf("<th nowrap>項目CD</th>\n");
			printf("<th nowrap>基準値Ｎｏ</th>\n");
			printf("<th nowrap>世代Ｎｏ</th>\n");
			printf("<th nowrap>材料CD</th>\n");
			printf("<th nowrap>年齢範囲区分</th>\n");
			printf("<th nowrap>その他区分</th>\n");
			printf("<th nowrap>日齢(下)</th>\n");
			printf("<th nowrap>日齢(上)</th>\n");
			printf("<th nowrap>男・基準値(下)</th>\n");
			printf("<th nowrap>男・基準値(上)</th>\n");
			printf("<th nowrap>女・基準値(下)</th>\n");
			printf("<th nowrap>女・基準値(上)</th>\n");
			printf("<th nowrap>不明・基準値(下)</th>\n");
			printf("<th nowrap>不明・基準値(上)</th>\n");
			printf("<th nowrap>小数点桁数</th>\n");
			printf("<th nowrap>単位(カナ)</th>\n");
			printf("<th nowrap>単位(漢字)</th>\n");
			printf("<th nowrap>開始年月日</th>\n");
			printf("<th nowrap>廃止年月日</th>\n");
			printf("<th nowrap>変更担当者ＩＤ</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kjnmst where ";
		$sql = $sql . "kmkcd = '$kmcd' ";
		$sql = $sql . "order by kmkcd,kjno for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJSDINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ZRCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['AGERNGKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['ETCKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NICHILW']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['NICHIHI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNMLW']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNMHI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNFLW']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNFHI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNELW']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNEHI']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJSSTNKSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TANKN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TANKJ']));
				printf("<td nowrap>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td nowrap>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td nowrap>%s</td>\n",$row['HNKTNTID']);
				printf("<td nowrap>%10.10s</td>\n",$row['KSNDH']);
			printf("</tr>\n");
		}
	}
	catch (Exception $ex) {
		GetDBErrMsg($ex);
	}
	printf("</table>\n");

	return 0;
}

?>
