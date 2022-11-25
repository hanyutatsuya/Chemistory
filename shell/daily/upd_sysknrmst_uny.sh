#!/bin/sh
#######################################################################
# �^�p�t���O�ݒ�
# $1 : �^�p�t���O(1or0)
# $2 : DB��
# $3 : ���[�U��
# $4 : �p�X���[�h
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $2 user $3 using $4
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst_uny.log"
    exit 1
fi

db2 "UPDATE SYSKNRMST SET UNYFLG = '$1'";
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �^�p�t���O�̐ݒ�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"upd_sysknrmst_uny.log"
    exit 1
fi

db2 terminate

exit 0
