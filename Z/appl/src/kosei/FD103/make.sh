#

while [ 1 ]
do
    echo ""
    echo "FD103(�����Z��)��MAKE���܂��B"
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

echo "�� FD103(�����Z��) Make ��"
echo ""

echo "�� rm *.o *.bnd FD103 ��"
rm *.o *.bnd FD103
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
	echo "	FD103"
	echo "	FD103.ini"
	echo "	FD103_LOG.ini"
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

echo "�� cp -p FD103 ~/bin/ ��"
cp -p FD103 ~/bin/
echo "�� cp -p FD103.ini ~/bin/ ��"
cp -p FD103.ini ~/bin/
echo "�� cp -p FD103_LOG.ini ~/bin/ ��"
cp -p FD103_LOG.ini ~/bin/
echo ""

echo "�� Make End ��"

