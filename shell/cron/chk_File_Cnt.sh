#!/bin/sh
############################################################
#
# chk_File_Cnt.sh ���ʃt�@�C���ؗ��Ď��V�F��
#
############################################################
DIR_LOG="/apdata/aplog"
ERR_LOG_FILE_NAME="FATAL_File_Cnt.log"	# ���[�����M�t�@�C����

# �Ď��f�B���N�g��
CHK_DIR="/apdata/today/file/KEA00/kea00ap/kekka/Data"
# �Ď��Ώۃt�@�C�� �g���q
CHK_FILE_EXT="dat"
# �ؗ��G���[���� ���̐ݒ�l��葽���t�@�C�����ؗ����Ă���ꍇ���G���[�Ƃ���B
RIMIT_FILE_CNT=1000
# ���g���C�� �A���ł��̉񐔕��Ď����s���A�S�ăG���[�Ȃ�΃G���[���[���𑗐M����B
RETRY_CNT=6
# ���g���C�Ԋu(�b)
RETRY_INTERVAL=30

# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /${sem}.lock ${sem} || exit
trap "rm ${sem}; exit" 2 3 15

if [ -e "${DIR_LOG}/${ERR_LOG_FILE_NAME}" ]; then
	echo "�����M�̃G���[�t�@�C�������݂��Ă��܂��B ${DIR_LOG}/${ERR_LOG_FILE_NAME}"
	exit 0
fi

ERR_FLG="NG"
for i in  `seq 1 ${RETRY_CNT}`
do
	FILE_CNT=`find ${CHK_DIR} -type f -maxdepth 1 -name *.${CHK_FILE_EXT} 2> /dev/null | wc -l`
	if [ ${FILE_CNT} -lt ${RIMIT_FILE_CNT} ]; then
		echo "���ʏ��t�@�C���� �F ${FILE_CNT}"
		ERR_FLG="OK"
		break
	fi
	sleep ${RETRY_INTERVAL}
done

if [ ${ERR_FLG} = "NG" ]; then
	echo "���ʏ��t�@�C���� �F ${FILE_CNT}"
	echo "���ʏ��t�@�C������ʂɑؗ����Ă��܂��B�m�F���Ă��������B" > ${DIR_LOG}/${ERR_LOG_FILE_NAME}
fi

rm "${sem}"

exit 0
