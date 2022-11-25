#!/bin/sh

DB_NAME=kea00db
DB_USER=db2inst1
DB_PASS=db2inst1

echo "�� DD401(���ʓo�^) Make ��"
echo ""

echo "�� db2look ��"
sh ./db2look.sh $DB_NAME $DB_USER $DB_PASS
echo ""

echo "�� make -f mak/Makefile clean ��"
make -f mak/Makefile clean
echo ""

cd src/

echo "�� sh src/bindall $DB_NAME $DB_USER $DB_PASS ��"
sh bindall $DB_NAME $DB_USER $DB_PASS
echo ""

cd ../

echo "�� make -f mak/Makefile ��"
make -f mak/Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
    echo "  DD401"
    echo "  DD401.ini"
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

echo "�� cp -p DD401 ~/bin/ ��"
cp -p DD401 ~/bin/

echo "�� cp -p DD401.ini ~/bin/ ��"
cp -p DD401.ini ~/bin/
echo ""

echo "�� Make End ��"

