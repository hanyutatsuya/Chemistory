/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：AD202.h                                                      */
/*   概      要：検査受付（緊急検査依頼展開）緊急検査情報展開                 */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/10     INTEC.INC      Create                             */
/*  2.00     2009/01/06     Merits K.Ameno 施設コード増桁 通信仕様変更対応    */
/******************************************************************************/
#ifndef _AD202_H
#define _AD202_H
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
#include "tagAD202.h"
#include "tagKINQ.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
//	ini FILE
#define		MYAPP_INIFILE		"$HOME/appl/src/irai/AD202/AD202.ini"	

//	APPLI
			// MAX LENGTH
#define		MYAPP_MAX_CHAR		256				// with iconv
#define		MYAPP_LEN_KEY		19
#define		MYAPP_LEN_KJN		14
#define		MYAPP_LEN_FNCNM		32
#define		MYAPP_LEN_ERR		32
#define		MYAPP_LEN_MSG		1024
			// 共有メモリサイズ
#define		MYAPP_SHM_SIZE		sizeof ( int )

#define		MYAPP_SPACE10		"          "
#define		MYAPP_KJSPACE10		"　　　　　　　　　　"
#define		MYAPP_APPLNAME		"緊急依頼展開"


#define		MYAPP_RTN_DUP		-803
#define		MYAPP_DEF_ZRCD		"023"			// 3.01 血清
#define		MYAPP_ZRCD_ASDEF	"0  "			/* 材料コードがない(AS側で頭に0を付けて送信してくる為)場合の値 */

#define		MYAPP_DEF_ERR01		"00000001"		// 3.01 緊急基準処理日と一致せず

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
	int		myp_sleep;					// SLEEP TIME
	char	myp_exefile[256];			// LoadModuleName
	char	myp_kjnymd[10+1];			// 基準処理日
	char	myp_zairyo[4];				// zairyo
	int		myp_sedai;
	int		myp_debug;        			/*CODEB  debug flg       */
} stcPRM;

// 件数情報構造体
struct CNT {
    int		cnt_irai;   				//  依頼ファイル 読み込み件数
    int		cnt_irai_err;   			//  依頼ファイル エラー件数
    int		cnt_skip;   				//  依頼ファイル SKIP件数
    int		cnt_exc;   					//  依頼ファイル SKIP件数 対象外
    int		cnt_sumi;   				//  依頼ファイル SKIP件数 処理済
    int		cnt_kanjya;   				//  患者属性データ  登録件数
    int		cnt_dbirai;   				//  依頼情報データ　登録件数
};

// 共有メモリ管理構造体
struct	SHM {
	int     shm_Id ;
	key_t   shm_Key ;
};

// <<   基準値NO取得用構造体
struct  stcKJNO {
	char	kjno[3+1];					// O 基準値NO
	char	kmkcd[7+1];				 	// I 項目コード
	char	zrcd[4+1];				  	// I 材料コード
	char	age[3+1];					// I 年齢
	char	agekbn[1+1];				// I 年齢区分
};

// 依頼項目情報構造体
struct KOMST {
    char	kmkcd[7+1];					// I 項目コード
    char	knsgrp[16+1];				// 1.04 O 検査グループ		
    char	kmkrs[16+1];				// O 項目略称
	char    oyakmkcd[7+1];      		// O 親項目コード
	char    fkbnkkb[1+1];       		// O 分画負荷区分
	char    seccd[2+1];       			// O セクションコード
	char    smpcd[7+1];         		// O サンプリングコード
	char    kjno[3+1];       			// O 基準値ＮＯ
};

// 1.04 ADD
// 自動発生依頼情報
struct  JIDOIRAI {
    struct  _JDKMKMST   sJdm;
    struct  _KMKMST     sKmk;
    struct  _IRAI       sIri;
    char    age[3+1];                   // I 年齢
    char    agekbn[1+1];                // I 年齢区分
};


// 診療科名	
struct  sinryo_rec {
    int     scode;
    char    sname[30+1];
};

