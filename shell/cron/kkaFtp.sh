#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#------------------------------------------------------------------------------
#	�萔
#------------------------------------------------------------------------------

MYNAME="kkaFtp.sh"

#��FTP�֘A
#FTP_HOSTNAME="10.1.181.22"
FTP_HOSTNAME="kinkyu"
FTP_LOG="/apdata/aplog/kkaFtp.log"
FTP_USER='kea00sys'
FTP_PASSWORD='kea00sys'

#��SQL�֘A
DB2_DBNAME="KEA00DB"
DB2_USER="db2inst1"
DB2_PASS="db2inst1"
DB2_EXE="db2"
DB2_OPTIONS="-x -s -f"
SQL_FILE="/apdata/aplog/kkaFtp.sql"
SQL_LOG="/apdata/aplog/kkaFtp.sql.log"

#�����ʊ֘A
KKA_PATH_LOCAL="/apdata/today/online/host/Kinq/Send"
#KKA_PATH_REMOTE="/home/kea00sys/work/askinq/kekka"
KKA_PATH_REMOTE="."
KKA_PATH_DATA="/apdata/today/online/host/Kinq/Send"
KKA_PATH_DATA_END="/apdata/today/online/host/Kinq/ok_Send"
KKA_LOCK_F_RLDEND="RLDEND.RLDEND"
KKA_DATA_F_RLDATA="RLDATA.RLDATA"

KKA_DATA_F_LOG="/apdata/aplog/KKE_FILE_"

#�����b�Z�[�W
LOG_ST="�������y�J�n�z"
LOG_ED="�������y�I���z"
LOG_01_FNC="������������"
LOG_01_MSG_01="���������^�p���ł��B"
LOG_02_FNC="�ًƖ��J�n����"
LOG_02_MSG_01="�ً}���b�g���ɋً}�ً}�˗����b�gNo�O�����݂��܂���B"
LOG_03_FNC="���M�Ώی��ʃt�@�C�����݃`�F�b�N"
LOG_03_MSG_01="���M�Ώی��ʃt�@�C�������݂��܂���B"
LOG_04_FNC="���ʑ��M���b�N�`�F�b�N"
LOG_04_MSG_01="���ʑ��M���b�N�t�@�C�������݂��܂��B"
LOG_05_FNC="���ʃt�@�C�����M"
LOG_06_FNC="���ʃt�@�C�����M���b�N"
LOG_07_FNC="���M�ό��ʃt�@�C���ޔ�"
LOG_SQL_MSG_01="�r�p�k�����s���܂���"
LOG_08_FNC="�񍐊Ǘ��e�[�u���X�V"

#------------------------------------------------------------------------------
#   2�d�N���`�F�b�N
#------------------------------------------------------------------------------
cmdAliveProcNum=`ps -ef | grep $MYNAME | grep -v $$ | grep -v $PPID | grep -v grep | grep -v vi | wc -l`
if [ $cmdAliveProcNum -ne "0" ];then
    echo "2�d�N��"
    exit 1
fi

#------------------------------------------------------------------------------
#   �֐�
#------------------------------------------------------------------------------
#��SQL�G���[�`�F�b�N
sqlCheck()
{
	#sqlSts=`cat $1 | grep SQLSTATE | wc -l`
	if [ `cat $1 | grep SQLSTATE | wc -l` = 1 ]; then
	#if [ $sqlSts = 1 ]; then
		echo $LOG_SQL_MSG_01
		cat $2
		return 1
	fi
	return 0
}
#------------------------------------------------------------------------------
#	��������
#------------------------------------------------------------------------------
#�����[�J�����b�N�t�@�C���폜
/bin/rm $KKA_PATH_LOCAL/$KKA_LOCK_F_RLDEND 2> /dev/null

#------------------------------------------------------------------------------
#	������������
#------------------------------------------------------------------------------
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_01_FNC $logDateTime
cat << EOS > $SQL_FILE
connect to $DB2_DBNAME user $DB2_USER using $DB2_PASS
select 'UNYFLG=' || UNYFLG from SYSKNRMST
terminate
EOS
#cat $SQL_FILE
#echo "$DB2_EXE $DB2_OPTIONS $SQL_FILE > $SQL_LOG 2>&1"
$DB2_EXE $DB2_OPTIONS $SQL_FILE > $SQL_LOG 2>&1
sqlCheck $SQL_LOG $SQL_FILE
if [ $? = 1 ]; then
	echo $LOG_SQL_MSG_01
    exit 1
fi
if [ `cat $SQL_LOG | grep 'UNYFLG=1' | wc -l` = 1 ]; then
    echo $LOG_01_MSG_01
    exit 0
fi
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_01_FNC $logDateTime

#------------------------------------------------------------------------------
#	�ًƖ��J�n����
#------------------------------------------------------------------------------
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_02_FNC $logDateTime
cat << EOS > $SQL_FILE
connect to $DB2_DBNAME user $DB2_USER using $DB2_PASS
select 'KKIRILOTNO=' || char(count(*)) from KNKYULOT where KKIRILOTNO = 0
terminate
EOS
#cat $SQL_FILE
#echo "$DB2_EXE $DB2_OPTIONS $SQL_FILE > $SQL_LOG 2>&1"
$DB2_EXE $DB2_OPTIONS $SQL_FILE > $SQL_LOG 2>&1
sqlCheck $SQL_LOG $SQL_FILE
if [ $? = 1 ]; then
	echo $LOG_SQL_MSG_01
    exit 1
