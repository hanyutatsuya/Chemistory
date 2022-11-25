/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：AD205Buntekai.h								*/
/*		概要		：分注展開処理ヘッダーファイル					*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/01/19		E.Osada			Create					*/
/*  4.01    2009-02-20      K.Ameno         緊急SUN EOSL対応        */
/********************************************************************/
#ifndef _AD205Buntekai_h
#define _AD205Buntekai_h

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <iconv.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <stdarg.h>
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_date.h"
#include "Bunchu.h"
#include "A205knja.h"
#include "A205irai.h"
#include "Kmkmst.h"
#include "A205knsgmst.h"
#include "A205zoku.h"
#include "Ninsiki.h"
#include "A205korder.h"
#include "A205realchk.h"
#include "Asyscdlmst.h"
#include "Trmst.h"
//#include "Skchkmst.h"
#include "A205sknchk.h"
#include "Krkmkmst.h"
#include "Kskbrmst.h"
#include "A205rngchk.h"
#include "Sysknrmst.h"
#include "A205Jdkmk.h"
#include "A205kmkmst.h"
#include "A205kjnmst.h"
#include "Calckmkmst.h"
#include "A205wsseq.h"
#include "Rkmst.h"
/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define MYAPP_APP_NAME          "AD205"
#define RETRY_NAME				"skip_"
#define SKIP_NAME				"zger_"
#define ERR_NAME				"iser_"
#define RETURN_NAME				"RETURN_"
#define BUNCHU_RECV_KIND		"CHK"
#define BUNCHU_RECV_KIND1	"HIBUN"
#define	BUNCHU_SYBT				"R1"
#define	BUNCHU_SYBT_END			"R2"
#define BUNCHU_SYBT_HED			"HD"
#define BUNCHU_SYBT_STP			"TR"
#define BUNCHU_END_OK			"11111"
#define BUNCHU_END_NUM			5
//  内部ステータスコード定義
typedef enum {
	BUNCHU_STSCODE_NORMAL,
	BUNCHU_STSCODE_ERR_USEGE,
	BUNCHU_STSCODE_ERR_PRM_FILE,
	BUNCHU_STSCODE_ERR_PRM_GET,
	BUNCHU_STSCODE_ERR_SHM_AT,
	BUNCHU_STSCODE_ERR_SHM_DT,
	BUNCHU_STSCODE_ERR_SHM_DEL,
	BUNCHU_STSCODE_ERR_SHM_GET,
	BUNCHU_STSCODE_ERR_DIR,
	BUNCHU_STSCODE_ERR_FR_FILE
} BUNCHU_STSCODE ;

//  エラーコード定義
#define MYAPP_LOG_ERRCODE_NON       "00000000"
#define MYAPP_LOG_ERRCODE_APP       "010"
#define MYAPP_LOG_ERRCODE_DB        "020"
#define MYAPP_LOG_ERRCODE_ETC       "0Z0"

//	パラメータ文字列
#define	BUNCHU_PRM_DIR_BUNCHU	"DIR_BUNCHU"		//分注情報
#define	BUNCHU_PRM_DIR_BUNCHU_OK	"DIR_BUNCHU_OK"		//分注情報既読
#define	BUNCHU_PRM_DIR_BUNCHU_NG	"DIR_BUNCHU_NG"		//分注情報エラー
#define BUNCHU_PRM_DIR_TRAY		"DIR_TRAY"			//トレー情報
#define BUNCHU_PRM_DIR_TRAY_OK	"DIR_TRAY_OK"		//トレー情報既読
#define BUNCHU_PRM_DIR_TRAY_NG	"DIR_ERR_LST"		//エラーリスト
#define	BUNCHU_PRM_DIR_LOG		"DIR_LOG"			//ログ
#define	BUNCHU_PRM_FILE_DBG		"FILE_DBG_NSME"		//デバッグ
#define	BUNCHU_PRM_FILE_TR		"FILE_TR_NAME"		//トレース
#define	BUNCHU_PRM_FILE_ACS		"FILE_ACS_NAME"		//アクセス
#define	BUNCHU_PRM_FILE_ERR		"FILE_ERR_NAME"		//エラー
#define BUNCHU_PRM_UP_ID		"UPDATE_ID"			//更新者ID
#define BUNCHU_PRM_UP_NM		"UPDATE_NM"			//更新者
#define BUNCHU_PRM_PROC_MD		"PROC_MD"			//実行モード

#define BUNCHU_PRM_DB			"DBNAME"
#define BUNCHU_PRM_UID			"DBUSER"
#define BUNCHU_PRM_PWD			"DBPAWD"
#define BUNCHU_PRM_LBCD			"LABOCD"
#define BUNCHU_PRM_STCD			"SATECD"

