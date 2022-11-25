#!/bin/sh
############################################################
#
# chk_disk_val.sh ディスク容量監視シェル
#
# 2021-06-24 #01    smz   メール送信先アドレスを個人からメーリングリストへ変更
#
############################################################

# 監視停止ファイルの設定
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

DIR_LOG="/tmp"
ERR_TMP_FILE_NAME="chk_disk_val"	# 一時ファイル名 

# 処理するファイル数 送信情報の数と同期をとること
FILE_COUNT=6
# 送信情報=( ディレクトリ しきい値)
FILE_NO_1=('/' '90')
FILE_NO_2=('/boot/zipl' '50')
FILE_NO_3=('/home' '90')
FILE_NO_4=('/opt' '90')
FILE_NO_5=('/var' '80')
FILE_NO_6=('/apdata' '80')

SLEEP=2

# FTP送信に使用するデータ
MAILSERVERNAME="kensys02"			# 送信先ホスト名
USER="merits"						# ユーザー
PASSWORD="merits"					# パスワード
DIR_MAILSERVER="/home/ftp/mail"		# 送信先ディレクトリ名
SEND_FILE_NAME="mail_chk_disk_err"	# 処理ファイル名
SEND_MAIL_LOG="chk_disk_log"		# メール送信ファイル名

# 擬似二次元配列処理関数
array2()
{
	eval y='${'$1$2'['$3']}'
	echo $y
}

# エラーメールを送信する。
send_ftp()
{
	echo "CODE: SJIS" > ${DIR_LOG}/${SEND_FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOG}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]マルチ ＡＰサーバ ディスク容量 危険" >> ${DIR_LOG}/${SEND_FILE_NAME}
	echo "BODY: " >> ${DIR_LOG}/${SEND_FILE_NAME}

	echo "下記、ディスク容量がしきい値を越えています。確認してください。" >> ${DIR_LOG}/${SEND_FILE_NAME}
	echo "" >> ${DIR_LOG}/${SEND_FILE_NAME}
	cat ${DIR_LOG}/${ERR_TMP_FILE_NAME} >> ${DIR_LOG}/${SEND_FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${MAILSERVERNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_MAILSERVER}
	lcd ${DIR_LOG}
	put ${SEND_FILE_NAME}
	quit
	END_FTP
	# エラー発生チェック
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep 1
		return -1
	fi

	echo "エラーメールを送信しました。"

	return 0
}

# 監視停止ファイルの存在確認。(ファイルが存在する場合、チェックをしない。)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "監視停止ファイルが存在しています。"
	exit 0
fi

if [ -e ${DIR_LOG}/${ERR_TMP_FILE_NAME} ]; then
	rm ${DIR_LOG}/${ERR_TMP_FILE_NAME}
fi

for i in  `seq 1 ${FILE_COUNT}`
do
	CHK_DIR="$(array2 FILE_NO_ $i 0)"       # 確認ディレクトリ
	MAX_VAL="$(array2 FILE_NO_ $i 1)"       # しきい値

	VAL=`df -Pt ext4 | awk '$6 == "'"${CHK_DIR}"'" {print $5}'`
	VAL=`echo ${VAL} | sed -e 's/%//g'`
	if [ ${VAL} -gt ${MAX_VAL} ]; then
		echo "${CHK_DIR}：${VAL} (しきい値：${MAX_VAL}%)" >> "${DIR_LOG}/${ERR_TMP_FILE_NAME}"
	fi
done

if [ -e "${DIR_LOG}/${ERR_TMP_FILE_NAME}" ]; then
	# エラーメール送信
	send_ftp
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "${ERR_TMP_FILE_NAME} : 送信失敗"
	fi
else
	echo "ディスク容量は問題ありませんでした。"
fi

exit 0
