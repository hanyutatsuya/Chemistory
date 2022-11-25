#!/bin/bash
# 2006-05-01 作成 e.osada
# 2006-06-18 修正 k.kamakura
while true; do
	clear
	echo □□□ ファイルシステムチェック □□□
	echo  " "
	echo 【 $HOST 】
	echo 【 `date` 】
	echo  " "
	df -k | grep %
	echo  " "
	sleep 10
done
