#!/bin/sh
#######################################################################
# 日次処理
# $1 : ユーザID(DB2)
# $2 : パスワード(DB2)
#######################################################################

if [ $# -lt 2 ]
then
	echo "引数を指定して下さい"
	echo "sh daily.sh   ユーザID(DB2)   パスワード(DB2)"
	exit 0
fi

DB=kea00db
USER=$1
PASS=$2

#-------------------------------------------------------------
#	MSG FUNCTION DEFINE
#-------------------------------------------------------------
startMsg() {
	echo "  `date +"%Y/%m/%d %H:%M:%S"`▼▼ $1 --- 開始 ▼▼" | tee -a $2
}

endMsg() {
	echo "  `date +"%Y/%m/%d %H:%M:%S"`▲▲ $1 --- 終了 ▲▲" | tee -a $2
}

errMsg() {
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"
	echo " "
	echo " エラーが発生しました。システム担当者に連絡してください。 "
	echo " "
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"

	while [ 1 ]
	do
		sleep 1 
	done
}

echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
echo ""
#######################################################################
# No.1	初期処理
#######################################################################

#-------------------------------------------------------------
#	作業ディレクトリ
#-------------------------------------------------------------
# SHELL DIR
SHDIR=$HOME/shell/daily

# バックアップディレクトリ
BUPDIR=/apdata/oldday

# エラーログ出力先
ERR_LOG_DIR="/apdata/aplog"

# エラーログのプレフィック
NAME_ERRLOG="FATAL_"

while [ 1 ]
do
    echo ""
    echo "○imp_rui_work.sh を用いて累積ＤＢへのインポートをやり直します。"
    echo ""
	echo "よろしいですか？(y/n)==>"
	read ans
	if [ "$ans" ]
	then
		if [ $ans = "y" ]
		then
			break
		else
			exit 0
		fi
	fi
done

#-------------------------------------------------------------
# DB2 CONNECT
#-------------------------------------------------------------
db2 connect to $DB user $USER using $PASS > /dev/null
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $ERR_LOG_DIR/$NAME_ERRLOG"daily.log"
    errMsg
fi

cd $BUPDIR

#######################################################################
# No.2 再処理日の入力
#######################################################################
ymd=`date +%Y%m%d --date '1 days ago'`
while [ 1 ]
do
	echo "やり直しを行う元処理日を入力してください($ymd) :"
	read ans
	if [ "$ans" ]
	then
		$SHDIR/checkdate.csh $ans
		if [ $? -ne 0 ]
		then
			echo "日付のフォーマットが異なります(YYYYMMDD)"
			echo ""
			continue
		else
			ymd=$ans
		fi
	fi

	yy=`echo $ymd | cut -c1-4`
	mm=`echo $ymd | cut -c5-6`
	dd=`echo $ymd | cut -c7-8`
	KJNSRIYMD=$yy-$mm-$dd

	# ファイルバックアップ先
	FBUDIR=$BUPDIR/$KJNSRIYMD
	if [ ! -d ${FBUDIR} ]; then
		echo "該当日の日次ディレクトリが存在しません(${FBUDIR})"
		echo ""
		continue
	fi

	echo "処理日[$KJNSRIYMD]分の累積インポートをやり直します。よろしいですか(y/n)"
	read ans
	if [ "$ans" ]
	then
		if [ $ans = "y" ]
		then
			break
		fi
	fi
done

LOGFILE=$FBUDIR/daily.log

echo "-----------------------------------------------------------------" >> $LOGFILE
startMsg "累積インポートリカバリー処理" $LOGFILE
echo "-----------------------------------------------------------------" >> $LOGFILE

#######################################################################
# No.14 累積テーブルにデータ追加・累積テーブルから未報告分データ削除
#######################################################################

startMsg "累積に追加＆累積から未報告分削除" $LOGFILE

cd $FBUDIR
# 累積 IMPORT (ixf)
sh $SHDIR/imp_rui.sh $DB $USER $PASS >> $LOGFILE

# 集計 IMPORT (ixf)
sh $SHDIR/imp_shu.sh KEA00DBN $USER $PASS >> $LOGFILE

# 未報告分データの累積、集計テーブルからの削除(IA)
sh $SHDIR/exp_DAY_MHKKEY.sh $DB $USER $PASS $FBUDIR >> $LOGFILE
sh $SHDIR/del_mhk_dbn.sh KEA00DBN $USER $PASS $FBUDIR >> $LOGFILE

endMsg "累積に追加＆累積から未報告分削除" $LOGFILE

#######################################################################
# No.15 EXPORTファイル(ixf, msg)圧縮＆結果out圧縮・削除
# 		  EXPORT FILE COMPRESS
#######################################################################

startMsg "EXPORTファイル(ixf, msg)圧縮＆結果out圧縮・削除" $LOGFILE

echo "[`date`][*.ixf] gzip start ----->" >> $LOGFILE
gzip *.ixf >> $LOGFILE

echo "[`date`][*.msg] gzip start ----->" >> $LOGFILE
gzip *.msg >> $LOGFILE

echo "[`date`][*.dat] gzip start ----->" >> $LOGFILE
gzip *.dat >> $LOGFILE

echo "[`date`][*.trg] gzip start ----->" >> $LOGFILE
gzip *.trg >> $LOGFILE

echo "[`date`][*.del] gzip start ----->" >> $LOGFILE
gzip *.del >> $LOGFILE

echo "[`date`][kekka_out] tar cvfz start ----->" >> $LOGFILE
sh $SHDIR/kekkaout_del.sh $FBUDIR

endMsg "EXPORTファイル(ixf, msg)圧縮＆結果out圧縮・削除" $LOGFILE
echo ""
echo "`date +"%Y/%m/%d %H:%M:%S"`▲▲ 日次処理 --- 終了 ▲▲" | tee -a $LOGFILE
echo ""
echo ""
exit 0
