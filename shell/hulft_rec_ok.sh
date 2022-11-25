:
#*****************************************************************
#   ＢＭＬ様向け検査システム
#
#   システム名：次世代システム
#   ファイル名：hulft_rec_ok.sh
#	概      要：検査受付（依頼展開）HULFT受信ファイルの振り分け
#				  ( HULFT受信 OK 時起動shell )
#
#*****************************************************************
#	No.Ver.    日付           名前          コメント
#---------------------------------------------------------------*
#	H000	2006.03.17	INTEC.INC	CREATE
#	H001	2006.06.01	INTEC.INC	UPDATE  該当dirにmv 後 rename
#*****************************************************************
#
#------------  実行ﾌﾟﾛｸﾞﾗﾑの指定 -----------------------------------
#-------------------------------------------------------------------

#
#	各種変数の設定
WK=/tmp/$$
# ファイル受信用ディレクトリ
RECD=/apdata/today/online/host/Recv
# 処理済みファイル待避ディレクトリ
ENDDIR=$RECD/sumi
# ｴﾗｰファイル待避ディレクトリ
ERRDIR=/apdata/today/online/host/err_Recv

KAN=$RECD/kan					# 患者属性ファイル
IRI=$RECD/iri					# 依頼情報ファイル
BUN=$RECD/bun					# 分注結果ファイル
KKA=$RECD/kka					# 他サテライト結果ファイル

DBG=$1							# DEBUG MODE指定

YMD=`date +%Y%m%d`

#
#	LOG OUTPUT VARIABLE
PROCESSID=$$
WKUPAPP=$0

#-------------------------  この下から処理を記述  ------------------
#
#	ファイル受信用ディレクトリへの移動	
cd $RECD

#
#	hulft登録物理名称からのファイル名変更
#		世代管理を行うので「物理ファイル名+seq」にてファイルが作成される
#			(hulft.rirai.9999)
#		受信終了時にHULFTが環境変数$FILENMに作成したファイル名を設定する
#

#
# ファイルの有無
if [ -s $FILENM ]
then
	echo " "
else
	#----------------
	#	LOG OUTPUT
	#----------------
	MESSAGE="File[$FILENM] does not exist"

	sh hulft_ins_log.sh "W" $PROCESSID $WKUPAPP "$MESSAGE" 

	#	DBG
	if [ "$DBG" = "-DBG" ] ; then
		echo "File[$FILENM] does not exist"
	fi

	#	処理終了
	exit 0
fi

#	環境変数からディレクトリを除いたファイル名を取り出す
LS=`basename $FILENM`
##mv $FILENM	$LS

#==========================================================================
#		
#		ファイル振り分け
#		
#==========================================================================
while true
do
	#
	# レコード件数取得  HD TRのみはSKIP
	RCNT=`grep -v "^HD" $LS | grep -v "^TR" | wc -l`
	if [ $RCNT -eq 0 ] 
	then
		#	DBG
		if [ "$DBG" = "-DBG" ] ; then
			echo "[$LS]HD TR ONLY RCNT[$RCNT]"
		fi

		#	処理済ディレクトリに移動
		mv $LS $ENDDIR/HDTR.$LS
		break
	fi

	#
	#	データフローIDの取得
	DFLWID=`head -1 $LS | cut -b 31-40`

	#	DBG
	if [ "$DBG" = "-DBG" ] ; then
		echo "対象ファイル[$LS][$DFLWID]"
	fi

	#
	#	データフローIDの取得
	case	"$DFLWID"
	in
		"SIRAI002  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "患者属性 -> [$KAN/KAN.$LS]"
			fi
			mv  $LS			$KAN/$LS
			rename $KAN/$LS $KAN/KAN.$LS $KAN/$LS
			break
			;;
		"SIRAI004  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "依頼情報 -> [$IRI/IRI.$LS]"
			fi
			mv  $LS			$IRI/$LS
			rename $IRI/$LS $IRI/IRI.$LS $IRI/$LS
			break
			;;
		"SBUNC003  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "分注結果 -> [$BUN/BUN.$LS]"
			fi
			mv  $LS			$BUN/$LS
			rename $BUN/$LS $BUN/BUN.$LS $BUN/$LS
			break
			;;
		"EHOKO002  "	)
			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "他サテライト結果 -> [$KKA/KKA.$LS]"
			fi
			mv  $LS			$KKA/$LS
			rename $KKA/$LS $KKA/KKA.$LS $KKA/$LS
			break
			;;
		*			)
			#----------------
			#	LOG OUTPUT
			#----------------
			MESSAGE="HULFT受信　データフローID対象外[$LS][$DFLWID]"

			sh hulft_ins_log.sh "W" $PROCESSID $WKUPAPP "$MESSAGE" 

			#	DBG
			if [ "$DBG" = "-DBG" ] ; then
				echo "対象外 -> [$ENDDIR/$LS][$DFLWID]"
			fi
			mv $LS $ENDDIR/$LS
			break
			;;
	esac

	#	処理は１回だけ
	break
done

#==========================================================================
#		
#		終了処理
#		
#==========================================================================
#
#	ファイル受信用ディレクトリへの移動	
cd $RECD

#
#	処理終了ファイルの移動
for i in `find $KAN $IRI $BUN  -name "END*" -print `
do
	mv $i  $ENDDIR
done

#
#  中間ファイルのｸﾘｱ
##rm $WK*

exit 0
