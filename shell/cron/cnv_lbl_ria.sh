#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#######################################################################
# �V�P�O�A���x���V�X�e���p�t�@�C���ϊ��V�F��
# $1 : �ϊ����t�@�C����(�t���p�X)
# $2 : �ϊ���t�@�C����(�t���p�X)
#######################################################################

# �V10�A���x����� �t�@�C���̒�`
SATE=""			# �T�e���C�g�h�c
SMPWS=""		# �T���v�����O�v�r��(�V�X�e�������Œ�`)
SMPSEQ=""		# �T���v�����O�r�d�p
WSTCDE=""		# �����O���[�v(�S���ϊ��㥥�T���ȏ�̏ꍇ�A�Q���ڂ��폜����)
KMKNME=""		# ���ږ� ���g�p
UKEYMD=""		# ��t�� YYYYMMDD
KNTNO=""		# ���̂m�n�V���{�}�ԂQ��
CHKMOJI=""		# �`�F�b�N����
ZAIRYO=""		# �ޗ��R�[�h �A�X�^���X�N�Œ�
BUNRYO=""		# ������(�P�}�C�N���P��)
ASIRYO=""		# �K�v�� �����ʂƓ������̂�����
FUKA=""			# ���׏��� ���g�p
TOKETU=""		# �����t���O ���g�p
TOSEKI=""		# ���̓t���O ���g�p
ATUKAI=""		# �����t���O ���g�p
FUKUSU=""		# �����{���t���O
SECID=""		# �Q�m�c�|�h�c
COUNT_KMKCD=""	# ���ڐ�
SECID2=""		# �Q�m�c�|�h�c(�����{���)
JIKAN=""		# �T���v�����O����(�T���v�����O�D��) ���g�p
ORDER=""		# �������t���O ���g�p
YSN_FLG=""		# �D��t���O ���g�p
YOBI=""			# �\�� ���g�p

# �N��������
MOTO_FILE=$1	# �ϊ��O�̃t�@�C����(�t���p�X)
SEND_FILE=$2	# �ϊ���̃t�@�C����(�t���p�X)
SMPWS_CODE=$3	# �����ΏۃT���v�����O�R�[�h(�T���R�[�h�͎w��s��)
SMPWS_NAME=$4	# �\���p�T���v�����O�R�[�h

# �c�a�ڑ���ݒ�
DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"

TMP_COUNT_KMKCD="TMP_COUNT_KMKCD.del"

# �˗����ڐ��擾�֐�
fnCountKmkcd()
{

	YEAR_TMP=`echo $1 | cut -c 1-4`
	MONTH_TMP=`echo $1 | cut -c 5-6`
	DAY_TMP=`echo $1 | cut -c 7-8`
	SRIYMD=`printf "%-4s%s%-2s%s%-2s" "${YEAR_TMP}" "-" "${MONTH_TMP}" "-" "${DAY_TMP}"`

	db2 "
    EXPORT to ${TMP_COUNT_KMKCD} of del \
	SELECT COUNT(kmkcd) \
	FROM BUNCHU \
	WHERE SRIYMD = '${SRIYMD}' \
	AND KNTNO = '00$2' \
	AND SMPCD = '$3' \
	"

	if [ $? -gt 0 ]; then
		return 1
    fi

	return 0
}

if [ ! -e $1 ]; then
    echo "$1 NOT found."
	exit 1
fi

# DB�ڑ�
db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

while read MOTO_RECORD
do
	SATE="A00"
	SMPWS="${SMPWS_NAME}"
	SMPSEQ=`echo -e "${MOTO_RECORD}" | cut -c4-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# SEQ 80000 �ȏ�͍Č����Ȃ̂ŁA�ǂݔ�΂��B�O�O������̂ŁA��x�Aexpr �Ōv�Z����B
	TMP_CALC=`expr ${SMPSEQ} - 80000`
	if [ ${TMP_CALC} -ge 0 ]; then
		continue
	fi
	WSTCDE=`echo -e "${MOTO_RECORD}" | cut -c9-12 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �w�肳�ꂽ�����O���[�v�ȊO�͓ǂݔ�΂�
	if [ "${WSTCDE}" != "${SMPWS_CODE}" ]; then
		continue
	fi
	WSTCDE="${SMPWS_NAME}"
	KMKNME="                                                                                                    "
	# ������
	UKEYMD=`echo -e "${MOTO_RECORD}" | cut -c18-25 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	KNTNO=`echo -e "${MOTO_RECORD}" | cut -c26-34 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	CHKMOJI=`echo -e "${MOTO_RECORD}" | cut -c44-45 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	ZAIRYO="*  "
	BUNRYO=`echo -e "${MOTO_RECORD}" | cut -c47-50 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	ASIRYO=$BUNRYO
	FUKA="  "
	TOKETU=" "
	TOSEKI=" "
	ATUKAI=" "
	FUKUSU=`echo -e "${MOTO_RECORD}" | cut -c51 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	SECID=`echo -e "${MOTO_RECORD}" | cut -c37-43 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �˗����ڐ���ǉ�
	fnCountKmkcd ${UKEYMD} ${KNTNO} ${SMPWS_CODE}
	if [ $? -gt 0 ]; then
		db2 terminate
		exit 1
	fi
	while read LINE_COUNT_KMKCD
	do
		COUNT_KMKCD=`echo -e ${LINE_COUNT_KMKCD} | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	done < ${TMP_COUNT_KMKCD}
	SECID2=`echo -e "${MOTO_RECORD}" | cut -c65-127 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	JIKAN="     "
	ORDER=" "
	YSN_FLG=" " 
	YOBI="               "

	# �V10�A���x���V�X�e���p�t�@�C�� ���̏o��
	printf "%-3s%-4s%-5s%-4s%-100s%-8s%-9s%-2s%-3s%-5s%-5s%-2s%-1s%-1s%-1s%-1s%-7s%-7s%-63s%-5s%-1s%-1s%-15s\r\n" "${SATE}" "${SMPWS}" "${SMPSEQ}" "${WSTCDE}" "${KMKNME}" "${UKEYMD}" "${KNTNO}" "${CHKMOJI}" "${ZAIRYO}" "0${BUNRYO}" "0${ASIRYO}" "${FUKA}" "${TOKETU}" "${TOSEKI}" "${ATUKAI}" "${FUKUSU}" "${SECID}" "${COUNT_KMKCD}" "${SECID2}" "${JIKAN}" "${ORDER}" "${YSN_FLG}" "${YOBI}" >> WORK
done < ${MOTO_FILE}

if [ ! -e WORK ]; then
	dateStr=`date +%F_%T%t`
	echo "${dateStr} : �Y�����R�[�h�Ȃ�"
	db2 terminate
	exit 9
fi

mv WORK ${SEND_FILE}

if [ -e ${TMP_COUNT_KMKCD} ]; then
	rm ${TMP_COUNT_KMKCD}
fi

db2 terminate
exit 0
