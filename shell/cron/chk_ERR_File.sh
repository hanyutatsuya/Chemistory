#!/bin/bash
############################################################
#
# chk_ERR_File.sh �G���[�t�@�C���Ď��V�F��
#
# 2012-02-03 Create H.Sekiya
# 2021-06-24 #01    smz   ���[�����M��A�h���X���l���烁�[�����O���X�g�֕ύX
#
############################################################

# �Ď���~�t�@�C���̐ݒ�
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

ERR_FLG="0"	# �G���[�t�@�C�������݂����痧�Ă�t���O

# �Ď��Ώۂ̐ݒ�
CHK_ERR_DIR=("/apdata/today/online/host/Recv/bun/NG" \
             "/apdata/today/online/host/Recv/3id/NG" \
             "/apdata/today/file/NSWS/Send/RkInfo/Multi/Err" \
             "/apdata/today/file/NSWS/Send/RkInfo/Single/Err" \
             "/apdata/today/file/NSWS/Send/RkInfo/Single2/Err" \
             "/apdata/today/file/NSWS/Send/TrInfo/Multi/Err" \
             "/apdata/today/file/NSWS/Send/TrInfo/Single/Err" \
             "/apdata/today/file/NSWS/Send/TrInfo/Single2/Err" \
             "/apdata/today/file/NSWS/Recv/TrRk/Err" \
             "/apdata/today/file/NSWS/Recv/Stocker/Err" )
#
CHK_DIR_NUM=${#CHK_ERR_DIR[*]}
CHK_DIR_NUM=`expr ${CHK_DIR_NUM} - 1`

# �ꎞ�t�@�C��
ERR_LOG="err_file_log"			# ���݂��Ă��郍�O�t�@�C�������i�[

# FTP���M�Ɏg�p����f�[�^
HOSTNAME="kensys02"				# ���M��z�X�g��
USER="merits"					# ���[�U�[
PASSWORD="merits"				# �p�X���[�h
DIR_HOST="/home/ftp/mail"		# ���M��f�B���N�g����
DIR_LOCAL="/tmp"				# ���[�J���t�@�C����
SEND_FILE_NAME="mail_send_err"	# �����t�@�C����
BIN_MODE="binary"				# ���M���[�h

if [ -e ${DIR_LOCAL}/${ERR_LOG} ]; then
	rm ${DIR_LOCAL}/${ERR_LOG}
fi

# �Ď���~�t�@�C���̑��݊m�F�B(�t�@�C�������݂���ꍇ�A�`�F�b�N�����Ȃ��B)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "�Ď���~�t�@�C�������݂��Ă��܂��B"
	exit 0
fi

# �G���[�f�B���N�g���Ƀt�@�C�������݂��Ă��Ȃ����m�F
for DIR_CNT in `seq 0 ${CHK_DIR_NUM}`;
do
	ls ${CHK_ERR_DIR[${DIR_CNT}]}/*
	RET_STATUS=$?
	if [ ${RET_STATUS} = "0" ]; then
		ERR_FLG="1"
		ls ${CHK_ERR_DIR[${DIR_CNT}]}/* >> ${DIR_LOCAL}/${ERR_LOG}
		echo "" >> ${DIR_LOCAL}/${ERR_LOG}
	fi
done

# �G���[�t�@�C�������݂����ꍇ�̓��[���𑗐M����B
if [ ${ERR_FLG} = "1" ]; then

	echo "CODE: SJIS" > ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]�}���` �G���[�t�@�C�� ��" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "BODY: " >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	cat ${DIR_LOCAL}/${ERR_LOG} >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "��L�A�G���[�t�@�C�������݂��Ă��܂��B�m�F���Ă��������B" >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${SEND_FILE_NAME}
	quit
	END_FTP

	echo "�G���[�t�@�C�������݁B���[���𑗐M���܂����B"

	rm ${DIR_LOCAL}/${SEND_FILE_NAME}
	rm ${DIR_LOCAL}/${ERR_LOG}
	
	exit 0

fi

echo "�G���[�t�@�C���͑��݂��܂���ł����B"
exit 0
