#

while [ 1 ]
do
    echo ""
    echo "AD206(�ً}�Ή�)��MAKE���܂��B"
    echo "��낵���ł����H(y/n)==>"
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

echo "�� AD206(�ً}�Ή�) Make ��"
echo ""

echo "�� rm *.o AD206 ��"
rm *.o AD206
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
	echo "	./AD206"
	echo "	./AD206.ini"
    echo "��낵���ł����H(y/n)==>"
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

echo "�� cp -p AD206 ~/bin/ ��"
cp -p AD206 ~/bin/
echo "�� cp -p AD206.ini ~/bin/ ��"
cp -p AD206.ini ~/bin/
echo ""

echo "�� Make End ��"

