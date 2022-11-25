#!/bin/ksh

new=`echo $1|sed 's/105/205/g'`

echo $1 $new
cat $1|sed -e 's/A105/A205/g' -e 's/AD105/AD205/g' > $new
rm $1

