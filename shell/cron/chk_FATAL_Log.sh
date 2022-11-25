#!/bin/bash
############################################################
#
# chk_FATAL_Log.sh 致命的エラーログ監視シェル
#
# 2012-02-03 Create H.Sekiya
# 2021-06-24 #01    smz   メール送信先アドレスを個人からメーリングリストへ変更
#
############################################################

# 監視停止ファイルの設定
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"

ERR_FLG="0"	# エラーログが存在したら立てるフラグ

# 監視対象の設定
DIR_LOG="/apdata/aplog"
NAME_ERRLOG="FATAL"
EXTENSION_LOG=".log"
EXTENSION_LOG_SUMI=".end"

# 一時ファイル
ERR_LOG="fatal_log"				# 存在しているログファイル名を格納

# FTP送信に使用するデータ
HOSTNAME="kensys02"				# 送信先ホスト名
USER="merits"					# ユーザー
PASSWORD="merits"				# パスワード
DIR_HOST="/home/ftp/mail"		# 送信先ディレクトリ名
DIR_LOCAL="/tmp"				# ローカルファイル名
#SEND_FILE_NAME="mail_send_err"	# 処理ファイル名
#送信ファイル名がしょぼいので変更	2021.07.06	Hanyu
SEND_FILE_NAME="A00_error_mail_"`date +'%Y%m%d_%H%M%S'`		# 処理ファイル名

# 監視停止ファイルの存在確認。(ファイルが存在する場合、チェックをしない。)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "監視停止ファイルが存在しています。"
	exit 0
fi

# Logディレクトリにエラーログが存在していないか確認
ls ${DIR_LOG}/${NAME_ERRLOG}*${EXTENSION_LOG} > ${DIR_LOCAL}/${ERR_LOG}
RET_STATUS=$?
if [ ${RET_STATUS} = "0" ]; then
	ERR_FLG="1"
	cat  ${DIR_LOCAL}/${ERR_LOG}
fi

# エラーログが存在した場合はメールを送信する。
if [ ${ERR_FLG} = "1" ]; then
	echo "CODE: SJIS" > ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]マルチ エラーログ 報告" >> ${DIR_LOCAL}/${SEND_FILE_NAME} 
	echo "BODY: " >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	while read MOTO_RECORD
	do
		echo -e "[ ${MOTO_RECORD} ]" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "-------------------------------------------------------------------" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		cat "${MOTO_RECORD}" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "-------------------------------------------------------------------" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	done < ${DIR_LOCAL}/${ERR_LOG}

	echo "上記、エラーログが存在しています。確認してください。" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${SEND_FILE_NAME}
	quit
	END_FTP
#	エラー発生チェック
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "エラーメールの送信に失敗しました。"
		exit 1
	fi

	echo "エラーログが存在。メールを送信しました。"
	# パトランプ点灯を追加 20210705
	/usr/bin/rsh -l root 10.1.51.157 ACOP 01010000

	# エラーログを送信済みの状態にリネームする。
	for MOTO_FILE_NAME in `cat ${DIR_LOCAL}/${ERR_LOG}`
	do
		MOVE_FILE_NAME=`echo ${MOTO_FILE_NAME} | sed -e "s/${EXTENSION_LOG}$/${EXTENSION_LOG_SUMI}/g"`.`date +"%Y%m%d%H%M%S"`
		mv ${MOTO_FILE_NAME} ${MOVE_FILE_NAME}
	done

	echo "エラーログを送信済みにリネームしました。"

	rm ${DIR_LOCAL}/${SEND_FILE_NAME}
	rm ${DIR_LOCAL}/${ERR_LOG}
	
	exit 0

fi

echo "エラーログは存在しませんでした。"
exit 0
