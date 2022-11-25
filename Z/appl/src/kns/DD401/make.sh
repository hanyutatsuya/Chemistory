#!/bin/sh

DB_NAME=kea00db
DB_USER=db2inst1
DB_PASS=db2inst1

echo "★ DD401(結果登録) Make ★"
echo ""

echo "★ db2look ★"
sh ./db2look.sh $DB_NAME $DB_USER $DB_PASS
echo ""

echo "★ make -f mak/Makefile clean ★"
make -f mak/Makefile clean
echo ""

cd src/

echo "★ sh src/bindall $DB_NAME $DB_USER $DB_PASS ★"
sh bindall $DB_NAME $DB_USER $DB_PASS
echo ""

cd ../

echo "★ make -f mak/Makefile ★"
make -f mak/Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
    echo "  DD401"
    echo "  DD401.ini"
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

echo "★ cp -p DD401 ~/bin/ ★"
cp -p DD401 ~/bin/

echo "★ cp -p DD401.ini ~/bin/ ★"
cp -p DD401.ini ~/bin/
echo ""

echo "★ Make End ★"

