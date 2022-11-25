#!/bin/sh
############################################################
#
#  ���{�����������t�@�C����M�p�V�F��
# $1 : �����o�b�N�A�b�v�f�B���N�g��
############################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

# ��������t�@�C���� ���M���̐��Ɠ������Ƃ邱��
FILE_COUNT=1
# ���M���=( ���M��IP ���[�U�[�� �p�X���[�h ��M���f�B���N�g�� ��M�Ώ�ID )
#FILE_NO_1=('10.1.42.134' 'kikan' 'kikan' '/home/kikan/Data/rireki/send/001' 'A00')
FILE_NO_1=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/rireki/send/001' 'A00')

DIR_DAILY=$1

SLEEP=2

# �[���񎟌��z�񏈗��֐�
array2()
{
	eval y='${'$1$2'['$3']}'
	echo $y
}

######################################################################################
# �ݒ肳��Ă���t�@�C������M����B
######################################################################################
get_ftp()
{
	# �e�s�o��M
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_KIKAN}
	lcd ${DIR_DAILY}
	mget -E *_${FILE_ID}.dat
	mget -E *_${FILE_ID}.trg
	quit
	END_FTP
	# �G���[�����`�F�b�N
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		return 1
	fi

	# �t�@�C���̌����`�F�b�N
	chk_file
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		return 1
	fi

	sleep ${SLEEP}
	return 0
}

######################################################################################
# trg �t�@�C�����̌����� dat �t�@�C�����̃��R�[�h�����r���� 
######################################################################################
chk_file()
{

	cd ${DIR_DAILY}

	for TRG_FILE_NAME in `ls *.trg`
	do
		FILE_BASENAME=`basename ${TRG_FILE_NAME} .trg`
		TRG_FILE_CNT=`cat ${FILE_BASENAME}.trg`
		DAT_FILE_CNT=`wc -l < ${FILE_BASENAME}.dat`
		if [ ${TRG_FILE_CNT} != ${DAT_FILE_CNT} ]; then
			echo "${TRG_FILE_NAME}:�����������Ă��܂���B" > "${LOG_DIR}/${NAME_ERRLOG}get_rireki_ftp"
			return 1
		fi
	done

}

######################################################################################
# main ����
######################################################################################
# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /${sem}.lock ${sem} || exit
trap "rm ${sem}; exit" 2 3 15

for i in  `seq 1 ${FILE_COUNT}`
do
	HOSTNAME="$(array2 FILE_NO_ $i 0)"		# ��M��z�X�g��
	USER="$(array2 FILE_NO_ $i 1)"			# ���[�U�[
	PASSWORD="$(array2 FILE_NO_ $i 2)"		# �p�X���[�h
	DIR_KIKAN="$(array2 FILE_NO_ $i 3)"		# ��M��f�B���N�g����
	FILE_ID="$(array2 FILE_NO_ $i 4)"		# ��M�t�@�C����

	echo "�����t�@�C���擾�J�n"

	get_ftp
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "${HOSTNAME} : �t�@�C�����擾�ł��܂���B" >> ${LOG_DIR}/${NAME_ERRLOG}"get_rireki_ftp.log"
		rm "${sem}"
		exit 1
	fi

	echo "�����t�@�C���擾�I��"


	sleep ${SLEEP}
done

rm "${sem}"
exit 0
