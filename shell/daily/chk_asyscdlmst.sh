#!/bin/sh
#######################################################################
# �A�b�Z�C�X�P�W���[���}�X�^���݃`�F�b�N
# $1 : DB��
# $2 : ���[�U��
# $3 : �p�X���[�h
#######################################################################

db2 connect to $1 user $2 using $3

db2 "select	knsgrp,KJNSRIYMD from knsgmst,sysknrmst \
except \
select	knsgrp,ASYSTARTYMD from	ASYSCDLMST "  \
 | grep "���R�[�h���I������܂���" | awk '{print $1}' > $$

CNT=`cat $$`
if [ $CNT -gt 0 ]
then
	echo "�A�b�Z�C�X�P�W���[���}�X�^�̐ݒ���m�F���ĉ�����.  "
else
	##echo "ASYSCDLMST CHECK OK"
	echo " "
fi

rm $$

db2 terminate
