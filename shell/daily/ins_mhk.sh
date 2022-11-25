
#######################################################################
#  未報告分KEYデータINSERT
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
# ---------------------------------------------------------------------
# UPD 2006-09-01 S.Ueda
#     依頼情報抽出の条件にオーダ作成フラグ＜＞空白を追加
#       未報告分に未着分を含めないようにするため
# add 2007-06-08 INTEC
#		緊急対応：緊急分は無条件に累積に移行するため対象外とする
#		irikbn <> 'K' を追加
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"ins_mhk.log"
    exit 1
fi

echo "[`date`][DAY_MHKKEY] insert start ----->"

db2 "import from /dev/null of del replace into day_mhkkey"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : 未報告分KEYデータの削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"ins_mhk.log"
	exit 1
fi

db2 "\
insert into day_mhkkey \
select	distinct utkymd, irino, current timestamp \
from \
( \
select  utkymd , irino , kmkcd \
from    irai \
where   irihsmkbn <>'2' \
and		sjflg='0' \
and		odrssflg <> ' ' \
and		irikbn <> 'K' \
EXCEPT \
select  distinct utkymd , irino , kmkcd \
from    kekka \
where   irihsmkbn <>'2' \
and     kkajkcd='3' \
and     knsflg='E' \
and		irikbn <> 'K' \
) daily "
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : 未報告分KEYデータのInsertに失敗しました" >> $LOG_DIR/$NAME_ERRLOG"ins_mhk.log"
    exit 1
fi

db2 terminate

exit 0
