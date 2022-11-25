#!/bin/bash
############################################################
#
# chk_FATAL_Log.sh �v���I�G���[���O�Ď��V�F��
#
# 2012-02-03 Create H.Sekiya
# 2021-06-24 #01    smz   ���[�����M��A�h���X���l���烁�[�����O���X�g�֕ύX
#
############################################################

# �Ď���~�t�@�C���̐ݒ�
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

ERR_FLG="0"	# �G���[���O�����݂����痧�Ă�t���O

# �Ď��Ώۂ̐ݒ�
DIR_LOG="/apdata/aplog"
NAME_ERRLOG="FATAL"
EXTENSION_LOG=".log"
EXTENSION_LOG_SUMI=".end"

# �ꎞ�t�@�C��
ERR_LOG="fatal_log"				# ���݂��Ă��郍�O�t�@�C�������i�[

# FTP���M�Ɏg�p����f�[�^
HOSTNAME="kensys02"				# ���M��z�X�g��
USER="merits"					# ���[�U�[
PASSWORD="merits"				# �p�X���[�h
DIR_HOST="/home/ftp/mail"		# ���M��f�B���N�g����
DIR_LOCAL="/tmp"				# ���[�J���t�@�C����
#SEND_FILE_NAME="mail_send_err"	# �����t�@�C����
#���M�t�@�C����������ڂ��̂ŕύX	2021.07.06	Hanyu
SEND_FILE_NAME="A00_error_mail_"`date +'%Y%m%d_%H%M%S'`		# �����t�@�C����

# �Ď���~�t�@�C���̑��݊m�F�B(�t�@�C�������݂���ꍇ�A�`�F�b�N�����Ȃ��B)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "�Ď���~�t�@�C�������݂��Ă��܂��B"
	exit 0
fi

# Log�f�B���N�g���ɃG���[���O�����݂��Ă��Ȃ����m�F
ls ${DIR_LOG}/${NAME_ERRLOG}*${EXTENSION_LOG} > ${DIR_LOCAL}/${ERR_LOG}
RET_STATUS=$?
if [ ${RET_STATUS} = "0" ]; then
	ERR_FLG="1"
	cat  ${DIR_LOCAL}/${ERR_LOG}
fi

# �G���[���O�����݂����ꍇ�̓��[���𑗐M����B
if [ ${ERR_FLG} = "1" ]; then
	echo "CODE: SJIS" > ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]�}���` �G���[���O ��" >> ${DIR_LOCAL}/${SEND_FILE_NAME} 
	echo "BODY: " >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	while read MOTO_RECORD
	do
		echo -e "[ ${MOTO_RECORD} ]" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "-------------------------------------------------------------------" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		cat "${MOTO_RECORD}" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "-------------------------------------------------------------------" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	done < ${DIR_LOCAL}/${ERR_LOG}

	echo "��L�A�G���[���O�����݂��Ă��܂��B�m�F���Ă��������B" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${SEND_FILE_NAME}
	quit
	END_FTP
#	�G���[�����`�F�b�N
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "�G���[���[���̑��M�Ɏ��s���܂����B"
		exit 1
	fi

	echo "�G���[���O�����݁B���[���𑗐M���܂����B"
	# �p�g�����v�_����ǉ� 20210705
	/usr/bin/rsh -l root 10.1.51.157 ACOP 01010000

	# �G���[���O�𑗐M�ς݂̏�ԂɃ��l�[������B
	for MOTO_FILE_NAME in `cat ${DIR_LOCAL}/${ERR_LOG}`
	do
		MOVE_FILE_NAME=`echo ${MOTO_FILE_NAME} | sed -e "s/${EXTENSION_LOG}$/${EXTENSION_LOG_SUMI}/g"`.`date +"%Y%m%d%H%M%S"`
		mv ${MOTO_FILE_NAME} ${MOVE_FILE_NAME}
	done

	echo "�G���[���O�𑗐M�ς݂Ƀ��l�[�����܂����B"

	rm ${DIR_LOCAL}/${SEND_FILE_NAME}
	rm ${DIR_LOCAL}/${ERR_LOG}
	
	exit 0

fi

echo "�G���[���O�͑��݂��܂���ł����B"
exit 0
