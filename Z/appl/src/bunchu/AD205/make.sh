#

while [ 1 ]
do
    echo ""
    echo "AD205(�ً}�Ή�)��MAKE���܂��B"
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

echo "�� AD205(�ً}�Ή�) Make ��"
echo ""

echo "�� rm *.o *.bnd AD205 ��"
rm *.o *.bnd AD205
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
	echo "	AD205"
	echo "	AD205.ini"
	echo "	AD205_SORT.ini"
	echo "	AD205_LOG.ini"
    echo "��낵���ł����H(y/n)==>"
    read ans
    if [ "$ans" ]
    then
        if [ $ans = "y" ]
        then
            break
        else
			echo ""
			echo "�� Make End ��"
            exit 0
        fi
    fi
done

echo "�� cp -p AD205 ~/bin/ ��"
cp -p AD205 ~/bin/
echo "�� cp -p AD205.ini ~/bin/ ��"
cp -p AD205.ini ~/bin/
echo "�� cp -p AD205_SORT.ini ~/bin/ ��"
cp -p AD205_SORT.ini ~/bin/
echo "�� cp -p AD205_LOG.ini ~/bin/ ��"
cp -p AD205_LOG.ini ~/bin/
echo ""

echo "�� Make End ��"

