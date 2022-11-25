/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD105Main.h									*/
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
/*  2.00	2009/05/19		K.Moriya		結果変換マスタ対応		*/
/********************************************************************/
#ifndef _GD105Main_h
#define _GD105Main_h

/********************************************************************/
/*  インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "GD105Sysknrmst.h"
#include "GD105Kekka.h"
/* 2.00 2009.05.19 結果変換マスタ対応 START */
#include "GD105KkaConvChk.h"
/* 2.00 2009.05.19 結果変換マスタ対応 END */

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/
#define CHAR_KANJI		  0x80
#define iskanji(c)  ((c) & CHAR_KANJI)

#define MYAPP_APP_NAME		  "GD105"

//  内部ステータスコード定義
typedef enum {
	GD105_STSCODE_NORMAL,
	GD105_STSCODE_ERR_USAGE,
	GD105_STSCODE_ERR_PRM_FILE,
	GD105_STSCODE_ERR_PRM_GET,
	GD105_STSCODE_ERR_SHM_AT,
	GD105_STSCODE_ERR_SHM_DT,
	GD105_STSCODE_ERR_SHM_DEL,
	GD105_STSCODE_ERR_SHM_GET,
	GD105_STSCODE_ERR_DIR,
	GD105_STSCODE_ERR_FR_FILE
} GD105_STSCODE;

//  共有メモリサイズ
#define GD105_SHM_SIZE			sizeof ( int )
#define GD105_SIZE_BUFF			1024	// データ処理用バッファサイズ

#define GD105_LEN_DATESHORT		8	// YYYYMMDDの長さ
#define GD105_LEN_NOITEM		11	// 依頼No、検体No項目の長さ
#define GD105_LEN_SRCNO1		3	// 依頼No、検体Noのブロック1の長さ
#define GD105_LEN_SRCNO2		6	// 依頼No、検体Noのブロック2の長さ
#define GD105_LEN_FILEID		12	// 送信ファイルID（YYYYMMDD9999）の長さ
#define GD105_LEN_FILESEQNO		4	// 送信ファイルIDのSeqNo（9999）の長さ

#define GD105_POS_SRCNO1		2	// 依頼No、検体Noのブロック1の開始位置
#define GD105_POS_SRCNO2		5	// 依頼No、検体Noのブロック2の開始位置
#define GD105_POS_DESTNO1		0	// 依頼No、検体Noの変換後のブロック1の開始位置
#define GD105_POS_DESTNO2		3	// 依頼No、検体Noの"00"の開始位置
#define GD105_POS_DESTNO3		5	// 依頼No、検体Noの変換後のブロック1の開始位置

//  パラメータファイルキー文字列
#define GD105_PRM_DBNAME		"DBNAME"		// データベース接続名
#define GD105_PRM_DBUSER		"DBUSER"		// ログインユーザ
#define GD105_PRM_DBPAWD		"DBPAWD"		// ログインパスワード
#define GD105_PRM_DIR_DATAFILE	"DIR_DATAFILE"	// 報告データファイル出力ディレクトリ
#define GD105_PRM_DIR_TODAY		"DIR_TODAY"		// 転送データファイル出力ディレクトリ
#define GD105_PRM_DIR_OLDDAY	"DIR_OLDDAY"	// 転送データファイル過去ディレクトリ
#define GD105_PRM_DIR_SENDFILE	"DIR_SENDFILE"	// 転送データファイル送信用ディレクトリ
#define GD105_PRM_DIR_SENDREQ	"DIR_SENDREQ"	// 転送データファイルREQUESTディレクトリ
#define GD105_PRM_DIR_SENDOK	"DIR_SENDOK"	// 転送データファイルOKディレクトリ
#define GD105_PRM_DIR_SENDERR	"DIR_SENDERR"	// 転送データファイルERRディレクトリ
#define GD105_PRM_DATAFLOWID	"DATAFLOWID"	// データフローＩＤ
#define GD105_PRM_SENDID_MOTO	"SENDID_MOTO"	// 送信元ＩＤ
#define GD105_PRM_SENDID_SAKI	"SENDID_SAKI"	// 送信先ＩＤ
#define GD105_PRM_SLEEP_SEC		"SLEEP_SEC"		// スリープ時間（秒）
#define GD105_PRM_SHM_KEY		"SHM_KEY"		// 共有メモリキー
#define GD105_PRM_FILE_DBG		"FILE_DBG_NSME"	// デバッグ
#define GD105_PRM_FILE_TR		"FILE_TR_NAME"	// トレース
#define GD105_PRM_FILE_ACS		"FILE_ACS_NAME"	// アクセス
#define GD105_PRM_FILE_ERR		"FILE_ERR_NAME"	// エラー
#define GD105_PRM_UP_ID			"UPDATE_ID"		// 更新者ID
#define GD105_PRM_UP_NM			"UPDATE_NM"		// 更新者
#define GD105_PRM_PROC_MD		"PROC_MD"		// 実行モード
#define GD105_PRM_COMMIT_SU		"COMMIT_SU"		// 1.13 ADD KEKKA COMMIT

