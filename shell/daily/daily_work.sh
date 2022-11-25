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
echo "■                    日次処理を再開します                    ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"

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
# No.2 受付日入力
#######################################################################

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
if [ $? -gt 0 ]; then
	echo `date`" ERROR : 基準処理日の取得に 失敗しました" >> $ERR_LOG_DIR/$NAME_ERRLOG"daily.log"
    errMsg
fi

KJNSRIYMD=`cat $$`
rm $$

#-------------------------------------------------------------
# 本日のバックアップディレクトリの作成
#-------------------------------------------------------------
# EXPORT 出力先
EXPDIR=$BUPDIR/$KJNSRIYMD

cd $BUPDIR
mkdir $KJNSRIYMD

# 既にディレクトリが存在する場合は既存を日時付き名にmvする
if [ $? -gt 0 ]; then
    NDIR=`date +"%Y%m%d%H%M%S"`
    echo "既存ディレクトリ[$KJNSRIYMD]を[${KJNSRIYMD}_$NDIR]に移動"
    mv $KJNSRIYMD ${KJNSRIYMD}_$NDIR
	mkdir $KJNSRIYMD
fi

LOGFILE=$BUPDIR/$KJNSRIYMD/daily.log
echo "`date +"%Y/%m/%d %H:%M:%S"`▼▼ 日次処理 --- 開始 ▼▼" | tee -a $LOGFILE
echo ""

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

# IAでの削除処理がオンライン起動までに間にあうようにするため処理順を変更
# IA 上 ( socket 経由でIA上のshellを起動.backup->dell）
sh $SHDIR/rsh_back_del.sh &

endMsg "常駐プロセスの停止" $LOGFILE

#######################################################################
# No.4 集計テーブルの作成
#######################################################################

startMsg "集計テーブルの作成" $LOGFILE

# バックアップディレクトリへの移動
cd $EXPDIR

# SHU_KEKKA
sh $SHDIR/exp_shu.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 項目別テスト数集計
sh $SHDIR/js111.sh $KJNSRIYMD $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 履歴データ蓄積
sh $SHDIR/cnv_rireki.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 地方検査分　履歴情報取得(ＦＴＰ)
sh $SHDIR/get_rireki_ftp.sh $EXPDIR >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 地方検査分　履歴情報コンバート用マスタファイルの取得
sh $SHDIR/exp_tmp_mst.sh $DB $USER $PASS $KJNSRIYMD >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 地方検査分　履歴情報コンバート
$SHDIR/RirekiConv $EXPDIR >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 地方検査分　履歴情報インサート
sh $SHDIR/imp_rireki_other.sh $DB $USER $PASS $EXPDIR >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# ＡＣＥコントロール計算結果作成 インサート
# 失敗しても、後日リカバリ可能なのでエラーが発生しても停止しない。
sh $SHDIR/imp_ctrl_074.sh $DB $USER $PASS >> $LOGFILE

endMsg "集計テーブルの作成" $LOGFILE

#######################################################################
# No.5 データベースのバックアップ→圧縮
#######################################################################

startMsg "データのバックアップ" $LOGFILE

# コントロール結果のみ日次でRUNSTATSをかけて、業務中はかけないように変更する。
db2 "RUNSTATS ON TABLE DB2INST1.CTRLKKA WITH DISTRIBUTION and detailed indexes all" >> $LOGFILE

# バックアップディレクトリへの移動
cd $EXPDIR

# データ(累計、集計以外）バックアップ 全件 IXF FORMAT
sh $SHDIR/exp_all.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 未報告分KEYテーブルINSERT
sh $SHDIR/ins_mhk.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# 未報告分バックアップ IXF FORMAT
sh $SHDIR/exp_mhk.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "データのバックアップ" $LOGFILE

#######################################################################
# No.6 テーブルデータの削除
#######################################################################

startMsg "テーブルデータの削除" $LOGFILE

# 検査進行状況表の退避
sh $SHDIR/exp_KNSSNKJYK.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

