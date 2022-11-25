#!/bin/sh

DB_NAME=kea00db
DB_USER=db2inst1
DB_PASS=db2inst1

echo ""
echo "★ LD104(報告ファイル作成) Make ★"
echo ""

echo "★ make -f ./Makefile clean ★"
make -f ./Makefile clean
echo ""

echo "★ sh ./allbind $DB_NAME $DB_USER $DB_PASS ★"
sh allbind $DB_NAME $DB_USER $DB_PASS
echo ""

#echo "★ バインド情報のチェックをします。 ★"
#echo "★ sh /home/kea00sys/work/proc/chk_bind.sh LD104 ★"
#sh /home/kea00sys/work/proc/chk_bind.sh LD104
#echo ""

echo "★ make -f Makefile ★"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
	echo "	LD104"
	echo "	LD104.ini"
	echo "	LD104_LOG.ini"
    echo "よろしいですか？(y/n)==>"
    read ans
    if [ "$ans" ]
    then
        if [ $ans = "y" ]
        then
            break
        else
			echo ""
			echo "★ Make End ★"
            exit 0
        fi
    fi
done

echo "★ cp -p LD104 ~/bin/ ★"
cp -p LD104 ~/bin/
echo "★ cp -p LD104.ini ~/bin/ ★"
cp -p LD104.ini ~/bin/
echo "★ cp -p LD104_LOG.ini ~/bin/ ★"
cp -p LD104_LOG.ini ~/bin/
echo ""

echo "★ Make End ★"

