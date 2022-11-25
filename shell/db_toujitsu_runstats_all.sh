#!/bin/bash -

db2 connect to kea00db user db2inst1 using db2inst1
if [ $? -gt 0 ]; then
    exit 1
fi

date
echo " "
echo "TOUJITSU DB RUNSTATS START"
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
echo "CHIKENZOK"
db2 RUNSTATS ON TABLE DB2INST1.CHIKENZOK WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "CTRLKKA"
db2 RUNSTATS ON TABLE DB2INST1.CTRLKKA WITH DISTRIBUTION and detailed indexes all;
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
echo "IRAI"
db2 RUNSTATS ON TABLE DB2INST1.IRAI WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KANJYA"
db2 RUNSTATS ON TABLE DB2INST1.KANJYA WITH DISTRIBUTION and detailed indexes all;
echo " "
echo "KEKKA"
db2 RUNSTATS ON TABLE DB2INST1.KEKKA WITH DISTRIBUTION and detailed indexes all;
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
echo "TOUJITSU DB RUNSTATS END"
echo " "
date
echo " "

db2 terminate;
