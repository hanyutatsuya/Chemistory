#!/bin/sh
#######################################################################
# 検査SEQ採番管理テーブル更新
# 	緊急分のレコードを削除（緊急基準処理日設定時にINSERT)
# $1 : DB名
# $2 : ユーザ名
# $3 : パスワード
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"del_knq_knsseqknri.log"
    exit 1
fi

db2 "delete from KNSSEQKNRI \
where  KNSKISYMD <> (select kjnsriymd from sysknrmst) "
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : KNSSEQKNRI Tableの削除に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"del_knq_knsseqknri.log"	
    exit 1
fi

db2 terminate

exit 0
