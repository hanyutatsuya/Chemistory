#!/bin/bash
############################################################
#
# chk_STOP_File.sh プロセス監視停止 確認シェル
#
# 2016-04-07 Create H.Sekiya
# 2021-06-24 #01    smz   メール送信先アドレスを個人からメーリングリストへ変更
#
# 監視停止ファイルが存在している場合に警告メールを送信する。
# 監視処理を停止したまま、再開するのを忘れないようにするため、
# 一日一回確認するように設定する。
############################################################

# 監視対象の設定
CHK_DIR_Z="/home/kea00sys/shell/cron"

IA_CNT="4"
CHK_IA=(KEA00IAW21.bml.co.jp KEA00IAW22.bml.co.jp KEA00IAW23.bml.co.jp KEA00IAW24.bml.co.jp)
CHK_DIR_IA="/home/kea00sys/shell"

STOP_FILE_NAME="STOP"
STOP_LD104_FILE_NAME="STOP_LD104"

# FTP送信に使用するデータ
HOSTNAME="kensys02"					# 送信先ホスト名
USER="merits"						# ユーザー
PASSWORD="merits"					# パスワード
DIR_HOST="/home/ftp/mail"			# 送信先ディレクトリ名
DIR_LOCAL="/tmp"					# ローカルファイル名
SEND_FILE_NAME="mail_chk_stop"		# 処理ファイル名
SEND_FILE_BODY="mail_chk_stop_body"	# 処理ファイル名(本文)

# 前回の処理分がメール未送信で残っていた場合は処理を抜ける。
if [ -e ${DIR_LOCAL}/${SEND_FILE_NAME} ]; then
	exit 0
fi

# プロセス監視停止ファイルが存在した場合はメールを送信する。(ＡＰサーバ)
if [ -e ${CHK_DIR_Z}/${STOP_FILE_NAME} ]; then
	echo "kea00apa : ${CHK_DIR_Z}/${STOP_FILE_NAME}" >> ${DIR_LOCAL}/${SEND_FILE_BODY}
fi

# プロセス監視停止ファイル(LD104用)が存在した場合はメールを送信する。(ＡＰサーバ)
if [ -e ${CHK_DIR_Z}/${STOP_LD104_FILE_NAME} ]; then
	echo "kea00apa : ${CHK_DIR_Z}/${STOP_LD104_FILE_NAME}" >> ${DIR_LOCAL}/${SEND_FILE_BODY}
fi

# プロセス監視停止ファイルが存在した場合はメールを送信する。(ＩＡサーバ)
for i in `seq 0 $((${IA_CNT} - 1))`;
do
	RET=`rsh ${CHK_IA[$i]} "ls ${CHK_DIR_IA}/${STOP_FILE_NAME}"`
	if [ ! -z ${RET} ]; then
		echo "${CHK_IA[$i]} : ${CHK_DIR_IA}/${STOP_FILE_NAME}" >> ${DIR_LOCAL}/${SEND_FILE_BODY}
	fi
done

if [ -e ${DIR_LOCAL}/${SEND_FILE_BODY} ]; then
	echo "CODE: SJIS" > ${DIR_LOCAL}/${SEND_FILE_NAME} 
	echo "TO: multi_log@bml.co.jp" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "SUBJECT: [`date`]マルチ ＡＰサーバ エラー監視 停止" >> ${DIR_LOCAL}/${SEND_FILE_NAME} 
	echo "BODY: " >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "プロセス監視が停止しています。" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "監視を再開するには、下記のファイルを削除して下さい。" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	cat ${DIR_LOCAL}/${SEND_FILE_BODY} >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${SEND_FILE_NAME}
	quit
	END_FTP

	echo "監視停止ファイルが存在。メールを送信しました。"
	rm ${DIR_LOCAL}/${SEND_FILE_BODY}
	rm ${DIR_LOCAL}/${SEND_FILE_NAME}
fi

exit 0
