/************************************************************************/
/*									*/
/*	ＢＭＬ様向け検査システム					*/
/*									*/
/*	システム名	：次世代システム				*/
/*	ファイル名	：LD104.h					*/
/*	概要		：報告データファイル作成ヘッダーファイル	*/
/*									*/
/************************************************************************/

/************************************************************************/
/*  Ver.	作成日		名前		修正内容		*/
/* -------------------------------------------------------------------- */
/*  1.00	2019/12/27	BML.inc		Create			*/
/************************************************************************/
#ifndef _LD104_h
#define _LD104_h

/************************************************************************/
/*  インクルード宣言							*/
/************************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "LD104Sysknrmst.h"
#include "LD104GetKekka.h"

/************************************************************************/
/* Define定義								*/
/************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "LD104"

//  内部ステータスコード定義
typedef enum {
	LD104_STSCODE_NORMAL,
	LD104_STSCODE_ERR_USAGE,
	LD104_STSCODE_ERR_PRM_FILE,
	LD104_STSCODE_ERR_PRM_GET,
	LD104_STSCODE_ERR_SHM_AT,
	LD104_STSCODE_ERR_SHM_DT,
	LD104_STSCODE_ERR_SHM_DEL,
	LD104_STSCODE_ERR_SHM_GET,
	LD104_STSCODE_ERR_DIR,
	LD104_STSCODE_ERR_FR_FILE
} LD104_STSCODE;

//  共有メモリサイズ
#define LD104_SHM_SIZE			sizeof ( int )
#define LD104_SIZE_BUFF			1024	// データ処理用バッファサイズ

#define LD104_LEN_DATETIME		14	// YYYYMMDDhhmmss
#define LD104_LEN_NOITEM		11	// 依頼No、検体No項目の長さ
#define LD104_LEN_SRCNO1		3	// 依頼No、検体Noのブロック1の長さ
#define LD104_LEN_SRCNO2		6	// 依頼No、検体Noのブロック2の長さ

#define LD104_POS_SRCNO1		2	// 依頼No、検体Noのブロック1の開始位置
#define LD104_POS_SRCNO2		5	// 依頼No、検体Noのブロック2の開始位置
#define LD104_POS_DESTNO1		0	// 依頼No、検体Noの変換後のブロック1の開始位置
#define LD104_POS_DESTNO2		3	// 依頼No、検体Noの"00"の開始位置
#define LD104_POS_DESTNO3		5	// 依頼No、検体Noの変換後のブロック1の開始位置

//  パラメータファイルキー文字列
#define LD104_PRM_DBNAME		"DBNAME"	// データベース接続名
#define LD104_PRM_DBUSER		"DBUSER"	// ログインユーザ
#define LD104_PRM_DBPAWD		"DBPAWD"	// ログインパスワード
#define LD104_PRM_DIR_DATAFILE		"DIR_DATAFILE"	// 要求データファイル出力ディレクトリ
#define LD104_PRM_DIR_SEND		"DIR_SEND"	// データファイル送信ディレクトリ
#define LD104_PRM_DATAFLOWID		"DATAFLOWID"    // データフローＩＤ
#define LD104_PRM_SENDID_MOTO		"SENDID_MOTO"   // 送信元ＩＤ
#define LD104_PRM_SENDID_SAKI		"SENDID_SAKI"   // 送信先ＩＤ
#define LD104_PRM_SLEEP_MIN		"SLEEP_MIN"	// スリープ時間（分）
#define LD104_PRM_DATE_RANGE		"DATE_RANGE"	// 要求カード出力対象期間
#define LD104_PRM_SHM_KEY		"SHM_KEY"	// 共有メモリキー
#define LD104_PRM_FILE_DBG		"FILE_DBG_NSME"	// デバッグ
#define LD104_PRM_FILE_TR		"FILE_TR_NAME"	// トレース
#define LD104_PRM_FILE_ACS		"FILE_ACS_NAME"	// アクセス
#define LD104_PRM_FILE_ERR		"FILE_ERR_NAME"	// エラー

//データ識別子
#define LD104_FILEEXT_DATA		".kka"
#define LD104_FILEEXT_TEMP		".tmp"
#define LD104_REC_LOOP_MAX		6
#define LD104_DATA_CHAR0		'0'
#define LD104_DATA_SPACE		' '
#define LD104_DATA_STR00		"00"

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// デフォルトINIファイル
#define MYAPP_INIFILE "$HOME/bin/LD104.ini"
// ログファイルINIファイル
#define MYAPP_LOGINIFILE "$HOME/bin/LD104_LOG.ini"

/************************************************************************/
/* 構造体定義								*/
/************************************************************************/
// 報告データ構造体
typedef struct {
	char	c_sbt[3];		// ﾚｺｰﾄﾞ識別子([R1]固定)
	char	c_utkymd[8];		// ＢＭＬ受付年月日 [YYYYMMDD]に変換して設定
	char	c_irino[11];		// 依頼書Ｎｏ．左から11桁を↓のように変換
					// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
					// (変換後)[3][4][5] 0  0 [6][7][8][9][10][11]
	char	c_kmkcd[7];		// 項目コード
	char	c_filler[994];		// FILLER
	char	c_kaigyo[1];		// 改行ｺｰﾄﾞ
} LD104Rec;

