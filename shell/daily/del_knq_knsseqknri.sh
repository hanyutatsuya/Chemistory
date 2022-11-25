#!/bin/sh
#######################################################################
# ����SEQ�̔ԊǗ��e�[�u���X�V
# 	�ً}���̃��R�[�h���폜�i�ً}��������ݒ莞��INSERT)
# $1 : DB��
# $2 : ���[�U��
# $3 : �p�X���[�h
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"del_knq_knsseqknri.log"
    exit 1
fi

db2 "delete from KNSSEQKNRI \
where  KNSKISYMD <> (select kjnsriymd from sysknrmst) "
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : KNSSEQKNRI Table�̍폜�Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"del_knq_knsseqknri.log"	
    exit 1
fi

db2 terminate

exit 0
