<?php
function kskbrmst_row($conn,$wscode,$kcode)
{
	if (!is_numeric($wscode)) {
		if (strlen($wscode) == 0) {
			$wcode = 0;
		} else {
			printf("<center>\n");
			printf("<h2>検査G入力エラー</h2>\n");
			printf("</center>\n");
			printf("<HR>\n");
			return -1;
		}
	} else {
		if (strlen($wscode) < 5) {
			$wcode = sprintf("%04d",$wscode);
		} else {
			$wcode = sprintf("%d",$wscode);
		}
	}

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
			printf("<th nowarp>分析機区分</th>\n");
			printf("<th nowarp>検査G</th>\n");
			printf("<th nowarp>項目CD</th>\n");
			printf("<th nowarp>希釈倍率</th>\n");
			printf("<th nowarp>希釈下限値</th>\n");
			printf("<th nowarp>希釈上限値</th>\n");
			printf("<th nowarp>分析条件</th>\n");
			printf("<th nowarp>開始年月日</th>\n");
			printf("<th nowarp>廃止年月日</th>\n");
			printf("<th nowarp>情報更新日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kskbrmst where ";
		if ($wcode > 0) {
			$sql = $sql . "knsgrp = '$wcode' and ";
		}
		$sql = $sql . "kmkcd = '$kmcd' ";
		$sql = $sql . "order by knsgrp,kmkcd,bskkbn,ksbr for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['BSKKBN']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KSBR']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KMIN']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['KMAX']));
				printf("<td nowarp>%s</td>\n",SjToUtfConv($row['HNKTNTID']));
				printf("<td nowarp>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td nowarp>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td nowarp>%10.10s</td>\n",$row['KSNDH']);
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
