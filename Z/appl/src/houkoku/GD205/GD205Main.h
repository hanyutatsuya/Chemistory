/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD205Main.h									*/
/*		概要		：報告データファイル作成ヘッダーファイル		*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  1.00	2006/02/27		H.Suyama		Create					*/
/*  1.01	2006/04/06		H.Suyama		エラーコード追加		*/
/*                                          トレーラの設定値修正    */
/*  1.02	2006/04/20		H.Suyama		コード追加				*/
/*  2.00	2009/01/06		Merits K.Ameno	施設コード増桁 通信仕様変更対応    */
/********************************************************************/
#ifndef _GD205Main_h
#define _GD205Main_h

/********************************************************************/
/*  インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "GD205Sysknrmst.h"
#include "GD205Kekka.h"

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "GD205"

//  内部ステータスコード定義
typedef enum {
	GD205_STSCODE_NORMAL,
	GD205_STSCODE_ERR_USAGE,
	GD205_STSCODE_ERR_PRM_FILE,
	GD205_STSCODE_ERR_PRM_GET,
	GD205_STSCODE_ERR_SHM_AT,
	GD205_STSCODE_ERR_SHM_DT,
	GD205_STSCODE_ERR_SHM_DEL,
	GD205_STSCODE_ERR_SHM_GET,
	GD205_STSCODE_ERR_DIR,
	GD205_STSCODE_ERR_FR_FILE
} GD205_STSCODE;

//  共有メモリサイズ
#define GD205_SHM_SIZE			sizeof ( int )
#define GD205_SIZE_BUFF			1024	// データ処理用バッファサイズ

#define GD205_LEN_DATESHORT		8	// YYYYMMDDの長さ
#define GD205_LEN_NOITEM		11	// 依頼No、検体No項目の長さ
#define GD205_LEN_SRCNO         6   // 3.01 ADD 検体Noの有効桁数
#define GD205_LEN_SRCNO1		3	// 依頼No、検体Noのブロック1の長さ
#define GD205_LEN_SRCNO2		6	// 依頼No、検体Noのブロック2の長さ
#define GD205_LEN_FILEID		12	// 送信ファイルID（YYYYMMDD9999）の長さ
#define GD205_LEN_FILESEQNO		4	// 送信ファイルIDのSeqNo（9999）の長さ

#define GD205_POS_SRCNO         3   // 3.01 ADD 依頼No、検体Noのブロック1の開始位置
#define GD205_POS_SRCNO1		2	// 依頼No、検体Noのブロック1の開始位置
#define GD205_POS_SRCNO2		5	// 依頼No、検体Noのブロック2の開始位置
#define GD205_POS_DESTNO1		0	// 依頼No、検体Noの変換後のブロック1の開始位置
#define GD205_POS_DESTNO2		3	// 依頼No、検体Noの"00"の開始位置
#define GD205_POS_DESTNO3		5	// 依頼No、検体Noの変換後のブロック1の開始位置

//  パラメータファイルキー文字列
#define GD205_PRM_DBNAME		"DBNAME"		// データベース接続名
#define GD205_PRM_DBUSER		"DBUSER"		// ログインユーザ
#define GD205_PRM_DBPAWD		"DBPAWD"		// ログインパスワード
#define GD205_PRM_DIR_DATAFILE	"DIR_DATAFILE"	// 報告データファイル出力ディレクトリ
#define GD205_PRM_DIR_TODAY		"DIR_TODAY"		// 転送データファイル出力ディレクトリ
#define GD205_PRM_DIR_OLDDAY	"DIR_OLDDAY"	// 転送データファイル過去ディレクトリ
#define GD205_PRM_DIR_SENDFILE	"DIR_SENDFILE"	// 転送データファイル送信用ディレクトリ
#define GD205_PRM_DIR_SENDREQ	"DIR_SENDREQ"	// 転送データファイルREQUESTディレクトリ
#define GD205_PRM_DIR_SENDOK	"DIR_SENDOK"	// 転送データファイルOKディレクトリ
#define GD205_PRM_DIR_SENDERR	"DIR_SENDERR"	// 転送データファイルERRディレクトリ
//#define GD205_PRM_DATAFLOWID	"DATAFLOWID"	// データフローＩＤ
//#define GD205_PRM_SENDID_MOTO	"SENDID_MOTO"	// 送信元ＩＤ
//#define GD205_PRM_SENDID_SAKI	"SENDID_SAKI"	// 送信先ＩＤ
#define GD205_PRM_SLEEP_SEC		"SLEEP_SEC"		// スリープ時間（秒）
#define GD205_PRM_SHM_KEY		"SHM_KEY"		// 共有メモリキー
#define GD205_PRM_FILE_DBG		"FILE_DBG_NSME"	// デバッグ
#define GD205_PRM_FILE_TR		"FILE_TR_NAME"	// トレース
#define GD205_PRM_FILE_ACS		"FILE_ACS_NAME"	// アクセス
#define GD205_PRM_FILE_ERR		"FILE_ERR_NAME"	// エラー
#define GD205_PRM_UP_ID			"UPDATE_ID"		// 更新者ID
#define GD205_PRM_UP_NM			"UPDATE_NM"		// 更新者
#define GD205_PRM_PROC_MD		"PROC_MD"		// 実行モード
#define GD205_PRM_COMMIT_SU		"COMMIT_SU"		// 1.13 ADD KEKKA COMMIT
#define GD205_PRM_PREFIXNM		"PREFIX_NM"		// 1.13 ADD KEKKA COMMIT

//データ識別子
#define GD205_FILE_HEADERID		"HD"
#define GD205_FILE_TRAILERID	"TR"
#define GD205_FILE_DATAID		"R1"
#define GD205_FILE_LINEFEED		'\n'
#define GD205_FILE_FILLER_SIZE	121
#define GD205_FILEEXT_DATA		".dat"
#define GD205_FILEEXT_TEMP		".tmp"
//#define GD205_REC_LOOP_MAX		6
#define GD205_REC_LOOP_MAX		1
#define GD205_DATA_CHAR0		'0'
#define GD205_DATA_SPACE		' '
#define GD205_DATA_STR00		"00"
#define GD205_DATA_ASTERISK     '*'				// 3.01 ADD

//結果編集
#define GD205_KEKKA_NG     		"*340"			// 3.01 ADD 結果編集不可
#define GD205_KEKKA_LT     		"LT"			// 3.01 ADD 未満、以下
#define GD205_KEKKA_GT     		"GT"			// 3.01 ADD 以上、超え

#define GD205_DB_HKKJKFLG_CHUU		"1 "
#define GD205_DB_HKKJKFLG_ERRFILE	"4 "
#define GD205_DB_HKKJKFLG_OK		'2'
#define GD205_DB_HKKJKN_CTRLNO		'1'
#define GD205_DB_HKKJKN_PLTNO		'2'
#define GD205_DB_HKKJKN_KNSSEQ		'3'
#define GD205_DB_HKKJKN_IRINO		'4'
#define GD205_DB_HKKJKN_KNTNO		'5'
#define GD205_DB_HKKJKN_RESEND		'8'
#define GD205_DB_KNSFLG_HORYU		'H'
#define GD205_DB_KNSFLG_DONE		'E'
#define GD205_DB_KKASSFLG_MAX		'9'
#define GD205_DB_SSNTUBN_MAX		9999
// 2006-04-20 H.Suyama Add Start
#define GD205_DB_HKKKBN_CYUU		'2'
#define GD205_DB_HKKKBN_LAST		'1'
#define GD205_DB_KKAJKCD_CYUU		'1'
#define GD205_DB_KKAJKCD_LAST		'3'
// 2006-04-20 H.Suyama Add End

#define GD205_DB_HKKERRCODE_HKKJKN	"00000001"
#define GD205_DB_HKKERRCODE_HKKKNRI	"00000002"
#define GD205_DB_HKKERRCODE_CREATE	"00000003"
#define GD205_DB_HKKERRCODE_RESEND	"00000004"
#define GD205_DB_HKKERRCODE_SEQMAX	"00000005"
#define GD205_DB_HKKERRCODE_NODATA	"00000006"
// 2006-04-06 H.Suyama Add Start
#define GD205_DB_HKKERRCODE_DBACS	"00000007"
#define GD205_DB_HKKERRCODE_HULFT	"00000008"
// 2006-04-06 H.Suyama Add End

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// デフォルトINIファイル
//1.03 DELL #define MYAPP_INIFILE "./GD205.ini"
#define MYAPP_INIFILE "$HOME/appl/src/houkoku/GD205/GD205.ini"
// ログファイルINIファイル
//1.03 DELL #define MYAPP_LOGINIFILE "./GD205_LOG.ini"
#define MYAPP_LOGINIFILE "$HOME/appl/src/houkoku/GD205/GD205_LOG.ini"

/******************************************************************************/
/* 構造体定義																  */
/******************************************************************************/
// 報告データ構造体
typedef struct {
    char    cUTKYMD[8];     /* BML受付年月日 [YYYYMMDD]形式 */
    char    cKNTNO[11];     // 検体No Ver 2.00 6->11桁PNC形式に変更 */
/*	char    cFILLER1[5];*/  /* FILLER *//* Ver 2.00 削除 */
    char    cOYAKMKCD[7];   /* 親項目コード Ver2.00 4->7桁に増桁 */
    char    cKMKCD[7];      /* 項目コード Ver2.00 4->7桁に増桁 */
    char    cWSCD[4];       /* WSコード(サンプリングコード) Ver 2.00 3->4桁に増桁 */
    char    cWSSEQ[4];      /* WSSEQ(検査SEQ) */
                            // 数値を文字列変換後、右から4桁を設定（wｼwﾜwﾙwｹwﾊwﾝwﾘwｻなし）
    char    cKNSKKA[6];     /* 検査結果 */
                            /* 検査結果１or検査結果２（検査結果１優先） */
                            /* 検査結果１：右から6桁を設定（wｼwﾜwﾙwｹwﾊwﾝwﾘwｻあり、小数点削除） */
                            /* 検査結果２：検査結果区分='0'→'*'+左2桁目から6桁目まで */
                            /* 　　　　　　以外→左から6桁を設定（2バイト文字に注意する） */
    char    cKKACMT[3];     /* 結果コメント */
                            /* 右から3桁を設定 */
    char    cIJKBN;         /* 異常値マーク区分 */
                            /* 異常値区分（男、女、不明）が'4','5','6'以外であれば'*' */
    char    cFILLER2[6];    /* FILLER */
    char    cLF;            /* LF */
} GD205Rec;

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
	char	cDirToday[1024];		// 転送データファイル出力ディレクトリ
	char	cDirOldday[1024];		// 転送データファイル過去ディレクトリ
	char	cDirSendFile[1024];		// 転送データファイル送信用ディレクトリ
	char	cDirSendREQ[1024];		// 転送データファイルREQディレクトリ
	char	cDirSendOK[1024];		// 転送データファイルOKディレクトリ
	char	cDirSendERR[1024];		// 転送データファイルERRディレクトリ
	char	cDataFlowID[1024];		// データフローＩＤ
	char	cSendIDMoto[1024];		// 送信元ＩＤ
	char	cSendIDSaki[1024];		// 送信先ＩＤ
	char	cDebugLogName[1024];	// デバッグログファイル名
	char	cTraceLogName[1024];	// トレースログファイル名
	char	cAccessLogName[1024];	// アクセスログファイル名
	char	cErrorLogName[1024];	// エラーログファイル名
	int		proc_mode;				// 処理モード	0：過渡期   1：次世代
	char	cUpdateId[128];			// 更新者ID
	char	cUpdateName[128];		// 更新者
	char	cLogName[128];			// ログ
	int		iCommitSu;				// 1.13 ADD 結果情報 一括COMMIT件数
	char	cPrefixNm[1024];		// 3.01 ADD 送信ファイル先頭文字列
} GD205Env;

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/
// extern
extern      char        G_msg[256]; // 1.06 ADD LogMessage

