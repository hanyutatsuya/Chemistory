#!/bin/bash
############################################################
#
# chk_ERR_File.sh エラーファイル監視シェル
#
# 2012-02-03 Create H.Sekiya
# 2021-06-24 #01    smz   メール送信先アドレスを個人からメーリングリストへ変更
#
############################################################

# 監視停止ファイルの設定
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

ERR_FLG="0"	# エラーファイルが存在したら立てるフラグ

# 監視対象の設定
CHK_ERR_DIR=("/apdata/today/online/host/Recv/bun/NG" \
             "/apdata/today/online/host/Recv/3id/NG" \
             "/apdata/today/file/NSWS/Send/RkInfo/Multi/Err" \
             "/apdata/today/file/NSWS/Send/RkInfo/Single/Err" \
             "/apdata/today/file/NSWS/Send/RkInfo/Single2/Err" \
             "/apdata/today/file/NSWS/Send/TrInfo/Multi/Err" \
             "/apdata/today/file/NSWS/Send/TrInfo/Single/Err" \
             "/apdata/today/file/NSWS/Send/TrInfo/Single2/Err" \
             "/apdata/today/file/NSWS/Recv/TrRk/Err" \
             "/apdata/today/file/NSWS/Recv/Stocker/Err" )
#
CHK_DIR_NUM=${#CHK_ERR_DIR[*]}
CHK_DIR_NUM=`expr ${CHK_DIR_NUM} - 1`

# 一時ファイル
ERR_LOG="err_file_log"			# 存在しているログファイル名を格納

# FTP送信に使用するデータ
HOSTNAME="kensys02"				# 送信先ホスト名
USER="merits"					# ユーザー
PASSWORD="merits"				# パスワード
DIR_HOST="/home/ftp/mail"		# 送信先ディレクトリ名
DIR_LOCAL="/tmp"				# ローカルファイル名
SEND_FILE_NAME="mail_send_err"	# 処理ファイル名
BIN_MODE="binary"				# 送信モード

if [ -e ${DIR_LOCAL}/${ERR_LOG} ]; then
	rm ${DIR_LOCAL}/${ERR_LOG}
fi

# 監視停止ファイルの存在確認。(ファイルが存在する場合、チェックをしない。)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "監視停止ファイルが存在しています。"
	exit 0
fi

# エラーディレクトリにファイルが存在していないか確認
for DIR_CNT in `seq 0 ${CHK_DIR_NUM}`;
do
	ls ${CHK_ERR_DIR[${DIR_CNT}]}/*
	RET_STATUS=$?
	if [ ${RET_STATUS} = "0" ]; then
		ERR_FLG="1"
		ls ${CHK_ERR_DIR[${DIR_CNT}]}/* >> ${DIR_LOCAL}/${ERR_LOG}
		echo "" >> ${DIR_LOCAL}/${ERR_LOG}
	fi
done

# エラーファイルが存在した場合はメールを送信する。
if [ ${ERR_FLG} = "1" ]; then

	echo "CODE: SJIS" > ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]マルチ エラーファイル 報告" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "BODY: " >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	cat ${DIR_LOCAL}/${ERR_LOG} >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "上記、エラーファイルが存在しています。確認してください。" >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${SEND_FILE_NAME}
	quit
	END_FTP

	echo "エラーファイルが存在。メールを送信しました。"

	rm ${DIR_LOCAL}/${SEND_FILE_NAME}
	rm ${DIR_LOCAL}/${ERR_LOG}
	
	exit 0

fi

echo "エラーファイルは存在しませんでした。"
exit 0
