#!/bin/bash -

#######################################################################
# �o�n�s�t�@�C���쐬�V�F���i���J�o���[�p�j
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
OUTPUTDIR="/apdata/today/file/pot/"

# potinf.dat �t�@�C���̒�`

SYSDATE=" "		# �V�X�e�����ԁiyyMMddHHmmss�`���j
KNSKISYMD=$1	# �����J�n��
TRID=$2			# �g���[�h�c
WSNO1=" "		# ���[�N�V�[�g�m�n
POTFILENAME=" "	# �o�n�s�t�@�C����

# �o�n�s��� �t�@�C���̒�`

SECCD="A00"		# �T�e���C�g�h�c
SRIYMD=" "		# ������
KNSGRP_4=" "	# �����O���[�v(�S���ϊ��㥥�T���ȏ�̏ꍇ�A�Q���ڂ��폜����)
SMPSEQ=" "		# �T���v�����O�r�d�p
KNTNO=" "		# ���̂m�n
CHKMJ=" "		# �`�F�b�N����
ZRKGOU=" "		# �ޗ��L��
BCRTJ=" "		# �����K�v��
FKJBN="00"		# ���׏���
TKTFLG=" "		# �����t���O
TSKFLG=" "		# ���̓t���O
KENKANFLG=" "	# ���ǃt���O
SMPCD=" "		# �T���v�����O�R�[�h
WSNO2=" "		# ���[�N�V�[�g�m�n�ipotinf.dat�t�@�C�����̂��̂Ƃ͎኱�������Ⴄ�j
FUKSUHNNO=" "	# �����{���̂̐� (�����̂������{��)
FUKSUHNID2=" "	# �����{���̂̌����̈ʒu

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
	SELECT	ODR.SRIYMD \
			, ODR.KNSGRP \
			, ODR.TRID \
			, ODR.TRPOS \
			, ODR.KNTNO \
			, ODR.KNTKETFLG \
			, BUN.CHKMJ \
			, ODR.ZRCD \
			, DECIMAL( trunc( DECIMAL(V_BCR.BCRTJ) / 1000 + .09, 1), 3, 1) \
			, ODR.TKTFLG \
			, ODR.TSKFLG \
			, ODR.SMPCD \
			, BUN.ID2 \
			, BUN.ID2POS \
			, ODR.IRINO \
	FROM \
		(	SELECT	DISTINCT SRIYMD \
					, KNSGRP \
					, TRID \
					, TRPOS \
					, KNTNO \
					, KNTKETFLG \
					, TKTFLG \
					, TSKFLG \
					, ZRCD \
					, SMPCD \
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
		(   SELECT  UTKYMD \
					, IRINO \
					, KNSGRP \
					, BCRTJ \
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
	AND		ID2 <> ''
	ORDER BY ID2,ID2POS \
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

PRE_SMPSEQ="0" # ���̏d���`�F�b�N�p���(�O��T���v�����OSEQ)
# �w�肵���g���[�ɑ��݂��錟�̐������[�v
FILE_KNTNO=TMP_KNTNO.del
while read LINE_KNTNO
do
	# ������
	SRIYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �����O���[�v(�S���ɕҏW����)
	KNSGRP=`echo -e ${LINE_KNTNO} | cut -d',' -f2-2 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${#KNSGRP} -ge 5 ]; then
		KNSGRP_4="`echo -e ${KNSGRP} | cut -c1-1``echo -e ${KNSGRP} | cut -c3-5`"
	else
		KNSGRP_4="${KNSGRP}"
	fi
	# �T���v�����OSEQ(�g���[ID�̉��S���A�g���[POS�A�����H���敪����Z�o)
	TRPOS=`echo -e ${LINE_KNTNO} | cut -d',' -f4-4 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${KSKTKBN} = "K" -o  ${KSKTKBN} = "T" -o ${KSKTKBN} = "R" -o ${KSKTKBN} = "S" ]; then
		SMPSEQ_TMP=`expr \( ${TRID_SEQ} - 1 \) \* 100 + ${TRPOS} + 80000`
	else
		SMPSEQ_TMP=`expr \( $TRID_SEQ - 1 \) \* 100 + ${TRPOS}`
	fi
	SMPSEQ_END=${#SMPSEQ_TMP}
	if [ ${SMPSEQ_END} -ge 6 ]; then
		SMPSEQ_START=`expr ${SMPCEQ_END} - 5`
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c${SMPCEQ_START}-${SMPCEQ_END}`
	else
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c1-${SMPCEQ_END}`
	fi
	# ���̏d���`�F�b�N(����ƑO��̃T���v�����OSEQ�̔�r) 
	if [ ${SMPSEQ} -eq ${PRE_SMPSEQ} ]; then
		continue
	else
		PRE_SMPSEQ=${SMPSEQ}
	fi
	# ����NO(����NO�����t���O����ҏW) 
	KNTNO_MOTO=`echo -e ${LINE_KNTNO} | cut -d',' -f5-5 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	KNTKETFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f6-6 | sed "s/\"//g" | sed "s/ //g"`
	if [ ${#NTKETFLG} -eq 0 ]; then
		KNTNO=`echo -e "${KNTNO_MOTO}" | cut -c3-11`
		KNTNO=`printf "%s%s" "${KNTNO}" "00"`
	else
		KNTNO=${KNTNO_TMP}
	fi
	# �`�F�b�N����
	CHKMJ=`echo -e ${LINE_KNTNO} | cut -d',' -f7-7 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	#�ޗ��L��(�ޗ��R�[�h����ݒ�)
	ZRCD=`echo -e ${LINE_KNTNO} | cut -d',' -f8-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ "${ZRCD}" = "021" -o "${ZRCD}" = "022" -o "${ZRCD}" = "023" -o "${ZRCD}" = "024" ]; then
		ZRKGOU="S  "
	else
		ZRKGOU="E  "
	fi
	# �K�v������(���ڃ}�X�^�A�����ʃ}�X�^������Z�o)
	BCRTJ_TMP=`echo -e ${LINE_KNTNO} | cut -d',' -f9-9 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	BCRTJ_TMP=`echo -e ${BCRTJ_TMP} | cut -c3-5`
	BCRTJ=`printf " %s " "${BCRTJ_TMP}"`
	# �����t���O
	TKTFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f10-10 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	# ���̓t���O
	TSKFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f11-11 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# ���ǃt���O(�V�t���ɂȂ��āA���ǈ������Ȃ��Ȃ����̂ŁA�X�y�[�X�Œ�)
	KENKANFLG_TMP=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-2`
	# ���t�����e�B�A�d�l�ł��邪�A�ꉞ�c���Ă���(�V�t�����e�B�A�ɂ�X�Ŏn�܂�ID2�͑��݂��Ȃ�)
	if [ "${KENKANFLG_TMP}" = "XX" ]; then
		KENKANFLG="�"
	else
		KENKANFLG=" "
	fi
	# �T���v�����O�R�[�h
	SMPCD=`echo -e ${LINE_KNTNO} | cut -d',' -f12-12 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# WSNO(�����O���[�v�����ɕҏW)
	WSNO2=`printf "%s%s" "WS:" "${KNSGRP}"`
	# �˗���NO
	IRINO=`echo -e ${LINE_KNTNO} | cut -d',' -f15-15 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# �����̂̌����̈ʒu���̎擾
	# �Q�h�c�̎��(SSSS,VVVV��)
	ID2_PRE=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	#�Q�h�c�̉��S��
	ID2_NO=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
	if [ ${#ID2_PRE} -eq 0 ]; then
		FUKSUHNID2="�Ҳ       "
	elif [ "${ID2_PRE}" = "X" ]; then
		FUKSUHNID2="�ݶ�      "
	elif [ "${ID2_PRE}" = "Y" ]; then
		FUKSUHNID2="�޾��     "
	elif [ "${ID2_PRE}" = "_" ]; then
		FUKSUHNID2="          "
	else
		ID2POS=`echo -e ${LINE_KNTNO} | cut -d',' -f14-14 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
		FUKSUHNID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
		FUKSUHNID2=`printf "%1s%06d%-3s" "${ID2_PRE}" "${FUKSUHNID2_TMP}" " "`
	fi
	# �����{��茟�̂̌����̈ʒu���̎擾
	YEAR_TMP=`echo ${SRIYMD} | cut -c 1-4`
	MONTH_TMP=`echo ${SRIYMD} | cut -c 5-6`
	DAY_TMP=`echo ${SRIYMD} | cut -c 7-8`
	SRIYMD_TMP=`printf "%-4s%s%-2s%s%-2s" "${YEAR_TMP}" "-" "${MONTH_TMP}" "-" "${DAY_TMP}"`
	fnGetFukusu "${SRIYMD_TMP}" "${IRINO}" "${KNTNO_MOTO}" "${SMPCD}"
	FILE_FUKUSU="TMP_FUKUSU.del"
	FUKSUHNNO=0
	while read LINE_FUKUSU
	do
		ID2_PRE=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
		ID2_NO=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
		if [ ${#ID2_PRE} -eq 0 ]; then
			FUKSUHNID2_TMP="�Ҳ       "
		elif [ "${ID2_PRE}" = "X" ]; then
			FUKSUHNID2_TMP="�ݶ�      "
		elif [ "${ID2_PRE}" = "Y" ]; then
			FUKSUHNID2_TMP="�޾��     "
		elif [ "${ID2_PRE}" = "_" ]; then
			FUKSUHNID2_TMP="          "
		else
			ID2POS=`echo -e ${LINE_FUKUSU} | cut -d',' -f2-2 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
			FUKSUHNID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
			FUKSUHNID2_TMP=`printf "%1s%06d%-3s" "${ID2_PRE}" "${FUKSUHNID2_TMP}" " "`
		fi
		# �����{��茟�̂̐����J�E���g����
		FUKSUHNNO=`expr ${FUKSUHNNO} + 1`
		# �����{��茟�̂̌����̈ʒu
		FUKSUHNID2="${FUKSUHNID2}""${FUKSUHNID2_TMP}"
	done < ${FILE_FUKUSU}

	# pot ���̏o��
	printf "%-3s%-8s%-4s%05d%-11s%-2s%-3s%-5s%-2s%-1s%-1s%-1s%-4s%-10s%-1s%-100s\r\n" "${SECCD}" "${SRIYMD}" "${KNSGRP_4}" "${SMPSEQ}" "${KNTNO}" "${CHKMJ}" "${ZRKGOU}" "${BCRTJ}" "${FKJBN}" "${TKTFLG}" "${TSKFLG}" "${KENKANFLG}" "${SMPCD}" "${WSNO2}" "${FUKSUHNNO}" "${FUKSUHNID2}" >> WORK
done < ${FILE_KNTNO}

# potinf.dat ���̏o��
SYSDATE=`date '+%y%m%d%H%M%S'`
WSNO1=`printf "(WS:%s)" "${KNSGRP_4}"`
# �����H���敪�ɂ���āA�t�@�C�����Ɏg�p����t���O������
if  [ ${KSKTKBN} = "N" ]; then
	MODEFLG="1"
elif [ ${KSKTKBN} = "K" -o  ${KSKTKBN} = "T" -o ${KSKTKBN} = "R" ]; then
	MODEFLG="2"
elif [ ${KSKTKBN} = "S" ]; then
	MODEFLG="3"
elif [ ${KSKTKBN} = "M" ]; then
	MODEFLG="4"
fi
POTFILENAME=`printf "%s.%s00" "${TRID}" "${MODEFLG}"`

# potinf.dat �̃o�b�N�A�b�v���������ɁA�V��������ǋL����B
cp -p ${OUTPUTDIR}potinf.dat ${OUTPUTDIR}${SYSDATE}potinf.dat
printf "%-12s%-8s%-42s%-24s\r\n" "${SYSDATE}" "${TRID}" "${WSNO1}" "${POTFILENAME}" >> ${OUTPUTDIR}potinf.dat

mv WORK ${OUTPUTDIR}${POTFILENAME}

exit 0