fi
if [ `cat $SQL_LOG | grep 'KKIRILOTNO=0' | wc -l` = 1 ]; then
    echo $LOG_02_MSG_01
    exit 0
fi
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_02_FNC $logDateTime


#------------------------------------------------------------------------------
#	���ʃt�@�C�����M	
#------------------------------------------------------------------------------
#�����M�Ώی��ʃt�@�C�����݃`�F�b�N
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_03_FNC $logDateTime
fLogFileName="$KKA_DATA_F_LOG`/bin/date +'%Y%m%d%H%M%S'`.log"
echo $fLogFileName
(cd $KKA_PATH_DATA;ls KKE*.dat) 2> /dev/null > $fLogFileName
#kkaFileCnt=`ls $KKA_PATH_DATA/KKE*.dat 2> /dev/null | wc -l`
kkaFileCnt=`cat $fLogFileName | wc -l`
if [ $kkaFileCnt = 0 ];
then
	echo $LOG_03_MSG_01
	rm $fLogFileName
	exit 0
fi
cat /dev/null > $KKA_PATH_LOCAL/$KKA_DATA_F_RLDATA
#for kkaFile in `ls $KKA_PATH_DATA/KKE*.dat`
for kkaFile in `cat $fLogFileName`
do
	echo $kkaFile
	cat $KKA_PATH_DATA/$kkaFile >> $KKA_PATH_LOCAL/$KKA_DATA_F_RLDATA
done
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_03_FNC $logDateTime

#��AS400�����b�N�t�@�C�����݊m�F
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_04_FNC $logDateTime
#cat << EOS | ftp -d >> $FTP_LOG 2>&1
cat << EOS | /usr/bin/lftp >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	USER $FTP_USER $FTP_PASSWORD
	passive
	ver
	lcd $KKA_PATH_LOCAL
	cd $KKA_PATH_REMOTE
	get $KKA_LOCK_F_RLDEND
	cl
	by
EOS
if [ -f $KKA_PATH_LOCAL/$KKA_LOCK_F_RLDEND ];
then
	echo $LOG_04_MSG_01
	rm $fLogFileName
	exit 0	
fi
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_04_FNC $logDateTime

#�����ʃt�@�C���̑��M
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_05_FNC $logDateTime
#cat << EOS | ftp -d >> $FTP_LOG 2>&1
cat << EOS | ftp -n -d >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	quote USER $FTP_USER
    quote PASS $FTP_PASSWORD
	passive
	ver
	lcd $KKA_PATH_LOCAL
	cd $KKA_PATH_REMOTE
	put $KKA_DATA_F_RLDATA
	cl
	by
EOS
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_05_FNC $logDateTime

#�����ʃt�@�C�����M���b�N�쐬
echo "KEKKA_SEND_LOCK `date +'%Y/%m/%d %H:%M:%S'`" > $KKA_PATH_LOCAL/$KKA_LOCK_F_RLDEND

#�����ʃt�@�C�����M���b�N
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_06_FNC $logDateTime
#cat << EOS | ftp -d >> $FTP_LOG 2>&1
cat << EOS | ftp -n -d >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	quote USER $FTP_USER
    quote PASS $FTP_PASSWORD
	passive
	ver
	lcd $KKA_PATH_LOCAL
	cd $KKA_PATH_REMOTE
	put $KKA_LOCK_F_RLDEND
	cl
	by
EOS
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_06_FNC $logDateTime

#�����ʃt�@�C�����M���b�N�폜
rm $KKA_PATH_LOCAL/$KKA_LOCK_F_RLDEND

#�����M�ό��ʃt�@�C���ޔ�
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_07_FNC $logDateTime
#/bin/mv $KKA_PATH_DATA/KKE*.dat $KKA_PATH_DATA_END 2> /dev/null
for kkaFile in `cat $fLogFileName`
do
	echo $kkaFile
	mv $KKA_PATH_DATA/$kkaFile $KKA_PATH_DATA_END/. 2> /dev/null
	echo "$KKA_PATH_DATA/$kkaFile $KKA_PATH_DATA_END/. "
done
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_07_FNC $logDateTime

#------------------------------------------------------------------------------
#	�񍐊Ǘ��e�[�u���X�V
#------------------------------------------------------------------------------
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_08_FNC $logDateTime
cat /dev/null > $SQL_FILE
echo "connect to $DB2_DBNAME user $DB2_USER using $DB2_PASS" >> $SQL_FILE
for kkaFile in `cat $fLogFileName`
do
	HKKSJNO=`expr substr $kkaFile 5 4`
	echo $kkaFile
	echo "update HKKKNRI set HKKJKFLG = '2', TNSSTDH=CURRENT TIMESTAMP, TNSEDDH = CURRENT TIMESTAMP where HKKSJNO = $HKKSJNO" >> $SQL_FILE
done
echo "terminate" >> $SQL_FILE
$DB2_EXE $DB2_OPTIONS $SQL_FILE > $SQL_LOG 2>&1
sqlCheck $SQL_LOG $SQL_FILE
if [ $? = 1 ]; then
	echo $LOG_SQL_MSG_01
	rm $fLogFileName
    exit 1
fi
rm $fLogFileName
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_08_FNC $logDateTime

