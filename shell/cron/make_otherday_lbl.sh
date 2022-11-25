#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

#######################################################################
# 隔日検査用 10連ラベルファイル作成シェル
# $1 : 検査開始日
# $2 : サンプリングコード
#######################################################################

# DB接続情報

DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"
#DBNAME="kea00db9"
#DBUSER="kea00dbt"
#DBPASS="kea00dbt"

# 出力先情報
OUTPUTDIR="/apdata/today/file/label/10label/"
LBLFILENAME="$3.dat"

# 一時ファイル設定
FILE_FUKUSU="/tmp/TMP_FUKUSU.del"
FILE_KNTNO="/tmp/TMP_KNTNO.del"

SRIYMD_DB=$1	# 処理日(ＤＢ形式 YYYY-MM-DD)

# ラベル情報 ファイルの定義
WSCODE=" "		# ワークシートＮＯ（検査グループ ３桁）
BNCHUNO=0		# 分注No(サンプリングＳＥＱと同じ)
SMPCD=$2		# サンプリングコード(検査グループ ４桁)
SMPSEQ=0		# サンプリングＳＥＱ(分注Noと同じ)
SRIYMD=" "		# 処理日(ファイル形式 YYYYMMDD)
KNTNO=" "		# 検体ＮＯ
ID2=" "			# 元検体ラックＩＤ
CHKMJ=" "		# チェック文字
SECCD="A"		# セクション
BCRTJ=" "		# 分注必要量
FUKSUHN=" "		# 複数本取りフラグ
YSNFLG=" "		# 優先フラグ
TKTFLG=" "		# 凍結フラグ
KMKNM=" "		# 項目名
GRPNM=" "		# グループ名
FUKSUHNID2=" " 	# 元検体ラックＩＤ（２本目以降）

fnGetSmpKntno() {
	#	対象トレーの検体一覧

	db2 "
	EXPORT to ${FILE_KNTNO} of del \
	SELECT	BUN.SRIYMD \
			, BUN.KNTNO \
			, BUN.ID2 \
			, BUN.ID2POS \
			, BUN.CHKMJ \
			, SUBSTR(CHAR(DECIMAL( BCRTJ, 4, 0)), 1, 4) \
			, NIN.FUKSUHN \
			, BUN.UTKYMD \
			, BUN.IRINO \
			, BUN.SRTKEY \
	FROM \
		(	SELECT  DISTINCT UTKYMD \
					, IRINO \
					, SRIYMD \
					, KNTNO \
					, SMPCD \
					, CHKMJ \
					, ID2 \
					, ID2POS \
					, SRTKEY \
			FROM	BUNCHU \
			WHERE	SRIYMD = '$1' \
			AND		SMPCD = '$2' \
			AND		BNCKKA not in ('0','1') \
		) BUN \
		LEFT OUTER JOIN \
		(   SELECT  DISTINCT UTKYMD \
					, IRINO \
					, SRIYMD \
					, KNTNO \
					, FUKSUHN \
			FROM	NINSIKI \
		) NIN \
		ON  BUN.IRINO = NIN.IRINO \
		AND BUN.UTKYMD = NIN.UTKYMD \
		AND BUN.KNTNO = NIN.KNTNO \
		AND BUN.SRIYMD = NIN.SRIYMD \
		LEFT OUTER JOIN \
		(   SELECT  UTKYMD \
					, IRINO \
					, KNSGRP \
					, INT( trunc( DECIMAL(BCRTJ) / 1000 + .09, 1) * 1000) BCRTJ \
			FROM    V_BUNCHURYO \
		) V_BCR \
		ON  BUN.UTKYMD = V_BCR.UTKYMD \
		AND BUN.IRINO = V_BCR.IRINO \
    	AND BUN.SMPCD = V_BCR.KNSGRP \
	ORDER BY SRTKEY,ID2,ID2POS \
	" > /dev/null
	if [ $? -gt 0 ]; then
		echo "データの取得に失敗しました。"
		rm ${FILE_KNTNO}
		return 1
	fi

	return 0
}

fnGetFukusu() {

    db2 "
	EXPORT to ${FILE_FUKUSU} of del \
	SELECT  DISTINCT ID2 \
			, ID2POS \
	FROM	BUNCHU \
	WHERE	UTKYMD = '$1' \
	AND		IRINO = '$2' \
	AND		SRIYMD = '$3' \
	AND		KNTNO <> '$4' \
	AND		SMPCD = '${SMPCD}' \
	AND		ID2 <> '' \
	ORDER BY ID2,ID2POS \
    " > /dev/null
	if [ $? -gt 0 ]; then
		return 1
	fi
	
	return 0
}

#######################################################################
# メイン開始
#######################################################################

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS} > /dev/null

