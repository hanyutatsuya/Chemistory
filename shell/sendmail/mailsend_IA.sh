#! /bin/sh
# �}���`����񍐗p�t�@�C���쐬�X�N���v�g
# 2006-12-18 �쐬 sekiya,nagata,kamakura
# 2006-12-18 �C�� sekiya ���M��ύX
# 2021-06-24 #01  smz    ���[�����M��A�h���X���l���烁�[�����O���X�g�֕ύX

# �[���񎟌��z�񏈗��֐�
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

# ��������t�@�C���� ���M���̐��Ɠ������Ƃ邱��
SVR_COUNT=5
# ���M���=( ���M��IP ���[�U�[�� �p�X���[�h ��M���f�B���N�g�� ��M�Ώۃt�@�C���� )
SVR_NO_1=('10.1.181.41' 'KEA00IAW21')
SVR_NO_2=('10.1.181.42' 'KEA00IAW22')
SVR_NO_3=('10.1.181.43' 'KEA00IAW23')
SVR_NO_4=('10.1.181.44' 'KEA00IAW24')
SVR_NO_5=('10.1.181.18' 'KEA00IAW08')


echo "CODE: SJIS" > /tmp/mailapdata
echo "TO: multi_log@bml.co.jp" >> /tmp/mailapdata
echo "SUBJECT: [`date`]�}���`����񍐂`�o���h�`" >> /tmp/mailapdata
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
	IP="$(array2 SVR_NO_ ${ia} 0)"		# ���O�擾��@�h�o
	HOSTNAME="$(array2 SVR_NO_ ${ia} 1)"	# ���O�擾��@�z�X�g��

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
