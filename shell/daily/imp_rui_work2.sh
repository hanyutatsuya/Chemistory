#######################################################################
#  �f�[�^��ݐς�import����( INSERT_UPDATE MODE )(IXF FORMAT)
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################

## �G���[���O�̏o�͐�
LOG_DIR="/apdata/aplog"

## �G���[���O�̃v���t�B�b�N
NAME_ERRLOG="WARNING_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
    exit 1
fi

#	�ݐϑΏۊO�e�[�u���ꗗ
echo "TABNAME
APLLOG
ASYRACKKNRI
AUTOKOSICTRL
BATCHKNRI
BSSIKKA
BSSIZOK
BUNCHU
CHIKENZOK
CTRLKKA
CTRLKNR
DAY_MHKKEY
HKKKNRI
HYJKMK
IRAI
IJYOSYA
KANJYA
KEKKA
KEKKAFREE
KENPOS
KMKBTUTEST
KNKMHMZK
KNKYULOT
KNSSEQKNRI
KNTIDUNKNOWN
LTHKFKLST
REALCHK
RIREKI
SLIDE
SOUKAN
STANDARD
TRAYKNRI
TRRAKHMZK
WSSEQKNRI
XEBSKFLG" > EXC.$$

db2 "select TABNAME from syscat.tables where TABSCHEMA='DB2INST1' and TYPE='T' and ((TABNAME not like '%MST') and (TABNAME not like 'RUI_%') and (TABNAME not like 'SHU_%')) order by TABNAME"  | grep ^[A-Z] | grep -vf EXC.$$ | grep -v ADVISE_ | grep -v EXPLAIN_ > TBLNM.$$
if [ $? -gt 0 ]; then
	echo `date`" ERROR : �ݐ�Table��IMPORT�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
	db2 terminate
	exit 1
fi


for TBL in `cat TBLNM.$$`
do
	echo "[`date`][RUI_$TBL] import start ----->"
	db2 "import from ./$TBL.ixf of ixf allow write access commitcount 20000 messages ./RUI_$TBL.msg INSERT_UPDATE into RUI_$TBL"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL ��IMPORT�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
		db2 terminate
		rm *.$$
		exit 1
	fi
done

# KENPOS INSERT_UPDATE���s�̂��ߕʓr����
for TBL in `echo "KENPOS"`
do
	echo "[`date`][RUI_$TBL] import start ----->"
	db2 "import from ./$TBL.ixf of ixf allow write access commitcount 20000 messages ./RUI_$TBL.msg INSERT into RUI_$TBL"
	if [ $? -gt 0 ]; then
		echo `date`" ERROR : $TBL ��IMPORT�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"imp_rui.log"
		db2 terminate
		rm *.$$
		exit 1
	fi
done

db2 terminate

rm *.$$

exit 0
