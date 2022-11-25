#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#######################################################################
#
# chk_HKHRIRAI.sh 報告保留テーブル 検査グループ更新シェル
#
# 2020-09-10 Create H.Sekiya
#
# 依頼END 受信時に属性チェックを行い HKHRIRAI へ INSERT しているが、
# その後に、複数本取りの別の分注情報がきて、IRAI の KNSGRP が更新され、 
# IRAI と HKHRIRAI の KNSGRP に食い違いが発生する場合がある。
# 本来なら分注展開時に IRAI と同時に HKHRIRAI も更新するようにすべきだが、
# 分注展開の変更は時間がかかるため、このシェルで HKHRIRAI の KNSGRP を更新する。
# このシェルの実行タイミングは分注END 受信後に一回起動すればよい。
#
#######################################################################
# 実行ログファイル
TMP_FILE="/tmp/chk_HKHRIRAI"
LOCK_FILE="/apdata/aplog/chk_HKHRIRAI.lock"

# DB接続情報
DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"

# フラグ
FLG="10"      # システム管理マスタのフラグ状況。運用フラグ(１桁目)+分注ENDフラグ(２桁目)

# 処理済みファイルの存在確認。(ファイルが存在する場合、チェックをしない。)
if [ -e ${LOCK_FILE} ]; then
	exit 0
fi

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS} > /dev/null

# 日次中もしくは、分注ＥＮＤが来ていない時は処理をしない。
db2 -x "SELECT UNYFLG,BCHENDFLG FROM SYSKNRMST FOR READ ONLY" | grep ^[0-9] | sed 's/ //g' > ${TMP_FILE}
FLG=`cat ${TMP_FILE}`
rm ${TMP_FILE}
if [ ${FLG} != "01" ]; then
	db2 terminate > /dev/null
	exit 0
fi

dateStr=`date '+%F %T%t'`
echo "$dateStr : 処理を開始しました。"

db2 "
SELECT
	HKHRIRAI.UTKYMD,
	HKHRIRAI.IRINO ,
	HKHRIRAI.KMKCD ,
	HKHRIRAI.KNSGRP HKHR_KNSGRP,
	IRAI.KNSGRP IRI_KNSGRP
FROM
	HKHRIRAI,
	IRAI
WHERE
	HKHRIRAI.UTKYMD = IRAI.UTKYMD AND
	HKHRIRAI.IRINO = IRAI.IRINO AND
	HKHRIRAI.KMKCD = IRAI.KMKCD AND
	HKHRIRAI.KNSGRP <> IRAI.KNSGRP
"

db2 "
UPDATE
	HKHRIRAI
SET
	HKHRIRAI.KNSGRP = IRAI.KNSGRP
FROM
	IRAI
WHERE
	HKHRIRAI.UTKYMD = IRAI.UTKYMD AND
	HKHRIRAI.IRINO = IRAI.IRINO AND
	HKHRIRAI.KMKCD = IRAI.KMKCD AND
	HKHRIRAI.KNSGRP <> IRAI.KNSGRP
"
# 戻り値が、正常終了 0 、対象なし 1 以外の場合、エラーとする。
if [ $? -gt 1 ]; then
	db2 terminate > /dev/null
	exit 1
fi

touch ${LOCK_FILE}
	
db2 terminate > /dev/null

dateStr=`date '+%F %T%t'`
echo "$dateStr : 処理が終了しました。"
echo ""

exit 0
