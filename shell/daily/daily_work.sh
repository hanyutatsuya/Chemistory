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
echo "��                    �����������ĊJ���܂�                    ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "����������������������������������������������������������������"

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
# No.2 ��t������
#######################################################################

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
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ��������̎擾�� ���s���܂���" >> $ERR_LOG_DIR/$NAME_ERRLOG"daily.log"
    errMsg
fi

KJNSRIYMD=`cat $$`
rm $$

#-------------------------------------------------------------
# �{���̃o�b�N�A�b�v�f�B���N�g���̍쐬
#-------------------------------------------------------------
# EXPORT �o�͐�
EXPDIR=$BUPDIR/$KJNSRIYMD

cd $BUPDIR
mkdir $KJNSRIYMD

# ���Ƀf�B���N�g�������݂���ꍇ�͊���������t������mv����
if [ $? -gt 0 ]; then
    NDIR=`date +"%Y%m%d%H%M%S"`
    echo "�����f�B���N�g��[$KJNSRIYMD]��[${KJNSRIYMD}_$NDIR]�Ɉړ�"
    mv $KJNSRIYMD ${KJNSRIYMD}_$NDIR
	mkdir $KJNSRIYMD
fi

LOGFILE=$BUPDIR/$KJNSRIYMD/daily.log
echo "`date +"%Y/%m/%d %H:%M:%S"`���� �������� --- �J�n ����" | tee -a $LOGFILE
echo ""

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

# IA�ł̍폜�������I�����C���N���܂łɊԂɂ����悤�ɂ��邽�ߏ�������ύX
# IA �� ( socket �o�R��IA���shell���N��.backup->dell�j
sh $SHDIR/rsh_back_del.sh &

endMsg "�풓�v���Z�X�̒�~" $LOGFILE

#######################################################################
# No.4 �W�v�e�[�u���̍쐬
#######################################################################

startMsg "�W�v�e�[�u���̍쐬" $LOGFILE

# �o�b�N�A�b�v�f�B���N�g���ւ̈ړ�
cd $EXPDIR

