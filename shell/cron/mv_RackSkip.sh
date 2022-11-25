#!/bin/sh
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

##############################################################
#
# スキップされたラック情報ファイルを処理ディレクトリへ移動する
#
##############################################################
SKIPDIR="/apdata/today/file/rack/SKIP"
WORKDIR="/apdata/today/file/rack"
#TMP FILE
WKF=/tmp/$$

# システム管理マスタ　運用フラグ＝１（日次処理中)
db2 connect to kea00db9 user kea00dbt using kea00dbt > /dev/null
db2 "select count(UNYFLG) as KEN from SYSKNRMST where UNYFLG='1' for read only" | sed 's/ //g' | grep ^[0-9] | grep -v "レコード" > $WKF
db2 terminate > /dev/null

if [ -s $WKF ]
then
    CNT=`cat $WKF`
else
    CNT=0
fi
rm $WKF
# Get Daily Process Unyou Flg [$CNT]
if [ $CNT -gt 0 ]
then
    exit 0
fi

cd $SKIPDIR
for FILENAME in `ls SKIP*`
do
    mv -f ${SKIPDIR}/${FILENAME} ${WORKDIR}/${FILENAME}
done 
