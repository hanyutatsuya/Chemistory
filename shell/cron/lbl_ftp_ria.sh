#!/bin/sh
############################################################
#
# lbl_sh 10�A���x�����M(�q�h�`�T�e���C�g�v�����^�p)
#
############################################################
DIR_LOG="/apdata/aplog"
LOG_FILE_NAME="lbl_ftp_RIA.log" # ���O�t�@�C����

FILE_COUNT=7 # ��������t�@�C���� ���M���̐��Ɠ������Ƃ邱��
# ���M���=( ���M��IP ���[�U�[�� �p�X���[�h ���M��f�B���N�g�� �����t�@�C���� �����Ώۂv�r�R�[�h �\���p�v�r�R�[�h)
#FILE_NO_1=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL21.dat' '0054' '0054')
#FILE_NO_2=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL22.dat' '0151' '0151')
#FILE_NO_3=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL23.dat' '0152' '0152')
#FILE_NO_4=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL03_RIA.dat' '0703' '0703')
#FILE_NO_5=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL04_RIA.dat' '0182' '0182')
#FILE_NO_6=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL11_RIA.dat' '0802' '0802')
#FILE_NO_7=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL24.dat' '0054' '0056')
FILE_NO_1=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL21.dat' '0054' '0054')
FILE_NO_2=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL22.dat' '0151' '0151')
FILE_NO_3=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL23.dat' '0152' '0152')
FILE_NO_4=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL03_RIA.dat' '0703' '0703')
FILE_NO_5=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL08_RIA.dat' '0182' '0182')
FILE_NO_6=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL11_RIA.dat' '0802' '0802')
FILE_NO_7=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL24.dat' '0054' '0056')

# INFO ���t�@�C����
INFO_FILE_NAME="lblinf.dat"

DIR_SJDATA="/apdata/today/file/label/10label"
DIR_CRRNT="/apdata/today/file/label/10label/ftp"
SLEEP=2
# 10�A���x���p�t�@�C���ϊ��V�F��
CONV_SHELL="/home/kea00sys/shell/cron/cnv_lbl_ria.sh"
# ���x��INFO
MAKE_INFO_SHELL="/home/kea00sys/shell/cron/make_lblinfo_ria.sh"

# �[���񎟌��z�񏈗��֐�
array2()
{
  eval y='${'$1$2'['$3']}'
  echo $y
}

# �����Ŏw�肵���t�@�C���𑗐M����B
send_ftp()
{
	SEND_FILE_NAME=$1	

	dateStr=`date +%F_%T%t`
	echo "${dateStr} : �e�s�o���M�X�^�[�g ${SEND_FILE_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}"
	# �e�s�o���M
	/usr/bin/lftp -e 'debug -o /tmp/lbl_ftp_ria.log 3; set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_CRRNT}
	put ${SEND_FILE_NAME}
	quit
	END_FTP
	# �G���[�����`�F�b�N
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		# �G���[�����������ꍇ�͂e�s�o�̑��M���O���c���Ă����B
		echo "${dateStr} : �e�s�o���M�G���[����" >> "${DIR_LOG}/${LOG_FILE_NAME}"
		cat /tmp/lbl_ftp_ria.log >> "${DIR_LOG}/${LOG_FILE_NAME}"
		rm /tmp/lbl_ftp_ria.log
		sleep ${SLEEP}
		return 1
	fi

	# ���푗�M�������ꍇ�͂e�s�o�̃��O���c���Ȃ��B(���O���傫���Ȃ肷���邽��)
	rm /tmp/lbl_ftp_ria.log
	sleep ${SLEEP}
	return 0
}

if [ -e "/tmp/lbl_ftp.sh" ]; then
	exit
fi
# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /${sem}.lock ${sem} || exit
trap "rm ${sem}; exit" 1 2 3 15

for i in  `seq 1 $FILE_COUNT`
do
	HOSTNAME="$(array2 FILE_NO_ $i 0)"		# ���M��z�X�g��
	USER="$(array2 FILE_NO_ $i 1)"			# ���[�U�[
	PASSWORD="$(array2 FILE_NO_ $i 2)"		# �p�X���[�h
	DIR_HOST="$(array2 FILE_NO_ $i 3)"		# ���M��f�B���N�g����
	FILE_NAME="$(array2 FILE_NO_ $i 4)"		# �����t�@�C����
	SMPWS_CODE="$(array2 FILE_NO_ $i 5)"	# ���M�Ώۂv�r�R�[�h
	SMPWS_NAME="$(array2 FILE_NO_ $i 6)"	# �\���p�v�r�R�[�h

	TRNS_NAME="`date +%d%H%M%S`"	# ���M�t�@�C����
	
	echo "${FILE_COUNT} ${HOSTNAME} ${USER} ${PASSWORD} ${DIR_HOST} ${FILE_NAME} ${TRNS_NAME}.dat"

	# File Check
	if [ -r "${DIR_SJDATA}/${FILE_NAME}" ]; then
		dateStr=`date +%F_%T%t`
		echo "$dateStr : �������t�@�C�����݊m�F ${FILE_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}"
	else
		echo "nofile : ${DIR_SJDATA}/${FILE_NAME}"
		continue
	fi

	echo "-----------START------------"

	echo ${FILE_NAME}

	cd "${DIR_SJDATA}"

	# �����ꖢ������ tmp �t�@�C�����c���Ă����ꍇ�́A���l�[�����ĕۑ�����B
	if [ -e "${DIR_SJDATA}/${FILE_NAME}.tmp" ] ; then
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
	fi
	
	mv "${DIR_SJDATA}/${FILE_NAME}" "${DIR_SJDATA}/${FILE_NAME}.tmp"

	# �P�~�X�g���[�p�̃��x�����t�@�C����RIA�p�̃��x�����t�@�C���ɕϊ�
	sh "${CONV_SHELL}" "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_CRRNT}/${TRNS_NAME}.dat" "${SMPWS_CODE}" "${SMPWS_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}" 2>&1
	EXITSTATUS=$?
	if [ ${EXITSTATUS} = "9" ]; then
		# ���M�Ώۂv�r�̃��R�[�h���Ȃ��ꍇ�͏������X���[
		sleep ${SLEEP}
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_CRRNT}/${FILE_NAME}.${TRNS_NAME}"
		continue
	elif [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		# �t�@�C�������ɖ߂�
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	send_ftp "${TRNS_NAME}.dat"
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	# inf �t�@�C���̍쐬
	sh "${MAKE_INFO_SHELL}" "${DIR_CRRNT}" "${TRNS_NAME}.dat" "${SMPWS_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}" 2>&1
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	send_ftp "${INFO_FILE_NAME}"
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_CRRNT}/${FILE_NAME}.${TRNS_NAME}"

	sleep ${SLEEP}
done

rm "${sem}"

exit 0
