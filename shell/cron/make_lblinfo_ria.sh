#!/bin/bash -

#######################################################################
# 新１０連ラベルシステム用ファイル変換シェル
# $1 : 変換元ファイル 存在ディレクトリ
# $1 : 変換元ファイル名
#######################################################################

# 出力情報ファイル名(フルパス)
INFO_FILE_NAME="lblinf.dat"
DIR_LOG="/apdata/aplog"

# INFOファイル定義
SYSDATETIME=""		# 作成日 作成時刻 yymmddhhmmss
MAKSBT=""			# 作成種別 ０固定
KNSSBT=""			# 検査種別 ０固定
OUTPUT=""			# 出力フラグ ０固定
WSTNAME=""			# ワークシート名 → 送信ファイル名
WSTCODE=""			# ワークシートコード
LBLFNAME=""			# ラベルファイル名
BCDFNAME=""			# バーコードファイル名 

SEND_FILE_DIR=$1	# 送信対象 ファイル存在ディレクトリ
SEND_FILE=$2		# 送信対象 ファイル名
SMPWS_NAME=$3		# サンプリングＷＳ名
START_SEQ=""		# 送信対象 開始ＳＥＱ
END_SEQ=""			# 送信対象 終了ＳＥＱ

if [ ! -e $1 ]; then
    echo "$1 NOT found."
	exit 1
fi

# lblinf.dat 情報の出力
SYSDATETIME=`date '+%y%m%d%H%M%S'`
MAKSBT="0"
KNSSBT="0"
OUTPUT="0"
START_SEQ_TMP=`head -n 1 ${SEND_FILE_DIR}/${SEND_FILE} | cut -c8-12`
START_SEQ=`expr ${START_SEQ_TMP} + 0`									# 送信ファイルの開始ＳＥＱ
END_SEQ_TMP=`tail -n 1 ${SEND_FILE_DIR}/${SEND_FILE} | cut -c8-12`
END_SEQ=`expr ${END_SEQ_TMP} + 0`										# 送信ファイルの終了ＳＥＱ
RECORD_COUNT=`wc -l < ${SEND_FILE_DIR}/${SEND_FILE}`
WSTNAME="SEQ ${START_SEQ}-${END_SEQ} (${RECORD_COUNT})"
WSTCODE="${SMPWS_NAME}"
LBLFNAME="${SEND_FILE}"
BCDFNAME=""

# 新10連ラベルシステム用ファイル 情報の出力
printf "%-12s%-1s%-1s%-1s%-20s%-7s%-12s%-12s\r\n" "${SYSDATETIME}" "${MAKSBT}" "${KNSSBT}" "${OUTPUT}" "${WSTNAME}" "${WSTCODE}" "${LBLFNAME}" "${BCDFNAME}" >> "${SEND_FILE_DIR}/WORK1"
EXITSTATUS=$?
if [ $EXITSTATUS != "0" ]; then
	exit 1
fi

# infファイル をEUCコードに変換
/usr/bin/iconv -f IBM943 -t EUC-JP-MS "${SEND_FILE_DIR}/WORK1" >> "${SEND_FILE_DIR}/WORK2"
EXITSTATUS=$?
if [ $EXITSTATUS != "0" ]; then
	exit 1
fi

if [ ! -e ${SEND_FILE_DIR}/${INFO_FILE_NAME} ]; then
	cat "${SEND_FILE_DIR}/WORK2" | sort -rk 1,12 -k 35,39 -o "${SEND_FILE_DIR}/WORK3"
else
	cat "${SEND_FILE_DIR}/WORK2" "${SEND_FILE_DIR}/${INFO_FILE_NAME}" | sort -rk 1,12 -k 35,39 -o "${SEND_FILE_DIR}/WORK3"
fi

mv "${SEND_FILE_DIR}/WORK3" "${SEND_FILE_DIR}/${INFO_FILE_NAME}"

rm "${SEND_FILE_DIR}/WORK1"
rm "${SEND_FILE_DIR}/WORK2"

exit 0
