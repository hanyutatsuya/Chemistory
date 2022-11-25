#######################################################################
#	未報告分データを累積、集計から削除する
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
# $4 : DAY_MHKKEY_Z.ixf保存先
#######################################################################

## エラーログの出力先
LOG_DIR="/apdata/aplog"

## エラーログのプレフィック
NAME_ERRLOG="WARNING_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    exit 1
fi

##MHKTBL="RUI_BUNCHU RUI_CHIKENZOK RUI_KENORDER RUI_NINSIKI SHU_KEKKA"
MHKTBL="RUI_BUNCHU RUI_CHIKENZOK RUI_KENORDER RUI_NINSIKI RUI_IRAI RUI_KANJYA RUI_KEKKA RUI_KENZOK SHU_KEKKA"

db2 "import from /dev/null of del replace into day_mhkkey"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : 未報告キー情報の削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    exit 1
fi

db2 "import from $4/DAY_MHKKEY_Z.ixf of ixf commitcount 5000 insert into DAY_MHKKEY"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : 未報告分データの削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    exit 1
fi

for TBL in `echo $MHKTBL`
do

	echo "[`date`][$TBL] delete start ----->"

	db2 "select count(*) from $TBL dd where exists ( select utkymd, irino from DAY_MHKKEY ky where ky.utkymd=dd.utkymd and ky.irino=dd.irino ) for read only"
	if [ $? -gt 0 ]; then
    	echo `date`" ERROR : $TBL 未報告分データの検索に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    	exit 1
	fi

	db2 "delete from $TBL dd where exists ( select utkymd, irino from DAY_MHKKEY ky where ky.utkymd=dd.utkymd and ky.irino=dd.irino )"
	if [ $? -gt 0 -a $? -gt 1 ]; then
    	echo `date`" ERROR : $TBL 未報告分データの削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    	exit 1
	fi
done

db2 terminate

exit 0
