#!/bin/bash -

#######################################################################
# 10�A���x���t�@�C���쐬�V�F���i���J�o���[�p�j
# $1 : �����J�n��
# $2 : �g���[�h�c
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

KNSKISYMD=$1
TRID=$2			# �g���[�h�c

# �o�n�s��� �t�@�C���̒�`

WSCODE=" "		# ���[�N�V�[�g�m�n�i�����O���[�v �R���j
BNCHUNO=" "		# ����No(�T���v�����O�r�d�p�Ɠ���)
SMPCD=" "		# �T���v�����O�R�[�h(�����O���[�v �S��)
SMPSEQ=" "		# �T���v�����O�r�d�p(����No�Ɠ���)
SRIYMD=" "		# ������
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

fnGetWsSeqKnri() {
    db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

    #   �Ώۃg���[�̌��̈ꗗ

	db2 "
	EXPORT to TMP_WSSEQKNRI.del of del messages TMP_WSSEQKNRI.msg \
	SELECT	KSKTKBN \
	FROM	WSSEQKNRI \
	WHERE	KNSKISYMD = '${KNSKISYMD}' \
	AND		WSSBT = '$1' \
	AND		WSNO = cast($2 as int) \
	"

	if [ $? -gt 0 ]; then
		db2 terminate
		return 1
	fi

	db2 terminate
	return 0
}

fnGetTrKntno() {
	db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

	#	�Ώۃg���[�̌��̈ꗗ

	db2 "
	EXPORT to TMP_KNTNO.del of del messages TMP_KNTNO.msg \
	SELECT	ODR.KNSGRP \
			, ODR.TRID \
			, ODR.TRPOS \
			, ODR.SMPCD \
			, ODR.SRIYMD \
			, ODR.KNTNO \
			, ODR.KNTKETFLG \
			, BUN.ID2 \
			, BUN.ID2POS \
			, BUN.CHKMJ \
			, LPAD( BCRTJ, 4, '0' ) \
			, NIN.FUKSUHN \
			, ODR.IRINO \
	FROM \
		(	SELECT	DISTINCT KNSGRP \
					, TRID \
					, TRPOS \
					, SMPCD \
					, SRIYMD \
					, KNTNO \
					, KNTKETFLG \
					, UTKYMD \
					, IRINO \
			FROM	KENORDER \
			WHERE	KNSKISYMD = '${KNSKISYMD}' \
			AND		TRID = '${TRID}' \
		) ODR \
		LEFT OUTER JOIN \
		(	SELECT  DISTINCT SRIYMD \
					, KNTNO \
					, SMPCD \
					, CHKMJ \
					, ID2 \
					, ID2POS \
			FROM	BUNCHU \
		) BUN \
		ON  ODR.SMPCD = BUN.SMPCD \
		AND ODR.KNTNO = BUN.KNTNO \
		AND ODR.SRIYMD = BUN.SRIYMD \
		LEFT OUTER JOIN \
		(   SELECT  DISTINCT UTKYMD \
					, IRINO \
					, SRIYMD \
					, KNTNO \
					, FUKSUHN \
			FROM	NINSIKI \
		) NIN \
		ON  ODR.IRINO = NIN.IRINO \
		AND ODR.UTKYMD = NIN.UTKYMD \
		AND ODR.KNTNO = NIN.KNTNO \
		AND ODR.SRIYMD = NIN.SRIYMD \
		LEFT OUTER JOIN \
		(   SELECT  UTKYMD \
					, IRINO \
					, KNSGRP \
					, INT( trunc( DECIMAL(BCRTJ) / 1000 + .09, 1) * 1000) BCRTJ \
			FROM    V_BUNCHURYO \
		) V_BCR \
		ON  ODR.IRINO = V_BCR.IRINO \
    	AND ODR.KNSGRP = V_BCR.KNSGRP \
		AND ODR.UTKYMD = V_BCR.UTKYMD \
	ORDER BY TRID,TRPOS \
	"
	if [ $? -gt 0 ]; then
	#	rm TMP_KNTNO.del
		db2 terminate
		return 1
	fi

	db2 terminate
	return 0
}

