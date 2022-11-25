/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD102Main.h									*/
/*		概要		：ファイル転送ヘッダーファイル					*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/********************************************************************/
#ifndef _GD102Main_h
#define _GD102Main_h

/********************************************************************/
/*  インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "GD102"

//  内部ステータスコード定義
typedef enum {
	GD102_STSCODE_NORMAL,
	GD102_STSCODE_ERR_USAGE,
	GD102_STSCODE_ERR_PRM_FILE,
	GD102_STSCODE_ERR_PRM_GET,
	GD102_STSCODE_ERR_SHM_AT,
	GD102_STSCODE_ERR_SHM_DT,
	GD102_STSCODE_ERR_SHM_DEL,
	GD102_STSCODE_ERR_SHM_GET,
	GD102_STSCODE_ERR_DIR,
	GD102_STSCODE_ERR_FR_FILE
} GD102_STSCODE;

//  共有メモリサイズ
#define GD102_SHM_SIZE			sizeof ( int )

#define GD102_LEN_DATESHORT		8	// YYYYMMDDの長さ
#define GD102_LEN_IRAIFILE		10	// 依頼項目要求情報ファイル名長
#define GD102_LEN_BUNCFILE		10	// 分注結果要求情報ファイル名長
#define GD102_LEN_OTHERKKAFILE		10	//

//  パラメータファイルキー文字列
#define GD102_PRM_DBNAME		"DBNAME"		// データベース接続名
#define GD102_PRM_DBUSER		"DBUSER"		// ログインユーザ
#define GD102_PRM_DBPAWD		"DBPAWD"		// ログインパスワード
#define GD102_PRM_DIR_HULFTBIN	"DIR_HULFTBIN"	// HULFT実行ファイルディレクトリ
#define GD102_PRM_DIR_REQ_KKA	"DIR_REQ_KKA"	// 結果報告ファイルREQUESTディレクトリ
#define GD102_PRM_DIR_REQ_IRAI	"DIR_REQ_IRAI"	// 依頼要求ファイルREQUESTディレクトリ
#define GD102_PRM_DIR_REQ_BUNC	"DIR_REQ_BUNC"	// 分注結果要求ファイルREQUESTディレクトリ
#define GD102_PRM_DIR_REQ_OTHERKKA	"DIR_REQ_OTHERKKA"	// 他サテライト結果要求ファイルREQUESTディレクトリ
#define GD102_PRM_DIR_OK_KKA	"DIR_OK_KKA"	// 結果報告ファイルOKディレクトリ
#define GD102_PRM_DIR_OK_IRAI	"DIR_OK_IRAI"	// 依頼要求ファイルOKディレクトリ
#define GD102_PRM_DIR_OK_BUNC	"DIR_OK_BUNC"	// 分注結果要求ファイルOKディレクトリ
#define GD102_PRM_DIR_OK_OTHERKKA	"DIR_OK_OTHERKKA"	// 他サテライト結果要求ファイルOKディレクトリ
#define GD102_PRM_DIR_ERR_KKA	"DIR_ERR_KKA"	// 結果報告ファイルERRディレクトリ
#define GD102_PRM_DIR_ERR_IRAI	"DIR_ERR_IRAI"	// 依頼要求ファイルERRディレクトリ
#define GD102_PRM_DIR_ERR_BUNC	"DIR_ERR_BUNC"	// 分注結果要求ファイルERRディレクトリ
#define GD102_PRM_DIR_ERR_OTHERKKA	"DIR_ERR_OTHERKKA"	// 他サテライト結果要求ファイルERRディレクトリ
#define GD102_PRM_SEND_FILENAME	"SEND_FILENAME"	// HULFT送信ファイル名
#define GD102_PRM_SEND_FILEOK	"SEND_FILEOK"	// HULFT送信OK確認ファイル名
#define GD102_PRM_SEND_FILENG	"SEND_FILENG"	// HULFT送信NG確認ファイル名
#define GD102_PRM_HULFT_FILEID	"HULFT_FILEID"	// HULFT送信ファイルID
#define GD102_PRM_INTERVAL		"INTERVAL"		// HULFT実行結果待ち時間
#define GD102_PRM_SEND_RETRY	"SEND_RETRY"	// 送信リトライ回数
#define GD102_PRM_CMD_RETRY		"CMD_RETRY"		// 送信コマンドリトライ回数
#define GD102_PRM_RESULT_RETRY	"RESULT_RETRY"	// 結果チェックリトライ回数
#define GD102_PRM_SLEEP_SEC		"SLEEP_SEC"		// スリープ時間（秒）
#define GD102_PRM_SHM_KEY		"SHM_KEY"		// 共有メモリキー
#define GD102_PRM_FILE_DBG		"FILE_DBG_NSME"	// デバッグ
#define GD102_PRM_FILE_TR		"FILE_TR_NAME"	// トレース
#define GD102_PRM_FILE_ACS		"FILE_ACS_NAME"	// アクセス
#define GD102_PRM_FILE_ERR		"FILE_ERR_NAME"	// エラー
#define GD102_PRM_UP_ID			"UPDATE_ID"		// 更新者ID
#define GD102_PRM_UP_NM			"UPDATE_NM"		// 更新者
#define GD102_PRM_PROC_MD		"PROC_MD"		// 実行モード

//データ識別子
#define GD102_FILE_HEADERID		"HD"
#define GD102_FILE_DATAID		"R1"
#define GD102_FILE_LINEFEED		'\n'
#define GD102_FILE_FILLER_SIZE	121
#define GD102_REC_LOOP_MAX		6
#define GD102_DATA_CHAR0		'0'
#define GD102_DATA_SPACE		' '
#define GD102_DATA_STR00		"00"

#define GD102_DB_HKKJKFLG_DONE			"2 "	// 送信完了(ＤＢエラーなし)
#define GD102_DB_HKKJKFLG_ERRSEND		"5 "	// 送信失敗(ＤＢエラーなし)
#define GD102_DB_HKKJKFLG_SEND_DBERR	"9 "	// 送信対象(ＤＢエラー有り)
#define GD102_DB_HKKJKFLG_ERRFILE		"4 "	// 送信完了(ＤＢエラー有り)

#define GD102_DB_HKKERRCODE_NOFILE	"00000009"
#define GD102_DB_HKKERRCODE_SENDNG	"00000010"

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// デフォルトINIファイル
#define MYAPP_INIFILE "./GD102.ini"
// ログファイルINIファイル
// 1.03 INTEC DELL #define MYAPP_LOGINIFILE "./GD102_LOG.ini"
#define MYAPP_LOGINIFILE "$HOME/appl/src/houkoku/GD102/GD102_LOG.ini"

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
	char	cDBName[1024];			// データベース接続名
	char	cDBUser[1024];			// ログインユーザ
	char	cDBPawd[1024];			// ログインパスワード
	char	cDirHULFTBin[1024];		// HULFT実行ファイルディレクトリ
	char	cDirReqKKA[1024];		// 結果報告ファイルREQUESTディレクトリ
	char	cDirReqIRAI[1024];		// 依頼要求ファイルREQUESTディレクトリ
	char	cDirReqBUNC[1024];		// 分注結果要求ファイルREQUESTディレクトリ
	char	cDirReqOTHERKKA[1024];		// 他サテライト結果要求ファイルREQUESTディレクトリ
	char	cDirOkKKA[1024];		// 結果報告ファイルOKディレクトリ
	char	cDirOkIRAI[1024];		// 依頼要求ファイルOKディレクトリ
	char	cDirOkBUNC[1024];		// 分注結果要求ファイルOKディレクトリ
	char	cDirOkOTHERKKA[1024];		// 他サテライト結果要求ファイルOKディレクトリ
	char	cDirErrKKA[1024];		// 結果報告ファイルERRディレクトリ
	char	cDirErrIRAI[1024];		// 依頼要求ファイルERRディレクトリ
	char	cDirErrBUNC[1024];		// 分注結果要求ファイルERRディレクトリ
	char	cDirErrOTHERKKA[1024];		// 他サテライト結果要求ファイルERRディレクトリ
	char	cSendFileName[1024];	// HULFT送信ファイル名
	char	cSendFileOK[1024];		// HULFT送信OK確認ファイル名
	char	cSendFileNG[1024];		// HULFT送信NG確認ファイル名
	char	cHULFTFileID[1024];		// HULFT送信ファイルID
	int		iInterval;				// HULFT実行結果待ち時間
	int		iSendRetry;				// 送信リトライ回数
	int		iCmdRetry;				// 送信コマンドリトライ回数
	int		iResultRetry;			// 結果チェックリトライ回数
	char	cDebugLogName[1024];	// デバッグログファイル名
	char	cTraceLogName[1024];	// トレースログファイル名
	char	cAccessLogName[1024];	// アクセスログファイル名
	char	cErrorLogName[1024];	// エラーログファイル名
	int		proc_mode;				// 処理モード	0：過渡期   1：次世代
	char	cUpdateId[128];			// 更新者ID
	char	cUpdateName[128];		// 更新者
	char	cLogName[128];			// ログ
} GD102Env;

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/
// 1.03 INTEC ADD extern
extern	char	gcLogMsg[256];				// 1.03 INTEC ADD

/******************************************************************************/
/* プロトタイプ宣言															  */
/******************************************************************************/
void GD102ConvTimestamp(ULONG ulTm, char *pDest);

int initFunction( int argc, char *argv[], GD102Env *pEnv );
int mainFunction( GD102Env *pEnv );
void endFunction( GD102Env *pEnv );
int GD102SendFile(GD102Env *pEnv, char *pFileName);
int GD102SendKekkaFile(GD102Env *pEnv);
int GD102BunchuFileFilter(struct dirent *pDirEnt);
int GD102SendBunchuFile(GD102Env *pEnv);
int GD102IraiFileFilter(struct dirent *pDirEnt);
int GD102SendIraiFile(GD102Env *pEnv);
int GD102OtherKkaFileFilter(struct dirent *pDirEnt);
int GD102SendOtherKkaFile(GD102Env *pEnv);

//  共有メモリ操作関数
static  int sFncShmCrt ( GD102Env * );
static  int sFncShmGet ( GD102Env * , int *);
static  int sFncShmDel ( GD102Env * );
//  トレース用
static  void	_sFncEnvDip ( GD102Env * );
//ログ関数
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
