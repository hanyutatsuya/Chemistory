#!/bin/bash
############################################################
#
# �v���Z�X�Ď���~
#
# 2016-04-07 Create H.Sekiya
#
# ��Ɠ��Ńv���Z�X�Ď����ꎞ�I�ɒ�~����ꍇ�Ɏg�p�B
# �Ď���~�t�@�C�����쐬����B
# �Ď����ĊJ����ɂ́A�R���ō쐬�����t�@�C�����폜����΂悢�B
# �����ԊĎ����~���Ă���ƁA�x�����[��������̂Œ��ӁB
############################################################

# �Ď��Ώۂ̐ݒ�
CHK_DIR_Z="/home/kea00sys/shell/cron"

IA_CNT="4"
CHK_IA=(KEA00IAW21.bml.co.jp KEA00IAW22.bml.co.jp KEA00IAW23.bml.co.jp KEA00IAW24.bml.co.jp)
CHK_DIR_IA="/home/kea00sys/shell"

STOP_FILE_NAME="STOP"

touch ${CHK_DIR_Z}/${STOP_FILE_NAME}

for i in `seq 0 $((${IA_CNT} - 1))`;
do
	rsh ${CHK_IA[$i]} touch ${CHK_DIR_IA}/${STOP_FILE_NAME}
done

exit 0
