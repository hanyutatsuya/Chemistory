#######################################################################
#	未報告分データをexportする(IXF)
#		リアルチェックはdelでexport不可であった
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"exp_mhk.log"
	exit 1
fi

MHKTBL="BUNCHU CHIKENZOK IRAI KANJYA KEKKA KENORDER KENZOK NINSIKI REALCHK"

for TBL in `echo $MHKTBL`
do
	echo "[`date`][$TBL] export start ----->"
	db2 "export to ./$TBL.mhk of ixf messages ./$TBL.mhk.msg select * from $TBL in, DAY_MHKKEY ky where in.utkymd=ky.utkymd and in.irino=ky.irino for read only"
	if [ $? -ne 0 ]; then
		echo `date`" ERROR : $TBL 未報告分の取得に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"exp_mhk.log"
		exit 1
	fi
	##  db2 "select count(in.irino) from $TBL in, DAY_MHKKEY ky where in.utkymd=ky.utkymd and in.irino=ky.irino"

done

# HKHRIRAI のみ、条件が異なるため、別途 EXPORT
echo "[`date`][HKHRIRAI] export start ----->"
db2 "export to ./HKHRIRAI.mhk of ixf messages ./HKHRIRAI.mhk.msg select * from HKHRIRAI hkhr where not exists (select * from KEKKA kka where hkhr.utkymd=kka.utkymd and hkhr.irino=kka.irino and hkhr.kmkcd=kka.kmkcd and kka.knsflg='E') for read only"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : HKHRIRAI 未報告分の取得に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"exp_mhk.log"
	exit 1
fi

db2 terminate

exit 0
