#######################################################################
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
# $4 : IXF�ۑ���
#######################################################################

# �G���[���O�̏o�͐�
LOG_DIR="/apdata/aplog"

## �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="WARNING_"

db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"exp_DAY_MHKKEY.log"
    exit 1
fi

db2 "export to $4/DAY_MHKKEY_Z.ixf of ixf messages $4/DAY_MHKKEY_Z.msg select * from DAY_MHKKEY"
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ���񍐃L�[���Table�̃o�b�N�A�b�v�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"exp_DAY_MHKKEY.log"
    exit 1
fi

db2 terminate

exit 0
