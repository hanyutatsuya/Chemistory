#!/bin/bash -
###############################################################################
#
# 履歴削除シェル
# $1 : DB名
# $2 : DBユーザ
# $3 : DBパスワード
# 
# 更新日 : 2008.08.06
#
###############################################################################

## 一度に削除する件数 (件)
DEL_CNT=10000

## 履歴保存期間 (日)
SAVE_DAYS=400

## スリープ (秒)
SLEEP_CNT=1

## エラーログの出力先
LOG_DIR="/apdata/aplog"

## エラーログのプレフィック
NAME_ERRLOG="WARNING_"

echo ""
echo "[`date`] db2 connect start ---------------------------------->"
db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"del_rireki.log"
    exit 1
fi
echo "[`date`] db2 connect end ------------------------------------<"
echo ""
echo ""

## 保存期間＋１の日数
DEL_DAYS=`expr $SAVE_DAYS + 1`

echo "[`date`] $DEL_DAYS日前の受付日取得 start -------------------------->"
echo ""
echo "    > SELECT (KNR.KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM (SELECT KJNSRIYMD FROM SYSKNRMST) AS KNR"
db2 "SELECT (KNR.KJNSRIYMD -$DEL_DAYS days) as KJNDAY FROM (SELECT KJNSRIYMD FROM SYSKNRMST) AS KNR" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > KJNYMD
echo ""

## 保存期間＋１日以前の受付日(複数ある場合もある)
DEL_UTKYMD=\'`cat KJNYMD`\'
rm KJNYMD
echo "    $DEL_DAYS日前の受付日 = $DEL_UTKYMD"
echo ""

echo "    > SELECT DISTINCT UTKYMD FROM RIREKI WHERE UTKYMD <= $DEL_UTKYMD"
db2 "SELECT DISTINCT UTKYMD FROM RIREKI WHERE UTKYMD <= $DEL_UTKYMD" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > KJNYMD
echo ""
echo "    以下の受付日のデータをRIREKIテーブルから削除します。"
for DEL_YMD in `cat KJNYMD`
do
    ## 削除対象の受付日を全て出力
	echo "    ・$DEL_YMD"
done
echo ""
echo "[`date`] $DEL_DAYS日前の受付日取得 end ----------------------------<"
echo ""
echo ""


ERR_FLG=0

for DEL_YMD in `cat KJNYMD`
do
	B_CNT=0
	A_CNT=0
	L_CNT=0

	DEL_DATE=\'$DEL_YMD\'
	echo "[`date`] 受付日 = $DEL_DATE を削除しています。------------>"
	echo ""

	echo "    [`date`] select before start ---------------------------->"
	echo ""
	echo "        > SELECT COUNT(UTKYMD) FROM RIREKI WHERE UTKYMD = $DEL_DATE"
	db2 "SELECT COUNT(UTKYMD) as CNT FROM RIREKI WHERE UTKYMD = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > CNT
	echo ""
	
	## 対象受付日の削除前の全件数
	B_CNT=`cat CNT`
	rm CNT
	echo "        [`date`] RIREKI削除前" $B_CNT "件 です。"
	L_CNT=`expr $B_CNT / $DEL_CNT + 1`
	#echo "        [`date`] $L_CNT 回 ループします。"
	echo ""
	echo "    [`date`] select before end ------------------------------<"
	echo ""
	echo ""

	echo "    [`date`] DELETE RIREKI UTKYMD = $DEL_DATE start ------>"
	echo ""
	echo "        > DELETE FROM (SELECT UTKYMD, IRINO, ZSSDINO, KNSGRP, KMKCD FROM RIREKI WHERE UTKYMD = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)"
	echo ""

	CNT_LOOP=1
	while [ $CNT_LOOP -le $L_CNT ];
	do
		db2 "DELETE FROM (SELECT UTKYMD, IRINO, ZSSDINO, KNSGRP, KMKCD FROM RIREKI WHERE UTKYMD = $DEL_DATE FETCH FIRST $DEL_CNT ROWS ONLY)" > /dev/null
		db2 COMMIT > /dev/null

		if [ $L_CNT -eq $CNT_LOOP ];
		then
			echo "        [`date`] $B_CNT 件削除しました。"
		else
			CNT_ECHO=`expr $CNT_LOOP \* $DEL_CNT`
			echo "        [`date`] $CNT_ECHO / $B_CNT 件削除しました。"
		fi

		CNT_LOOP=`expr $CNT_LOOP + 1`
		
		#echo "        [`date`] SLEEP($SLEEP_CNT) START"
		## スリープ処理(秒数はこのシェルの先頭で宣言)
		sleep $SLEEP_CNT
		#echo "        [`date`] SLEEP($SLEEP_CNT) END"
	done
	
	echo ""
	echo "    [`date`] DELETE RIREKI UTKYMD = $DEL_DATE end --------<"

	echo ""
	echo ""
	echo "    [`date`] select after start ----------------------------->"
	echo ""
	echo "        > SELECT COUNT(UTKYMD) FROM RIREKI WHERE UTKYMD = $DEL_DATE"
	db2 "SELECT COUNT(UTKYMD) as CNT FROM RIREKI WHERE UTKYMD = $DEL_DATE" | sed 's/ //g' | grep ^[0-9] | grep -v レコード > CNT
	echo ""
	A_CNT=`cat CNT`
	rm CNT
	if [ $A_CNT -eq 0 ];
	then
		echo "        [`date`] RIREKI削除後" $A_CNT "件 です。"
	else
		echo "        ◆ [`date`] ERROR : RIREKI削除後" $A_CNT "件 です。"
		ERR_FLG=1
	fi
	echo ""
	echo "    [`date`] select after end -------------------------------<"
	echo ""
	echo ""

done

rm KJNYMD

if [ $ERR_FLG -eq 1 ];
then
	echo "[`date`] 履歴削除でエラーが発生しました。"
	echo ""
	echo ""
	echo `date`" ERROR : 履歴削除でエラーが発生しました。" >> $LOG_DIR/$NAME_ERRLOG"del_rireki.log"
fi

echo "[`date`] db2 terminate start -------------------------------->"
echo ""
db2 terminate;
echo ""
echo "[`date`] db2 terminate end ----------------------------------<"
echo ""

exit 0
