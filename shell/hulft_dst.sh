#*****************************************************************
#   ＢＭＬ様向け検査システム
#
#   システム名：次世代システム
#   ファイル名：hulft_dst.sh
#   概      要：検査受付（依頼展開）HULFT受信ファイルの振り分け
#                   テスト時用振り分け
#   起動ﾊﾟﾗﾒｰﾀ
#           hulft_dst.sh
#*****************************************************************
#   No.Ver.    日付           名前          コメント
#---------------------------------------------------------------*
#   H000    95.09.20    INTEC.INC   CREATE
#*****************************************************************
#
#------------  実行ﾌﾟﾛｸﾞﾗﾑの指定 -----------------------------------
#-------------------------------------------------------------------

#
#   各種変数の設定
WK=/tmp/$$
# ファイル受信用ディレクトリ
RECD=/apdata/today/online/host/Recv
# 処理済みファイル待避ディレクトリ
ENDDIR=$RECD/sumi
# ｴﾗｰファイル待避ディレクトリ
ERRDIR=/apdata/today/online/host/err_Recv

KAN=$RECD/kan                   # 患者属性ファイル
IRI=$RECD/iri                   # 依頼情報ファイル
BUN=$RECD/bun                   # 分注結果ファイル

PREF=PNC.                       # PNC稼動前後の判定用

DBG=$1                          # DEBUG MODE指定

YMD=`date +%Y%m%d`

#-------------------------  この下から処理を記述  ------------------
echo "##### [`date`] 依頼受信処理開始 #####"    >> $WK.uerr
echo " "                                        >> $WK.uerr

#
#   ファイル受信用ディレクトリへの移動
cd $RECD

#
#   hulft登録物理名称からのファイル名変更
#       世代管理を行うので「物理ファイル名+seq」にてファイルが作成される
#           (hulft.rirai.9999)
#       受信終了時にHULFTが環境変数$FILENMに作成したファイル名を設定する
#

#mv $FILENM     PNC/"$PREF"HIP$YMD.$$
##cp  PNC/hulft.rirai   PNC/"$PREF"HIP$YMD.$$

#==========================================================================
#
#       ファイル振り分け
#
#==========================================================================
#
for LS in `ls ./`
do
        echo "処理中。。。[$LS]"

        # ディレクトリを対象外に
        if [ -d $LS ]
        then
            echo "Directory ->  SKIP [$LS]" >> $WK.uerr
            continue
        fi

        # レコード件数取得
        RCNT=`grep -v "^HD" $LS | grep -v "^TR" | wc -l`
        if [ $RCNT -eq 0 ]
        then
            echo "HD TR ONLY ->  SKIP [$LS][$RCNT]" >> $WK.uerr
            mv $LS $ENDDIR/HDTR.$LS
            continue
        fi

        #   データフローIDの取得
        DFLWID=`head -1 $LS | cut -b 31-40`

        echo "対象ファイル[$LS][$DFLWID][$RCNT]" >> $WK.uerr

        case    "$DFLWID"
        in
            "SIRAI002  "    )
                PREF=KAN.
                echo "$LS ---> $KAN/\"$PREF\"$LS" >> $WK.uerr
                mv $LS $KAN/"$PREF"$LS
                ;;
            "SIRAI004  "    )
                PREF=IRI.
                echo "$LS ---> $IRI/\"$PREF\"$LS" >> $WK.uerr
                mv $LS $IRI/"$PREF"$LS
                ;;
            "SBUNC003  "    )
                PREF=BUN.
                echo "$LS ---> $BUN/\"$PREF\"$LS" >> $WK.uerr
                mv $LS $BUN/"$PREF"$LS
                ;;
            *           )
                echo "$LS ---> 対象外" >> $WK.uerr
                ;;
        esac
done

#==========================================================================
#
#       終了処理
#
#==========================================================================
#
#   ファイル受信用ディレクトリへの移動
cd $RECD

#   DBG
    CURDIR=`pwd`
    echo "終了処理 START!! CURDIR=[$CURDIR]" >> $WK.uerr

exit 0

