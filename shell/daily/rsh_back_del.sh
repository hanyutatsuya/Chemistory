#!/bin/sh
###################################################
# �����[�g�V�F���N��(�t�@�C���̃o�b�N�A�b�v���폜
###################################################
for ip in `cat $HOME/shell/daily/IAServ.txt | grep -v "#" | grep ^1`
do
#	echo "$HOME/bin/IAcom $ip 4"
	$HOME/bin/IAcom $ip 4 &
done

exit 0
