#! /bin/sh
# マルチ定期報告用ファイル作成スクリプト
# 2006-12-18 作成 sekiya,nagata,kamakura
# 2006-12-18 修正 sekiya 送信先変更
# 2021-06-24 #01  smz    メール送信先アドレスを個人からメーリングリストへ変更

# 擬似二次元配列処理関数
array2()
{
    eval y='${'$1$2'['$3']}'
    echo $y
}

if  [ -e /tmp/mailapdata ]; then
	FILE_DATE=`ls -l --time-style="+%Y%m%d%H%M%S" /tmp/mailapdata | awk '{print $6; }'`
	mv /tmp/mailapdata /tmp/mailapdata.${FILE_DATE}
	gzip /tmp/mailapdata.${FILE_DATE}
fi

# 処理するファイル数 送信情報の数と同期をとること
SVR_COUNT=5
# 送信情報=( 送信先IP ユーザー名 パスワード 受信元ディレクトリ 受信対象ファイル名 )
SVR_NO_1=('10.1.181.41' 'KEA00IAW21')
SVR_NO_2=('10.1.181.42' 'KEA00IAW22')
SVR_NO_3=('10.1.181.43' 'KEA00IAW23')
SVR_NO_4=('10.1.181.44' 'KEA00IAW24')
SVR_NO_5=('10.1.181.18' 'KEA00IAW08')


echo "CODE: SJIS" > /tmp/mailapdata
echo "TO: multi_log@bml.co.jp" >> /tmp/mailapdata
echo "SUBJECT: [`date`]マルチ定期報告ＡＰ＆ＩＡ" >> /tmp/mailapdata
echo "BODY: " >> /tmp/mailapdata

echo "********** kea00apa **********" >> /tmp/mailapdata
echo " --- memory ----" >> /tmp/mailapdata
free >> /tmp/mailapdata
echo " " >> /tmp/mailapdata
echo " --- load average ----" >> /tmp/mailapdata
w >> /tmp/mailapdata
echo " " >> /tmp/mailapdata
echo "--- disk space ---" >> /tmp/mailapdata
df -k | grep % >> /tmp/mailapdata
echo " " >> /tmp/mailapdata
echo "--- Messages ---" >> /tmp/mailapdata
tail -10000 /var/log/messages | grep -v vsftpd | grep -v sshd | grep -v MARK | grep -v CRON | grep -v cron | grep -v systemd | grep -v liblogging-stdlog | grep -v smbd | grep -v hulft>> /tmp/mailapdata
echo " " >> /tmp/mailapdata
echo "--- end ---" >> /tmp/mailapdata
echo " " >> /tmp/mailapdata

for ia in `seq 1 ${SVR_COUNT}`
do
	IP="$(array2 SVR_NO_ ${ia} 0)"		# ログ取得先　ＩＰ
	HOSTNAME="$(array2 SVR_NO_ ${ia} 1)"	# ログ取得先　ホスト名

	echo "********** ${HOSTNAME} **********" >> /tmp/mailapdata
	echo " --- memory ----" >> /tmp/mailapdata
	rsh ${IP} -l kea00sys free | iconv -f=EUC-JP -t=SHIFT_JIS >> /tmp/mailapdata
	echo " " >> /tmp/mailapdata
	echo " --- load average ----" >> /tmp/mailapdata
	rsh ${IP} -l kea00sys w | iconv -f=EUC-JP -t=SHIFT_JIS >> /tmp/mailapdata
	echo "--- disk space ---" >> /tmp/mailapdata
	rsh ${IP} -l kea00sys df -k | grep % | iconv -f=EUC-JP -t=SHIFT_JIS >> /tmp/mailapdata
	echo "--- Messages ---" >> /tmp/mailapdata
	rsh ${IP} -l kea00sys 'sudo /home/kea00sys/shell/messages.sh' | iconv -c -f=EUC-JP -t=SHIFT_JIS >> /tmp/mailapdata
	echo "--- end ---" >> /tmp/mailapdata
	echo " " >> /tmp/mailapdata
done
echo "--- AP&IA check all end ---" >> /tmp/mailapdata
