#!/bin/ksh
# kshell�p��ʐ���ėp�֐�

####################################
# �F�w��
# esColor �F�C���f�b�N�X
# 0�`7�i���`���j�܂ł̂W�F���w��\
# 8 ��NO_COLOR
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
# �J�[�\���ړ�
# esCursol X�ʒu Y�ʒu
# ��ʏ�̔C�ӈʒu�ɃJ�[�\�����ړ�
####################################
esCursol() {
	local _esx=$1
	local _esy=$2
	echo -en "\033["$_esy";"$_esx"H"
}

####################################
# �J�[�\���ړ�
# esCursolUp ��ړ��s��
# ���݂̍s�ʒu����w��s������ɃJ�[�\�����ړ�
####################################
esCursolUp() {
	local _espos=$1
echo "-"$_espos"-"
	echo -en "\033["$_espos"A"
}

####################################
# �J�[�\���ړ�
# esCursolDown ���ړ��s��
# ���݂̍s�ʒu����w��s�������ɃJ�[�\�����ړ�
####################################
esCursolDown() {
	local _espos=$1
	echo -en "\033["$_espos"B"
}
 
####################################
# �J�[�\���ړ�
# esCursolRight �E�ړ��J������
# ���݂̃J�����ʒu����w��J���������E�ɃJ�[�\�����ړ�
####################################
esCursolRight() {
	local _espos=$1
	echo -en "\033["$_esdown"C"
}

####################################
# �J�[�\���ړ�
# esCursolLeft ���ړ��J������
# ���݂̃J�����ʒu����w��J�����������ɃJ�[�\�����ړ�
####################################
esCursolLeft() {
	local _espos=$1
	echo -en "\033["$_esdown"D"
}

####################################
# ���b�Z�[�W�\��
# esMessageBoxEnt x y message
# Enter���͑҂����b�Z�[�W�\��
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
# ���b�Z�[�W�\��
# esMessageBoxEntMax y maxlen message
# Enter���͑҂����b�Z�[�W�\��
# �z���ʂ̍ő啝���w�肷�邱�Ƃ�
# ���̂قڒ����Ƀ��b�Z�[�W��\������
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

