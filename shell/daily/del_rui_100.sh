#!/bin/bash -
###############################################################################
#
# 累積削除シェル(100日分)
# $1 : DB名
# $2 : DBユーザ
# $3 : DBパスワード
# 
# 更新日 : 2008.10.01
#
###############################################################################

###############################################################################
# 0. 定数宣言
###############################################################################

## 一度に削除する件数 (件)
DEL_CNT=10000

## 保存期間 (100日)
SAVE_DAY100=100
TBL_100=(RUI_BUNCHU RUI_HKKKNRI RUI_KENORDER RUI_KENPOS RUI_OTHERKKA)
KEY_100=(SRIYMD HKKSJYMD KNSKISYMD KNSKISYMD UTKYMD)
## 各テーブルのキー
## TABLE名       │ 日付キー   │ DELETEキー
## ───────┼──────┼───────────────────────────────
## RUI_BUNCHU    │ SRIYMD     │ SRIYMD, KNTNO, SMPCD, KMKCD
## RUI_HKKKNRI   │ HKKSJYMD   │ HKKSJYMD, HKKSJNO
## RUI_KENORDER  │ KNSKISYMD  │ KNSKISYMD, SRIYMD, KNTNO, KNSGRP, KMKCD, KNSSU, KNSSUEDA
## RUI_KENPOS    │ KNSKISYMD  │ KNSKISYMD, SRIYMD, KNTNO, KNNDH, ASYRCKID
## RUI_OTHERKKA  │ UTKYMD     │ UTKYMD, IRINO, KMKCD

## スリープ (秒)
SLEEP_CNT=1

## エラーログの出力先
LOG_DIR="/apdata/aplog"

## エラーログのプレフィック
NAME_ERRLOG="WARNING_"

###############################################################################
# 1. DB2 CONNECT 処理
###############################################################################
echo ""
echo "[`date`] DB2 CONNECT START ---------------------------------->"
db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"del_rui_100.log"
    exit 1
fi
echo "[`date`] DB2 CONNECT END ------------------------------------<"
echo ""
echo ""


###############################################################################
# 2. 100日分保管テーブルの削除処理
###############################################################################

## 保存期間＋１の日数
DEL_DAYS=`expr $SAVE_DAY100 + 1`

echo "●○● [`date`] 100日保管テーブル削除処理 START ●○● ==========================>"
echo ""
echo ""
echo "[`date`] $DEL_DAYS日前の日付取得 START -------------------------->"
echo ""
echo "    > SELECT (KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM SYSKNRMST"
db2 "SELECT (KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM SYSKNRMST" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > KJNYMD
echo ""

## 保存期間＋１日以前の日付取得(複数ある場合もある)
DEL_UTKYMD=\'`cat KJNYMD`\'
rm KJNYMD

echo "    ● $DEL_DAYS日前の日付 = $DEL_UTKYMD"
echo ""
echo "[`date`] $DEL_DAYS日前の日付取得 END ----------------------------<"
echo ""
echo ""

## 削除対象のテーブル数
TBL_CNT=0

