#!/bin/ksh
# kshell用画面制御汎用関数

####################################
# 色指定
# esColor 色インデックス
# 0～7（黒～白）までの８色を指定可能
# 8 はNO_COLOR
####################################
esColor() {
	local esBLACK="\033[30m"
	local esRED="\033[31m"
	local esGREEN="\033[32m"
	local esYELLOW="\033[33m"
	local esBLUE="\033[34m"
	local esPURPLE="\033[35m"
	local esCYAN="\033[36m"
	local esWHITE="\033[37m"
	local esNOCOLOR="\033[0m"

	local _escol=""

	case $1 in
	0)	_escol=$esBLACK
		;;
	1)	_escol=$esRED
		;;
	2)	_escol=$esGREEN
		;;
	3)	_escol=$esYELLOW
		;;
	4)	_escol=$esBLUE
		;;
	5)	_escol=$esPURPLE
		;;
	6)	_escol=$esCYAN
		;;
	7)	_escol=$esWHITE
		;;
	*)	_escol=$esNOCOLOR
		;;
	esac

	echo -en $_escol
}

####################################
# カーソル移動
# esCursol X位置 Y位置
# 画面上の任意位置にカーソルを移動
####################################
esCursol() {
	local _esx=$1
	local _esy=$2
	echo -en "\033["$_esy";"$_esx"H"
}

####################################
# カーソル移動
# esCursolUp 上移動行数
# 現在の行位置から指定行数分上にカーソルを移動
####################################
esCursolUp() {
	local _espos=$1
echo "-"$_espos"-"
	echo -en "\033["$_espos"A"
}

####################################
# カーソル移動
# esCursolDown 下移動行数
# 現在の行位置から指定行数分下にカーソルを移動
####################################
esCursolDown() {
	local _espos=$1
	echo -en "\033["$_espos"B"
}
 
####################################
# カーソル移動
# esCursolRight 右移動カラム数
# 現在のカラム位置から指定カラム数分右にカーソルを移動
####################################
esCursolRight() {
	local _espos=$1
	echo -en "\033["$_esdown"C"
}

####################################
# カーソル移動
# esCursolLeft 左移動カラム数
# 現在のカラム位置から指定カラム数分左にカーソルを移動
####################################
esCursolLeft() {
	local _espos=$1
	echo -en "\033["$_esdown"D"
}

####################################
# メッセージ表示
# esMessageBoxEnt x y message
# Enter入力待ちメッセージ表示
####################################
esMessageBoxEnt() {
local tempLine="----------------------------------------------------------------------------------------------------"
local lineStr=""
local lineEnt=""
local form=""
local ans=""
typeset -i x
typeset -i y
typeset -i datLen
	local message=$3

	maxLen=$2
	datLen=`echo $message|wc -c`
	let datLen=datLen+1
	y=$1
	x=$2

	form="%-"$datLen"."$datLen"s"
	lineStr="+"`printf $form $tempLine`"+"
	lineEnt="| [Enter]: "

	esCursol $x $y; echo -n $lineStr; let y=y+1
	esCursol $x $y; echo -n "| "$message" |"; let y=y+1
	esCursol $x $y; echo -n $lineStr; let y=y+1
	esCursol $x $y; echo -n $lineEnt; let y=y+1
	esCursol $x $y; echo -n $lineStr;
	let y=y-1
	let x=x+10
	esCursol $x $y
	read ans
}

####################################
# メッセージ表示
# esMessageBoxEntMax y maxlen message
# Enter入力待ちメッセージ表示
# 想定画面の最大幅を指定することで
# そのほぼ中央にメッセージを表示する
####################################
esMessageBoxEntMax() {
local tempLine="----------------------------------------------------------------------------------------------------"
local lineStr=""
local lineEnt=""
local form=""
local ans=""
typeset -i x
typeset -i y
typeset -i maxLen
typeset -i datLen
	local message=$3

	maxLen=$2
	datLen=`echo $message|wc -c`
	let datLen=datLen+1
	y=$1
	let x=maxLen-datLen-1
	let x=x/2

	form="%-"$datLen"."$datLen"s"
	lineStr="+"`printf $form $tempLine`"+"
	lineEnt="| [Enter]: "

	esCursol $x $y; echo -n $lineStr; let y=y+1
	esCursol $x $y; echo -n "| "$message" |"; let y=y+1
	esCursol $x $y; echo -n $lineStr; let y=y+1
	esCursol $x $y; echo -n $lineEnt; let y=y+1
	esCursol $x $y; echo -n $lineStr;
	let y=y-1
	let x=x+10
	esCursol $x $y
	read ans
}

