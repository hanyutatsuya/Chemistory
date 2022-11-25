#######################################################################
#  集計テーブル対象データをimportする
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

## エラーログの出力先
LOG_DIR="/apdata/aplog"

## エラーログのプレフィック
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"imp_shu.log"
	exit 1
fi

echo "[`date`][SHU_KEKKA] import start ----->"

TBL="SHU_KEKKA"

db2 "import from ./$TBL.ixf of ixf allow write access commitcount 10000 messages ./$TBL.msg INSERT_UPDATE into $TBL"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : $TBL のIMPORTに失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"imp_shu.log"
    exit 1
fi

db2 terminate

exit 0