fnGetFukusu() {
    db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

    db2 "
	EXPORT to TMP_FUKUSU.del of del messages TMP_FUKUSU.msg \
	SELECT  DISTINCT ID2 \
			, ID2POS \
	FROM	BUNCHU \
	WHERE	SRIYMD = '$1' \
	AND		IRINO = '$2' \
	AND		KNTNO <> '$3' \
	AND		SMPCD = '$4' \
	AND		ID2 <> '' \
	ORDER BY ID2,ID2POS \
    "
	if [ $? -gt 0 ]; then
		db2 terminate
		return 1
	fi
	
	db2 terminate
	return 0
}

fnGetFileName() {
    db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

    #   �Ώۃg���[�̌��̈ꗗ

	db2 "
	EXPORT to TMP_KNSGMST.del of del messages TMP_KNSGMST.msg \
	SELECT	DISTINCT SPLBLID \
	FROM	KNSGMST \
	WHERE	KNSGRP = '$1' \
	AND		KAIYMD <= '${KNSKISYMD}' \
	AND		HAIYMD >= '${KNSKISYMD}' \
	"

	if [ $? -gt 0 ]; then
		db2 terminate
		return 1
	fi

	db2 terminate
	return 0
}

# �g���[�h�c�̃��b�N�h�c(2MLT,1SIN��)
TRID_PRE=`echo -e ${TRID} | cut -c1-4`
# �g���[�h�c�̉��S��
TRID_SEQ=`echo -e ${TRID} | cut -c5-8`

