/*****************************************************************************

	SYSTEM NAME:  【NonRIA】サテライト

	FILE NAME:    ＦＴＰ受信  共通ヘッダ

	DATE/Var:     2008/04/01 Ver.1.00

	Edited:       S.Sato (apricot)

*****************************************************************************
	#001 08/01/15 ksuzu     分画対応
	#002 08/01/23 ksusu     ケミストリー対応
	#003 08/12/22 sekiya	一時ファイルの作成中にAD108が一時ファイルの処理を
							行ってしまったトラブルに対する対応
							一時ファイルと作成済みファイルの頭文字を別にする
*****************************************************************************/

#ifndef	__LO_FTP3RDID

#define	LEN_BUFF	256

/***********************************************************************
	転送定義ファイル
***********************************************************************/
/* ファイル名	*/
#define	MYAPP_APP_NAME		"AD107"
#define	MYAPP_APP_NAME_JP	"AD107"
#define	MYAPP_LOGINIFILE	"/home/kea00sys/bin/AD107_LOG.ini"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_TR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	エラーコード定義
#define	MYAPP_LOG_ERRCODE_NON		"00000000"

/* タグの定義	*/
#define	MYAPP_PRM_SHM_KEY		"SHM_KEY"		/* 共有メモリキー							*/
#define	MYAPP_PRM_SLEEP_SEC		"SLEEP_SEC"		/* スリープ									*/
#define	MYAPP_PRM_FTP_HOST		"FTP_HOST"		/* リモート側ホスト名						*/
#define	MYAPP_PRM_FTP_USER		"FTP_USER"		/* リモート側ログインユーザ					*/
#define	MYAPP_PRM_FTP_PSWD		"FTP_PSWD"		/* リモート側ログインパスワード 			*/
#define	MYAPP_PRM_R_PATH		"R_PATH"		/* リモート側受信元パス						*/
#define	MYAPP_PRM_R_FILE		"R_FILE"		/* リモート側受信ファイル名					*/
#define	MYAPP_PRM_L_PATH		"L_PATH"		/* ローカル側受信先パス						*/
#define	MYAPP_PRM_I_PATH		"I_PATH"		/* ローカル側展開用パス						*/
#define	MYAPP_PRM_M_PATH		"M_PATH"		/* 差分管理ディレクトリパス					*/
#define	MYAPP_PRM_S_PATH		"S_PATH"		/* 3ID情報展開(AD108)のスキップファイルパス	*/
#define	MYAPP_PRM_ITVAL			"ITVAL"			/* FTP周期（単位：秒）						*/

/***********************************************************************
	３ｒｄＩＤファイル（BUNPOS）
***********************************************************************/
/* 差分管理用ファイル名(１世代前)	*/
#define		FNM_3RDID_BAK		"3rdid.bak"
/* 差分管理用ファイル名(今回)	*/
#define		FNM_3RDID_DAT		"3rdid.dat"
/* ｆｔｐコマンドファイル名	*/
#define		FNM_3RDID_CMD		"3rdid.ftp"
/* 通番管理ファイル	*/
#define		FNM_3RDID_NUM		"3rdid.num"

#define    RET_NOTH  100
#define    RET_OK    0
#define    RET_NG   -1
#define	RET_NORMAL	RET_OK
#define	RET_ERROR	RET_NG

/*********************************************
*  ログメッセージ関連
*********************************************/
#define _LOG_MSG_START          1	/* プロセス開始 */
#define _LOG_MSG_STARTERR       4	/* ER プロセス起動失敗 */
#define _LOG_MSG_HIGAWARI       9	/* 日替終了          */
#define _LOG_MSG_SYSTEM        10	/* 強制終了          */
#define _LOG_MSG_ABORT         11	/* ｱﾎﾞｰﾄ終了         */
#define _LOG_MSG_RCVEND       122	/* NR ＥＮＤ受信確認 */
#define _LOG_MSG_FACCESSERR   201	/* ER ファイルアクセスエラー */
#define _LOG_MSG_FOPENERR     202	/* ER ファイルオープンエラー */
#define _LOG_MSG_FREAD        205	/* NR ファイルＲＥＡＤ */
#define _LOG_MSG_FREADERR     206	/* ER ファイルＲＥＡＤエラー */
#define _LOG_MSG_FWRITE       207	/* NR ファイルＷＲＩＴＥ */
#define _LOG_MSG_FWRITEERR    208	/* ER ファイルＷＲＩＴＥエラー */
#define _LOG_MSG_DATAERR     5305	/* ER データ不正 */
#define _LOG_MSG_DEBUG       9000	/* デバッグ           */

