#!/bin/bash
##################################################################
#
# proc.sh �v���Z�X�N����~
#
# 2007-03-23 Update �i�c BM13���@�ǉ�
#
# 2007-04-23 Update ���q LABO11���@�ALABO12���@�폜
#                   ���q BM  11���@�ABM  12���@�ǉ�
#
# 2007-06-07 Update ���q LABO10���@�폜
#                   ���q BM  10���@�ǉ�
#
# 2008-04-04 Update �牮 �V�t�����e�B�A�Ή�
#                   �牮 �R�h�c��M(AD107)�A�R�h�c�W�J(AD108)�ǉ�
#
# 2008-11-21 Update �牮 �����Z��(FD103)�ǉ�
#
# 2009-01-05 Update �牮 �ً}�֘APG�ǉ�
#
##################################################################
IA_COM="/home/kea00sys/bin/IAcom"
PROC_Z_ID=(AD102 AD103 AD105 AD107 AD108 BD301 BD302 BD401 DD401 FD101 FD103 JD112 GD102 GD105 ZD101 AD202 AD205 GD205)
PROC_Z_NM=(�˗��W�J ���ғW�J �����W�J �R�h�c��M �R�h�c�W�J �����X�g�b�J ����X�g�b�J �T���v�� ���ʓo�^ �Ď��o�b�` �����Z�� �����i�s�󋵏W�v HULFT���M �������ʕ� ���O�o�� �ً}�˗��W�J �ً}�����W�J �ً}���ʕ�)
PROC_Z_ST=(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
# PROC_Z_BG�ڍ�
#  0:�ʏ�N���A1:�o�b�N�O���E���h�N���A2:�����ŋN�����Ȃ�����(�ً}�Ȃ�)
PROC_Z_BG=(1 1 0 0 0 0 0 0 0 1 0 1 1 0 0 2 2 2)
PROC_Z_SM=(5102 5103 5105 5107 5108 6301 6302 6401 7401 9101 9103 11112 10102 10105 12101 5202 5205 10205)

PROC_IA_ID=(DD201 DD203)
PROC_IA_NM=(DD201 DD203)
PROC_IA_HT=(KEA00IAW02.bml.co.jp KEA00IAW03.bml.co.jp KEA00IAW04.bml.co.jp KEA00IAW05.bml.co.jp KEA00IAW06.bml.co.jp KEA00IAW07.bml.co.jp KEA00IAW08.bml.co.jp)

PROC_IA_LB_ST=(0 0 0 0 0 0 0 0 0)
PROC_IA_LB_HT=(0 0 0 0 0 0 0 0 0)
PROC_IA_LB_HT_DEF=(W02 W02 W02 W03 W03 W03 W04 W04 W04)
PROC_IA_LB_SM=(7201 7202 7203 7204 7205 7206 7207 7208 7209)
PROC_IA_BM_ST=(0 0 0 0 0 0 0 0 0)
PROC_IA_BM_HT=(0 0 0 0 0 0 0 0 0)
PROC_IA_BM_HT_DEF=(W05 W05 W05 W07 W06 W06 W06 W07 W07)
PROC_IA_BM_SM=(7210 7211 7212 7213 7221 7222 7223 7224 7225)

PROC_IA_BM_IDX=(10 11 12 13 21 22 23 24 25)

EXEC_BIN=$HOME/bin
PEOC_STOP=$EXEC_BIN/ZD999stop

################################################################################
#
#
################################################################################
msgBoxQ()
{
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[5B\x1b[20C"
	printf "+--------------------------------------+\n"
	printf "\x1b[20C"
	printf "|                                      |\n"
	printf "\x1b[20C"
	printf "|  %-34.34s  |\n" $msgBox_msg01
	printf "\x1b[20C"
	printf "|  %-34.34s  |\n" $msgBox_msg02
	printf "\x1b[20C"
	printf "|  %-34.34s  |\n" $msgBox_msg03
	printf "\x1b[20C"
	printf "|                                      |\n"
	printf "\x1b[20C"
	printf "|  =>                                  |\n"
	printf "\x1b[20C"
	printf "|                                      |\n"
	printf "\x1b[20C"
	printf "+--------------------------------------+\n"
	printf "\x1b[20C"
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[11B\x1b[26C"
	done=false
	while [ $done = false ]; do
		read msgBoxQInput
		case $msgBoxQInput in
			[yY])
				done=true
				msgBoxQKey="Y"
				;;
			[nN])
				done=true
				msgBoxQKey="N"
				;;
			*)
				printf "\x1b[100A\x1b[100D"
				printf "\x1b[11B\x1b[26C"
				;;
		esac
	done
	
}
################################################################################
#
#
################################################################################
msgBoxI()
{
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[5B\x1b[20C"
	printf "+--------------------------------------+\n"
	printf "\x1b[20C"
	printf "|                                      |\n"
	printf "\x1b[20C"
	printf "|  %-34.34s  |\n" $msgBox_msg01
	printf "\x1b[20C"
	printf "|  %-34.34s  |\n" $msgBox_msg02
	printf "\x1b[20C"
	printf "|  %-34.34s  |\n" $msgBox_msg03
	printf "\x1b[20C"
	printf "|  Hit Return Key                      |\n"
	printf "\x1b[20C"
	printf "|                                      |\n"
	printf "\x1b[20C"
	printf "+--------------------------------------+\n"
	printf "\x1b[20C"
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[11B\x1b[26C"
	read 
	
}
################################################################################
#
#
################################################################################
menuDisp()
{
	clear 
	printf "\x1b[1m %s:%s \x1b[0m\n" $MENU_ID $MENU_TITLE
	printf "\n"
	printf "                              %s\n" ${MENU[0]}
	printf "                              %s\n" ${MENU[1]}
	printf "                              %s\n" ${MENU[2]}
	printf "                              %s\n" ${MENU[3]}
	printf "                              %s\n" ${MENU[4]}
	printf "                              %s\n" ${MENU[5]}
	printf "                              %s\n" ${MENU[6]}
	printf "                              %s\n" ${MENU[7]}
	printf "                              %s\n" ${MENU[8]}
	printf "                              %s\n" ${MENU[9]}
	printf "                              %s\n" ${MENU[10]}
	printf "                              %s\n" ${MENU[11]}
	printf "                              %s\n" ${MENU[12]}
	printf "                              %s\n" ${MENU[13]}
	printf "                              %s\n" ${MENU[14]}
	printf "                              %s\n" ${MENU[15]}
	printf "                              %s\n" ${MENU[16]}
	printf "                              %s\n" ${MENU[17]}
	printf "                              %s\n" ${MENU[18]}
	printf "\n" 
	printf "\n" 
	printf "\n" 
	printf "                              %s\n" ${MENU[99]}
	printf "________________________________________________________________________________\n" 
	printf " =>                   \x1b[31m%s\x1b[39m\n" $errMsg 
	printf "________________________________________________________________________________\n" 
}

################################################################################
#
#
################################################################################
menuDisp_FREE()
{
	clear 
	printf "\x1b[1m %s:%s \x1b[0m\n" $MENU_ID $MENU_TITLE
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "\n"
	printf "                              %s\n" ${MENU[99]}
	printf "________________________________________________________________________________\n" 
	printf " =>                   \x1b[31m%s\x1b[39m\n" $errMsg 
	printf "________________________________________________________________________________\n" 
}

################################################################################
#
#
################################################################################
menuInit()
{
	for i in `seq 0 99`;
	do
		MENU[$i]=""
	done

	case $menuPos in
		MAIN)
			MENU_ID=000000
			MENU_TITLE=�v���Z�X�Ď�
			MENU[0]=[1]�ғ���
			MENU[2]=[2]�v���Z�X�N��
			MENU[4]=[3]�v���Z�X��~
			MENU[99]=[Q]�I��
			;;
		SUB01)
			MENU_ID=000100
			MENU_TITLE=�v���Z�X�Ď��|�ғ���
			MENU[0]=[1]�����T�[�o
			MENU[2]=[2]�h�`�T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB0101)
			MENU_ID=000101
			MENU_TITLE=�v���Z�X�Ď��|�ғ��󋵁|�����T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB0102)
			MENU_ID=000102
			MENU_TITLE=�v���Z�X�Ď��|�ғ��󋵁|�h�`�T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB02)
			MENU_ID=000200
			MENU_TITLE=�v���Z�X�Ď��|�v���Z�X�N��
			MENU[0]=[1]�����T�[�o
			MENU[2]=[2]�h�`�T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB0201)
			MENU_ID=000201
			MENU_TITLE=�v���Z�X�Ď��|�v���Z�X�N���|�����T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB0202)
			MENU_ID=000202
			MENU_TITLE=�v���Z�X�Ď��|�v���Z�X�N���|�h�`�T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB03)
			MENU_ID=000300
			MENU_TITLE=�v���Z�X�Ď��|�v���Z�X��~
			MENU[0]=[1]�����T�[�o
			MENU[2]=[2]�h�`�T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB0301)
			MENU_ID=000301
			MENU_TITLE=�v���Z�X�Ď��|�v���Z�X��~�|�����T�[�o
			MENU[99]=[Q]�߂�
			;;
		SUB0302)
			MENU_ID=000302
			MENU_TITLE=�v���Z�X�Ď��|�v���Z�X��~�|�h�`�T�[�o
			MENU[99]=[Q]�߂�
			;;
	esac
}

################################################################################
#
#
################################################################################
fncMenuMain ()
{
	case $inputKey in
		1)
			menuPos=SUB01
			menuInit
			menuDisp
			setPrompt
			;;
		2)
			menuPos=SUB02
			menuInit
			menuDisp
			setPrompt
			;;
		3)
			menuPos=SUB03
			menuInit
			menuDisp
			setPrompt
			;;
		[qQ])
			clear
			exit
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp
			setPrompt
			;;
	esac
}

################################################################################
#
#
################################################################################
fncMenuSub01 ()
{
	case $inputKey in
		1)
			menuPos=SUB0101
			menuInit
			menuDisp_FREE
			procStatusDisp_Z
			setPrompt
			;;
		2)
			menuPos=SUB0102
			menuInit
			menuDisp_FREE
			procStatusDisp_IA
			setPrompt
			;;
		[qQ])
			menuPos=MAIN
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp
			setPrompt
			;;
	esac
}
################################################################################
#
#
################################################################################
fncMenuSub0101 ()
{
	case $inputKey in
		[qQ])
			menuPos=SUB01
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp_FREE
			procStatusDisp_Z
			setPrompt
			;;
	esac
}

################################################################################
#
#
################################################################################
fncMenuSub0102 ()
{
	case $inputKey in
		[qQ])
			menuPos=SUB01
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp_FREE
			procStatusDisp_IA
			setPrompt
			;;
	esac
}

################################################################################
#
#
################################################################################
fncMenuSub02 ()
{
	case $inputKey in
		1)
			menuPos=SUB0201
			menuInit
			menuDisp_FREE
			procExecuteDisp_Z
			setPrompt
			;;
		2)
			menuPos=SUB0202
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
		[qQ])
			menuPos=MAIN
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp
			setPrompt
			;;
	esac
} 
################################################################################
#
#
################################################################################
fncMenuSub0201 ()
{
	case $inputKey in
		[|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|])
			procStatusGet_Z
			if [ ${PROC_Z_ST[$inputKey-1]} != 0 ]; then
				errMsg=���łɋN������Ă��܂�
			else
				msgBox_msg01=${PROC_Z_ID[$inputKey-1]}
				msgBox_msg02='���N�����܂����H'
				msgBox_msg03='(y/n)'
				msgBoxQ	
				if [ $msgBoxQKey = "Y" ]; then

					if [ ${PROC_Z_BG[$inputKey-1]} != 0 ]; then
						$EXEC_BIN/${PROC_Z_ID[$inputKey-1]} $EXEC_BIN/${PROC_Z_ID[$inputKey-1]}.ini &
					else
						$EXEC_BIN/${PROC_Z_ID[$inputKey-1]} $EXEC_BIN/${PROC_Z_ID[$inputKey-1]}.ini
					fi
					if [ ${PROC_Z_ID[$inputKey-1]} = "AD105" ]; then
						$EXEC_BIN/AD106 $EXEC_BIN/AD106.ini
					fi
					if [ ${PROC_Z_ID[$inputKey-1]} = "AD205" ]; then
						$EXEC_BIN/AD206 $EXEC_BIN/AD206.ini
					fi
					errMsg=${PROC_Z_ID[$inputKey-1]}���N�����܂���
				fi
			fi
			menuInit
			menuDisp_FREE
			procExecuteDisp_Z
			setPrompt
			;;
		[qQ])
			menuPos=SUB02
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp_FREE
			procExecuteDisp_Z
			setPrompt
			;;
	esac
}
################################################################################
#
#
################################################################################
fncMenuSub0202 ()
{
	case $inputKey in
		[|10|11|12|13|21|22|23|24|25|])
			procStatusGet_IA
			# BM���@ �� �z��C���f�b�N�X
			let INPUT_BM_GOKI=$inputKey 
			setIndex_BM
			if [ ${PROC_IA_BM_ST[$IDX_BM]} != 0 ]; then
				errMsg=���łɋN������Ă��܂�
			else
				msgBox_msg01="BM-$inputKey���@"
				msgBox_msg02="��KEA00IA${PROC_IA_BM_HT_DEF[$IDX_BM]}.co.jp�ŋN�����܂��B"
				msgBox_msg03='��낵���ł����H(y/n)'
				msgBoxQ	
				if [ $msgBoxQKey = "Y" ]; then
					let GOK=$inputKey
					GOK=`printf "%02d" $GOK`
					$IA_COM KEA00IA${PROC_IA_BM_HT_DEF[$IDX_BM]}.bml.co.jp 2 $GOK 2> /dev/null
					errMsg=�N�����܂���
				fi
			fi
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
		[|1|2|3|4|5|6|7|8|9|])
			if [ ${PROC_IA_LB_ST[$inputKey-1]} != 0 ]; then
				errMsg=���łɋN������Ă��܂�
			else
				msgBox_msg01="LABO-$inputKey���@"
				msgBox_msg02="��KEA00IA${PROC_IA_LB_HT_DEF[$inputKey-1]}.co.jp�ŋN�����܂��B"
				msgBox_msg03='��낵���ł����H(y/n)'
				msgBoxQ	
				if [ $msgBoxQKey = "Y" ]; then
					let GOK=$inputKey
					GOK=`printf "%02d" $GOK`
					$IA_COM KEA00IA${PROC_IA_LB_HT_DEF[$inputKey-1]}.bml.co.jp 1 $GOK 2> /dev/null
					errMsg=�N�����܂���
				fi
			fi
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
		[qQ])
			menuPos=SUB02
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
	esac
}

################################################################################
#
#
################################################################################
fncMenuSub03 ()
{
	case $inputKey in
		1)
			menuPos=SUB0301
			menuInit
			menuDisp_FREE
			procExecuteDisp_Z
			setPrompt
			;;
		2)
			menuPos=SUB0302
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
		[qQ])
			menuPos=MAIN
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp
			setPrompt
			;;
	esac
} 
################################################################################
#
#
################################################################################
fncMenuSub0301 ()
{
	case $inputKey in
		[|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|])
			procStatusGet_Z
			if [ ${PROC_Z_ST[$inputKey-1]} = 0 ]; then
				errMsg=���łɒ�~����Ă��܂�
			else
				msgBox_msg01=${PROC_Z_ID[$inputKey-1]}
				msgBox_msg02='���~���܂����H'
				msgBox_msg03='(y/n)'
				msgBoxQ	
				if [ $msgBoxQKey = "Y" ]; then
					$PEOC_STOP ${PROC_Z_SM[$inputKey-1]}
					if [ ${PROC_Z_ID[$inputKey-1]} = "AD105" ]; then 
						$PEOC_STOP 5106
					fi
					if [ ${PROC_Z_ID[$inputKey-1]} = "AD205" ]; then 
						$PEOC_STOP 5206
					fi
					errMsg=${PROC_Z_ID[$inputKey-1]}���~���܂���
				fi
			fi
			menuInit
			menuDisp_FREE
			procExecuteDisp_Z
			setPrompt
			;;
		[qQ])
			menuPos=SUB03
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp_FREE
			procExecuteDisp_Z
			setPrompt
			;;
	esac
}
################################################################################
#
#
################################################################################
fncMenuSub0302 ()
{
	case $inputKey in
		[|10|11|12|13|21|22|23|24|25|])
			procStatusGet_IA
			# BM���@ �� �z��C���f�b�N�X
			let INPUT_BM_GOKI=$inputKey 
			setIndex_BM
			if [ ${PROC_IA_BM_ST[$IDX_BM]} = 0 ]; then
				errMsg=���łɒ�~����Ă��܂�
			else
				msgBox_msg01="BM-$inputKey���@"
				msgBox_msg02="���~���܂��B"
				msgBox_msg03='��낵���ł����H(y/n)'
				msgBoxQ	
				if [ $msgBoxQKey = "Y" ]; then
					let GOK=$inputKey
					GOK=`printf "%02d" $GOK`
					$IA_COM KEA00IA${PROC_IA_BM_HT_DEF[$IDX_BM]}.bml.co.jp 3 ${PROC_IA_BM_SM[$IDX_BM]} 2> /dev/null
					errMsg=��~���܂���
				fi
			fi
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
		[|1|2|3|4|5|6|7|8|9|])
			if [ ${PROC_IA_LB_ST[$inputKey-1]} = 0 ]; then
				errMsg=���łɒ�~����Ă��܂�
			else
				msgBox_msg01="LABO-$inputKey���@"
				msgBox_msg02="���~���܂��B"
				msgBox_msg03='��낵���ł����H(y/n)'
				msgBoxQ	
				if [ $msgBoxQKey = "Y" ]; then
					let GOK=$inputKey
					GOK=`printf "%02d" $GOK`
					$IA_COM KEA00IA${PROC_IA_LB_HT_DEF[$inputKey-1]}.bml.co.jp 3 ${PROC_IA_LB_SM[$inputKey-1]} 2> /dev/null
					errMsg=��~���܂���
				fi
			fi
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
		[qQ])
			menuPos=SUB03
			menuInit
			menuDisp
			setPrompt
			;;
		*)
			errMsg=��肪����܂�
			menuInit
			menuDisp_FREE
			procExecuteDisp_IA
			setPrompt
			;;
	esac
}
################################################################################
#
#
################################################################################
procStatusGet_Z()
{
	for i in `seq 0 18`;
    do
		PROC_Z_ST[$i]=`ps -e | awk -v PROC_ID=${PROC_Z_ID[$i]} 'BEGIN{STS=0;}{if($4==PROC_ID){STS=1}}END{print STS}'`
	done   
}
################################################################################
#
#
################################################################################
procStatusDisp_Z()
{
	procStatusGet_Z
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[2B\x1b[15C"
    printf "ID         ����                  ���\n"
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[3B\x1b[15C"
    printf "_____________________________________\n"
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[4B\x1b[15C"
	for i in `seq 0 18`;
   	do
		if [ ${PROC_Z_ST[$i]} != 0 ]; then
			printf "%-10.10s %-20.20s  \x1b[32m�ғ�\x1b[37m\n" ${PROC_Z_ID[$i]} ${PROC_Z_NM[$i]}
		else
			printf "%-10.10s %-20.20s  \x1b[31m��~\x1b[37m\n" ${PROC_Z_ID[$i]} ${PROC_Z_NM[$i]}
		fi
		printf "\x1b[%sB\x1b[15C" 3+$i
	done
}
################################################################################
#
#
################################################################################
procStatusGet_IA()
{
	PROC_IA_LB_ST=(0 0 0 0 0 0 0 0 0)
	PROC_IA_LB_HT=(W-- W-- W-- W-- W-- W-- W-- W-- W--)

	PROC_IA_BM_ST=(0 0 0 0 0 0 0 0 0)
	PROC_IA_BM_HT=(W-- W-- W-- W-- W-- W-- W-- W-- W--)

	for i in `seq 0 6`;
    do
		for j in `seq 0 1`;
    	do
			IA_PS_BUF=`$IA_COM ${PROC_IA_HT[$i]} 0 2> /dev/null` 
			if [ $? != 0 ]; then
				PROC_IA_ST[($i*2)+$j]=-1
			else
				if [ $j = 0 ]; then
					for idxBM in $( $IA_COM ${PROC_IA_HT[$i]} 0 2> /dev/null | awk -v PROC_ID=${PROC_IA_ID[$j]} '{if($8==PROC_ID){printf("%d\n",$9)}}' );
					do
						# BM���@ �� �z��C���f�b�N�X
						let INPUT_BM_GOKI=$idxBM 
						setIndex_BM
						PROC_IA_BM_ST[$IDX_BM]=1
						PROC_IA_BM_HT[$IDX_BM]=${PROC_IA_HT[$i]:7:3}
					done
				else
					for idxLB in $( $IA_COM ${PROC_IA_HT[$i]} 0 2> /dev/null | awk -v PROC_ID=${PROC_IA_ID[$j]} '{if($8==PROC_ID){printf("%d\n",$9)}}' );
					do
						PROC_IA_LB_ST[$idxLB-1]=1
						PROC_IA_LB_HT[$idxLB-1]=${PROC_IA_HT[$i]:7:3}
					done
				fi
			fi	
		done   
	done   
}
################################################################################
#
#
################################################################################
procStatusDisp_IA()
{
	procStatusGet_IA
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[2B\x1b[15C"
    printf "���͊�      STS   IA  |���͊�      STS   IA  \n"
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[3B\x1b[15C"
    printf "______________________|______________________\n"
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[4B\x1b[15C"

	for i in `seq 0 8`;
	do
		let no=$i+1
		if [ ${PROC_IA_LB_ST[$i]} != 0 ]; then
			printf "LABO-%02s���@ \x1b[32m�ғ� \x1b[37m %-3.3s |\n" $no ${PROC_IA_LB_HT[$i]}
		else
			printf "LABO-%02s���@ \x1b[31m��~ \x1b[37m %-3.3s |\n" $no ${PROC_IA_LB_HT[$i]}
		fi
		printf "\x1b[%sB\x1b[15C" 3+$i
	done
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[4B\x1b[38C"
	for i in `seq 0 8`;
	do
		let no=${PROC_IA_BM_IDX[$i]}
		if [ ${PROC_IA_BM_ST[$i]} != 0 ]; then
			printf "BM-%02s���@   \x1b[32m�ғ� \x1b[37m %-3.3s\n" $no ${PROC_IA_BM_HT[$i]}
		else
			printf "BM-%02s���@   \x1b[31m��~ \x1b[37m %-3.3s\n" $no ${PROC_IA_BM_HT[$i]}
		fi
		printf "\x1b[%sB\x1b[38C" 3+$i
	done

}
################################################################################
#
#
################################################################################
procExecuteDisp_Z()
{
	procStatusGet_Z
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[2B\x1b[30C"
	for i in `seq 0 18`;
   	do
		let no=$i+1
		if [ ${PROC_Z_ST[$i]} != 0 ]; then
			printf "[%2.2s] \x1b[32m�ғ�\x1b[37m %-10.10s %-20.20s\n" $no ${PROC_Z_ID[$i]} ${PROC_Z_NM[$i]}
		else
			printf "[%2.2s] \x1b[31m��~\x1b[37m %-10.10s %-20.20s\n" $no ${PROC_Z_ID[$i]} ${PROC_Z_NM[$i]}
		fi
		printf "\x1b[%sB\x1b[30C" 3+$i
	done
}
################################################################################
#
#
################################################################################
procExecuteDisp_IA()
{
	procStatusGet_IA
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[3B\x1b[15C"
	for i in `seq 0 8`;
	do
		let no=$i+1
		if [ ${PROC_IA_LB_ST[$i]} != 0 ]; then
			printf "[%2.2s] LABO-%02s���@ \x1b[32m�ғ� \x1b[37m %s  \n" $no $no ${PROC_IA_LB_HT[$i]}
		else
			printf "[%2.2s] LABO-%02s���@ \x1b[31m��~ \x1b[37m %s  \n" $no $no ${PROC_IA_LB_HT[$i]}
		fi
		printf "\x1b[%sB\x1b[15C" 3+$i
	done
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[3B\x1b[43C"
	for i in `seq 0 8`;
	do
		let no=${PROC_IA_BM_IDX[$i]}
		if [ ${PROC_IA_BM_ST[$i]} != 0 ]; then
			printf "[%2.2s] BM-%02s���@   \x1b[32m�ғ� \x1b[37m %-3.3s\n" $no $no ${PROC_IA_BM_HT[$i]}
		else
			printf "[%2.2s] BM-%02s���@   \x1b[31m��~ \x1b[37m %-3.3s\n" $no $no ${PROC_IA_BM_HT[$i]}
		fi
		printf "\x1b[%sB\x1b[43C" 3+$i
	done

}

################################################################################
#
#
################################################################################
setPrompt()
{
	printf "\x1b[100A\x1b[100D"
	printf "\x1b[26B\x1b[4C"
}
################################################################################
#
#
################################################################################
setIndex_BM()
{
	for ix in `seq 0 8`;
	do
		if [ ${PROC_IA_BM_IDX[$ix]} = $INPUT_BM_GOKI ]; then
			let IDX_BM=$ix
			break
		fi
	done
}
################################################################################
#
#
################################################################################

menuPos=MAIN
menuInit
menuDisp 
setPrompt

while true; do
	errMsg=""
	read inputKey 
	case $menuPos in
		MAIN)
			fncMenuMain
			;;
		SUB01)
			fncMenuSub01
			;;
		SUB0101)
			fncMenuSub0101
			;;
		SUB0102)
			fncMenuSub0102
			;;
		SUB02)
			fncMenuSub02
			;;
		SUB0201)
			fncMenuSub0201
			;;
		SUB0202)
			fncMenuSub0202
			;;
		SUB03)
			fncMenuSub03
			;;
		SUB0301)
			fncMenuSub0301
			;;
		SUB0302)
			fncMenuSub0302
			;;
		*)
			errMsg=��肪����܂�
			;;
	esac
done