//データ識別子
#define GD105_FILE_HEADERID		"HD"
#define GD105_FILE_TRAILERID	"TR"
#define GD105_FILE_DATAID		"R1"
#define GD105_FILE_LINEFEED		'\n'
#define GD105_FILE_FILLER_SIZE	121
#define GD105_FILEEXT_DATA		".dat"
#define GD105_FILEEXT_TEMP		".tmp"
#define GD105_REC_LOOP_MAX		6
#define GD105_DATA_CHAR0		'0'
#define GD105_DATA_SPACE		' '
#define GD105_DATA_STR00		"00"

#define GD105_DB_HKKJKFLG_CHUU		"1 "
#define GD105_DB_HKKJKFLG_ERRFILE	"4 "
#define GD105_DB_HKKJKFLG_OK		"2 "
#define GD105_DB_HKKJKFLG_OK_DBERR	"9 "
#define GD105_DB_HKKJKN_CTRLNO		'1'
#define GD105_DB_HKKJKN_PLTNO		'2'
#define GD105_DB_HKKJKN_KNSSEQ		'3'
#define GD105_DB_HKKJKN_IRINO		'4'
#define GD105_DB_HKKJKN_KNTNO		'5'
#define GD105_DB_HKKJKN_RESEND		'8'
#define GD105_DB_KNSFLG_HORYU		'H'
#define GD105_DB_KNSFLG_DONE		'E'
#define GD105_DB_KKASSFLG_MAX		'9'
#define GD105_DB_SSNTUBN_MAX		9999
// 2006-04-20 H.Suyama Add Start
#define GD105_DB_HKKKBN_CYUU		'2'
#define GD105_DB_HKKKBN_LAST		'1'
#define GD105_DB_KKAJKCD_CYUU		'1'
#define GD105_DB_KKAJKCD_LAST		'3'
// 2006-04-20 H.Suyama Add End

#define GD105_DB_HKKERRCODE_HKKJKN	"00000001"
#define GD105_DB_HKKERRCODE_HKKKNRI	"00000002"
#define GD105_DB_HKKERRCODE_CREATE	"00000003"
#define GD105_DB_HKKERRCODE_RESEND	"00000004"
#define GD105_DB_HKKERRCODE_SEQMAX	"00000005"
#define GD105_DB_HKKERRCODE_NODATA	"00000006"
// 2006-04-06 H.Suyama Add Start
#define GD105_DB_HKKERRCODE_DBACS	"00000007"
#define GD105_DB_HKKERRCODE_HULFT	"00000008"
// 2006-04-06 H.Suyama Add End

#define MYAPP_LOG_ERRCODE_NON		"00000000"
#define MYAPP_LOG_ERRCODE_APP		"010"
#define MYAPP_LOG_ERRCODE_DB		"020"
#define MYAPP_LOG_ERRCODE_ETC		"0Z0"