# 検査グループ(３桁に編集する)
if [ ${#SMPCD} -ge 5 ]; then
	WSCODE="`echo -e ${SMPCD} | cut -c3-5`"
elif [ ${#SMPCD} -ge 4 ]; then
	WSCODE="`echo -e ${SMPCD}  | cut -c2-4`"
fi

# 対象検体取得
fnGetSmpKntno ${SRIYMD_DB} ${SMPCD}
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# ファイルサイズ確認
if [ -s ${FILE_KNTNO} ]; then
	:
else
	echo "対象の検体が存在しません。"
	rm ${FILE_KNTNO}
	db2 terminate > /dev/null
	exit 0
fi

# 指定した検査グループの検体数分ループ
while read LINE_KNTNO
do
	# 擬似ＳＥＱを割り振る。（ラベル出力システムの仕様上、ＳＥＱが必要なため）
	BNCHUNO=$(( BNCHUNO + 1 )) 
	SMPSEQ=${BNCHUNO}
	# 処理日
	SRIYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 検体NO(検体NO桁数フラグから編集) 
	KNTNO=`echo -e ${LINE_KNTNO} | cut -d',' -f2 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	EDIT_KNTNO=`echo -e ${KNTNO} | cut -c3-11`"00"
	# 元検体位置情報の取得
	# ２ＩＤの種別(SSSS,VVVV等)
	ID2_PRE=`echo -e ${LINE_KNTNO} | cut -d',' -f3 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	#２ＩＤの下４桁
	ID2_NO=`echo -e ${LINE_KNTNO} | cut -d',' -f3 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
	if [ ${#ID2_PRE} -eq 0 ]; then
		ID2="       "
	elif [ "${ID2_PRE}" = "X" ]; then
		ID2=" 検 管 "
	elif [ "${ID2_PRE}" = "Y" ]; then
		ID2=" 事 前 "
	elif [ "${ID2_PRE}" = "_" ]; then
		ID2="       "
	else
		ID2POS=`echo -e ${LINE_KNTNO} | cut -d',' -f4 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
		ID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
		ID2=`printf "%1s%06d" "${ID2_PRE}" "${ID2_TMP}"`
	fi
	# チェック文字
	CHKMJ=`echo -e ${LINE_KNTNO} | cut -d',' -f5 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 必要分注量(項目マスタ、分注量マスタ等から算出)
	BCRTJ=`echo -e ${LINE_KNTNO} | cut -d',' -f6 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 複数本フラグ
	FUKSUHN=`echo -e ${LINE_KNTNO} | cut -d',' -f7 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 優先フラグ(未使用)
	YSNFLG="  "
	# 凍結フラグ(未使用)
	TKTFLG=" "
	# 項目名(未使用)
	KMKNM="      "
	# 項目名(未使用)
	GRPNM="    "
	# 複数本取り検体の元検体位置情報の取得
	FUKSUHNID2=""
	FUKSUHNID2_TMP=""
	UTKYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	YY=`echo ${UTKYMD} | cut -c1-4`
	MM=`echo ${UTKYMD} | cut -c5-6`
	DD=`echo ${UTKYMD} | cut -c7-8`
	UTKYMD_DB=${YY}-${MM}-${DD}
	IRINO=`echo -e ${LINE_KNTNO} | cut -d',' -f9 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	fnGetFukusu ${UTKYMD_DB} ${IRINO} ${SRIYMD_DB} ${KNTNO}
	if [ $? -gt 0 ]; then
		echo "データの取得に失敗しました。"
		db2 terminate > /dev/null
		exit 1
	fi
	while read LINE_FUKUSU
	do
		FUKSUHNID2_PRE=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
		FUKSUHNID2_NO=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
		if [ ${#ID2_PRE} -eq 0 ]; then
			FUKSUHNID2_TMP="       "
		elif [ "${ID2_PRE}" = "X" ]; then
			FUKSUHNID2_TMP=" 検 管 "
		elif [ "${ID2_PRE}" = "Y" ]; then
			FUKSUHNID2_TMP=" 事 前 "
		elif [ "${ID2_PRE}" = "_" ]; then
			FUKSUHNID2_TMP="       "
		else
			FUKSUHNID2POS=`echo -e ${LINE_FUKUSU} | cut -d',' -f2-2 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
			FUKSUHNID2_TMP=`expr \( ${FUKSUHNID2_NO} - 1 \) \* 50 + ${FUKSUHNID2POS}`
			FUKSUHNID2_TMP=`printf "%1s%06d" "${FUKSUHNID2_PRE}" "${FUKSUHNID2_TMP}"`
		fi
		# 複数本取り検体の元検体位置
		FUKSUHNID2="${FUKSUHNID2}""${FUKSUHNID2_TMP}"
	done < ${FILE_FUKUSU}

	rm ${FILE_FUKUSU}

	# label 情報の出力
	printf "%-3s%05d%-4s%05d%-8s%-11s%-7s%-2s%-1s%-4s%-1s%-2s%-1s%-6s%-4s%-70.70s\n" "${WSCODE}" "${BNCHUNO}" "${SMPCD}" "${SMPSEQ}" "${SRIYMD}" "${EDIT_KNTNO}" "${ID2}" "${CHKMJ}" "${SECCD}" "${BCRTJ}" "${FUKSUHN}" "${YSNFLG}" "${TKTFLG}" "${KMKNM}" "${GRPNM}" "${FUKSUHNID2}" >> WORK
	if [ $? -gt 0 ]; then
		echo "ファイルの出力に失敗しました。"
		db2 terminate > /dev/null
		exit 1
	fi
done < ${FILE_KNTNO}

rm ${FILE_KNTNO}

# 未送信ファイルがあった場合は結合
if [ -e ${OUTPUTDIR}${LBLFILENAME} ]; then
	mv ${OUTPUTDIR}${LBLFILENAME} ./WORK2
	cat ./WORK ./WORK2 >> ./${LBLFILENAME}
	rm WORK WORK2
else
	cat ./WORK >> ./${LBLFILENAME}
	rm WORK
fi

# ファイルを送信ディレクトリに移動
mv ${LBLFILENAME} ${OUTPUTDIR}${LBLFILENAME}

db2 terminate > /dev/null

exit 0
