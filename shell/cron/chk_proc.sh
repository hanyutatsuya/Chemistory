#!/bin/bash
############################################################
#
# chk_proc.sh プロセス起動状況監視シェル
#
# 2009-09-25 Create 関家
# 2021-06-24 #01    smz   メール送信先アドレスを個人からメーリングリストへ変更
#
############################################################

# 監視停止ファイルの設定
STOP_DIR="/home/kea00sys/shell/cron"
STOP_FILE_NAME="STOP"
STOP_LD104_FILE_NAME="STOP_LD104"	# LD104 結果要求カード作成専用の監視停止ファイル(日曜日夜のみ停止する)

ZOKCHK_LIST_FILE="/apdata/today/file/list/HOKO.ZKSYU.FAX.INPUT.A00.SB"		# 属性エラーリストファイル

# 接続先ＤＢの情報
DB_NAME="kea00db"
DB_USER="db2inst1"
DB_PASS="db2inst1"

# フラグ
UNYFLG="0"	# システム管理マスタ 運用フラグの状況
ERR_FLG="0"	# 起動していないプロセスが存在したら立てるフラグ

# プロセス一覧(緊急関連のプロセスは現場で起動、停止ができるため、対象から除外する。)
PROC_Z_ID=(AD102 AD103 AD105 AD106 AD107 AD108 AD301 BD301 BD302 BD401 DD401 FD101 FD103 JD112 GD102 GD105 ZD101 LD101 LD103 LD104 LD105 LD106 MD101_L1 MD101_L2 MD102_L1 MD102_L2 MD103 MD104 MD105 ND101 ND102 hulsndd hulobsd hulrcvd)
PROC_Z_NM=(依頼展開 患者展開 分注展開 分注展開_裏プロセス ３ＩＤ受信 ３ＩＤ展開 要求カード作成 供給ストッカ 回収ストッカ サンプラ 結果登録 監視バッチ 自動校正 検査進行状況集計 HULFT送信 検査結果報告 ログ出力 属性エラーチェック 属性修正情報取得 結果要求カード作成 他サテライト結果情報取得 再計算処理 ＺＳオンライン１ ＺＳオンライン２ ＺＳ再検判定１ ＺＳ再検判定２ ＺＳ用投入トレー登録 ＺＳ用収納トレー登録 ＺＳ用結果登録 フロンティアラック登録 オーダーラック登録 HULFT_SND HULFT_OBS HULFT_RCV)
PROC_Z_NUM=${#PROC_Z_ID[*]}	# プロセスの数
PROC_Z_NUM=`expr ${PROC_Z_NUM} - 1`

# 一時ファイル
SELECT_UNY="select_uny"		# 日次中かチェックするＳＱＬの結果を格納
SELECT_BCHEND="select_bchend"	# 分注ＥＮＤ受信後かどうかチェックするＳＱＬの結果を格納
PS_KEKKA="ps_kekka" 		# 起動中プロセス一覧
ERR_APPL="err_appl"		# 異常終了しているプロセスを格納

# FTP送信に使用するデータ
HOSTNAME="kensys02"		# 送信先ホスト名
USER="merits"			# ユーザー
PASSWORD="merits"		# パスワード
DIR_HOST="/home/ftp/mail"	# 送信先ディレクトリ名
DIR_LOCAL="/tmp"		# ローカルファイル名
FILE_NAME="mail_send_err"	# 処理ファイル名

# cron から起動した shell で DB2 にアクセスする場合に必要
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

# 監視停止ファイルの存在確認。(ファイルが存在する場合、チェックをしない。)
if [ -e ${STOP_DIR}/${STOP_FILE_NAME} ]; then
	echo "監視停止ファイルが存在しています。"
	exit 0
fi

# 日次中かどうかチェック
db2 connect to ${DB_NAME} user ${DB_USER} using ${DB_PASS}
db2 "select UNYFLG from sysknrmst for read only" | grep ^[0-9] | sed 's/ //g' > ${DIR_LOCAL}/${SELECT_UNY}
db2 terminate
# 日次中の場合は終了する。
UNYFLG=`cat ${DIR_LOCAL}/${SELECT_UNY}`
if [ ${UNYFLG} = "1" ]; then
	rm ${DIR_LOCAL}/${SELECT_UNY}
	echo "日次中なので、処理を終了しました。" 
	exit 0
fi

rm ${DIR_LOCAL}/${SELECT_UNY}

ps ax > ${DIR_LOCAL}/${PS_KEKKA}
for ps_cnt in `seq 0 ${PROC_Z_NUM}`;
do
	grep ${PROC_Z_ID[$ps_cnt]} ${DIR_LOCAL}/${PS_KEKKA}
	RET_STATUS=$?
	if [ ${RET_STATUS} = "1" ]; then
		if [ ${PROC_Z_ID[$ps_cnt]} = "AD301" ] || [ ${PROC_Z_ID[$ps_cnt]} = "ND101" ] ; then
			# 要求カード作成プロセスは分注ＥＮＤが来ていない時だけエラーとする。
			db2 connect to ${DB_NAME} user ${DB_USER} using ${DB_PASS}
			db2 "select BCHENDFLG from sysknrmst for read only" | grep ^[0-9] | sed 's/ //g' > ${DIR_LOCAL}/${SELECT_BCHEND}
			db2 terminate
			BCHENDFLG=`cat ${DIR_LOCAL}/${SELECT_BCHEND}`
			if [ ${BCHENDFLG} = "0" ]; then
				ERR_FLG="1"
				echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
			fi
			rm ${DIR_LOCAL}/${SELECT_BCHEND}
		elif [ ${PROC_Z_ID[$ps_cnt]} = "LD101" ]; then
			# 属性エラーチェックプロセスは属性エラーリストファイルが作成されていない時だけエラーとする。
			if [ ! -e ${ZOKCHK_LIST_FILE} ]; then
				ERR_FLG="1"
				echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
			fi
		elif [ ${PROC_Z_ID[$ps_cnt]} = "LD104" ]; then
			# 結果要求カード作成は専用の監視停止ファイルが作成されていない時だけエラーとする。
			# 日曜日の夜にホストへ要求カードを送信するとエラーになる件についての対応
			if [ ! -e ${STOP_DIR}/${STOP_LD104_FILE_NAME} ]; then
				ERR_FLG="1"
				echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
			fi
		else
			ERR_FLG="1"
			echo "${PROC_Z_ID[$ps_cnt]} ${PROC_Z_NM[$ps_cnt]}" >> ${DIR_LOCAL}/${ERR_APPL}
		fi
	fi
done

rm ${DIR_LOCAL}/${PS_KEKKA}

# 起動していないプロセスが存在した場合はメールを送信する。
if [ ${ERR_FLG} = "1" ]; then
	echo "CODE: SJIS" > ${DIR_LOCAL}/${FILE_NAME}
	echo "TO: multi_log@bml.co.jp,multi_error@bml.co.jp" >> ${DIR_LOCAL}/${FILE_NAME}
	echo "SUBJECT: [`date`]マルチ異常報告" >> ${DIR_LOCAL}/${FILE_NAME}
	echo "BODY: " >> ${DIR_LOCAL}/${FILE_NAME}

	cat ${DIR_LOCAL}/${ERR_APPL} >> ${DIR_LOCAL}/${FILE_NAME}

	echo "" >> ${DIR_LOCAL}/${FILE_NAME}
	echo "上記プロセスが起動していません。確認してください。" >> ${DIR_LOCAL}/${FILE_NAME}

	/usr/bin/lftp -e 'set net:reconnect-interval-base 5; set net:max-retries 5' ${HOSTNAME} <<-END_FTP
	USER ${USER} ${PASSWORD}
	cd ${DIR_HOST}
	lcd ${DIR_LOCAL}
	put ${FILE_NAME}
	quit
	END_FTP

	rm ${DIR_LOCAL}/${ERR_APPL}
	rm ${DIR_LOCAL}/${FILE_NAME}

	echo "異常終了プロセスが存在。メールを送信しました。"
	exit 0

fi

echo "異常終了プロセスは存在しませんでした。"
exit 0
