<?php
function kekka_data($conn,$utkymd,$irino)
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
			printf("<th nowrap>検査G</th>\n");
			printf("<th nowrap>項目CD</th>\n");
			printf("<th nowrap>項目名</th>\n");
			printf("<th nowrap>検査回数</th>\n");
			printf("<th nowrap>親項目CD</th>\n");
			printf("<th nowrap>生データ</th>\n");
			printf("<th nowrap>検査結果１</th>\n");
			printf("<th nowrap>検査結果２</th>\n");
			printf("<th nowrap>検査結果２区分</th>\n");
			printf("<th nowrap>検査結果補足</th>\n");
			printf("<th nowrap>表示結果</th>\n");
			printf("<th nowrap>結果CMT１</th>\n");
			printf("<th nowrap>結果CMT２</th>\n");
			printf("<th nowrap>結果状況CD</th>\n");
			printf("<th nowrap>TBF</th>\n");
			printf("<th nowrap>MEKBN</th>\n");
			printf("<th nowrap>MELine</th>\n");
			printf("<th nowrap>GOKI</th>\n");
			printf("<th nowrap>ME-SEQ</th>\n");
			printf("<th nowrap>基準値No</th>\n");
			printf("<th nowrap>PANIC</th>\n");
			printf("<th nowrap>検査室P</th>\n");
			printf("<th nowrap>結果換算F</th>\n");
			printf("<th nowrap>結果修正F</th>\n");
			printf("<th nowrap>異常値区分(男)</th>\n");
			printf("<th nowrap>異常値区分(女)</th>\n");
			printf("<th nowrap>異常値区分(不明)</th>\n");
			printf("<th nowrap>コントロールNo</th>\n");
			printf("<th nowrap>検査ＳＥＱ</th>\n");
			printf("<th nowrap>補正F</th>\n");
			printf("<th nowrap>結果優先F</th>\n");
			printf("<th nowrap>手入力F</th>\n");
			printf("<th nowrap>採用F</th>\n");
			printf("<th nowrap>検査F</th>\n");
			printf("<th nowrap>照会結果</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select ka.*,km.* from kekka ka,kmkmst km where ";
		$sql = $sql . "ka.utkymd = '$udate' and ";
		$sql = $sql . "ka.irino = '$ino' and ";
		$sql = $sql . "km.knsgrp = ka.knsgrp and ";
		$sql = $sql . "km.kmkcd = ka.kmkcd ";
		$sql = $sql . "order by ka.knssu,ka.knsgrp,ka.oyakmkcd,ka.kmkcd for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['UTKYMD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IRINO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KMKRS']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSU']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['OYAKMKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['RAWDATA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKKA1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKKA2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSKKA2KBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAHSKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HJKKA']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKACMT1']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKACMT2']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAJKCD']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BKFKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKKBN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKLNE']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKGOK']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['BSKSEQ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KJNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['PNCRGFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSPNCRGFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAKSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKASSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IJKBNM']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IJKBNF']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['IJKBNN']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['CTRLNO']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSSEQ']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['HSIFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KKAYSNFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['TNYRKFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SIYFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['KNSFLG']));
				printf("<td nowrap>%s</td>\n",SjToUtfConv($row['SKKKA']));
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
