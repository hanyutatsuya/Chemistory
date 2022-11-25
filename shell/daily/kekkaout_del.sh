#!/bin/sh
#######################################################################
# out�ޔ��f�B���N�g�����t�@�C���̃o�b�N�A�b�v���폜
#######################################################################

BPDIR=$1
bupFile="$BPDIR/Backup_kekkaout"

seq=0
cd /apdata


echo "[`date`][kekka_out] tar cvfz start ----->"

for i in `cat $HOME/shell/daily/delDirkekkaout.txt | grep -v ^"#"`
do
	echo "tar cvfz ${bupFile}_$seq.tgz $i"
	tar cvfz ${bupFile}_$seq.tgz $i
	seq=`expr $seq + 1`
done


echo "[`date`][kekka_out] rm start ----->"

for i in `cat $HOME/shell/daily/delDirkekkaout.txt | grep -v ^"#"`
do
##	find $i -type f
    find $i -type f -exec rm -f {} \;
done

exit 0
