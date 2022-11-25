#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#######################################################################
#
# chk_nyou_fumei.sh 尿電解質フメイ検体 確認シェル
#
# 2016-06-20 Create H.Sekiya
# 2021-06-24 #01    smz   メール送信先アドレスを個人からメーリングリストへ変更
#
#######################################################################

# DB接続情報

DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"
#DBNAME="kea00db9"
#DBUSER="kea00dbt"
#DBPASS="kea00dbt"

# FTP送信に使用するデータ
HOSTNAME="kensys02"			# 送信先ホスト名
USER="merits"				# ユーザー
PASSWORD="merits"			# パスワード
DIR_HOST="/home/ftp/mail"		# 送信先ディレクトリ名
DIR_LOCAL="/tmp"			# ローカルファイル名
SEND_FILE_NAME="nyou_bun_fumei"		# 処理ファイル名

# 出力先情報
TMP_FILE_NAME="TMP_BUNCHU.del"
SEND_FLG="0"
SLEEP="120"

cd ${DIR_LOCAL}

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

db2 "
EXPORT to ${DIR_LOCAL}/${TMP_FILE_NAME} of del \
SELECT  DISTINCT UTKYMD, IRINO \
FROM	BUNCHU \
WHERE	SRIYMD IN (SELECT DISTINCT KJNSRIYMD FROM SYSKNRMST) \
AND		SMPCD = '0003' \
AND		BNCKKA = 'G' \
ORDER BY UTKYMD, IRINO \
"
if [ $? -gt 0 ]; then
	db2 terminate
	exit 1
fi
	
db2 terminate

while read LINE_BUNCHU
do
	if [ ${SEND_FLG} != "1" ]; then
		echo "CODE: SJIS" > ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "SUBJECT: [`date`]尿電解質 フメイ検体 確認" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
		echo "BODY: " >> ${DIR_LOCAL}/${SEND_FILE_NAME}
	fi

	echo ${LINE_BUNCHU}  >> ${DIR_LOCAL}/${SEND_FILE_NAME}

	SEND_FLG="1"
done  < ${DIR_LOCAL}/${TMP_FILE_NAME}

if [ ${SEND_FLG} != "1" ]; then
	rm ${DIR_LOCAL}/${TMP_FILE_NAME}
	exit 0
fi

echo "" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
echo "上記、尿電解質でフメイ検体が存在しています。" >> ${DIR_LOCAL}/${SEND_FILE_NAME}
echo "検査室に連絡して対応を確認し、不要ならば削除して下さい。" >> ${DIR_LOCAL}/${SEND_FILE_NAME}

while [ 1 ]
do
	rm "${DIR_LOCAL}/work" > /dev/null

	dateStr=`date +%F_%T%t`
	# ＦＴＰ送信
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${SEND_FILE_NAME}
	quit
	END_FTP
	# エラー発生チェック
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
	else
		break
	fi
done

rm ${DIR_LOCAL}/${TMP_FILE_NAME}
rm ${DIR_LOCAL}/${SEND_FILE_NAME} 

exit

