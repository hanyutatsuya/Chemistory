#!/bin/bash -
###############################################################################
#
# �ݐύ폜�V�F��(100����)
# $1 : DB��
# $2 : DB���[�U
# $3 : DB�p�X���[�h
# 
# �X�V�� : 2008.10.01
#
###############################################################################

###############################################################################
# 0. �萔�錾
###############################################################################

## ��x�ɍ폜���錏�� (��)
DEL_CNT=10000

## �ۑ����� (100��)
SAVE_DAY100=100
TBL_100=(RUI_BUNCHU RUI_HKKKNRI RUI_KENORDER RUI_KENPOS RUI_OTHERKKA)
KEY_100=(SRIYMD HKKSJYMD KNSKISYMD KNSKISYMD UTKYMD)
## �e�e�[�u���̃L�[
## TABLE��       �� ���t�L�[   �� DELETE�L�[
## ��������������������������������������������������������������������������������������������
## RUI_BUNCHU    �� SRIYMD     �� SRIYMD, KNTNO, SMPCD, KMKCD
## RUI_HKKKNRI   �� HKKSJYMD   �� HKKSJYMD, HKKSJNO
## RUI_KENORDER  �� KNSKISYMD  �� KNSKISYMD, SRIYMD, KNTNO, KNSGRP, KMKCD, KNSSU, KNSSUEDA
## RUI_KENPOS    �� KNSKISYMD  �� KNSKISYMD, SRIYMD, KNTNO, KNNDH, ASYRCKID
## RUI_OTHERKKA  �� UTKYMD     �� UTKYMD, IRINO, KMKCD

## �X���[�v (�b)
SLEEP_CNT=1

## �G���[���O�̏o�͐�
LOG_DIR="/apdata/aplog"

## �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="WARNING_"

###############################################################################
# 1. DB2 CONNECT ����
###############################################################################
echo ""
echo "[`date`] DB2 CONNECT START ---------------------------------->"
db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"del_rui_100.log"
    exit 1
fi
echo "[`date`] DB2 CONNECT END ------------------------------------<"
echo ""
echo ""


###############################################################################
# 2. 100�����ۊǃe�[�u���̍폜����
###############################################################################

## �ۑ����ԁ{�P�̓���
DEL_DAYS=`expr $SAVE_DAY100 + 1`

echo "������ [`date`] 100���ۊǃe�[�u���폜���� START ������ ==========================>"
echo ""
echo ""
echo "[`date`] $DEL_DAYS���O�̓��t�擾 START -------------------------->"
echo ""
echo "    > SELECT (KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM SYSKNRMST"
db2 "SELECT (KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM SYSKNRMST" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > KJNYMD
echo ""

## �ۑ����ԁ{�P���ȑO�̓��t�擾(��������ꍇ������)
DEL_UTKYMD=\'`cat KJNYMD`\'
rm KJNYMD

echo "    �� $DEL_DAYS���O�̓��t = $DEL_UTKYMD"
echo ""
echo "[`date`] $DEL_DAYS���O�̓��t�擾 END ----------------------------<"
echo ""
echo ""

## �폜�Ώۂ̃e�[�u����
TBL_CNT=0

