#!/bin/bash
# 2006-05-01 �쐬 e.osada
# 2006-06-18 �C�� k.kamakura
while true; do
	clear
	echo ������ �t�@�C���V�X�e���`�F�b�N ������
	echo  " "
	echo �y $HOST �z
	echo �y `date` �z
	echo  " "
	df -k | grep %
	echo  " "
	sleep 10
done
