#!/bin/bash -

for hed in ../src/lib/db/*.h; do
	#echo $hed
	hed1=`echo $hed | colrm 1 14`
	#echo $hed1
	ln -s $hed ./$hed1
done
