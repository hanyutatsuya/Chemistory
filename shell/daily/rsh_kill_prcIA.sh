#!/bin/sh
###################################################
# リモートシェル起動( kill daemon
###################################################
IASHELL=/home/kea00sys/shell/stop_daemon.sh

for ip in `cat $HOME/shell/daily/IAServ.txt | grep -v "#" | grep ^1`
do
	echo "rsh $ip  $IASHELL"
	rsh $ip  $IASHELL
done

exit 0
