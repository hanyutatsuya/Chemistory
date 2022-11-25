#!/bin/sh

#------------------------------------------------
# ACE �R���g���[���v�Z���� �쐬�A�o�^
# -----------------------------------------------
# v1.0		2020.10.08	Sekiya
#------------------------------------------------

# �������̃R���g���[�����ʂ��폜�����O�Ɏ��s���邱�ƁB
fnExport() {
	db2 connect to $1 user $2 using $3
	ret=$?

	if [ $ret -ne 0 ]
	then
        echo `date`" ERROR : DB�ڑ����s($1,$2,$3,$ret)" >> $LOG_DIR/$NAME_ERRLOG$ME.log
		return $ret
	fi

	db2 "export to $WORK_DIR/CTRLKKA_074.ixf of ixf messages $ME.export.msg \
		SELECT \
			CTRL_B.KNSKISYMD, \
			CTRL_B.BSKKBN, \
			CTRL_B.BSKLNE, \
			CTRL_B.BSKGOK, \
			CTRL_B.KNSGRP, \
			'0900006', \
			'074', \
			CTRL_B.CTRLNO, \
			CTRL_B.CTRLSBT, \
			CTRL_B.CTRLSBTEDA, \
			CTRL_B.CTRLLBL, \
			CTRL_B.TSTRFLG, \
			CTRL_B.ASYRCKID, \
			CTRL_B.ASYRCKPOS, \
			CTRL_B.KNSSEQ, \
			CTRL_B.BSKSEQ, \
			CTRL_B.BTHNO, \
			CTRL_B.BTHRCKJBN, \
			CTRL_B.SYKLOTNO, \
			RPAD(LPAD(TO_CHAR(DECFLOAT(CTRL_B.SKTTI) - DECFLOAT(CTRL_S.SKTTI)),8,' '),24,' ') AS SKTTI, \
			RPAD(TO_CHAR(DECFLOAT(CTRL_B.SKTTI) - DECFLOAT(CTRL_S.SKTTI)),24,' ') AS KNZTI, \
			CTRL_B.KNZTISTFLG, \
			CTRL_B.SKTDH, \
			0, \
			'1', \
			CTRL_B.FACTER, \
			CTRL_B.BASE, \
			CTRL_B.KOSIJT, \
			CTRL_B.KOSITTS, \
			CTRL_B.KOSIDH, \
			CTRL_B.KSNDH \
		FROM \
			CTRLKKA CTRL_B \
			INNER JOIN CTRLKKA CTRL_S \
				ON  CTRL_B.KNSKISYMD = CTRL_S.KNSKISYMD \
				AND CTRL_B.CTRLSBT = CTRL_S.CTRLSBT \
				AND CTRL_B.SKTDH = CTRL_S.SKTDH \
				AND CTRL_B.KMKCD = '0900004' \
				AND CTRL_S.KMKCD = '0900005' \
				AND CTRL_B.SKTTI <> ''\
				AND CTRL_S.SKTTI <> '' \
		WHERE \
			CTRL_B.CTRLSBT IN ('002','042') \
		ORDER BY \
			CTRL_B.CTRLSBT, \
			CTRL_B.KNSKISYMD, \
			CTRL_B.CTRLNO"
	ret=$?

	if [ $ret -ne 0 ]
	then
		db2 terminate
		return $ret
	fi

	db2 terminate

	return 0
}

fnImport() {
	db2 connect to $1 user $2 using $3
	ret=$?

	if [ $ret -ne 0 ]
	then
		return $ret
	fi

	db2 "import from $WORK_DIR/CTRLKKA_074.ixf of ixf commitcount 10000 messages $ME.import.msg insert_update into RUI_CTRLKKA"
	ret=$?

	if [ $ret -ne 0 ]
	then
		db2 terminate
		return $ret
	fi

	db2 terminate

	return 0
}

#------------------------------------------------
# main()
#   input : DBNAME
#           id(DB)
#           password(DB)
#------------------------------------------------

ME=`basename $0`
WORK_DIR=`pwd`
LOG_DIR="/apdata/aplog"
# �ォ�烊�J�o���[�o���鏈���Ȃ̂ŁA���[�j���O���x���ōς܂��B(�G���[���[���͑��M���邪�A�����͒��f���Ȃ��B)
NAME_ERRLOG="WARNING_"

USE_DB=""
USE_ID=""
USE_PW=""
sem=""


# �r������
sem="/tmp/`basename $0`"
ln -s /$sem.lock $sem || exit
trap "rm $sem; db2 terminate; exit 0" 2 3 15

echo "$ME : �N��"`date`

# ---------------------------------
# �I�v�V�������`�F�b�N
# ---------------------------------
if [ $# -lt 3 ]
then
	echo "$ME : �������w�肵�ĉ�����"
	echo "sh $ME DB�ڑ���   ���[�UID(DB2)   �p�X���[�h(DB2)"
	rm $sem
	exit 0
else
	USE_DB=$1
	USE_ID=$2
	USE_PW=$3
fi

# ---------------------------------
# ���DIR�`�F�b�N
# ---------------------------------
if [ -d $WORK_DIR ]
then
	if [ -w $WORK_DIR ]
	then
		# EXPORT���s
		fnExport $USE_DB $USE_ID $USE_PW
		if [ $? -ne 0 ]
		then
       		echo `date`" ERROR : EXPORT�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG$ME.log
			rm "$sem"
			exit 1
		else
			# IMPORT���s
			fnImport $USE_DB $USE_ID $USE_PW
			if [ $? -ne 0 ]
			then
       			echo `date`" ERROR : IMPORT�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG$ME.log
				rm "$sem"
				exit 1
			fi
		fi
	else
       	echo `date`" ERROR : �ݒ肳��Ă����Ɨ̈悪�����ݕs�ł�" >> $LOG_DIR/$NAME_ERRLOG$ME.log
		rm "$sem"
		exit 1
	fi
else
    echo `date`" ERROR : �ݒ肳��Ă����Ɨ̈悪�s���ł�" >> $LOG_DIR/$NAME_ERRLOG$ME.log
	rm "$sem"	
	exit 1
fi

# �r������(��n��)
rm "$sem"

## daily.log �ɕ\�����邽�߁A���_�C���N�V�������O��
echo "$ME : �I�� "`date`

exit 0
