#!/bin/sh

echo ""
echo "★ GD102(ＨＵＬＦＴ送信) Make ★"
echo ""

echo "★ make -f ./Makefile clean ★"
make -f ./Makefile clean
echo ""

echo "★ make -f Makefile ★"
make -f Makefile
echo ""

echo "★ バインド情報のチェックをします。 ★"
echo "★ sh /home/kea00sys/work/proc/chk_bind.sh GD102 ★"
sh /home/kea00sys/work/proc/chk_bind.sh GD102
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
	echo "	GD102"
	echo "	GD102.ini"
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

echo "★ cp -p GD102 ~/bin/ ★"
cp -p GD102 ~/bin/
echo "★ cp -p GD102.ini ~/bin/ ★"
cp -p GD102.ini ~/bin/
echo ""

echo "★ Make End ★"

