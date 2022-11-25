#!/bin/bash
############################################################
#
# chk_STOP_File.sh �v���Z�X�Ď���~ �m�F�V�F��
#
# 2016-04-07 Create H.Sekiya
# 2021-06-24 #01    smz   ���[�����M��A�h���X���l���烁�[�����O���X�g�֕ύX
#
# �Ď���~�t�@�C�������݂��Ă���ꍇ�Ɍx�����[���𑗐M����B
# �Ď��������~�����܂܁A�ĊJ����̂�Y��Ȃ��悤�ɂ��邽�߁A
# ������m�F����悤�ɐݒ肷��B
############################################################

# �Ď��Ώۂ̐ݒ�
CHK_DIR_Z="/home/kea00sys/shell/cron"

IA_CNT="4"
CHK_IA=(KEA00IAW21.bml.co.jp KEA00IAW22.bml.co.jp KEA00IAW23.bml.co.jp KEA00IAW24.bml.co.jp)
CHK_DIR_IA="/home/kea00sys/shell"

STOP_FILE_NAME="STOP"
STOP_LD104_FILE_NAME="STOP_LD104"

# FTP���M�Ɏg�p����f�[�^
HOSTNAME="kensys02"					# ���M��z�X�g��
USER="merits"						# ���[�U�[
PASSWORD="merits"					# �p�X���[�h
DIR_HOST="/home/ftp/mail"			# ���M��f�B���N�g����
DIR_LOCAL="/tmp"					# ���[�J���t�@�C����
SEND_FILE_NAME="mail_chk_stop"		# �����t�@�C����
SEND_FILE_BODY="mail_chk_stop_body"	# �����t�@�C����(�{��)

# �O��̏����������[�������M�Ŏc���Ă����ꍇ�͏����𔲂���B
if [ -e ${DIR_LOCAL}/${SEND_FILE_NAME} ]; then
	exit 0
fi

# �v���Z�X�Ď���~�t�@�C�������݂����ꍇ�̓��[���𑗐M����B(�`�o�T�[�o)
if [ -e ${CHK_DIR_Z}/${STOP_FILE_NAME} ]; then
	echo "kea00apa : ${CHK_DIR_Z}/${STOP_FILE_NAME}" >> ${DIR_LOCAL}/${SEND_FILE_BODY}
fi

# �v���Z�X�Ď���~�t�@�C��(LD104�p)�����݂����ꍇ�̓��[���𑗐M����B(�`�o�T�[�o)
if [ -e ${CHK_DIR_Z}/${STOP_LD104_FILE_NAME} ]; then
	echo "kea00apa : ${CHK_DIR_Z}/${STOP_LD104_FILE_NAME}" >> ${DIR_LOCAL}/${SEND_FILE_BODY}
fi

# �v���Z�X�Ď���~�t�@�C�������݂����ꍇ�̓��[���𑗐M����B(�h�`�T�[�o)
for i in `seq 0 $((${IA_CNT} - 1))`;
do
	RET=`rsh ${CHK_IA[$i]} "ls ${CHK_DIR_IA}/${STOP_FILE_NAME}"`
	if [ ! -z ${RET} ]; then
		echo "${CHK_IA[$i]} : ${CHK_DIR_IA}/${STOP_FILE_NAME}" >> ${DIR_LOCAL}/${SEND_FILE_BODY}
	fi
done

if [ -e ${DIR_LOCAL}/${SEND_FILE_BODY} ]; then
	echo "CODE: SJIS" > ${DIR_LOCAL}/${SEND_FILE_NAME} 
	echo "TO: multi_log@bml.co.jp" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]�}���` �`�o�T�[�o �G���[�Ď� ��~" >> ${DIR_LOCAL}/${SEND_FILE_NAME} 
	echo "BODY: " >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "�v���Z�X�Ď�����~���Ă��܂��B" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "�Ď����ĊJ����ɂ́A���L�̃t�@�C�����폜���ĉ������B" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	cat ${DIR_LOCAL}/${SEND_FILE_BODY} >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${SEND_FILE_NAME}
	quit
	END_FTP

	echo "�Ď���~�t�@�C�������݁B���[���𑗐M���܂����B"
	rm ${DIR_LOCAL}/${SEND_FILE_BODY}
	rm ${DIR_LOCAL}/${SEND_FILE_NAME}
fi

exit 0
