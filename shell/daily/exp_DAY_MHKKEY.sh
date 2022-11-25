#######################################################################
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
# $4 : IXF保存先
#######################################################################

# エラーログの出力先
LOG_DIR="/apdata/aplog"

## エラーログのプレフィック
NAME_ERRLOG="WARNING_"

db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"exp_DAY_MHKKEY.log"
    exit 1
fi

db2 "export to $4/DAY_MHKKEY_Z.ixf of ixf messages $4/DAY_MHKKEY_Z.msg select * from DAY_MHKKEY"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : 未報告キー情報Tableのバックアップに失敗しました" >> $LOG_DIR/$NAME_ERRLOG"exp_DAY_MHKKEY.log"
    exit 1
fi

db2 terminate

exit 0
