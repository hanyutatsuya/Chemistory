#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

db2 connect to kea00db user db2inst1 using db2inst1
if [ $? -gt 0 ]; then
    exit 1
fi

USERID=""
PASSWD=""
USERNAME=""

while [ 1 ]
do
    echo "登録するユーザーＩＤを入力してください :"
    read ans
    if [ "$ans" ]
    then
        USERID=$ans
		break
    else
        echo "ユーザーＩＤを入力してください。"
        continue
    fi
done

while [ 1 ]
do
    echo "パスワードを入力してください :"
    read ans
    if [ "$ans" ]
    then
        PASSWD=$ans
		break
    else
        echo "パスワードを入力してください。"
        continue
    fi
done

while [ 1 ]
do
    echo "ユーザー名を入力してください :"
    read ans
    if [ "$ans" ]
    then
        USERNAME=$ans
		break
    else
        echo "ユーザー名を入力してください。"
        continue
    fi
done

echo "ユーザーＩＤ[$USERID] パスワード[$PASSWD] ユーザー名[$USERNAME]で登録します。"
echo "よろしいですか(y/n)"

while [ 1 ]
do
    read ans
    if [ "$ans" ]
    then
        if [ $ans = "y" ]
        then
            break
        fi
    fi
done

KJNSRIYMD=$(date +"%Y-%m-%d")

echo $KJNSRIYMD

db2 "INSERT INTO USERMST VALUES('$USERID',' ','$PASSWD','$USERNAME',' ','2099-12-31','2001-01-01-00.00.00.000000','2099-12-31','A ',' ','2099-12-31-12.00.00.000000',' ','2001-01-01','2099-12-31','$KJNSRIYMD','$KJNSRIYMD')"
db2 "INSERT INTO KNOKGNMST VALUES('$USERID','A00','a','a','a','a','a','1','2001-01-01','2099-12-31','$KJNSRIYMD','$KJNSRIYMD')"

db2 terminate

exit 0
