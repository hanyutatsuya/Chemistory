#!/bin/sh
############################################################
#
#  属性修正情報ファイル受信用シェル
#
############################################################
DIR_LOG="/apdata/aplog"
FILE_LOG_NAME="LD102_"
FILE_ERRLOG_NAME="FATAL_LD102_ERR"

# DIR_LOCAL_TMP の最後に / をつけないこと
DIR_LOCAL_TMP="/apdata/today/file/shusei/tmp"
DIR_LOCAL="/apdata/today/file/shusei"
FILE_HOST_PRX="SIRAI002_"

DIR_LAST_PROC="/home/kea00sys/bin/LD102_Log/"

DIR_PROC="/apdata/today/online/host/Recv/shusei"
FILE_PROC_PRX="SHU.data."

# 処理するディレクトリ数 送信情報の数と同期をとること
FILE_COUNT=7
# 送信情報=( 送信先IP ユーザー名 パスワード 受信元ディレクトリ )
# 受信元ディレクトリの最後に / をつけないこと
#ILE_NO_1=('10.1.42.141' 'kikan' 'kikan' '/home/kikan/Data/0/File/A00')
#ILE_NO_2=('10.1.42.141' 'kikan' 'kikan' '/home/kikan/Data/1/File/A00')
#ILE_NO_3=('10.1.42.141' 'kikan' 'kikan' '/home/kikan/Data/2/File/A00')
#ILE_NO_4=('10.1.42.141' 'kikan' 'kikan' '/home/kikan/Data/3/File/A00')
#ILE_NO_5=('10.1.42.141' 'kikan' 'kikan' '/home/kikan/Data/4/File/A00')
#ILE_NO_6=('10.1.42.141' 'kikan' 'kikan' '/home/kikan/Data/5/File/A00')
#ILE_NO_7=('10.1.42.141' 'kikan' 'kikan' '/home/kikan/Data/6/File/A00')
FILE_NO_1=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/0/File/A00')
FILE_NO_2=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/1/File/A00')
FILE_NO_3=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/2/File/A00')
FILE_NO_4=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/3/File/A00')
FILE_NO_5=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/4/File/A00')
FILE_NO_6=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/5/File/A00')
FILE_NO_7=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/6/File/A00')

SLEEP=1


# 擬似二次元配列処理関数
array2()
{
	eval y='${'$1$2'['$3']}'
	echo $y
}

######################################################################################
# 設定されているファイルを受信する。
######################################################################################
get_ftp()
{
	echo `date "+%Y/%m/%d %H:%M:%S"`" : ＦＴＰ受信開始[${SENDHOSTNAME}:${DIR_KIKAN}]"

	# ＦＴＰ受信
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${SENDHOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	mirror --include-glob ${FILE_HOST_PRX}* --only-missing -r ${DIR_KIKAN} ${DIR_LOCAL_TMP}
	quit
	END_FTP
	# エラー発生チェック
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		return 1
	fi

	echo `date "+%Y/%m/%d %H:%M:%S"`" : ＦＴＰ受信終了"

	sleep ${SLEEP}
	return 0
}

######################################################################################
# main 処理
######################################################################################
# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /${sem}.lock ${sem} || exit
trap "rm ${sem}; exit" 2 3 15

LOG_DATE=`date "+%Y%m%d"`

echo `date "+%Y/%m/%d %H:%M:%S"`" : LD102.sh : 処理起動" >> ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log" 2>&1

for i in  `seq 1 ${FILE_COUNT}`
do
	SENDHOSTNAME="$(array2 FILE_NO_ $i 0)"		# 送信先ホスト名
	USER="$(array2 FILE_NO_ $i 1)"			# ユーザー
	PASSWORD="$(array2 FILE_NO_ $i 2)"		# パスワード
	DIR_KIKAN="$(array2 FILE_NO_ $i 3)"		# 受信先ディレクトリ名

	get_ftp >>  ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log" 2>&1
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo `date "+%Y/%m/%d %H:%M:%S"`" : ${SENDHOSTNAME} : ファイルが取得できません。" >> ${DIR_LOG}/${FILE_ERRLOG_NAME}${LOG_DATE}".log"
		rm "${sem}"
		exit 1
	fi

	sleep ${SLEEP}
done

LAST_PROC_FILE=`ls -t ${DIR_LAST_PROC}/${FILE_HOST_PRX}* | head -n 1`

if [ -e "${LAST_PROC_FILE}" ]; then
	# 最終処理ファイルの更新日時－１秒 を取得する。
	LAST_PROC_DATE=`date "+%Y-%m-%d %H:%M:%S" -r "${LAST_PROC_FILE}"`
	LAST_PROC_DATE_AGO=`date -d "${LAST_PROC_DATE} 1 second ago" "+%Y-%m-%d %H:%M:%S"`
	# 取得したファイルのうち、作業対象のファイルのみ作業用ディレクトリへコピー
	find ${DIR_LOCAL_TMP}/ -name "${FILE_HOST_PRX}*" -newermt "${LAST_PROC_DATE_AGO}" -newercc ${LAST_PROC_FILE} -print0 | xargs -0 cp -p --target-directory=${DIR_LOCAL} 2> /dev/null
else
	# 作業ファイルが見当たらない場合は終了する。
	echo `date "+%Y/%m/%d %H:%M:%S"`" : ${DIR_LAST_PROC} : 最終処理ファイルが取得できません。" >> ${DIR_LOG}/${FILE_ERRLOG_NAME}${LOG_DATE}".log"
	rm "${sem}"
	exit 1
fi

FILE_DATE=`date "+%y%m%d%H%M%S"`
for FILE_NAME in `ls ${DIR_LOCAL}/${FILE_HOST_PRX}* | sort 2>/dev/null`
do
	CNT=0
	echo `date "+%Y/%m/%d %H:%M:%S"`" : ${FILE_NAME} : 属性修正情報 抽出処理開始" >> ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log" 2>&1

	while IFS= read -r MOTO_RECORD
	do
	        KKASSFLG=`echo -e "${MOTO_RECORD}" | cut -b376 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	        if [ "${KKASSFLG}" = "1" ]; then
	                echo -e "${MOTO_RECORD}" >> ${DIR_PROC}/${FILE_PROC_PRX}${FILE_DATE}
			CNT=$((++CNT))    
	        fi
	done < ${FILE_NAME}

	echo `date "+%Y/%m/%d %H:%M:%S"`" : ${FILE_NAME} : 属性修正情報 抽出処理終了:${CNT}件" >> ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log" 2>&1
done

if [ -e "${FILE_NAME}" ]; then
	# 最後に処理したファイルを変更する。
	rm ${DIR_LAST_PROC}/${FILE_HOST_PRX}*
	cp -p ${FILE_NAME} "${DIR_LAST_PROC}/"

	# 処理済みファイルを削除する。
	rm ${DIR_LOCAL}/${FILE_HOST_PRX}* 
	echo `date "+%Y/%m/%d %H:%M:%S"`" : LD102.sh : 処理終了。最終取得ファイル : ${FILE_NAME}" >> ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log" 2>&1
else
	echo `date "+%Y/%m/%d %H:%M:%S"`" : LD102.sh : 処理終了。取得ファイル 無し" >> ${DIR_LOG}/${FILE_LOG_NAME}${LOG_DATE}".log" 2>&1
fi

rm "${sem}"
exit 0
