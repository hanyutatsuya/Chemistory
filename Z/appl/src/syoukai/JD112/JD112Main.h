/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：JD112Main.h									*/
/*		概要		：検査進行状況集計ヘッダーファイル				*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/23		H.Suyama		Create					*/
/*  1.04    2006-06-17      INTEC           登録日時10分単位に作成  */
/********************************************************************/
#ifndef _JD112Main_h
#define _JD112Main_h

/********************************************************************/
/*  インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "JD112Knssnkjyk.h"

#define MYAPP_APP_NAME		  "JD112"

//  内部ステータスコード定義
typedef enum {
	JD112_STSCODE_NORMAL,
	JD112_STSCODE_ERR_USAGE,
	JD112_STSCODE_ERR_PRM_FILE,
	JD112_STSCODE_ERR_PRM_GET,
	JD112_STSCODE_ERR_SHM_AT,
	JD112_STSCODE_ERR_SHM_DT,
	JD112_STSCODE_ERR_SHM_DEL,
	JD112_STSCODE_ERR_SHM_GET,
	JD112_STSCODE_ERR_DIR,
	JD112_STSCODE_ERR_FR_FILE
} JD112_STSCODE;

// 共有メモリサイズ
#define JD112_SHM_SIZE			sizeof ( int ) * 2

// パラメータファイルキー文字列
#define JD112_PRM_DBNAME		"DBNAME"		// データベース接続名
#define JD112_PRM_DBUSER		"DBUSER"		// ログインユーザ
#define JD112_PRM_DBPAWD		"DBPAWD"		// ログインパスワード
#define JD112_PRM_PORTNO		"PORTNO"		// ポート番号
#define JD112_PRM_LISTEN		"LISTEN"		// コネクト要求待ち数
#define JD112_PRM_RETRY_CNT		"RETRY_CNT"		// 通信リトライ回数
#define JD112_PRM_TIMEOUT		"TIMEOUT"		// タイムアウト値（秒）
#define JD112_PRM_APP_IRAI		"APP_IRAI"		// 依頼展開アプリ名
#define JD112_PRM_APP_KANJYA	"APP_KANJYA"	// 患者属性展開アプリ名
#define JD112_PRM_APP_BUNCHU	"APP_BUNCHU"	// 分注展開アプリ名
#define JD112_PRM_APP_NINSIKI	"APP_NINSIKI"	// 認識展開アプリ名
#define JD112_PRM_APP_KENZOK	"APP_KENZOK"	// 検体属性展開アプリ名
#define JD112_PRM_UPDATE_MIN	"UPDATE_MIN"	// 更新間隔（分）
#define JD112_PRM_SLEEP_SEC		"SLEEP_SEC"		// スリープ時間（秒）
#define JD112_PRM_SHM_KEY		"SHM_KEY"		// 共有メモリキー
#define JD112_PRM_FILE_DBG		"FILE_DBG_NSME"	// デバッグ
#define JD112_PRM_FILE_TR		"FILE_TR_NAME"	// トレース
#define JD112_PRM_FILE_ACS		"FILE_ACS_NAME"	// アクセス
#define JD112_PRM_FILE_ERR		"FILE_ERR_NAME"	// エラー
#define JD112_PRM_UP_ID			"UPDATE_ID"		// 更新者ID
#define JD112_PRM_UP_NM			"UPDATE_NM"		// 更新者
#define JD112_PRM_PROC_MD		"PROC_MD"		// 実行モード

#define JD112_PRM_STA_DH		"STA_DH"		// 1.04 ADD 集計開始日時

// 集計要求電文
#define JD112_MSG_BUFFLEN		1024
#define JD112_MSG_START			"JD112CALLFUNC"
#define JD112_MSG_END			"JD112FUNCEND"

// データ識別子
#define JD112_DB_KOTEIKBN_IRAI		'A'		// 依頼
#define JD112_DB_KOTEIKBN_KANJYA	'B'		// 患者
#define JD112_DB_KOTEIKBN_BUNCHU	'C'		// 分注
#define JD112_DB_KOTEIKBN_NINSIKI	'D'		// 認識
#define JD112_DB_KOTEIKBN_KENZOK	'E'		// 検体属性
#define JD112_DB_KOTEIKBN_E_IRAI	'F'		// 依頼（エラー）
#define JD112_DB_KOTEIKBN_E_KANJYA	'G'		// 患者（エラー）
#define JD112_DB_KOTEIKBN_E_BUNCHU	'H'		// 分注（エラー）
#define JD112_DB_KOTEIKBN_E_NINSIKI	'I'		// 認識（エラー）
#define JD112_DB_KOTEIKBN_E_KENZOK	'J'		// 検体属性（エラー）
#define JD112_DB_KOTEIKBN_TOUNYU	'K'		// 投入
#define JD112_DB_KOTEIKBN_SOKUTEI	'L'		// 測定
#define JD112_DB_KOTEIKBN_SYUNOU	'M'		// 収納
//(MOD)<START>2006/5/9 S.Fukuyama
//     供給ストッカ／回収ストッカに変更
//#define JD112_DB_KNSJKFLG_CHUU	'1'		// 検査中
//#define JD112_DB_KNSJKFLG_DONE	'2'		// 検査完了
#define JD112_DB_KNSJKFLG_CHUU		'A'		// 供給ストッカ
#define JD112_DB_KNSJKFLG_DONE		'E'		// 回収ストッカ
//(MOD)<END>2006/5/9 S.Fukuyama
#define JD112_DB_SKFLG_NORMAL		'0'		// 一般
#define JD112_DB_SKFLG_SYUKEN		'1'		// 集検
#define JD112_DB_DATAZOK_NORMAL		'A'		// 一般
#define JD112_DB_DATAZOK_SYUKEN		'B'		// 集検

#define JD112_CALLFUNC_STOP			0
#define JD112_CALLFUNC_START		1
#define JD112_SECOFMIN				60
#define JD112_CHAR_SPACE			' '

#define JD112_FMT_TIMESTAMP			"%04d-%02d-%02d-%02d.%02d.%02d.000000"
#define JD112_FMT_DATETIME			"%04d-%02d-%02d%02d:%02d:%02d"

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"
#define MYAPP_LOG_ERRCODE_SOCKET	999

#define MYAPP_FUNC_MINUS			0				// 1.04 ADD 
#define MYAPP_FUNC_PLUS				1				// 1.04 ADD 

// デフォルトINIファイル
#define MYAPP_INIFILE "./JD112.ini"
// ログファイルINIファイル
#define MYAPP_LOGINIFILE "$HOME/bin/JD112_LOG.ini"

/******************************************************************************/
/* 構造体定義																  */
/******************************************************************************/
// プログラム環境構造体
typedef struct {
	BMLPRM	*bp;
	char	*pcFileNamePRM;
	int		shm_Id;					// 共有メモリID
	key_t	shm_Key;				// 共有メモリキー
	int		iSleepSec;				// スリープ時間（秒）
	int		iUpdateMin;				// 更新間隔（分）
	int		iSockFd;				// ソケットFD
	int		iCallFunc;				// 集計実行開始フラグ
	int		iThreadSts;				// スレッドステータス
	int		iPortNo;				// ポート番号
	int		iListen;				// コネクト接続待ち数
	int		iRetryCnt;				// 通信リトライ回数
	int		iTimeout;				// タイムアウト値（秒）
	char	cAppIrai[1024];			// 依頼展開アプリ名
	char	cAppKanjya[1024];		// 患者属性展開アプリ名
	char	cAppBunchu[1024];		// 分注展開アプリ名
	char	cAppNinsiki[1024];		// 認識展開アプリ名
	char	cAppKenzok[1024];		// 検体属性展開アプリ名
	char	cDBName[1024];			// データベース接続名
	char	cDBUser[1024];			// ログインユーザ
	char	cDBPawd[1024];			// ログインパスワード
	char	cDebugLogName[1024];	// デバッグログファイル名
	char	cTraceLogName[1024];	// トレースログファイル名
	char	cAccessLogName[1024];	// アクセスログファイル名
	char	cErrorLogName[1024];	// エラーログファイル名
	int		proc_mode;				// 処理モード	0：過渡期   1：次世代
	char	cUpdateId[128];			// 更新者ID
	char	cUpdateName[128];		// 更新者
	char	cLogName[128];			// ログ
	ULONG	ulPrevKsndh;			// 前回集計開始時間
	int		iBaseJikan;				// 初回起動時の時間
	char	clPrevKsndh[27];		// 1.04 ADD 前回集計開始時間
	char	cStaTimestamp[27];		// 1.04 ADD 集計対象開始日時(必須ではない)
									// YYYY-MM-DD-HH24:MI:00
} JD112Env;

// 1.02 INTEC ADD STA
	// 分析機マスタ
struct _MEMST {
	char	bskkbn[4+1];			// 分析機区分
	char	bsklne[4+1];			// 分析機ライン
} hmemst;
// 1.02 INTEC ADD END
/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言															  */
/******************************************************************************/
void JD112ConvTimestamp(ULONG ulTm, int iFlg, char *pDest);

int initFunction( int argc, char *argv[], JD112Env *pEnv );
int mainFunction( JD112Env *pEnv );
void endFunction( JD112Env *pEnv );

int JD112SyukeiMain(JD112Env *pEnv, char *pKnskisymd);
int JD112UpdateKnssnkjyk(Knssnkjyk *pKnssnkjyk);
void *JD112SocketThread(void *pParam);

//  共有メモリ操作関数
static  int sFncShmCrt ( JD112Env * );
static  int sFncShmGet ( JD112Env * , int *);
static  int sFncShmDel ( JD112Env * );
//  トレース用
static  void	_sFncEnvDip ( JD112Env * );
//ログ関数
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
