/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD103.h                                                      */
/*   概      要：検査受付（依頼展開）患者情報・治験拡張登録                   */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/10     INTEC.INC      Create                             */
/*  1.01     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応*/
/*                                         SelKanjya関数追加/DelKanjya関数追加*/
/*                                         InsShusei_Kanjya関数追加           */
/******************************************************************************/
#ifndef _AD103_H
#define _AD103_H
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
#include "tagAD103.h"
#include "tagPNC.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
//	ini FILE
#define		MYAPP_INIFILE		"$HOME/appl/src/irai/AD103/AD103.ini"	

//	APPLI
			// MAX LENGTH
#define		MYAPP_MAX_CHAR		256				// with iconv
#define		MYAPP_MAX_EIGMST	100
#define		MYAPP_LEN_KEY		19
#define		MYAPP_LEN_FNCNM		32
#define		MYAPP_LEN_ERR		32
#define		MYAPP_LEN_MSG		1024
			// 共有メモリサイズ
#define		MYAPP_SHM_SIZE		sizeof ( int )

#define		MYAPP_SPACE10		"          "
#define		MYAPP_KJSPACE10		"　　　　　　　　　　"
#define		MYAPP_APPLNAME		"患者情報登録"

#define		MYAPP_RTN_DUP		-803
#define		MYAPP_IRIKBN_AS400	"K"				// AS400からの依頼

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

// INPUT REC SIZE
#define		NXT_RECSIZE     	1024

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// ＤＢ接続情報
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
	char	myp_zairyo[4];				// zairyo
	int		myp_sedai;
	int		myp_debug;        			/*CODEB  debug flg       */
} stcPRM;

// 件数情報構造体
struct CNT {
    int		cnt_irai;   				//  依頼ファイル 読み込み件数
    int		cnt_irai_err;   			//  依頼ファイル エラー件数
    int		cnt_irai_del;   			//  依頼ファイル 削除件数
    int		cnt_kanjya;   				//  患者属性データ  登録件数
    int		cnt_chiken;   				//  治験拡張データ　登録件数
    int		cnt_hd;   					//  PNC HD レコード件数
    int		cnt_tr;   					//  PNC TR レコード件数
    int		cnt_r1;   					//  PNC R1 レコード件数
    int		cnt_r2;   					//  PNC R2 レコード件数
};

// 共有メモリ管理構造体
struct	SHM {
	int     shm_Id ;
	key_t   shm_Key ;
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
extern		int			G_zssdino;				// LogMessage(csv)
extern		int			G_line;					// InputFileLineNo


/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void		DispHelpMsg( int argc, char	**argv );
int			ParamCheckProc( int argc, char **argv, struct SHM  *stcShm );
int			GetKjnymd( );
static	int	FileFilter( struct dirent *namelist );

//2006.12.08 Kim Jinsuk DBエラー時
//int			PncProc( FILE *pfp );
int			PncProc( FILE *pfp ,int *stopValue);
//2006.12.08 Kim Jinsuk DBエラー時

int			ReadPnc( char *rbuf, FILE *pfp	);
int			NxtProc( FILE *nfp );
int			ReadNxt( char *rbuf, FILE *nfp	);
int			EditCsvKanjya( struct _KANJYA *kan );
int			EditCsvMsg( char *msg );
int			LogOut( char *sbt, char *flg, char *ecd, char *msg, 
					char *fncnm, char *file, long line );
int			EditPncKanjya( struct Z02SJIR1 *iirai, struct _KANJYA *zok );
int			EditNxtKanjya( struct _KANJYA *zok );
int			EditCommonKanjya( struct _KANJYA *zok );
int			zoku_pr( struct _KANJYA *in );
int			NameKeyMake( char *name_key, char *kan_name, int len );
int			EditPncChikenzok( struct Z04SJIR2 *iirai, struct _CHIKENZOK *zok );
int			EditNxtChikenzok( struct _CHIKENZOK *zok );
int			EditCommonChikenzok( struct _CHIKENZOK *zok );
int			chiken_pr( struct _CHIKENZOK *in );
int			GetEigmst( char *eigyo_cd, char *syuhai_cd, char *ymd, char *kbn );
// PG固有せず
char		*EnvRef( char *src_cp );
char		*GetIniFile( char *section, char *key, char *profile );
int			DaemonCheckProc( int argc, char **argv );
int			sj2euc( char *bufot, char *bufin, int len );
int			to_csv( char *delim, int len, char *msg, char *col );
int			wa2ymd( char *ymd10, char *gengou, char *ymd );
int			ValidDate( int mode, char *indate );
// 共有メモリ
int			sFncShmCrt ( struct SHM *strShm );
int			sFncShmGet ( struct SHM *strShm, int *pshmData );
int			sFncShmDel ( struct SHM *strShm);
// ＤＢ関連関数
int			SelSysknrmst( struct _SYSKNRMST *knr );
int			SelEigmst( struct _EIGMST *egm );
int			InsKanjya( struct _KANJYA *kan );
int			SelKanjyaZssdinoMax( struct _KANJYA *kan );
int			UpdKanjyaTktyflg( struct _KANJYA *kan );
int			UpdKinkyuKanjya( struct _KANJYA *kan );
int			SelKinkyuIrai( struct _KANJYA *kan );
int			InsChikenzok( struct _CHIKENZOK *try );
/*  1.01     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 --> */
int			SelKanjya( struct _KANJYA *kan );
int			DelKanjya( struct _KANJYA *kan );
int			InsShusei_Kanjya();
/*  1.01     2009/06/29     Merits K.Ameno 障害管理No:0904031814/0904031719対応 <-- */
int			Ydbcommit();
int			Ydbrollback();
int			Ydbconn();
int			Ydbdisconn();

#endif
/** End of File ***************************************************************/
