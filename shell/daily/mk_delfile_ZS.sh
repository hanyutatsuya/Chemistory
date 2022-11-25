
#######################################################################
# �I�����C���p�}�X�^del�t�@�C���쐬
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
    exit 1
fi

#	�Ώۃ}�X�^�̈ꗗ�쐬

echo "ctrlmst
ctrlsbtmst
mechmst" > LST.$$

for TBL in `cat LST.$$`
do
	echo "mk_delfile[$TBL][`date`]"
	db2 "export to $TBL.$$ of del messages $TBL.msg select * from $TBL where BSKKBN = 'Z050'"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL �}�X�^�̎擾�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
		exit 1
	fi
	
	cat  $TBL.$$ | sed 's/"//g' $TBL.$$ | sed 's/$//' | sort > $TBL.del
	if [ $? -gt 0 ]; then
		exit 1
	fi
	rm $TBL.$$
done

echo "calckmkmst
kmkmst
knsgmst
krkmkmst
rngchkmst
sysknrmst
xbarmmst" > LST2.$$

for TBL in `cat LST2.$$`
do
	echo "mk_delfile[$TBL][`date`]"
	db2 "export to $TBL.$$ of del messages $TBL.msg select * from $TBL"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL �}�X�^�̎擾�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
		exit 1
	fi
	
	cat  $TBL.$$ | sed 's/"//g' $TBL.$$ | sed 's/$//' | sort > $TBL.del
	if [ $? -gt 0 ]; then
		exit 1
	fi
	rm $TBL.$$
done

# kskbrmst �̍ŏI�J�����Ɏ{�݃R�[�h(�Œ�l�F0000000)��ǉ�����
TBL=kskbrmst
echo "mk_delfile[$TBL][`date`]"
db2 "export to $TBL.$$ of del messages $TBL.msg select tbl.*, '0000000' from $TBL as tbl where BSKKBN = 'Z050'"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : $TBL �}�X�^�̎擾�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
	exit 1
fi

cat  $TBL.$$ | sed 's/"//g' $TBL.$$ | sed 's/$//' | sort > $TBL.del
if [ $? -gt 0 ]; then
	echo `date`" ERROR : $TBL �}�X�^�̎擾�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"mk_delfile.log"
	exit 1
fi
rm $TBL.$$

rm LST.$$ 
rm LST2.$$ 
rm *.msg

db2 terminate

exit 0
