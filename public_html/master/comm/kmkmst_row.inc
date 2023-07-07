<?php
function kmkmst_row($conn,$wscode,$kcode)
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
			printf("<th nowrap>検査G</th>\n");
			printf("<th nowrap>項目CD</th>\n");
			printf("<th nowrap>項目正式名称(カナ)</th>\n");
			printf("<th nowrap>項目正式名称(漢字)</th>\n");
			printf("<th nowrap>項目略称(カナ)</th>\n");
			printf("<th nowrap>項目略称(漢字)</th>\n");
			printf("<th nowrap>項目名(英語)</th>\n");
			printf("<th nowrap>サンプリングCD</th>\n");
			printf("<th nowrap>親項目CD</th>\n");
			printf("<th nowrap>子ＲＲＮ</th>\n");
			printf("<th nowrap>SECCD </th>\n");
			printf("<th nowrap>小数点桁数</th>\n");
			printf("<th nowrap>負荷分画区分</th>\n");
			printf("<th nowrap>凍結F</th>\n");
			printf("<th nowrap>透析F</th>\n");
			printf("<th nowrap>ＬＴ未満F</th>\n");
			printf("<th nowrap>夜間検査F</th>\n");
			printf("<th nowrap>表示順</th>\n");
			printf("<th nowrap>開始年月日</th>\n");
			printf("<th nowrap>廃止年月日</th>\n");
			printf("<th nowrap>変更担当者ＩＤ</th>\n");
			printf("<th nowrap>情報更新日時</th>\n");
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
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKNMJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKRS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKRSJ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKNME']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SMPCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['OYAKMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KORRN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SECCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SSTNKSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['FKBNKKB']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TSKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TKTFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['LTMMNFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['YKNKNSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HYJIJN']));
				printf("<td nowrap>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td nowrap>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td nowrap>%s</td>\n",$row['HNKTNTID']);
				printf("<td nowrap>%10.10s</td>\n",$row['KSNDH']);
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
