/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：bmllog.h                                                     */
/* 　概　　　要：ログ出力関数ヘッダ                                           */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2005/12/26     芳賀弘幸       新規                               */
/******************************************************************************/
#ifndef _bmllog_h
#define _bmllog_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
//	INIファイル環境変数
#define 	BML_LOGINIPATH	"BML_LOGINIPATH"		// ログINIファイルPATH

//	INIファイル定義文字
#define 	BML_LOGINI_ENV1	"logOutLv"				// ログ出力レベル
#define 	BML_LOGINI_ENV2	"logdbOutLv"			// ログテーブル出力レベル
#define 	BML_LOGINI_ENV3	"logdbConnect"			// ＤＢ出力デーモン接続先
#define 	BML_LOGINI_ENV4	"logPath"				// ログ出力パス 
#define 	BML_LOGINI_ENV5	"logdbPort"			    // ＤＢ出力デーモンポート
#define 	BML_LOGINI_ENV6	"logdbOutFilePath"		// ＤＢ登録ファイル出力先
#define 	BML_LOGINI_INFO	"logInfo"				// ログ情報

//	ＤＢ登録ファイル出力先関連
#define		BML_SFX_DBFILE	".log"

#define 	ZbmlPutLog(p)     _ZbmlPutLog(p, __FILE__, __LINE__)

//	実行フラグ
#define		EXEFLG_SEL		"S" 
#define		EXEFLG_INS		"I" 
#define		EXEFLG_UPD		"U" 
#define		EXEFLG_DEL		"D" 
#define		EXEFLG_NON		" " 

//	トレース種別
typedef	enum {
	TRCKIND_DEBUG	= 'D',
	TRCKIND_TRACE	= 'T',
	TRCKIND_OPT		= 'O',
	TRCKIND_WARNING	= 'W',
	TRCKIND_ERROR   = 'E',
	TRCKIND_SYSERR  = 'A'
} LOG_TRCKIND ;		


/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// ログ構造体
struct stcLogInfo {
	LOG_TRCKIND			 eTrcKind ;					// トレース種別
	int		 			 iLogLv ;					// ログ出力レベル
	char	 			 pcLogName[256] ;			// ログファイル名
	struct stcLogInfo	*next ;						// 次ログ情報	
} ;

// ログ環境構造体
struct stcLogEnv {
	//	ＩＮＩファイル用
	int				 	 iLogOutLv ;				// ログ出力レベル
	int				 	 iDBOutLv ;					// ログテーブル出力レベル
	char				 pcDBConnect[32] ;			// ログテーブル出力接続先
	int					 pcDBPort ;				    // ログテーブル出力ポート
	char				 pcLogPath[256] ;			// ログ出力パス
	char				 pcDBOutFilePath[256] ;		// ＤＢ登録ファイル出力先
	struct stcLogInfo	*topLoginfo ;
	//	ファイル指定用
	char				 pcLogFile[256] ;			// ログファイル名
} ;

// ログ出力情報構造体
struct stcLogMember {
	LOG_TRCKIND	 eTrcKind ;							// トレース種別
	long		 lPid ;								// プロセスＩＤ
    char		 pcLoginId[8+1] ;					// ログインＩＤ
    char		 pcAppName[32+1] ;					// アプリケーション名
    char	 	 pcSrcName[32+1] ;					// ソース名
    char		 pcFncName[32+1] ;					// 関数名
	long		 lLineNo ;							// ライン数
    char		 pcExeFlg[2+1] ;					// 実行フラグ
    char		 pcErrCode[8+1] ;					// エラーコード
    char		 pcMsg[1024+1] ;					// 詳細メッセージ
} ;

// アプリケーションログ情報構造体
struct stcLogAPLLOG
{
  char sydate[11];
  char sytime[9];
  char tracekbn[2];
  char pcname[33];
  //sqlint32 proccessid;
  char proccessid[33];
  char loginid[9];
  char wkupapp[33];
  char srcname[33];
  char funcname[33];
  //sqlint32 getline;
  char getline[33];
  char procflg[3];
  char errcode[9];
  char message[1024];
  //struct
  //{
  //  short length;
  //  char  data[1024];
  //} message;
} ;


/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
//extern struct stcLogEnv *gpstLogEnv ;			// ログ環境構造体
static struct stcLogEnv *gpstLogEnv = NULL;			// ログ環境構造体

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
// ログオープン関数
int ZbmlOpenLog( char * ) ;

// ログオープン関数
int _ZbmlPutLog( struct stcLogMember *, char *, long ) ;

// ログオープン関数
void ZbmlCloseLog() ;

#endif
/** End of File ***************************************************************/
