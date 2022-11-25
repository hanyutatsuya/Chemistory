#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#*****************************************************************
#   �a�l�k�l���������V�X�e��
#
#   �V�X�e�����F������V�X�e��
#   �t�@�C�����Fsun_bun_rec.sh
#	�T      �v�F�ً}�Ή�  SUN�������ʎ�M�t�@�C���̐U�蕪��
#
#*****************************************************************
#	No.Ver.    ���t           ���O          �R�����g
#---------------------------------------------------------------*
#	H000	2007.06.18	INTEC.INC	CREATE
#*****************************************************************

#-------------------------------------------------------------------
#
#	�e��ϐ��̐ݒ�
#
#-------------------------------------------------------------------
# HOME
KHOME=/home/kea00sys
# APPNM
EXENM=sun_bun_dst.sh

#TMP FILE
WK=/tmp/$$
# SUN�������ʃt�@�C����M�p�f�B���N�g��
RECD=/apdata/today/file/kinq
#�ً}�p�f�B���N�g��
KINQ=/apdata/today/online/host/Kinq
# �G���[�t�@�C���Ҕ��f�B���N�g��
ERRDIR=$KINQ/err_Recv
# �ً}�p�������ʃt�@�C���ړ���
BUNDIR=$KINQ/Recv/bun

# �ً}�p�������ʃt�@�C�����쐬
PRFN=KBU
EXFN=".dat"
# �ً}��������FTP���M�I���t�@�C��
ENDFN="KBUNEND.dat"

# �ً}�p�˗��t�@�C���ړ���
IRIDIR=$KINQ/Recv/iri
# �����ς݃t�@�C���Ҕ��f�B���N�g��
ENDDIR=$KINQ/Recv/sumi
# LOG FILE
APLOG=/apdata/aplog/$EXENM.log

DBG=$1							# DEBUG MODE�w��

YMD=`date +%Y%m%d`

#
#	LOG OUTPUT VARIABLE
PROCESSID=$$
WKUPAPP=$EXENM

db2 connect to kea00db user db2inst1 using db2inst1
if [ $? -gt 0 ]; then
    exit 1
fi

#-------------------------------------------------------------------
#
#	���s���f
#
#-------------------------------------------------------------------
ps -ef | grep sun
#
#	�d���������f

ps -ef | grep "$EXENM" | grep -v $$ | grep -v $PPID | grep -v grep | grep -v vi  > $WK.dup
if [ -s $WK.dup ]
then
	echo "[`date`] DUPLICATE EXIT !" >> $APLOG
	rm $WK.*
	db2 terminate
	exit 0
fi

#
#	�����������f		1:�������͏����𔲂���
db2 "select count(*) as uny from sysknrmst where UNYFLG='1'" | sed 's/ //g' | grep ^[0-9] | grep -v "���R�[�h" > $WK.uny

if [ -s $WK.uny ]
then
	CNT=`cat $WK.uny`
else
	echo "ERROR "
	db2 terminate
	rm $WK.*
	exit 0
fi
if [ $CNT -eq 1 ]
then
	echo "[`date`] ���������� EXIT !" >> $APLOG
	db2 terminate
	rm $WK.*
	exit 0
fi

#
#	�ً}�Ɩ��J�n���f	 �ً}�˗����b�gNo=0:�f�[�^���݂��Ȃ�
db2 "select count(*) as lotno from knkyulot where knskisymd=(select kkkjsriymd from sysknrmst) and kkirilotno=0" | sed 's/ //g' | grep ^[0-9] | grep -v "���R�[�h" > $WK.lotno

if [ -s $WK.lotno ]
then
	CNT=`cat $WK.lotno`
else
	echo "ERROR "
	db2 terminate
	rm $WK.*
	exit 0
fi
if [ $CNT -eq 0 ]
then
	echo "[`date`] �ً}�Ɩ��J�n�O EXIT !" >> $APLOG
	db2 terminate
	rm $WK.*
	exit 0
fi

#-------------------------------------------------------------------
#
#	�t�@�C���U�蕪��
#
#-------------------------------------------------------------------
#
#	�t�@�C����M�p�f�B���N�g���ւ̈ړ�	
cd $RECD

#
# ���b�N�t�@�C���̗L��
if [ -s $ENDFN ]
then
	echo "[`date`] �ً}�p��������END�t�@�C����M����" >> $APLOG
else
	echo "[`date`] �ً}�p��������END�t�@�C����M���݂��� -> EXIT" >> $APLOG
	#	�����I��
	db2 terminate
	rm $WK.*
	exit 0
fi

#	���ϐ�����f�B���N�g�����������t�@�C���������o��
##LS=`basename $FILENM`
##mv $FILENM	$LS

#==========================================================================
#		
#		�t�@�C���U�蕪��
#		
#==========================================================================
##for FNM in `ls $BUN*`
for FNM in `ls KBUNCHU*`
do

	#	stat
	if [ -w $FNM ]
	then		
		echo "[`date`] �ً}�p�������ʃt�@�C����M [$FNM]" >> $APLOG
	else
		continue;
	fi

	#	�������ł͖������Ƃ��m�F 	wc��size��diff�����
	wc $FNM > $WK.mae
	sleep 2
	wc $FNM > $WK.ato
	diff $WK.mae $WK.ato > $WK.diff

	if [ -s $WK.diff ]
	then
		echo "[`date`] �ً}�p�������ʃt�@�C����M���@SKIP..... [$FNM]" >> $APLOG
		continue;
	fi

	#	�t�@�C�����쐬
	##BFNM=$PRFN.$FNM.`date +%m%d%H%M%S`$EXFN
	BFNM=$PRFN.`date +%m%d%H%M%S`

	#	�����σf�B���N�g���Ɉړ�
	mv $FNM $BUNDIR/$BFNM

	echo "[`date`] �t�@�C��MOVE EXECUTE [$FNM]->[$BFNM]" >> $APLOG
	#----------------
	#	LOG OUTPUT
	#----------------
	MESSAGE="SUN�������ʎ�M[$FNM]--->[$BFNM]"

	sh $KHOME/shell/hulft_ins_log.sh "T" $PROCESSID $WKUPAPP "$MESSAGE" 

	#	�t�@�C�����̃��j�[�N��KEEP�̂���SLEEP
	sleep 1
done

#==========================================================================
#		
#		�I������
#		
#==========================================================================
#	DB DISCONNECT
db2 terminate

#
#	�t�@�C����M�p�f�B���N�g���ւ̈ړ�	
cd $RECD

echo "[`date`] �ً}�p��������END�t�@�C����M�폜" >> $APLOG
rm $ENDFN

#
#	�����I���t�@�C���̈ړ�
for i in `find $IRIDIR  -name "END*" -print `
do
	mv $i  $ENDDIR
done

#
#  ���ԃt�@�C���̸ر
rm $WK*

exit 0
