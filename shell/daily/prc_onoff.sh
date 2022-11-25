
#	PROCESS ON OFF

#-------------------------------------------------------------------
#	$HOME/bin/proc.shから起動・停止に必要な情報、コマンドを取得
#	-> shell　コマンドを編集
#	-> shell　を実行
#-------------------------------------------------------------------

#
#	EDIT
#
#>>>>> START <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
if [ "$1" == "-START" ]
then

#	$HOME/bin/proc.sh から 起動に必要な情報を取得
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
			# バックグラウンドで実行
			nohup \$EXEC_BIN/\${PROC_Z_ID[\$CNT]} \$EXEC_BIN\/\${PROC_Z_ID[\$CNT]}.ini &
			;;
		2)
			# 日次で起動しないもの(緊急など)
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

#	$HOME/bin/proc.sh から 停止に必要な情報を取得

grep "^PEOC_STOP
^EXEC_BIN
^PROC_Z_SM" $HOME/bin/proc.sh > $$

#	停止コマンドの作成
#	一定時間待って切れないものをkill
#	SHM_KEY の削除
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

# 20秒待つ
sleep 20

# まだ終了していないプロセスは強制終了させる
for PG in \`grep ^PROC_Z_ID \$HOME/bin/proc.sh | sed 's/PROC_Z_ID=(//' | sed 's/)//'\`
do
	PGID=\`ps -ef | grep \$PG | grep -v grep | awk '{print \$2}'\`
	if [ \"\$PGID\" != \"\" ]
	then
		echo \"kill \$PG  \$PGID\"
		kill \$PGID
	fi	
done

#SHM_KEY の削除
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
