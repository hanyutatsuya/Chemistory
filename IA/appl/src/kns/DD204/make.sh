#!/bin/sh

while [ 1 ]
do
    echo ""
    echo "DD204(�I�����C���FLABO �A)��MAKE���܂��B"
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

echo "�� DD204(�I�����C���FLABO) Make ��"
echo ""

echo "�� make -f mak/Makefile clean ��"
make -f mak/Makefile clean
echo ""

echo "�� make -f mak/Makefile ��"
make -f mak/Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
    echo "  /home/kea00sys/appl/src/kns/DD204/src/DD204"
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

echo "�� cp -p /home/kea00sys/appl/src/kns/DD204/src/DD204 ~/bin/ ��"
cp -p /home/kea00sys/appl/src/kns/DD204/src/DD204 ~/bin/
echo ""

echo "�� Make End ��"


