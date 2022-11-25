#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#------------------------------------------------------------------------------
#	定数
#------------------------------------------------------------------------------

MYNAME="iriFtp.sh"

#■FTP関連
FTP_HOSTNAME="kinkyu"
FTP_LOG="/apdata/aplog/iriFtp.log"
FTP_USER='kea00sys'
FTP_PASSWORD='kea00sys'

#■SQL関連
DB2_DBNAME="KEA00DB"
DB2_USER="db2inst1"
DB2_PASS="db2inst1"
DB2_EXE="db2"
DB2_OPTIONS="-x -s -f"
SQL_FILE="/apdata/aplog/iriFtp.sql"
SQL_LOG="/apdata/aplog/iriFtp.sql.log"

#■依頼関連
#IRI_PATH_LOCAL="/export/home/gyoko/dat/kinkyu"
IRI_PATH_LOCAL="/apdata/today/online/host/Kinq/Recv/iri"
#IRI_PATH_REMOTE="/home/kea00sys/work/askinq/irai"
IRI_PATH_REMOTE="."
IRI_LOCK_F_RLUKEE="RLUKEE.RLUKEE"
IRI_LOCK_F_RLUKEX="RLUKEX.RLUKEX"
IRI_DATA_F_RLUKEF="RLUKEF.RLUKEF"
IRI_DATA_F_IRAI="kin_irai.dat"

#■メッセージ
LOG_ST="▼▼▼【開始】"
LOG_ED="▲▲▲【終了】"
LOG_01_FNC="日次処理判定"
LOG_01_MSG_01="日次処理運用中です。"
LOG_02_FNC="緊業務開始判定"
LOG_02_MSG_01="緊急ロット情報に緊急緊急依頼ロットNo０が存在しません。"
LOG_03_FNC="依頼受信ロックチェック"
LOG_03_MSG_01="依頼受信ロックファイルが存在します。"
LOG_04_FNC="依頼ファイル取得ロック"
LOG_05_FNC="依頼ファイル取得"
LOG_05_MSG_01="依頼ファイルが存在しません。"
LOG_05_MSG_02="依頼ファイルのサイズが０バイトです。"
LOG_06_FNC="依頼ファイル・ロックファイル削除"
LOG_07_FNC="依頼ファイル名変更"
LOG_SQL_MSG_01="ＳＱＬが失敗しました"

#------------------------------------------------------------------------------
#	2重起動チェック
#------------------------------------------------------------------------------
cmdAliveProcNum=`ps -ef | grep $MYNAME | grep -v $$ | grep -v $PPID | grep -v grep | grep -v vi | wc -l`
if [ $cmdAliveProcNum -ne "0" ];then
	echo "2重起動"
	exit 1
fi

#------------------------------------------------------------------------------
#	関数
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
#	依頼受信
#------------------------------------------------------------------------------
#■依頼受信ロックファイル存在チェック
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_03_FNC $logDateTime
#cat << EOS | ftp -d >> $FTP_LOG 2>&1
cat << EOS | /usr/bin/lftp >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	USER $FTP_USER $FTP_PASSWORD
	passive
	ver
	lcd $IRI_PATH_LOCAL
	cd $IRI_PATH_REMOTE
	get $IRI_LOCK_F_RLUKEE
	cl
	by
EOS
if [ -f $IRI_PATH_LOCAL/$IRI_LOCK_F_RLUKEE ];
then
	echo $LOG_03_MSG_01
	echo $IRI_PATH_LOCAL/$IRI_LOCK_F_RLUKEE
	#■LOCAL 依頼受信ロックファイルの削除
	rm $IRI_PATH_LOCAL/$IRI_LOCK_F_RLUKEE

	exit 0	
fi
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_03_FNC $logDateTime

#■依頼ファイル取得ロックファイル作成
cd $IRI_PATH_LOCAL
echo "IRAI_GET_LOCK `date +'%Y/%m/%d %H:%M:%S'`" > $IRI_LOCK_F_RLUKEX

#■依頼ファイル取得ロック
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_04_FNC $logDateTime
#cat << EOS | ftp -d >> $FTP_LOG 2>&1
cat << EOS | ftp -n -d >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	quote USER $FTP_USER
	quote PASS $FTP_PASSWORD
	passive
	ver
	lcd $IRI_PATH_LOCAL
	cd $IRI_PATH_REMOTE
	put $IRI_LOCK_F_RLUKEX
	cl
	by
EOS
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_04_FNC $logDateTime

#■依頼ファイル取得
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_05_FNC $logDateTime
#cat << EOS | ftp -d >> $FTP_LOG 2>&1
cat << EOS | ftp -n -d >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	quote USER $FTP_USER
	quote PASS $FTP_PASSWORD
	passive
	ver
	lcd $IRI_PATH_LOCAL
	cd $IRI_PATH_REMOTE
	get $IRI_DATA_F_RLUKEF $IRI_DATA_F_IRAI
	cl
	by
EOS
iriErr=0
if [ ! -f $IRI_PATH_LOCAL/$IRI_DATA_F_IRAI ];
then
	echo $LOG_05_MSG_01
	iriErr=1
else
	if [ ! -s $IRI_PATH_LOCAL/$IRI_DATA_F_IRAI ];
	then
		echo $LOG_05_MSG_02
		iriErr=1
	fi
fi

if [ $iriErr = 1 ];
then
#cat << EOS | ftp -d >> $FTP_LOG 2>&1
cat << EOS | ftp -n -d >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	quote USER $FTP_USER
	quote PASS $FTP_PASSWORD
	passive
	ver
	cd $IRI_PATH_REMOTE
	delete $IRI_LOCK_F_RLUKEX
	cl
	by
EOS
exit 0
fi

logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_05_FNC $logDateTime

#■依頼ファイル・ロックファイル削除　
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_06_FNC $logDateTime
cat << EOS | ftp -n -d >> $FTP_LOG 2>&1
	op $FTP_HOSTNAME
	quote USER $FTP_USER
	quote PASS $FTP_PASSWORD
	passive
	ver
	cd $IRI_PATH_REMOTE
	delete $IRI_DATA_F_RLUKEF
	delete $IRI_LOCK_F_RLUKEX
	cl
	by
EOS
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_06_FNC $logDateTime

#■依頼ファイル名の変更
logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ST $LOG_07_FNC $logDateTime
NEW_IRI_DATA_F_IRAI=`/bin/date +'KIR.%m%d%H%M%S.dat'`
mv $IRI_PATH_LOCAL/$IRI_DATA_F_IRAI $IRI_PATH_LOCAL/$NEW_IRI_DATA_F_IRAI
echo $IRI_PATH_LOCAL/$NEW_IRI_DATA_F_IRAI

logDateTime="[`/bin/date +'%Y/%m/%d %H:%M:%S'`]"
echo $LOG_ED $LOG_07_FNC $logDateTime

exit 0
