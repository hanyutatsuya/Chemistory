#######################################################################
#	���񍐕��f�[�^��imprt���� (IXF)
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"imp_mhk.log"
	exit 1
fi

MHKTBL="BUNCHU CHIKENZOK IRAI KANJYA KEKKA KENORDER KENZOK NINSIKI REALCHK HKHRIRAI"

for TBL in `echo $MHKTBL`
do
	echo "[`date`][$TBL] import start ----->"
	db2 "import from ./$TBL.mhk of ixf allow write access commitcount 5000 messages ./$TBL.mhk.msg insert into $TBL"
	if [ $? -ne 0 ]; then
		echo `date`" ERROR : $TBL ���񍐕���import�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"imp_mhk.log"
		exit 1
	fi
done

db2 terminate

exit 0
