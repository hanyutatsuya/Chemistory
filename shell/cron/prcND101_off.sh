#!/bin/bash
##################################################################
#
# prcND101_off.sh
#
##################################################################
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

export PATH=./:$PATH:/sbin
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/ibm/db2/V11.1/lib64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/ibm/db2/V11.1/lib32

DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"

PROC_STOP="/home/kea00sys/bin/ZD999stop"
PROC_ND101="ND101"
PROC_ND101_SM="15001"

MOTODIR1="/apdata/today/file/rack/OK"
MOTODIR2="/apdata/today/file/rack/SKIP"
SAKIDIR="/apdata/oldday/rack_out"

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS}

# 分注ＥＮＤ情報の取得
BCHENDFLG=`db2 -x "SELECT trim(BCHENDFLG) FROM SYSKNRMST FOR READ ONLY"`
# 分注ＥＮＤ情報の取得に失敗した場合、処理を終了する。
if [ $? -gt 0 ]; then
        exit 0
fi
# 分注ＥＮＤ前だった場合、処理を終了する。
if [ ${BCHENDFLG} = "0" ]; then
        exit 0
fi
sleep 300

# プロセスの停止
${PROC_STOP} ${PROC_ND101_SM}
sleep 10

# ファイルの移動
find  ${MOTODIR1} -type f | xargs -r mv --target-directory=${SAKIDIR}
find  ${MOTODIR2} -type f | xargs -r mv --target-directory=${SAKIDIR}

exit 0
