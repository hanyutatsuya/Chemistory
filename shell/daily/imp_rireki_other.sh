#!/bin/sh
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

#######################################################################
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
# $4 : ��ƃf�B���N�g��
#######################################################################

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : �����{��������INSERT�Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"imp_rireki_other.log"
	exit 1
fi

WORKDIR=$4
CURDIR=`pwd`

cd $WORKDIR
for FILENAME in `ls CNV*_A00.dat`
do
	db2 "import from ${FILENAME} of del commitcount 20000 insert_update into RIREKI"
	if [ $? -ne 0 -a $? -ne 1 ]; then
		echo `date`" ERROR : �����{��������INSERT�Ɏ��s���܂����B" >> $LOG_DIR/$NAME_ERRLOG"imp_rireki_other.log"
		exit 1
	fi
done 
cd $CURDIR
