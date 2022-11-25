#!/bin/bash
############################################################
#
# chk_proc.sh �v���Z�X�N���󋵊Ď��V�F��
#
# 2009-09-25 Create �։�
# 2021-06-24 #01    smz   ���[�����M��A�h���X���l���烁�[�����O���X�g�֕ύX
#
############################################################

# �Ď���~�t�@�C���̐ݒ�
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"
STOP_LD104_FILE_NAME="STOP_LD104"	# LD104 ���ʗv���J�[�h�쐬��p�̊Ď���~�t�@�C��(���j����̂ݒ�~����)

ZOKCHK_LIST_FILE="/apdata/today/file/list/HOKO.ZKSYU.FAX.INPUT.A00.SB"		# �����G���[���X�g�t�@�C��

# �ڑ���c�a�̏��
DB_NAME="kea00db"
DB_USER="db2inst1"
DB_PASS="db2inst1"

# �t���O
UNYFLG="0"	# �V�X�e���Ǘ��}�X�^ �^�p�t���O�̏�
ERR_FLG="0"	# �N�����Ă��Ȃ��v���Z�X�����݂����痧�Ă�t���O

# �v���Z�X�ꗗ(�ً}�֘A�̃v���Z�X�͌���ŋN���A��~���ł��邽�߁A�Ώۂ��珜�O����B)
PROC_Z_ID=(AD102 AD103 AD105 AD106 AD107 AD108 AD301 BD301 BD302 BD401 DD401 FD101 FD103 JD112 GD102 GD105 ZD101 LD101 LD103 LD104 LD105 LD106 MD101_L1 MD101_L2 MD102_L1 MD102_L2 MD103 MD104 MD105 ND101 ND102 hulsndd hulobsd hulrcvd)
PROC_Z_NM=(�˗��W�J ���ғW�J �����W�J �����W�J_���v���Z�X �R�h�c��M �R�h�c�W�J �v���J�[�h�쐬 �����X�g�b�J ����X�g�b�J �T���v�� ���ʓo�^ �Ď��o�b�` �����Z�� �����i�s�󋵏W�v HULFT���M �������ʕ� ���O�o�� �����G���[�`�F�b�N �����C�����擾 ���ʗv���J�[�h�쐬 ���T�e���C�g���ʏ��擾 �Čv�Z���� �y�r�I�����C���P �y�r�I�����C���Q �y�r�Č�����P �y�r�Č�����Q �y�r�p�����g���[�o�^ �y�r�p���[�g���[�o�^ �y�r�p���ʓo�^ �t�����e�B�A���b�N�o�^ �I�[�_�[���b�N�o�^ HULFT_SND HULFT_OBS HULFT_RCV)
PROC_Z_NUM=${#PROC_Z_ID[*]}	# �v���Z�X�̐�
PROC_Z_NUM=`expr ${PROC_Z_NUM} - 1`

# �ꎞ�t�@�C��
SELECT_UNY="select_uny"		# ���������`�F�b�N����r�p�k�̌��ʂ��i�[
SELECT_BCHEND="select_bchend"	# �����d�m�c��M�ォ�ǂ����`�F�b�N����r�p�k�̌��ʂ��i�[
PS_KEKKA="ps_kekka" 		# �N�����v���Z�X�ꗗ
ERR_APPL="err_appl"		# �ُ�I�����Ă���v���Z�X���i�[

# FTP���M�Ɏg�p����f�[�^
HOSTNAME="kensys02"		# ���M��z�X�g��
USER="merits"			# ���[�U�[
PASSWORD="merits"		# �p�X���[�h
DIR_HOST="/home/ftp/mail"	# ���M��f�B���N�g����
DIR_LOCAL="/tmp"		# ���[�J���t�@�C����
FILE_NAME="mail_send_err"	# �����t�@�C����

# cron ����N������ shell �� DB2 �ɃA�N�Z�X����ꍇ�ɕK�v
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

# �Ď���~�t�@�C���̑��݊m�F�B(�t�@�C�������݂���ꍇ�A�`�F�b�N�����Ȃ��B)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "�Ď���~�t�@�C�������݂��Ă��܂��B"
	exit 0
fi

# ���������ǂ����`�F�b�N
db2 connect to ${DB_NAME} user ${DB_USER} using ${DB_PASS}
db2 "select UNYFLG from sysknrmst for read only" | grep ^[0-9] | sed 's/ //g' > ${DIR_LOCAL}/${SELECT_UNY}
db2 terminate
# �������̏ꍇ�͏I������B
UNYFLG=`cat ${DIR_LOCAL}/${SELECT_UNY}`
if [ ${UNYFLG} = "1" ]; then
	rm ${DIR_LOCAL}/${SELECT_UNY}
	echo "�������Ȃ̂ŁA�������I�����܂����B" 
	exit 0
fi

rm ${DIR_LOCAL}/${SELECT_UNY}

ps ax > ${DIR_LOCAL}/${PS_KEKKA}
for ps_cnt in `seq 0 ${PROC_Z_NUM}`;
do
	grep ${PROC_Z_ID[$ps_cnt]} ${DIR_LOCAL}/${PS_KEKKA}
	RET_STATUS=$?
	if [ ${RET_STATUS} = "1" ]; then
		if [ ${PROC_Z_ID[$ps_cnt]} = "AD301" ] || [ ${PROC_Z_ID[$ps_cnt]} = "ND101" ] ; then
			# �v���J�[�h�쐬�v���Z�X�͕����d�m�c�����Ă��Ȃ��������G���[�Ƃ���B
			db2 connect to ${DB_NAME} user ${DB_USER} using ${DB_PASS}
			db2 "select BCHENDFLG from sysknrmst for read only" | grep ^[0-9] | sed 's/ //g' > ${DIR_LOCAL}/${SELECT_BCHEND}
			db2 terminate
			BCHENDFLG=`cat ${DIR_LOCAL}/${SELECT_BCHEND}`
			if [ ${BCHENDFLG} = "0" ]; then
				ERR_FLG="1"
				echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
			fi
			rm ${DIR_LOCAL}/${SELECT_BCHEND}
		elif [ ${PROC_Z_ID[$ps_cnt]} = "LD101" ]; then
			# �����G���[�`�F�b�N�v���Z�X�͑����G���[���X�g�t�@�C�����쐬����Ă��Ȃ��������G���[�Ƃ���B
			if [ ! -e ${ZOKCHK_LIST_FILE} ]; then
				ERR_FLG="1"
				echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
			fi
		elif [ ${PROC_Z_ID[$ps_cnt]} = "LD104" ]; then
			# ���ʗv���J�[�h�쐬�͐�p�̊Ď���~�t�@�C�����쐬����Ă��Ȃ��������G���[�Ƃ���B
			# ���j���̖�Ƀz�X�g�֗v���J�[�h�𑗐M����ƃG���[�ɂȂ錏�ɂ��Ă̑Ή�
			if [ ! -e ${STOP_DIR}/${STOP_LD104_FILE_NAME} ]; then
				ERR_FLG="1"
				echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
			fi
		else
			ERR_FLG="1"
			echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
		fi
	fi
done

rm ${DIR_LOCAL}/${PS_KEKKA}

# �N�����Ă��Ȃ��v���Z�X�����݂����ꍇ�̓��[���𑗐M����B
if [ ${ERR_FLG} = "1" ]; then
	echo "CODE: SJIS" > ${DIR_LOCAL}/${FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOCAL}/${FILE_NAME}
	echo "SUBJECT: [`date`]�}���`�ُ��" >> ${DIR_LOCAL}/${FILE_NAME}
	echo "BODY: " >> ${DIR_LOCAL}/${FILE_NAME}

	cat ${DIR_LOCAL}/${ERR_APPL} >> ${DIR_LOCAL}/${FILE_NAME}

	echo "" >> ${DIR_LOCAL}/${FILE_NAME}
	echo "��L�v���Z�X���N�����Ă��܂���B�m�F���Ă��������B" >> ${DIR_LOCAL}/${FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${FILE_NAME}
	quit
	END_FTP

	rm ${DIR_LOCAL}/${ERR_APPL}
	rm ${DIR_LOCAL}/${FILE_NAME}

	echo "�ُ�I���v���Z�X�����݁B���[���𑗐M���܂����B"
	exit 0

fi

echo "�ُ�I���v���Z�X�͑��݂��܂���ł����B"
exit 0
