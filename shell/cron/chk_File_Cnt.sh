#!/bin/sh
############################################################
#
# chk_File_Cnt.sh 結果ファイル滞留監視シェル
#
############################################################
DIR_LOG="/apdata/aplog"
ERR_LOG_FILE_NAME="FATAL_File_Cnt.log"	# メール送信ファイル名

# 監視ディレクトリ
CHK_DIR="/apdata/today/file/KEA00/kea00ap/kekka/Data"
# 監視対象ファイル 拡張子
CHK_FILE_EXT="dat"
# 滞留エラー件数 この設定値より多くファイルが滞留している場合をエラーとする。
RIMIT_FILE_CNT=1000
# リトライ回数 連続でこの回数分監視を行い、全てエラーならばエラーメールを送信する。
RETRY_CNT=6
# リトライ間隔(秒)
RETRY_INTERVAL=30

# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /${sem}.lock ${sem} || exit
trap "rm ${sem}; exit" 2 3 15

if [ -e "${DIR_LOG}/${ERR_LOG_FILE_NAME}" ]; then
	echo "未送信のエラーファイルが存在しています。 ${DIR_LOG}/${ERR_LOG_FILE_NAME}"
	exit 0
fi

ERR_FLG="NG"
for i in  `seq 1 ${RETRY_CNT}`
do
	FILE_CNT=`find ${CHK_DIR} -type f -maxdepth 1 -name *.${CHK_FILE_EXT} 2> /dev/null | wc -l`
	if [ ${FILE_CNT} -lt ${RIMIT_FILE_CNT} ]; then
		echo "結果情報ファイル数 ： ${FILE_CNT}"
		ERR_FLG="OK"
		break
	fi
	sleep ${RETRY_INTERVAL}
done

if [ ${ERR_FLG} = "NG" ]; then
	echo "結果情報ファイル数 ： ${FILE_CNT}"
	echo "結果情報ファイルが大量に滞留しています。確認してください。" > ${DIR_LOG}/${ERR_LOG_FILE_NAME}
fi

rm "${sem}"

exit 0
