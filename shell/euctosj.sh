
#  euc to sj  convert
#   euctosj.sh ファイル名（複数指定可能）
#   変換前のEUCのファイルは、INPUTファイル名.euc　


for INF in $*
do
    BUF=$INF.euc
    OUF=$INF
    mv $INF $BUF
    echo "CONVERT [$BUF]--->[$OUF]"
##  iconv -t EUC-JP -f SJIS $BUF > $OUF
##  iconv -f SHIFT-JIS -t EUC-JP $BUF > $OUF
##  iconv -f EUC-JP    -t SHIFT-JIS $BUF > $OUF
	iconv -f EUCJP-OPEN	-t IBM943	$BUF > $OUF

done

exit 0

