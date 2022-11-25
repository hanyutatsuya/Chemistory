#!/bin/sh
#######################################################################
# ��������
# $1 : ���[�UID(DB2)
# $2 : �p�X���[�h(DB2)
#######################################################################

if [ $# -lt 2 ]
then
	echo "�������w�肵�ĉ�����"
	echo "sh daily.sh   ���[�UID(DB2)   �p�X���[�h(DB2)"
	exit 0
fi

DB=kea00db
USER=$1
PASS=$2

#-------------------------------------------------------------
#	MSG FUNCTION DEFINE
#-------------------------------------------------------------
startMsg() {
	echo "  `date +"%Y/%m/%d %H:%M:%S"`���� $1 --- �J�n ����" | tee -a $2
}

endMsg() {
	echo "  `date +"%Y/%m/%d %H:%M:%S"`���� $1 --- �I�� ����" | tee -a $2
}

errMsg() {
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"
	echo " "
	echo " �G���[���������܂����B�V�X�e���S���҂ɘA�����Ă��������B "
	echo " "
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"

	while [ 1 ]
	do
		sleep 1 
	done
}

echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
#######################################################################
# No.1	��������
#######################################################################

#-------------------------------------------------------------
#	��ƃf�B���N�g��
#-------------------------------------------------------------
# SHELL DIR
SHDIR=$HOME/shell/daily

# �o�b�N�A�b�v�f�B���N�g��
BUPDIR=/apdata/oldday

# �G���[���O�o�͐�
ERR_LOG_DIR="/apdata/aplog"

# �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="FATAL_"

while [ 1 ]
do
    echo ""
    echo "��imp_rui_work.sh ��p���ėݐςc�a�ւ̃C���|�[�g����蒼���܂��B"
    echo ""
	echo "��낵���ł����H(y/n)==>"
	read ans
	if [ "$ans" ]
	then
		if [ $ans = "y" ]
		then
			break
		else
			exit 0
		fi
	fi
done

#-------------------------------------------------------------
# DB2 CONNECT
#-------------------------------------------------------------
db2 connect to $DB user $USER using $PASS > /dev/null
if [ $? -gt 0 ]; then
	echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $ERR_LOG_DIR/$NAME_ERRLOG"daily.log"
    errMsg
fi

cd $BUPDIR

#######################################################################
# No.2 �ď������̓���
#######################################################################
ymd=`date +%Y%m%d --date '1 days ago'`
while [ 1 ]
do
	echo "��蒼�����s��������������͂��Ă�������($ymd) :"
	read ans
	if [ "$ans" ]
	then
		$SHDIR/checkdate.csh $ans
		if [ $? -ne 0 ]
		then
			echo "���t�̃t�H�[�}�b�g���قȂ�܂�(YYYYMMDD)"
			echo ""
			continue
		else
			ymd=$ans
		fi
	fi

	yy=`echo $ymd | cut -c1-4`
	mm=`echo $ymd | cut -c5-6`
	dd=`echo $ymd | cut -c7-8`
	KJNSRIYMD=$yy-$mm-$dd

	# �t�@�C���o�b�N�A�b�v��
	FBUDIR=$BUPDIR/$KJNSRIYMD
	if [ ! -d ${FBUDIR} ]; then
		echo "�Y�����̓����f�B���N�g�������݂��܂���(${FBUDIR})"
		echo ""
		continue
	fi

	echo "������[$KJNSRIYMD]���̗ݐσC���|�[�g����蒼���܂��B��낵���ł���(y/n)"
	read ans
	if [ "$ans" ]
	then
		if [ $ans = "y" ]
		then
			break
		fi
	fi
done

LOGFILE=$FBUDIR/daily.log

echo "-----------------------------------------------------------------" >> $LOGFILE
startMsg "�ݐσC���|�[�g���J�o���[����" $LOGFILE
echo "-----------------------------------------------------------------" >> $LOGFILE

#######################################################################
# No.14 �ݐσe�[�u���Ƀf�[�^�ǉ��E�ݐσe�[�u�����疢�񍐕��f�[�^�폜
#######################################################################

startMsg "�ݐςɒǉ����ݐς��疢�񍐕��폜" $LOGFILE

cd $FBUDIR
# �ݐ� IMPORT (ixf)
sh $SHDIR/imp_rui.sh $DB $USER $PASS >> $LOGFILE

# �W�v IMPORT (ixf)
sh $SHDIR/imp_shu.sh KEA00DBN $USER $PASS >> $LOGFILE

# ���񍐕��f�[�^�̗ݐρA�W�v�e�[�u������̍폜(IA)
sh $SHDIR/exp_DAY_MHKKEY.sh $DB $USER $PASS $FBUDIR >> $LOGFILE
sh $SHDIR/del_mhk_dbn.sh KEA00DBN $USER $PASS $FBUDIR >> $LOGFILE

endMsg "�ݐςɒǉ����ݐς��疢�񍐕��폜" $LOGFILE

#######################################################################
# No.15 EXPORT�t�@�C��(ixf, msg)���k������out���k�E�폜
# 		  EXPORT FILE COMPRESS
#######################################################################

startMsg "EXPORT�t�@�C��(ixf, msg)���k������out���k�E�폜" $LOGFILE

echo "[`date`][*.ixf] gzip start ----->" >> $LOGFILE
gzip *.ixf >> $LOGFILE

echo "[`date`][*.msg] gzip start ----->" >> $LOGFILE
gzip *.msg >> $LOGFILE

echo "[`date`][*.dat] gzip start ----->" >> $LOGFILE
gzip *.dat >> $LOGFILE

echo "[`date`][*.trg] gzip start ----->" >> $LOGFILE
gzip *.trg >> $LOGFILE

echo "[`date`][*.del] gzip start ----->" >> $LOGFILE
gzip *.del >> $LOGFILE

echo "[`date`][kekka_out] tar cvfz start ----->" >> $LOGFILE
sh $SHDIR/kekkaout_del.sh $FBUDIR

endMsg "EXPORT�t�@�C��(ixf, msg)���k������out���k�E�폜" $LOGFILE
echo ""
echo "`date +"%Y/%m/%d %H:%M:%S"`���� �������� --- �I�� ����" | tee -a $LOGFILE
echo ""
echo ""
exit 0
