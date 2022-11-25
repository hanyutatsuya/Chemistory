#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

#######################################################################
# �u�������p 10�A���x���t�@�C���쐬�V�F��
# $1 : �����J�n��
# $2 : �T���v�����O�R�[�h
#######################################################################

# DB�ڑ����

DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"
#DBNAME="kea00db9"
#DBUSER="kea00dbt"
#DBPASS="kea00dbt"

# �o�͐���
OUTPUTDIR="/apdata/today/file/label/10label/"
LBLFILENAME="$3.dat"

# �ꎞ�t�@�C���ݒ�
FILE_FUKUSU="/tmp/TMP_FUKUSU.del"
FILE_KNTNO="/tmp/TMP_KNTNO.del"

SRIYMD_DB=$1	# ������(�c�a�`�� YYYY-MM-DD)

# ���x����� �t�@�C���̒�`
WSCODE=" "		# ���[�N�V�[�g�m�n�i�����O���[�v �R���j
BNCHUNO=0		# ����No(�T���v�����O�r�d�p�Ɠ���)
SMPCD=$2		# �T���v�����O�R�[�h(�����O���[�v �S��)
SMPSEQ=0		# �T���v�����O�r�d�p(����No�Ɠ���)
SRIYMD=" "		# ������(�t�@�C���`�� YYYYMMDD)
KNTNO=" "		# ���̂m�n
ID2=" "			# �����̃��b�N�h�c
CHKMJ=" "		# �`�F�b�N����
SECCD="A"		# �Z�N�V����
BCRTJ=" "		# �����K�v��
FUKSUHN=" "		# �����{���t���O
YSNFLG=" "		# �D��t���O
TKTFLG=" "		# �����t���O
KMKNM=" "		# ���ږ�
GRPNM=" "		# �O���[�v��
FUKSUHNID2=" " 	# �����̃��b�N�h�c�i�Q�{�ڈȍ~�j

fnGetSmpKntno() {
	#	�Ώۃg���[�̌��̈ꗗ

	db2 "
	EXPORT to ${FILE_KNTNO} of del \
	SELECT	BUN.SRIYMD \
			, BUN.KNTNO \
			, BUN.ID2 \
			, BUN.ID2POS \
			, BUN.CHKMJ \
			, SUBSTR(CHAR(DECIMAL( BCRTJ, 4, 0)), 1, 4) \
			, NIN.FUKSUHN \
			, BUN.UTKYMD \
			, BUN.IRINO \
			, BUN.SRTKEY \
	FROM \
		(	SELECT  DISTINCT UTKYMD \
					, IRINO \
					, SRIYMD \
					, KNTNO \
					, SMPCD \
					, CHKMJ \
					, ID2 \
					, ID2POS \
					, SRTKEY \
			FROM	BUNCHU \
			WHERE	SRIYMD = '$1' \
			AND		SMPCD = '$2' \
			AND		BNCKKA not in ('0','1') \
		) BUN \
		LEFT OUTER JOIN \
		(   SELECT  DISTINCT UTKYMD \
					, IRINO \
					, SRIYMD \
					, KNTNO \
					, FUKSUHN \
			FROM	NINSIKI \
		) NIN \
		ON  BUN.IRINO = NIN.IRINO \
		AND BUN.UTKYMD = NIN.UTKYMD \
		AND BUN.KNTNO = NIN.KNTNO \
		AND BUN.SRIYMD = NIN.SRIYMD \
		LEFT OUTER JOIN \
		(   SELECT  UTKYMD \
					, IRINO \
					, KNSGRP \
					, INT( trunc( DECIMAL(BCRTJ) / 1000 + .09, 1) * 1000) BCRTJ \
			FROM    V_BUNCHURYO \
		) V_BCR \
		ON  BUN.UTKYMD = V_BCR.UTKYMD \
		AND BUN.IRINO = V_BCR.IRINO \
    	AND BUN.SMPCD = V_BCR.KNSGRP \
	ORDER BY SRTKEY,ID2,ID2POS \
	" > /dev/null
	if [ $? -gt 0 ]; then
		echo "�f�[�^�̎擾�Ɏ��s���܂����B"
		rm ${FILE_KNTNO}
		return 1
	fi

	return 0
}

fnGetFukusu() {

    db2 "
	EXPORT to ${FILE_FUKUSU} of del \
	SELECT  DISTINCT ID2 \
			, ID2POS \
	FROM	BUNCHU \
	WHERE	UTKYMD = '$1' \
	AND		IRINO = '$2' \
	AND		SRIYMD = '$3' \
	AND		KNTNO <> '$4' \
	AND		SMPCD = '${SMPCD}' \
	AND		ID2 <> '' \
	ORDER BY ID2,ID2POS \
    " > /dev/null
	if [ $? -gt 0 ]; then
		return 1
	fi
	
	return 0
}

#######################################################################
# ���C���J�n
#######################################################################

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS} > /dev/null

