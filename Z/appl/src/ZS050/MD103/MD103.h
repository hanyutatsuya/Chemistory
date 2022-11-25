/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：MD103.h                                                      */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _stocker_h
#define _stocker_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"
#include "bml_DBCom.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"MD103"
#define	MYAPP_APP_NAME_JP		"MD103"

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
#define MYAPP_SQL_NOT_FOUND		100

//	パラメータ文字列
#define	MYAPP_PRM_DIR_NR_SUP		"DIR_NR_SUP"
#define	MYAPP_PRM_DIR_NR_SUP_OK		"DIR_NR_SUP_OK"
#define	MYAPP_PRM_DIR_NR_SUP_ERR	"DIR_NR_SUP_ERR"
#define	MYAPP_PRM_DIR_ONL_DAT		"DIR_ONL_DAT"
#define	MYAPP_PRM_DIR_LANE_DAT		"DIR_LANE_DAT"
#define	MYAPP_PRM_NYUBI_CODE		"NYUBI_CODE"
#define	MYAPP_PRM_YOKETSU_CODE		"YOKETSU_CODE"
#define	MYAPP_PRM_OUDANCD_CODE		"OUDANCD_CODE"
#define	MYAPP_PRM_SEISYOKU_CODE		"SEISYOKU_CODE"
#define	MYAPP_PRM_KSKBR_B10_HYOJI	"KSKBR_B10_HYOJI"
#define	MYAPP_PRM_KSKBR_B10_CODE	"KSKBR_B10_CODE"
#define	MYAPP_PRM_KSKBR_B2_HYOJI	"KSKBR_B2_HYOJI"
#define	MYAPP_PRM_KSKBR_B2_CODE		"KSKBR_B2_CODE"
#define	MYAPP_PRM_SHM_KEY		"SHM_KEY"
#define	MYAPP_PRM_SLEEP_SEC		"SLEEP_SEC"
#define	MYAPP_PRM_DB_NAME		"DB_NAME"
#define	MYAPP_PRM_DB_USER		"DB_USER"
#define	MYAPP_PRM_DB_PASSWD		"DB_PASSWD"
#define	MYAPP_PRM_FILE_RETRY		"FILE_RETRY"

//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	受信ファイル関連
#define	MYAPP_RECV_SFX			".dat"
#define	MYAPP_RECV_SFX_END		".end"
#define	MYAPP_RECV_SFX_ERR		".err"
#define	MYAPP_RECV_RECSIZE		(512)
#define	MYAPP_RECV_COLCNT		(22)
#define	MYAPP_RACK_MAXCNT		(20)
#define	MYAPP_TRKNHSU_MAXCNT		(100)		//トレー内検体本数

//	送信ファイル関連
#define	MYAPP_SEND_KIND_OD		"OD"		//検査オーダー情報
#define	MYAPP_SEND_KIND_CH		"CH"		//即時チェック情報
#define	MYAPP_SEND_SFX			".dat"
#define	MYAPP_SEND_SFX_TMP		".tmp"
#define	MYAPP_SEND_RECSIZE		(512)

//	データサイズ
#define	MYAPP_TRNO_SIZE			(10+1)	
#define	MYAPP_STKNO_SIZE		(6+1)	
#define	MYAPP_DATE_SIZE			(10+1)	
#define	MYAPP_RKNO_SIZE			(10+1)	
#define	MYAPP_DEOF_SIZE			(20+1)	

//	分注区分フラグ
#define	MYAPP_BUNCHU_OK			(0)
#define	MYAPP_BUNCHU_NG			(1)

#define TRID_BLANK "____0000"


/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
struct	appEnv	{
	BMLPRM		*bp ;
	char		*pcFielNamePRM ;
	int		 fileRetry ;
	int		 shm_Id ;
	key_t		 shm_Key ;
	int		 sleep_Sec ;
	char		 cDb_Name[32+1] ;
	char		 cDb_User[32+1] ;
	char		 cDb_Passwd[32+1] ;
	char		 cDirNR_Sup[MYAPP_PATH_SIZE] ;
	char		 cDirNR_SupOk[MYAPP_PATH_SIZE];
	char	 	 cDirNR_SupErr[MYAPP_PATH_SIZE] ;
	char		 cDirOnl_Dat[MYAPP_PATH_SIZE] ;
	char		 cDirLane_Dat[MYAPP_PATH_SIZE] ;
	char		 cNyubiCD[7+1] ;
	char		 cYoketsuCD[7+1] ;
	char		 cOudanCD[7+1] ;
	char		 cSeisyokuCD[7+1] ;
	char		 cKskbrB10HY[16+1] ;
	char		 cKskbrB10CD[16+1] ;
	char		 cKskbrB2HY[16+1] ;
	char		 cKskbrB2CD[16+1] ;
} ;

//	トレー・ラック紐付け情報定義構造体
struct	trInfo	{
	char	 trid[MYAPP_TRNO_SIZE] ;
	char	 asyrckid[MYAPP_RACK_MAXCNT][MYAPP_RKNO_SIZE] ;
	char	 knskisymd[MYAPP_DATE_SIZE] ;
	char	 stkno[MYAPP_STKNO_SIZE] ;
} ;

