
#######################################################################
# オンライン用マスタdelファイル作成
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
    exit 1
fi

#	対象マスタの一覧作成

echo "ctrlmst
ctrlsbtmst
kmkmst
knsgmst
mechmst
rngchkmst
sysknrmst
xbarmmst" > LST.$$

for TBL in `cat LST.$$`
do
	echo "mk_delfile[$TBL][`date`]"
	db2 "export to $TBL.$$ of del messages $TBL.msg select * from $TBL"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL マスタの取得に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
		exit 1
	fi
	
	cat  $TBL.$$ | sed 's/"//g' $TBL.$$ | sed 's/$//' | sort > $TBL.del
	if [ $? -gt 0 ]; then
		exit 1
	fi
	rm $TBL.$$
done

# kskbrmst の最終カラムに施設コード(固定値：0000000)を追加する
TBL=kskbrmst
echo "mk_delfile[$TBL][`date`]"
db2 "export to $TBL.$$ of del messages $TBL.msg select tbl.*, '0000000' from $TBL as tbl"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : $TBL マスタの取得に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
	exit 1
fi

cat  $TBL.$$ | sed 's/"//g' $TBL.$$ | sed 's/$//' | sort > $TBL.del
if [ $? -gt 0 ]; then
	echo `date`" ERROR : $TBL マスタの取得に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
	exit 1
fi
rm $TBL.$$

rm LST.$$ 
rm *.msg

db2 terminate

exit 0
