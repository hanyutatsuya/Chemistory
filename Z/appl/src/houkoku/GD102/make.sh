#!/bin/sh

echo ""
echo "�� GD102(�g�t�k�e�s���M) Make ��"
echo ""

echo "�� make -f ./Makefile clean ��"
make -f ./Makefile clean
echo ""

echo "�� make -f Makefile ��"
make -f Makefile
echo ""

echo "�� �o�C���h���̃`�F�b�N�����܂��B ��"
echo "�� sh /home/kea00sys/work/proc/chk_bind.sh GD102 ��"
sh /home/kea00sys/work/proc/chk_bind.sh GD102
echo ""

while [ 1 ]
do
    echo ""
    echo "���L�̃t�@�C���� /home/kea00sys/bin �̉��ɃR�s�[���܂��B"
	echo "	GD102"
	echo "	GD102.ini"
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

echo "�� cp -p GD102 ~/bin/ ��"
cp -p GD102 ~/bin/
echo "�� cp -p GD102.ini ~/bin/ ��"
cp -p GD102.ini ~/bin/
echo ""

echo "�� Make End ��"