fnGetWsSeqKnri ${TRID_PRE} ${TRID_SEQ}
FILE_WSSEQKNRI=TMP_WSSEQKNRI.del
while read LINE_WSSEQKNRI
do
	# �o�͂��ꂽ�v�r�̋敪(�Č��v�r,�đ���v�r��)
	KSKTKBN=`echo -e ${LINE_WSSEQKNRI} | cut -d',' -f1-1 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
done  < ${FILE_WSSEQKNRI}

fnGetTrKntno
if [ $? -gt 0 ]; then
	echo "�f�[�^�̎擾�Ɏ��s���܂����B"
	exit 1
fi

# �w�肵���g���[�ɑ��݂��錟�̐������[�v
FILE_KNTNO=TMP_KNTNO.del
while read LINE_KNTNO
do
	# �����O���[�v(�R���ɕҏW����)
	KNSGRP=`echo -e ${LINE_KNTNO} | cut -d',' -f1-1 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${#KNSGRP} -ge 5 ]; then
		WSCODE="`echo -e ${KNSGRP} | cut -c3-5`"
	elif [ ${#KNSGRP} -ge 4 ]; then
		WSCODE="`echo -e ${KNSGRP}  | cut -c2-4`"
	fi
	# ����NO,�T���v�����OSEQ(�g���[ID�̉��S���A�g���[POS�A�����H���敪����Z�o�B�����l�ƂȂ�B)
	TRPOS=`echo -e ${LINE_KNTNO} | cut -d',' -f3-3 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${KSKTKBN} = "K" -o  ${KSKTKBN} = "T" -o ${KSKTKBN} = "R" -o ${KSKTKBN} = "S" ]; then
		SMPSEQ_TMP=`expr \( ${TRID_SEQ} - 1 \) \* 100 + ${TRPOS} + 80000`
	else
		SMPSEQ_TMP=`expr \( ${TRID_SEQ} - 1 \) \* 100 + ${TRPOS}`
	fi
	SMPSEQ_END=${#SMPSEQ_TMP}
	if [ ${SMPSEQ_END} -ge 6 ]; then
		SMPSEQ_START=`expr ${SMPCEQ_END} - 5`
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c${SMPCEQ_START}-${SMPCEQ_END}`
	else
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c1-${SMPCEQ_END}`
	fi
	BNCHUNO=${SMPSEQ}
	# �T���v�����O�R�[�h
	SMPCD=`echo -e ${LINE_KNTNO} | cut -d',' -f4-4 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# ������
	SRIYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f5-5 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# ����NO(����NO�����t���O����ҏW) 
	KNTNO_MOTO=`echo -e ${LINE_KNTNO} | cut -d',' -f6-6 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	KNTKETFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f7-7 | sed "s/\"//g" | sed "s/ //g"`
	if [ ${#KNTKETFLG} -eq 0 ]; then
		KNTNO=`echo -e "${KNTNO_MOTO}" | cut -c3-11`
		KNTNO=`printf "%s%s" "${KNTNO}" "00"`
	else
		KNTNO=${KNTNO_TMP}
	fi
	# �����̈ʒu���̎擾
	# �Q�h�c�̎��(SSSS,VVVV��)
	ID2_PRE=`echo -e ${LINE_KNTNO} | cut -d',' -f8-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	#�Q�h�c�̉��S��
	ID2_NO=`echo -e ${LINE_KNTNO} | cut -d',' -f8-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
	if [ ${#ID2_PRE} -eq 0 ]; then
		ID2="       "
	elif [ "${ID2_PRE}" = "X" ]; then
		ID2=" �� �� "
	elif [ "${ID2_PRE}" = "Y" ]; then
		ID2=" �� �O "
	elif [ "${ID2_PRE}" = "_" ]; then
		ID2="       "
	else
		ID2POS=`echo -e ${LINE_KNTNO} | cut -d',' -f9-9 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
		ID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
		ID2=`printf "%1s%06d" "${ID2_PRE}" "${ID2_TMP}"`
	fi
	# �`�F�b�N����
	CHKMJ=`echo -e ${LINE_KNTNO} | cut -d',' -f10-10 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �K�v������(���ڃ}�X�^�A�����ʃ}�X�^������Z�o)
	BCRTJ=`echo -e ${LINE_KNTNO} | cut -d',' -f11-11 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �����{�t���O
	FUKSUHN=`echo -e ${LINE_KNTNO} | cut -d',' -f12-12 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
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
	YEAR_TMP=`echo ${SRIYMD} | cut -c 1-4`
	MONTH_TMP=`echo ${SRIYMD} | cut -c 5-6`
	DAY_TMP=`echo ${SRIYMD} | cut -c 7-8`
	SRIYMD_TMP=`printf "%-4s%s%-2s%s%-2s" "${YEAR_TMP}" "-" "${MONTH_TMP}" "-" "${DAY_TMP}"`
	IRINO=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	fnGetFukusu "${SRIYMD_TMP}" "${IRINO}" "${KNTNO_MOTO}" "${SMPCD}"
	FILE_FUKUSU="TMP_FUKUSU.del"
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

	# label ���̏o��
	printf "%-3s%05d%-4s%05d%-8s%-11s%-7s%-2s%-1s%-4s%-1s%-2s%-1s%-6s%-4s%-70.70s\n" "${WSCODE}" "${BNCHUNO}" "${SMPCD}" "${SMPSEQ}" "${SRIYMD}" "${KNTNO}" "${ID2}" "${CHKMJ}" "${SECCD}" "${BCRTJ}" "${FUKSUHN}" "${YSNFLG}" "${TKTFLG}" "${KMKNM}" "${GRPNM}" "${FUKSUHNID2}" >> WORK
done < ${FILE_KNTNO}

# �w�肵���g���[�ɑ��݂��錟�̐������[�v
fnGetFileName "${KNSGRP}"
FILE_SPLBLID=TMP_KNSGMST.del
while read LINE_SPLBLID
do
	LBLFILENAME=`echo -e ${LINE_SPLBLID} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${#LBLFILENAME} -eq 0 ]; then
		exit 0
	else
		LBLFILENAME=${LBLFILENAME}.dat
	fi
	#�����M�t�@�C�����������ꍇ�͌���
	if [ -e ${OUTPUTDIR}${LBLFILENAME} ]; then
		mv ${OUTPUTDIR}${LBLFILENAME} ./WORK2
		cat ./WORK ./WORK2 > ./${LBLFILENAME}
		rm WORK WORK2
	else
		cat ./WORK > ./${LBLFILENAME}
		rm WORK
	fi
	#�t�@�C���𑗐M�f�B���N�g���Ɉړ�
	mv ${LBLFILENAME} ${OUTPUTDIR}${LBLFILENAME}
	break
done < ${FILE_SPLBLID}

exit 0
