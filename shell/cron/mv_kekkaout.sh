#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi
#######################################################################
# cron	結果out内ファイルの移動 (日次所要時間軽減措置)
#---------------------------------------------------------------------
#	mv元：	/apdata/today/file/KEA00/kea00ap/kekka/Data/out
#	mv先：	/apdata/oldday/kekka_out
#	対象ファイル：作成日時が●時間経過したファイル
#
#######################################################################
HZMIN=120
MOTODIR=/apdata/today/file/KEA00/kea00ap/kekka/Data/out
SAKIDIR=/apdata/oldday/kekka_out

#TMP FILE
WKF=/tmp/$$

#---<< 日次処理中はRUNSTATSを実行しない >>---------------------------------
# システム管理マスタ　運用フラグ＝１（日次処理中)
db2 connect to kea00db user db2inst1 using db2inst1 > /dev/null
db2 "select count(UNYFLG) as KEN from SYSKNRMST where UNYFLG='1' for read only" | sed 's/ //g' | grep ^[0-9] | grep -v "レコード" > $WKF
db2 terminate > /dev/null

if [ -s $WKF ]
then
    CNT=`cat $WKF`
else
    CNT=0
fi
rm $WKF
##echo "[`date`] Get Daily Process Unyou Flg [$CNT]"
if [ $CNT -gt 0 ]
then
    ##echo "[`date`] CNT[$CNT]  Daily Processing!! mv kekka_out EXIT !"
    exit 0
fi

find  ${MOTODIR} -type f -mmin +$HZMIN | xargs mv --target-directory=${SAKIDIR}

# mv元への移動
# cd $MOTODIR
#for LFL in `find  $MOTODIR -type f -mmin +$HZMIN -print`
#do
#	MFN=`basename $LFL`
#	mv $MOTODIR/$MFN $SAKIDIR
#done
exit 0
