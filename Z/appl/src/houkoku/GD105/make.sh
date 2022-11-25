#!/bin/sh

DB_NAME=kea00db
DB_USER=db2inst1
DB_PASS=db2inst1

echo ""
echo "�� GD105(�񍐃t�@�C���쐬) Make ��"
echo ""

echo "�� make -f ./Makefile clean ��"
make -f ./Makefile clean
echo ""

echo "�� sh ./allbind $DB_NAME $DB_USER $DB_PASS ��"
sh allbind $DB_NAME $DB_USER $DB_PASS
echo ""

echo "�� �o�C���h���̃`�F�b�N�����܂��B ��"
echo "�� sh /home/kea00sys/work/proc/chk_bind.sh GD105 ��"
sh /home/kea00sys/work/proc/chk_bind.sh GD105
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
	echo "	GD105"
	echo "	GD105.ini"
	echo "	GD105_LOG.ini"
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

echo "�� cp -p GD105 ~/bin/ ��"
cp -p GD105 ~/bin/
echo "�� cp -p GD105.ini ~/bin/ ��"
cp -p GD105.ini ~/bin/
echo "�� cp -p GD105_LOG.ini ~/bin/ ��"
cp -p GD105_LOG.ini ~/bin/
echo ""

echo "�� Make End ��"

