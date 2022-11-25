#

while [ 1 ]
do
    echo ""
    echo "AD205(緊急対応)をMAKEします。"
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

echo "★ AD205(緊急対応) Make ★"
echo ""

echo "★ rm *.o *.bnd AD205 ★"
rm *.o *.bnd AD205
echo ""

echo "★ make -f Makefile ★"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
	echo "	AD205"
	echo "	AD205.ini"
	echo "	AD205_SORT.ini"
	echo "	AD205_LOG.ini"
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

echo "★ cp -p AD205 ~/bin/ ★"
cp -p AD205 ~/bin/
echo "★ cp -p AD205.ini ~/bin/ ★"
cp -p AD205.ini ~/bin/
echo "★ cp -p AD205_SORT.ini ~/bin/ ★"
cp -p AD205_SORT.ini ~/bin/
echo "★ cp -p AD205_LOG.ini ~/bin/ ★"
cp -p AD205_LOG.ini ~/bin/
echo ""

echo "★ Make End ★"

