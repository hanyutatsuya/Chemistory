#######################################################################
#  �W�v�e�[�u���Ώۃf�[�^��import����
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################

## �G���[���O�̏o�͐�
LOG_DIR="/apdata/aplog"

## �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"imp_shu.log"
	exit 1
fi

echo "[`date`][SHU_KEKKA] import start ----->"

TBL="SHU_KEKKA"

db2 "import from ./$TBL.ixf of ixf allow write access commitcount 10000 messages ./$TBL.msg INSERT_UPDATE into $TBL"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : $TBL ��IMPORT�Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"imp_shu.log"
    exit 1
fi

db2 terminate

exit 0
