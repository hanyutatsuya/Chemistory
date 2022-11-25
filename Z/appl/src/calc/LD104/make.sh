#!/bin/sh

DB_NAME=kea00db
DB_USER=db2inst1
DB_PASS=db2inst1

echo ""
echo "�� LD104(�񍐃t�@�C���쐬) Make ��"
echo ""

echo "�� make -f ./Makefile clean ��"
make -f ./Makefile clean
echo ""

echo "�� sh ./allbind $DB_NAME $DB_USER $DB_PASS ��"
sh allbind $DB_NAME $DB_USER $DB_PASS
echo ""

#echo "�� �o�C���h���̃`�F�b�N�����܂��B ��"
#echo "�� sh /home/kea00sys/work/proc/chk_bind.sh LD104 ��"
#sh /home/kea00sys/work/proc/chk_bind.sh LD104
#echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
	echo "	LD104"
	echo "	LD104.ini"
	echo "	LD104_LOG.ini"
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

echo "�� cp -p LD104 ~/bin/ ��"
cp -p LD104 ~/bin/
echo "�� cp -p LD104.ini ~/bin/ ��"
cp -p LD104.ini ~/bin/
echo "�� cp -p LD104_LOG.ini ~/bin/ ��"
cp -p LD104_LOG.ini ~/bin/
echo ""

echo "�� Make End ��"

