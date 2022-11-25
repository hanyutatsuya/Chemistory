#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#######################################################################
#
# chk_HKHRIRAI.sh �񍐕ۗ��e�[�u�� �����O���[�v�X�V�V�F��
#
# 2020-09-10 Create H.Sekiya
#
# �˗�END ��M���ɑ����`�F�b�N���s�� HKHRIRAI �� INSERT ���Ă��邪�A
# ���̌�ɁA�����{���̕ʂ̕�����񂪂��āAIRAI �� KNSGRP ���X�V����A 
# IRAI �� HKHRIRAI �� KNSGRP �ɐH���Ⴂ����������ꍇ������B
# �{���Ȃ番���W�J���� IRAI �Ɠ����� HKHRIRAI ���X�V����悤�ɂ��ׂ������A
# �����W�J�̕ύX�͎��Ԃ������邽�߁A���̃V�F���� HKHRIRAI �� KNSGRP ���X�V����B
# ���̃V�F���̎��s�^�C�~���O�͕���END ��M��Ɉ��N������΂悢�B
#
#######################################################################
# ���s���O�t�@�C��
TMP_FILE="/tmp/chk_HKHRIRAI"
LOCK_FILE="/apdata/aplog/chk_HKHRIRAI.lock"

# DB�ڑ����
DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"

# �t���O
FLG="10"      # �V�X�e���Ǘ��}�X�^�̃t���O�󋵁B�^�p�t���O(�P����)+����END�t���O(�Q����)

# �����ς݃t�@�C���̑��݊m�F�B(�t�@�C�������݂���ꍇ�A�`�F�b�N�����Ȃ��B)
if [ -e ${LOCK_FILE} ]; then
	exit 0
fi

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS} > /dev/null

# �������������́A�����d�m�c�����Ă��Ȃ����͏��������Ȃ��B
db2 -x "SELECT UNYFLG,BCHENDFLG FROM SYSKNRMST FOR READ ONLY" | grep ^[0-9] | sed 's/ //g' > ${TMP_FILE}
FLG=`cat ${TMP_FILE}`
rm ${TMP_FILE}
if [ ${FLG} != "01" ]; then
	db2 terminate > /dev/null
	exit 0
fi

dateStr=`date '+%F %T%t'`
echo "$dateStr : �������J�n���܂����B"

db2 "
SELECT
	HKHRIRAI.UTKYMD,
	HKHRIRAI.IRINO ,
	HKHRIRAI.KMKCD ,
	HKHRIRAI.KNSGRP HKHR_KNSGRP,
	IRAI.KNSGRP IRI_KNSGRP
FROM
	HKHRIRAI,
	IRAI
WHERE
	HKHRIRAI.UTKYMD = IRAI.UTKYMD AND
	HKHRIRAI.IRINO = IRAI.IRINO AND
	HKHRIRAI.KMKCD = IRAI.KMKCD AND
	HKHRIRAI.KNSGRP <> IRAI.KNSGRP
"

db2 "
UPDATE
	HKHRIRAI
SET
	HKHRIRAI.KNSGRP = IRAI.KNSGRP
FROM
	IRAI
WHERE
	HKHRIRAI.UTKYMD = IRAI.UTKYMD AND
	HKHRIRAI.IRINO = IRAI.IRINO AND
	HKHRIRAI.KMKCD = IRAI.KMKCD AND
	HKHRIRAI.KNSGRP <> IRAI.KNSGRP
"
# �߂�l���A����I�� 0 �A�ΏۂȂ� 1 �ȊO�̏ꍇ�A�G���[�Ƃ���B
if [ $? -gt 1 ]; then
	db2 terminate > /dev/null
	exit 1
fi

touch ${LOCK_FILE}
	
db2 terminate > /dev/null

dateStr=`date '+%F %T%t'`
echo "$dateStr : �������I�����܂����B"
echo ""

exit 0
