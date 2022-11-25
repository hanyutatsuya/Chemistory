/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：LD101.h                                                      */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2006/01/15     芳賀弘幸       新規作成                           */
/*  x.xx     2006/12/15     YOON	       DEFINE追加                         */
/*  x.xx     2008/02/04     moriya	       新フロンティア対応                 */
/******************************************************************************/
#ifndef _LD101_h
#define _LD101_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"LD101"
#define	MYAPP_APP_NAME_JP		"LD101"
#define	MYAPP_LOGINIFILE		"LD101_LOG.ini"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	エラーコード定義
#define	MYAPP_LOG_ERRCODE_NON		"00000000"
#define	MYAPP_LOG_ERRCODE_APP		"010"
#define	MYAPP_LOG_ERRCODE_DB		"020"
#define	MYAPP_LOG_ERRCODE_ETC		"0Z0"

//	エラーコード詳細
#define MYAPP_SQL_DEADLOCK		-911
#define MYAPP_SQL_DUPLICATION		-803

//	パラメータ文字列
#define	MYAPP_PRM_SHM_KEY		"SHM_KEY"
#define	MYAPP_PRM_SLEEP_SEC		"SLEEP_SEC"
#define	MYAPP_PRM_DB_NAME		"DB_NAME"
#define	MYAPP_PRM_DB_USER		"DB_USER"
#define	MYAPP_PRM_DB_PASSWD		"DB_PASSWD"
#define MYAPP_PRM_OUTPUT_DIR		"OUTPUT_DIR"
#define MYAPP_PRM_OUTPUT_FILE		"OUTPUT_FILE"
#define MYAPP_PRM_SEND_SHELL		"SEND_SHELL"
#define	MYAPP_PRM_TRG_FILE		"TRG_FILE"
#define	MYAPP_PRM_DATE_RANGE		"DATE_RANGE"
#define MYAPP_PRM_AGE_HI		"AGE_HI"
#define MYAPP_PRM_AGE_LOW		"AGE_LOW"
#define MYAPP_PRM_SC_HI			"SC_HI"
#define MYAPP_PRM_SC_LOW		"SC_LOW"
#define MYAPP_PRM_TJ_HI			"TJ_HI"
#define MYAPP_PRM_TJ_LOW		"TJ_LOW"

//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

#define MYAPP_LEN_FNCNM			32
#define MYAPP_LEN_MSG			3072


//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	属性チェックフラグ定義
#define MYAPP_ZOK_NOT_CHK		"0"	// 属性チェック対象外
#define MYAPP_ZOK_CHK			"1"	// 属性チェック対象
#define MYAPP_ZOK_ERR			"2"	// 属性チェックエラー
#define MYAPP_ZOK_NG			"3"	// 属性チェックエラー(異常値)

#define MYAPP_SBTKBN_MALE		"0"	// 性別区分定義(男)
#define MYAPP_SBTKBN_FEMALE		"1"	// 性別区分定義(女)
#define MYAPP_SBTKBN_UNKNOWN		"9"	// 性別区分定義(不明)

#define MYAPP_AGEKBN_YEAR		"Y"	// 年齢区分定義(年)
#define MYAPP_AGEKBN_MONTH		"M"	// 年齢区分定義(月)
#define MYAPP_AGEKBN_WEEK		"W"	// 年齢区分定義(週)
#define MYAPP_AGEKBN_DAY		"D"	// 年齢区分定義(日)

#define MYAPP_TJTNI_KGRAM		"0"	// 体重単位(kg)
#define MYAPP_TJTNI_GRAM		"1"	// 体重単位(g)

//	ファイルフィールド用定義
#define MYAPP_SPACE_HALF		' '
#define MYAPP_HYPHEN_HALF		'-'
#define MYAPP_SPACE_FULL		"　"
#define MYAPP_HYPHEN_FULL		"－"
#define MYAPP_MARK_MALE			"男"
#define MYAPP_MARK_FEMALE		"女"
#define MYAPP_MARK_YEAR			"歳　"
#define MYAPP_MARK_MONTH		"ヶ月"
#define MYAPP_MARK_WEEK			"週"
#define MYAPP_MARK_DAY			"日　"
#define MYAPP_MARK_KGRAM		"KG"
#define MYAPP_MARK_GRAM			"G "
#define MYAPP_MARK_KBN_ERR		"未入力"
#define MYAPP_MARK_KBN_NG		"確認　"
#define MYAPP_MARK_ERR			'*'
#define MYAPP_MARK_NG			'?'

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	int	 sleep_Sec ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ;
	char	 cOutputDir[MYAPP_PATH_SIZE] ;
	char	 cOutputFile[MYAPP_PATH_SIZE] ;
	char	 cSendShell[MYAPP_PATH_SIZE] ;
	char	 cTrgFile[MYAPP_PATH_SIZE] ;
	int	 DateRange ;
	int	 AgeHi ;
	int	 AgeLow ;
	double	 ScHi ;
	double	 ScLow ;
	double	 TjHi ;
	double	 TjLow ;
} pAppEnv ;

//	システム管理マスタ情報構造体
typedef struct  _stSYSKNR 
{
        char    kjnsriymd[10+1];	// 基準処理年月日
        char    iriendflg[1+1];		// 依頼ENDフラグ
        char    bchendflg[1+1];		// 分注ENDフラグ
        char    unyflg[1+1];		// 運用フラグ
} my_stSYSKNR ;

typedef struct _stCHKZOK
{
	char	utkymd[10+1];		// 1  ＢＭＬ受付年月日
	char	irino[11+1];		// 2  依頼書Ｎｏ
	char	knsgrp[16+1];		// 3  検査グループ
	char	kmkcd[7+1];		// 4  項目コード
	char	kmknmj[46+1];		// 5  項目名
	char	sstcd[7+1];		// 6  施設コード
	char	sstssnmj[40+1];		// 7  施設名称
	char	knjnmn[60+1];		// 8  患者名
	char	krtno[40+1];		// 9  カルテＮＯ
	char	sc[5+1];		// 10 身長
	char	scflg[1+1];		// 11 身長 チェックフラグ
	char	tj[5+1];		// 12 体重
	char	tjflg[1+1];		// 13 体重  チェックフラグ
	char	tjtni[1+1];		// 14 体重区分
	char	tjtniflg[1+1];		// 15 体重区分チェックフラグ
	char	sbtkbn[1+1];		// 16 性別区分
	char	sbtkbnflg[1+1];		// 17 性別区分チェックフラグ
	char	age[3+1];		// 18 年齢
	char	ageflg[1+1];		// 19 年齢チェックフラグ
	char	agekbn[1+1];		// 20 年齢区分
	char	agekbnflg[1+1];		// 21 年齢区分チェックフラグ
} my_stCHKZOK ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void	sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
int	sFncSelSysKnr ( my_stSYSKNR* ) ;
int	sFncSelChkZok( char *, my_stCHKZOK **, int * );
int	InsHkHrIrai( my_stCHKZOK * ) ;

#endif
/** End of File ***************************************************************/
