#
#   �������킹�iKEA00AP�p�j
#
#   2007.11.14 ksuzu
#

#!/bin/sh

# ntpdate �t���p�X
NTPDATE=/usr/local/bin/ntpdate

# NTP�T�[�o
SERVER=10.1.41.65

# hwclock �t���p�X
#HWCLOCK=/sbin/hwclock

# ���O�t�@�C�� �t���p�X
LOGFILE=/home/kea00sys/shell/log/ntpdate.log

# ���s
(${NTPDATE} -b ${SERVER} 2>&1) >> ${LOGFILE}
#${HWCLOCK} --systohc

# ���O����
/usr/bin/tail -50 ${LOGFILE} > ${LOGFILE}.wk
/bin/mv -f ${LOGFILE}.wk ${LOGFILE}

