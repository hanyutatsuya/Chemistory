#!/bin/sh
############################################################
#
# chk_disk_val.sh �f�B�X�N�e�ʊĎ��V�F��
#
# 2021-06-24 #01    smz   ���[�����M��A�h���X���l���烁�[�����O���X�g�֕ύX
#
############################################################

# �Ď���~�t�@�C���̐ݒ�
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

DIR_LOG="/tmp"
ERR_TMP_FILE_NAME="chk_disk_val"	# �ꎞ�t�@�C���� 

# ��������t�@�C���� ���M���̐��Ɠ������Ƃ邱��
FILE_COUNT=6
# ���M���=( �f�B���N�g�� �������l)
FILE_NO_1=('/' '90')
FILE_NO_2=('/boot/zipl' '50')
FILE_NO_3=('/home' '90')
FILE_NO_4=('/opt' '90')
FILE_NO_5=('/var' '80')
FILE_NO_6=('/apdata' '80')

SLEEP=2

# FTP���M�Ɏg�p����f�[�^
MAILSERVERNAME="kensys02"			# ���M��z�X�g��
USER="merits"						# ���[�U�[
PASSWORD="merits"					# �p�X���[�h
DIR_MAILSERVER="/home/ftp/mail"		# ���M��f�B���N�g����
SEND_FILE_NAME="mail_chk_disk_err"	# �����t�@�C����
SEND_MAIL_LOG="chk_disk_log"		# ���[�����M�t�@�C����

# �[���񎟌��z�񏈗��֐�
array2()
{
	eval y='${'$1$2'['$3']}'
	echo $y
}

# �G���[���[���𑗐M����B
send_ftp()
{
	echo "CODE: SJIS" > ${DIR_LOG}/${SEND_FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOG}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]�}���` �`�o�T�[�o �f�B�X�N�e�� �댯" >> ${DIR_LOG}/${SEND_FILE_NAME}
	echo "BODY: " >> ${DIR_LOG}/${SEND_FILE_NAME}

	echo "���L�A�f�B�X�N�e�ʂ��������l���z���Ă��܂��B�m�F���Ă��������B" >> ${DIR_LOG}/${SEND_FILE_NAME}
	echo "" >> ${DIR_LOG}/${SEND_FILE_NAME}
	cat ${DIR_LOG}/${ERR_TMP_FILE_NAME} >> ${DIR_LOG}/${SEND_FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${MAILSERVERNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_MAILSERVER}
	lcd ${DIR_LOG}
	put ${SEND_FILE_NAME}
	quit
	END_FTP
	# �G���[�����`�F�b�N
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep 1
		return -1
	fi

	echo "�G���[���[���𑗐M���܂����B"

	return 0
}

# �Ď���~�t�@�C���̑��݊m�F�B(�t�@�C�������݂���ꍇ�A�`�F�b�N�����Ȃ��B)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "�Ď���~�t�@�C�������݂��Ă��܂��B"
	exit 0
fi

if [ -e ${DIR_LOG}/${ERR_TMP_FILE_NAME} ]; then
	rm ${DIR_LOG}/${ERR_TMP_FILE_NAME}
fi

for i in  `seq 1 ${FILE_COUNT}`
do
	CHK_DIR="$(array2 FILE_NO_ $i 0)"       # �m�F�f�B���N�g��
	MAX_VAL="$(array2 FILE_NO_ $i 1)"       # �������l

	VAL=`df -Pt ext4 | awk '$6 == "'"${CHK_DIR}"'" {print $5}'`
	VAL=`echo ${VAL} | sed -e 's/%//g'`
	if [ ${VAL} -gt ${MAX_VAL} ]; then
		echo "${CHK_DIR}�F${VAL} (�������l�F${MAX_VAL}%)" >> "${DIR_LOG}/${ERR_TMP_FILE_NAME}"
	fi
done

if [ -e "${DIR_LOG}/${ERR_TMP_FILE_NAME}" ]; then
	# �G���[���[�����M
	send_ftp
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "${ERR_TMP_FILE_NAME} : ���M���s"
	fi
else
	echo "�f�B�X�N�e�ʂ͖�肠��܂���ł����B"
fi

exit 0
