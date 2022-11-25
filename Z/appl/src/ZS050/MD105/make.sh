#!/bin/sh

DB_NAME=kea00db
DB_USER=db2inst1
DB_PASS=db2inst1

echo "�� MD105(���ʓo�^) Make ��"
echo ""

echo "�� make -f Makefile clean ��"
make -f /home/kea00sys/appl/src/ZS050/MD105/Makefile clean
echo ""

echo "�� sh src/bindall $DB_NAME $DB_USER $DB_PASS ��"
sh bindall $DB_NAME $DB_USER $DB_PASS
echo ""

cd ../

echo "�� make -f Makefile ��"
make -f /home/kea00sys/appl/src/ZS050/MD105/Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
    echo "  MD105"
    echo "  MD105.ini"
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

echo "�� cp -p MD105 ~/bin/ ��"
cp -p /home/kea00sys/appl/src/ZS050/MD105/MD105 ~/bin/

echo "�� cp -p MD105.ini ~/bin/ ��"
cp -p /home/kea00sys/appl/src/ZS050/MD105/MD105.ini ~/bin/
echo ""

echo "�� Make End ��"

