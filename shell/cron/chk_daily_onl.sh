#!/bin/bash
################################################################
#
# chk_daily_end.sh 日次オンライン可能監視シェル
#
# 2021-03-09 H.Sekiya
#            ・日次で翌日の業務開始可能な状態になったかどうかを確認する。
#
################################################################

# 監視対象の設定
DIR_OLDDAY="/apdata/oldday"
# 監視対象の日次ログファイル名
DAILY_LOG="daily.log"
# 監視対象のワード
DAILY_END_WORD1="常駐プロセスの起動 --- 終了"
DAILY_END_WORD2="日次処理 --- 終了"
# 日次開始のワード
DAILY_START_WORD="常駐プロセスの停止 --- 開始"
# エラー時の出力ログ名
DIR_ERRLOG="/apdata/aplog"
NAME_ERRLOG="FATAL_DAILY_ONL_"
EXTENSION_LOG=".log"

# oldday 下に存在する日次バックアップディレクトリを検索する。
ls -F ${DIR_OLDDAY} | grep / > ${DIR_ERRLOG}/tmp_DAILY_ONL.$$

# 日次バックアップディレクトリ分ループ
for DAILY_DIR  in `cat ${DIR_ERRLOG}/tmp_DAILY_ONL.$$ | sed -e "s/\///g"`
do
	# 日次ログファイルの中に開始メッセージが存在しない場合はスキップ。
	grep "${DAILY_START_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -ne "0" ]; then
		continue
	fi

	# 日次ログファイルの中に終了メッセージが存在する場合はスキップ。
	grep "${DAILY_END_WORD2}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -eq "0" ]; then
		continue
	fi

	# 日次ログファイルの中に常駐起動メッセージが存在するか確認。
	grep "${DAILY_END_WORD1}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG}
	RET_STATUS=$?
	if [ ${RET_STATUS} -ne "0" ]; then
		# 日次開始時刻と現在時刻を比較し、６０分以上経っていた場合、エラーメール送信
		START_TIME=`grep "${DAILY_START_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} | cut -b3-21`
		ELAPSE=`expr \( \`date +%s\` - \`date -d"${START_TIME}" +%s\` \) / 60`
		if [ ${ELAPSE} -ge 60 ]; then
			ERROR_LOG=${NAME_ERRLOG}${DAILY_DIR}${EXTENSION_LOG}
			echo "日次が開始してから６０分経過していますが、終了していません。" > ${DIR_ERRLOG}/${ERROR_LOG}
			echo "${DAILY_DIR} ログを確認して下さい。" >> ${DIR_ERRLOG}/${ERROR_LOG}
			tail -n 15 ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} >> ${DIR_ERRLOG}/${ERROR_LOG}
		fi
	fi
#	START_TIME=`grep "${DAILY_START_WORD}" ${DIR_OLDDAY}/${DAILY_DIR}/${DAILY_LOG} | cut -b3-21`
#	ELAPSE=`expr \( \`date +%s\` - \`date -d"${START_TIME}" +%s\` \) / 60`
done

rm ${DIR_ERRLOG}/tmp_DAILY_ONL.$$

exit 0