// デフォルトINIファイル
//#define MYAPP_INIFILE "$HOME/appl/src/houkoku/GD105/GD105.ini"
#define MYAPP_INIFILE "$HOME/bin/GD105.ini"
// ログファイルINIファイル
//#define MYAPP_LOGINIFILE "$HOME/appl/src/houkoku/GD105/GD105_LOG.ini"
#define MYAPP_LOGINIFILE "$HOME/bin/GD105_LOG.ini"

/******************************************************************************/
/* 構造体定義																  */
/******************************************************************************/
// ファイルヘッダ
typedef struct {
	char	cID[2];				// レコード識別子
	char	cSendToID[8];		// 送信先ID
	char	cSendFromID[8];		// 送信元ID
	char	cSendDate[8];		// 送信元処理年月日
	char	cSeqNo[4];			// 通番
	char	cDataFlowID[10];	// ﾃﾞｰﾀﾌﾛｰID
	char	cParam1[128];		// ﾊﾟﾗﾒｰﾀ1
	char	cParam2[128];		// ﾊﾟﾗﾒｰﾀ2
	char	cReserve[728];		// 予備
} FILEHEADER;

// ファイルトレーラ
typedef struct {
	char	cID[2];				// レコード識別子
	char	cSendToID[8];		// 送信先ID
	char	cSendFromID[8];		// 送信元ID
	char	cSendDate[8];		// 送信元処理年月日
	char	cSeqNo[4];			// 通番
	char	cDataFlowID[10];	// ﾃﾞｰﾀﾌﾛｰID
	char	cPhysicalCnt[8];	// 物理ﾚｺｰﾄﾞ件数
	char	cRecCnt1[8];		// 論理ﾚｺｰﾄﾞ件数１
	char	cRecCnt2[8];		// 論理ﾚｺｰﾄﾞ件数２
	char	cRecCnt3[8];		// 論理ﾚｺｰﾄﾞ件数３
	char	cRecCnt4[8];		// 論理ﾚｺｰﾄﾞ件数４
	char	cRecCnt5[8];		// 論理ﾚｺｰﾄﾞ件数５
	char	cRecCnt6[8];		// 論理ﾚｺｰﾄﾞ件数６
	char	cRecCnt7[8];		// 論理ﾚｺｰﾄﾞ件数７
	char	cRecCnt8[8];		// 論理ﾚｺｰﾄﾞ件数８
	char	cRecCnt9[8];		// 論理ﾚｺｰﾄﾞ件数９
	char	cRecCnt10[8];		// 論理ﾚｺｰﾄﾞ件数１０
	char	cRecCnt11[8];		// 論理ﾚｺｰﾄﾞ件数１１
	char	cRecCnt12[8];		// 論理ﾚｺｰﾄﾞ件数１２
	char	cRecCnt13[8];		// 論理ﾚｺｰﾄﾞ件数１３
	char	cRecCnt14[8];		// 論理ﾚｺｰﾄﾞ件数１４
	char	cRecCnt15[8];		// 論理ﾚｺｰﾄﾞ件数１５
	char	cReserve[856];		// 予備
} FILETRAILER;

