#!/bin/sh
############################################################
#
# chk_IA_Log.sh �h�`�T�[�o�G���[�t�@�C����M�p�V�F��
#
############################################################

# �Ď���~�t�@�C���̐ݒ�
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

DIR_LOG="/apdata/aplog"
LOG_FILE_NAME="chk_IA.log"				# ���O�t�@�C����
ERR_LOG_FILE_NAME="FATAL_chk_IA.log"	# ���[�����M�t�@�C����
#ERR_LOG_FILE_NAME="TST_chk_IA.log"		# ���[�����M�t�@�C����(�e�X�g�p)

# ��������t�@�C���� ���M���̐��Ɠ������Ƃ邱��
FILE_COUNT=5
# ���M���=( ���M��IP ���[�U�[�� �p�X���[�h ��M���f�B���N�g�� ��M�Ώۃt�@�C���� )
FILE_NO_1=('10.1.181.41' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA21.log')
FILE_NO_2=('10.1.181.42' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA22.log')
FILE_NO_3=('10.1.181.43' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA23.log')
FILE_NO_4=('10.1.181.44' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA24.log')
FILE_NO_5=('10.1.181.41' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_CS_ERR.log')

DIR_HOST="/apdata/aplog"

SLEEP=2

# �[���񎟌��z�񏈗��֐�
array2()
{
	eval y='${'$1$2'['$3']}'
	echo $y
}

# �����Ŏw�肵���t�@�C������M����B
get_ftp()
{
	GET_END_FILE_NAME=${FILE_NAME}.`date '+%y%m%d%H%M%S'`

	dateStr=`date +%F_%T%t`
	# �e�s�o��M
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" >"${DIR_LOG}/IA_check_work" 2>&1 <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_IA}
	lcd ${DIR_HOST}
	get ${FILE_NAME} ${FILE_NAME}_EUC
	rename ${FILE_NAME} ${GET_END_FILE_NAME}
	quit
	END_FTP

	if [ -e "${DIR_HOST}/${FILE_NAME}_EUC" ]; then 
		/usr/bin/iconv -f EUC-JP-MS -t IBM943 "${DIR_HOST}/${FILE_NAME}_EUC" > ${DIR_HOST}/${FILE_NAME}
		rm ${DIR_HOST}/${FILE_NAME}_EUC
	fi

	sleep ${SLEEP}
	return 0
}

# �Ď���~�t�@�C���̑��݊m�F�B(�t�@�C�������݂���ꍇ�A�`�F�b�N�����Ȃ��B)
if [ -e $STOP_DIR/$STOP_FILE_NAME ]; then
	echo "�Ď���~�t�@�C�������݂��Ă��܂��B"
	exit 0
fi

for i in  `seq 1 ${FILE_COUNT}`
do
	HOSTNAME="$(array2 FILE_NO_ $i 0)"		# ��M��z�X�g��
	USER="$(array2 FILE_NO_ $i 1)"			# ���[�U�[
	PASSWORD="$(array2 FILE_NO_ $i 2)"		# �p�X���[�h
	DIR_IA="$(array2 FILE_NO_ $i 3)"		# ��M��f�B���N�g����
	FILE_NAME="$(array2 FILE_NO_ $i 4)"		# ��M�t�@�C����

	echo "${FILE_COUNT} ${HOSTNAME} ${USER} ${PASSWORD} ${DIR_IA} ${FILE_NAME}"

	if [ -e "${DIR_HOST}/${FILE_NAME}" ]; then
		echo "�t�@�C�������݂��Ă��܂��B ${DIR_HOST}/${FILE_NAME}"
		continue
	fi

	ping -c 3 ${HOSTNAME} > /dev/null
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "${HOSTNAME} : ���ʂ��m�F�ł��܂���B" >> "${DIR_LOG}/IA_check_err"
		continue
	fi

	GET_END_FILE_NAME=${FILE_NAME}.`date '+%y%m%d%H%M%S'`

	dateStr=`date +%F_%T%t`
	# �e�s�o��M
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_IA}
	lcd ${DIR_HOST}
	get ${FILE_NAME} ${FILE_NAME}_EUC
	mv ${FILE_NAME} ${GET_END_FILE_NAME}
	quit
	END_FTP

	if [ -e "${DIR_HOST}/${FILE_NAME}_EUC" ]; then 
		/usr/bin/iconv -f EUC-JP-MS -t IBM943 "${DIR_HOST}/${FILE_NAME}_EUC" > ${DIR_HOST}/${FILE_NAME}
		rm ${DIR_HOST}/${FILE_NAME}_EUC
	fi

	sleep ${SLEEP}
done

if [ -e "${DIR_HOST}/IA_check_err" ]; then
	mv "${DIR_HOST}/IA_check_err" "${DIR_HOST}/${ERR_LOG_FILE_NAME}" 
fi

exit 0
