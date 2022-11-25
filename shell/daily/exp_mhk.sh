#######################################################################
#	���񍐕��f�[�^��export����(IXF)
#		���A���`�F�b�N��del��export�s�ł�����
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"exp_mhk.log"
	exit 1
fi

MHKTBL="BUNCHU CHIKENZOK IRAI KANJYA KEKKA KENORDER KENZOK NINSIKI REALCHK"

for TBL in `echo $MHKTBL`
do
	echo "[`date`][$TBL] export start ----->"
	db2 "export to ./$TBL.mhk of ixf messages ./$TBL.mhk.msg select * from $TBL in, DAY_MHKKEY ky where in.utkymd=ky.utkymd and in.irino=ky.irino for read only"
	if [ $? -ne 0 ]; then
		echo `date`" ERROR : $TBL ���񍐕��̎擾�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"exp_mhk.log"
		exit 1
	fi
	##  db2 "select count(in.irino) from $TBL in, DAY_MHKKEY ky where in.utkymd=ky.utkymd and in.irino=ky.irino"

done

# HKHRIRAI �̂݁A�������قȂ邽�߁A�ʓr EXPORT
echo "[`date`][HKHRIRAI] export start ----->"
db2 "export to ./HKHRIRAI.mhk of ixf messages ./HKHRIRAI.mhk.msg select * from HKHRIRAI hkhr where not exists (select * from KEKKA kka where hkhr.utkymd=kka.utkymd and hkhr.irino=kka.irino and hkhr.kmkcd=kka.kmkcd and kka.knsflg='E') for read only"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : HKHRIRAI ���񍐕��̎擾�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"exp_mhk.log"
	exit 1
fi

db2 terminate

exit 0
