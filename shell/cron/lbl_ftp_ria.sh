#!/bin/sh
############################################################
#
# lbl_sh 10連ラベル送信(ＲＩＡサテライトプリンタ用)
#
############################################################
DIR_LOG="/apdata/aplog"
LOG_FILE_NAME="lbl_ftp_RIA.log" # ログファイル名

FILE_COUNT=7 # 処理するファイル数 送信情報の数と同期をとること
# 送信情報=( 送信先IP ユーザー名 パスワード 送信先ディレクトリ 処理ファイル名 処理対象ＷＳコード 表示用ＷＳコード)
#FILE_NO_1=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL21.dat' '0054' '0054')
#FILE_NO_2=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL22.dat' '0151' '0151')
#FILE_NO_3=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL23.dat' '0152' '0152')
#FILE_NO_4=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL03_RIA.dat' '0703' '0703')
#FILE_NO_5=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL04_RIA.dat' '0182' '0182')
#FILE_NO_6=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL11_RIA.dat' '0802' '0802')
#FILE_NO_7=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL24.dat' '0054' '0056')
FILE_NO_1=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL21.dat' '0054' '0054')
FILE_NO_2=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL22.dat' '0151' '0151')
FILE_NO_3=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL23.dat' '0152' '0152')
FILE_NO_4=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL03_RIA.dat' '0703' '0703')
FILE_NO_5=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL08_RIA.dat' '0182' '0182')
FILE_NO_6=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL11_RIA.dat' '0802' '0802')
FILE_NO_7=('172.16.42.2' 'pot' 'pot' '/export/ligand/NFS/pot/CEM' 'A0_LBL24.dat' '0054' '0056')

# INFO 情報ファイル名
INFO_FILE_NAME="lblinf.dat"

DIR_SJDATA="/apdata/today/file/label/10label"
DIR_CRRNT="/apdata/today/file/label/10label/ftp"
SLEEP=2
# 10連ラベル用ファイル変換シェル
CONV_SHELL="/home/kea00sys/shell/cron/cnv_lbl_ria.sh"
# ラベルINFO
MAKE_INFO_SHELL="/home/kea00sys/shell/cron/make_lblinfo_ria.sh"

# 擬似二次元配列処理関数
array2()
{
  eval y='${'$1$2'['$3']}'
  echo $y
}

# 引数で指定したファイルを送信する。
send_ftp()
{
	SEND_FILE_NAME=$1	

	dateStr=`date +%F_%T%t`
	echo "${dateStr} : ＦＴＰ送信スタート ${SEND_FILE_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}"
	# ＦＴＰ送信
	/usr/bin/lftp -e 'debug -o /tmp/lbl_ftp_ria.log 3; set net:reconnect-interval-base 5; set net:max-retries 5' "${HOSTNAME}" <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_CRRNT}
	put ${SEND_FILE_NAME}
	quit
	END_FTP
	# エラー発生チェック
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		# エラーが発生した場合はＦＴＰの送信ログを残しておく。
		echo "${dateStr} : ＦＴＰ送信エラー発生" >> "${DIR_LOG}/${LOG_FILE_NAME}"
		cat /tmp/lbl_ftp_ria.log >> "${DIR_LOG}/${LOG_FILE_NAME}"
		rm /tmp/lbl_ftp_ria.log
		sleep ${SLEEP}
		return 1
	fi

	# 正常送信だった場合はＦＴＰのログを残さない。(ログが大きくなりすぎるため)
	rm /tmp/lbl_ftp_ria.log
	sleep ${SLEEP}
	return 0
}

if [ -e "/tmp/lbl_ftp.sh" ]; then
	exit
fi
# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /${sem}.lock ${sem} || exit
trap "rm ${sem}; exit" 1 2 3 15

for i in  `seq 1 $FILE_COUNT`
do
	HOSTNAME="$(array2 FILE_NO_ $i 0)"		# 送信先ホスト名
	USER="$(array2 FILE_NO_ $i 1)"			# ユーザー
	PASSWORD="$(array2 FILE_NO_ $i 2)"		# パスワード
	DIR_HOST="$(array2 FILE_NO_ $i 3)"		# 送信先ディレクトリ名
	FILE_NAME="$(array2 FILE_NO_ $i 4)"		# 処理ファイル名
	SMPWS_CODE="$(array2 FILE_NO_ $i 5)"	# 送信対象ＷＳコード
	SMPWS_NAME="$(array2 FILE_NO_ $i 6)"	# 表示用ＷＳコード

	TRNS_NAME="`date +%d%H%M%S`"	# 送信ファイル名
	
	echo "${FILE_COUNT} ${HOSTNAME} ${USER} ${PASSWORD} ${DIR_HOST} ${FILE_NAME} ${TRNS_NAME}.dat"

	# File Check
	if [ -r "${DIR_SJDATA}/${FILE_NAME}" ]; then
		dateStr=`date +%F_%T%t`
		echo "$dateStr : 未処理ファイル存在確認 ${FILE_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}"
	else
		echo "nofile : ${DIR_SJDATA}/${FILE_NAME}"
		continue
	fi

	echo "-----------START------------"

	echo ${FILE_NAME}

	cd "${DIR_SJDATA}"

	# 万が一未処理の tmp ファイルが残っていた場合は、リネームして保存する。
	if [ -e "${DIR_SJDATA}/${FILE_NAME}.tmp" ] ; then
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
	fi
	
	mv "${DIR_SJDATA}/${FILE_NAME}" "${DIR_SJDATA}/${FILE_NAME}.tmp"

	# ケミストリー用のラベル情報ファイルをRIA用のラベル情報ファイルに変換
	sh "${CONV_SHELL}" "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_CRRNT}/${TRNS_NAME}.dat" "${SMPWS_CODE}" "${SMPWS_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}" 2>&1
	EXITSTATUS=$?
	if [ ${EXITSTATUS} = "9" ]; then
		# 送信対象ＷＳのレコードがない場合は処理をスルー
		sleep ${SLEEP}
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_CRRNT}/${FILE_NAME}.${TRNS_NAME}"
		continue
	elif [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		# ファイルを元に戻す
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	send_ftp "${TRNS_NAME}.dat"
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	# inf ファイルの作成
	sh "${MAKE_INFO_SHELL}" "${DIR_CRRNT}" "${TRNS_NAME}.dat" "${SMPWS_NAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}" 2>&1
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		sleep ${SLEEP}
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	send_ftp "${INFO_FILE_NAME}"
	EXITSTATUS=$?
	if [ ${EXITSTATUS} != "0" ]; then
		cat "${DIR_SJDATA}/${FILE_NAME}.tmp" >> "${DIR_SJDATA}/${FILE_NAME}"
		mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_SJDATA}/${FILE_NAME}.tmp.`date '+%y%m%d%H%M%S'`"
		continue
	fi

	mv "${DIR_SJDATA}/${FILE_NAME}.tmp" "${DIR_CRRNT}/${FILE_NAME}.${TRNS_NAME}"

	sleep ${SLEEP}
done

rm "${sem}"

exit 0
