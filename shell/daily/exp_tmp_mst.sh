#!/bin/bash -
# The following three lines have been added by UDB DB2.
if [ -f /home/db2inst1/sqllib/db2profile ]; then
	. /home/db2inst1/sqllib/db2profile
fi

#######################################################################
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

db2 connect to $1 user $2 using $3

echo "[`date`] ----->"

db2 "export to ./TMP_KMKMST.del of del messages TMP_KMKMST.msg \
	select \
		KMKCD,KNSGRP \
	from \
    	KMKMST \
	where  \
		KNSGRP not like  '8%' AND \
		KNSGRP not like  '9%' AND \
		KNSGRP not in ('0056','3400','3430','3431') AND \
		NOT (KNSGRP = '0719' AND KMKCD IN ('0000368','0000369','0000546','0003170','0003172','0003173','0003175','0003176','0003399','0003422','0003423','0003545','0003733','0003734','0003735','0003736','0003981','0003982','0003996','0004011','0004125','0006116','0006118','0006119','0006120','0050841','0050842','0050843','0050844','0050845','0050846') ) AND \
		HAIYMD > '$4' \
	order by KMKCD, KAIYMD desc \
	for read only"
ret=$?
if [ $ret -ne 0 ]
then
	db2 terminate
	exit $ret
fi

db2 "export to ./TMP_CMTMST.del of del messages TMP_CMTMST.msg \
	select \
		CMCD,KNSKKA1 \
	from \
		CMTMST \
	where \
		KNSKKA1 <> '' \
	order by CMCD \
	for read only"
ret=$?
if [ $ret -ne 0 ]
then
	db2 terminate
	exit $ret
fi

db2 terminate

exit 0
