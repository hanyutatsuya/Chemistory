#######################################################################
#	未着分データをexportする(DEL)
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

db2 CONNECT TO $1 USER $2 USING $3

echo "[`date`][IRAI] export start ----->"
db2 "export to ./IRAI.mtk of del messages ./IRAI.exp_mtk.msg SELECT IRAI.* FROM IRAI WHERE NOT EXISTS (SELECT * FROM BUNCHU WHERE BUNCHU.UTKYMD = IRAI.UTKYMD AND BUNCHU.IRINO = IRAI.IRINO AND BUNCHU.KMKCD = IRAI.KMKCD) ORDER BY UTKYMD,IRINO,KMKCD FOR READ ONLY"

echo "[`date`][KANJYA] export start ----->"
db2 "export to ./KANJYA.mtk of del messages ./KANJYA.exp_mtk.msg SELECT KANJYA.* FROM KANJYA WHERE KANJYA.ZSSDINO <> 100 AND NOT EXISTS (SELECT * FROM BUNCHU WHERE BUNCHU.UTKYMD = KANJYA.UTKYMD AND BUNCHU.IRINO = KANJYA.IRINO) ORDER BY UTKYMD,IRINO FOR READ ONLY"

echo "[`date`][CHIKENZOK] export start ----->"
db2 "export to ./CHIKENZOK.mtk of del messages ./CHIKENZOK.exp_mtk.msg SELECT CHIKENZOK.* FROM CHIKENZOK WHERE NOT EXISTS (SELECT * FROM BUNCHU WHERE BUNCHU.UTKYMD = CHIKENZOK.UTKYMD AND BUNCHU.IRINO = CHIKENZOK.IRINO) ORDER BY UTKYMD,IRINO FOR READ ONLY"

db2 terminate
