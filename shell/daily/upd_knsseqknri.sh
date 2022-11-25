#!/bin/sh
#######################################################################
# ����SEQ�̔ԊǗ��e�[�u���X�V
# $1 : DB��
# $2 : ���[�U��
# $3 : �p�X���[�h
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $1 user $2 using $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"upd_knsseqknri.log"
    exit 1
fi

db2 "update KNSSEQKNRI \
set KNSKISYMD = (select kjnsriymd from sysknrmst) \
	, WSNO = 0 \
	, KNSSEQMAX = 500000 \
	, SYTRYMAX = 0 \
	, KSNDH = CURRENT_TIMESTAMP"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ����SEQ�̔ԊǗ��e�[�u���̍X�V�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"upd_knsseqknri.log"
    exit 1
fi

db2 "update KNSSEQKNRI \
set KNSSEQMAX = 0 \
where WSSBT in ('1TDM','2439')"
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : ����SEQ�̔ԊǗ��e�[�u���̍X�V�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"upd_knsseqknri.log"
	exit 1 
fi

db2 terminate

exit 0
