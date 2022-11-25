/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：ED203Main.h									*/
/*		概要		：緊急報告データファイル作成ヘッダーファイル	*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/03/13		H.Suyama		Create					*/
/********************************************************************/
#ifndef _ED203Main_h
#define _ED203Main_h

/********************************************************************/
/*  インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "ED203Kekka.h"

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "ED203"

//  内部ステータスコード定義
typedef enum {
	ED203_STSCODE_NORMAL,
	ED203_STSCODE_ERR_USAGE,
	ED203_STSCODE_ERR_PRM_FILE,
	ED203_STSCODE_ERR_PRM_GET,
	ED203_STSCODE_ERR_SHM_AT,
	ED203_STSCODE_ERR_SHM_DT,
	ED203_STSCODE_ERR_SHM_DEL,
	ED203_STSCODE_ERR_SHM_GET,
	ED203_STSCODE_ERR_DIR,
	ED203_STSCODE_ERR_FR_FILE
} ED203_STSCODE;

//  共有メモリサイズ
#define ED203_SHM_SIZE			sizeof ( int )

#define ED203_LEN_DATESHORT		8	// YYYYMMDDの長さ
#define ED203_LEN_NOITEM		11	// 検体No項目の長さ
#define ED203_LEN_SRCNO			6	// 検体Noの有効桁数
#define ED203_LEN_FILEID		12	// 送信ファイルID（YYYYMMDD9999）の長さ
#define ED203_LEN_FILESEQNO		4	// 送信ファイルIDのSeqNo（9999）の長さ

#define ED203_POS_SRCNO			3	// 依頼No、検体Noのブロック1の開始位置

//  パラメータファイルキー文字列
#define ED203_PRM_DBNAME		"DBNAME"		// データベース接続名
#define ED203_PRM_DBUSER		"DBUSER"		// ログインユーザ
#define ED203_PRM_DBPAWD		"DBPAWD"		// ログインパスワード
#define ED203_PRM_DIR_DATAFILE	"DIR_DATAFILE"	// 報告データファイル出力ディレクトリ
#define ED203_PRM_SLEEP_SEC		"SLEEP_SEC"		// スリープ時間（秒）
#define ED203_PRM_SHM_KEY		"SHM_KEY"		// 共有メモリキー
#define ED203_PRM_FILE_DBG		"FILE_DBG_NSME"	// デバッグ
#define ED203_PRM_FILE_TR		"FILE_TR_NAME"	// トレース
#define ED203_PRM_FILE_ACS		"FILE_ACS_NAME"	// アクセス
#define ED203_PRM_FILE_ERR		"FILE_ERR_NAME"	// エラー
#define ED203_PRM_UP_ID			"UPDATE_ID"		// 更新者ID
#define ED203_PRM_UP_NM			"UPDATE_NM"		// 更新者
#define ED203_PRM_PROC_MD		"PROC_MD"		// 実行モード

//データ識別子
#define ED203_FILE_LINEFEED		'\n'
#define ED203_REC_LOOP_MAX		6
#define ED203_DATA_CHAR0		'0'
#define ED203_DATA_SPACE		' '
#define ED203_DATA_ASTERISK		'*'
#define ED203_DATA_STR00		"00"

#define ED203_DB_HKKJKFLG_CHUU		"1 "
#define ED203_DB_KNSFLG_HORYU		'H'
#define ED203_DB_KNSFLG_DONE		'E'
#define ED203_DB_KKASSFLG_MAX		'9'

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// デフォルトINIファイル
#define MYAPP_INIFILE "./ED203.ini"
// ログファイルINIファイル
#define MYAPP_LOGINIFILE "./ED203_LOG.ini"

/******************************************************************************/
/* 構造体定義																  */
/******************************************************************************/
// 報告データ構造体
typedef struct {
	char	cUTKYMD[8];		// ＢＭＬ受付年月日
							// [YYYYMMDD]に変換して設定
	char	cKNTNO[6];		// 検体Ｎｏ．
							// 左から11桁を↓のように変換
							// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
							// (変換後)[4][5][6][7][8][9]
	char	cFILLER1[5];	// FILLER
	char	cOYAKMKCD[4];	// 親項目コード
							// 右から4桁を設定
	char	cKMKCD[4];		// 項目コード
							// 右から4桁を設定
	char	cWSCD[3];		// ＷＳコード（サンプリングコード）
							// 右から3桁を設定
	char	cWSSEQ[4];		// ＷＳＳＥＱ（検査ＳＥＱ）
							// 数値を文字列変換後、右から4桁を設定（wｼwﾜwﾙwｹwﾊwﾝwﾘwｻなし）
	char	cKNSKKA[6];		// 検査結果
							// 検査結果１or検査結果２（検査結果１優先）
							// 検査結果１：右から6桁を設定（wｼwﾜwﾙwｹwﾊwﾝwﾘwｻあり、小数点削除）
							// 検査結果２：検査結果区分='0'→'*'+左2桁目から6桁目まで
							// 　　　　　　以外→左から6桁を設定（2バイト文字に注意する）
	char	cKKACMT[3];		// 結果コメント
							// 右から3桁を設定
	char	cIJKBN;			// 異常値マーク区分
							// 異常値区分（男、女、不明）が'4','5','6'以外であれば'*'
	char	cFILLER2[6];	// FILLER
	char	cLF;			// LF
} ED203Rec;

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
	char	cDirDataFile[1024];		// 報告データファイル出力ディレクトリ
	char	cDebugLogName[1024];	// デバッグログファイル名
	char	cTraceLogName[1024];	// トレースログファイル名
	char	cAccessLogName[1024];	// アクセスログファイル名
	char	cErrorLogName[1024];	// エラーログファイル名
	int		proc_mode;				// 処理モード	0：過渡期   1：次世代
	char	cUpdateId[128];			// 更新者ID
	char	cUpdateName[128];		// 更新者
	char	cLogName[128];			// ログ
} ED203Env;

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言															  */
/******************************************************************************/
void ED203ConvTimestamp(ULONG ulTm, char *pDest);
int ED203ConvNumber(char *pDest, char *pSrc);
int ED203CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int ED203CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[], ED203Env *pEnv );
int mainFunction( ED203Env *pEnv );
void endFunction( ED203Env *pEnv );
int ED203MakeData(Kekka *pKekka, ED203Rec *pED203Rec);
int ED203DataFileFilter(struct dirent *pDirEnt);
int ED203HulftFileFilter(struct dirent *pDirEnt);
int ED203WriteFile(FILE *fp, ED203Rec *pED203Rec, int iRecCnt);
int ED203CreateFile(ED203Env *pEnv, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName);

//  共有メモリ操作関数
static  int sFncShmCrt ( ED203Env * );
static  int sFncShmGet ( ED203Env * , int *);
static  int sFncShmDel ( ED203Env * );
//  トレース用
static  void	_sFncEnvDip ( ED203Env * );
//ログ関数
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif

