#!/bin/sh
#######################################################################
# 日次処理(日付間違いリカバリー用)
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

# 現時点のDIR
CURDIR=`pwd`

# バックアップディレクトリ
BUPDIR=/apdata/oldday

# エラーログ出力先
ERR_LOG_DIR="/apdata/aplog"

# エラーログのプレフィック
NAME_ERRLOG="FATAL_"

echo ""
echo "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                    日次処理を開始します                    ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"
while [ 1 ]
do
    echo ""
    echo "◎◎◎ライン側の日次処理は済んでいますか？◎◎◎"
    echo "★★★　各端末の画面は終了していますか？　★★★"
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

#-------------------------------------------------------------
# 現システム管理マスタ基準処理日の取得
#-------------------------------------------------------------
db2 "select kjnsriymd from sysknrmst for read only" | grep ^2 > $$
KJNSRIYMD=`cat $$`
rm $$

LOGFILE=$BUPDIR/daily.log_$KJNSRIYMD
echo "`date +"%Y/%m/%d %H:%M:%S"`▼▼ 日次処理 --- 開始 ▼▼" | tee -a $LOGFILE
echo ""

#######################################################################
# No.2 受付日入力
#######################################################################
ymd=`date +%Y%m%d`
while [ 1 ]
do
	echo "受付日を入力してください($ymd) :"
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
	utkymd=$yy-$mm-$dd

	echo "受付日は[$utkymd]でよろしいですか(y/n)" | tee -a $LOGFILE
	read ans
	if [ "$ans" ]
	then
		if [ $ans = "y" ]
		then
			break
		fi
	fi
done

#######################################################################
# No.3 常駐プロセスの停止
#######################################################################

startMsg "常駐プロセスの停止" $LOGFILE

# 運用フラグON
sh $SHDIR/upd_sysknrmst_uny.sh 1 $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
	errMsg
fi

# LD103,LD106 は運用フラグ ON になれば自動で落ちるので待つ。(ロックファイルの存在確認)
while [ 1 ]
do
	LOCK_FILE_NUM=`ls -U1 ~/bin/lock/*lock 2>/dev/null | wc -l`
	if [ ${LOCK_FILE_NUM} = "0" ] ; then
 		 break
	fi
	sleep 10
done

# プロセス終了
sh $SHDIR/prc_onoff.sh -STOP >> $LOGFILE

# IA側プロセス 日次前稼動O/L号機の確認
# 	IA_STT_FILE=./IA_STS.txt
sh $SHDIR/prcIA_stat.sh  >> $LOGFILE
sleep 3

# IA側プロセス終了
sh $SHDIR/prcIA_onoff.sh -STOP >> $LOGFILE
sleep 10
# IA側プロセス kill (rsh)
sh $SHDIR/rsh_kill_prcIA.sh	 >> $LOGFILE

# ＺＳ用プロセス終了
sh $SHDIR/prcZS_onoff.sh -STOP >> $LOGFILE
sleep 10

endMsg "常駐プロセスの停止" $LOGFILE

#######################################################################
# No.10 日付の更新
#######################################################################

startMsg "日付の更新" $LOGFILE

# システム管理マスタ 基準処理年月日の設定
sh $SHDIR/upd_sysknrmst.sh $utkymd $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi


# 検査SEQ採番管理テーブルの初期化
sh $SHDIR/upd_knsseqknri.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "日付の更新" $LOGFILE

#######################################################################
# No.11 Delファイルの作成
#######################################################################

startMsg "Delファイルの作成" $LOGFILE

# 出力先ディレクトリ
outdir="/apdata/today/file/KEA00/kea00ap/master"

cd $outdir

sh $SHDIR/mk_delfile.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 出力先ディレクトリ(ZS用)
outdirZS="/apdata/today/file/KEA00/kea00ap/ZS050/mst_file"

cd $outdirZS

sh $SHDIR/mk_delfile_ZS.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "Delファイルの作成" $LOGFILE

#######################################################################
# No.12 常駐プロセスの起動
#######################################################################

startMsg "常駐プロセスの起動" $LOGFILE

# CHANGE DIRECTRY 
cd $CURDIR

# プロセス起動
sh $SHDIR/prc_onoff.sh -START > /dev/null

#  IA側プロセス起動
sh $SHDIR/prcIA_onoff.sh -START >> $LOGFILE

#  ＺＳ用プロセス起動
sh $SHDIR/prcZS_onoff.sh -START > /dev/null

# 運用フラグOFF
sh $SHDIR/upd_sysknrmst_uny.sh 0 $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "常駐プロセスの起動" $LOGFILE
echo " "
echo "----------------------------------------------------"
echo "★★★★★　オンラインが可能になりました　★★★★★"
echo "----------------------------------------------------"
echo " "

#	緊急使用中のため起動しない号機の表示
#	/tmp/IA_KNQ.txt
if [ -s /tmp/IA_KNQ.txt ]
then
	echo " "
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"
	echo " "
	cat /tmp/IA_KNQ.txt
	echo " "
	echo "WARNING ! WARNING ! WARNING ! WARNING ! WARNING ! WARNING"
	echo " "
	echo " "
	cat /tmp/IA_KNQ.txt >> $LOGFILE
	rm /tmp/IA_KNQ.txt
fi

#######################################################################
# No.18 終了処理
#######################################################################

db2 terminate > /dev/null
cd $CURDIR
echo ""
echo "`date +"%Y/%m/%d %H:%M:%S"`▲▲ 日次処理 --- 終了 ▲▲" | tee -a $LOGFILE
echo ""
echo ""
echo "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                    日次処理が終了しました                  ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"
echo "ＥＮＴＥＲキーを押してください"
read ans
exit 0