sh $SHDIR/delKea00_dat.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

endMsg "テーブルデータの削除" $LOGFILE

#######################################################################
# No.7 未報告データの戻し
#######################################################################

startMsg "未報告データの戻し" $LOGFILE

sh $SHDIR/imp_mhk.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

echo "[`date`][*.mhk] gzip start ----->" >> $LOGFILE
gzip *.mhk >> $LOGFILE

endMsg "未報告データの戻し" $LOGFILE

#######################################################################
# No.8 ファイルのバックアップ
#######################################################################

startMsg "ファイルのバックアップ" $LOGFILE

# Z 上
#sh $SHDIR/data_back.sh $EXPDIR >> $LOGFILE
echo "[`date`][data_back] start ----->" >> $LOGFILE
sh $SHDIR/data_back.sh $EXPDIR

endMsg "ファイルのバックアップ" $LOGFILE

#######################################################################
# No.9 ファイルの削除
#######################################################################

startMsg "ファイルの削除" $LOGFILE

# Z 上
sh $SHDIR/data_del.sh >> $LOGFILE

endMsg "ファイルの削除" $LOGFILE

#######################################################################
# No.10 日付の更新
#######################################################################

startMsg "日付の更新" $LOGFILE

# 検査SEQ採番管理テーブルの緊急分の削除
sh $SHDIR/del_knq_knsseqknri.sh $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# システム管理マスタ 基準処理年月日の設定
sh $SHDIR/upd_sysknrmst.sh $utkymd $DB $USER $PASS >> $LOGFILE
if [ $? -gt 0 ]; then
    errMsg
fi

# アッセイスケジュールマスタ存在チェック
# このマスタ使用していないためコメント
# sh $SHDIR/chk_asyscdlmst.sh $DB $USER $PASS >> $LOGFILE

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
#		!!PG内のprintfが延々出力されるためやむなく/dev/nullを指定!!
##sh $SHDIR/prc_onoff.sh -START >> $LOGFILE
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
# No.13 履歴の保存期間(400日)より前のデータ削除
#######################################################################

startMsg "履歴の保存期間(400日)より前のデータ削除" $LOGFILE

# CHANGE DIRECTRY 
cd $EXPDIR

# 履歴削除用シェル
sh $SHDIR/del_rireki.sh $DB $USER $PASS >> $LOGFILE

endMsg "履歴の保存期間(400日)より前のデータ削除" $LOGFILE

#######################################################################
# No.14 累積テーブルにデータ追加・累積テーブルから未報告分データ削除
#######################################################################

startMsg "累積に追加＆累積から未報告分削除" $LOGFILE

# 累積 IMPORT (ixf)
sh $SHDIR/imp_rui.sh $DB $USER $PASS >> $LOGFILE

# 集計 IMPORT (ixf)
sh $SHDIR/imp_shu.sh KEA00DBN $USER $PASS >> $LOGFILE

# 未報告分データの累積、集計テーブルからの削除(IA)
sh $SHDIR/exp_DAY_MHKKEY.sh $DB $USER $PASS $EXPDIR >> $LOGFILE
sh $SHDIR/del_mhk_dbn.sh KEA00DBN $USER $PASS $EXPDIR >> $LOGFILE

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

# ログを出力しないように修正
#sh $SHDIR/kekkaout_del.sh $EXPDIR >> $LOGFILE
echo "[`date`][kekka_out] tar cvfz start ----->" >> $LOGFILE
sh $SHDIR/kekkaout_del.sh $EXPDIR > /dev/null

endMsg "EXPORTファイル(ixf, msg)圧縮＆結果out圧縮・削除" $LOGFILE

#######################################################################
# No.16 以降の処理は翌日に持ち越しても問題ないため削除
#######################################################################


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
echo "■           日次処理のリカバリーが終了しました               ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■                                                            ■"
echo "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"
echo "ＥＮＴＥＲキーを押してください"
read ans
exit 0

