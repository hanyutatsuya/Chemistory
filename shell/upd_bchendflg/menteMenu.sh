#!/bin/ksh

##############################################################
#
# menteMenu.sh メンテナンスメニュー表示
# 通常はTeraTermマクロから起動される
#
# 2007.03.29 T.Wajima Create
# 2008.08.21 Moriya   本番用に修正
#
##############################################################

USE_DB="KEA00DB"
USE_ID="db2inst1"
USE_PW="db2inst1"

ME=`basename $0`
COMDIR="$HOME/shell/upd_bchendflg"
FIN="fin."

#. esfunc.h
. $COMDIR/esfunc.h

# 排他制御
sem="/tmp/`basename $0`"
ln -s /$sem.lock $sem || exit
trap "rm $sem; echo $FIN; db2 terminate; exit 0" 2 3 15

viewInput() {
	esCursol 1 19
	echo "                              [Q]戻る"
	echo "________________________________________________________________________________"
	echo " => "
	echo "________________________________________________________________________________"
	esCursol 5 21
}

while (( 1 ))
do
	clear
	esCursol 1 1;   echo "メンテナンスメニュー"
	esCursol 31 3;  echo "[1]分注END強制作成"
#	esCursol 31 5;  echo "[2]ラック登録リセット"
	viewInput
	read ans

	if [[ -z $ans ]]
	then
		continue
	fi

	if [[ $ans = [Qq] ]]
	then
		# 排他制御(後始末)
		rm $sem

		echo $FIN

		exit 0
	fi

	case $ans in
	1)
		ksh $COMDIR/upd_bchendflg.sh $USE_DB $USE_ID $USE_PW
		;;
#	2)
#		ksh $COMDIR/upd_rackreset.sh $USE_DB $USE_ID $USE_PW
#		;;
	*)
		esColor 5
		esMessageBoxEntMax 8 84 "Error:指定された番号が無効です"
		esColor 8
		;;
	esac
done

# 排他制御(後始末)
rm $sem

echo $FIN

exit 0

