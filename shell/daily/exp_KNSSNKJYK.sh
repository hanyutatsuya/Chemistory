#######################################################################
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################
HOZON=7

LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $1 user $2 using $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"exp_KNSSNKJYK.log"
	exit 1
fi

echo "[`date`][KNSSNKJYK] export update delete start ----->"

# 全件分を別名に
mv ./KNSSNKJYK.ixf ./all_KNSSNKJYK.ixf

db2 "export to ./KNSSNKJYK.ixf of ixf messages KNSSNKJYK.msg select * from KNSSNKJYK where KNSKISYMD <= ( select KJNSRIYMD - $HOZON days from sysknrmst ) for read only"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : KNSSNKJYK Tableのバックアップに失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"exp_KNSSNKJYK.log"
    exit 1
fi

db2 "update KNSSNKJYK set KNSKISYMD2=( select KJNSRIYMD from sysknrmst ) where KNSKISYMD2='2100-12-31'"
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : KNSSNKJYK Tableの更新に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"exp_KNSSNKJYK.log"
    exit 1
fi

db2 "delete from KNSSNKJYK where KNSKISYMD <= ( select KJNSRIYMD - $HOZON days from sysknrmst )"
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : KNSSNKJYK Tableの削除に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"exp_KNSSNKJYK.log"
    exit 1
fi

db2 terminate

exit 0
