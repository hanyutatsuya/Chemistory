#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

#######################################################################
# 隔日検査用 10連ラベルファイル作成シェル
#######################################################################

# DB接続情報

DBNAME="kea00db"
DBUSER="db2inst1"
DBPASS="db2inst1"
#DBNAME="kea00db9"
#DBUSER="kea00dbt"
#DBPASS="kea00dbt"

# ファイル作成シェルのフルパス
SHELL_MAKEFILE="$HOME/shell/cron/make_otherday_lbl.sh"
#SHELL_MAKEFILE="/apdata/work/sekiya/sh/cron/10lbl_kakujitu/make_otherday_lbl.sh"

# 日付チェックシェルのフルパス
SHELL_CHECKDATE="$HOME/shell/daily/checkdate.csh"

#######################################################################
# １０連ラベル用ファイル名の取得
#######################################################################
fnGetFileName() {

	# １０連ラベル用ファイル名の取得
	SPLBLID=`db2 -x "SELECT DISTINCT SPLBLID FROM KNSGMST WHERE KNSGRP = '$2' AND KAIYMD <= '$1' AND HAIYMD >= '$1'"`
	if [ $? -gt 0 ]; then
		echo "出力ファイル名の取得に失敗しました。"
		return 1
	fi

	return 0
}

#######################################################################
# アッセイ日の取得
#######################################################################
fnGetKNSYB() {

	# アッセイ日の取得
	KNSYB=`db2 -x "SELECT DISTINCT KNSYB FROM KNSGMST WHERE KNSGRP = '$2' AND KAIYMD <= '$1' AND HAIYMD >= '$1'"`
	if [ $? -gt 0 ]; then
		echo "アッセイ日の取得に失敗しました。"
		return 1
	fi

	return 0
}

#######################################################################
# 基準処理日の取得
#######################################################################
fnGetKjnSriymd() {

	# システム管理マスタの基準処理日の取得
	SRIYMD=`db2 -x "SELECT KJNSRIYMD FROM SYSKNRMST FOR READ ONLY"`
	if [ $? -gt 0 ]; then
		echo "基準処理日の取得に失敗しました。"
		return 1
	fi

	return 0
}

#######################################################################
# 分注ＥＮＤ情報の取得
#######################################################################
fnGetBCHEND() {

	# 分注ＥＮＤ情報の取得
	BCHENDFLG=`db2 -x "SELECT BCHENDFLG FROM SYSKNRMST FOR READ ONLY"`
	if [ $? -gt 0 ]; then
		echo "分注ＥＮＤ情報の取得に失敗しました。"
		return 1
	fi

	if [ ${BCHENDFLG} = "0" ]; then
		echo "分注ＥＮＤを受信していません。分注ＥＮＤ受信後に再実行して下さい。"
		return 1
	fi

	return 0
}

#######################################################################
# ロック情報の取得
#######################################################################
fnGetLock() {

	db2 "SELECT * FROM KNSSEQKNRI WHERE KNSKISYMD = '${SRIYMD}' AND KNSGRP = 'KEA00SYS' AND TRAYKBN = 'E' AND WSSBT = 'KEA00SYS' FOR READ ONLY" > /dev/null
	if [ $? -eq 0 ]; then
		echo "ＷＳ出力中です。終わってから再度実行して下さい。"
		return 1
	elif [ $? -eq 1 ]; then
		# ロック情報レコードがなかった場合、1 を返す。
		return 0
	else
		echo "ロック情報の取得に失敗しました。"
		return 1
	fi

}

#######################################################################
# ロック情報の設定
#######################################################################
fnSetLock() {

	db2 "INSERT INTO KNSSEQKNRI (KNSKISYMD, KNSGRP, TRAYKBN, WSSBT, WSNO, KNSSEQMAX, SYTRYMAX, KSNDH) VALUES ('${SRIYMD}','KEA00SYS','E','KEA00SYS',0,0,0,CURRENT TIMESTAMP)" > /dev/null
	if [ $? -gt 0 ]; then
		echo "ロック情報の設定に失敗しました。"
		return 1
	fi

	return 0
}

#######################################################################
# ロック情報の削除
#######################################################################
fnDelLock() {

	db2 "DELETE FROM KNSSEQKNRI WHERE KNSKISYMD = '${SRIYMD}' AND KNSGRP = 'KEA00SYS' AND TRAYKBN = 'E' AND WSSBT = 'KEA00SYS'" > /dev/null
	if [ $? -gt 0 ]; then
		echo "ロック情報の削除に失敗しました。"
		return 1
	fi

	return 0
}

#######################################################################
# メイン開始
#######################################################################

db2 connect to ${DBNAME} user ${DBUSER} using ${DBPASS} > /dev/null

# ＥＮＤ情報の取得
fnGetBCHEND
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# 基準処理日の取得
fnGetKjnSriymd
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# 処理日入力待ち
while [ 1 ]
do
	echo "処理日[${SRIYMD}]で出力します。よろしいですか(y/n)"
	read ANS
	if [ "${ANS}" ]; then
		if [ ${ANS} = "y" ]; then
			break
		fi
	fi

    echo "対象処理日を入力して下さい。(YYYYMMDD)"
	read ANS
	if [ "${ANS}" ]; then
		${SHELL_CHECKDATE} ${ANS}
		if [ $? -ne 0 ]; then
			echo "日付のフォーマットが異なります(YYYYMMDD)"
			echo ""
		else
			YY=`echo ${ANS} | cut -c1-4`
			MM=`echo ${ANS} | cut -c5-6`
			DD=`echo ${ANS} | cut -c7-8`
			SRIYMD=${YY}-${MM}-${DD}
			continue
		fi
	fi

	echo "出力を中止しますか？(y/n)"
	read ANS
	if [ "${ANS}" ]; then
		if [ ${ANS} = "y" ]; then
			db2 terminate > /dev/null
			exit 0
		fi
	fi
done

# 出力対象入力待ち
while [ 1 ]; do
	echo "出力対象を選択して下さい"
	echo "1) 3086:Ｈ－ＦＡＢＰ"
	echo "2) 3195:アディポネクチン"

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
			echo "出力を中止しますか？(y/n)"
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

# 処理日の曜日を取得（1:日曜～7:土曜）
WEEK=`date -d "${SRIYMD}" +"%w"`
WEEK=$(( WEEK + 1 ))

# 処理日の曜日でのアッセイ有無の設定を取得(検査グループマスタ)
fnGetKNSYB ${SRIYMD} ${KNSGRP}
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

KNSYB_FLG=`echo ${KNSYB} | cut -c ${WEEK}`
# アッセイ日だった場合、警告を出力する。
if [ ${KNSYB_FLG} = '1' ]; then
	echo "本日はアッセイ日ですが、出力しますか？(y/n)"
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

# ロック情報の取得
fnGetLock
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

# ロック情報の設定
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

# ファイル出力シェルの起動
${SHELL_MAKEFILE} ${SRIYMD} ${KNSGRP} ${SPLBLID}
if [ $? -gt 0 ]; then
	fnDelLock
	db2 terminate > /dev/null
	exit 1
fi

# ロック情報の削除
fnDelLock
if [ $? -gt 0 ]; then
	db2 terminate > /dev/null
	exit 1
fi

echo "処理が終了しました。"
echo ""

db2 terminate > /dev/null

exit 0