/**********************************************
*   プロセス引数構造体
***********************************************/
typedef struct _LM_FILED {
	char    name[ LEN_BUFF +1 ] ;   /* プロセス名 */
	int     pno ;                   /* プロセスNo */
} LM_FILED ;
LM_FILED  LM ;    /* ﾌﾟﾛｾｽ引数構造体    */

#define		MYAPP_PATH_SIZE		(1024)	/* ディレクトリ格納サイズ */

/* プログラム環境構造体 */
struct	appEnv	{
	BMLPRM				*bp ;
	char				*pcFielNamePRM ;
	int					 shm_Id ;
	key_t				 shm_Key ;						/* 共有メモリキー							*/
	int					 sleep_Sec ;					/* スリープ									*/
	char	 			 cFtpHost[32+1] ;				/* リモート側ホスト名						*/
	char				 cFtpUser[32+1] ;				/* リモート側ログインユーザ					*/
	char				 cFtpPswd[32+1] ;				/* リモート側ログインパスワード 			*/
	char				 cR_Path[MYAPP_PATH_SIZE] ;		/* リモート側受信元パス						*/
	char				 cR_File[64+1] ;				/* リモート側受信ファイル名					*/
	char				 cL_Path[MYAPP_PATH_SIZE] ;		/* ローカル側受信先パス						*/
	char				 cI_Path[MYAPP_PATH_SIZE] ;		/* ローカル側展開用パス						*/
	char				 cM_Path[MYAPP_PATH_SIZE] ;		/* 差分管理ディレクトリパス					*/
	char				 cS_Path[MYAPP_PATH_SIZE] ;		/* 3ID情報展開(AD108)のスキップファイルパス	*/
	int					 iItval ;						/* FTP周期（単位：秒）						*/
} ;

/* 受信ファイルのデータレコード(固定長) */
typedef	struct	_3rdid {
	char	szUkeymd[8];
	char	szIraino[11];
	char	szSriymd[8];
	char	szKentaino[11];
	char	szRuckid[8];
	char	szPos[3];
	char	szYobi[15];
	char	lf[1];
} TXT_3RDID;

/* 受信ファイルのＥＮＤレコード(固定長) */
typedef	struct	_3rdid_end {
	char	szEnd[3];
	char	szYobi[61];
	char	lf[1];
} TXT_3RDID_END;

#define		RECLEN_3RDID		65		/* １レコード長 */

#define		RECEND_3RDID		"END"	/* ＥＮＤレコード */

#define		SEND_BUNPOS			"POS"	/* BUNPOS展開用ファイル頭文字 */

#define		SKIP_BUNPOS			"SKIP"	/* BUNPOS展開SKIPファイル頭文字 */

/* #003 対応 */
#define		TMP_BUNPOS			"TMP"	/* BUNPOS展開一時ファイル頭文字 */

/***********************************************************************
	マクロ定義
***********************************************************************/

/* トレース種別 */
#define		LT_DBG			"D"	
#define		LT_TRC			"T"	
#define		LT_OPT			"O"	
#define		LT_WRN			"W"	
#define		LT_ERR			"E"	
#define		LT_SYS			"A"	
#define		LT_STA			"STA"	
#define		LT_END			"END"	
/* 実行フラグ */
#define		LX_SEL			"S"	
#define		LX_INS			"I"	
#define		LX_UPD			"U"	
#define		LX_DEL			"D"	
#define		LX_NON			" "	

#define		MYAPP_SHM_SIZE		sizeof ( int )


#define	__LO_FTP3RDID
#endif
