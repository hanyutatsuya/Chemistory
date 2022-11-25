
#	PROCESS ON OFF

#-------------------------------------------------------------------
#	$HOME/bin/proc.sh����N���E��~�ɕK�v�ȏ��A�R�}���h���擾
#	-> shell�@�R�}���h��ҏW
#	-> shell�@�����s
#-------------------------------------------------------------------

#
#	EDIT
#
#>>>>> START <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
if [ "$1" == "-START" ]
then

#	$HOME/bin/proc.sh ���� �N���ɕK�v�ȏ����擾
grep "^PROC_Z_BG
^EXEC_BIN
^PROC_Z_ID" $HOME/bin/proc.sh > $$

echo "
CNT=0
while true
do
	if [ \$CNT -ge 23 ]
	then
		break;
	fi

	if [ \"\${PROC_Z_ID[\$CNT]}\" == \"XXXXX\" ]
	then
		CNT=\`expr \$CNT + 1\`
	fi

	case \${PROC_Z_BG[\$CNT]} in
		0)
			# 
			\$EXEC_BIN/\${PROC_Z_ID[\$CNT]} \$EXEC_BIN\/\${PROC_Z_ID[\$CNT]}.ini
			;;
		1)
			# �o�b�N�O���E���h�Ŏ��s
			nohup \$EXEC_BIN/\${PROC_Z_ID[\$CNT]} \$EXEC_BIN\/\${PROC_Z_ID[\$CNT]}.ini &
			;;
		2)
			# �����ŋN�����Ȃ�����(�ً}�Ȃ�)
			;;
		*)
			;;
	esac

	if [ \"\${PROC_Z_ID[\$CNT]}\" == \"AD105\" ]
	then
		\$EXEC_BIN/AD106 \$EXEC_BIN/AD106.ini
	fi

	if [ \"\${PROC_Z_ID[\$CNT]}\" == \"AD205\" ] && [ \${PROC_Z_BG[\$CNT]} != 2 ]
	then
		\$EXEC_BIN/AD206 \$EXEC_BIN/AD206.ini
	fi

	CNT=\`expr \$CNT + 1\`
done

" >> $$

fi
#>>>>> START <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#<<<<< STOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
if [ "$1" == "-STOP" ]
then

#	$HOME/bin/proc.sh ���� ��~�ɕK�v�ȏ����擾

grep "^PEOC_STOP
^EXEC_BIN
^PROC_Z_SM" $HOME/bin/proc.sh > $$

#	��~�R�}���h�̍쐬
#	��莞�ԑ҂��Đ؂�Ȃ����̂�kill
#	SHM_KEY �̍폜
echo "
CNT=0
while true
do
	if [ \$CNT -ge 23 ]
	then
		break;
	fi

	\$PEOC_STOP \${PROC_Z_SM[\$CNT]}

	if [ \"\${PROC_Z_SM[\$CNT]}\" == \"5105\" ]
	then
		\$PEOC_STOP 5106
	fi

	if [ \"\${PROC_Z_SM[\$CNT]}\" == \"5205\" ]
	then
		\$PEOC_STOP 5206
	fi

	CNT=\`expr \$CNT + 1\`
done

# 20�b�҂�
sleep 20

# �܂��I�����Ă��Ȃ��v���Z�X�͋����I��������
for PG in \`grep ^PROC_Z_ID \$HOME/bin/proc.sh | sed 's/PROC_Z_ID=(//' | sed 's/)//'\`
do
	PGID=\`ps -ef | grep \$PG | grep -v grep | awk '{print \$2}'\`
	if [ \"\$PGID\" != \"\" ]
	then
		echo \"kill \$PG  \$PGID\"
		kill \$PGID
	fi	
done

#SHM_KEY �̍폜
CNT=0
while true
do
	if [ \$CNT -ge 23 ]
	then
		break;
	fi
	if [ \"\${PROC_Z_SM[\$CNT]}\" == \"FB103\" ]
	then
		CNT=\`expr \$CNT + 1\`
	fi

	ipcrm -M \${PROC_Z_SM[\$CNT]}  2> /dev/null

	if [ \"\${PROC_Z_SM[\$CNT]}\" == \"5105\" ]
	then
		ipcrm -M 5106 2> /dev/null
	fi

	if [ \"\${PROC_Z_SM[\$CNT]}\" == \"5205\" ]
	then
		ipcrm -M 5206 2> /dev/null
	fi

	CNT=\`expr \$CNT + 1\`
done

" >> $$

fi
#<<<<< STOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

cat $$

#
#	EXECUTE
#
sh $$

rm $$
