#!/bin/bash
################################################################################
#
#	�萔��`
#
################################################################################
IA_COM=$HOME/bin/IAcom
IA_STS_FILE=$HOME/shell/daily/IA_STS.txt

PROC_IA_LABO_ID=DD203
PROC_IA_LABO_NYO_ID=DD204
PROC_IA_BIOM_ID=DD201
PROC_IA_HT=(KEA00IAW21.bml.co.jp KEA00IAW22.bml.co.jp KEA00IAW23.bml.co.jp KEA00IAW24.bml.co.jp KEA00IAW02.bml.co.jp)

cat /dev/null > $IA_STS_FILE

################################################################################
# LABO�v���Z�X�󋵎擾
################################################################################
	for i in `seq 0 4`;
	do
		for bsklne in $( $IA_COM ${PROC_IA_HT[$i]} 0 2> /dev/null | awk -v PROC_ID=$PROC_IA_LABO_ID '{if($8==PROC_ID){printf("%d\n",$9)}}' );
		do
#			printf "%s\t%s\t%s\n" ${PROC_IA_HT[$i]} $PROC_IA_LABO_ID $bsklne >> $IA_STS_FILE
			printf "%s %s 1 %s\n" $IA_COM ${PROC_IA_HT[$i]}  $bsklne >> $IA_STS_FILE
		done   
		# �A���ڗp�I�����C���̏󋵎擾��ǉ�
		for bsklne in $( $IA_COM ${PROC_IA_HT[$i]} 0 2> /dev/null | awk -v PROC_ID=$PROC_IA_LABO_NYO_ID '{if($8==PROC_ID){printf("%d\n",$9)}}' );
		do
#			printf "%s\t%s\t%s\n" ${PROC_IA_HT[$i]} $PROC_IA_LABO_ID $bsklne >> $IA_STS_FILE
			printf "%s %s 1 %s\n" $IA_COM ${PROC_IA_HT[$i]}  $bsklne >> $IA_STS_FILE
		done
	done
################################################################################
# BIOM�v���Z�X�󋵎擾
################################################################################
	for i in `seq 0 4`;
	do
		for bsklne in $( $IA_COM ${PROC_IA_HT[$i]} 0 2> /dev/null | awk -v PROC_ID=$PROC_IA_BIOM_ID '{if($8==PROC_ID){printf("%d\n",$9)}}' );
		do
#			printf "%s\t%s\t%s\n" ${PROC_IA_HT[$i]} $PROC_IA_BIOM_ID $bsklne >> $IA_STS_FILE
			printf "%s %s 2 %s\n" $IA_COM ${PROC_IA_HT[$i]}  $bsklne >> $IA_STS_FILE
		done
	done
