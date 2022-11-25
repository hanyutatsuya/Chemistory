#!/bin/bash -
#######################################################################
#  �ݐρA�W�v�e�[�u����runstat��������
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################

cd /home/kea00sys/shell/cron

db2 CONNECT TO $1 USER $2 USING $3

db2 "select TABNAME from syscat.tables where TABSCHEMA='DB2INST1' and TYPE='T' and ( TABNAME like 'RUI_%' or TABNAME like 'SHU_%') order by TABNAME" | grep ^[RS]  > TBLNM.$$

for TBL in `cat TBLNM.$$`
do
	echo "[`date`][$TBL] runstats start ----->"
	db2 RUNSTATS ON TABLE DB2INST1.$TBL WITH DISTRIBUTION AND DETAILED INDEXES ALL
done

db2 terminate
rm TBLNM.$$

