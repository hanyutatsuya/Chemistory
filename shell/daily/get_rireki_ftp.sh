#!/bin/sh
############################################################
#
#  ラボ検査分履歴ファイル受信用シェル
# $1 : 日次バックアップディレクトリ
############################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

# 処理するファイル数 送信情報の数と同期をとること
FILE_COUNT=1
# 送信情報=( 送信先IP ユーザー名 パスワード 受信元ディレクトリ 受信対象ID )
#FILE_NO_1=('10.1.42.134' 'kikan' 'kikan' '/home/kikan/Data/rireki/send/001' 'A00')
FILE_NO_1=('10.1.42.27' 'kikan' 'kikan' '/home/kikan/Data/rireki/send/001' 'A00')

DIR_DAILY=$1

SLEEP=2

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
	# ＦＴＰ受信
	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_KIKAN}
	lcd ${DIR_DAILY}
	mget -E *_${FILE_ID}.dat
	mget -E *_${FILE_ID}.trg
	quit
	END_FTP
	# エラー発生チェック
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		return 1
	fi

	# ファイルの件数チェック
	chk_file
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		return 1
	fi

	sleep ${SLEEP}
	return 0
}

######################################################################################
# trg ファイル内の件数と dat ファイル内のレコード数を比較する 
######################################################################################
chk_file()
{

	cd ${DIR_DAILY}

	for TRG_FILE_NAME in `ls *.trg`
	do
		FILE_BASENAME=`basename ${TRG_FILE_NAME} .trg`
		TRG_FILE_CNT=`cat ${FILE_BASENAME}.trg`
		DAT_FILE_CNT=`wc -l < ${FILE_BASENAME}.dat`
		if [ ${TRG_FILE_CNT} != ${DAT_FILE_CNT} ]; then
			echo "${TRG_FILE_NAME}:件数が合っていません。" > "${LOG_DIR}/${NAME_ERRLOG}get_rireki_ftp"
			return 1
		fi
	done

}

######################################################################################
# main 処理
######################################################################################
# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /${sem}.lock ${sem} || exit
trap "rm ${sem}; exit" 2 3 15

for i in  `seq 1 ${FILE_COUNT}`
do
	HOSTNAME="$(array2 FILE_NO_ $i 0)"		# 受信先ホスト名
	USER="$(array2 FILE_NO_ $i 1)"			# ユーザー
	PASSWORD="$(array2 FILE_NO_ $i 2)"		# パスワード
	DIR_KIKAN="$(array2 FILE_NO_ $i 3)"		# 受信先ディレクトリ名
	FILE_ID="$(array2 FILE_NO_ $i 4)"		# 受信ファイル名

	echo "履歴ファイル取得開始"

	get_ftp
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		echo "${HOSTNAME} : ファイルが取得できません。" >> ${LOG_DIR}/${NAME_ERRLOG}"get_rireki_ftp.log"
		rm "${sem}"
		exit 1
	fi

	echo "履歴ファイル取得終了"


	sleep ${SLEEP}
done

rm "${sem}"
exit 0
