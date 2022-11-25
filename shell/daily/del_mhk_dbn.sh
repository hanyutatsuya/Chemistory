#######################################################################
#	���񍐕��f�[�^��ݐρA�W�v����폜����
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
# $4 : DAY_MHKKEY_Z.ixf�ۑ���
#######################################################################

## �G���[���O�̏o�͐�
LOG_DIR="/apdata/aplog"

## �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="WARNING_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    exit 1
fi

##MHKTBL="RUI_BUNCHU RUI_CHIKENZOK RUI_KENORDER RUI_NINSIKI SHU_KEKKA"
MHKTBL="RUI_BUNCHU RUI_CHIKENZOK RUI_KENORDER RUI_NINSIKI RUI_IRAI RUI_KANJYA RUI_KEKKA RUI_KENZOK SHU_KEKKA"

db2 "import from /dev/null of del replace into day_mhkkey"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ���񍐃L�[���̍폜�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    exit 1
fi

db2 "import from $4/DAY_MHKKEY_Z.ixf of ixf commitcount 5000 insert into DAY_MHKKEY"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ���񍐕��f�[�^�̍폜�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    exit 1
fi

for TBL in `echo $MHKTBL`
do

	echo "[`date`][$TBL] delete start ----->"

	db2 "select count(*) from $TBL dd where exists ( select utkymd, irino from DAY_MHKKEY ky where ky.utkymd=dd.utkymd and ky.irino=dd.irino ) for read only"
	if [ $? -gt 0 ]; then
    	echo `date`" ERROR : $TBL ���񍐕��f�[�^�̌����Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    	exit 1
	fi

	db2 "delete from $TBL dd where exists ( select utkymd, irino from DAY_MHKKEY ky where ky.utkymd=dd.utkymd and ky.irino=dd.irino )"
	if [ $? -gt 0 -a $? -gt 1 ]; then
    	echo `date`" ERROR : $TBL ���񍐕��f�[�^�̍폜�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"del_mhk_dbn.log"
    	exit 1
	fi
done

db2 terminate

exit 0
