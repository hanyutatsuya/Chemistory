#######################################################################
#	���񍐕��f�[�^��import���� (DEL)
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################

db2 CONNECT TO $1 USER $2 USING $3

MTKTBL="CHIKENZOK IRAI KANJYA"

for TBL in `echo $MTKTBL`
do
	echo "[`date`][$TBL] import start ----->"
	db2 "import from ./$TBL.mtk of del allow write access commitcount 5000 messages ./$TBL.imp_mtk.msg insert_update into $TBL"
done

db2 terminate
