#!/bin/sh
############################################################
#
# chk_IA_Log.sh ＩＡサーバエラーファイル受信用シェル
#
############################################################

# 監視停止ファイルの設定
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

DIR_LOG="/apdata/aplog"
LOG_FILE_NAME="chk_IA.log"				# ログファイル名
ERR_LOG_FILE_NAME="FATAL_chk_IA.log"	# メール送信ファイル名
#ERR_LOG_FILE_NAME="TST_chk_IA.log"		# メール送信ファイル名(テスト用)

# 処理するファイル数 送信情報の数と同期をとること
FILE_COUNT=5
# 送信情報=( 送信先IP ユーザー名 パスワード 受信元ディレクトリ 受信対象ファイル名 )
FILE_NO_1=('10.1.181.41' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA21.log')
FILE_NO_2=('10.1.181.42' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA22.log')
FILE_NO_3=('10.1.181.43' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA23.log')
FILE_NO_4=('10.1.181.44' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_IA24.log')
FILE_NO_5=('10.1.181.41' 'kea00sys' 'kea00sys' '/apdata/aplog' 'FATAL_CS_ERR.log')

DIR_HOST="/apdata/aplog"

SLEEP=2

# 擬似二次元配列処理関数
array2()
{
	eval y='${'$1$2'['$3']}'
	echo $y
}

# 引数で指定したファイルを受信する。
get_ftp()
{
	GET_END_FILE_NAME=${FILE_NAME}.`date '+%y%m%d%H%M%S'`

	dateStr=`date +%F_%T%t`
	# ＦＴＰ受信
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" >"${DIR_LOG}/IA_check_work" 2>&1 <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_IA}
	lcd ${DIR_HOST}
	get ${FILE_NAME} ${FILE_NAME}_EUC
	rename ${FILE_NAME} ${GET_END_FILE_NAME}
	quit
	END_FTP

	if [ -e "${DIR_HOST}/${FILE_NAME}_EUC" ]; then 
		/usr/bin/iconv -f EUC-JP-MS -t IBM943 "${DIR_HOST}/${FILE_NAME}_EUC" > ${DIR_HOST}/${FILE_NAME}
		rm ${DIR_HOST}/${FILE_NAME}_EUC
	fi

	sleep ${SLEEP}
	return 0
}

# 監視停止ファイルの存在確認。(ファイルが存在する場合、チェックをしない。)
if [ -e $STOP_DIR/$STOP_FILE_NAME ]; then
	echo "監視停止ファイルが存在しています。"
	exit 0
fi

for i in  `seq 1 ${FILE_COUNT}`
do
	HOSTNAME="$(array2 FILE_NO_ $i 0)"		# 受信先ホスト名
	USER="$(array2 FILE_NO_ $i 1)"			# ユーザー
	PASSWORD="$(array2 FILE_NO_ $i 2)"		# パスワード
	DIR_IA="$(array2 FILE_NO_ $i 3)"		# 受信先ディレクトリ名
	FILE_NAME="$(array2 FILE_NO_ $i 4)"		# 受信ファイル名

	echo "${FILE_COUNT} ${HOSTNAME} ${USER} ${PASSWORD} ${DIR_IA} ${FILE_NAME}"

	if [ -e "${DIR_HOST}/${FILE_NAME}" ]; then
		echo "ファイルが存在しています。 ${DIR_HOST}/${FILE_NAME}"
		continue
	fi

	ping -c 3 ${HOSTNAME} > /dev/null
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "${HOSTNAME} : 導通が確認できません。" >> "${DIR_LOG}/IA_check_err"
		continue
	fi

	GET_END_FILE_NAME=${FILE_NAME}.`date '+%y%m%d%H%M%S'`

	dateStr=`date +%F_%T%t`
	# ＦＴＰ受信
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_IA}
	lcd ${DIR_HOST}
	get ${FILE_NAME} ${FILE_NAME}_EUC
	mv ${FILE_NAME} ${GET_END_FILE_NAME}
	quit
	END_FTP

	if [ -e "${DIR_HOST}/${FILE_NAME}_EUC" ]; then 
		/usr/bin/iconv -f EUC-JP-MS -t IBM943 "${DIR_HOST}/${FILE_NAME}_EUC" > ${DIR_HOST}/${FILE_NAME}
		rm ${DIR_HOST}/${FILE_NAME}_EUC
	fi

	sleep ${SLEEP}
done

if [ -e "${DIR_HOST}/IA_check_err" ]; then
	mv "${DIR_HOST}/IA_check_err" "${DIR_HOST}/${ERR_LOG_FILE_NAME}" 
fi

exit 0
