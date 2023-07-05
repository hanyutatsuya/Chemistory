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
			printf("<th>項目CD</th>\n");
			printf("<th>基準値Ｎｏ</th>\n");
			printf("<th>世代Ｎｏ</th>\n");
			printf("<th>材料CD</th>\n");
			printf("<th>年齢範囲区分</th>\n");
			printf("<th>その他区分</th>\n");
			printf("<th>日齢(下)</th>\n");
			printf("<th>日齢(上)</th>\n");
			printf("<th>男・基準値(下)</th>\n");
			printf("<th>男・基準値(上)</th>\n");
			printf("<th>女・基準値(下)</th>\n");
			printf("<th>女・基準値(上)</th>\n");
			printf("<th>不明・基準値(下)</th>\n");
			printf("<th>不明・基準値(上)</th>\n");
			printf("<th>小数点桁数</th>\n");
			printf("<th>単位(カナ)</th>\n");
			printf("<th>単位(漢字)</th>\n");
			printf("<th>開始年月日</th>\n");
			printf("<th>廃止年月日</th>\n");
			printf("<th>変更担当者ＩＤ</th>\n");
			printf("<th>情報更新日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kjnmst where ";
		$sql = $sql . "kmkcd = '$kmcd' ";
		$sql = $sql . "order by kmkcd,kjno for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJNO']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJSDINO']));
				printf("<td>%s</td>\n",SjToUtfConv($row['ZRCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['AGERNGKBN']));
				printf("<td>%s</td>\n",SjToUtfConv($row['ETCKBN']));
				printf("<td>%s</td>\n",SjToUtfConv($row['NICHILW']));
				printf("<td>%s</td>\n",SjToUtfConv($row['NICHIHI']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJNMLW']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJNMHI']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJNFLW']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJNFHI']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJNELW']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJNEHI']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KJSSTNKSU']));
				printf("<td>%s</td>\n",SjToUtfConv($row['TANKN']));
				printf("<td>%s</td>\n",SjToUtfConv($row['TANKJ']));
				printf("<td>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td>%s</td>\n",$row['HNKTNTID']);
				printf("<td>%10.10s</td>\n",$row['KSNDH']);
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
