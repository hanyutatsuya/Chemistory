#
#   時刻合わせ（KEA00AP用）
#
#   2007.11.14 ksuzu
#

#!/bin/sh

# ntpdate フルパス
NTPDATE=/usr/local/bin/ntpdate

# NTPサーバ
SERVER=10.1.41.65

# hwclock フルパス
#HWCLOCK=/sbin/hwclock

# ログファイル フルパス
LOGFILE=/home/kea00sys/shell/log/ntpdate.log

# 実行
(${NTPDATE} -b ${SERVER} 2>&1) >> ${LOGFILE}
#${HWCLOCK} --systohc

# ログ消去
/usr/bin/tail -50 ${LOGFILE} > ${LOGFILE}.wk
/bin/mv -f ${LOGFILE}.wk ${LOGFILE}

