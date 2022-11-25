#!/bin/ksh

#------------------------------------------------
# ����END�����쐬
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
    echo "                              [Q]�߂�"
    echo "________________________________________________________________________________"
    echo " => "
    echo "________________________________________________________________________________"
    esCursol 5 21
}

# DB�ڑ�
fnDBConnect() {
	db2 connect to $1 user $2 using $3 > /dev/null 2>&1
	ret=$?

	if [[ $ret -ne 0 ]]
	then
		esColor 5
		esMessageBoxEntMax 8 84 "ERROR : DB�ڑ����s($1,$2,$3,$ret)"
		esColor 8
		return $ret
	fi

	return 0
}

# DB�ؒf
fnDBTerminate() {
	db2 terminate > /dev/null 2>&1
}

# ����END�����쐬 : �����t���O��'0'�Ȃ�'1'�ɍX�V
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
		esMessageBoxEntMax 8 84 "ERROR : ����END�����쐬���s($ret)"
		esColor 8
		return $ret
	fi

	esColor 2
	esCursol 2 15; echo "����END�t���O���X�V���܂����B"
	esColor 8
	sleep 1

	db2 commit > /dev/null 2>&1

	return 0
}

# ����END���\���m�F
fnBendView2() {
	set -A bend in `db2 -x "select BCHENDFLG,BCHEND0DH,BCHEND1DH,BCHEND2DH,BCHEND3DH,BCHEND4DH from sysknrmst for read only"`

	if [[ ${#bend[*]} -lt 1 ]]
	then
		esColor 5
		esMessageBoxEntMax 8 84 "ERROR:�V�X�e���Ǘ��}�X�^�̓Ǎ��݂Ɏ��s���܂����B"
		esColor 8
		return -1
	fi

	esColor 7
	esCursol 48 5;  echo -n "����END�֘A�̏��(������)"
	esCursol 48 7;  echo -n "�����d�m�c�t���O : "; esColor 2; echo -n "${bend[1]}"; esColor 7
	esCursol 48 8;  echo -n "�A�t�� ��M����  : ${bend[2]}"
	esCursol 48 9;  echo -n "�����P ��M����  : ${bend[3]}"
	esCursol 48 10; echo -n "�����Q ��M����  : ${bend[4]}"
	esCursol 48 11; echo -n "�����R ��M����  : ${bend[5]}"
	esCursol 48 12; echo -n "�����S ��M����  : ${bend[6]}"
	esColor 8

	if [[ ${bend[1]} = "0" ]]
	then
		esColor 5
		esCursol 48 14; echo -n "�����d�m�c�t���O���X�V�o���܂���ł����B(Enter)"
		esColor 8
		read ans
	else
		esColor 2
		esCursol 48 14; echo -n "�����d�m�c�t���O�͐ݒ�ς݂ł��B(Enter)"
		esColor 8
		read ans
	fi
	
	db2 commit > /dev/null 2>&1

	return 0
}

# ����END���\��/�ݒ�
fnBendView() {
	clear

	set -A bend in `db2 -x "select BCHENDFLG,BCHEND0DH,BCHEND1DH,BCHEND2DH,BCHEND3DH,BCHEND4DH from sysknrmst for read only"`

	if [[ ${#bend[*]} -lt 1 ]]
	then
		esColor 5
		esMessageBoxEntMax 8 84 "ERROR:�V�X�e���Ǘ��}�X�^�̓Ǎ��݂Ɏ��s���܂����B"
		esColor 8
		return -1
	fi

	esCursol 2 5;  echo -n "����END�֘A�̏��(�����O)"
	esCursol 2 7;  echo -n "�����d�m�c�t���O : "; esColor 3; echo -n "${bend[1]}"; esColor 8
	esCursol 2 8;  echo -n "�A�t�� ��M����  : ${bend[2]}"
	esCursol 2 9;  echo -n "�����P ��M����  : ${bend[3]}"
	esCursol 2 10; echo -n "�����Q ��M����  : ${bend[4]}"
	esCursol 2 11; echo -n "�����R ��M����  : ${bend[5]}"
	esCursol 2 12; echo -n "�����S ��M����  : ${bend[6]}"

	if [[ ${bend[1]} = "0" ]]
	then
		esCursol 2 14; echo -n "�����d�m�c�t���O���X�V���܂����H�iy/n�j"
		viewInput
		read ans
		
		if [[ $ans = [Yy] ]]
		then
			fnSetBunchuEnd
			fnBendView2
		fi
	else
		esCursol 2 14; echo -n "�����d�m�c�t���O�͐ݒ�ς݂ł��B(Enter)"
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

# �r������
sem="/tmp/`basename $0`"
ln -s /$sem.lock $sem || exit
# trap "echo $FIN; db2 terminate; rm $sem; exit 0" 2 3 15
trap "db2 terminate; rm $sem; exit 0" 2 3 15

echo "$ME : �N�� "`date`

# �I�v�V�������`�F�b�N
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

# DB�ڑ�
fnDBConnect $USE_DB $USE_ID $USE_PW

fnBendView

# DB�ؒf
fnDBTerminate

# �r������(��n��)
rm "$sem"

echo "$ME : �I�� "`date`

# echo $FIN

exit 0
