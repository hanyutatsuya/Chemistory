<?php
function kmkmst_row($conn,$wscode,$kcode)
{
	if (!is_numeric($wscode)) {
		if (strlen($wscode) == 0) {
			$wcode = 0;
		} else {
			printf("<center>\n");
			printf("<h2>検査グループ入力エラー</h2>\n");
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
			printf("<h2>項目コード入力エラー</h2>\n");
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
			printf("<th>検査グループ</th>\n");
			printf("<th>項目コード</th>\n");
			printf("<th>項目正式名称(カナ)</th>\n");
			printf("<th>項目正式名称(漢字)</th>\n");
			printf("<th>項目略称(カナ)</th>\n");
			printf("<th>項目略称(漢字)</th>\n");
			printf("<th>項目名(英語)</th>\n");
			printf("<th>サンプリングコード</th>\n");
			printf("<th>親項目コード</th>\n");
			printf("<th>子ＲＲＮ</th>\n");
			printf("<th>セクションコード </th>\n");
			printf("<th>小数点桁数</th>\n");
			printf("<th>負荷分画区分</th>\n");
			printf("<th>凍結フラグ</th>\n");
			printf("<th>透析フラグ</th>\n");
			printf("<th>ＬＴ未満フラグ</th>\n");
			printf("<th>夜間検査フラグ</th>\n");
			printf("<th>表示順</th>\n");
			printf("<th>開始年月日</th>\n");
			printf("<th>廃止年月日</th>\n");
			printf("<th>変更担当者ＩＤ</th>\n");
			printf("<th>情報更新日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from kmkmst where ";
		if ($wcode > 0) {
			$sql = $sql . "knsgrp = '$wcode' and ";
		}
		$sql = $sql . "kmkcd = '$kmcd' ";
		$sql = $sql . "order by knsgrp,oyakmkcd,kmkcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKNM']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKNMJ']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKRS']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKRSJ']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKNME']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SMPCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['OYAKMKCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KORRN']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SECCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SSTNKSU']));
				printf("<td>%s</td>\n",SjToUtfConv($row['FKBNKKB']));
				printf("<td>%s</td>\n",SjToUtfConv($row['TSKFLG']));
				printf("<td>%s</td>\n",SjToUtfConv($row['TKTFLG']));
				printf("<td>%s</td>\n",SjToUtfConv($row['LTMMNFLG']));
				printf("<td>%s</td>\n",SjToUtfConv($row['YKNKNSFLG']));
				printf("<td>%s</td>\n",SjToUtfConv($row['HYJIJN']));
				printf("<td>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td>%s</td>\n",$row['HNKTNTID']);
				printf("<td>%10.10s</td>\n",$row['KSNDH']);
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
