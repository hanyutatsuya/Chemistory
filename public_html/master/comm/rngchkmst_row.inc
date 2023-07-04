<?php
function rngchkmst_row($conn,$wscode,$kcode)
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

	printf("<table align=\"center\" bgcolor = \"white\" border>\n");
		printf("<tr>\n");
			printf("<th>範囲区分</th>\n");
			printf("<th>検査グループ</th>\n");
			printf("<th>項目コード</th>\n");
			printf("<th>材料コード</th>\n");
			printf("<th>施設コード</th>\n");
			printf("<th>性別</th>\n");
			printf("<th>上下限区分</th>\n");
			printf("<th>許容区分</th>\n");
			printf("<th>レンジ上限</th>\n");
			printf("<th>レンジ下限</th>\n");
			printf("<th>開始年月日</th>\n");
			printf("<th>廃止年月日</th>\n");
			printf("<th>変更担当者ＩＤ</th>\n");
			printf("<th>情報更新日時</th>\n");
		printf("</tr>\n");

	try {
		$sql = "select * from rngchkmst where ";
		if ($wcode > 0) {
			$sql = $sql . "knsgrp = '$wcode' and ";
		}
		$sql = $sql . "kmkcd = '$kmcd' ";
		$sql = $sql . "order by knsgrp,kmkcd,hnikbn,zaicd,sstcd,sbt for read only";
		foreach ($conn->query($sql) as $row) {
			printf("<tr>\n");
				printf("<td>%s</td>\n",SjToUtfConv($row['HNIKBN']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KNSGRP']));
				printf("<td>%s</td>\n",SjToUtfConv($row['KMKCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['ZAICD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SSTCD']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SBT']));
				printf("<td>%s</td>\n",SjToUtfConv($row['SSA']));
				printf("<td>%s</td>\n",SjToUtfConv($row['ZEN_KYOYOU']));
				printf("<td>%s</td>\n",SjToUtfConv($row['HRNG']));
				printf("<td>%s</td>\n",SjToUtfConv($row['LRNG']));
				printf("<td>%10.10s</td>\n",$row['KAIYMD']);
				printf("<td>%10.10s</td>\n",$row['HAIYMD']);
				printf("<td>%s</td>\n",$row['HNKTNTID']);
				printf("<td>%20.20s</td>\n",$row['KSNDH']);
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
