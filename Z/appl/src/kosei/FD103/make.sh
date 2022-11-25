#

while [ 1 ]
do
    echo ""
    echo "FD103(自動校正)をMAKEします。"
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

echo "★ FD103(自動校正) Make ★"
echo ""

echo "★ rm *.o *.bnd FD103 ★"
rm *.o *.bnd FD103
echo ""

echo "★ make -f Makefile ★"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
	echo "	FD103"
	echo "	FD103.ini"
	echo "	FD103_LOG.ini"
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

echo "★ cp -p FD103 ~/bin/ ★"
cp -p FD103 ~/bin/
echo "★ cp -p FD103.ini ~/bin/ ★"
cp -p FD103.ini ~/bin/
echo "★ cp -p FD103_LOG.ini ~/bin/ ★"
cp -p FD103_LOG.ini ~/bin/
echo ""

echo "★ Make End ★"

