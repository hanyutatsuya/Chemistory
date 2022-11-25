#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

#######################################################################
#  �ݐρA�W�v�e�[�u����runstat��������
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################

cd /home/kea00sys/shell/cron

db2 CONNECT TO kea00dbn USER db2inst1 USING db2inst1

db2 "select TABNAME from syscat.tables where TABSCHEMA='DB2INST1' and TYPE='T' and ( TABNAME like 'RUI_%' or TABNAME like 'SHU_%') order by TABNAME" | grep ^[RS]  > TBLNM.$$

for TBL in `cat TBLNM.$$`
do
	echo "[`date`][$TBL] runstats start ----->"
	db2 RUNSTATS ON TABLE DB2INST1.$TBL WITH DISTRIBUTION AND DETAILED INDEXES ALL
done

db2 terminate

echo "[`date`] �ݐ�runstats end ----->"

rm TBLNM.$$
