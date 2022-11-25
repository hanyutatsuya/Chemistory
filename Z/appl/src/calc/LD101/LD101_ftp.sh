#!/bin/sh
############################################################
#
#  �����C�����t�@�C�����M�p�V�F��
#
############################################################
#export GET_FILE="PNCID.FAXY.JCL(FAXY100)"
export GET_FILE="PNC.FAXY.JCL(FAXY100)"
export TRNS_FILE="FAXY100.TXT"

DIR_LOG="/apdata/aplog"
FILE_LOG_NAME="LD101_ftp_"
FILE_ERRLOG_NAME="FATAL_LD101_ftp_ERR"

#SEND_HOST="172.17.0.2"
SEND_HOST="172.17.0.1"
SEND_PORT="4021"
USER="IRAI"
PASS="IRAI"

FILE_DIR="/apdata/today/file/list"
FILE="HOKO.ZKSYU.FAX.INPUT.A00.SB"

LOG_DATE=`date "+%Y%m%d"`

get_ftp()
{
	# �f�[�^�t�@�C���ƃR�}���h�t�@�C���𑗐M(�R�}���h�ŃG���[�����������璆�f)
	/usr/bin/lftp -e 'debug 5; set net:reconnect-interval-base 5; set net:max-retries 5; set xfer:clobber on; set cmd:fail-exit yes' ${SEND_HOST} -p ${SEND_PORT} <<-END_FTP
	user "${USER}" "${PASS}"
	lcd "${FILE_DIR}"
	quote type b 1
	get "'${GET_FILE}'" -o "${TRNS_FILE}"
	quote type b 1
	put ${FILE} -o "'${FILE}'"
	quote SITE FILETYPE=JES
	quote type b 1
	put "${TRNS_FILE}"
	quit
END_FTP
	# �G���[�����`�F�b�N
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		return 1
	fi
	return 0
}

cd ${FILE_DIR}

echo `date "+%Y/%m/%d %H:%M:%S"`" : ${SENDHOSTNAME} : �t�@�C�����M�J�n " >> ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log"

get_ftp >>  ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log" 2>&1
EXITSTATUS=$?
if [ ${EXITSTATUS} != "0" ]; then
	echo `date "+%Y/%m/%d %H:%M:%S"`" : ${SENDHOSTNAME} : �t�@�C�����擾�ł��܂���B" >> ${DIR_LOG}/${FILE_ERRLOG_NAME}${LOG_DATE}".log"
	exit 1
fi

echo `date "+%Y/%m/%d %H:%M:%S"`" : ${SENDHOSTNAME} : �t�@�C�����M�I�� " >> ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log"

exit 0
