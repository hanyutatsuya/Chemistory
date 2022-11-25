#######################################################################
#  �e�[�u����S��export����
#		�݌v(RUI_)�A�W�v(SHU_)�A����(RIREKI)�e�[�u���͏���
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �c�a�̐ڑ��Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"exp_all.log"
	exit 1
fi

db2 "select TABNAME from syscat.tables where TABSCHEMA='DB2INST1' and TYPE='T' order by TABNAME" | grep ^[A-Z] | grep -v TABNAME | grep -v RUI_ | grep -v SHU_ | grep -v RIREKI | grep -v ADVISE_ | grep -v EXPLAIN_ > TBLNM.$$
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �Ώ�Table�̎擾�Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"exp_all.log"
	exit 1
fi


for TBL in `cat TBLNM.$$`
do
	echo "[`date`][$TBL] export start ----->"
    db2 "export to ./$TBL.ixf of ixf messages ./$TBL.msg select * from $TBL for read only"
	if [ $? -ne 0 ]; then
		echo `date`" ERROR : $TBL �o�b�N�A�b�v�̎擾�Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"exp_all.log"
		exit 1
	fi
done

db2 terminate
rm TBLNM.$$

exit 0
