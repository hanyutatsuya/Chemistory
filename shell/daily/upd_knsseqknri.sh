#!/bin/sh
#######################################################################
# 検査SEQ採番管理テーブル更新
# $1 : DB名
# $2 : ユーザ名
# $3 : パスワード
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $1 user $2 using $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"upd_knsseqknri.log"
    exit 1
fi

db2 "update KNSSEQKNRI \
set KNSKISYMD = (select kjnsriymd from sysknrmst) \
	, WSNO = 0 \
	, KNSSEQMAX = 500000 \
	, SYTRYMAX = 0 \
	, KSNDH = CURRENT_TIMESTAMP"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : 検査SEQ採番管理テーブルの更新に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"upd_knsseqknri.log"
    exit 1
fi

db2 "update KNSSEQKNRI \
set KNSSEQMAX = 0 \
where WSSBT in ('1TDM','2439')"
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : 検査SEQ採番管理テーブルの更新に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"upd_knsseqknri.log"
	exit 1 
fi

db2 terminate

exit 0
