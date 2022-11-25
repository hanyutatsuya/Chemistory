#!/bin/bash -
###############################################################################
#
# �����폜�V�F��
# $1 : DB��
# $2 : DB���[�U
# $3 : DB�p�X���[�h
# 
# �X�V�� : 2008.08.06
#
###############################################################################

## ��x�ɍ폜���錏�� (��)
DEL_CNT=10000

## ����ۑ����� (��)
SAVE_DAYS=400

## �X���[�v (�b)
SLEEP_CNT=1

## �G���[���O�̏o�͐�
LOG_DIR="/apdata/aplog"

## �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="WARNING_"

echo ""
echo "[`date`] db2 connect start ---------------------------------->"
db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"del_rireki.log"
    exit 1
fi
echo "[`date`] db2 connect end ------------------------------------<"
echo ""
echo ""

## �ۑ����ԁ{�P�̓���
DEL_DAYS=`expr $SAVE_DAYS + 1`

echo "[`date`] $DEL_DAYS���O�̎�t���擾 start -------------------------->"
echo ""
echo "    > SELECT (KNR.KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM (SELECT KJNSRIYMD FROM SYSKNRMST) AS KNR"
db2 "SELECT (KNR.KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM (SELECT KJNSRIYMD FROM SYSKNRMST) AS KNR" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > KJNYMD
echo ""

## �ۑ����ԁ{�P���ȑO�̎�t��(��������ꍇ������)
DEL_UTKYMD=\'`cat KJNYMD`\'
rm KJNYMD
echo "    $DEL_DAYS���O�̎�t�� = $DEL_UTKYMD"
echo ""

echo "    > SELECT DISTINCT UTKYMD FROM RIREKI WHERE UTKYMD <= $DEL_UTKYMD"
db2 "SELECT DISTINCT UTKYMD FROM RIREKI WHERE UTKYMD <= $DEL_UTKYMD" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > KJNYMD
echo ""
echo "    �ȉ��̎�t���̃f�[�^��RIREKI�e�[�u������폜���܂��B"
for DEL_YMD in `cat KJNYMD`
do
    ## �폜�Ώۂ̎�t����S�ďo��
	echo "    �E$DEL_YMD"
done
echo ""
echo "[`date`] $DEL_DAYS���O�̎�t���擾 end ----------------------------<"
echo ""
echo ""


ERR_FLG=0

for DEL_YMD in `cat KJNYMD`
do
	B_CNT=0
	A_CNT=0
	L_CNT=0

	DEL_DATE=\'$DEL_YMD\'
	echo "[`date`] ��t�� = $DEL_DATE ���폜���Ă��܂��B------------>"
	echo ""

	echo "    [`date`] select before start ---------------------------->"
	echo ""
	echo "        > SELECT COUNT(UTKYMD) FROM RIREKI WHERE UTKYMD = $DEL_DATE"
	db2 "SELECT COUNT(UTKYMD) as CNT FROM RIREKI WHERE UTKYMD = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > CNT
	echo ""
	
	## �Ώێ�t���̍폜�O�̑S����
	B_CNT=`cat CNT`
	rm CNT
	echo "        [`date`] RIREKI�폜�O" $B_CNT "�� �ł��B"
	L_CNT=`expr $B_CNT / $DEL_CNT + 1`
	#echo "        [`date`] $L_CNT �� ���[�v���܂��B"
	echo ""
	echo "    [`date`] select before end ------------------------------<"
	echo ""
	echo ""

	echo "    [`date`] DELETE RIREKI UTKYMD = $DEL_DATE start ------>"
	echo ""
	echo "        > DELETE FROM (SELECT UTKYMD, IRINO, ZSSDINO, KNSGRP, KMKCD FROM RIREKI WHERE UTKYMD = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)"
	echo ""

	CNT_LOOP=1
	while [ $CNT_LOOP -le $L_CNT ];
	do
		db2 "DELETE FROM (SELECT UTKYMD, IRINO, ZSSDINO, KNSGRP, KMKCD FROM RIREKI WHERE UTKYMD = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)" > /dev/null
		db2 COMMIT > /dev/null

		if [ $L_CNT -eq $CNT_LOOP ];
		then
			echo "        [`date`] $B_CNT ���폜���܂����B"
		else
			CNT_ECHO=`expr $CNT_LOOP \* $DEL_CNT`
			echo "        [`date`] $CNT_ECHO / $B_CNT ���폜���܂����B"
		fi

		CNT_LOOP=`expr $CNT_LOOP + 1`
		
		#echo "        [`date`] SLEEP($SLEEP_CNT) START"
		## �X���[�v����(�b���͂��̃V�F���̐擪�Ő錾)
		sleep $SLEEP_CNT
		#echo "        [`date`] SLEEP($SLEEP_CNT) END"
	done
	
	echo ""
	echo "    [`date`] DELETE RIREKI UTKYMD = $DEL_DATE end --------<"

	echo ""
	echo ""
	echo "    [`date`] select after start ----------------------------->"
	echo ""
	echo "        > SELECT COUNT(UTKYMD) FROM RIREKI WHERE UTKYMD = $DEL_DATE"
	db2 "SELECT COUNT(UTKYMD) as CNT FROM RIREKI WHERE UTKYMD = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v ���R�[�h > CNT
	echo ""
	A_CNT=`cat CNT`
	rm CNT
	if [ $A_CNT -eq 0 ];
	then
		echo "        [`date`] RIREKI�폜��" $A_CNT "�� �ł��B"
	else
		echo "        �� [`date`] ERROR : RIREKI�폜��" $A_CNT "�� �ł��B"
		ERR_FLG=1
	fi
	echo ""
	echo "    [`date`] select after end -------------------------------<"
	echo ""
	echo ""

done

rm KJNYMD

if [ $ERR_FLG -eq 1 ];
then
	echo "[`date`] �����폜�ŃG���[���������܂����B"
	echo ""
	echo ""
	echo `date`" ERROR : �����폜�ŃG���[���������܂����B" >> $LOG_DIR/$NAME_ERRLOG"del_rireki.log"
fi

echo "[`date`] db2 terminate start -------------------------------->"
echo ""
db2 terminate;
echo ""
echo "[`date`] db2 terminate end ----------------------------------<"
echo ""

exit 0
