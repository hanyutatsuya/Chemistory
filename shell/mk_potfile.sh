#!/bin/bash -

#######################################################################
# ＰＯＴファイル作成シェル（リカバリー用）
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
OUTPUTDIR="/apdata/today/file/pot/"

# potinf.dat ファイルの定義

SYSDATE=" "		# システム時間（yyMMddHHmmss形式）
KNSKISYMD=$1	# 検査開始日
TRID=$2			# トレーＩＤ
WSNO1=" "		# ワークシートＮＯ
POTFILENAME=" "	# ＰＯＴファイル名

# ＰＯＴ情報 ファイルの定義

SECCD="A00"		# サテライトＩＤ
SRIYMD=" "		# 処理日
KNSGRP_4=" "	# 検査グループ(４桁変換後･･５桁以上の場合、２桁目を削除する)
SMPSEQ=" "		# サンプリングＳＥＱ
KNTNO=" "		# 検体ＮＯ
CHKMJ=" "		# チェック文字
ZRKGOU=" "		# 材料記号
BCRTJ=" "		# 分注必要量
FKJBN="00"		# 負荷順番
TKTFLG=" "		# 凍結フラグ
TSKFLG=" "		# 透析フラグ
KENKANFLG=" "	# 検管フラグ
SMPCD=" "		# サンプリングコード
WSNO2=" "		# ワークシートＮＯ（potinf.datファイル内のものとは若干書式が違う）
FUKSUHNNO=" "	# 複数本検体の数 (自検体を除く本数)
FUKSUHNID2=" "	# 複数本検体の元検体位置

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
	SELECT	ODR.SRIYMD \
			, ODR.KNSGRP \
			, ODR.TRID \
			, ODR.TRPOS \
			, ODR.KNTNO \
			, ODR.KNTKETFLG \
			, BUN.CHKMJ \
			, ODR.ZRCD \
			, DECIMAL( trunc( DECIMAL(V_BCR.BCRTJ) / 1000 + .09, 1), 3, 1) \
			, ODR.TKTFLG \
			, ODR.TSKFLG \
			, ODR.SMPCD \
			, BUN.ID2 \
			, BUN.ID2POS \
			, ODR.IRINO \
	FROM \
		(	SELECT	DISTINCT SRIYMD \
					, KNSGRP \
					, TRID \
					, TRPOS \
					, KNTNO \
					, KNTKETFLG \
					, TKTFLG \
					, TSKFLG \
					, ZRCD \
					, SMPCD \
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
		(   SELECT  UTKYMD \
					, IRINO \
					, KNSGRP \
					, BCRTJ \
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
	AND		ID2 <> ''
	ORDER BY ID2,ID2POS \
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

PRE_SMPSEQ="0" # 検体重複チェック用情報(前回サンプリングSEQ)
# 指定したトレーに存在する検体数分ループ
FILE_KNTNO=TMP_KNTNO.del
while read LINE_KNTNO
do
	# 処理日
	SRIYMD=`echo -e ${LINE_KNTNO} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 検査グループ(４桁に編集する)
	KNSGRP=`echo -e ${LINE_KNTNO} | cut -d',' -f2-2 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${#KNSGRP} -ge 5 ]; then
		KNSGRP_4="`echo -e ${KNSGRP} | cut -c1-1``echo -e ${KNSGRP} | cut -c3-5`"
	else
		KNSGRP_4="${KNSGRP}"
	fi
	# サンプリングSEQ(トレーIDの下４桁、トレーPOS、検査工程区分から算出)
	TRPOS=`echo -e ${LINE_KNTNO} | cut -d',' -f4-4 | sed  "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ ${KSKTKBN} = "K" -o  ${KSKTKBN} = "T" -o ${KSKTKBN} = "R" -o ${KSKTKBN} = "S" ]; then
		SMPSEQ_TMP=`expr \( ${TRID_SEQ} - 1 \) \* 100 + ${TRPOS} + 80000`
	else
		SMPSEQ_TMP=`expr \( $TRID_SEQ - 1 \) \* 100 + ${TRPOS}`
	fi
	SMPSEQ_END=${#SMPSEQ_TMP}
	if [ ${SMPSEQ_END} -ge 6 ]; then
		SMPSEQ_START=`expr ${SMPCEQ_END} - 5`
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c${SMPCEQ_START}-${SMPCEQ_END}`
	else
		SMPSEQ=`echo -e ${SMPSEQ_TMP} | cut -c1-${SMPCEQ_END}`
	fi
	# 検体重複チェック(今回と前回のサンプリングSEQの比較) 
	if [ ${SMPSEQ} -eq ${PRE_SMPSEQ} ]; then
		continue
	else
		PRE_SMPSEQ=${SMPSEQ}
	fi
	# 検体NO(検体NO桁数フラグから編集) 
	KNTNO_MOTO=`echo -e ${LINE_KNTNO} | cut -d',' -f5-5 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	KNTKETFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f6-6 | sed "s/\"//g" | sed "s/ //g"`
	if [ ${#NTKETFLG} -eq 0 ]; then
		KNTNO=`echo -e "${KNTNO_MOTO}" | cut -c3-11`
		KNTNO=`printf "%s%s" "${KNTNO}" "00"`
	else
		KNTNO=${KNTNO_TMP}
	fi
	# チェック文字
	CHKMJ=`echo -e ${LINE_KNTNO} | cut -d',' -f7-7 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	#材料記号(材料コードから設定)
	ZRCD=`echo -e ${LINE_KNTNO} | cut -d',' -f8-8 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	if [ "${ZRCD}" = "021" -o "${ZRCD}" = "022" -o "${ZRCD}" = "023" -o "${ZRCD}" = "024" ]; then
		ZRKGOU="S  "
	else
		ZRKGOU="E  "
	fi
	# 必要分注量(項目マスタ、分注量マスタ等から算出)
	BCRTJ_TMP=`echo -e ${LINE_KNTNO} | cut -d',' -f9-9 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	BCRTJ_TMP=`echo -e ${BCRTJ_TMP} | cut -c3-5`
	BCRTJ=`printf " %s " "${BCRTJ_TMP}"`
	# 凍結フラグ
	TKTFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f10-10 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	# 透析フラグ
	TSKFLG=`echo -e ${LINE_KNTNO} | cut -d',' -f11-11 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 検管フラグ(新フロになって、検管扱いがなくなったので、スペース固定)
	KENKANFLG_TMP=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-2`
	# 旧フロンティア仕様であるが、一応残しておく(新フロンティアにはXで始まるID2は存在しない)
	if [ "${KENKANFLG_TMP}" = "XX" ]; then
		KENKANFLG="ｱ"
	else
		KENKANFLG=" "
	fi
	# サンプリングコード
	SMPCD=`echo -e ${LINE_KNTNO} | cut -d',' -f12-12 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# WSNO(検査グループを元に編集)
	WSNO2=`printf "%s%s" "WS:" "${KNSGRP}"`
	# 依頼書NO
	IRINO=`echo -e ${LINE_KNTNO} | cut -d',' -f15-15 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
	# 自検体の元検体位置情報の取得
	# ２ＩＤの種別(SSSS,VVVV等)
	ID2_PRE=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
	#２ＩＤの下４桁
	ID2_NO=`echo -e ${LINE_KNTNO} | cut -d',' -f13-13 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
	if [ ${#ID2_PRE} -eq 0 ]; then
		FUKSUHNID2="ﾌﾒｲ       "
	elif [ "${ID2_PRE}" = "X" ]; then
		FUKSUHNID2="ｹﾝｶﾝ      "
	elif [ "${ID2_PRE}" = "Y" ]; then
		FUKSUHNID2="ｼﾞｾﾞﾝ     "
	elif [ "${ID2_PRE}" = "_" ]; then
		FUKSUHNID2="          "
	else
		ID2POS=`echo -e ${LINE_KNTNO} | cut -d',' -f14-14 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
		FUKSUHNID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
		FUKSUHNID2=`printf "%1s%06d%-3s" "${ID2_PRE}" "${FUKSUHNID2_TMP}" " "`
	fi
	# 複数本取り検体の元検体位置情報の取得
	YEAR_TMP=`echo ${SRIYMD} | cut -c 1-4`
	MONTH_TMP=`echo ${SRIYMD} | cut -c 5-6`
	DAY_TMP=`echo ${SRIYMD} | cut -c 7-8`
	SRIYMD_TMP=`printf "%-4s%s%-2s%s%-2s" "${YEAR_TMP}" "-" "${MONTH_TMP}" "-" "${DAY_TMP}"`
	fnGetFukusu "${SRIYMD_TMP}" "${IRINO}" "${KNTNO_MOTO}" "${SMPCD}"
	FILE_FUKUSU="TMP_FUKUSU.del"
	FUKSUHNNO=0
	while read LINE_FUKUSU
	do
		ID2_PRE=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c1-1`
		ID2_NO=`echo ${LINE_FUKUSU} | cut -d',' -f1-1 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g" | cut -c5-8`
		if [ ${#ID2_PRE} -eq 0 ]; then
			FUKSUHNID2_TMP="ﾌﾒｲ       "
		elif [ "${ID2_PRE}" = "X" ]; then
			FUKSUHNID2_TMP="ｹﾝｶﾝ      "
		elif [ "${ID2_PRE}" = "Y" ]; then
			FUKSUHNID2_TMP="ｼﾞｾﾞﾝ     "
		elif [ "${ID2_PRE}" = "_" ]; then
			FUKSUHNID2_TMP="          "
		else
			ID2POS=`echo -e ${LINE_FUKUSU} | cut -d',' -f2-2 | sed "s/\"//g" | sed "s/^ *//g" | sed "s/ *$//g"`
			FUKSUHNID2_TMP=`expr \( ${ID2_NO} - 1 \) \* 50 + ${ID2POS}`
			FUKSUHNID2_TMP=`printf "%1s%06d%-3s" "${ID2_PRE}" "${FUKSUHNID2_TMP}" " "`
		fi
		# 複数本取り検体の数をカウントする
		FUKSUHNNO=`expr ${FUKSUHNNO} + 1`
		# 複数本取り検体の元検体位置
		FUKSUHNID2="${FUKSUHNID2}""${FUKSUHNID2_TMP}"
	done < ${FILE_FUKUSU}

	# pot 情報の出力
	printf "%-3s%-8s%-4s%05d%-11s%-2s%-3s%-5s%-2s%-1s%-1s%-1s%-4s%-10s%-1s%-100s\r\n" "${SECCD}" "${SRIYMD}" "${KNSGRP_4}" "${SMPSEQ}" "${KNTNO}" "${CHKMJ}" "${ZRKGOU}" "${BCRTJ}" "${FKJBN}" "${TKTFLG}" "${TSKFLG}" "${KENKANFLG}" "${SMPCD}" "${WSNO2}" "${FUKSUHNNO}" "${FUKSUHNID2}" >> WORK
done < ${FILE_KNTNO}

# potinf.dat 情報の出力
SYSDATE=`date '+%y%m%d%H%M%S'`
WSNO1=`printf "(WS:%s)" "${KNSGRP_4}"`
# 検査工程区分によって、ファイル名に使用するフラグを決定
if  [ ${KSKTKBN} = "N" ]; then
	MODEFLG="1"
elif [ ${KSKTKBN} = "K" -o  ${KSKTKBN} = "T" -o ${KSKTKBN} = "R" ]; then
	MODEFLG="2"
elif [ ${KSKTKBN} = "S" ]; then
	MODEFLG="3"
elif [ ${KSKTKBN} = "M" ]; then
	MODEFLG="4"
fi
POTFILENAME=`printf "%s.%s00" "${TRID}" "${MODEFLG}"`

# potinf.dat のバックアップを取った後に、新しい情報を追記する。
cp -p ${OUTPUTDIR}potinf.dat ${OUTPUTDIR}${SYSDATE}potinf.dat
printf "%-12s%-8s%-42s%-24s\r\n" "${SYSDATE}" "${TRID}" "${WSNO1}" "${POTFILENAME}" >> ${OUTPUTDIR}potinf.dat

mv WORK ${OUTPUTDIR}${POTFILENAME}

exit 0
