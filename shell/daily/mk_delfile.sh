
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
kmkmst
knsgmst
mechmst
rngchkmst
sysknrmst
xbarmmst" > LST.$$

for TBL in `cat LST.$$`
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
db2 "export to $TBL.$$ of del messages $TBL.msg select tbl.*, '0000000' from $TBL as tbl"
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
rm *.msg

db2 terminate

exit 0
