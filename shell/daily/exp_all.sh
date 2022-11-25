#######################################################################
#  テーブルを全件exportする
#		累計(RUI_)、集計(SHU_)、履歴(RIREKI)テーブルは除く
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢの接続に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"exp_all.log"
	exit 1
fi

db2 "select TABNAME from syscat.tables where TABSCHEMA='DB2INST1' and TYPE='T' order by TABNAME" | grep ^[A-Z] | grep -v TABNAME | grep -v RUI_ | grep -v SHU_ | grep -v RIREKI | grep -v ADVISE_ | grep -v EXPLAIN_ > TBLNM.$$
if [ $? -ne 0 ]; then
	echo `date`" ERROR : 対象Tableの取得に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"exp_all.log"
	exit 1
fi


for TBL in `cat TBLNM.$$`
do
	echo "[`date`][$TBL] export start ----->"
    db2 "export to ./$TBL.ixf of ixf messages ./$TBL.msg select * from $TBL for read only"
	if [ $? -ne 0 ]; then
		echo `date`" ERROR : $TBL バックアップの取得に失敗しました。" >> $LOG_DIR/$NAME_ERRLOG"exp_all.log"
		exit 1
	fi
done

db2 terminate
rm TBLNM.$$

exit 0
