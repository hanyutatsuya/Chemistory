#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#------------------------------------------------------------------------------
#	定数
#------------------------------------------------------------------------------

MYNAME="kkaFtp.sh"

#■FTP関連
#FTP_HOSTNAME="10.1.181.22"
FTP_HOSTNAME="kinkyu"
FTP_LOG="/apdata/aplog/kkaFtp.log"
FTP_USER='kea00sys'
FTP_PASSWORD='kea00sys'

#■SQL関連
DB2_DBNAME="KEA00DB"
DB2_USER="db2inst1"
DB2_PASS="db2inst1"
DB2_EXE="db2"
DB2_OPTIONS="-x -s -f"
SQL_FILE="/apdata/aplog/kkaFtp.sql"
SQL_LOG="/apdata/aplog/kkaFtp.sql.log"

#■結果関連
KKA_PATH_LOCAL="/apdata/today/online/host/Kinq/Send"
#KKA_PATH_REMOTE="/home/kea00sys/work/askinq/kekka"
KKA_PATH_REMOTE="."
KKA_PATH_DATA="/apdata/today/online/host/Kinq/Send"
KKA_PATH_DATA_END="/apdata/today/online/host/Kinq/ok_Send"
KKA_LOCK_F_RLDEND="RLDEND.RLDEND"
KKA_DATA_F_RLDATA="RLDATA.RLDATA"

KKA_DATA_F_LOG="/apdata/aplog/KKE_FILE_"

#■メッセージ
LOG_ST="▼▼▼【開始】"
LOG_ED="▲▲▲【終了】"
LOG_01_FNC="日次処理判定"
LOG_01_MSG_01="日次処理運用中です。"
LOG_02_FNC="緊業務開始判定"
LOG_02_MSG_01="緊急ロット情報に緊急緊急依頼ロットNo０が存在しません。"
LOG_03_FNC="送信対象結果ファイル存在チェック"
LOG_03_MSG_01="送信対象結果ファイルが存在しません。"
LOG_04_FNC="結果送信ロックチェック"
LOG_04_MSG_01="結果送信ロックファイルが存在します。"
LOG_05_FNC="結果ファイル送信"
LOG_06_FNC="結果ファイル送信ロック"
LOG_07_FNC="送信済結果ファイル退避"
LOG_SQL_MSG_01="ＳＱＬが失敗しました"
LOG_08_FNC="報告管理テーブル更新"

#------------------------------------------------------------------------------
#   2重起動チェック
#------------------------------------------------------------------------------
cmdAliveProcNum=`ps -ef | grep $MYNAME | grep -v $$ | grep -v $PPID | grep -v grep | grep -v vi | wc -l`
if [ $cmdAliveProcNum -ne "0" ];then
    echo "2重起動"
    exit 1
fi

#------------------------------------------------------------------------------
#   関数
#------------------------------------------------------------------------------
#■SQLエラーチェック
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
#	初期処理
#------------------------------------------------------------------------------
#■ローカルロックファイル削除
/bin/rm $KKA_PATH_LOCAL/$KKA_LOCK_F_RLDEND 2> /dev/null

#------------------------------------------------------------------------------
#	日次処理判定
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
#	緊業務開始判定
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
#	結果ファイル送信	
#------------------------------------------------------------------------------
#■送信対象結果ファイル存在チェック
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

#■AS400側ロックファイル存在確認
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

#■結果ファイルの送信
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

#■結果ファイル送信ロック作成
echo "KEKKA_SEND_LOCK `date +'%Y/%m/%d %H:%M:%S'`" > $KKA_PATH_LOCAL/$KKA_LOCK_F_RLDEND

#■結果ファイル送信ロック
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

#■結果ファイル送信ロック削除
rm $KKA_PATH_LOCAL/$KKA_LOCK_F_RLDEND

#■送信済結果ファイル退避
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
#	報告管理テーブル更新
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

