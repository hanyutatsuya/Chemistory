/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD102.h                                                      */
/*   概      要：検査受付（依頼展開）依頼情報登録                             */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/20     INTEC.INC      Create                             */
/******************************************************************************/
#ifndef _AD102_H
#define _AD102_H
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <errno.h>
#include <iconv.h>
#include <dirent.h>
#include "bml_base.h"
#include "tagAD102.h"
#include "tagPNC.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
//	ini FILE
#define		MYAPP_INIFILE		"$HOME/appl/src/irai/AD102/AD102.ini"	

//	APPLI
			// MAX LENGTH
#define		MYAPP_MAX_CHAR		256				// with iconv
#define		MYAPP_MAX_KJNO		700
#define		MYAPP_LEN_KEY		19
#define		MYAPP_LEN_KJN		14
#define		MYAPP_LEN_FNCNM		32
#define		MYAPP_LEN_ERR		32
#define		MYAPP_LEN_MSG		1024
			// 共有メモリサイズ
#define		MYAPP_SHM_SIZE		sizeof ( int )

#define		MYAPP_SPACE10		"          "
#define		MYAPP_KJSPACE10		"　　　　　　　　　　"
#define		MYAPP_APPLNAME		"依頼情報登録"

#define		MYAPP_RTN_DUP		-803
#define		MYAPP_RTN_LOCK		-911
#define		MYAPP_RTN_NTFND		 100

			// トレース種別
#define		LT_DBG			"D"	
#define		LT_TRC			"T"	
#define		LT_OPT			"O"	
#define		LT_WRN			"W"	
#define		LT_ERR			"E"	
#define		LT_SYS			"A"	
#define		LT_STA			"STA"	
#define		LT_END			"END"	
			// 実行フラグ
#define		LX_SEL			"S"	
#define		LX_INS			"I"	
#define		LX_UPD			"U"	
#define		LX_DEL			"D"	
#define		LX_NON			" "	
			// エラーコード
#define		LE_NON			" "	

//	日付チェックモード
#define		VALDATE_DATE		1			// DATE型
#define		VALDATE_TIME		2			// time型
#define		VALDATE_TIMESTAMP	3			// taimestamp型

// INPUT FILE REC SIZE
#define		NXT_RECSIZE			1024

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
struct {
    char	dbp_dbAlias[15];			//  DB
    char	dbp_user[129];   			//  user
    char	dbp_pswd[15];   			//  password
	char	ifp_indir[256];				// INPUT FILE DIRECTRY
	char	ifp_infprx[10];				// INPUT FILE PREFIX
	char	ifp_endfprx[10];			// END FILE DIRECTRY
	char	lgp_comlog[256];			// LOG FILE NAME
	char	lgp_flog[256];				// LOG FILE NAME for debug
	int		myp_sleep;					// SLEEP TIME
	char	myp_exefile[256];			// LoadModuleName
	char	myp_gene[4];				// システム世代(PNCorNXT)
	char	myp_kjnymd[10+1];			// 基準処理日
	int		myp_sedai;
	int		myp_debug;        		
} stcPRM;

// 件数情報構造体
struct CNT {
    int		cnt_irai;   				//  依頼ファイル 読み込み件数
    int		cnt_irai_err;   			//  依頼ファイル エラー件数
    int		cnt_hd;   					//  PNC HD レコード件数
    int		cnt_tr;   					//  PNC TR レコード件数
    int		cnt_r1;   					//  PNC R1 レコード件数
    int		cnt_rf;   					//  PNC R2 レコード件数
    int		cnt_oth;   					//  PNC 以外 レコード件数
    int		cnt_dbirai;   				//  患者属性データ  登録件数
    int		cnt_dbirai_del;   			//  依頼ファイル 削除件数
    int		cnt_dbirai_jdi;   			//  依頼ファイル 自動発生登録件数
    int		cnt_end;   					//  治験拡張データ　登録件数
};

// 共有メモリ管理構造体
struct  SHM {
	int		shm_Id ;
	key_t	shm_Key ;
};

// <<   基準値NO取得用構造体
struct  stcKJNO	{
    char    kjno[3+1];          		// O 基準値NO
    char    kmkcd[7+1];         		// I 項目コード
    char    zrcd[4+1];          		// I 材料コード
	char    age[3+1];           		// I 年齢
    char    agekbn[1+1];        		// I 年齢区分
};

// 自動発生依頼情報
struct  JIDOIRAI {
    struct  _JDKMKMST   sJdm;
    struct  _KMKMST     sKmk;
    struct  _IRAI       sIri;
	char	age[3+1];                   // I 年齢
    char	agekbn[1+1];                // I 年齢区分
};

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
// extern
extern		iconv_t		G_ic;					// with iconv
extern		char		G_fnm[256];				// InputFileName
extern		char		G_msg[MYAPP_LEN_MSG+1];	// LogMessage
extern		char		G_err[MYAPP_LEN_ERR+1];	// LogMessage(errcode)
extern		char		G_utkymd[10+1];			// LogMessage(csv)
extern		char		G_irino[13+1];			// LogMessage(csv)
extern		char		G_kntno[13+1];			// LogMessage(csv)
extern		int			G_zssdino;				// LogMessage(csv)
extern		char		G_kmkcd[7+1];			// LogMessage(csv)
extern		int			G_line;					// InputFileLineNo

extern		struct      _KJNMST     *pKjn;

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void		DispHelpMsg( int argc, char	**argv );
int			ParamCheckProc( int argc, char **argv, struct SHM  *stcShm );
int			GetKjnymd( );
static	int	FileFilter( struct dirent *namelist );

//<== 2006.12.08 Kim Jinsuk 引数追加
int			PncProc( FILE *pfp , int *stopValue); 
//<== 2006.12.08 Kim Jinsuk　引数追加

int			ReadPnc( char *rbuf, FILE *pfp	);
int			NxtProc( FILE *nfp );
int			ReadNxt( char *rbuf, FILE *nfp	);
int			EditCsvIrai( struct _IRAI *kan );
int			EditCsvMsg( char *msg );
int			LogOut( char *sbt, char *flg, char *ecd, char *msg, 
					char *fncnm, char *file, long line );
// EDIT
int			EditPncIrai( struct Z05SJIR1 *inp, struct _IRAI *iri );
int			EditNxtIrai( struct _IRAI *iri );
int			EditCommonIrai( struct _IRAI *iri );
int			irai_pr( struct _IRAI *in );
int			GetKjnmst( struct stcKJNO	*in );
// PG固有せず
char		*EnvRef( char *src_cp );
char		*GetIniFile( char *section, char *key, char *profile );
int			DaemonCheckProc( int argc, char **argv );
int			sj2euc( char *bufot, char *bufin, int len );
int			to_csv( char *delim, int len, char *msg, char *col );
int			wa2ymd( char *ymd10, char *gengou, char *ymd );
int			ValidDate( int mode, char *indate );
// 共有メモリ
int         sFncShmCrt ( struct SHM *strShm );
int         sFncShmGet ( struct SHM *strShm, int *pshmData );
int         sFncShmDel ( struct SHM *strShm);
// ＤＢ関連関数
int			SelSysknrmst( struct _SYSKNRMST *knr );
int			UpdSysknrmstIriend( char *nxtymd );
int			SelCountKjnmst( char *ymd );
int			SelKjnmst( char *ymd , int kensu );
int			InsIrai( struct _IRAI *iri );
int			UpdIraiSjflg( struct _IRAI *iri );
int			Ydbcommit();
int			Ydbrollback();
int			Ydbconn();
int			Ydbdisconn();

#endif
/** End of File ***************************************************************/
