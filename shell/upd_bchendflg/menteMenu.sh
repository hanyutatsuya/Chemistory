#!/bin/ksh

##############################################################
#
# menteMenu.sh �����e�i���X���j���[�\��
# �ʏ��TeraTerm�}�N������N�������
#
# 2007.03.29 T.Wajima Create
# 2008.08.21 Moriya   �{�ԗp�ɏC��
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

# �r������
sem="/tmp/`basename $0`"
ln -s /$sem.lock $sem || exit
trap "rm $sem; echo $FIN; db2 terminate; exit 0" 2 3 15

viewInput() {
	esCursol 1 19
	echo "                              [Q]�߂�"
	echo "________________________________________________________________________________"
	echo " => "
	echo "________________________________________________________________________________"
	esCursol 5 21
}

while (( 1 ))
do
	clear
	esCursol 1 1;   echo "�����e�i���X���j���["
	esCursol 31 3;  echo "[1]����END�����쐬"
#	esCursol 31 5;  echo "[2]���b�N�o�^���Z�b�g"
	viewInput
	read ans

	if [[ -z $ans ]]
	then
		continue
	fi

	if [[ $ans = [Qq] ]]
	then
		# �r������(��n��)
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
		esMessageBoxEntMax 8 84 "Error:�w�肳�ꂽ�ԍ��������ł�"
		esColor 8
		;;
	esac
done

# �r������(��n��)
rm $sem

echo $FIN

exit 0