# SHU_KEKKA
sh $SHDIR/exp_shu.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# ���ڕʃe�X�g���W�v
sh $SHDIR/js111.sh $KJNSRIYMD $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �����f�[�^�~��
sh $SHDIR/cnv_rireki.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �n���������@�������擾(�e�s�o)
sh $SHDIR/get_rireki_ftp.sh $EXPDIR >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �n���������@�������R���o�[�g�p�}�X�^�t�@�C���̎擾
sh $SHDIR/exp_tmp_mst.sh $DB $USER $PASS $KJNSRIYMD >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �n���������@�������R���o�[�g
$SHDIR/RirekiConv $EXPDIR >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �n���������@�������C���T�[�g
sh $SHDIR/imp_rireki_other.sh $DB $USER $PASS $EXPDIR >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �`�b�d�R���g���[���v�Z���ʍ쐬 �C���T�[�g
# ���s���Ă��A������J�o���\�Ȃ̂ŃG���[���������Ă���~���Ȃ��B
sh $SHDIR/imp_ctrl_074.sh $DB $USER $PASS >> $LOGFILE

endMsg "�W�v�e�[�u���̍쐬" $LOGFILE

#######################################################################
# No.5 �f�[�^�x�[�X�̃o�b�N�A�b�v�����k
#######################################################################

startMsg "�f�[�^�̃o�b�N�A�b�v" $LOGFILE

# �R���g���[�����ʂ̂ݓ�����RUNSTATS�������āA�Ɩ����͂����Ȃ��悤�ɕύX����B
db2 "RUNSTATS ON TABLE DB2INST1.CTRLKKA WITH DISTRIBUTION and detailed indexes all" >> $LOGFILE

# �o�b�N�A�b�v�f�B���N�g���ւ̈ړ�
cd $EXPDIR

# �f�[�^(�݌v�A�W�v�ȊO�j�o�b�N�A�b�v �S�� IXF FORMAT
sh $SHDIR/exp_all.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# ���񍐕�KEY�e�[�u��INSERT
sh $SHDIR/ins_mhk.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# ���񍐕��o�b�N�A�b�v IXF FORMAT
sh $SHDIR/exp_mhk.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "�f�[�^�̃o�b�N�A�b�v" $LOGFILE

#######################################################################
# No.6 �e�[�u���f�[�^�̍폜
#######################################################################

startMsg "�e�[�u���f�[�^�̍폜" $LOGFILE

# �����i�s�󋵕\�̑ޔ�
sh $SHDIR/exp_KNSSNKJYK.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

sh $SHDIR/delKea00_dat.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "�e�[�u���f�[�^�̍폜" $LOGFILE

#######################################################################
# No.7 ���񍐃f�[�^�̖߂�
#######################################################################

startMsg "���񍐃f�[�^�̖߂�" $LOGFILE

sh $SHDIR/imp_mhk.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

echo "[`date`][*.mhk] gzip start ----->" >> $LOGFILE
gzip *.mhk >> $LOGFILE

endMsg "���񍐃f�[�^�̖߂�" $LOGFILE

#######################################################################
# No.8 �t�@�C���̃o�b�N�A�b�v
#######################################################################

startMsg "�t�@�C���̃o�b�N�A�b�v" $LOGFILE

# Z ��
#sh $SHDIR/data_back.sh $EXPDIR >> $LOGFILE
echo "[`date`][data_back] start ----->" >> $LOGFILE
sh $SHDIR/data_back.sh $EXPDIR

endMsg "�t�@�C���̃o�b�N�A�b�v" $LOGFILE

#######################################################################
# No.9 �t�@�C���̍폜
#######################################################################

startMsg "�t�@�C���̍폜" $LOGFILE

# Z ��
sh $SHDIR/data_del.sh >> $LOGFILE

endMsg "�t�@�C���̍폜" $LOGFILE

#######################################################################
# No.10 ���t�̍X�V
#######################################################################

startMsg "���t�̍X�V" $LOGFILE

# ����SEQ�̔ԊǗ��e�[�u���ً̋}���̍폜
sh $SHDIR/del_knq_knsseqknri.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �V�X�e���Ǘ��}�X�^ ������N�����̐ݒ�
sh $SHDIR/upd_sysknrmst.sh $utkymd $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# �A�b�Z�C�X�P�W���[���}�X�^���݃`�F�b�N
# ���̃}�X�^�g�p���Ă��Ȃ����߃R�����g
# sh $SHDIR/chk_asyscdlmst.sh $DB $USER $PASS >> $LOGFILE

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
#		!!PG����printf�����X�o�͂���邽�߂�ނȂ�/dev/null���w��!!
##sh $SHDIR/prc_onoff.sh -START >> $LOGFILE
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
# No.13 �����̕ۑ�����(400��)���O�̃f�[�^�폜
#######################################################################

startMsg "�����̕ۑ�����(400��)���O�̃f�[�^�폜" $LOGFILE

# CHANGE DIRECTRY 
cd $EXPDIR

# �����폜�p�V�F��
sh $SHDIR/del_rireki.sh $DB $USER $PASS >> $LOGFILE

endMsg "�����̕ۑ�����(400��)���O�̃f�[�^�폜" $LOGFILE

#######################################################################
# No.14 �ݐσe�[�u���Ƀf�[�^�ǉ��E�ݐσe�[�u�����疢�񍐕��f�[�^�폜
#######################################################################

startMsg "�ݐςɒǉ����ݐς��疢�񍐕��폜" $LOGFILE

# �ݐ� IMPORT (ixf)
sh $SHDIR/imp_rui.sh $DB $USER $PASS >> $LOGFILE

# �W�v IMPORT (ixf)
sh $SHDIR/imp_shu.sh KEA00DBN $USER $PASS >> $LOGFILE

# ���񍐕��f�[�^�̗ݐρA�W�v�e�[�u������̍폜(IA)
sh $SHDIR/exp_DAY_MHKKEY.sh $DB $USER $PASS $EXPDIR >> $LOGFILE
sh $SHDIR/del_mhk_dbn.sh KEA00DBN $USER $PASS $EXPDIR >> $LOGFILE

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

# ���O���o�͂��Ȃ��悤�ɏC��
#sh $SHDIR/kekkaout_del.sh $EXPDIR >> $LOGFILE
echo "[`date`][kekka_out] tar cvfz start ----->" >> $LOGFILE
sh $SHDIR/kekkaout_del.sh $EXPDIR > /dev/null

endMsg "EXPORT�t�@�C��(ixf, msg)���k������out���k�E�폜" $LOGFILE

#######################################################################
# No.16 �ȍ~�̏����͗����Ɏ����z���Ă����Ȃ����ߍ폜
#######################################################################


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
echo "��           ���������̃��J�o���[���I�����܂���               ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "��                                                            ��"
echo "����������������������������������������������������������������"
echo "�d�m�s�d�q�L�[�������Ă�������"
read ans
exit 0

