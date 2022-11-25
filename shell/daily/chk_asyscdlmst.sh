#!/bin/sh
#######################################################################
# アッセイスケジュールマスタ存在チェック
# $1 : DB名
# $2 : ユーザ名
# $3 : パスワード
#######################################################################

db2 connect to $1 user $2 using $3

db2 "select	knsgrp,KJNSRIYMD from knsgmst,sysknrmst \
except \
select	knsgrp,ASYSTARTYMD from	ASYSCDLMST "  \
 | grep "レコードが選択されました" | awk '{print $1}' > $$

CNT=`cat $$`
if [ $CNT -gt 0 ]
then
	echo "アッセイスケジュールマスタの設定を確認して下さい.  "
else
	##echo "ASYSCDLMST CHECK OK"
	echo " "
fi

rm $$

db2 terminate
