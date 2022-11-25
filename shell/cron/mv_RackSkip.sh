#!/bin/sh
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

##############################################################
#
# �X�L�b�v���ꂽ���b�N���t�@�C���������f�B���N�g���ֈړ�����
#
##############################################################
SKIPDIR="/apdata/today/file/rack/SKIP"
WORKDIR="/apdata/today/file/rack"
#TMP FILE
WKF=/tmp/$$

# �V�X�e���Ǘ��}�X�^�@�^�p�t���O���P�i����������)
db2 connect to kea00db9 user kea00dbt using kea00dbt > /dev/null
db2 "select count(UNYFLG) as KEN from SYSKNRMST where UNYFLG='1' for read only" | sed 's/ //g' | grep ^[0-9] | grep -v "���R�[�h" > $WKF
db2 terminate > /dev/null

if [ -s $WKF ]
then
    CNT=`cat $WKF`
else
    CNT=0
fi
rm $WKF
# Get Daily Process Unyou Flg [$CNT]
if [ $CNT -gt 0 ]
then
    exit 0
fi

cd $SKIPDIR
for FILENAME in `ls SKIP*`
do
    mv -f ${SKIPDIR}/${FILENAME} ${WORKDIR}/${FILENAME}
done 
