#!/bin/bash
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#*****************************************************************
#   ＢＭＬ様向け検査システム
#
#   システム名：次世代システム
#   ファイル名：sun_bun_rec.sh
#	概      要：緊急対応  SUN分注結果受信ファイルの振り分け
#
#*****************************************************************
#	No.Ver.    日付           名前          コメント
#---------------------------------------------------------------*
#	H000	2007.06.18	INTEC.INC	CREATE
#*****************************************************************

#-------------------------------------------------------------------
#
#	各種変数の設定
#
#-------------------------------------------------------------------
# HOME
KHOME=/home/kea00sys
# APPNM
EXENM=sun_bun_dst.sh

#TMP FILE
WK=/tmp/$$
# SUN分注結果ファイル受信用ディレクトリ
RECD=/apdata/today/file/kinq
#緊急用ディレクトリ
KINQ=/apdata/today/online/host/Kinq
# エラーファイル待避ディレクトリ
ERRDIR=$KINQ/err_Recv
# 緊急用分注結果ファイル移動先
BUNDIR=$KINQ/Recv/bun

# 緊急用分注結果ファイル名作成
PRFN=KBU
EXFN=".dat"
# 緊急分注結果FTP送信終了ファイル
ENDFN="KBUNEND.dat"

# 緊急用依頼ファイル移動先
IRIDIR=$KINQ/Recv/iri
# 処理済みファイル待避ディレクトリ
ENDDIR=$KINQ/Recv/sumi
# LOG FILE
APLOG=/apdata/aplog/$EXENM.log

DBG=$1							# DEBUG MODE指定

YMD=`date +%Y%m%d`

#
#	LOG OUTPUT VARIABLE
PROCESSID=$$
WKUPAPP=$EXENM

db2 connect to kea00db user db2inst1 using db2inst1
if [ $? -gt 0 ]; then
    exit 1
fi

#-------------------------------------------------------------------
#
#	実行判断
#
#-------------------------------------------------------------------
ps -ef | grep sun
#
#	重複処理判断

ps -ef | grep "$EXENM" | grep -v $$ | grep -v $PPID | grep -v grep | grep -v vi  > $WK.dup
if [ -s $WK.dup ]
then
	echo "[`date`] DUPLICATE EXIT !" >> $APLOG
	rm $WK.*
	db2 terminate
	exit 0
fi

#
#	日次処理判断		1:日次中は処理を抜ける
db2 "select count(*) as uny from sysknrmst where UNYFLG='1'" | sed 's/ //g' | grep ^[0-9] | grep -v "レコード" > $WK.uny

if [ -s $WK.uny ]
then
	CNT=`cat $WK.uny`
else
	echo "ERROR "
	db2 terminate
	rm $WK.*
	exit 0
fi
if [ $CNT -eq 1 ]
then
	echo "[`date`] 日次処理中 EXIT !" >> $APLOG
	db2 terminate
	rm $WK.*
	exit 0
fi

#
#	緊急業務開始判断	 緊急依頼ロットNo=0:データ存在しない
db2 "select count(*) as lotno from knkyulot where knskisymd=(select kkkjsriymd from sysknrmst) and kkirilotno=0" | sed 's/ //g' | grep ^[0-9] | grep -v "レコード" > $WK.lotno

if [ -s $WK.lotno ]
then
	CNT=`cat $WK.lotno`
else
	echo "ERROR "
	db2 terminate
	rm $WK.*
	exit 0
fi
if [ $CNT -eq 0 ]
then
	echo "[`date`] 緊急業務開始前 EXIT !" >> $APLOG
	db2 terminate
	rm $WK.*
	exit 0
fi

#-------------------------------------------------------------------
#
#	ファイル振り分け
#
#-------------------------------------------------------------------
#
#	ファイル受信用ディレクトリへの移動	
cd $RECD

#
# ロックファイルの有無
if [ -s $ENDFN ]
then
	echo "[`date`] 緊急用分注結果ENDファイル受信存在" >> $APLOG
else
	echo "[`date`] 緊急用分注結果ENDファイル受信存在せず -> EXIT" >> $APLOG
	#	処理終了
	db2 terminate
	rm $WK.*
	exit 0
fi

#	環境変数からディレクトリを除いたファイル名を取り出す
##LS=`basename $FILENM`
##mv $FILENM	$LS

#==========================================================================
#		
#		ファイル振り分け
#		
#==========================================================================
##for FNM in `ls $BUN*`
for FNM in `ls KBUNCHU*`
do

	#	stat
	if [ -w $FNM ]
	then		
		echo "[`date`] 緊急用分注結果ファイル受信 [$FNM]" >> $APLOG
	else
		continue;
	fi

	#	処理中では無いことを確認 	wcのsizeでdiffを取る
	wc $FNM > $WK.mae
	sleep 2
	wc $FNM > $WK.ato
	diff $WK.mae $WK.ato > $WK.diff

	if [ -s $WK.diff ]
	then
		echo "[`date`] 緊急用分注結果ファイル受信中　SKIP..... [$FNM]" >> $APLOG
		continue;
	fi

	#	ファイル名作成
	##BFNM=$PRFN.$FNM.`date +%m%d%H%M%S`$EXFN
	BFNM=$PRFN.`date +%m%d%H%M%S`

	#	処理済ディレクトリに移動
	mv $FNM $BUNDIR/$BFNM

	echo "[`date`] ファイルMOVE EXECUTE [$FNM]->[$BFNM]" >> $APLOG
	#----------------
	#	LOG OUTPUT
	#----------------
	MESSAGE="SUN分注結果受信[$FNM]--->[$BFNM]"

	sh $KHOME/shell/hulft_ins_log.sh "T" $PROCESSID $WKUPAPP "$MESSAGE" 

	#	ファイル名のユニーク性KEEPのためSLEEP
	sleep 1
done

#==========================================================================
#		
#		終了処理
#		
#==========================================================================
#	DB DISCONNECT
db2 terminate

#
#	ファイル受信用ディレクトリへの移動	
cd $RECD

echo "[`date`] 緊急用分注結果ENDファイル受信削除" >> $APLOG
rm $ENDFN

#
#	処理終了ファイルの移動
for i in `find $IRIDIR  -name "END*" -print `
do
	mv $i  $ENDDIR
done

#
#  中間ファイルのｸﾘｱ
rm $WK*

exit 0
