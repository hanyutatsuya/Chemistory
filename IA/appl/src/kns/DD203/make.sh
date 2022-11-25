#!/bin/sh

while [ 1 ]
do
    echo ""
    echo "DD203(オンライン：LABO)をMAKEします。"
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

echo "★ DD203(オンライン：LABO) Make ★"
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
    echo "  /home/kea00sys/appl/src/kns/DD203/src/DD203"
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

echo "★ cp -p /home/kea00sys/appl/src/kns/DD203/src/DD203 ~/bin/ ★"
cp -p /home/kea00sys/appl/src/kns/DD203/src/DD203 ~/bin/
echo ""

echo "★ Make End ★"


