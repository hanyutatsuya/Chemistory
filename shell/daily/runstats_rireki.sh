#######################################################################
#  �����e�[�u����runstat��������
# $1 : DB��
# $2 : ���[�UID(DB2)
# $3 : �p�X���[�h(DB2)
#######################################################################

db2 CONNECT TO $1 USER $2 USING $3

echo "[`date`][RIREKI] runstats start ----->"
db2 RUNSTATS ON TABLE DB2INST1.RIREKI WITH DISTRIBUTION and detailed indexes all;

db2 terminate
