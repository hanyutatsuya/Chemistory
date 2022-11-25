#

while [ 1 ]
do
    echo ""
    echo "GD205をMAKEします。"
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

echo "★ GD205 Make ★"
echo ""

echo "★ rm *.o *.bnd GD205 ★"
rm *.o *.bnd GD205
echo ""

echo "★ make -f Makefile ★"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "下記のファイルを /home/kea00sys/bin の下にコピーします。"
	echo "	./GD205"
	echo "	./GD205.ini"
	echo "	./GD205_LOG.ini"
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

echo "★ cp -p GD205 ~/bin/ ★"
cp -p GD205 ~/bin/
echo "★ cp -p GD205.ini ~/bin/ ★"
cp -p GD205.ini ~/bin/
echo "★ cp -p GD205_LOG.ini ~/bin/ ★"
cp -p GD205_LOG.ini ~/bin/

echo ""

ls -ltr GD205
ls -ltr ~/bin/GD205
ls -ltr ~/bin/GD205.ini
ls -ltr ~/bin/GD205_LOG.ini
echo""

echo "★ Make End ★"

