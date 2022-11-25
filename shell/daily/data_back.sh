#!/bin/sh
#######################################################################
# �t�@�C���̃o�b�N�A�b�v
#######################################################################

BPDIR=$1
bupFile="$BPDIR/Backup_apdata"

mv /apdata/today/file/KEA00/kea00ap/ZS050/*MD101.sav /apdata/aplog/ 
mv /apdata/today/file/KEA00/kea00ap/ZS050/*MD102.sav /apdata/aplog/ 

seq=0
cd /apdata
for i in `cat $HOME/shell/daily/delDir.txt | grep -v ^"#"`
do
	echo "tar cvfz ${bupFile}_$seq.tgz $i"
	tar cvfz ${bupFile}_$seq.tgz $i
	seq=`expr $seq + 1`
done

# �t�����e�B�A����̃��b�N���ޔ��t�@�C�� �o�b�N�A�b�v
bupFile2="$BPDIR/Backup_rackout"
bupDir="/apdata/oldday/rack_out"

echo "tar cvfz ${bupFile2}.tgz bupDir"
tar cvfz ${bupFile2}.tgz ${bupDir}

exit 0
