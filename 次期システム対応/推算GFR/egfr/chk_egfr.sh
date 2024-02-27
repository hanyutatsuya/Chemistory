#!/bin/bash
# ���ZGFR�����G���[�`�F�b�N���X�g�o��

EXECSTS=0

OUTFILE=/apdata/today/file/list/EGFR_$$.sel
PRTFILE=/apdata/today/file/list/EGFR_$$.txt
TMPFILE=/apdata/today/file/list/EGFR_$$.tmp
SELSQL=/home/kea00sys/shell/egfr/egfrsel.sql
UPDSQL=/home/kea00sys/shell/egfr/egfrupd.sql
AWKFILE=/home/kea00sys/shell/egfr/egfr.awk
#/usr/bin/rm ${OUTFILE}

#db2 connect to kea00db user db2inst1 using db2inst1
db2 connect to kea00db9 user kea00dbt using kea00dbt
if [ $? != 0 ]
then
        echo "DB��login�ł��܂���"
        exit 1
fi

#���oSQL���s
db2 -t -f ${SELSQL} > ${OUTFILE}

db2 terminate

#select�s�݂̂ɂ���
grep AAAAAAAA ${OUTFILE} > ${TMPFILE}

#�X�y�[�X���܂ލ��ږ��̒���
#cat ${TMPFILE} | sed "s/PG 1\/2�/PG1\/2�/g" > ${PRTFILE}
#mv ${PRTFILE} ${TMPFILE}

#�X�y�[�X��1���������ɂ���
for ((i=0; i<20;i++))
do
	cat ${TMPFILE} | sed "s/  / /g" > ${PRTFILE}
	mv ${PRTFILE} ${TMPFILE}
done

#awk�Ő��`
awk -f ${AWKFILE} ${TMPFILE} > ${PRTFILE}
#cp ${TMPFILE} ${PRTFILE}
cat ${PRTFILE}

echo -n "������܂����H(y/n):"
read yn
if [ "${yn}" = "Y" ] || [ "${yn}" = "y" ]; then
	npdl -15 -a4p < ${PRTFILE} | lp -d prt01 |& iconv -f utf8 -t sjis
fi

# �Ώۖ����̎�UPDATE����ƃG���[�ɂȂ�̂ŉ��
if [ -s ${TMPFILE} ]; then

	echo -n "�N���A�`�j���ۗ̕����������܂����H(y/n):"
	read yn
	if [ "${yn}" = "Y" ] || [ "${yn}" = "y" ]; then
#		db2 connect to kea00db user db2inst1 using db2inst1
		db2 connect to kea00db9 user kea00dbt using kea00dbt
		if [ $? != 0 ]
		then
		        echo "DB��login�ł��܂���"
		        exit 1
		fi

		#���oSQL���s
		db2 -t -f ${UPDSQL}
		if [ $? = 0 ]
		then
		        echo "����ɍX�V���܂���"
		else
				echo $?
		fi

		db2 terminate
	fi
fi

exit $EXECSTS