for RUI_TBL in ${TBL_100[@]}
do
    ## �Ώۃe�[�u���̓��t�L�[�ݒ�
	RUI_KEY=${KEY_100[$TBL_CNT]}
	
	echo "    ���������� [`date`] $RUI_TBL �̍폜���J�n ����������"
	echo ""
	echo "        > SELECT DISTINCT $RUI_KEY FROM $RUI_TBL WHERE $RUI_KEY <= $DEL_UTKYMD"
	db2 "SELECT DISTINCT $RUI_KEY FROM $RUI_TBL WHERE $RUI_KEY <= $DEL_UTKYMD" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > KJNYMD
	echo ""
	
	## SELECT �Ώی�����0���ǂ����H
	CNT_KJNYMD=`wc -l KJNYMD | sed 's/KJNYMD//g' | sed 's/ //g'`
	if [ $CNT_KJNYMD == 0 ]
	then
		echo "        $RUI_TBL �e�[�u���ɍ폜�Ώۂ̃f�[�^������܂���B"
	else
		echo "        �ȉ��̓��t�̃f�[�^�� $RUI_TBL �e�[�u������폜���܂��B"
		for DEL_YMD in `cat KJNYMD`
		do
		    ## �폜�Ώۂ̓��t��S�ďo��
			echo "          �E$DEL_YMD"
		done
	fi
	echo ""
	echo ""


	ERR_FLG=0

	for DEL_YMD in `cat KJNYMD`
	do
	    ## �Ώۓ��t�̍폜�O�̑S����
		B_CNT=0
		## �Ώۓ��t�̍폜��̑S����
		A_CNT=0
		## ���[�v��
		L_CNT=0

		DEL_DATE=\'$DEL_YMD\'

		echo "    [`date`] SELECT BEFORE START ---------------------------->"
		echo ""
		echo "        > SELECT COUNT($RUI_KEY) FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE"
		db2 "SELECT COUNT($RUI_KEY) as CNT FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > CNT
		echo ""
		
		## �Ώۓ��t�̍폜�O�̑S����
		B_CNT=`cat CNT`
		rm CNT
		
		echo "        [`date`] $RUI_TBL �폜�O" $B_CNT "�� �ł��B"
		
		## ���[�v��
		L_CNT=`expr $B_CNT / $DEL_CNT + 1`

		echo ""
		echo "    [`date`] SELECT BEFORE END ------------------------------<"
		echo ""
		echo ""

        ## RUI_KENPOS�̏ꍇ�̓��j�[�N�L�[�����Ȃ̂ŁADELETE�L�[���Œ�Őݒ�
		if [ $RUI_TBL == RUI_KENPOS ]
		then
			COLNAMES="KNSKISYMD, SRIYMD, KNTNO, KNNDH, ASYRCKID"
		else
			db2 "SELECT COLNAME FROM SYSCAT.COLUMNS WHERE TABNAME = '$RUI_TBL' AND KEYSEQ IS NOT NULL ORDER BY KEYSEQ" | sed 's/ //g' | grep ^[A-Z] | grep -v COLNAME | grep -v ���R�[�h > SEL_COL
			
			## DELETE�L�[�̃J������
			COL_CNT=0
			
			for colnm in `cat SEL_COL`
			do
				## COL_CNT��1�ȏ�̏ꍇ
				if [ $COL_CNT -ge 1 ]
				then
					COLNAMES="$COLNAMES, $colnm"
				else
				    ## 1�J�����ڂ̓J���}��t���Ȃ�
					COLNAMES="$colnm"
				fi
				COL_CNT=`expr $COL_CNT + 1`
			done
			rm SEL_COL
		fi

		echo "    [`date`] DELETE $RUI_TBL $RUI_KEY = $DEL_DATE START ------>"
		echo ""
		echo "        > DELETE FROM (SELECT $COLNAMES FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)"
		echo ""

		CNT_LOOP=1
		while [ $CNT_LOOP -le $L_CNT ];
		do
			## �ݐσe�[�u���폜����
			db2 "DELETE FROM (SELECT $COLNAMES FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)" > /dev/null
			db2 COMMIT > /dev/null

			if [ $L_CNT -eq $CNT_LOOP ];
			then
				echo "        [`date`] $B_CNT ���폜���܂����B"
			else
				CNT_ECHO=`expr $CNT_LOOP \* $DEL_CNT`
				echo "        [`date`] $CNT_ECHO / $B_CNT ���폜���܂����B"
			fi

            ## ���݂̃��[�v�����J�E���g�A�b�v
			CNT_LOOP=`expr $CNT_LOOP + 1`
			
			## �X���[�v����(�b���͂��̃V�F���̐擪�Ő錾)
			sleep $SLEEP_CNT
		done
		
		echo ""
		echo "    [`date`] DELETE $RUI_TBL $RUI_KEY = $DEL_DATE END --------<"

		echo ""
		echo ""
		echo "    [`date`] SELECT AFTER START --------------------------------->"
		echo ""
		echo "        > SELECT COUNT($RUI_KEY) FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE"
		db2 "SELECT COUNT($RUI_KEY) as CNT FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > CNT
		echo ""
		
		## �Ώۓ��t�̍폜��̑S����
		A_CNT=`cat CNT`
		rm CNT
		
		if [ $A_CNT -eq 0 ];
		then
			echo "        [`date`] $RUI_TBL �폜��" $A_CNT "�� �ł��B"
		else
			echo "        [`date`] �� ERROR : $RUI_TBL �폜��" $A_CNT "�� �ł��B"
			ERR_FLG=1
		fi
		echo ""
		echo "    [`date`] SELECT AFTER END -----------------------------------<"
		echo ""
		echo ""

	done

	rm KJNYMD

	if [ $ERR_FLG -eq 1 ];
	then
		echo "������ [`date`] $RUI_TBL �̍폜�ŃG���[���������܂����B ������"
		echo ""
		echo ""
		echo `date`" ERROR : $RUI_TBL �̍폜�ŃG���[���������܂����B" >> $LOG_DIR/$NAME_ERRLOG"del_rui_100.log"
	fi
	
	## �폜�Ώۂ̃e�[�u�����J�E���g�A�b�v
	TBL_CNT=`expr $TBL_CNT + 1`
done

echo "������ [`date`] 100���ۊǃe�[�u���폜���� END   ������ ==========================<"
echo ""
echo ""


###############################################################################
# 3. DB2 TERMINATE ����
###############################################################################
echo "[`date`] DB2 TERMINATE START -------------------------------->"
echo ""
db2 terminate;
echo ""
echo "[`date`] DB2 TERMINATE END ----------------------------------<"
echo ""


###############################################################################
# 4. �ݐύ폜�V�F���I��
###############################################################################
exit 0
