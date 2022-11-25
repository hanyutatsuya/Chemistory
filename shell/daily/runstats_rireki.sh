#######################################################################
#  履歴テーブルにrunstatをかける
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

db2 CONNECT TO $1 USER $2 USING $3

echo "[`date`][RIREKI] runstats start ----->"
db2 RUNSTATS ON TABLE DB2INST1.RIREKI WITH DISTRIBUTION and detailed indexes all;

db2 terminate
