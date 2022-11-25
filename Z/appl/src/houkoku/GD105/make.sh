#!/bin/sh

DB_NAME=kea00db
DB_USER=db2inst1
DB_PASS=db2inst1

echo ""
echo "★ GD105(報告ファイル作成) Make ★"
echo ""

echo "★ make -f ./Makefile clean ★"
make -f ./Makefile clean
echo ""

echo "★ sh ./allbind $DB_NAME $DB_USER $DB_PASS ★"
sh allbind $DB_NAME $DB_USER $DB_PASS
echo ""

echo "★ バインド情報のチェックをします。 ★"
echo "★ sh /home/kea00sys/work/proc/chk_bind.sh GD105 ★"
sh /home/kea00sys/work/proc/chk_bind.sh GD105
echo ""

echo "★ make -f Makefile ★"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
	echo "	GD105"
	echo "	GD105.ini"
	echo "	GD105_LOG.ini"
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

echo "★ cp -p GD105 ~/bin/ ★"
cp -p GD105 ~/bin/
echo "★ cp -p GD105.ini ~/bin/ ★"
cp -p GD105.ini ~/bin/
echo "★ cp -p GD105_LOG.ini ~/bin/ ★"
cp -p GD105_LOG.ini ~/bin/
echo ""

echo "★ Make End ★"