// 報告データ構造体
typedef struct {
	char	cUTKYMD[8];		// ＢＭＬ受付年月日
							// [YYYYMMDD]に変換して設定
	char	cIRINO[11];		// 依頼書Ｎｏ．
							// 左から11桁を↓のように変換
							// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
							// (変換後)[3][4][5] 0  0 [6][7][8][9][10][11]
	char	cKMKCD[7];		// 項目コード
	char	cKNTNO[11];		// 検体Ｎｏ．
							// 左から11桁を↓のように変換
							// (変換前)[1][2][3][4][5][6][7][8][9][10][11]
							// (変換後)[3][4][5] 0  0 [6][7][8][9][10][11]
	char	cOYAKMKCD[7];	// 親項目コード
	char	cKNSKKA1[8];	// 検査結果１
							// 右から8桁を設定（ｾﾞﾛｻﾌﾟﾚｽあり）
	char	cKNSKKA2[8];	// 検査結果２
							// 左から8桁を設定（2バイト文字に注意する）
	char	cKNSKKA2KBN;	// 結果２区分
							// 左から1桁を設定
	char	cKKAHSKCD[3];	// 結果補足コード
	char	cKKACMT1[4];	// 結果コメント１
							// 右から4桁を設定
	char	cKKACMT2[4];	// 結果コメント２
							// 右から4桁を設定
	char	cIJKBNM;		// 異常値区分（男）
	char	cIJKBNF;		// 異常値区分（女）
	char	cIJKBNN;		// 異常値区分（不明）
	char	cSDI[3];		// 指数（ＳＤ１）
	char	cKJNO[3];		// 基準値Ｎｏ．
	char	cLABOARVDT[8];	// ラボ着日
							// 空白を設定
	char	cKNSENDDT[8];	// 検査完了予定日
							// 空白を設定
	char	cEXTKKADBIDCD;	// 拡張結果DB識別ｺｰﾄﾞ
							// [0]を設定
	char	cKKAJKCD;		// 結果状況コード
	char	cPNCRGFLG;		// パニックレンジフラグ
	char	cSMPCD[4];		// ＷＳコード
							// 右から4桁を設定
	char	cKNSSEQ[6];		// 検査ＳＥＱ
							// 数値を文字列に変換後、右から6桁を設定。
							// （ｾﾞﾛｻﾌﾟﾚｽなし）
	char	cZRCD[3];		// 推定材料コード
							// 右から3桁設定
	char	cKKAKSFLG;		// 結果換算フラグ
	char	cKKASSFLG;		// 結果修正フラグ
	char	cHSYKFLG;		// 非照会フラグ
	char	cHSKFLG;		// 非請求区分
	char	cHHKKFLG;		// 非報告フラグ
	char	cKNSIDCD;		// 検査識別コード
							// [0]を設定
	char	cLBCD[3];		// 検査実施ラボコード
	char	cRESERVE[28];	// 予約フィールド
							// 空白を設定
} GD105Rec;

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
} GD105Env;

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/
// extern
extern      char        G_msg[256]; // 1.06 ADD LogMessage

/******************************************************************************/
/* プロトタイプ宣言															  */
/******************************************************************************/
void GD105ConvTimestamp(ULONG ulTm, char *pDest);
int GD105ConvNumber(char *pDest, char *pSrc);
int GD105CopyFromLeft(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);
int GD105CopyFromRight(char *pDest, char *pSrc, int iSize, BOOL bMbFlg);

int initFunction( int argc, char *argv[], GD105Env *pEnv );
int mainFunction( GD105Env *pEnv );
void endFunction( GD105Env *pEnv );
int GD105MakeData(Kekka *pKekka, char *pLBCD, GD105Rec *pGD105Rec);
int GD105DataFileFilter(struct dirent *pDirEnt);
int GD105WriteFile(FILE *fp, GD105Rec *pGD105Rec, int iRecCnt);

//2006.12.08 Kim Jinsuk ＤＢエラー異常時終了
int GD105CreateFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *piHkkssknsu, int *piHkkhrysu, char *pFileName,int *sqlErrorFlag);
// 2006-04-06 H.Suyama Change Start

//2006-07-06 CHG Osada ファイル名命名方法変更
int GD105CreateHULFTFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri, char *pDataFile, int iLogicalCnt, Hkkknri *pHkkknriArrayOut);

//2014-01-15 sekiya ファイル作成とフラグ更新を分ける対応
int GD105UpdateKekka(GD105Env *pEnv, Sysknrmst *pSysknrmst, Kekka *pKekkaArrayOut, int iKekkaNumOut, int *sqlErrorFlag);

// 2006-04-06 H.Suyama Change End
int GD105ResendFile(GD105Env *pEnv, Sysknrmst *pSysknrmst, Hkkknri *pHkkknri);
void GD105UpdateHkkknriSts( Hkkknri *pHkkknri, char *pHkkjkflg, char *pHkkerrcode );

//  共有メモリ操作関数
static  int sFncShmCrt ( GD105Env * );
static  int sFncShmGet ( GD105Env * , int *);
static  int sFncShmDel ( GD105Env * );
//  トレース用
static  void	_sFncEnvDip ( GD105Env * );
//ログ関数
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
