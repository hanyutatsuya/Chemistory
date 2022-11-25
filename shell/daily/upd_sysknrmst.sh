#!/bin/sh
#######################################################################
# システム管理マスタ更新
# $1 : 受付日(YYYY-MM-DD)
# $2 : DB名
# $3 : ユーザ名
# $4 : パスワード
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

UTKYMD=$1

db2 connect to $2 user $3 using $4
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst.log"	
	exit 1
fi

db2 "UPDATE	SYSKNRMST  \
SET		KJNSRIYMD	='$UTKYMD' \
		,KKKJSRIYMD	='1000-01-01' \
		,IRIENDFLG	='0' \
		,IRIENDDH	='1000-01-01-00.00.00.000001' \
        ,NSKENDFLG  ='0' \
        ,NSKENDDH   ='1000-01-01-00.00.00.000001' \
		,BCHENDFLG	='0' \
		,BCHEND0DH	='1000-01-01-00.00.00.000001' \
		,BCHEND1DH	='1000-01-01-00.00.00.000001' \
		,BCHEND2DH	='1000-01-01-00.00.00.000001' \
		,BCHEND3DH	='1000-01-01-00.00.00.000001' \
		,BCHEND4DH	='1000-01-01-00.00.00.000001' \
		,SSNTUBN	=0 \
		,HNKTNTID	='DAILY' \
		,KSNDH		=CURRENT TIMESTAMP"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : システム管理マスタの更新に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst.log"
    exit 1
fi

db2 terminate

exit 0
