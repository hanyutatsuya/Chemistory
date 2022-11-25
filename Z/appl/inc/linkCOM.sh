#!/bin/bash -

for hed in ../src/lib/common/*.h; do
	#echo $hed
	hed1=`echo $hed | colrm 1 18`
	#echo $hed1
	ln -s $hed ./$hed1
done
