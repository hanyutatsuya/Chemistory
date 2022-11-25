#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi
#######################################################################
# cron	����out���t�@�C���̈ړ� (�������v���Ԍy���[�u)
#---------------------------------------------------------------------
#	mv���F	/apdata/today/file/KEA00/kea00ap/kekka/Data/out
#	mv��F	/apdata/oldday/kekka_out
#	�Ώۃt�@�C���F�쐬�����������Ԍo�߂����t�@�C��
#
#######################################################################
HZMIN=120
MOTODIR=/apdata/today/file/KEA00/kea00ap/kekka/Data/out
SAKIDIR=/apdata/oldday/kekka_out

#TMP FILE
WKF=/tmp/$$

#---<< ������������RUNSTATS�����s���Ȃ� >>---------------------------------
# �V�X�e���Ǘ��}�X�^�@�^�p�t���O���P�i����������)
db2 connect to kea00db user db2inst1 using db2inst1 > /dev/null
db2 "select count(UNYFLG) as KEN from SYSKNRMST where UNYFLG='1' for read only" | sed 's/ //g' | grep ^[0-9] | grep -v "���R�[�h" > $WKF
db2 terminate > /dev/null

if [ -s $WKF ]
then
    CNT=`cat $WKF`
else
    CNT=0
fi
rm $WKF
##echo "[`date`] Get Daily Process Unyou Flg [$CNT]"
if [ $CNT -gt 0 ]
then
    ##echo "[`date`] CNT[$CNT]  Daily Processing!! mv kekka_out EXIT !"
    exit 0
fi

find  ${MOTODIR} -type f -mmin +$HZMIN | xargs mv --target-directory=${SAKIDIR}

# mv���ւ̈ړ�
# cd $MOTODIR
#for LFL in `find  $MOTODIR -type f -mmin +$HZMIN -print`
#do
#	MFN=`basename $LFL`
#	mv $MOTODIR/$MFN $SAKIDIR
#done
exit 0
