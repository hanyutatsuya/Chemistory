# PG比用awkパラメーターファイル
BEGIN {
	cnt = 0
	line = 0
	page = 1
	stamp = strftime("DATE:%Y/%m/%d TIME:%H:%M:%S",systime())
	printf("     PG1/PG2比チェックリスト            ")
	printf("%s  ",stamp)
	printf("Page: %3d\n\n",page)
	printf("      処理日      依頼書No.  項目CD   項目名         結果  FLG  号機   ME-SEQ\n")
	printf("    -------------------------------------------------------------------\n")
}

{
	#分析機SEQが0でないもののみを印字
	if ($9 != "0") {
		cnt = cnt + 1
		line = line + 1
		printf("    %s %s-%s  %s  %-8.8s %8.8s  %s    %s   %s\n",
								$2,substr($3,3,3),substr($3,6,4),$4,$5,$6,$7,substr($8,1,2),$9)
		if ($15 != "0") {
			printf("                         %s  %-8.8s %8.8s  %s    %s   %s\n",$10,$11,$12,$13,substr($14,1,2),$15)
		}
		if ($21 != "0") {
			printf("                         %s  %-8.8s %8.8s  %s    %s   %s\n",$16,$17,$18,$19,substr($20,1,2),$21)
		}
		if ($27 != "0") {
			printf("                         %s  %-8.8s %8.8s  %s    %s   %s\n",$22,$23,$24,$25,substr($26,1,2),$27)
		}
		printf("\n")
	}
	# 10件ごとに改ページ
	if (line > 9) {
		printf("\f")
		page = page + 1
		line = 0
		printf("     PG1/PG2比チェックリスト            ")
		printf("%s  ",stamp)
		printf("Page: %3d\n\n",page)
		printf("      処理日      依頼書No.  項目CD   項目名         結果  FLG  号機   ME-SEQ\n")
		printf("    -------------------------------------------------------------------\n")
	}
}

END {
	if (cnt == 0) {
		printf("                        対象データはありません\n")
	}
	printf("    -----------  E  N  D  ---------------------------------------------\n")
}
