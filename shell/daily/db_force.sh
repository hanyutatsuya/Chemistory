# �ݐςc�a �A�v���P�[�V�����I���R�}���h���s
db2 attach to IA08 user db2inst1 using db2inst1
db2 force application all
db2 detach

sleep 1

# �����c�a �A�v���P�[�V�����I���R�}���h���s
db2 attach to KEA00DB user db2inst1 using db2inst1
db2 force application all
db2 detach

sleep 1
