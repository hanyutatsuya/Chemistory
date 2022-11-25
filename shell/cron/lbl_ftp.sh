#!/bin/sh
############################################################
#
# lbl_sh 10連ラベル送信
#
# 2016-09-01 Replace 関家 全面刷新
############################################################
DIR_LOG="/apdata/aplog"
LOG_FILE_NAME="lbl_ftp.log" # ログファイル名

FILE_COUNT=16 # 処理するファイル数 送信情報の数と同期をとること
# 送信情報=( 送信先IP ユーザー名 パスワード 送信先ディレクトリ 処理ファイル名 送信ファイル名 サブ送信先IP )
# サブ送信先IP 送信先と同じディレクトリ構成ならば、別サーバへも送信可能。移行時のテスト用
#ILE_NO_1=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL01.dat' 'multi01.dat' 'NONE')
#ILE_NO_2=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL02.dat' 'multi02.dat' 'NONE')
#ILE_NO_3=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL03.dat' 'multi03.dat' 'NONE')
#ILE_NO_4=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL04.dat' 'multi04.dat' 'NONE')
#ILE_NO_5=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL05.dat' 'multi05.dat' 'NONE')
#ILE_NO_6=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL06.dat' 'multi06.dat' 'NONE')
#ILE_NO_7=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL07.dat' 'multi07.dat' 'NONE')
#ILE_NO_8=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'FR_LBL01.dat' 'lblkes05.dat' 'NONE')
#ILE_NO_9=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL11.dat' 'multi11.dat' 'NONE')
#ILE_NO_10=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL12.dat' 'multi12.dat' 'NONE')
#ILE_NO_11=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL13.dat' 'multi13.dat' 'NONE')
#ILE_NO_12=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL14.dat' 'multi14.dat' 'NONE')
#ILE_NO_13=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL15.dat' 'multi15.dat' 'NONE')
#ILE_NO_14=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL08.dat' 'multi08.dat' 'NONE')
#ILE_NO_15=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL09.dat' 'multi09.dat' 'NONE')
#ILE_NO_16=('10.1.181.22' 'kea00sys' 'kea00sys' '/apdata/bkup/lbl_tst' 'A0_LBL10.dat' 'multi10.dat' 'NONE')

FILE_NO_1=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL01.dat' 'multi01.dat' 'NONE')
FILE_NO_2=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL02.dat' 'multi02.dat' 'NONE')
FILE_NO_3=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL03.dat' 'multi03.dat' 'NONE')
FILE_NO_4=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL04.dat' 'multi04.dat' 'NONE')
FILE_NO_5=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL05.dat' 'multi05.dat' 'NONE')
FILE_NO_6=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL06.dat' 'multi06.dat' 'NONE')
FILE_NO_7=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL07.dat' 'multi07.dat' 'NONE')
FILE_NO_8=('172.16.1.125' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'FR_LBL01.dat' 'lblkes05.dat' 'NONE')
FILE_NO_9=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL11.dat' 'multi11.dat' 'NONE')
FILE_NO_10=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL12.dat' 'multi12.dat' 'NONE')
FILE_NO_11=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL13.dat' 'multi13.dat' 'NONE')
FILE_NO_12=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL14.dat' 'multi14.dat' 'NONE')
FILE_NO_13=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL15.dat' 'multi15.dat' 'NONE')
FILE_NO_14=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL08.dat' 'multi08.dat' 'NONE')
FILE_NO_15=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL09.dat' 'multi09.dat' 'NONE')
FILE_NO_16=('10.1.181.161' 'kes0' 'kes0' '/export/home/kes0/dat/lbl' 'A0_LBL10.dat' 'multi10.dat' 'NONE')

CPY_FILE_COUNT=3 # ＲＩＡ送信用にコピーするファイル数 コピー情報の数と同期をとること
# コピー情報=( コピー元ファイル名 コピー先ファイル名 )
CPY_FILE_NO_1=('A0_LBL03.dat' 'A0_LBL03_RIA.dat') 
CPY_FILE_NO_2=('A0_LBL08.dat' 'A0_LBL08_RIA.dat')
CPY_FILE_NO_3=('A0_LBL11.dat' 'A0_LBL11_RIA.dat')

DIR_SJDATA="/apdata/today/file/label/10label"
DIR_CRRNT="/apdata/today/file/label/10label/ftp"
SLEEP=2

# 擬似二次元配列処理関数
array2()
{
	eval y='${'$1$2'['$3']}'
	echo $y
}

# 引数で指定したファイルを送信する。
send_ftp()
{
	SEND_HOSTNAME=$1
	SEND_FILE_NAME=$2

	dateStr=`date +%F_%T%t`
	echo "${dateStr} : ＦＴＰ送信スタート ${SEND_FILE_NAME} ${SEND_HOSTNAME}" >> "${DIR_LOG}/${LOG_FILE_NAME}"

	# ＦＴＰ送信
	/usr/bin/lftp -e 'debug -o /tmp/lbl_ftp.log 3; set net:reconnect-interval-base 5; set net:max-retries 5' ${SEND_HOSTNAME} <<-END_FTP
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
		cat /tmp/lbl_ftp.log >> "${DIR_LOG}/${LOG_FILE_NAME}"
		rm /tmp/lbl_ftp.log
		sleep ${SLEEP}
		return 1
	fi

	# 正常送信だった場合はＦＴＰのログを残さない。(ログが大きくなりすぎるため)	
	rm /tmp/lbl_ftp.log
	sleep ${SLEEP}
	return 0
}

