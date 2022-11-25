#!/bin/ksh

#------------------------------------------------
# 分注END強制作成
# ---------------------------------
# v1.0		2007.03.28	Wajima
#------------------------------------------------

ME=`basename $0`
DEF_DB="KEA00DB"  #TEST DB
DEF_ID="db2inst1" #TEST ID
DEF_PW="db2inst1" #TEST Password
USE_DB=""
USE_ID=""
USE_PW=""
sem=""
COMDIR="$HOME/shell/upd_bchendflg"

#. esfunc.h
. $COMDIR/esfunc.h

DEBUG=0 # 1: DEBUG MODE

viewInput() {
    esCursol 1 19
    echo "                              [Q]戻る"
    echo "________________________________________________________________________________"
    echo " => "
    echo "________________________________________________________________________________"
    esCursol 5 21
}

# DB接続
fnDBConnect() {
	db2 connect to $1 user $2 using $3 > /dev/null 2>&1
	ret=$?

	if [[ $ret -ne 0 ]]
	then
		esColor 5
		esMessageBoxEntMax 8 84 "ERROR : DB接続失敗($1,$2,$3,$ret)"
		esColor 8
		return $ret
	fi

	return 0
}

# DB切断
fnDBTerminate() {
	db2 terminate > /dev/null 2>&1
}

# 分注END強制作成 : 分注フラグが'0'なら'1'に更新
fnSetBunchuEnd() {
	hnktntid=`echo $ME | awk -F'.' '{print substr($1,1,8)}'`
	if [[ $DEBUG -eq 1 ]]
	then
		COMMAND="select BCHENDFLG, HNKTNTID, KSNDH from sysknrmst for read only"
	else
		COMMAND="update sysknrmst set BCHENDFLG='1', HNKTNTID='"$hnktntid"', KSNDH=current timestamp"
	fi

	db2 $COMMAND > /dev/null 2>&1

	ret=$?

	if [[ $ret -ne 0 ]]
	then
		esColor 5
		esMessageBoxEntMax 8 84 "ERROR : 分注END強制作成失敗($ret)"
		esColor 8
		return $ret
	fi

	esColor 2
	esCursol 2 15; echo "分注ENDフラグを更新しました。"
	esColor 8
	sleep 1

	db2 commit > /dev/null 2>&1

	return 0
}

# 分注END情報表示確認
fnBendView2() {
	set -A bend in `db2 -x "select BCHENDFLG,BCHEND0DH,BCHEND1DH,BCHEND2DH,BCHEND3DH,BCHEND4DH from sysknrmst for read only"`

	if [[ ${#bend[*]} -lt 1 ]]
	then
		esColor 5
		esMessageBoxEntMax 8 84 "ERROR:システム管理マスタの読込みに失敗しました。"
		esColor 8
		return -1
	fi

	esColor 7
	esCursol 48 5;  echo -n "分注END関連の情報(処理後)"
	esCursol 48 7;  echo -n "分注ＥＮＤフラグ : "; esColor 2; echo -n "${bend[1]}"; esColor 7
	esCursol 48 8;  echo -n "尿フロ 受信日時  : ${bend[2]}"
	esCursol 48 9;  echo -n "血清１ 受信日時  : ${bend[3]}"
	esCursol 48 10; echo -n "血清２ 受信日時  : ${bend[4]}"
	esCursol 48 11; echo -n "血清３ 受信日時  : ${bend[5]}"
	esCursol 48 12; echo -n "血清４ 受信日時  : ${bend[6]}"
	esColor 8

	if [[ ${bend[1]} = "0" ]]
	then
		esColor 5
		esCursol 48 14; echo -n "分注ＥＮＤフラグを更新出来ませんでした。(Enter)"
		esColor 8
		read ans
	else
		esColor 2
		esCursol 48 14; echo -n "分注ＥＮＤフラグは設定済みです。(Enter)"
		esColor 8
		read ans
	fi
	
	db2 commit > /dev/null 2>&1

	return 0
}

# 分注END情報表示/設定
fnBendView() {
	clear

	set -A bend in `db2 -x "select BCHENDFLG,BCHEND0DH,BCHEND1DH,BCHEND2DH,BCHEND3DH,BCHEND4DH from sysknrmst for read only"`

	if [[ ${#bend[*]} -lt 1 ]]
	then
		esColor 5
		esMessageBoxEntMax 8 84 "ERROR:システム管理マスタの読込みに失敗しました。"
		esColor 8
		return -1
	fi

	esCursol 2 5;  echo -n "分注END関連の情報(処理前)"
	esCursol 2 7;  echo -n "分注ＥＮＤフラグ : "; esColor 3; echo -n "${bend[1]}"; esColor 8
	esCursol 2 8;  echo -n "尿フロ 受信日時  : ${bend[2]}"
	esCursol 2 9;  echo -n "血清１ 受信日時  : ${bend[3]}"
	esCursol 2 10; echo -n "血清２ 受信日時  : ${bend[4]}"
	esCursol 2 11; echo -n "血清３ 受信日時  : ${bend[5]}"
	esCursol 2 12; echo -n "血清４ 受信日時  : ${bend[6]}"

	if [[ ${bend[1]} = "0" ]]
	then
		esCursol 2 14; echo -n "分注ＥＮＤフラグを更新しますか？（y/n）"
		viewInput
		read ans
		
		if [[ $ans = [Yy] ]]
		then
			fnSetBunchuEnd
			fnBendView2
		fi
	else
		esCursol 2 14; echo -n "分注ＥＮＤフラグは設定済みです。(Enter)"
		viewInput
		read ans
	fi
	
	db2 commit > /dev/null 2>&1

	return 0
}

#------------------------------------------------
# main()
#   input : DBNAME
#           id(DB)
#           password(DB)
#------------------------------------------------

ME=`basename $0`
DEF_DB="KEA00DB"  #TEST DB
DEF_ID="db2inst1" #TEST ID
DEF_PW="db2inst1" #TEST Password
USE_DB=""
USE_ID=""
USE_PW=""
sem=""
FIN="fin."

DEBUG=0 # 1: DEBUG MODE

# 排他制御
sem="/tmp/`basename $0`"
ln -s /$sem.lock $sem || exit
# trap "echo $FIN; db2 terminate; rm $sem; exit 0" 2 3 15
trap "db2 terminate; rm $sem; exit 0" 2 3 15

echo "$ME : 起動 "`date`

# オプション数チェック
# ---------------------------------
if [ $# -lt 3 ]
then
	USE_DB=$DEF_DB
	USE_ID=$DEF_ID
	USE_PW=$DEF_PW
else
	USE_DB=$1
	USE_ID=$2
	USE_PW=$3
fi

# DB接続
fnDBConnect $USE_DB $USE_ID $USE_PW

fnBendView

# DB切断
fnDBTerminate

# 排他制御(後始末)
rm "$sem"

echo "$ME : 終了 "`date`

# echo $FIN

exit 0
