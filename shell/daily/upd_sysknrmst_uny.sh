#!/bin/sh
#######################################################################
# 運用フラグ設定
# $1 : 運用フラグ(1or0)
# $2 : DB名
# $3 : ユーザ名
# $4 : パスワード
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $2 user $3 using $4
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst_uny.log"
    exit 1
fi

db2 "UPDATE SYSKNRMST SET UNYFLG = '$1'";
if [ $? -ne 0 ]; then
	echo `date`" ERROR : 運用フラグの設定に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst_uny.log"
    exit 1
fi

db2 terminate

exit 0