#define	BUNCHU_PRM_SHM_KEY			"SHM_KEY"
#define	BUNCHU_PRM_SLEEP_SEC		"SLEEP_SEC"

//	ディレクトリ格納サイズ
#define	BUNCHU_DIR_SIZE			(512)

//	ファイル名サイズ
#define	BUNCHU_FILE_SIZE			(1024)

//	共有メモリサイズ
#define	BUNCHU_SHM_SIZE			sizeof ( int )

//	受信ファイル関連
#define	BUNCHU_RECV_SFX			".dat"
#define	BUNCHU_RECV_RECSIZE		(1024)

//分注情報ファイルの項目コード先頭位置
#define BUNCHU_KMK_ADR			(101)

//項目コード桁数
#define BUNCHU_KMK_SZ				(7)

//項目コードMAX
#define BUNCHU_KMK_MAX				(64)

//トレー＆ラックポジション数
#define	MAXPOS	10
#define	MAXPOSOLD	100
#define MAXRACK 20

//ログファイルINIファイル
#define MYAPP_LOGINIFILE "/home/kea00sys/bin/AD205_LOG.ini"
//ソートキーINIファイル
#define MYAPP_SORTINIFILE "/home/kea00sys/bin/AD205_SORT.ini"

/* 2009-02-20 緊急SUN EOSL対応 INS START */
#define TRID_BLANK "____0000"
/* 2009-02-20 緊急SUN EOSL対応 INS END */


//展開エラーリスト用
#define SYBT_BUNCH		"分注情報"
/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
typedef struct {
	char	sData[5];
	char	sKey[4];
} BUNSORT;
struct	bunchuEnv	{
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;

	int		shm_Id ;

	key_t	shm_Key ;
	int		sleep_Sec ;
	char	cDirBunchu[BUNCHU_DIR_SIZE];		// 分注結果情報ファイル格納ディレクトリ
	char	cDirBunchuOK[BUNCHU_DIR_SIZE];		// 分注結果情報ファイル格納ディレクトリ(既読)
	char	cDirBunchuNG[BUNCHU_DIR_SIZE];		// 分注結果情報ファイル格納ディレクトリ(エラー)
	char	cDirTryinfo[BUNCHU_DIR_SIZE];		//トレーNo情報ファイル格納ディレクトリ
	char	cDirTryinfoOK[BUNCHU_DIR_SIZE];		//トレーNo情報ファイル格納ディレクトリ(既読)
	char	cDirTryinfoNG[BUNCHU_DIR_SIZE];		//エラーリストファイル格納ディレクトリ
	char	cDirLog[BUNCHU_DIR_SIZE];			// ログファイル格納ディレクトリ
	char	cDebugLogName[BUNCHU_FILE_SIZE];	// デバッグログファイル名
	char	cTraceLogName[BUNCHU_FILE_SIZE];	// トレースログファイル名
	char	cAccessLogName[BUNCHU_FILE_SIZE];	// アクセスログファイル名
	char	cErrorLogName[BUNCHU_FILE_SIZE];	// エラーログファイル名
	int		proc_mode;							//処理モード	0：過渡期	1：次世代
	char	cUpdateId[128];						//更新者ID
	char	cUpdateName[128];					//更新者
	char	cLogName[128];						//ログ
	char	sPutDir[BUNCHU_DIR_SIZE];
	char	sDbName[BUNCHU_FILE_SIZE];
	char	sDbUser[BUNCHU_FILE_SIZE];
	char	sDbPswd[BUNCHU_FILE_SIZE];
	char	sLbcd[BUNCHU_FILE_SIZE];
	char	sSateid[BUNCHU_FILE_SIZE];
	int		pSortNo;
	BUNSORT	*pSort;
} ;

