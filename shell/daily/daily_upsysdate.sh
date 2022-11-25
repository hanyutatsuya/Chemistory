#!/bin/sh
#######################################################################
# ��������(���t�ԈႢ���J�o���[�p)
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

# �����_��DIR
CURDIR=`pwd`

# �o�b�N�A�b�v�f�B���N�g��
BUPDIR=/apdata/oldday

# �G���[���O�o�͐�
ERR_LOG_DIR="/apdata/aplog"

# �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="FATAL_"

echo ""
echo "����������������������������������������������������������������"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                    �����������J�n���܂�                    ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "����������������������������������������������������������������"
while [ 1 ]
do
    echo ""
    echo "���������C�����̓��������͍ς�ł��܂����H������"
    echo "�������@�e�[���̉�ʂ͏I�����Ă��܂����H�@������"
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

#-------------------------------------------------------------
# ���V�X�e���Ǘ��}�X�^��������̎擾
#-------------------------------------------------------------
db2 "select kjnsriymd from sysknrmst for read only" | grep ^2 > $$
KJNSRIYMD=`cat $$`
rm $$

LOGFILE=$BUPDIR/daily.log_$KJNSRIYMD
echo "`date +"%Y/%m/%d %H:%M:%S"`���� �������� --- �J�n ����" | tee -a $LOGFILE
echo ""

#######################################################################
# No.2 ��t������
#######################################################################
ymd=`date +%Y%m%d`
while [ 1 ]
do
	echo "��t������͂��Ă�������($ymd) :"
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
	utkymd=$yy-$mm-$dd

	echo "��t����[$utkymd]�ł�낵���ł���(y/n)" | tee -a $LOGFILE
	read ans
	if [ "$ans" ]
	then
		if [ $ans = "y" ]
		then
			break
		fi
	fi
done

#######################################################################
# No.3 �풓�v���Z�X�̒�~
#######################################################################

startMsg "�풓�v���Z�X�̒�~" $LOGFILE

# �^�p�t���OON
sh $SHDIR/upd_sysknrmst_uny.sh 1 $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
	errMsg
fi

# LD103,LD106 �͉^�p�t���O ON �ɂȂ�Ύ����ŗ�����̂ő҂B(���b�N�t�@�C���̑��݊m�F)
while [ 1 ]
do
	LOCK_FILE_NUM=`ls -U1 ~/bin/lock/*lock 2>/dev/null | wc -l`
	if [ ${LOCK_FILE_NUM} = "0" ] ; then
 		 break
	fi
	sleep 10
done

# �v���Z�X�I��
sh $SHDIR/prc_onoff.sh -STOP >> $LOGFILE

# IA���v���Z�X �����O�ғ�O/L���@�̊m�F
# 	IA_STT_FILE=./IA_STS.txt
sh $SHDIR/prcIA_stat.sh  >> $LOGFILE
sleep 3

# IA���v���Z�X�I��
sh $SHDIR/prcIA_onoff.sh -STOP >> $LOGFILE
sleep 10
# IA���v���Z�X kill (rsh)
sh $SHDIR/rsh_kill_prcIA.sh	 >> $LOGFILE

# �y�r�p�v���Z�X�I��
sh $SHDIR/prcZS_onoff.sh -STOP >> $LOGFILE
sleep 10

endMsg "�풓�v���Z�X�̒�~" $LOGFILE

#######################################################################
# No.10 ���t�̍X�V
#######################################################################

startMsg "���t�̍X�V" $LOGFILE

# �V�X�e���Ǘ��}�X�^ ������N�����̐ݒ�
sh $SHDIR/upd_sysknrmst.sh $utkymd $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi


# ����SEQ�̔ԊǗ��e�[�u���̏�����
sh $SHDIR/upd_knsseqknri.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "���t�̍X�V" $LOGFILE

#######################################################################
# No.11 Del�t�@�C���̍쐬
#######################################################################

startMsg "Del�t�@�C���̍쐬" $LOGFILE

# �o�͐�f�B���N�g��
outdir="/apdata/today/file/KEA00/kea00ap/master"

cd $outdir

sh $SHDIR/mk_delfile.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �o�͐�f�B���N�g��(ZS�p)
outdirZS="/apdata/today/file/KEA00/kea00ap/ZS050/mst_file"

cd $outdirZS

sh $SHDIR/mk_delfile_ZS.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "Del�t�@�C���̍쐬" $LOGFILE

#######################################################################
# No.12 �풓�v���Z�X�̋N��
#######################################################################

startMsg "�풓�v���Z�X�̋N��" $LOGFILE

# CHANGE DIRECTRY 
cd $CURDIR

# �v���Z�X�N��
sh $SHDIR/prc_onoff.sh -START > /dev/null

#  IA���v���Z�X�N��
sh $SHDIR/prcIA_onoff.sh -START >> $LOGFILE

#  �y�r�p�v���Z�X�N��
sh $SHDIR/prcZS_onoff.sh -START > /dev/null

# �^�p�t���OOFF
sh $SHDIR/upd_sysknrmst_uny.sh 0 $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "�풓�v���Z�X�̋N��" $LOGFILE
echo " "
echo "----------------------------------------------------"
echo "�����������@�I�����C�����\�ɂȂ�܂����@����������"
echo "----------------------------------------------------"
echo " "

#	�ً}�g�p���̂��ߋN�����Ȃ����@�̕\��
#	/tmp/IA_KNQ.txt
if [ -s /tmp/IA_KNQ.txt ]
then
	echo " "
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"
	echo " "
	cat /tmp/IA_KNQ.txt
	echo " "
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"
	echo " "
	echo " "
	cat /tmp/IA_KNQ.txt >> $LOGFILE
	rm /tmp/IA_KNQ.txt
fi

#######################################################################
# No.18 �I������
#######################################################################

db2 terminate > /dev/null
cd $CURDIR
echo ""
echo "`date +"%Y/%m/%d %H:%M:%S"`���� �������� --- �I�� ����" | tee -a $LOGFILE
echo ""
echo ""
echo "����������������������������������������������������������������"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                    �����������I�����܂���                  ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "����������������������������������������������������������������"
echo "�d�m�s�d�q�L�[�������Ă�������"
read ans
exit 0

