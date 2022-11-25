#!/bin/sh

while [ 1 ]
do
    echo ""
    echo "DD201(オンライン：BM)をMAKEします。"
    echo "よろしいですか？(y/n)==>"
    read ans
    if [ "$ans" ]
    then
        if [ $ans = "y" ]
        then
            break
        else
            exit 0
        fi
    fi
done

echo "★ DD201(オンライン：BM) Make ★"
echo ""

echo "★ make -f mak/Makefile clean ★"
make -f mak/Makefile clean
echo ""

echo "★ make -f mak/Makefile ★"
make -f mak/Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
    echo "  src/DD201"
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

echo "★ cp -p src/DD201 ~/bin/ ★"
cp -p src/DD201 ~/bin/
echo ""

echo "★ Make End ★"


