#!/bin/bash
# PG1/2比チェックリスト出力

EXECSTS=0

OUTFILE=/apdata/today/file/list/PG12_$$.sel
PRTFILE=/apdata/today/file/list/PG12_$$.txt
TMPFILE=/apdata/today/file/list/PG12_$$.tmp
SQLFILE=/home/kea00sys/shell/keisan/pg12.sql
AWKFILE=/home/kea00sys/shell/keisan/pg12.awk
#/usr/bin/rm ${OUTFILE}

db2 connect to kea00db user db2inst1 using db2inst1
if [ $? != 0 ]
then
        echo "DBにloginできません"
        exit 1
fi

#抽出SQL実行
db2 -t -f ${SQLFILE} > ${OUTFILE}

db2 terminate

#select行のみにする
grep AAAAAAAA ${OUTFILE} > ${TMPFILE}

#スペースを含む項目名の調整
cat ${TMPFILE} | sed "s/PG 1\/2ﾋ/PG1\/2ﾋ/g" > ${PRTFILE}
mv ${PRTFILE} ${TMPFILE}

#スペースを1文字だけにする
for ((i=0; i<20;i++))
do
	cat ${TMPFILE} | sed "s/  / /g" > ${PRTFILE}
	mv ${PRTFILE} ${TMPFILE}
done

#awkで整形
awk -f ${AWKFILE} ${TMPFILE} > ${PRTFILE}
cat ${PRTFILE}

read -p "印刷しますか？(y/n):" yn
case "$yn" in
	[yY]*)
		echo "OK";;
	*)
		echo "終了します"
esac

exit $EXECSTS
