
#######################################################################
#  ���񍐕�KEY�f�[�^INSERT
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
# ---------------------------------------------------------------------
# UPD 2006-09-01 S.Ueda
#     �˗���񒊏o�̏����ɃI�[�_�쐬�t���O�����󔒂�ǉ�
#       ���񍐕��ɖ��������܂߂Ȃ��悤�ɂ��邽��
# add 2007-06-08 INTEC
#		�ً}�Ή��F�ً}���͖������ɗݐςɈڍs���邽�ߑΏۊO�Ƃ���
#		irikbn <> 'K' ��ǉ�
#######################################################################
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 CONNECT TO $1 USER $2 USING $3
if [ $? -gt 0 ]; then
    echo `date`" ERROR : �c�a�ڑ��Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"ins_mhk.log"
    exit 1
fi

echo "[`date`][DAY_MHKKEY] insert start ----->"

db2 "import from /dev/null of del replace into day_mhkkey"
if [ $? -ne 0 ]; then
	echo `date`" ERROR : ���񍐕�KEY�f�[�^�̍폜�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"ins_mhk.log"
	exit 1
fi

db2 "\
insert into day_mhkkey \
select	distinct utkymd, irino, current timestamp \
from \
( \
select  utkymd , irino , kmkcd \
from    irai \
where   irihsmkbn <>'2' \
and		sjflg='0' \
and		odrssflg <> ' ' \
and		irikbn <> 'K' \
EXCEPT \
select  distinct utkymd , irino , kmkcd \
from    kekka \
where   irihsmkbn <>'2' \
and     kkajkcd='3' \
and     knsflg='E' \
and		irikbn <> 'K' \
) daily "
if [ $? -ne 0 -a $? -ne 1 ]; then
	echo `date`" ERROR : ���񍐕�KEY�f�[�^��Insert�Ɏ��s���܂���" >> $LOG_DIR/$NAME_ERRLOG"ins_mhk.log"
    exit 1
fi

db2 terminate

exit 0
