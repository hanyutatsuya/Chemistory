#!/bin/sh
#######################################################################
# �V�X�e���Ǘ��}�X�^�X�V
# $1 : ��t��(YYYY-MM-DD)
# $2 : DB��
# $3 : ���[�U��
# $4 : �p�X���[�h
#######################################################################

UTKYMD=$1

db2 connect to $2 user $3 using $4

db2 "UPDATE	SYSKNRMST  \
SET		KJNSRIYMD	='$UTKYMD' \
		,KKKJSRIYMD	='1000-01-01' \
		,IRIENDFLG	='1' \
		,IRIENDDH	='1000-01-01-00.00.00.000001' \
        ,NSKENDFLG  ='1' \
        ,NSKENDDH   ='1000-01-01-00.00.00.000001' \
		,BCHENDFLG	='1' \
		,BCHEND0DH	='1000-01-01-00.00.00.000001' \
		,BCHEND1DH	='1000-01-01-00.00.00.000001' \
		,BCHEND2DH	='1000-01-01-00.00.00.000001' \
		,BCHEND3DH	='1000-01-01-00.00.00.000001' \
		,BCHEND4DH	='1000-01-01-00.00.00.000001' \
		,SSNTUBN	=0 \
		,HNKTNTID	='DAILY' \
		,KSNDH		=CURRENT TIMESTAMP"

db2 terminate