// 分注結果情報ファイル
typedef struct {
	char	sDataSybt[2];		//データ識別子
	char	sTranId[6];			//トランザクションID
	char	sRackId[8];			//アッセイラックID
	char	sUkebi[8];			//受付年月日
	char	sIchi[3];			//位置１
	char	sUkebiBML[8];		//BML受付日
	char	sIraiNo[11];		//依頼書No
	char	sKentaiNo[11];		//検体No
	char	sKenChkChar[2];		//検体チェック文字
	char	sWStandoku[1];		//WS単独
	char	sSexKbn[1];			//性別区分
	char	sAgeKbn[1];			//年齢区分
	char	sAge[3];			//年齢
	char	sChikuTm[4];		//畜尿時間
	char	sChikuTmTni[1];		//畜尿時間(単位)
	char	sChikuRyo[5];		//畜尿量
	char	sChikuRyoTani[1];	//畜尿量(単位)
	char	sSisetuCd[7];		//施設コード
	char	sEigyoCd[3];		//営業コード
	char	sMotoKenRk[8];		//元検体ラックID
	char	sMotoKenPos[3];		//元検体ポジション
	char	sWS[4];				//WSコード
	char	sKmkCd64[7];		//検査項目コード64
	char	sKmkCd63[7];		//検査項目コード63
	char	sKmkCd62[7];		//検査項目コード62
	char	sKmkCd61[7];		//検査項目コード61
	char	sKmkCd60[7];		//検査項目コード60
	char	sKmkCd59[7];		//検査項目コード59
	char	sKmkCd58[7];		//検査項目コード58
	char	sKmkCd57[7];		//検査項目コード57
	char	sKmkCd56[7];		//検査項目コード56
	char	sKmkCd55[7];		//検査項目コード55
	char	sKmkCd54[7];		//検査項目コード54
	char	sKmkCd53[7];		//検査項目コード53
	char	sKmkCd52[7];		//検査項目コード52
	char	sKmkCd51[7];		//検査項目コード51
	char	sKmkCd50[7];		//検査項目コード50
	char	sKmkCd49[7];		//検査項目コード49
	char	sKmkCd48[7];		//検査項目コード48
	char	sKmkCd47[7];		//検査項目コード47
	char	sKmkCd46[7];		//検査項目コード46
	char	sKmkCd45[7];		//検査項目コード45
	char	sKmkCd44[7];		//検査項目コード44
	char	sKmkCd43[7];		//検査項目コード43
	char	sKmkCd42[7];		//検査項目コード42
	char	sKmkCd41[7];		//検査項目コード41
	char	sKmkCd40[7];		//検査項目コード40
	char	sKmkCd39[7];		//検査項目コード39
	char	sKmkCd38[7];		//検査項目コード38
	char	sKmkCd37[7];		//検査項目コード37
	char	sKmkCd36[7];		//検査項目コード36
	char	sKmkCd35[7];		//検査項目コード35
	char	sKmkCd34[7];		//検査項目コード34
	char	sKmkCd33[7];		//検査項目コード33
	char	sKmkCd32[7];		//検査項目コード32
	char	sKmkCd31[7];		//検査項目コード31
	char	sKmkCd30[7];		//検査項目コード30
	char	sKmkCd29[7];		//検査項目コード29
	char	sKmkCd28[7];		//検査項目コード28
	char	sKmkCd27[7];		//検査項目コード27
	char	sKmkCd26[7];		//検査項目コード26
	char	sKmkCd25[7];		//検査項目コード25
	char	sKmkCd24[7];		//検査項目コード24
	char	sKmkCd23[7];		//検査項目コード23
	char	sKmkCd22[7];		//検査項目コード22
	char	sKmkCd21[7];		//検査項目コード21
	char	sKmkCd20[7];		//検査項目コード20
	char	sKmkCd19[7];		//検査項目コード19
	char	sKmkCd18[7];		//検査項目コード18
	char	sKmkCd17[7];		//検査項目コード17
	char	sKmkCd16[7];		//検査項目コード16
	char	sKmkCd15[7];		//検査項目コード15
	char	sKmkCd14[7];		//検査項目コード14
	char	sKmkCd13[7];		//検査項目コード13
	char	sKmkCd12[7];		//検査項目コード12
	char	sKmkCd11[7];		//検査項目コード11
	char	sKmkCd10[7];		//検査項目コード10
	char	sKmkCd9[7];			//検査項目コード9
	char	sKmkCd8[7];			//検査項目コード8
	char	sKmkCd7[7];			//検査項目コード7
	char	sKmkCd6[7];			//検査項目コード6
	char	sKmkCd5[7];			//検査項目コード5
	char	sKmkCd4[7];			//検査項目コード4
	char	sKmkCd3[7];			//検査項目コード3
	char	sKmkCd2[7];			//検査項目コード2
	char	sKmkCd1[7];			//検査項目コード1
	char	sBunKiId[3];		//分注機ID
	char	sStsFlg[1];			//状態フラグ
	char	sKnsSyrui[1];		//検査種類
	char	sChiKenFlg[1];		//治験フラグ
	char	sKnkyFlg[1];		//特定・緊急フラグ
	char	sBunKekka[1];		//分注結果
	char	sFiller[466];		//フィラー
	char	sLF[1];				//終端子(LF)
}	Flbun;

