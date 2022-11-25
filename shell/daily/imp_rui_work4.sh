#######################################################################
#  ƒf[ƒ^‚ð—ÝÏ‚Éimport‚·‚é( INSERT_UPDATE MODE )(IXF FORMAT)
# $1 : DB–¼
# $2 : ƒ†[ƒUID(DB2)
# $3 : ƒpƒXƒ[ƒh(DB2)
#######################################################################

## ƒGƒ‰[ƒƒO‚Ìo—Íæ
LOG_DIR="/apdata/aplog"

## ƒGƒ‰[ƒƒO‚ÌƒvƒŒƒtƒBƒbƒN
NAME_ERRLOG="WARNING_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ‚c‚aÚ‘±‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
    exit 1
fi

#	—ÝÏ‘ÎÛŠOƒe[ƒuƒ‹ˆê——
echo "TABNAME
APLLOG
ASYRACKKNRI
AUTOKOSICTRL
BATCHKNRI
BSSIKKA
BSSIZOK
BUNCHU
CHIKENZOK
CTRLKKA
CTRLKNR
DAY_MHKKEY
HKKKNRI
HYJKMK
IRAI
IJYOSYA
KANJYA
KEKKA
KEKKAFREE
KENORDER
KENPOS
KMKBTUTEST
KNKMHMZK
KNKYULOT
KNSSEQKNRI
KNTIDUNKNOWN
LTHKFKLST
REALCHK
RIREKI
SLIDE
SOUKAN
STANDARD
TRAYKNRI
TRRAKHMZK
WSSEQKNRI
XEBSKFLG" > EXC.$$

db2 "select TABNAME from syscat.tables where TABSCHEMA='DB2INST1' and TYPE='T' and ((TABNAME not like '%MST') and (TABNAME not like 'RUI_%') and (TABNAME not like 'SHU_%')) order by TABNAME"  | grep ^[A-Z] | grep -vf EXC.$$ | grep -v ADVISE_ | grep -v EXPLAIN_ > TBLNM.$$
if [ $? -gt 0 ]; then
	echo `date`" ERROR : —ÝÏTable‚ÌIMPORT‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
	db2 terminate
	exit 1
fi

# CTRLKKA ‚yƒT[ƒoã‚É‘¶Ý‚·‚é‚½‚ßA•Ê“rˆ—
for TBL in `echo "CTRLKKA"`
do
	echo "[`date`][RUI_$TBL] import start ----->"
	db2 "import from ./$TBL.ixf of ixf allow write access commitcount 20000 messages ./RUI_$TBL.msg INSERT_UPDATE into RUI_$TBL"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL ‚ÌIMPORT‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
		db2 terminate
		exit 1
	fi
done

db2 terminate

# ƒtƒFƒfƒŒ[ƒVƒ‡ƒ“‰z‚µ‚ÉINSERT‚·‚é‚ÆƒŒƒXƒ|ƒ“ƒX‚ªˆ«‚­‚È‚éê‡‚ª‚ ‚é‚Ì‚ÅA—ÝÏ‚c‚a‚É’¼ÚINSERT
db2 CONNECT TO kea00dbn USER db2inst1 USING db2inst1
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ‚c‚aÚ‘±(‚c‚a‚m)‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
    exit 1
fi

for TBL in `cat TBLNM.$$`
do
	echo "[`date`][RUI_$TBL] import start ----->"
	db2 "import from ./$TBL.ixf of ixf allow write access commitcount 20000 messages ./RUI_$TBL.msg INSERT_UPDATE into RUI_$TBL"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL ‚ÌIMPORT‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
		db2 terminate
		rm *.$$
		exit 1
	fi
done

# KENPOS INSERT_UPDATE‚ª•s‰Â‚Ì‚½‚ß•Ê“rˆ—
for TBL in `echo "KENPOS"`
do
	echo "[`date`][RUI_$TBL] import start ----->"
	db2 "import from ./$TBL.ixf of ixf allow write access commitcount 20000 messages ./RUI_$TBL.msg INSERT into RUI_$TBL"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL ‚ÌIMPORT‚ÉŽ¸”s‚µ‚Ü‚µ‚½" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
		db2 terminate
		exit 1
	fi
done

db2 terminate

rm *.$$

exit 0
