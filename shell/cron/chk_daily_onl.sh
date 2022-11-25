#!/bin/bash
################################################################
#
# chk_daily_end.sh �����I�����C���\�Ď��V�F��
#
# 2021-03-09 H.Sekiya
#            �E�����ŗ����̋Ɩ��J�n�\�ȏ�ԂɂȂ������ǂ������m�F����B
#
################################################################

# �Ď��Ώۂ̐ݒ�
DIR_OLDDAY="/apdata/oldday"
# �Ď��Ώۂ̓������O�t�@�C����
DAILY_LOG="daily.log"
# �Ď��Ώۂ̃��[�h
DAILY_END_WORD1="�풓�v���Z�X�̋N�� --- �I��"
DAILY_END_WORD2="�������� --- �I��"
# �����J�n�̃��[�h
DAILY_START_WORD="�풓�v���Z�X�̒�~ --- �J�n"
# �G���[���̏o�̓��O��
DIR_ERRLOG="/apdata/aplog"
NAME_ERRLOG="FATAL_DAILY_ONL_"
EXTENSION_LOG=".log"

# oldday ���ɑ��݂�������o�b�N�A�b�v�f�B���N�g������������B
ls -F ${DIR_OLDDAY} | grep / > ${DIR_ERRLOG}/tmp_DAILY_ONL.$$

# �����o�b�N�A�b�v�f�B���N�g�������[�v
for DAILY_DIR  in `cat ${DIR_ERRLOG}/tmp_DAILY_ONL.$$ | sed -e "s/\///g"`
do
	# �������O�t�@�C���̒��ɊJ�n���b�Z�[�W�����݂��Ȃ��ꍇ�̓X�L�b�v�B
	grep "${DAILY_START_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -ne "0" ]; then
		continue
	fi

	# �������O�t�@�C���̒��ɏI�����b�Z�[�W�����݂���ꍇ�̓X�L�b�v�B
	grep "${DAILY_END_WORD2}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -eq "0" ]; then
		continue
	fi

	# �������O�t�@�C���̒��ɏ풓�N�����b�Z�[�W�����݂��邩�m�F�B
	grep "${DAILY_END_WORD1}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -ne "0" ]; then
		# �����J�n�����ƌ��ݎ������r���A�U�O���ȏ�o���Ă����ꍇ�A�G���[���[�����M
		START_TIME=`grep "${DAILY_START_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} | cut -b3-21`
		ELAPSE=`expr \( \`date +%s\` - \`date -d"${START_TIME}" +%s\` \) / 60`
		if [ ${ELAPSE} -ge 60 ]; then
			ERROR_LOG=${NAME_ERRLOG}${DAILY_DIR}${EXTENSION_LOG}
			echo "�������J�n���Ă���U�O���o�߂��Ă��܂����A�I�����Ă��܂���B" > ${DIR_ERRLOG}/${ERROR_LOG}
			echo "${DAILY_DIR} ���O���m�F���ĉ������B" >> ${DIR_ERRLOG}/${ERROR_LOG}
			tail -n 15 ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} >> ${DIR_ERRLOG}/${ERROR_LOG}
		fi
	fi
#	START_TIME=`grep "${DAILY_START_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} | cut -b3-21`
#	ELAPSE=`expr \( \`date +%s\` - \`date -d"${START_TIME}" +%s\` \) / 60`
done

rm ${DIR_ERRLOG}/tmp_DAILY_ONL.$$

exit 0