// ヘッダー情報
typedef struct	Z00SJHD {		// 送受信ﾍｯﾀﾞｰ(S-JIS） 1024byte
	char	c_sbt[2];		// ﾚｺｰﾄﾞ識別子([HD]固定)
	char	c_sosinsaki[8];		// 送信先
	char	c_sosinmoto[8];		// 送信元
	char	c_opedate[8];  		// 送信元処理年月日
	char	c_tuban[4];    	        // 通番
	char	c_dflow[10];		// ﾃﾞｰﾀﾌﾛｰID
	char	c_param1[128];		// ﾊﾟﾗﾒｰﾀ1
	char	c_param2[128];		// ﾊﾟﾗﾒｰﾀ2
	char	c_yobi[216];		// 予備
	char	c_filler[511];		// FILLER
	char	c_kaigyo[1];		// 改行ｺｰﾄﾞ
} LD104Header;

typedef struct	Z01SJTR {		// 送受信ﾄﾚｰﾗｰ(S-JIS） 1024byte
	char	c_sbt[2];		// ﾚｺｰﾄﾞ識別子([TR]固定)
	char	c_sosinsaki[8];		// 送信先
	char	c_sosinmoto[8];		// 送信元
	char	c_opedate[8];		// 送信元処理年月日
	char	c_tuban[4];		// 通番
	char	c_dflow[10];		// ﾃﾞｰﾀﾌﾛｰID
	char	c_reccnt[8];		// 物理ﾚｺｰﾄﾞ件数
	char	c_reccnt01[8];		// 論理ﾚｺｰﾄﾞ件数１
	char	c_reccnt02[112];	// 論理ﾚｺｰﾄﾞ件数２～１５( 0 固定)
	char	c_yobi[344];		// 予備 
	char	c_filler[511];		// FILLER
	char	c_kaigyo[1];		// 改行ｺｰﾄﾞ
} LD104Trailer ;

// プログラム環境構造体
struct appEnv {
	BMLPRM	*bp;
	char	*pcFileNamePRM;
	int	shm_Id;				// 共有メモリID
	key_t	shm_Key;			// 共有メモリキー
	int	iSleepMin;			// スリープ時間（分）
	char	cDBName[1024];			// データベース接続名
	char	cDBUser[1024];			// ログインユーザ
	char	cDBPawd[1024];			// ログインパスワード
	char	cDataFlowID[1024];		// データフローＩＤ
	char	cSendIDMoto[1024];		// 送信元ＩＤ
	char	cSendIDSaki[1024];		// 送信先ＩＤ
	char	cDirDataFile[1024];		// 要求カードファイル出力ディレクトリ
	char	cDirSend[1024];			// 要求カードファイル送信用ディレクトリ
	int	DateRange ;			// 要求カード出力対象期間
	char	cDebugLogName[1024];		// デバッグログファイル名
	char	cTraceLogName[1024];		// トレースログファイル名
	char	cAccessLogName[1024];		// アクセスログファイル名
	char	cErrorLogName[1024];		// エラーログファイル名
	char	cLogName[128];			// ログ
} pAppEnv;

/**************************************************************************/
/* グローバル宣言							  */
/**************************************************************************/
extern	char	G_msg[256]; // LogMessage

/**************************************************************************/
/* プロトタイプ宣言							  */
/**************************************************************************/
void LD104ConvTimestamp(ULONG ulTm, char *pDest);
int LD104ConvNumber(char *pDest, char *pSrc);
int LD104CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int LD104CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[] );
int mainFunction();
void endFunction();
int LD104MakeData(GetKekka *pGetKekka, LD104Rec *pLD104Rec);
int LD104DataFileFilter(struct dirent *pDirEnt);
int LD104WriteFile(FILE *fp, LD104Rec *pLD104Rec);
int LD104CreateFile(Sysknrmst *pSysKnrmst, GetKekka *pGetKekkaArrayOut, int iKekkaNumOut);

void sFncGetdate( char *, char *, int );

//  共有メモリ操作関数
static  int sFncShmCrt();
static  int sFncShmGet(int *);
static  int sFncShmDel();
//  トレース用
static  void	_sFncEnvDip();
//ログ関数
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***********************************************************/
