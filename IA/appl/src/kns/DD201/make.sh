#!/bin/sh

while [ 1 ]
do
    echo ""
    echo "DD201(�I�����C���FBM)��MAKE���܂��B"
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

echo "�� DD201(�I�����C���FBM) Make ��"
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
    echo "  src/DD201"
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

echo "�� cp -p src/DD201 ~/bin/ ��"
cp -p src/DD201 ~/bin/
echo ""

echo "�� Make End ��"