/******************************************************************************/
/* プロトタイプ宣言															  */
/******************************************************************************/
void GD205ConvTimestamp(ULONG ulTm, char *pDest);
int GD205ConvNumber(char *pDest, char *pSrc);
int GD205CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int GD205CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[], GD205Env *pEnv );
int mainFunction( GD205Env *pEnv );
void endFunction( GD205Env *pEnv );
int GD205MakeData(Kekka *pKekka, char *pLBCD, GD205Rec *pGD205Rec);
int GD205DataFileFilter(struct dirent *pDirEnt);
int GD205WriteFile(FILE *fp, GD205Rec *pGD205Rec, int iRecCnt);

//2006.12.08 Kim Jinsuk ＤＢエラー異常時終了
//int GD205CreateFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName,int *sqlErrorFlag);
int GD205CreateFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName,Hkkknri *pHkkknriArrayOut, int *sqlErrorFlag);
//2006-07-06 CHG Osada ファイル名命名方法変更
//int GD205CreateHULFTFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt);
int GD205CreateHULFTFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt, Hkkknri *pHkkknriArrayOut);
// 2006-04-06 H.Suyama Change End
int GD205ResendFile(GD205Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri);
void GD205UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode );

//  共有メモリ操作関数
static  int sFncShmCrt ( GD205Env * );
static  int sFncShmGet ( GD205Env * , int *);
static  int sFncShmDel ( GD205Env * );
//  トレース用
static  void	_sFncEnvDip ( GD205Env * );
//ログ関数
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
