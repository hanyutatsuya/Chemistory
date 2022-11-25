#!/bin/bash
################################################################
#
# chk_daily_end.sh ���������Ď��V�F��
#
# 2014-07-01 Create H.Sekiya
#
# 2016-07-22 Update H.Sekiya
#             �E�����f�[�^�̃o�b�N�A�b�v�����擾�@�\�ǉ�
#
# 2021-07-06 Update Hanyu
#	���O�t�@�C���̃^�C���X�^���v�`�F�b�N��ǉ�
#
################################################################

# �Ď��Ώۂ̐ݒ�
DIR_OLDDAY="/apdata/oldday"
# �Ď��Ώۂ̓������O�t�@�C����
DAILY_LOG="daily.log"
# �Ď��Ώۂ̃��[�h
DAILY_END_WORD="�������� --- �I��"
# �G���[���̏o�̓��O��
DIR_ERRLOG="/apdata/aplog"
NAME_ERRLOG="FATAL_DAILY_"`date +'%Y%m%d_%H%M%S'`
NAME_WARNLOG="WARNING_DAILY_"`date +'%Y%m%d_%H%M%S'`
EXTENSION_LOG=".log"

# �o�b�N�A�b�v��ݒ� 
BKUP_SERVER="10.1.181.22"
BKUP_PATH="/mnt/usb/bak_daily"

# �o�b�N�A�b�v��ݒ�ǉ�(nfs �� mount ���Ă���f�B���N�g���j
BKUP_PATH2="/apdata/today/file/KEA00/KEA00IAW02/bak_daily/"

# �o�b�N�A�b�v�Ώۂ��ǂ����i0:�ΏۊO 1:�Ώہj
FLG_COPY="1"

# oldday ���ɑ��݂�������o�b�N�A�b�v�f�B���N�g������������B
ls -F ${DIR_OLDDAY} | grep / | grep -v kekka_out | grep -v rack_out > ${DIR_ERRLOG}/tmp_DAILY_DIR.$$

# �����o�b�N�A�b�v�f�B���N�g�������[�v
for DAILY_DIR  in `cat ${DIR_ERRLOG}/tmp_DAILY_DIR.$$ | sed -e "s/\///g"`
do
	# �������O�t�@�C���̒��ɏI�����b�Z�[�W�����݂��邩�m�F�B
	grep "${DAILY_END_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -ne "0" ]; then
		#���O�t�@�C���̃^�C���X�^���v�ƌ��ݓ������r
		#�P�T���ȓ��Ȃ�n�j�Ƃ���
		RSTAMP=`date '+%s'`
		RSTAMP=$((RSTAMP-900))
		FSTAMP=`date '+%s' -r ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}`
		if [ ${RSTAMP} -gt ${FSTAMP} ]; then
			ERROR_LOG=${NAME_ERRLOG}${DAILY_DIR}${EXTENSION_LOG}
			echo "<<<<<  ���������`�F�b�N���[��  >>>>>" > ${DIR_ERRLOG}/${ERROR_LOG}
			echo "����������ɏI����Ă��Ȃ��\��������܂��B" >> ${DIR_ERRLOG}/${ERROR_LOG}
			echo "${DAILY_DIR} ���O���m�F���ĉ������B" >> ${DIR_ERRLOG}/${ERROR_LOG}
			tail -n 15 ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} >> ${DIR_ERRLOG}/${ERROR_LOG}
		else
			ERROR_LOG=${NAME_WARNLOG}${DAILY_DIR}${EXTENSION_LOG}
			echo "<<<<<  ���������`�F�b�N�x�����[��  >>>>>" > ${DIR_ERRLOG}/${ERROR_LOG}
			echo "����������ɏI����Ă��Ȃ��\��������܂���" >> ${DIR_ERRLOG}/${ERROR_LOG}
			echo "�ߋ��P�T���ȓ��Ƀ��O���o�͂���Ă���̂�" >> ${DIR_ERRLOG}/${ERROR_LOG}
			echo "�����͐i�s���ł��B" >> ${DIR_ERRLOG}/${ERROR_LOG}
			tail -n 5 ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} >> ${DIR_ERRLOG}/${ERROR_LOG}
		fi
	else
		# �I�����b�Z�[�W�����݂���ꍇ�A�o�b�N�A�b�v�T�[�o�ɃR�s�[�ς݂��m�F
		for BKUP_DIR in `rsh ${BKUP_SERVER} ls ${BKUP_PATH}`; do
			if [ ${BKUP_DIR} = ${DAILY_DIR} ]; then
				FLG_COPY="0"
			fi
		done
		# �o�b�N�A�b�v�T�[�o�ɃR�s�[���Ă��Ȃ��ꍇ�A�R�s�[���s
		if [ ${FLG_COPY} = "1" ]; then
			rcp -pr "${DIR_OLDDAY}/${DAILY_DIR}" "${BKUP_SERVER}:${BKUP_PATH}"
			# �o�b�N�A�b�v���ǉ�
			cp -pr "${DIR_OLDDAY}/${DAILY_DIR}" "${BKUP_PATH2}"
		fi
		FLG_COPY="1"
	fi
done

rm ${DIR_ERRLOG}/tmp_DAILY_DIR.$$

exit 0
