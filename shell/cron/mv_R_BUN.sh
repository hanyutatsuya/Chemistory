#!/bin/sh
################################################
## /apdata/today/online/host/Recv/bun/SUMI/NG ��
## �o���Ă��܂��� R_BUNYYYYMMDD.dat ����������
## /apdata/today/online/host/Recv/bun/SUMI ��
## move ����
## 
## 2007.05.07  K.Kamakura
################################################

BNGDIR=/apdata/today/online/host/Recv/bun/SUMI/NG
BSMDIR=/apdata/today/online/host/Recv/bun/SUMI
CURDIR=`pwd`

cd $BNGDIR
for FILENAME in `ls R_BUN*`
do
    sleep 5
    MOVENAME=CHK`date +"%Y%m%d%H%M%S"`.dat
    mv -f $BNGDIR/$FILENAME $BSMDIR/$MOVENAME
done 
cd $CURDIR
