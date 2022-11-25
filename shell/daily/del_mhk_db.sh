#######################################################################
#	未報告分データを累積、集計から削除する
# $1 : DB名
# $2 : ユーザID(DB2)
# $3 : パスワード(DB2)
#######################################################################

db2 CONNECT TO $1 USER $2 USING $3

##MHKTBL="RUI_BUNCHU RUI_CHIKENZOK RUI_IRAI RUI_KANJYA RUI_KEKKA RUI_KENORDER RUI_KENZOK RUI_NINSIKI RUI_REALCHK SHU_KEKKA"
MHKTBL="RUI_IRAI RUI_KANJYA RUI_KEKKA RUI_KENZOK"

for TBL in `echo $MHKTBL`
do

echo "[`date`][$TBL] delete start ----->"

db2 "select count(*) from $TBL dd where exists ( select utkymd, irino from DAY_MHKKEY ky where ky.utkymd=dd.utkymd and ky.irino=dd.irino ) for read only"

db2 "delete from $TBL dd where exists ( select utkymd, irino from DAY_MHKKEY ky where ky.utkymd=dd.utkymd and ky.irino=dd.irino )"
done

db2 terminate
