#!/bin/bash -
LOG_DIR="/apdata/aplog"
NAME_ERRLOG="FATAL_"

db2 connect to $1 user $2 using $3
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ＤＢ接続に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "[`date`][TABLE] import /dev/null start ----->"

echo "CHIKENZOK"
db2 "import from /dev/null of del replace into CHIKENZOK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : CHIKENZOK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "CTRLKKA"
db2 "import from /dev/null of del replace into CTRLKKA"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : CTRLKKA Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "CTRLKNR"
db2 "import from /dev/null of del replace into CTRLKNR"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : CTRLKNR Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "HKKKNRI"
db2 "import from /dev/null of del replace into HKKKNRI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : HKKKNRI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

## マスタデータ扱いのため対象外とする
##db2 "import from /dev/null of del replace into HYJKMK"
##if [ $? -gt 0 ]; then
##	exit 1
##fi

echo "IJYOSYA"
db2 "import from /dev/null of del replace into IJYOSYA"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : IJYOSYA Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "IRAI"
db2 "import from /dev/null of del replace into IRAI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : IRAI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KANJYA"
db2 "import from /dev/null of del replace into KANJYA"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KANJYA Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KEKKA"
db2 "import from /dev/null of del replace into KEKKA"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KEKKA Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KEKKAFREE"
db2 "import from /dev/null of del replace into KEKKAFREE"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KEKKAFREE Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KENORDER"
db2 "import from /dev/null of del replace into KENORDER"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KENORDER Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KENPOS"
db2 "import from /dev/null of del replace into KENPOS"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KENPOS Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KENZOK"
db2 "import from /dev/null of del replace into KENZOK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KENZOK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KKACONVKNR"
db2 "import from /dev/null of del replace into KKACONVKNR"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KKACONVKNR Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi


echo "KMKBTUTEST"
db2 "import from /dev/null of del replace into KMKBTUTEST"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KMKBTUTEST Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KNKMHMZK"
db2 "import from /dev/null of del replace into KNKMHMZK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KNKMHMZK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "KNKYULOT"
db2 "import from /dev/null of del replace into KNKYULOT"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KNKYULOT Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

## 一定日数を残すため対象外とする
##echo "KNSSNKJYK"
##db2 "import from /dev/null of del replace into KNSSNKJYK"
##if [ $? -gt 0 ]; then
##	exit 1
##fi

echo "KNTIDUNKNOWN"
db2 "import from /dev/null of del replace into KNTIDUNKNOWN"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : KNTIDUNKNOWN Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "NINSIKI"
db2 "import from /dev/null of del replace into NINSIKI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : NINSIKI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "REALCHK"
db2 "import from /dev/null of del replace into REALCHK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : REALCHK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

## 履歴扱いのため対象外とする
##echo "RIREKI"
##db2 "import from /dev/null of del replace into RIREKI"
##if [ $? -gt 0 ]; then
##	exit 1
##fi

echo "SLIDE"
db2 "import from /dev/null of del replace into SLIDE"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : SLIDE Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "SOUKAN"
db2 "import from /dev/null of del replace into SOUKAN"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : SOUKAN Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "STANDARD"
db2 "import from /dev/null of del replace into STANDARD"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : STANDARD Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "TRAYKNRI"
db2 "import from /dev/null of del replace into TRAYKNRI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : TRAYKNRI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "TRRAKHMZK"
db2 "import from /dev/null of del replace into TRRAKHMZK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : TRRAKHMZK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

## 初期値設定が必要なため対象外とする
##db2 "import from /dev/null of del replace into KNSSEQKNRI"
##if [ $? -gt 0 ]; then
##	exit 1
##fi

echo "WSSEQKNRI"
db2 "import from /dev/null of del replace into WSSEQKNRI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : WSSEQKNRI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "XBARM"
db2 "import from /dev/null of del replace into XBARM"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : XBARM Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "XEBSKFLG"
db2 "import from /dev/null of del replace into XEBSKFLG"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : XEBSKFLG Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "APLLOG"
db2 "import from /dev/null of del replace into APLLOG"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : APLLOG Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "ASYRACKKNRI"
db2 "import from /dev/null of del replace into ASYRACKKNRI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ASYRACKKNRI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "AUTOKOSICTRL"
db2 "import from /dev/null of del replace into AUTOKOSICTRL"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : AUTOKOSICTRL Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "BSSIKKA"
db2 "import from /dev/null of del replace into BSSIKKA"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : BSSIKKA Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "BATCHKNRI"
db2 "import from /dev/null of del replace into BATCHKNRI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : BATCHKNRI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "BSSIZOK"
db2 "import from /dev/null of del replace into BSSIZOK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : BSSIZOK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "BUNCHU"
db2 "import from /dev/null of del replace into BUNCHU"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : BUNCHU Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "SHUSEI_KANJYA"
db2 "import from /dev/null of del replace into SHUSEI_KANJYA"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : SHUSEI_KANJYA Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "OTHERKKA"
db2 "import from /dev/null of del replace into OTHERKKA"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : OTHERKKA Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "HKHRIRAI"
db2 "import from /dev/null of del replace into HKHRIRAI"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : HKHRIRAI Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "ORDERRACK"
db2 "import from /dev/null of del replace into ORDERRACK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : ORDERRACK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

echo "FRONRACK"
db2 "import from /dev/null of del replace into FRONRACK"
if [ $? -gt 0 ]; then
	echo `date`" ERROR : FRONRACK Tabel削除に失敗しました" >> $LOG_DIR/$NAME_ERRLOG"delKea00_dat.log"
	exit 1
fi

db2 terminate

exit 0