//	検査オーダー情報構造体
struct my_stKENORDER
{
  char knskisymd[11];
  char sriymd[11];
  char kntno[14];
  char kntketflg[2];
  char knsgrp[17];
  char kmkcd[8];
  short knssu;
  short knssueda;
  char irihsmkbn[2];
  char irikbn[2];
  char ksktkbn[2];
  char utkymd[11];
  char irino[12];
  char iriketflg[2];
  short zssdino;
  char sstcd[8];
  char trid[11];
  short trpos;
  char asyrckid[11];
  short asyrckpos;
  char oyakmkcd[8];
  char seccd[3];
  char bkfkkbn[2];
  char smpcd[8];
  char bskkbn[5];
  char nbkmkcd[8];
  char zrcd[5];
  char ysnlbl[3];
  char kjno[4];
  char fkhkknohjkbn[2];
  char tbkjno[4];
  char tbkjflg[2];
  char htkfkhms[25];
  char skflg[2];
  char tskflg[3];
  char tktflg[3];
  char ytiksbr[16];
  char kkflg[2];
  char kkiriflg[2];
  short kkirilotno;
  char sc[6];
  char tj[6];
  char tjtni[2];
  char sbtkbn[2];
  char birthday[9];
  char birthdaykbn[2];
  char age[4];
  char agekbn[2];
  char sstme[9];
  char ssymd[11];
  char tntme[5];
  char tntni[2];
  char tnryo[6];
  char tnryotni[2];
  sqlint32 knsseq;
  short bthno;
  char knsjkflg[2];
  char ksndh[27];
} ;

//	即時チェック情報構造体
struct my_stREALCHK
{
  char knskisymd[11];
  char sriymd[11];
  char kntno[14];
  char kntketflg[2];
  char knsgrp[17];
  char kmkcd[8];
  short knssu;
  short knssueda;
  char utkymd[11];
  char irino[12];
  char iriketflg[2];
  short zssdino;
  char trid[11];
  short trpos;
  char asyrckid[11];
  short asyrckpos;
  char bskkbn[5];
  char nbkmkcd[8];
  char renjicflg[2];
  char soukn1flg[2];
  char kanrenflg[2];
  char bunkkuflg[2];
  char kesseiflg[2];
  char rirekiflg[2];
  char syougoflg[2];
  char keisanflg[2];
  char per100flg[2];
  char tousekflg[2];
  char kisyakflg[2];
  char kouseiflg[2];
  char syoungflg[2];
  char soukn2flg[2];
  char fukaptflg[2];
  char yobiflg01[2];
  char tobiflg02[2];
  char yobiflg03[2];
  char yobiflg04[2];
  char yobiflg05[2];
  struct
  {
    short length;
    char  data[256];
  } renjicpara;
  struct
  {
    short length;
    char  data[256];
  } soukn1para;
  struct
  {
    short length;
    char  data[256];
  } kanrenpara;
  struct
  {
    short length;
    char  data[256];
  } bunkkupara;
  struct
  {
    short length;
    char  data[256];
  } kesseipara;
  struct
  {
    short length;
    char  data[256];
  } rirekipara;
  struct
  {
    short length;
    char  data[256];
  } syougopara;
  struct
  {
    short length;
    char  data[1024];
  } keisanpara;
  struct
  {
    short length;
    char  data[256];
  } per100para;
  struct
  {
    short length;
    char  data[256];
  } tousekpara;
  struct
  {
    short length;
    char  data[256];
  } kisyakpara;
  struct
  {
    short length;
    char  data[256];
  } kouseipara;
  struct
  {
    short length;
    char  data[256];
  } syoungpara;
  struct
  {
    short length;
    char  data[256];
  } soukn2para;
  struct
  {
    short length;
    char  data[256];
  } fukaptpara;
  struct
  {
    short length;
    char  data[256];
  } yobipara01;
  struct
  {
    short length;
    char  data[256];
  } yobipara02;
  struct
  {
    short length;
    char  data[256];
  } yobipara03;
  struct
  {
    short length;
    char  data[256];
  } yobipara04;
  struct
  {
    short length;
    char  data[256];
  } yobipara05;
  char ksndh[27];
} ;

//	ワークシートＳＥＱ管理情報構造体
struct my_stWSSEQKNRI
{
    int      wstbnknr;		// ＷＳ管理通番
    char     knskisymd[11];	// 検査開始日
    char     knsgrp[17];	// 検査グループ
    char     wssbt[11];		// ＷＳ種別
    int      wsno;			// ＷＳ番号
    int      knsseqst;		// 検査ＳＥＱ（開始）
    int      knsseqed;		// 検査ＳＥＱ（終了）
    int      knsseqsu;		// 検査ＳＥＱ数（検体数）
    char     ksktkbn;		// 検査工程区分
    char     dtnrtts[9];	// データ入力担当者
    char     ksndh[27];		// 情報更新日時
} ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;

int sFncSelChkOrderSumiTray ( char *, char *, int * ) ;
int sFncSelCntKENORDER ( char *, char *, int * ) ;
int sFncSelZsLineMstTray( char *, char *, int * ) ;
int sFncSelChkOrderSumiRack ( char *, char *, int * ) ;
int sFncUpdKENORDER ( char *, char *, int, int, char *, int ) ;
int sFncInsKENPOS ( char *, char *, int, int, char * ) ;
int sFncSelKENORDER_REALCHK ( char *, char *, int, int, struct my_stKENORDER **, struct my_stREALCHK **, int * ) ;
int sFncSelZsLineMstRack( char *, char *, int * ) ;
int sFncUpdKENORDER_NXT ( char *, char *, char *, int, int ) ;
int sFncInsKENPOS_NXT ( char *, char *, char * ) ;
int sFncSelKENORDER_REALCHK_NXT ( char *, char *, int, int, struct my_stKENORDER **, struct my_stREALCHK **, int * ) ;
int sFncSelKENORDER ( char *, char *, int * );
int insWsseqknri( char *, char *, char *, int, int, int ) ;

int sFncSelZsLineMst ( char *, char *, int * ) ;
int sFncSelWSSEQKNRI( int * ) ;
long sFncInsWSSEQKNRI( struct my_stWSSEQKNRI * ) ;
int sFncSelCntKesseiOrder ( char *, char *, int ,int * ) ;

#endif
/** End of File ***************************************************************/
