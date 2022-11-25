#!/bin/bash
################################################################
#
# chk_daily_backup.sh �o�b�N�A�b�v���퐫�m�F�V�F��
#
# 2016-07-22 Create H.Sekiya
#
################################################################

# �Ώۂ̐ݒ�
DIR_OLDDAY="/apdata/oldday"

# �o�b�N�A�b�v��ݒ� 
MY_SERVER=`hostname -i | tr -d ' '`
BK_SERVER="10.1.181.22"
BK_PATH="/mnt/usb/bak_daily"

DAILY_DIR=$1

# �������O�t�@�C���̍X�V�����m�F�B
MY_USER=`ls -dl --time-style="+%Y-%m-%d-%H:%M:%S" ${DIR_OLDDAY}/${DAILY_DIR} | cut -d' ' -f4`
if [ -z ${MY_USER} ]; then
	echo "�����f�B���N�g�� ( ${DIR_OLDDAY}/${DAILY_DIR} ) �����݂��܂���B"
	exit 0
fi
MY_GRP=`ls -dl --time-style="+%Y-%m-%d-%H:%M:%S" ${DIR_OLDDAY}/${DAILY_DIR} | cut -d' ' -f5`
MY_DATETIME=`ls -dl --time-style="+%Y-%m-%d-%H:%M:%S" ${DIR_OLDDAY}/${DAILY_DIR} | cut -d' ' -f7`
MY_FULLPATH=`ls -dl --time-style="+%Y-%m-%d-%H:%M:%S" ${DIR_OLDDAY}/${DAILY_DIR} | cut -d' ' -f8`
MY_VOL=`du -slx ${DIR_OLDDAY}/${DAILY_DIR} | cut -d'	' -f1`

BK_USER=`rsh ${BK_SERVER} "ls -dl --time-style=+%Y-%m-%d-%H:%M:%S ${BK_PATH}/${DAILY_DIR}" | cut -d' ' -f6`
if [ -z ${BK_USER} ]; then
	echo "�����f�B���N�g���̃o�b�N�A�b�v ( ${BK_PATH}/${DAILY_DIR} ) �����݂��܂���B"
	exit 0
fi
BK_GRP=`rsh ${BK_SERVER} "ls -dl --time-style=+%Y-%m-%d-%H:%M:%S ${BK_PATH}/${DAILY_DIR}" | cut -d' ' -f7`
BK_DATETIME=`rsh ${BK_SERVER} "ls -dl --time-style=+%Y-%m-%d-%H:%M:%S ${BK_PATH}/${DAILY_DIR}" | cut -d' ' -f16`
BK_FULLPATH=`rsh ${BK_SERVER} "ls -dl --time-style=+%Y-%m-%d-%H:%M:%S ${BK_PATH}/${DAILY_DIR}" | cut -d' ' -f17`
BK_VOL=`rsh ${BK_SERVER} du -slx ${BK_PATH}/${DAILY_DIR} | cut -d'	' -f1`

echo ""
echo "[${MY_SERVER}]"
echo "${MY_VOL} ${MY_USER} ${MY_GRP} ${MY_DATETIME} ${MY_FULLPATH}"
echo ""
echo "[${BK_SERVER}]"
echo "${BK_VOL} ${BK_USER} ${BK_GRP} ${BK_DATETIME} ${BK_FULLPATH}"
echo ""

exit 0
