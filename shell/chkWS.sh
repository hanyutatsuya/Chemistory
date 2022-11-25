#!/bin/bash -

while true; do
	db2 connect to kea00db user db2inst1 using db2inst1 1> /dev/null 

	echo 【 `date` 】
	echo WSチェック


	db2 "SELECT K.SRIYMD, K.UTKYMD, K.IRINO,K.KMKCD, K.KNSSU FROM IRAI I,KENORDER K WHERE I.ODRSSFLG = '1' AND I.UTKYMD=K.UTKYMD AND I.IRINO = K.IRINO AND I.KNSGRP=K.KNSGRP AND I.KMKCD = K.KMKCD AND I.KNSSU = K.KNSSU FOR READ ONLY"

	db2 terminate 1> /dev/null

	sleep $1
	clear
done

##SELECT I.IRINO,I.KMKCD
##        ,I.KNSSU AS IRAI更新前
##        ,'→'
##        ,K.MAX_SU AS 更新すべき検査回数
##FROM IRAI I,
##    (SELECT SRIYMD,IRINO,KMKCD,MAX(KNSSU)+1 AS MAX_SU
##        FROM KENORDER
##        WHERE SRIYMD = '2006-09-25'
##        AND IRINO = '$IRINO'
##        AND KMKCD = '$KMKCD'
##        GROUP BY SRIYMD,IRINO,KMKCD
##        ) K
##WHERE I.ODRSSFLG = '1'
##AND I.SRIYMD = K.SRIYMD
##AND I.IRINO = K.IRINO
##AND I.KMKCD = K.KMKCD
##ORDER BY KMKCD
##;
