#!/bin/bash
# 推算GFR属性エラーチェックリスト出力

EXECSTS=0

OUTFILE=/apdata/today/file/list/EGFR_$$.sel
PRTFILE=/apdata/today/file/list/EGFR_$$.txt
TMPFILE=/apdata/today/file/list/EGFR_$$.tmp
SELSQL=/home/kea00sys/shell/egfr/egfrsel.sql
UPDSQL=/home/kea00sys/shell/egfr/egfrupd.sql
AWKFILE=/home/kea00sys/shell/egfr/egfr.awk
#/usr/bin/rm ${OUTFILE}

#db2 connect to kea00db user db2inst1 using db2inst1
db2 connect to kea00db9 user kea00dbt using kea00dbt
if [ $? != 0 ]
then
        echo "DBにloginできません"
        exit 1
fi

#抽出SQL実行
db2 -t -f ${SELSQL} > ${OUTFILE}

db2 terminate

#select行のみにする
grep AAAAAAAA ${OUTFILE} > ${TMPFILE}

#スペースを含む項目名の調整
#cat ${TMPFILE} | sed "s/PG 1\/2ﾋ/PG1\/2ﾋ/g" > ${PRTFILE}
#mv ${PRTFILE} ${TMPFILE}

#スペースを1文字だけにする
for ((i=0; i<20;i++))
do
	cat ${TMPFILE} | sed "s/  / /g" > ${PRTFILE}
	mv ${PRTFILE} ${TMPFILE}
done

#awkで整形
awk -f ${AWKFILE} ${TMPFILE} > ${PRTFILE}
#cp ${TMPFILE} ${PRTFILE}
cat ${PRTFILE}

echo -n "印刷しますか？(y/n):"
read yn
if [ "${yn}" = "Y" ] || [ "${yn}" = "y" ]; then
	npdl -15 -a4p < ${PRTFILE} | lp -d prt01 |& iconv -f utf8 -t sjis
fi

# 対象無しの時UPDATEするとエラーになるので回避
if [ -s ${TMPFILE} ]; then

	echo -n "クレアチニンの保留を解除しますか？(y/n):"
	read yn
	if [ "${yn}" = "Y" ] || [ "${yn}" = "y" ]; then
#		db2 connect to kea00db user db2inst1 using db2inst1
		db2 connect to kea00db9 user kea00dbt using kea00dbt
		if [ $? != 0 ]
		then
		        echo "DBにloginできません"
		        exit 1
		fi

		#抽出SQL実行
		db2 -t -f ${UPDSQL}
		if [ $? = 0 ]
		then
		        echo "正常に更新しました"
		else
				echo $?
		fi

		db2 terminate
	fi
fi

exit $EXECSTS
