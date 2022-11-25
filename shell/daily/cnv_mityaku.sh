#######################################################################
#	未着分データの依頼の処理日をUPDATEする
# $1 : 処理日(yyyy-mm-dd) 
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

db2 CONNECT TO $2 USER $3 USING $4

echo "[`date`][IRAI] update start ----->"
db2 "  UPDATE IRAI SET SRIYMD = '$1' WHERE NOT EXISTS (SELECT * FROM BUNCHU WHERE BUNCHU.UTKYMD = IRAI.UTKYMD AND BUNCHU.IRINO = IRAI.IRINO AND BUNCHU.KMKCD = IRAI.KMKCD)"

db2 terminate
