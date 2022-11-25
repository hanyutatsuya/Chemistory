#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
    . /home/db2inst1/sqllib/db2profile
fi

db2 connect to kea00db user db2inst1 using db2inst1
if [ $? -gt 0 ]; then
    exit 1
fi

echo "[`date`] TOUJITSU DB RUNSTATS START"
echo " "
#---------------------------------------------------------
#	初期処理
#---------------------------------------------------------
#	変数設定
	# 基準件数
KNJKEN=5000
BUNKEN=5000
KEKKEN=5000

# RUNSTATS 判断　FILE
KJ_EXC=/apdata/aplog/RST_KJ
BN_EXC=/apdata/aplog/RST_BN
KK_EXC=/apdata/aplog/RST_KK

#TMP FILE
WKF=/tmp/$$

#---<< 日次処理中はRUNSTATSを実行しない >>---------------------------------
# システム管理マスタ　運用フラグ＝１（日次処理中)
db2 "select count(UNYFLG) as KEN from SYSKNRMST where UNYFLG='1' for read only" | sed 's/ //g' | grep ^[0-9] | grep -v "レコード" > $WKF

if [ -s $WKF ]
then
    CNT=`cat $WKF`
else
    CNT=0
fi
echo "[`date`] Get Daily Process Unyou Flg [$CNT]"
if [ $CNT -gt 0 ]
then
    echo "[`date`] CNT[$CNT]  Daily Processing!! RUNSTATS EXIT !"
    rm $WKF
    db2 terminate
    exit 0
fi

#---<< IRAI GROUP : KANJYA REC CNT > KNJKEN --> MAKE RUNSTAT EXECUTE FILE >>
if [ -s $KJ_EXC ]
then
    echo "[`date`] $KJ_EXC EXIST"
else
    # KANJYA
    db2 "select count(irino) as KEN from KANJYA for read only"  | sed 's/ //g' |
 grep ^[0-9] | grep -v "レコード" > $WKF

    # 基準件数と比較してRUNSTATS実行を判断
    if [ -s $WKF ]
    then
        CNT=`cat $WKF`
    else
        CNT=0
    fi
    echo "[`date`] KANJYA REC CNT[$CNT]"
    if [ $CNT -gt $KNJKEN ]
    then
        echo "[`date`] CNT[$CNT] IRAI GROUP TABLE RUNSTAT STA !" > $KJ_EXC
    fi
	rm $WKF
fi
#---<< BUNCHU GROUP : BUNCHU REC CNT > BUNKEN --> MAKE RUNSTAT EXECUTE FILE >>
if [ -s $BN_EXC ]
then
    echo "[`date`] $BN_EXC EXIST"
else
    # BUNCHU
    db2 "select count(irino) as KEN from BUNCHU for read only"  | sed 's/ //g' |
 grep ^[0-9] | grep -v "レコード" > $WKF

    # 基準件数と比較してRUNSTATS実行を判断
    if [ -s $WKF ]
    then
        CNT=`cat $WKF`
    else
        CNT=0
    fi
    echo "[`date`] BUNCHU REC CNT[$CNT]"
    if [ $CNT -gt $BUNKEN ]
    then
        echo "[`date`] CNT[$CNT] BUNCHU GROUP TABLE RUNSTAT STA !" > $BN_EXC
    fi
	rm $WKF
fi
#---<< KEKKA GROUP : KEKKA REC CNT > BUNKEN --> MAKE RUNSTAT EXECUTE FILE >>
if [ -s $KK_EXC ]
then
    echo "[`date`] $KK_EXC EXIST"
else
    # KEKKA
    db2 "select count(irino) as KEN from KEKKA for read only"  | sed 's/ //g' |
grep ^[0-9] | grep -v "レコード" > $WKF

    # 基準件数と比較してRUNSTATS実行を判断
    if [ -s $WKF ]
    then
        CNT=`cat $WKF`
    else
        CNT=0
    fi
    echo "[`date`] KEKKA REC CNT[$CNT]"
    if [ $CNT -gt $KEKKEN ]
    then
        echo "[`date`] CNT[$CNT] KEKKA GROUP TABLE RUNSTAT STA !" > $KK_EXC
    fi
	rm $WKF
fi

if [ -f $WKF ]
then
    rm $WKF
fi

#---------------------------------------------------------
#	依頼系  KANJYA REC CNT > KNJKEN --> RUNSTAT EXECUTE
#---------------------------------------------------------
if [ -s $KJ_EXC ]
then
    echo "[`date`] IRAI GROUP TABLE RUNSTAT EXECUTE !"
else
    echo "[`date`] $KJ_EXC DOES'N EXIST"
    db2 terminate
    exit 0
fi

# 依頼系テーブル
echo " "
echo "CHIKENZOK"
db2 RUNSTATS ON TABLE DB2INST1.CHIKENZOK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "IRAI"
db2 RUNSTATS ON TABLE DB2INST1.IRAI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KANJYA"
db2 RUNSTATS ON TABLE DB2INST1.KANJYA WITH DISTRIBUTION and detailed indexes all;
echo " "

