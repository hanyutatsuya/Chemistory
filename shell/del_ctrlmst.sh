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
    echo "削除する分析機区分を入力してください(BIOM/LABO) :"
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
			echo "正しい分析機区分入力してください。"
			continue
		fi
		break
    else
        echo "分析機区分を入力してください。"
        continue
    fi
done

while [ 1 ]
do
    echo "内部項目コードを入力してください :"
    read ans
    if [ "$ans" ]
    then
        NBKMKCD=$ans
		break
    else
        echo "内部項目コードを入力してください。"
        continue
    fi
done

while [ 1 ]
do
    echo "コントロール種別を入力してください :"
    read ans
    if [ "$ans" ]
    then
        CTRLSBT=$ans
		break
    else
        echo "コントロール種別を入力してください。"
        continue
    fi
done

while [ 1 ]
do
    echo "ロットＮＯを入力してください :"
    read ans
    if [ "$ans" ]
    then
        SYKLOTNO=$ans
        break
    else
        echo "ロットＮＯを入力してください。"
        continue
    fi
done

echo "コントロールマスタを以下の条件で削除します。"
echo "分析機区分[$BSKKBN] パスワード[$NBKMKCD] コントロール種別[$CTRLSBT] ロットＮＯ[$SYKLOTNO]"
echo "よろしいですか(y/n)"

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