//トレー情報
typedef struct {
	char	sUkeDate[9];
	char	sKentaiID[14];
	char	sIraiNo[14];
	char	sKenSybt[4];
} POS;
typedef struct {
	char	sStDate[9];
	char	sRackID[9];
/* 2009-02-20 緊急SUN EOSL対応 INS START */
	char	sPutDir[BUNCHU_DIR_SIZE];
/* 2009-02-20 緊急SUN EOSL対応 INS END */
	int iMaxSeq;
	int iMinSeq;
	int iKntSuu;
	POS strPosInfo[MAXPOS+1];
} RACK;
typedef struct {
	char	sTryID[9];
	char	sStDate[9];
	char	sPutDir[BUNCHU_DIR_SIZE];
	int iMaxSeq;
	int iMinSeq;
	int iKntSuu;
	POS strPosInfo[MAXPOSOLD+1];
}TRAY;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
// 分注情報展開処理
int initFunction( int, char **, struct bunchuEnv * );
int mainFunction( struct bunchuEnv * );
void endFunction( struct bunchuEnv * );
int dBunchu_ins( struct bunchuEnv *, char *, RACK **s, int *, char *, int );
static int sFncTrFileRead( struct bunchuEnv *, char *, Flbun * );
static char *sFncTrFileToken( char *, char * );
static int sFncFileFillter( struct dirent * );
int ABunGetKnsgrp( Bunchu *strBunchu, Kanjya *strKanjya, char *sKmkcd, char *sKnsgrp );
// 3.02 int AbunInsZokusei( struct bunchuEnv *pst_Env, Bunchu *strBunchu, Kanjya *strKanjya );
int AbunInsZokusei( struct bunchuEnv *pst_Env, Bunchu *strBunchu, Kanjya *strKanjya , int);
//3.02 int AbunInsNinsiki( struct bunchuEnv *pst_Env, Bunchu *strBunchu, int);
int AbunInsNinsiki( struct bunchuEnv *pst_Env, Bunchu *strBunchu, int, int);
int AbufInsOrder( struct bunchuEnv *pst_Env, Irai *pIrai, Bunchu *pBun, Kanjya *pKan, Kenorder *pOrder);
int AbunInsChk( struct bunchuEnv *pst_Env, Kenorder *pOrder, Kanjya *pKan);
int AerrFilePut( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut1( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut2( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut3( struct bunchuEnv *pEnv, char *sData );
int AerrFilePut4( struct bunchuEnv *pEnv, char *sData, char * );
int AgetSortInfo(BUNSORT **strBun );
int AbunGetSort(struct bunchuEnv *pst_Env, char *sId, char flg );
int dBunEnd( struct bunchuEnv *pst_Env, char *sTrId );
void nowdateget1( char *sysdttm );
int ADateChk( char *sDate );
int ATimeChk( char *sTime );
void ABunchuChk( Bunchu *pBunch );
void AKenzokChk( Kenzok *pKenzok );
void ANinsikiChk( Ninsiki *pNinsiki );
void AKenorderChk( Kenorder *pKen );
void ARealchkChk( Realchk  *pReal );
int     sj2euc(char *, char *, int);
int ABunJido( struct bunchuEnv *pst_Env, Irai *pIrai, Bunchu *pBun, Kanjya *pKan, Kenorder *pOrder, int iLine, int Nflg );
int getKnsKaisibi(char *sKnsgrp, char *sDateK, char *sDateH );
int getShoribi( char *sLbcd, char *sSatecd, char *sSyri );
int GetKjnNo(char *, char *, char *, char, char *, char *, int *);
//2.01 DELL int chkBunchu( struct bunchuEnv *, int, Bunchu *, char *);
int chkBunchu( struct bunchuEnv *, int, Bunchu *, char *, int);
/* 2009-02-20 緊急SUN EOSL対応 INS START */
//int insWsseqknri( char *sSriymd, char *sKnsgrp, char *sTrid, int iKntno, int iMinSeq, int iMaxSeq );
int sFncChkDigit( char * );
/* 2009-02-20 緊急SUN EOSL対応 INS END */
//  共有メモリ操作関数
static  int sFncShmCrt ( struct bunchuEnv * ) ;
static  int sFncShmGet ( struct bunchuEnv * , int *) ;
static  int sFncShmDel ( struct bunchuEnv * ) ;
//  トレース用
static  void    _sFncEnvDip ( struct bunchuEnv * ) ;
//ログ関数
void sFncPutLog( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... );
void sFuncPutErrlist( struct bunchuEnv *, char *, int, char *, char *, char *, 
		char *, char *, char *, ... );
#endif
/** End of File ***************************************************************/
