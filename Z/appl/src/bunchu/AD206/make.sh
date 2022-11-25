#

while [ 1 ]
do
    echo ""
    echo "AD206(緊急対応)をMAKEします。"
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

echo "★ AD206(緊急対応) Make ★"
echo ""

echo "★ rm *.o AD206 ★"
rm *.o AD206
echo ""

echo "★ make -f Makefile ★"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記ファイルを /home/kea00sys/bin の下にコピーします。"
	echo "	./AD206"
	echo "	./AD206.ini"
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

echo "★ cp -p AD206 ~/bin/ ★"
cp -p AD206 ~/bin/
echo "★ cp -p AD206.ini ~/bin/ ★"
cp -p AD206.ini ~/bin/
echo ""

echo "★ Make End ★"