static struct	sinryo_rec	kanm[]= {
{    0," ", },
{    1,"内科", },
{    2,"一内科", },
{    3,"二内科", },
{    4,"三内科", },
{    5,"呼吸器科", },
{    6,"消化器科", },
{    7,"循環器科", },
{    8,"小児科", },
{    9,"精神科", },
{    10,"神経科", },
{    11,"外科", },
{    12,"一外科", },
{    13,"二外科", },
{    14,"三外科", },
{    15,"整形科", },
{    16,"脳外科", },
{    17,"心臓外科", },
{    18,"皮膚科", },
{    19,"泌尿器科", },
{    20,"放射線科", },
{    21,"透析科", },
{    22,"産科", },
{    23,"婦人科", },
{    24,"耳鼻科", },
{    25,"咽頭科", },
{    26,"麻酔科", },
{    27,"歯科", },
{    28,"眼科", },
{    29,"ドック", },
{    30,"検診科", },
{    31,"検査科", },
{    32,"研究室", },
{    33,"その他", },
{    34,"形成外科", },
{    35,"隔離科", },
{    36,"小児外科", },
{    37,"心療内科", },
{    38,"脳神経内科", },
{    39,"胸部外科", },
{    40,"原医研内科", },
{    41,"原医研外科", },
{    42,"東洋医学科", },
{    43,"神経内科", },
{    44,"第４内科", },
{    45,"内分泌科", },
{    46,"老年内科", },
{    47,"口腔外科", },
{    48,"リウマチセンター", },
{    49,"産婦人科", },
{    50,"２Ａ", },
{    51,"２Ｂ", },
{    52,"３Ａ", },
{    53,"３Ｂ", },
{    54,"４Ａ", },
{    55,"４Ｂ", },
{    56,"５Ａ", },
{    57,"５Ｂ", },
{    58,"６Ａ", },
{    59,"６Ｂ", },
{    60,"循内", },
{    61,"呼吸器１", },
{    62,"呼吸器２", },
{    63,"胃腸科", },
{    64,"リハビリ科", },
{    65,"自動化健診", },
{    66,"主婦健診", },
{    67,"集検", },
{    68,"腎", },
{    69,"心臓内科", },
{    70,"救急科", },
{    71,"画診", },
{    72,"免疫科", },
{    73,"消化器内科", },
{    74,"血液内科", },
{    75,"老人科", },
{    76,"臨床病理科", },
{    77,"肛門科", },
{    78,"糖尿", },
{    79,"腹外", },
{    80,"成検", },
{    81,"病透", },
{    82,"腎臓外科", },
{    83,"頭ケイ科", },
{    84,"理学療法科", },
{    85,"総合科", },
{    86,"保健指導科", },
{    87,"こう原病内科", },
{    88,"不妊外来", },
{    89,"第二小児科", },
{    90,"呼吸器外科", },
{    91,"肝臓科", },
{    92,"消化器外科", },
{    93,"診療所", },
{    94,"神経耳鼻科", },
{    95,"腎移植科", },
{    96,"整形外科", },
{    97,"ＷＩＣ", },
{    98,"アレルギー科", },
{    99," ", },
{    -1,"" }
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
extern		char		G_irino[11+1];			// LogMessage(csv)
extern		int			G_zssdino;				// LogMessage(csv)
extern		char		G_kntno[13+1];			// LogMessage(csv)
extern		char		G_kmkcd[7+1];			// LogMessage(csv)
extern		int			G_line;					// InputFileLineNo

extern		struct		_KJNMST     *pKjn;

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void		DispHelpMsg( int argc, char	**argv );
int			ParamCheckProc( int argc, char **argv, struct SHM  *stcShm );
int			GetKjnymd( );
static	int	FileFilter( struct dirent *namelist );
//int			KinqProc( FILE *pfp );
int			KinqProc( FILE *pfp, int *stopValue );
int			ReadKinq( char *rbuf, FILE *pfp	);
int			EditCsvMsg( char *msg );
int			LogOut( char *sbt, char *flg, char *ecd, char *msg, 
					char *fncnm, char *file, long line );
int			EditKinqKanjya( struct AS4IRAI *iirai, struct _KANJYA *zok );
int         EditKinqIrai( struct AS4IRAI *inp, struct _KANJYA *kan, struct _IRAI *iri );
int			zoku_pr( struct _KANJYA *in );
int			irai_pr( struct _IRAI *in );
int			NameKeyMake( char *name_key, char *kan_name, int len );
int         GetKjnmst( struct stcKJNO   *in );
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
int         SelCountKjnmst( char *ymd );
int         SelKjnmst( char *ymd , int kensu );
int			InsKanjya( struct _KANJYA *kan );
int         InsIrai( struct _IRAI *iri );
int			Ydbcommit();
int			Ydbrollback();
int			Ydbconn();
int			Ydbdisconn();

#endif
/** End of File ***************************************************************/
