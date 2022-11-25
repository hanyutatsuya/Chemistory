#!/bin/bash -

#######################################################################
# �V�P�O�A���x���V�X�e���p�t�@�C���ϊ��V�F��
# $1 : �ϊ����t�@�C�� ���݃f�B���N�g��
# $1 : �ϊ����t�@�C����
#######################################################################

# �o�͏��t�@�C����(�t���p�X)
INFO_FILE_NAME="lblinf.dat"
DIR_LOG="/apdata/aplog"

# INFO�t�@�C����`
SYSDATETIME=""		# �쐬�� �쐬���� yymmddhhmmss
MAKSBT=""			# �쐬��� �O�Œ�
KNSSBT=""			# ������� �O�Œ�
OUTPUT=""			# �o�̓t���O �O�Œ�
WSTNAME=""			# ���[�N�V�[�g�� �� ���M�t�@�C����
WSTCODE=""			# ���[�N�V�[�g�R�[�h
LBLFNAME=""			# ���x���t�@�C����
BCDFNAME=""			# �o�[�R�[�h�t�@�C���� 

SEND_FILE_DIR=$1	# ���M�Ώ� �t�@�C�����݃f�B���N�g��
SEND_FILE=$2		# ���M�Ώ� �t�@�C����
SMPWS_NAME=$3		# �T���v�����O�v�r��
START_SEQ=""		# ���M�Ώ� �J�n�r�d�p
END_SEQ=""			# ���M�Ώ� �I���r�d�p

if [ ! -e $1 ]; then
    echo "$1 NOT found."
	exit 1
fi

# lblinf.dat ���̏o��
SYSDATETIME=`date '+%y%m%d%H%M%S'`
MAKSBT="0"
KNSSBT="0"
OUTPUT="0"
START_SEQ_TMP=`head -n 1 ${SEND_FILE_DIR}/${SEND_FILE} | cut -c8-12`
START_SEQ=`expr ${START_SEQ_TMP} + 0`									# ���M�t�@�C���̊J�n�r�d�p
END_SEQ_TMP=`tail -n 1 ${SEND_FILE_DIR}/${SEND_FILE} | cut -c8-12`
END_SEQ=`expr ${END_SEQ_TMP} + 0`										# ���M�t�@�C���̏I���r�d�p
RECORD_COUNT=`wc -l < ${SEND_FILE_DIR}/${SEND_FILE}`
WSTNAME="SEQ ${START_SEQ}-${END_SEQ} (${RECORD_COUNT})"
WSTCODE="${SMPWS_NAME}"
LBLFNAME="${SEND_FILE}"
BCDFNAME=""

# �V10�A���x���V�X�e���p�t�@�C�� ���̏o��
printf "%-12s%-1s%-1s%-1s%-20s%-7s%-12s%-12s\r\n" "${SYSDATETIME}" "${MAKSBT}" "${KNSSBT}" "${OUTPUT}" "${WSTNAME}" "${WSTCODE}" "${LBLFNAME}" "${BCDFNAME}" >> "${SEND_FILE_DIR}/WORK1"
EXITSTATUS=$?
if [ $EXITSTATUS != "0" ]; then
	exit 1
fi

# inf�t�@�C�� ��EUC�R�[�h�ɕϊ�
/usr/bin/iconv -f IBM943 -t EUC-JP-MS "${SEND_FILE_DIR}/WORK1" >> "${SEND_FILE_DIR}/WORK2"
EXITSTATUS=$?
if [ $EXITSTATUS != "0" ]; then
	exit 1
fi

if [ ! -e ${SEND_FILE_DIR}/${INFO_FILE_NAME} ]; then
	cat "${SEND_FILE_DIR}/WORK2" | sort -rk 1,12 -k 35,39 -o "${SEND_FILE_DIR}/WORK3"
else
	cat "${SEND_FILE_DIR}/WORK2" "${SEND_FILE_DIR}/${INFO_FILE_NAME}" | sort -rk 1,12 -k 35,39 -o "${SEND_FILE_DIR}/WORK3"
fi

mv "${SEND_FILE_DIR}/WORK3" "${SEND_FILE_DIR}/${INFO_FILE_NAME}"

rm "${SEND_FILE_DIR}/WORK1"
rm "${SEND_FILE_DIR}/WORK2"

exit 0
