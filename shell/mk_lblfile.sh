#!/bin/bash -

#######################################################################
# 10連ラベルファイル作成シェル（リカバリー用）
# $1 : 検査開始日
# $2 : トレーＩＤ
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

KNSKISYMD=$1
TRID=$2			# トレーＩＤ

# ＰＯＴ情報 ファイルの定義

WSCODE=" "		# ワークシートＮＯ（検査グループ ３桁）
BNCHUNO=" "		# 分注No(サンプリングＳＥＱと同じ)
SMPCD=" "		# サンプリングコード(検査グループ ４桁)
SMPSEQ=" "		# サンプリングＳＥＱ(分注Noと同じ)
SRIYMD=" "		# 処理日
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

fnGetWsSeqKnri() {
    db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

    #   対象トレーの検体一覧

	db2 "
	EXPORT to TMP_WSSEQKNRI.del of del messages TMP_WSSEQKNRI.msg \
	SELECT	KSKTKBN \
	FROM	WSSEQKNRI \
	WHERE	KNSKISYMD = '${KNSKISYMD}' \
	AND		WSSBT = '$1' \
	AND		WSNO = cast($2 as int) \
	"

	if [ $? -gt 0 ]; then
		db2 terminate
		return 1
	fi

	db2 terminate
	return 0
}

fnGetTrKntno() {
	db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

	#	対象トレーの検体一覧

	db2 "
	EXPORT to TMP_KNTNO.del of del messages TMP_KNTNO.msg \
	SELECT	ODR.KNSGRP \
			, ODR.TRID \
			, ODR.TRPOS \
			, ODR.SMPCD \
			, ODR.SRIYMD \
			, ODR.KNTNO \
			, ODR.KNTKETFLG \
			, BUN.ID2 \
			, BUN.ID2POS \
			, BUN.CHKMJ \
			, LPAD( BCRTJ, 4, '0' ) \
			, NIN.FUKSUHN \
			, ODR.IRINO \
	FROM \
		(	SELECT	DISTINCT KNSGRP \
					, TRID \
					, TRPOS \
					, SMPCD \
					, SRIYMD \
					, KNTNO \
					, KNTKETFLG \
					, UTKYMD \
					, IRINO \
			FROM	KENORDER \
			WHERE	KNSKISYMD = '${KNSKISYMD}' \
			AND		TRID = '${TRID}' \
		) ODR \
		LEFT OUTER JOIN \
		(	SELECT  DISTINCT SRIYMD \
					, KNTNO \
					, SMPCD \
					, CHKMJ \
					, ID2 \
					, ID2POS \
			FROM	BUNCHU \
		) BUN \
		ON  ODR.SMPCD = BUN.SMPCD \
		AND ODR.KNTNO = BUN.KNTNO \
		AND ODR.SRIYMD = BUN.SRIYMD \
		LEFT OUTER JOIN \
		(   SELECT  DISTINCT UTKYMD \
					, IRINO \
					, SRIYMD \
					, KNTNO \
					, FUKSUHN \
			FROM	NINSIKI \
		) NIN \
		ON  ODR.IRINO = NIN.IRINO \
		AND ODR.UTKYMD = NIN.UTKYMD \
		AND ODR.KNTNO = NIN.KNTNO \
		AND ODR.SRIYMD = NIN.SRIYMD \
		LEFT OUTER JOIN \
		(   SELECT  UTKYMD \
					, IRINO \
					, KNSGRP \
					, INT( trunc( DECIMAL(BCRTJ) / 1000 + .09, 1) * 1000) BCRTJ \
			FROM    V_BUNCHURYO \
		) V_BCR \
		ON  ODR.IRINO = V_BCR.IRINO \
    	AND ODR.KNSGRP = V_BCR.KNSGRP \
		AND ODR.UTKYMD = V_BCR.UTKYMD \
	ORDER BY TRID,TRPOS \
	"
	if [ $? -gt 0 ]; then
	#	rm TMP_KNTNO.del
		db2 terminate
		return 1
	fi

	db2 terminate
	return 0
}