for RUI_TBL in ${TBL_100[@]}
do
    ## 対象テーブルの日付キー設定
	RUI_KEY=${KEY_100[$TBL_CNT]}
	
	echo "    ■■■■■ [`date`] $RUI_TBL の削除を開始 ■■■■■"
	echo ""
	echo "        > SELECT DISTINCT $RUI_KEY FROM $RUI_TBL WHERE $RUI_KEY <= $DEL_UTKYMD"
	db2 "SELECT DISTINCT $RUI_KEY FROM $RUI_TBL WHERE $RUI_KEY <= $DEL_UTKYMD" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > KJNYMD
	echo ""
	
	## SELECT 対象件数が0かどうか？
	CNT_KJNYMD=`wc -l KJNYMD | sed 's/KJNYMD//g' | sed 's/ //g'`
	if [ $CNT_KJNYMD == 0 ]
	then
		echo "        $RUI_TBL テーブルに削除対象のデータがありません。"
	else
		echo "        以下の日付のデータを $RUI_TBL テーブルから削除します。"
		for DEL_YMD in `cat KJNYMD`
		do
		    ## 削除対象の日付を全て出力
			echo "          ・$DEL_YMD"
		done
	fi
	echo ""
	echo ""


	ERR_FLG=0

	for DEL_YMD in `cat KJNYMD`
	do
	    ## 対象日付の削除前の全件数
		B_CNT=0
		## 対象日付の削除後の全件数
		A_CNT=0
		## ループ回数
		L_CNT=0

		DEL_DATE=\'$DEL_YMD\'

		echo "    [`date`] SELECT BEFORE START ---------------------------->"
		echo ""
		echo "        > SELECT COUNT($RUI_KEY) FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE"
		db2 "SELECT COUNT($RUI_KEY) as CNT FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > CNT
		echo ""
		
		## 対象日付の削除前の全件数
		B_CNT=`cat CNT`
		rm CNT
		
		echo "        [`date`] $RUI_TBL 削除前" $B_CNT "件 です。"
		
		## ループ回数
		L_CNT=`expr $B_CNT / $DEL_CNT + 1`

		echo ""
		echo "    [`date`] SELECT BEFORE END ------------------------------<"
		echo ""
		echo ""

        ## RUI_KENPOSの場合はユニークキー無しなので、DELETEキーを固定で設定
		if [ $RUI_TBL == RUI_KENPOS ]
		then
			COLNAMES="KNSKISYMD, SRIYMD, KNTNO, KNNDH, ASYRCKID"
		else
			db2 "SELECT COLNAME FROM SYSCAT.COLUMNS WHERE TABNAME = '$RUI_TBL' AND KEYSEQ IS NOT NULL ORDER BY KEYSEQ" | sed 's/ //g' | grep ^[A-Z] | grep -v COLNAME | grep -v レコード > SEL_COL
			
			## DELETEキーのカラム数
			COL_CNT=0
			
			for colnm in `cat SEL_COL`
			do
				## COL_CNTが1以上の場合
				if [ $COL_CNT -ge 1 ]
				then
					COLNAMES="$COLNAMES, $colnm"
				else
				    ## 1カラム目はカンマを付けない
					COLNAMES="$colnm"
				fi
				COL_CNT=`expr $COL_CNT + 1`
			done
			rm SEL_COL
		fi

		echo "    [`date`] DELETE $RUI_TBL $RUI_KEY = $DEL_DATE START ------>"
		echo ""
		echo "        > DELETE FROM (SELECT $COLNAMES FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)"
		echo ""

		CNT_LOOP=1
		while [ $CNT_LOOP -le $L_CNT ];
		do
			## 累積テーブル削除処理
			db2 "DELETE FROM (SELECT $COLNAMES FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)" > /dev/null
			db2 COMMIT > /dev/null

			if [ $L_CNT -eq $CNT_LOOP ];
			then
				echo "        [`date`] $B_CNT 件削除しました。"
			else
				CNT_ECHO=`expr $CNT_LOOP \* $DEL_CNT`
				echo "        [`date`] $CNT_ECHO / $B_CNT 件削除しました。"
			fi

            ## 現在のループ数をカウントアップ
			CNT_LOOP=`expr $CNT_LOOP + 1`
			
			## スリープ処理(秒数はこのシェルの先頭で宣言)
			sleep $SLEEP_CNT
		done
		
		echo ""
		echo "    [`date`] DELETE $RUI_TBL $RUI_KEY = $DEL_DATE END --------<"

		echo ""
		echo ""
		echo "    [`date`] SELECT AFTER START --------------------------------->"
		echo ""
		echo "        > SELECT COUNT($RUI_KEY) FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE"
		db2 "SELECT COUNT($RUI_KEY) as CNT FROM $RUI_TBL WHERE $RUI_KEY = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > CNT
		echo ""
		
		## 対象日付の削除後の全件数
		A_CNT=`cat CNT`
		rm CNT
		
		if [ $A_CNT -eq 0 ];
		then
			echo "        [`date`] $RUI_TBL 削除後" $A_CNT "件 です。"
		else
			echo "        [`date`] ◆ ERROR : $RUI_TBL 削除後" $A_CNT "件 です。"
			ERR_FLG=1
		fi
		echo ""
		echo "    [`date`] SELECT AFTER END -----------------------------------<"
		echo ""
		echo ""

	done

	rm KJNYMD

	if [ $ERR_FLG -eq 1 ];
	then
		echo "◆◇◆ [`date`] $RUI_TBL の削除でエラーが発生しました。 ◆◇◆"
		echo ""
		echo ""
		echo `date`" ERROR : $RUI_TBL の削除でエラーが発生しました。" >> $LOG_DIR/$NAME_ERRLOG"del_rui_100.log"
	fi
	
	## 削除対象のテーブル数カウントアップ
	TBL_CNT=`expr $TBL_CNT + 1`
done

echo "●○● [`date`] 100日保管テーブル削除処理 END   ●○● ==========================<"
echo ""
echo ""


###############################################################################
# 3. DB2 TERMINATE 処理
###############################################################################
echo "[`date`] DB2 TERMINATE START -------------------------------->"
echo ""
db2 terminate;
echo ""
echo "[`date`] DB2 TERMINATE END ----------------------------------<"
echo ""


###############################################################################
# 4. 累積削除シェル終了
###############################################################################
exit 0
