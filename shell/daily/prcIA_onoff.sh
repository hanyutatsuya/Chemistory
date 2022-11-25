
#	PROCESS ON OFF

#-------------------------------------------------------------------
#	$HOME/bin/proc.sh����N���E��~�ɕK�v�ȏ��A�R�}���h���擾
#	-> shell�@�R�}���h��ҏW
#	-> shell�@�����s
#
# UPD 2007-03-26 Nagata   BM13���@
# UPD 2007-04-23 Kamakura BM11���@ BM12���@
# DEL 2007-04-23 Kamakura LB11���@ LB12���@
# UPD 2007-06-07 Kamakura BM10���@
# DEL 2007-06-07 Kamakura LB10���@
# UPD 2014-06-11 Sekiya   BM26���@
#-------------------------------------------------------------------

#
#	EDIT
#
#>>>>> START <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
if [ "$1" == "-START" ]
then

#	$HOME/bin/proc.sh ���� �N���ɕK�v�ȏ����擾
grep "^IA_COM
^PROC_IA_BM_HT_DEF
^PROC_IA_LB_HT_DEF" $HOME/bin/proc.sh > $$

echo "

idx=0
for inputKey in 10 11 12 13 21 22 23 24 25 31 32 33
do
	let GOK=\$inputKey
######################## ADD STA
IA_STS=\$HOME/shell/daily/IA_STS.txt
IA_KNQ=/tmp/IA_KNQ.txt
	ARU=0
    if [ -f \$IA_STS ]
    then
        for QGOK in \`cat \$IA_STS | awk '{print \$4}'\`
        do
            if [ \"\$QGOK\" == \"\$GOK\" ]
            then
                ARU=1
                break;
            fi
        done
    fi
    if [ \$ARU -eq 0 ]
    then
        echo \"BM   \${GOK} ���@�ً͋}�g�p���Ɣ��f���AO/L���N�����܂���\" >> \$IA_KNQ
        idx=\`expr \$idx + 1\`
        continue;
    fi
######################## ADD END
	GOK=\`printf "%02d" \$GOK\`
	\$IA_COM KEA00IA\${PROC_IA_BM_HT_DEF[\$idx]}.bml.co.jp 2 \$GOK 2> /dev/null

    idx=\`expr \$idx + 1\`
done
" >> $$

echo "
inputKey=1
while true
do
	if [ \$inputKey -gt 9 ]
	then
		break;
	fi
	let GOK=\$inputKey
########## ADD STA
	ARU=0
    if [ -f \$IA_STS ]
    then
        for QGOK in \`cat \$IA_STS | awk '{print \$4}'\`
        do
            if [ \"\$QGOK\" == \"\$GOK\" ]
            then
                ARU=1
                break;
            fi
        done
    fi
    if [ \$ARU -eq 0 ]
    then
        echo \"LABO \${GOK} ���@�ً͋}�g�p���Ɣ��f���AO/L���N�����܂���\" >> \$IA_KNQ
        inputKey=\`expr \$inputKey + 1\`
        continue;
    fi
	
############# ADD END
	GOK=\`printf "%02d" \$GOK\`
	\$IA_COM KEA00IA\${PROC_IA_LB_HT_DEF[\$inputKey-1]}.bml.co.jp 1 \$GOK 2> /dev/null
	inputKey=\`expr \$inputKey + 1\`
done
" >> $$

fi
#>>>>> START <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#<<<<< STOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
if [ "$1" == "-STOP" ]
then

#	$HOME/bin/proc.sh ���� ��~�ɕK�v�ȏ����擾


grep "^IA_COM
^PROC_IA_BM_HT
^PROC_IA_BM_SM
^PROC_IA_LB_HT
^PROC_IA_LB_SM" $HOME/bin/proc.sh > $$

echo "
idx=0
for inputKey in 10 11 12 13 21 22 23 24 25 31 32 33
do
	let GOK=\$inputKey
	GOK=\`printf "%02d" \$GOK\`
	\$IA_COM KEA00IA\${PROC_IA_BM_HT_DEF[\$idx]}.bml.co.jp 3 \${PROC_IA_BM_SM[\$idx]} 2> /dev/null
	idx=\`expr \$idx + 1\`
done
" >> $$

echo "
inputKey=1
while true
do
	if [ \$inputKey -gt 9 ]
	then
		break;
	fi
	let GOK=\$inputKey
	GOK=\`printf "%02d" \$GOK\`
	\$IA_COM KEA00IA\${PROC_IA_LB_HT_DEF[\$inputKey-1]}.bml.co.jp 3 \${PROC_IA_LB_SM[\$inputKey-1]} 2> /dev/null
	inputKey=\`expr \$inputKey + 1\`
done
" >> $$

fi
#<<<<< STOP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

##cat $$

#
#	EXECUTE
#
sh $$

rm $$
