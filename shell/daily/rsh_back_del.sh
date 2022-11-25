#!/bin/sh
###################################################
# リモートシェル起動(ファイルのバックアップ＆削除
###################################################
for ip in `cat $HOME/shell/daily/IAServ.txt | grep -v "#" | grep ^1`
do
#	echo "$HOME/bin/IAcom $ip 4"
	$HOME/bin/IAcom $ip 4 &
done

exit 0
