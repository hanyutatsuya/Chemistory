#!/bin/bash
##################################################################
#
# prcND101_off.sh
#
##################################################################
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

export PATH=./:$PATH:/sbin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/ibm/db2/V11.1/lib64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/ibm/db2/V11.1/lib32

DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"

PROC_STOP="/home/kea00sys/bin/ZD999stop"
PROC_ND101="ND101"
PROC_ND101_SM="15001"

MOTODIR1="/apdata/today/file/rack/OK"
MOTODIR2="/apdata/today/file/rack/SKIP"
SAKIDIR="/apdata/oldday/rack_out"

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

# �����d�m�c���̎擾
BCHENDFLG=`db2 -x "SELECT trim(BCHENDFLG) FROM SYSKNRMST FOR READ ONLY"`
# �����d�m�c���̎擾�Ɏ��s�����ꍇ�A�������I������B
if [ $? -gt 0 ]; then
        exit 0
fi
# �����d�m�c�O�������ꍇ�A�������I������B
if [ ${BCHENDFLG} = "0" ]; then
        exit 0
fi
sleep 300

# �v���Z�X�̒�~
${PROC_STOP} ${PROC_ND101_SM}
sleep 10

# �t�@�C���̈ړ�
find  ${MOTODIR1} -type f | xargs -r mv --target-directory=${SAKIDIR}
find  ${MOTODIR2} -type f | xargs -r mv --target-directory=${SAKIDIR}

exit 0
