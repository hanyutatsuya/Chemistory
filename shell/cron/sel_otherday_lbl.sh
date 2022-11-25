#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

#######################################################################
# �u�������p 10�A���x���t�@�C���쐬�V�F��
#######################################################################

# DB�ڑ����

DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"
#DBNAME="kea00db9"
#DBUSER="kea00dbt"
#DBPASS="kea00dbt"

# �t�@�C���쐬�V�F���̃t���p�X
SHELL_MAKEFILE="$HOME/shell/cron/make_otherday_lbl.sh"
#SHELL_MAKEFILE="/apdata/work/sekiya/sh/cron/10lbl_kakujitu/make_otherday_lbl.sh"

# ���t�`�F�b�N�V�F���̃t���p�X
SHELL_CHECKDATE="$HOME/shell/daily/checkdate.csh"

#######################################################################
# �P�O�A���x���p�t�@�C�����̎擾
#######################################################################
fnGetFileName() {

	# �P�O�A���x���p�t�@�C�����̎擾
	SPLBLID=`db2 -x "SELECT DISTINCT SPLBLID FROM KNSGMST WHERE KNSGRP = '$2' AND KAIYMD <= '$1' AND HAIYMD >= '$1'"`
	if [ $? -gt 0 ]; then
		echo "�o�̓t�@�C�����̎擾�Ɏ��s���܂����B"
		return 1
	fi

	return 0
}

#######################################################################
# �A�b�Z�C���̎擾
#######################################################################
fnGetKNSYB() {

	# �A�b�Z�C���̎擾
	KNSYB=`db2 -x "SELECT DISTINCT KNSYB FROM KNSGMST WHERE KNSGRP = '$2' AND KAIYMD <= '$1' AND HAIYMD >= '$1'"`
	if [ $? -gt 0 ]; then
		echo "�A�b�Z�C���̎擾�Ɏ��s���܂����B"
		return 1
	fi

	return 0
}

#######################################################################
# ��������̎擾
#######################################################################
fnGetKjnSriymd() {

	# �V�X�e���Ǘ��}�X�^�̊�������̎擾
	SRIYMD=`db2 -x "SELECT KJNSRIYMD FROM SYSKNRMST FOR READ ONLY"`
	if [ $? -gt 0 ]; then
		echo "��������̎擾�Ɏ��s���܂����B"
		return 1
	fi

	return 0
}

#######################################################################
# �����d�m�c���̎擾
#######################################################################
fnGetBCHEND() {

	# �����d�m�c���̎擾
	BCHENDFLG=`db2 -x "SELECT BCHENDFLG FROM SYSKNRMST FOR READ ONLY"`
	if [ $? -gt 0 ]; then
		echo "�����d�m�c���̎擾�Ɏ��s���܂����B"
		return 1
	fi

	if [ ${BCHENDFLG} = "0" ]; then
		echo "�����d�m�c����M���Ă��܂���B�����d�m�c��M��ɍĎ��s���ĉ������B"
		return 1
	fi

	return 0
}

#######################################################################
# ���b�N���̎擾
#######################################################################
fnGetLock() {

	db2 "SELECT * FROM KNSSEQKNRI WHERE KNSKISYMD = '${SRIYMD}' AND KNSGRP = 'KEA00SYS' AND TRAYKBN = 'E' AND WSSBT = 'KEA00SYS' FOR READ ONLY" > /dev/null
	if [ $? -eq 0 ]; then
		echo "�v�r�o�͒��ł��B�I����Ă���ēx���s���ĉ������B"
		return 1
	elif [ $? -eq 1 ]; then
		# ���b�N��񃌃R�[�h���Ȃ������ꍇ�A1 ��Ԃ��B
		return 0
	else
		echo "���b�N���̎擾�Ɏ��s���܂����B"
		return 1
	fi

}

#######################################################################
# ���b�N���̐ݒ�
#######################################################################
fnSetLock() {

	db2 "INSERT INTO KNSSEQKNRI (KNSKISYMD, KNSGRP, TRAYKBN, WSSBT, WSNO, KNSSEQMAX, SYTRYMAX, KSNDH) VALUES ('${SRIYMD}','KEA00SYS','E','KEA00SYS',0,0,0,CURRENT TIMESTAMP)" > /dev/null
	if [ $? -gt 0 ]; then
		echo "���b�N���̐ݒ�Ɏ��s���܂����B"
		return 1
	fi

	return 0
}