fnGetFukusu() {
    db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

    db2 "
	EXPORT to TMP_FUKUSU.del of del messages TMP_FUKUSU.msg \
	SELECT  DISTINCT ID2 \
			, ID2POS \
	FROM	BUNCHU \
	WHERE	SRIYMD = '$1' \
	AND		IRINO = '$2' \
	AND		KNTNO <> '$3' \
	AND		SMPCD = '$4' \
	AND		ID2 <> '' \
	ORDER BY ID2,ID2POS \
    "
	if [ $? -gt 0 ]; then
		db2 terminate
		return 1
	fi
	
	db2 terminate
	return 0
}

fnGetFileName() {
    db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

    #   対象トレーの検体一覧

	db2 "
	EXPORT to TMP_KNSGMST.del of del messages TMP_KNSGMST.msg \
	SELECT	DISTINCT SPLBLID \
	FROM	KNSGMST \
	WHERE	KNSGRP = '$1' \
	AND		KAIYMD <= '${KNSKISYMD}' \
	AND		HAIYMD >= '${KNSKISYMD}' \
	"

	if [ $? -gt 0 ]; then
		db2 terminate
		return 1
	fi

	db2 terminate
	return 0
}

# トレーＩＤのラックＩＤ(2MLT,1SIN等)
TRID_PRE=`echo -e ${TRID} | cut -c1-4`
# トレーＩＤの下４桁
TRID_SEQ=`echo -e ${TRID} | cut -c5-8`

