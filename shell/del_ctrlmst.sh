#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

db2 connect to kea00db user db2inst1 using db2inst1
if [ $? -gt 0 ]; then
    exit 1
fi

BSKKBN=""
NBKMKCD=""
CTRLSBT=""
SYKLOTNO=""

while [ 1 ]
do
    echo "�폜���镪�͋@�敪����͂��Ă�������(BIOM/LABO) :"
    read ans
    if [ "$ans" ]
    then
		if [ $ans = "BIOM" ]
		then
        	BSKKBN=$ans
		elif [ $ans = "LABO" ]
		then
			BSKKBN=$ans
		else
			echo "���������͋@�敪���͂��Ă��������B"
			continue
		fi
		break
    else
        echo "���͋@�敪����͂��Ă��������B"
        continue
    fi
done

while [ 1 ]
do
    echo "�������ڃR�[�h����͂��Ă������� :"
    read ans
    if [ "$ans" ]
    then
        NBKMKCD=$ans
		break
    else
        echo "�������ڃR�[�h����͂��Ă��������B"
        continue
    fi
done

while [ 1 ]
do
    echo "�R���g���[����ʂ���͂��Ă������� :"
    read ans
    if [ "$ans" ]
    then
        CTRLSBT=$ans
		break
    else
        echo "�R���g���[����ʂ���͂��Ă��������B"
        continue
    fi
done

while [ 1 ]
do
    echo "���b�g�m�n����͂��Ă������� :"
    read ans
    if [ "$ans" ]
    then
        SYKLOTNO=$ans
        break
    else
        echo "���b�g�m�n����͂��Ă��������B"
        continue
    fi
done

echo "�R���g���[���}�X�^���ȉ��̏����ō폜���܂��B"
echo "���͋@�敪[$BSKKBN] �p�X���[�h[$NBKMKCD] �R���g���[�����[$CTRLSBT] ���b�g�m�n[$SYKLOTNO]"
echo "��낵���ł���(y/n)"

while [ 1 ]
do
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

db2 "DELETE FROM CTRLMST WHERE BSKKBN = '$BSKKBN' and NBKMKCD = '$NBKMKCD' and CTRLSBT = '$CTRLSBT' and SYKLOTNO = '$SYKLOTNO'"

db2 terminate

exit 0
