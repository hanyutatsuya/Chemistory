#!/bin/sh
#######################################################################
# ÉtÉ@ÉCÉãÇÃçÌèú
#######################################################################
cd /apdata
for i in `cat $HOME/shell/daily/delDir.txt | grep -v ^"#"`
do
	find $i -type f | xargs rm -f
	find $i -type f ##-exec rm -f {} \;
done
touch /apdata/today/file/pot/potinf.dat
chmod 777 /apdata/today/file/pot/potinf.dat

find /apdata/today/file/shusei/tmp/ -name "S*" -type f -mtime +6 -delete

bupDir="/apdata/oldday/rack_out"
find ${bupDir} -type f | xargs rm -f

exit 0