if [ -r "/tmp/lbl_ftp_ria.sh" ]; then
	exit 
fi
# Control of exclusion
sem="/tmp/`basename $0`"
ln -s /$sem.lock $sem || exit
trap "rm $sem; exit" 1 2 3 15

# RIA 送信用ファイル複製
for j in  `seq 1 ${CPY_FILE_COUNT}`
do
	CPY_MOTO_NAME=$(array2 CPY_FILE_NO_ $j 0) # 処理ファイル名
	CPY_NAME=$(array2 CPY_FILE_NO_ $j 1) # 送信ファイル名

	if [ -r "${DIR_SJDATA}/${CPY_MOTO_NAME}" ]; then
		if [ -r "${DIR_SJDATA}/${CPY_NAME}" ]; then
			cat "${DIR_SJDATA}/${CPY_MOTO_NAME}" >> "${DIR_SJDATA}/${CPY_NAME}"
		else
			cp "${DIR_SJDATA}/${CPY_MOTO_NAME}" "${DIR_SJDATA}/${CPY_NAME}"
		fi
	fi
done

for i in  `seq 1 ${FILE_COUNT}`
do

	HOSTNAME=$(array2 FILE_NO_ $i 0)  # 送信先ホスト名
	USER=$(array2 FILE_NO_ $i 1)      # ユーザー
	PASSWORD=$(array2 FILE_NO_ $i 2)  # パスワード
	DIR_HOST=$(array2 FILE_NO_ $i 3)  # 送信先ディレクトリ名
	FILE_NAME=$(array2 FILE_NO_ $i 4) # 処理ファイル名
	TRNS_NAME=$(array2 FILE_NO_ $i 5) # 送信ファイル名
	SUB_HOSTNAME=$(array2 FILE_NO_ $i 6)  # サブ送信先ホスト名

	echo "${i} ${HOSTNAME} ${USER} ${PASSWORD} ${DIR_HOST} ${FILE_NAME} ${TRNS_NAME} ${SUB_HOSTNAME}"

	if [ -r ${DIR_SJDATA}/${FILE_NAME} ]; then
		dateStr=`date +%F_%T%t`
		echo "${dateStr} : ${FILE_NAME} 未処理ファイル存在確認" >> ${DIR_LOG}/${LOG_FILE_NAME}
	else
		echo "nofile : ${DIR_SJDATA}/${FILE_NAME}"
		continue
	fi

	echo ${FILE_NAME}

	cd ${DIR_SJDATA}
	
	mv ${DIR_SJDATA}/${FILE_NAME} ${DIR_SJDATA}/${FILE_NAME}.tmp
	# EUCコードに変換
	/usr/bin/iconv -f IBM943 -t EUC-JP-MS ${DIR_SJDATA}/${FILE_NAME}.tmp > ${DIR_SJDATA}/euc${FILE_NAME} 2> ${DIR_LOG}/fail
	
	EXITSTATUS=$?
	if [ $EXITSTATUS != "0" ]; then
        # handle the error...
        echo "iconv ERROR"
		mv ${DIR_SJDATA}/${FILE_NAME}.tmp ${DIR_SJDATA}/${FILE_NAME}.err
		dateStr=`date +%F_%T%t`
		sed "s/^/${dateStr}/" ${DIR_LOG}/fail >> ${DIR_LOG}/${LOG_FILE_NAME}
		rm ${DIR_LOG}/fail
        sleep ${SLEEP}
        continue
    fi

	rm ${DIR_LOG}/fail

	if [ -r ${DIR_CRRNT}/${TRNS_NAME} ]; then
		cat ${DIR_CRRNT}/${TRNS_NAME} ${DIR_SJDATA}/euc${FILE_NAME} > ${DIR_SJDATA}/trn${FILE_NAME}
	else
		cp ${DIR_SJDATA}/euc${FILE_NAME} ${DIR_SJDATA}/trn${FILE_NAME}
	fi

	sort < ${DIR_SJDATA}/trn${FILE_NAME} > ${DIR_CRRNT}/${TRNS_NAME}
	rm  ${DIR_SJDATA}/trn${FILE_NAME}
	rm  ${DIR_SJDATA}/euc${FILE_NAME}

	# ＦＴＰ送信。失敗したら次に移る。特にリカバリー等は行わない。
	send_ftp "${HOSTNAME}" "${TRNS_NAME}"

	# サブ送信先が設定されている場合は、そちらへも送信する。
	if [ ${SUB_HOSTNAME} != "NONE" ]; then
		# ＦＴＰ送信。失敗したら次に移る。特にリカバリー等は行わない。
		send_ftp "${SUB_HOSTNAME}" "${TRNS_NAME}"
	fi

	rm -f ${DIR_SJDATA}/${FILE_NAME}.tmp

	sleep ${SLEEP}
done

# Control of exclusion
rm "$sem"

exit 0
