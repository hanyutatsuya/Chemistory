#! /bin/sh
############################################################
# 項目別テスト数集計
# $1 : 基準処理日
# $2 : DB名
# $3 : ユーザID(DB2)
# $4 : パスワード(DB2)
############################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

YMD=$1

db2 CONNECT TO $2 USER $3 USING $4
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"js111.log"
    exit 1
fi

echo "[`date`][KMKBTUTEST] insert start ----->"

db2 "
INSERT INTO KMKBTUTEST \
SELECT	 \
	'$YMD' \
	, MST.KNSGRP   \
	, MST.KMKCD   \
	, COALESCE(ZEN.ZENCNT, 0) AS IRIALLSU   \
	, COALESCE(IRI.IRICNT, 0) AS IRIJSNSU   \
	, COALESCE(KNS.KNSCNT, 0) AS KENSASU   \
	, 0 AS STADSU   \
	, COALESCE(CTL.CTLCNT, 0) AS CTRLSU   \
	, COALESCE(TST.TSTCNT, 0) AS TESTSU   \
	, COALESCE(SVY.SVYCNT, 0) AS SAVYSU   \
	, COALESCE(CRY.CRYCNT, 0) AS KBRTSU   \
	, COALESCE(KST.KSTCNT, 0) AS KSTATSU   \
	, CURRENT TIMESTAMP \
FROM  \
	(  SELECT *  \
		FROM  \
			(  SELECT	KGM.SECCD \
						, KGM.KNSGRP \
						, KMM.KMKCD \
						, KGM.KNSGRPRS \
						, KGM.KNSHOKBN \
						, KMM.KMKRSJ \
						, KMM.HYJIJN   \
				FROM	KNSGMST KGM   \
						, KMKMST KMM   \
				WHERE	KMM.FKBNKKB <> '1'  \
				AND		KMM.FKBNKKB <> '3'  \
				AND		KGM.KNSGRP = KMM.KNSGRP  \
				AND		KGM.KAIYMD <= '$YMD'  \
				AND	 	KGM.HAIYMD >= '$YMD'  \
				AND		KMM.KAIYMD <= '$YMD'  \
				AND		KMM.HAIYMD >= '$YMD' \
			) ORG   \
		WHERE	1=1 ) MST  \
		LEFT OUTER JOIN  \
			(   SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS ZENCNT   \
				FROM	IRAI   \
				WHERE	SJFLG = '0'   \
				GROUP BY KNSGRP,KMKCD  \
			) ZEN  \
			ON	MST.KNSGRP = ZEN.KNSGRP  \
			AND	MST.KMKCD = ZEN.KMKCD  \
		LEFT OUTER JOIN  \
			(   SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS IRICNT   \
				FROM	IRAI   \
				WHERE	SJFLG = '0'     \
				AND		(IRIHSMKBN = '0' OR IRIHSMKBN = '1')   \
				GROUP BY KNSGRP,KMKCD  \
			) IRI  \
			ON	MST.KNSGRP = IRI.KNSGRP  \
			AND MST.KMKCD  = IRI.KMKCD  \
		LEFT OUTER JOIN  \
			(   SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS KNSCNT   \
				FROM	KEKKA   \
				WHERE 	(IRIKBN = 'A' OR IRIKBN = 'K')     \
				AND		BSKKBN <> ''  \
				AND		KNSKISYMD='$YMD'   \
				GROUP BY KNSGRP, KMKCD  \
			) KNS  \
			ON	MST.KNSGRP	= KNS.KNSGRP  \
			AND MST.KMKCD	= KNS.KMKCD  \
		LEFT OUTER JOIN  \
			(	SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS CRYCNT   \
				FROM	KEKKA   \
				WHERE	IRIKBN = 'Y'  \
				AND		KNSKISYMD='$YMD'   \
				GROUP BY KNSGRP,KMKCD  \
			) CRY  \
			ON	MST.KNSGRP = CRY.KNSGRP  \
			AND MST.KMKCD = CRY.KMKCD  \
		LEFT OUTER JOIN  \
			(   SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS KSTCNT   \
				FROM	KEKKA   \
				WHERE	IRIKBN = 'Z'  \
				AND		BSKKBN <> ''  \
				AND		KNSKISYMD='$YMD'  \
				GROUP BY KNSGRP,KMKCD  \
			) KST  \
			ON	MST.KNSGRP = KST.KNSGRP  \
			AND MST.KMKCD = KST.KMKCD  \
		LEFT OUTER JOIN  \
			(   SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS CTLCNT   \
				FROM	CTRLKKA   \
				WHERE	1 = 1  \
				AND		KNSKISYMD='$YMD'   \
				GROUP BY KNSGRP,KMKCD  \
			) CTL  \
			ON MST.KNSGRP = CTL.KNSGRP  \
			AND MST.KMKCD = CTL.KMKCD  \
		LEFT OUTER JOIN  \
			(   SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS TSTCNT   \
				FROM	KEKKA   \
				WHERE	IRIKBN = 'T'  \
				AND		BSKKBN <> ''  \
				AND		KNSKISYMD='$YMD'   \
				GROUP BY KNSGRP, KMKCD \
			 ) TST  \
			ON	MST.KNSGRP = TST.KNSGRP  \
			AND MST.KMKCD = TST.KMKCD  \
		LEFT OUTER JOIN  \
			(  SELECT	KNSGRP \
						, KMKCD \
						, COUNT(*) AS SVYCNT   \
				FROM	KEKKA   \
				WHERE	IRIKBN = 'S'  \
				AND		BSKKBN <> ''  \
				AND		KNSKISYMD='$YMD'   \
				GROUP BY KNSGRP,KMKCD  \
			) SVY  \
			ON	MST.KNSGRP = SVY.KNSGRP  \
			AND MST.KMKCD = SVY.KMKCD  \
"
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : KMKBTUTEST のInsertに失敗しました" >> $LOG_DIR/$NAME_ERRLOG"js111.log"
    exit 1
fi

db2 terminate

exit 0