fnGetWsSeqKnri ${TRID_PRE} ${TRID_SEQ}
FILE_WSSEQKNRI=TMP_WSSEQKNRI.del
while read LINE_WSSEQKNRI
do
	# 出力されたＷＳの区分(再検ＷＳ,再測定ＷＳ等)
	KSKTKBN=`echo -e ${LINE_WSSEQKNRI} | cut -d',' -f1-1 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
done  < ${FILE_WSSEQKNRI}

fnGetTrKntno
if [ $? -gt 0 ]; then
	echo "データの取得に失敗しました。"
	exit 1
fi

# 指定したトレーに存在する検体数分ループ
FILE_KNTNO=TMP_KNTNO.del
while read LINE_KNTNO
do
	# 検査グループ(３桁に編集する)
	KNSGRP=`echo -e ${LINE_KNTNO} | cut -d',' -f1-1 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${#KNSGRP} -ge 5 ]; then
		WSCODE="`echo -e ${KNSGRP} | cut -c3-5`"
	elif [ ${#KNSGRP} -ge 4 ]; then
		WSCODE="`echo -e ${KNSGRP}  | cut -c2-4`"
	fi
	# 分注NO,サンプリングSEQ(トレーIDの下４桁、トレーPOS、検査工程区分から算出。同じ値となる。)
	TRPOS=`echo -e ${LINE_KNTNO} | cut -d',' -f3-3 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${KSKTKBN} = "K" -o  ${KSKTKBN} = "T" -o ${KSKTKBN} = "R" -o ${KSKTKBN} = "S" ]; then
		SMPSEQ_TMP=`expr \( ${TRID_SEQ} - 1 \) \* 100 + ${TRPOS} + 80000`
	else
		SMPSEQ_TMP=`expr \( ${TRID_SEQ} - 1 \) \* 100 + ${TRPOS}`
	fi
	SMPSEQ_END=${#SMPSEQ_TMP}
	if [ ${SMPSEQ_END} -ge 6 ]; then
		SMPSEQ_START=`expr ${SMPCEQ_END} - 5`
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c${SMPCEQ_START}-${SMPCEQ_END}`
	else
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c1-${SMPCEQ_END}`
	fi
	BNCHUNO=${SMPSEQ}
	# サンプリングコード
	SMPCD=`echo -e ${LINE_KNTNO} | cut -d',' -f4-4 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 処理日
	SRIYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f5-5 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 検体NO(検体NO桁数フラグから編集) 
	KNTNO_MOTO=`echo -e ${LINE_KNTNO} | cut -d',' -f6-6 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	KNTKETFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f7-7 | sed "s/\"//g" | sed "s/ //g"`
	if [ ${#KNTKETFLG} -eq 0 ]; then
		KNTNO=`echo -e "${KNTNO_MOTO}" | cut -c3-11`
		KNTNO=`printf "%s%s" "${KNTNO}" "00"`
	else
		KNTNO=${KNTNO_TMP}
	fi
	# 元検体位置情報の取得
	# ２ＩＤの種別(SSSS,VVVV等)
	ID2_PRE=`echo -e ${LINE_KNTNO} | cut -d',' -f8-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	#２ＩＤの下４桁
	ID2_NO=`echo -e ${LINE_KNTNO} | cut -d',' -f8-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
	if [ ${#ID2_PRE} -eq 0 ]; then
		ID2="       "
	elif [ "${ID2_PRE}" = "X" ]; then
		ID2=" 検 管 "
	elif [ "${ID2_PRE}" = "Y" ]; then
		ID2=" 事 前 "
	elif [ "${ID2_PRE}" = "_" ]; then
		ID2="       "
	else
		ID2POS=`echo -e ${LINE_KNTNO} | cut -d',' -f9-9 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
		ID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
		ID2=`printf "%1s%06d" "${ID2_PRE}" "${ID2_TMP}"`
	fi
	# チェック文字
	CHKMJ=`echo -e ${LINE_KNTNO} | cut -d',' -f10-10 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 必要分注量(項目マスタ、分注量マスタ等から算出)
	BCRTJ=`echo -e ${LINE_KNTNO} | cut -d',' -f11-11 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 複数本フラグ
	FUKSUHN=`echo -e ${LINE_KNTNO} | cut -d',' -f12-12 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
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
	YEAR_TMP=`echo ${SRIYMD} | cut -c 1-4`
	MONTH_TMP=`echo ${SRIYMD} | cut -c 5-6`
	DAY_TMP=`echo ${SRIYMD} | cut -c 7-8`
	SRIYMD_TMP=`printf "%-4s%s%-2s%s%-2s" "${YEAR_TMP}" "-" "${MONTH_TMP}" "-" "${DAY_TMP}"`
	IRINO=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	fnGetFukusu "${SRIYMD_TMP}" "${IRINO}" "${KNTNO_MOTO}" "${SMPCD}"
	FILE_FUKUSU="TMP_FUKUSU.del"
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

	# label 情報の出力
	printf "%-3s%05d%-4s%05d%-8s%-11s%-7s%-2s%-1s%-4s%-1s%-2s%-1s%-6s%-4s%-70.70s\n" "${WSCODE}" "${BNCHUNO}" "${SMPCD}" "${SMPSEQ}" "${SRIYMD}" "${KNTNO}" "${ID2}" "${CHKMJ}" "${SECCD}" "${BCRTJ}" "${FUKSUHN}" "${YSNFLG}" "${TKTFLG}" "${KMKNM}" "${GRPNM}" "${FUKSUHNID2}" >> WORK
done < ${FILE_KNTNO}

# 指定したトレーに存在する検体数分ループ
fnGetFileName "${KNSGRP}"
FILE_SPLBLID=TMP_KNSGMST.del
while read LINE_SPLBLID
do
	LBLFILENAME=`echo -e ${LINE_SPLBLID} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${#LBLFILENAME} -eq 0 ]; then
		exit 0
	else
		LBLFILENAME=${LBLFILENAME}.dat
	fi
	#未送信ファイルがあった場合は結合
	if [ -e ${OUTPUTDIR}${LBLFILENAME} ]; then
		mv ${OUTPUTDIR}${LBLFILENAME} ./WORK2
		cat ./WORK ./WORK2 > ./${LBLFILENAME}
		rm WORK WORK2
	else
		cat ./WORK > ./${LBLFILENAME}
		rm WORK
	fi
	#ファイルを送信ディレクトリに移動
	mv ${LBLFILENAME} ${OUTPUTDIR}${LBLFILENAME}
	break
done < ${FILE_SPLBLID}

exit 0
