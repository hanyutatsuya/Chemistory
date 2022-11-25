#!/bin/bash
##################################################################
#
# prcLD104_onoff.sh
# ���j���̖�Ɍ��ʗv���J�[�h���z�X�g�֑���ƃG���[�ƂȂ邽�߁A
# ���j 23:00 �` ���j 5:00 �܂ł̊Ԃ͌��ʗv���J�[�h�쐬���~�߂�B
#
##################################################################
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

export PATH=./:$PATH:/sbin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/ibm/db2/V11.1/lib64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/ibm/db2/V11.1/lib32

EXEC_BIN="/home/kea00sys/bin"
SHELL_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP_LD104"

PROC_STOP=${EXEC_BIN}/ZD999stop
PROC_LD104="LD104"
PROC_LD104_SM=13004

if [ "$1" = "-START" ]; then
	cd ${EXEC_BIN}

	${EXEC_BIN}/${PROC_LD104} ${EXEC_BIN}/${PROC_LD104}.ini

	rm ${SHELL_DIR}/${STOP_FILE_NAME}
elif [ "$1" = "-STOP" ]; then
	touch ${SHELL_DIR}/${STOP_FILE_NAME}

	${PROC_STOP} ${PROC_LD104_SM}
fi
