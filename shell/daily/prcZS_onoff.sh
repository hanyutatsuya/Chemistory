#!/bin/bash
##################################################################
#
# prcZS_onoff.sh yrpvZXN®â~
#
##################################################################
PROC_ZS_ID=(MD101 MD101 MD102 MD102 MD103 MD104 MD105 )
PROC_ZS_INI=(MD101_L1 MD101_L2 MD102_L1 MD102_L2 MD103 MD104 MD105 )
PROC_ZS_NM=(yrICP@ yrICQ@ yrÄ»èP@ yrÄ»èQ@ yrpüg[o^ yrpû[g[o^ yrpÊîño^)
# PROC_ZS_BGÚ× 0:N®µÈ¢,1:N®·é
PROC_ZS_BG=(1 1 1 1 1 1 1)
PROC_ZS_SM=(14001 14006 14002 14007 14003 14004 14005)

EXEC_BIN=$HOME/bin
PEOC_STOP=${EXEC_BIN}/ZD999stop

if [ "$1" = "-START" ]; then
	cd ${EXEC_BIN}

	for i in `seq 0 6`;
	do
		if [ ${PROC_ZS_BG[$i]} != 0 ]; then
			if [ ${PROC_ZS_ID[$i]} = "MD101" ]; then
				${PROC_ZS_ID[$i]} ${EXEC_BIN}/${PROC_ZS_INI[$i]}.ini
			elif [ ${PROC_ZS_ID[$i]} = "MD102" ]; then
				# ö 1 Í debug ÌoÍð}§·étO
				${PROC_ZS_ID[$i]} ${EXEC_BIN}/${PROC_ZS_INI[$i]}.ini 1
			else
				${EXEC_BIN}/${PROC_ZS_ID[$i]} ${EXEC_BIN}/${PROC_ZS_INI[$i]}.ini
			fi
		fi
	done

elif [ "$1" = "-STOP" ]; then
	for i in `seq 0 6`;
	do
		if [ ${PROC_ZS_BG[$i]} != 0 ]; then
			${PEOC_STOP} ${PROC_ZS_SM[$i]}
		fi
	done
fi
