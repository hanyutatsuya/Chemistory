#!/bin/sh
#######################################################################
#  集計テーブル対象データをexportする
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"exp_shu.log"
	exit 1
fi

echo "[`date`][SHU_KEKKA.ixf] export start ----->"

db2 "export to SHU_KEKKA.ixf of ixf messages SHU_KEKKA.msg \
select  kek.KNSKISYMD , \
	kek.SRIYMD  , \
	kek.KNTNO  , \
	kek.KNSGRP , \
	kek.KMKCD  , \
	kek.KNSSU  , \
	kek.KNSSUEDA  , \
	kek.IRIHSMKBN  , \
	kek.IRIKBN  , \
	kek.KSKTKBN  , \
	kek.UTKYMD  , \
	kek.IRINO  , \
	kek.ZSSDINO  , \
	kek.SSTCD  , \
	kek.OYAKMKCD  , \
	kek.SECCD  , \
	kek.BKFKKBN  , \
	kek.BSKKBN  , \
	kek.BSKLNE  , \
	kek.BSKGOK  , \
	kek.BSKSEQ  , \
	kek.NBKMKCD  , \
	kek.TSTRFLG  , \
	kek.ZRCD  , \
	kek.KJNO  , \
	kek.SKFLG  , \
	kek.KNSKKA1  , \
	kek.KNSKKA2  , \
	kek.KNSKKA2KBN  , \
	kek.IJKBNM  , \
	kek.IJKBNF  , \
	kek.IJKBNN  , \
	kek.CTRLNO  , \
	kek.KNSKRDH  , \
	kek.HKKDH  , \
	kek.TNYRKFLG  , \
	kek.SIYFLG  , \
	kek.KNSFLG  , \
	kek.KSNDH  , \
	COALESCE(kan.SBTKBN, '9') AS SBTKBN , \
	CURRENT TIMESTAMP    \
from KEKKA kek LEFT OUTER JOIN KANJYA kan \
	ON kek.UTKYMD = kan.UTKYMD \
	AND kek.IRINO = kan.IRINO \
	AND kek.ZSSDINO = kan.ZSSDINO \
for read only"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : 集計結果の取得に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"exp_shu.log"
	exit 1
fi

db2 terminate

exit 0
