
#######################################################################
#  未報告分KEYデータINSERT
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

db2 CONNECT TO $1 USER $2 USING $3

echo "[`date`][DAY_MHKKEY] insert mityaku start ----->"

db2 "export to ./DAY_MHKKEY_mityaku.ixf of ixf messages ./DAY_MHKKEY_mityaku.msg select distinct utkymd, irino, current timestamp from (select utkymd,irino,kmkcd from irai where not exists (select * from bunchu where bunchu.utkymd = irai.utkymd and bunchu.irino = irai.irino and bunchu.kmkcd = irai.kmkcd) ) daily "
db2 "import from ./DAY_MHKKEY_mityaku.ixf of ixf allow write access commitcount 5000 messages ./DAY_MHKKEY_mityaku.mhk.msg insert_update into DAY_MHKKEY"

db2 terminate