#######################################################################
# ���b�N���̍폜
#######################################################################
fnDelLock() {

	db2 "DELETE FROM KNSSEQKNRI WHERE KNSKISYMD = '${SRIYMD}' AND KNSGRP = 'KEA00SYS' AND TRAYKBN = 'E' AND WSSBT = 'KEA00SYS'" > /dev/null
	if [ $? -gt 0 ]; then
		echo "���b�N���̍폜�Ɏ��s���܂����B"
		return 1
	fi

	return 0
}

#######################################################################
# ���C���J�n
#######################################################################

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS} > /dev/null

# �d�m�c���̎擾
fnGetBCHEND
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# ��������̎擾
fnGetKjnSriymd
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# ���������͑҂�
while [ 1 ]
do
	echo "������[${SRIYMD}]�ŏo�͂��܂��B��낵���ł���(y/n)"
	read ANS
	if [ "${ANS}" ]; then
		if [ ${ANS} = "y" ]; then
			break
		fi
	fi

    echo "�Ώۏ���������͂��ĉ������B(YYYYMMDD)"
	read ANS
	if [ "${ANS}" ]; then
		${SHELL_CHECKDATE} ${ANS}
		if [ $? -ne 0 ]; then
			echo "���t�̃t�H�[�}�b�g���قȂ�܂�(YYYYMMDD)"
			echo ""
		else
			YY=`echo ${ANS} | cut -c1-4`
			MM=`echo ${ANS} | cut -c5-6`
			DD=`echo ${ANS} | cut -c7-8`
			SRIYMD=${YY}-${MM}-${DD}
			continue
		fi
	fi

	echo "�o�͂𒆎~���܂����H(y/n)"
	read ANS
	if [ "${ANS}" ]; then
		if [ ${ANS} = "y" ]; then
			db2 terminate > /dev/null
			exit 0
		fi
	fi
done

# �o�͑Ώۓ��͑҂�
while [ 1 ]; do
	echo "�o�͑Ώۂ�I�����ĉ�����"
	echo "1) 3086:�g�|�e�`�a�o"
	echo "2) 3195:�A�f�B�|�l�N�`��"

	read ANS
	case ${ANS} in
		[1])
			KNSGRP="3086"
			break
			;;
		[2])
			KNSGRP="3195"
			break
			;;
		*)
			echo "�o�͂𒆎~���܂����H(y/n)"
			read ANS
			while [ 1 ]; do
				if [ "${ANS}" ]; then
					if [ ${ANS} = "y" ]; then
						db2 terminate > /dev/null
						exit 0
					else
						break
					fi
				fi
			done
	esac
done

# �������̗j�����擾�i1:���j�`7:�y�j�j
WEEK=`date -d "${SRIYMD}" +"%w"`
WEEK=$(( WEEK + 1 ))

# �������̗j���ł̃A�b�Z�C�L���̐ݒ���擾(�����O���[�v�}�X�^)
fnGetKNSYB ${SRIYMD} ${KNSGRP}
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

KNSYB_FLG=`echo ${KNSYB} | cut -c ${WEEK}`
# �A�b�Z�C���������ꍇ�A�x�����o�͂���B
if [ ${KNSYB_FLG} = '1' ]; then
	echo "�{���̓A�b�Z�C���ł����A�o�͂��܂����H(y/n)"
	read ANS
	while [ 1 ]; do
		if [ "${ANS}" ]; then
			if [ ${ANS} = "y" ]; then
				break
			else
				db2 terminate > /dev/null
				exit 0
			fi
		fi
	done
fi

# ���b�N���̎擾
fnGetLock
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# ���b�N���̐ݒ�
fnSetLock
if [ $? -gt 0 ]; then
	fnDelLock
	db2 terminate > /dev/null
	exit 1
fi

fnGetFileName ${SRIYMD} ${KNSGRP}
if [ $? -gt 0 ]; then
	fnDelLock
	db2 terminate > /dev/null
	exit 1
fi

# �t�@�C���o�̓V�F���̋N��
${SHELL_MAKEFILE} ${SRIYMD} ${KNSGRP} ${SPLBLID}
if [ $? -gt 0 ]; then
	fnDelLock
	db2 terminate > /dev/null
	exit 1
fi

# ���b�N���̍폜
fnDelLock
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

echo "�������I�����܂����B"
echo ""

db2 terminate > /dev/null

exit 0
