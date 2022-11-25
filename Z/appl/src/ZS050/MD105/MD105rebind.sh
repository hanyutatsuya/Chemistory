#!/bin/bash

################################################################################
#
#	�f�[�^�x�[�X�ڑ�
#
################################################################################
db2 connect to kea00db user db2inst1 using db2inst1

################################################################################
#
#	RUNSTATS���s
#
################################################################################
db2 RUNSTATS ON TABLE DB2INST1.CTRLKKA  WITH DISTRIBUTION and detailed indexes all
db2 RUNSTATS ON TABLE DB2INST1.IRAI     WITH DISTRIBUTION and detailed indexes all
db2 RUNSTATS ON TABLE DB2INST1.KANJYA   WITH DISTRIBUTION and detailed indexes all
db2 RUNSTATS ON TABLE DB2INST1.KEKKA    WITH DISTRIBUTION and detailed indexes all
db2 RUNSTATS ON TABLE DB2INST1.KENORDER WITH DISTRIBUTION and detailed indexes all
db2 RUNSTATS ON TABLE DB2INST1.REALCHK  WITH DISTRIBUTION and detailed indexes all
db2 RUNSTATS ON TABLE DB2INST1.SOUKAN   WITH DISTRIBUTION and detailed indexes all
db2 RUNSTATS ON TABLE DB2INST1.XBARM    WITH DISTRIBUTION and detailed indexes all

################################################################################
#
#	REBIND���s
#
################################################################################

#	DD401�ŗL
db2 rebind 1ZTUNE
db2 rebind 2ZTUNE
db2 rebind 3ZTUNE
db2 rebind 4ZTUNE
db2 rebind 5ZTUNE
db2 rebind 6ZTUNE
db2 rebind 7ZTUNE
db2 rebind 8ZTUNE
db2 rebind DD401_01

#	���ʊ֐�
db2 rebind 15ZCtrl
db2 rebind 25ZIrai
db2 rebind 27ZKanj
db2 rebind 28ZKekk
db2 rebind 30ZKeno
db2 rebind 57ZReal
db2 rebind 65ZSouk
db2 rebind 76ZXbar

################################################################################
#
#	�f�[�^�x�[�X�ؒf
#
################################################################################
db2 terminate
