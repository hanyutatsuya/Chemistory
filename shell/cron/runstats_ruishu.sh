#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#######################################################################
#  累積、集計テーブルにrunstatをかける
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

cd /home/kea00sys/shell/cron

db2 CONNECT TO kea00dbn USER db2inst1 USING db2inst1

db2 "select TABNAME from syscat.tables where TABSCHEMA='DB2INST1' and TYPE='T' and ( TABNAME like 'RUI_%' or TABNAME like 'SHU_%') order by TABNAME" | grep ^[RS]  > TBLNM.$$

for TBL in `cat TBLNM.$$`
do
	echo "[`date`][$TBL] runstats start ----->"
	db2 RUNSTATS ON TABLE DB2INST1.$TBL WITH DISTRIBUTION AND DETAILED INDEXES ALL
done

db2 terminate

echo "[`date`] 累積runstats end ----->"

rm TBLNM.$$