#---------------------------------------------------------
#	結果以外系  BUNCHU REC CNT > BUNKEN --> RUNSTAT EXECUTE
#---------------------------------------------------------
if [ -s $BN_EXC ]
then
    echo "[`date`] BUNCHU GROUP TABLE RUNSTAT EXECUTE !"
else
    echo "[`date`] $BN_EXC DOES'N EXIST"
    db2 terminate
    exit 0
fi

# 結果以外系テーブル
echo " "
echo "APLLOG"
db2 RUNSTATS ON TABLE DB2INST1.APLLOG WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "ASYRACKKNRI"
db2 RUNSTATS ON TABLE DB2INST1.ASYRACKKNRI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "BATCHKNRI"
db2 RUNSTATS ON TABLE DB2INST1.BATCHKNRI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "BSSIKKA"
db2 RUNSTATS ON TABLE DB2INST1.BSSIKKA WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "BSSIZOK"
db2 RUNSTATS ON TABLE DB2INST1.BSSIZOK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "BUNCHU"
db2 RUNSTATS ON TABLE DB2INST1.BUNCHU WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "CTRLKNR"
db2 RUNSTATS ON TABLE DB2INST1.CTRLKNR WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "HKKKNRI"
db2 RUNSTATS ON TABLE DB2INST1.HKKKNRI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "HYJKMK"
db2 RUNSTATS ON TABLE DB2INST1.HYJKMK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "IJYOSYA"
db2 RUNSTATS ON TABLE DB2INST1.IJYOSYA WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KEKKAFREE"
db2 RUNSTATS ON TABLE DB2INST1.KEKKAFREE WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KENORDER"
db2 RUNSTATS ON TABLE DB2INST1.KENORDER WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KENPOS"
db2 RUNSTATS ON TABLE DB2INST1.KENPOS WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KENZOK"
db2 RUNSTATS ON TABLE DB2INST1.KENZOK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KMKBTUTEST"
db2 RUNSTATS ON TABLE DB2INST1.KMKBTUTEST WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KNKMHMZK"
db2 RUNSTATS ON TABLE DB2INST1.KNKMHMZK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KNKYULOT"
db2 RUNSTATS ON TABLE DB2INST1.KNKYULOT WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KNSSEQKNRI"
db2 RUNSTATS ON TABLE DB2INST1.KNSSEQKNRI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KNSSNKJYK"
db2 RUNSTATS ON TABLE DB2INST1.KNSSNKJYK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KNTIDUNKNOWN"
db2 RUNSTATS ON TABLE DB2INST1.KNTIDUNKNOWN WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "NINSIKI"
db2 RUNSTATS ON TABLE DB2INST1.NINSIKI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "REALCHK"
db2 RUNSTATS ON TABLE DB2INST1.REALCHK WITH DISTRIBUTION and detailed indexes all;
echo " "
##echo "RIREKI"
##db2 RUNSTATS ON TABLE DB2INST1.RIREKI WITH DISTRIBUTION and detailed indexes all;
##echo " "
echo "SLIDE"
db2 RUNSTATS ON TABLE DB2INST1.SLIDE WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "SOUKAN"
db2 RUNSTATS ON TABLE DB2INST1.SOUKAN WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "STANDARD"
db2 RUNSTATS ON TABLE DB2INST1.STANDARD WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "TRAYKNRI"
db2 RUNSTATS ON TABLE DB2INST1.TRAYKNRI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "TRRAKHMZK"
db2 RUNSTATS ON TABLE DB2INST1.TRRAKHMZK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "WSSEQKNRI"
db2 RUNSTATS ON TABLE DB2INST1.WSSEQKNRI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "XBARM"
db2 RUNSTATS ON TABLE DB2INST1.XBARM WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "XEBSKFLG"
db2 RUNSTATS ON TABLE DB2INST1.XEBSKFLG WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "FRONRACK"
db2 RUNSTATS ON TABLE DB2INST1.FRONRACK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "ORDERRACK"
db2 RUNSTATS ON TABLE DB2INST1.ORDERRACK WITH DISTRIBUTION and detailed indexes all;
echo " "

#---------------------------------------------------------
#	結果系  KEKKA REC CNT > BUNKEN --> RUNSTAT EXECUTE
#---------------------------------------------------------
if [ -s $KK_EXC ]
then
    echo "[`date`] KEKKA GROUP TABLE RUNSTAT EXECUTE !"
else
    echo "[`date`] $KK_EXC DOES'N EXIST"
    db2 terminate
    exit 0
fi

# 結果系テーブル
echo " "
echo "KEKKA"
db2 RUNSTATS ON TABLE DB2INST1.KEKKA WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "CTRLKKA"
db2 RUNSTATS ON TABLE DB2INST1.CTRLKKA WITH DISTRIBUTION and detailed indexes all;
echo " "

echo "[`date`]TOUJITSU DB RUNSTATS END"
echo " "

db2 terminate;