# �����O���[�v(�R���ɕҏW����)
if [ ${#SMPCD} -ge 5 ]; then
	WSCODE="`echo -e ${SMPCD} | cut -c3-5`"
elif [ ${#SMPCD} -ge 4 ]; then
	WSCODE="`echo -e ${SMPCD}  | cut -c2-4`"
fi

# �Ώی��̎擾
fnGetSmpKntno ${SRIYMD_DB} ${SMPCD}
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# �t�@�C���T�C�Y�m�F
if [ -s ${FILE_KNTNO} ]; then
	:
else
	echo "�Ώۂ̌��̂����݂��܂���B"
	rm ${FILE_KNTNO}
	db2 terminate > /dev/null
	exit 0
fi

# �w�肵�������O���[�v�̌��̐������[�v
while read LINE_KNTNO
do
	# �[���r�d�p������U��B�i���x���o�̓V�X�e���̎d�l��A�r�d�p���K�v�Ȃ��߁j
	BNCHUNO=$(( BNCHUNO + 1 )) 
	SMPSEQ=${BNCHUNO}
	# ������
	SRIYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# ����NO(����NO�����t���O����ҏW) 
	KNTNO=`echo -e ${LINE_KNTNO} | cut -d',' -f2 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	EDIT_KNTNO=`echo -e ${KNTNO} | cut -c3-11`"00"
	# �����̈ʒu���̎擾
	# �Q�h�c�̎��(SSSS,VVVV��)
	ID2_PRE=`echo -e ${LINE_KNTNO} | cut -d',' -f3 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	#�Q�h�c�̉��S��
	ID2_NO=`echo -e ${LINE_KNTNO} | cut -d',' -f3 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
	if [ ${#ID2_PRE} -eq 0 ]; then
		ID2="       "
	elif [ "${ID2_PRE}" = "X" ]; then
		ID2=" �� �� "
	elif [ "${ID2_PRE}" = "Y" ]; then
		ID2=" �� �O "
	elif [ "${ID2_PRE}" = "_" ]; then
		ID2="       "
	else
		ID2POS=`echo -e ${LINE_KNTNO} | cut -d',' -f4 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
		ID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
		ID2=`printf "%1s%06d" "${ID2_PRE}" "${ID2_TMP}"`
	fi
	# �`�F�b�N����
	CHKMJ=`echo -e ${LINE_KNTNO} | cut -d',' -f5 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �K�v������(���ڃ}�X�^�A�����ʃ}�X�^������Z�o)
	BCRTJ=`echo -e ${LINE_KNTNO} | cut -d',' -f6 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �����{�t���O
	FUKSUHN=`echo -e ${LINE_KNTNO} | cut -d',' -f7 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �D��t���O(���g�p)
	YSNFLG="  "
	# �����t���O(���g�p)
	TKTFLG=" "
	# ���ږ�(���g�p)
	KMKNM="      "
	# ���ږ�(���g�p)
	GRPNM="    "
	# �����{��茟�̂̌����̈ʒu���̎擾
	FUKSUHNID2=""
	FUKSUHNID2_TMP=""
	UTKYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	YY=`echo ${UTKYMD} | cut -c1-4`
	MM=`echo ${UTKYMD} | cut -c5-6`
	DD=`echo ${UTKYMD} | cut -c7-8`
	UTKYMD_DB=${YY}-${MM}-${DD}
	IRINO=`echo -e ${LINE_KNTNO} | cut -d',' -f9 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	fnGetFukusu ${UTKYMD_DB} ${IRINO} ${SRIYMD_DB} ${KNTNO}
	if [ $? -gt 0 ]; then
		echo "�f�[�^�̎擾�Ɏ��s���܂����B"
		db2 terminate > /dev/null
		exit 1
	fi
	while read LINE_FUKUSU
	do
		FUKSUHNID2_PRE=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
		FUKSUHNID2_NO=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
		if [ ${#ID2_PRE} -eq 0 ]; then
			FUKSUHNID2_TMP="       "
		elif [ "${ID2_PRE}" = "X" ]; then
			FUKSUHNID2_TMP=" �� �� "
		elif [ "${ID2_PRE}" = "Y" ]; then
			FUKSUHNID2_TMP=" �� �O "
		elif [ "${ID2_PRE}" = "_" ]; then
			FUKSUHNID2_TMP="       "
		else
			FUKSUHNID2POS=`echo -e ${LINE_FUKUSU} | cut -d',' -f2-2 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
			FUKSUHNID2_TMP=`expr \( ${FUKSUHNID2_NO} - 1 \) \* 50 + ${FUKSUHNID2POS}`
			FUKSUHNID2_TMP=`printf "%1s%06d" "${FUKSUHNID2_PRE}" "${FUKSUHNID2_TMP}"`
		fi
		# �����{��茟�̂̌����̈ʒu
		FUKSUHNID2="${FUKSUHNID2}""${FUKSUHNID2_TMP}"
	done < ${FILE_FUKUSU}

	rm ${FILE_FUKUSU}

	# label ���̏o��
	printf "%-3s%05d%-4s%05d%-8s%-11s%-7s%-2s%-1s%-4s%-1s%-2s%-1s%-6s%-4s%-70.70s\n" "${WSCODE}" "${BNCHUNO}" "${SMPCD}" "${SMPSEQ}" "${SRIYMD}" "${EDIT_KNTNO}" "${ID2}" "${CHKMJ}" "${SECCD}" "${BCRTJ}" "${FUKSUHN}" "${YSNFLG}" "${TKTFLG}" "${KMKNM}" "${GRPNM}" "${FUKSUHNID2}" >> WORK
	if [ $? -gt 0 ]; then
		echo "�t�@�C���̏o�͂Ɏ��s���܂����B"
		db2 terminate > /dev/null
		exit 1
	fi
done < ${FILE_KNTNO}

rm ${FILE_KNTNO}

# �����M�t�@�C�����������ꍇ�͌���
if [ -e ${OUTPUTDIR}${LBLFILENAME} ]; then
	mv ${OUTPUTDIR}${LBLFILENAME} ./WORK2
	cat ./WORK ./WORK2 >> ./${LBLFILENAME}
	rm WORK WORK2
else
	cat ./WORK >> ./${LBLFILENAME}
	rm WORK
fi

# �t�@�C���𑗐M�f�B���N�g���Ɉړ�
mv ${LBLFILENAME} ${OUTPUTDIR}${LBLFILENAME}

db2 terminate > /dev/null

exit 0
