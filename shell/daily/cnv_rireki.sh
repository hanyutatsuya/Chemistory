#!/bin/sh

#------------------------------------------------
# 履歴テーブル作成・更新
# ---------------------------------
# v1.0		2007.01.29	Wajima
#------------------------------------------------

fnExport() {
	db2 connect to $1 user $2 using $3
	ret=$?

	if [ $ret -ne 0 ]
	then
        echo `date`" ERROR : DB接続失敗($1,$2,$3,$ret)" >> $LOG_DIR/$NAME_ERRLOG$ME.log
		return $ret
	fi

#kka.JISKSBR -> KSBR,
#kka.NBDOLBL -> NBDO,
#kka.YKDOLBL -> YKDO,
	db2 "export to $WORK_DIR/TOU_RIREKI.ixf of ixf messages $ME.export.msg \
	select \
		kka.UTKYMD, \
		kka.IRINO, \
		kka.IRIKETFLG, \
		kka.ZSSDINO, \
		kka.KNSGRP, \
		kka.KMKCD, \
		kka.SSTCD, \
		kja.KRTNO, \
		kja.KNJNMKEY, \
		kja.SBTKBN, \
		kja.AGE, \
		kja.AGEKBN, \
		kka.BSKKBN, \
		kka.BSKLNE, \
		kka.BSKGOK, \
		kka.RAWDATA, \
		kka.HJKKA, \
		kka.KKACMT1, \
		kka.KKACMT2, \
		kka.IJKBNM, \
		kka.IJKBNF, \
		kka.IJKBNN, \
		kka.TBIJKBNM, \
		kka.TBIJKBNF, \
		kka.TBIJKBNN, \
		kka.JISKSBR, \
		kka.NBDOLBL, \
		kka.YKDOLBL, \
		kka.HKKDH, \
		kka.KSNDH, \
		kja.OYASSTCD \
	from  KMKMST kmk, KEKKA kka, KANJYA kja \
	where kmk.RRKHZN > 0 \
	and   kka.KNSFLG = 'E' \
	and   kmk.KMKCD=kka.KMKCD \
	and   kmk.KNSGRP=kka.KNSGRP \
and kja.UTKYMD=kka.UTKYMD \
and kja.IRINO=kka.IRINO \
and kja.ZSSDINO=kka.ZSSDINO \
and   ((kka.SKFLG <> '1'  and   kja.KNJNMKEY <> '') \
  or   ((kka.SKFLG = '1'  and   kja.KNJNMKEY <> '') and  kja.KRTNO <> '' )) for read only"
	ret=$?

	if [ $ret -ne 0 ]
	then
		db2 terminate
		return $ret
	fi

	db2 terminate

	return 0
}

fnImport() {
	db2 connect to $1 user $2 using $3
	ret=$?

	if [ $ret -ne 0 ]
	then
		return $ret
	fi

	db2 "import from $WORK_DIR/TOU_RIREKI.ixf of ixf commitcount 10000 messages $ME.import.msg insert_update into rireki"
	ret=$?

	if [ $ret -ne 0 ]
	then
		db2 terminate
		return $ret
	fi

	db2 terminate

	return 0
}

#------------------------------------------------
# main()
#   input : DBNAME
#           id(DB)
#           password(DB)
#------------------------------------------------

ME=`basename $0`
##WORK_DIR="/home/kea00sys/work/wajima/work"
##LOG_DIR="/home/kea00sys/work/wajima/work"
WORK_DIR=`pwd`
#LOG_DIR=`pwd`
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

DEF_DB="KEA00DB2" #TEST DB
DEF_ID="db2inst1" #TEST ID
DEF_PW="db2inst1" #TEST Password
USE_DB=""
USE_ID=""
USE_PW=""
sem=""

DEBUG=0 # 1: DEBUG MODE

# 排他制御
sem="/tmp/`basename $0`"
ln -s /$sem.lock $sem || exit
trap "rm $sem; db2 terminate; exit 0" 2 3 15

echo "$ME : 起動"`date`
echo "### WORK_DIR [$WORK_DIR]  LOG_DIR [$LOG_DIR]##"

# オプション数チェック
# ---------------------------------
if [ $# -lt 3 ]
then
	if [ $DEBUG -eq 1 ]
	then
		USE_DB=$DEF_DB
		USE_ID=$DEF_ID
		USE_PW=$DEF_PW
	else
        echo "$ME : 引数を指定して下さい"
        echo "sh $ME DB接続先   ユーザID(DB2)   パスワード(DB2)"
		rm $sem
        exit 0
	fi
else
	USE_DB=$1
	USE_ID=$2
	USE_PW=$3
fi

# 作業DIRチェック
# ---------------------------------
if [ -d $WORK_DIR ]
then
	if [ -w $WORK_DIR ]
	then
		# EXPORT実行
		fnExport $USE_DB $USE_ID $USE_PW
		if [ $? -ne 0 ]
		then
       		echo `date`" ERROR : EXPORTに失敗しました" >> $LOG_DIR/$NAME_ERRLOG$ME.log
			rm "$sem"
			exit 1
		else
			# IMPORT実行
			fnImport $USE_DB $USE_ID $USE_PW
			if [ $? -ne 0 ]
			then
       			echo `date`" ERROR : IMPORTに失敗しました" >> $LOG_DIR/$NAME_ERRLOG$ME.log
				rm "$sem"
				exit 1
			fi
		fi
	else
       	echo `date`" ERROR : 設定されている作業領域が書込み不可です" >> $LOG_DIR/$NAME_ERRLOG$ME.log
		rm "$sem"
		exit 1
	fi
else
    echo `date`" ERROR : 設定されている作業領域が不正です" >> $LOG_DIR/$NAME_ERRLOG$ME.log
	rm "$sem"	
	exit 1
fi

# 排他制御(後始末)
rm "$sem"

## daily.log に表示するため、リダイレクションを外す
##echo "$ME : 終了 "`date` >> $LOG_DIR/$ME.log
echo "$ME : 終了 "`date`

exit 0
