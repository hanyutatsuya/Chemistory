#!/bin/bash
################################################################
#
# chk_daily_end.sh 日次完了監視シェル
#
# 2014-07-01 Create H.Sekiya
#
# 2016-07-22 Update H.Sekiya
#             ・日次データのバックアップ自動取得機能追加
#
# 2021-07-06 Update Hanyu
#	ログファイルのタイムスタンプチェックを追加
#
################################################################

# 監視対象の設定
DIR_OLDDAY="/apdata/oldday"
# 監視対象の日次ログファイル名
DAILY_LOG="daily.log"
# 監視対象のワード
DAILY_END_WORD="日次処理 --- 終了"
# エラー時の出力ログ名
DIR_ERRLOG="/apdata/aplog"
NAME_ERRLOG="FATAL_DAILY_"`date +'%Y%m%d_%H%M%S'`
NAME_WARNLOG="WARNING_DAILY_"`date +'%Y%m%d_%H%M%S'`
EXTENSION_LOG=".log"

# バックアップ先設定 
BKUP_SERVER="10.1.181.22"
BKUP_PATH="/mnt/usb/bak_daily"

# バックアップ先設定追加(nfs で mount しているディレクトリ）
BKUP_PATH2="/apdata/today/file/KEA00/KEA00IAW02/bak_daily/"

# バックアップ対象かどうか（0:対象外 1:対象）
FLG_COPY="1"

# oldday 下に存在する日次バックアップディレクトリを検索する。
ls -F ${DIR_OLDDAY} | grep / | grep -v kekka_out | grep -v rack_out > ${DIR_ERRLOG}/tmp_DAILY_DIR.$$

# 日次バックアップディレクトリ分ループ
for DAILY_DIR  in `cat ${DIR_ERRLOG}/tmp_DAILY_DIR.$$ | sed -e "s/\///g"`
do
	# 日次ログファイルの中に終了メッセージが存在するか確認。
	grep "${DAILY_END_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -ne "0" ]; then
		#ログファイルのタイムスタンプと現在日時を比較
		#１５分以内ならＯＫとする
		RSTAMP=`date '+%s'`
		RSTAMP=$((RSTAMP-900))
		FSTAMP=`date '+%s' -r ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}`
		if [ ${RSTAMP} -gt ${FSTAMP} ]; then
			ERROR_LOG=${NAME_ERRLOG}${DAILY_DIR}${EXTENSION_LOG}
			echo "<<<<<  日次処理チェックメール  >>>>>" > ${DIR_ERRLOG}/${ERROR_LOG}
			echo "日次が正常に終わっていない可能性があります。" >> ${DIR_ERRLOG}/${ERROR_LOG}
			echo "${DAILY_DIR} ログを確認して下さい。" >> ${DIR_ERRLOG}/${ERROR_LOG}
			tail -n 15 ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} >> ${DIR_ERRLOG}/${ERROR_LOG}
		else
			ERROR_LOG=${NAME_WARNLOG}${DAILY_DIR}${EXTENSION_LOG}
			echo "<<<<<  日次処理チェック警告メール  >>>>>" > ${DIR_ERRLOG}/${ERROR_LOG}
			echo "日次が正常に終わっていない可能性がありますが" >> ${DIR_ERRLOG}/${ERROR_LOG}
			echo "過去１５分以内にログが出力されているので" >> ${DIR_ERRLOG}/${ERROR_LOG}
			echo "処理は進行中です。" >> ${DIR_ERRLOG}/${ERROR_LOG}
			tail -n 5 ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} >> ${DIR_ERRLOG}/${ERROR_LOG}
		fi
	else
		# 終了メッセージが存在する場合、バックアップサーバにコピー済みか確認
		for BKUP_DIR in `rsh ${BKUP_SERVER} ls ${BKUP_PATH}`; do
			if [ ${BKUP_DIR} = ${DAILY_DIR} ]; then
				FLG_COPY="0"
			fi
		done
		# バックアップサーバにコピーしていない場合、コピー実行
		if [ ${FLG_COPY} = "1" ]; then
			rcp -pr "${DIR_OLDDAY}/${DAILY_DIR}" "${BKUP_SERVER}:${BKUP_PATH}"
			# バックアップ先を追加
			cp -pr "${DIR_OLDDAY}/${DAILY_DIR}" "${BKUP_PATH2}"
		fi
		FLG_COPY="1"
	fi
done

rm ${DIR_ERRLOG}/tmp_DAILY_DIR.$$

exit 0
