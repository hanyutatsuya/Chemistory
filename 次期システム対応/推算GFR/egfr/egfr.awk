# PG比用awkパラメーターファイル
BEGIN {
	cnt = 0
	line = 0
	page = 1
	stamp = strftime("DATE:%Y/%m/%d TIME:%H:%M:%S",systime())
	printf("     推算GFRエラーチェックリスト        ")
	printf("%s  ",stamp)
	printf("Page: %3d\n\n",page)
	printf("      処理日      依頼書No.  項目CD   項目名         結果  FLG     項目CD   項目名         結果  FLG\n")
	printf("    ------------------------------------------------------------------------------------------------\n")
}

{
	#分析機SEQが0でないもののみを印字
	if ($9 != "0") {
		cnt = cnt + 1
		line = line + 1
		printf("    %s %s-%s  %s  %-8.8s %8.8s  %s    %s  %-8.8s %8.8s  %s\n",
					$2,substr($3,3,3),substr($3,6,4),$4,$5,$6,$7,$8,$9,$10,$11)

		if ((line % 5) == 0) {
			printf("\n")
		}

	}
	# 50件ごとに改ページ
	if (line >= 50) {
		printf("\f")
		page = page + 1
		line = 0
		printf("     推算GFRエラーチェックリスト        ")
		printf("%s  ",stamp)
		printf("Page: %3d\n\n",page)
		printf("      処理日      依頼書No.  項目CD   項目名         結果  FLG     項目CD   項目名         結果  FLG\n")
		printf("    ------------------------------------------------------------------------------------------------\n")
	}
}

END {
	if (cnt == 0) {
		printf("                        対象データはありません\n")
	}
	printf("    -----------  E  N  D  ---------------------------------------------\n")
}
