#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#######################################################################
# 新１０連ラベルシステム用ファイル変換シェル
# $1 : 変換元ファイル名(フルパス)
# $2 : 変換後ファイル名(フルパス)
#######################################################################

# 新10連ラベル情報 ファイルの定義
SATE=""			# サテライトＩＤ
SMPWS=""		# サンプリングＷＳ名(システム内部で定義)
SMPSEQ=""		# サンプリングＳＥＱ
WSTCDE=""		# 検査グループ(４桁変換後･･５桁以上の場合、２桁目を削除する)
KMKNME=""		# 項目名 未使用
UKEYMD=""		# 受付日 YYYYMMDD
KNTNO=""		# 検体ＮＯ７桁＋枝番２桁
CHKMOJI=""		# チェック文字
ZAIRYO=""		# 材料コード アスタリスク固定
BUNRYO=""		# 分注量(１マイクロ単位)
ASIRYO=""		# 必要量 分注量と同じものを入れる
FUKA=""			# 負荷順番 未使用
TOKETU=""		# 凍結フラグ 未使用
TOSEKI=""		# 透析フラグ 未使用
ATUKAI=""		# 扱いフラグ 未使用
FUKUSU=""		# 複数本取りフラグ
SECID=""		# ２ＮＤ－ＩＤ
COUNT_KMKCD=""	# 項目数
SECID2=""		# ２ＮＤ－ＩＤ(複数本取り)
JIKAN=""		# サンプリング時間(サンプリング優先) 未使用
ORDER=""		# 検査日フラグ 未使用
YSN_FLG=""		# 優先フラグ 未使用
YOBI=""			# 予備 未使用

# 起動時引数
MOTO_FILE=$1	# 変換前のファイル名(フルパス)
SEND_FILE=$2	# 変換後のファイル名(フルパス)
SMPWS_CODE=$3	# 処理対象サンプリングコード(５桁コードは指定不可)
SMPWS_NAME=$4	# 表示用サンプリングコード

# ＤＢ接続先設定
DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"

TMP_COUNT_KMKCD="TMP_COUNT_KMKCD.del"

# 依頼項目数取得関数
fnCountKmkcd()
{

	YEAR_TMP=`echo $1 | cut -c 1-4`
	MONTH_TMP=`echo $1 | cut -c 5-6`
	DAY_TMP=`echo $1 | cut -c 7-8`
	SRIYMD=`printf "%-4s%s%-2s%s%-2s" "${YEAR_TMP}" "-" "${MONTH_TMP}" "-" "${DAY_TMP}"`

	db2 "
    EXPORT to ${TMP_COUNT_KMKCD} of del \
	SELECT COUNT(kmkcd) \
	FROM BUNCHU \
	WHERE SRIYMD = '${SRIYMD}' \
	AND KNTNO = '00$2' \
	AND SMPCD = '$3' \
	"

	if [ $? -gt 0 ]; then
		return 1
    fi

	return 0
}

if [ ! -e $1 ]; then
    echo "$1 NOT found."
	exit 1
fi

# DB接続
db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

while read MOTO_RECORD
do
	SATE="A00"
	SMPWS="${SMPWS_NAME}"
	SMPSEQ=`echo -e "${MOTO_RECORD}" | cut -c4-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# SEQ 80000 以上は再検分なので、読み飛ばし。前０があるので、一度、expr で計算する。
	TMP_CALC=`expr ${SMPSEQ} - 80000`
	if [ ${TMP_CALC} -ge 0 ]; then
		continue
	fi
	WSTCDE=`echo -e "${MOTO_RECORD}" | cut -c9-12 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 指定された検査グループ以外は読み飛ばし
	if [ "${WSTCDE}" != "${SMPWS_CODE}" ]; then
		continue
	fi
	WSTCDE="${SMPWS_NAME}"
	KMKNME="                                                                                                    "
	# 処理日
	UKEYMD=`echo -e "${MOTO_RECORD}" | cut -c18-25 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	KNTNO=`echo -e "${MOTO_RECORD}" | cut -c26-34 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	CHKMOJI=`echo -e "${MOTO_RECORD}" | cut -c44-45 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	ZAIRYO="*  "
	BUNRYO=`echo -e "${MOTO_RECORD}" | cut -c47-50 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	ASIRYO=$BUNRYO
	FUKA="  "
	TOKETU=" "
	TOSEKI=" "
	ATUKAI=" "
	FUKUSU=`echo -e "${MOTO_RECORD}" | cut -c51 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	SECID=`echo -e "${MOTO_RECORD}" | cut -c37-43 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 依頼項目数を追加
	fnCountKmkcd ${UKEYMD} ${KNTNO} ${SMPWS_CODE}
	if [ $? -gt 0 ]; then
		db2 terminate
		exit 1
	fi
	while read LINE_COUNT_KMKCD
	do
		COUNT_KMKCD=`echo -e ${LINE_COUNT_KMKCD} | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	done < ${TMP_COUNT_KMKCD}
	SECID2=`echo -e "${MOTO_RECORD}" | cut -c65-127 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	JIKAN="     "
	ORDER=" "
	YSN_FLG=" " 
	YOBI="               "

	# 新10連ラベルシステム用ファイル 情報の出力
	printf "%-3s%-4s%-5s%-4s%-100s%-8s%-9s%-2s%-3s%-5s%-5s%-2s%-1s%-1s%-1s%-1s%-7s%-7s%-63s%-5s%-1s%-1s%-15s\r\n" "${SATE}" "${SMPWS}" "${SMPSEQ}" "${WSTCDE}" "${KMKNME}" "${UKEYMD}" "${KNTNO}" "${CHKMOJI}" "${ZAIRYO}" "0${BUNRYO}" "0${ASIRYO}" "${FUKA}" "${TOKETU}" "${TOSEKI}" "${ATUKAI}" "${FUKUSU}" "${SECID}" "${COUNT_KMKCD}" "${SECID2}" "${JIKAN}" "${ORDER}" "${YSN_FLG}" "${YOBI}" >> WORK
done < ${MOTO_FILE}

if [ ! -e WORK ]; then
	dateStr=`date +%F_%T%t`
	echo "${dateStr} : 該当レコードなし"
	db2 terminate
	exit 9
fi

mv WORK ${SEND_FILE}

if [ -e ${TMP_COUNT_KMKCD} ]; then
	rm ${TMP_COUNT_KMKCD}
fi

db2 terminate
exit 0
