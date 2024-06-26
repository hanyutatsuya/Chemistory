/******************************************************************************/
/* @alklü¯¸VXe                                                 */
/*                                                                            */
/* @VXe¼F¢ãVXe                                               */
/* @t@C¼FLD103.h                                                      */
/* @T@@@vFp[^æ¾wb_                                         */
/******************************************************************************/
/*  Ver.     út           ¼O           C³àe                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _LD103_h
#define _LD103_h
/******************************************************************************/
/* CN[hé¾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "bmlprm.h"
#include "bmllog.h"

/******************************************************************************/
/* Defineè`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"LD103"
#define	MYAPP_APP_NAME_JP		"LD103"
#define	MYAPP_LOGINIFILE		"LD103_LOG.ini"

//  àXe[^XR[hè`
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

//	®«`FbNtOè`
#define MYAPP_ZOK_NOT_CHK		"0"	// ®«`FbNÎÛO
#define MYAPP_ZOK_CHK			"1"	// ®«`FbNÎÛ
#define MYAPP_ZOK_ERR			"2"	// ®«`FbNG[
#define MYAPP_ZOK_NG			"3"	// ®«`FbNG[(Ùíl)

//	ñÛ¯tOè`
#define MYAPP_HKKHR_ERR			1	// ®«îñG[Lè
#define MYAPP_HKKHR_NG			2	// ®«îñÙílLè
#define MYAPP_HKKHR_CALC		3	// ÄvZÒ¿(®«C³Ï)
#define MYAPP_HKKHR_OK			0	// Û¯ð
 
//	G[R[hè`
#define	MYAPP_LOG_ERRCODE_NON		"00000000"
#define	MYAPP_LOG_ERRCODE_APP		"010"
#define	MYAPP_LOG_ERRCODE_DB		"020"
#define	MYAPP_LOG_ERRCODE_ETC		"0Z0"

//	G[R[hÚ×
#define MYAPP_SQL_DEADLOCK		-911
#define MYAPP_SQL_DUPLICATION		-803

//	p[^¶ñ
#define MYAPP_PRM_SHM_KEY		"SHM_KEY"
#define MYAPP_PRM_SLEEP_MIN		"SLEEP_MIN"
#define MYAPP_PRM_DB_NAME		"DB_NAME"
#define MYAPP_PRM_DB_USER		"DB_USER"
#define MYAPP_PRM_DB_PASSWD		"DB_PASSWD"
#define MYAPP_PRM_DIR_INPUT		"INPUT_DIR"
#define MYAPP_PRM_DIR_OK		"END_DIR_OK"
#define MYAPP_PRM_DIR_NG		"END_DIR_NG"
#define MYAPP_PRM_FILE_PRX		"FILE_PRX"
#define MYAPP_PRM_FILE_GET_SHELL	"FILE_GET_SHELL"
#define MYAPP_PRM_LOCK_FILE		"LOCK_FILE"
#define MYAPP_PRM_AGE_HI		"AGE_HI"
#define MYAPP_PRM_AGE_LOW		"AGE_LOW"
#define MYAPP_PRM_SC_HI			"SC_HI"
#define MYAPP_PRM_SC_LOW		"SC_LOW"
#define MYAPP_PRM_TJ_HI			"TJ_HI"
#define MYAPP_PRM_TJ_LOW		"TJ_LOW"


//	fBNgi[TCY
#define	MYAPP_PATH_SIZE			(1024)

#define MYAPP_LEN_FNCNM			32
#define MYAPP_LEN_MSG			3072

#define RECORDSIZE			1024

//	¤LTCY
#define	MYAPP_SHM_SIZE			sizeof ( int )

#define	MYAPP_ZAIRYO			"002"
#define	MYAPP_KJSPACE10			"@@@@@@@@@@"
#define	MYAPP_SPACE10			"          "

//      út`FbN[h
#define	VALDATE_DATE			1			// DATE^
#define	VALDATE_TIME			2			// time^
#define	VALDATE_TIMESTAMP 		3			// taimestamp^

//	MAX LENGTH
#define	MYAPP_MAX_CHAR			256			// with iconv

//	MAX LENGTH
#define	RTN_NONE			100
/******************************************************************************/
/* \¢Ìè`                                                                 */
/******************************************************************************/
// vOÂ«\¢Ì
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ; 
	char	 cInputDir[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirOK[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirNG[MYAPP_PATH_SIZE] ;
	char	 cFilePrx[MYAPP_PATH_SIZE] ;
	char	 cFileGetSH[MYAPP_PATH_SIZE] ;
	char	 cLockFile[MYAPP_PATH_SIZE] ;
	int	 AgeHi;
	int	 AgeLow;
	double	 ScHi;
	double	 ScLow;
	double	 TjHi;
	double	 TjLow;
	int	 SleepMin ;
} pAppEnv ;

//	VXeÇ}X^îñ\¢Ì
typedef struct  _stSYSKNR {
        char    kjnsriymd[10+1];	// îNú
        char    iriendflg[1+1];		// ËENDtO
        char    bchendflg[1+1];		// ªENDtO
        char    unyflg[1+1];		// ^ptO
} my_stSYSKNR ;

//	îñ\¢Ì
typedef struct  _stFileKanjya {
	char	c_sbt[2];		/* Úº°ÄÞ¯Êæª        */
	char	c_bml_ymd[8];		/* BMLótNú        */
	char	c_irai_no[11];		/* ËNo             */
	char	c_siset_cd[7];		/* {Ýº°ÄÞ             */
	char	c_subsiset_cd[4];	/* »ÌÞ{Ýº°ÄÞ          */
	char	c_card1_kbn[2];		/* ¶°ÄÞæª1            */
	char	c_card2_kbn[2];		/* ¶°ÄÞæª2            */
	char	c_iraimoto_key[20];	/* Ë³·°             */
	char	c_ka_cd[3]; 		/* fÃÈº°ÄÞ           */
	char	c_ka_nm[15];		/* fÃÈ¼             */
	char	c_dr_cd[8]; 		/* Sãº°ÄÞ           */
	char	c_dr_nm[15];		/* Sã¼             */
	char	c_karte_no[15];		/* ¶ÙÃNo                */
	char	c_kanja_id[15];		/* ³ÒID               */
	char	c_kanja_nm[20];		/* ³Ò¼               */
	char	c_kanja_knm[20];	/* ³Ò¼i¿j       */
	char	c_tall[5];        	/* g·                 */
	char	c_weight[5];      	/* Ìd                 */
	char	c_weight_kbn[1];  	/* ÌdPÊ             */
	char	c_sex[1];         	/* «Êæª             */
	char	c_birth_ymd[8];   	/* ¶Nú             */
	char	c_birth_kbn[1];   	/* ¶Núæª         */
	char	c_age[3];         	/* Nî                 */
	char	c_age_kbn[1];     	/* Nîæª             */
	char	c_byoto_cd[5];    	/* aº°ÄÞ             */
	char	c_byoto_nm[15];   	/* a¼               */
	char	c_ukecmt1_cd[2];  	/* ótºÒÝÄº°ÄÞ1        */
	char	c_ukecmt2_cd[2];  	/* ótºÒÝÄº°ÄÞ2        */
	char	c_ukecmt3_cd[2];  	/* ótºÒÝÄº°ÄÞ3        */
	char	c_ukecmt1_cmt[20];	/* ótºÒÝÄÌØ°1         */
	char	c_ukecmt2_cmt[20];	/* ótºÒÝÄÌØ°2         */
	char	c_ng_kbn[1];     	/* üOæª             */
	char	c_ninsin_cnt[2]; 	/* DPT             */
	char	c_hoken_cd[1];   	/* Û¯º°ÄÞ             */
	char	c_zairyo01_cd[3];	/* Þ¿º°ÄÞ1            */
	char	c_zairyo02_cd[3];	/* Þ¿º°ÄÞ2            */
	char	c_zairyo03_cd[3];	/* Þ¿º°ÄÞ3            */
	char	c_zairyo04_cd[3];	/* Þ¿º°ÄÞ4            */
	char	c_zairyo05_cd[3];	/* Þ¿º°ÄÞ5            */
	char	c_zairyo06_cd[3];	/* Þ¿º°ÄÞ6            */
	char	c_zairyo07_cd[3];	/* Þ¿º°ÄÞ7            */
	char	c_zairyo08_cd[3];	/* Þ¿º°ÄÞ8            */
	char	c_zairyo09_cd[3];	/* Þ¿º°ÄÞ9            */
	char	c_zairyo10_cd[3];	/* Þ¿º°ÄÞ10           */
	char	c_yokisu01[2];		/* {ieíj1      */
	char	c_yokisu02[2];		/* {ieíj2      */
	char	c_yokisu03[2];		/* {ieíj3      */
	char	c_yokisu04[2];		/* {ieíj4      */
	char	c_yokisu05[2];		/* {ieíj5      */
	char	c_yokisu06[2];		/* {ieíj6      */
	char	c_yokisu07[2];		/* {ieíj7      */
	char	c_yokisu08[2];		/* {ieíj8      */
	char	c_yokisu09[2];		/* {ieíj9      */
	char	c_yokisu10[2];		/* {ieíj10     */
	char	c_saisyu_time[4];	/* ÌæÔ             */
	char	c_saisyu_ymd[8];	/* ÌæNú           */
	char	c_nyotime[4];		/* ~AÔ             */
	char	c_nyotime_kbn[1];	/* ~AÔiPÊj     */
	char	c_nyoryo[5];		/* ~AÊ               */
	char	c_nyoryo_kbn[1]; 	/* ~AÊiPÊj       */
	char	c_tochak_ymd[8]; 	/* Ì\èú       */
	char	c_imoto_lab[3];		/* Ë³ID             */
	char	c_hsaki_lab1[3]; 	/* ñæIDP           */
	char	c_hsaki_lab2[3]; 	/* ñæIDQ           */
	char	c_hsaki_lab3[3]; 	/* ñæIDR           */
	char	c_gmoto_lab1[3]; 	/* O³ID1            */
	char	c_gmoto_lab2[3]; 	/* O³ID2            */
	char	c_gmoto_lab3[3]; 	/* O³ID3            */
	char	c_gmoto_lab4[3]; 	/* O³ID4            */
	char	c_gmoto_lab5[3]; 	/* O³ID5            */
	char	c_gsaki_lab[3];	 	/* OæID             */
	char	c_verify_kbn[1]; 	/* ÍÞØÌ§²óµæª       */
	char	c_zokdel_flg[1]; 	/* ®«íÌ×¸Þ         */
	char	c_zokupd_flg[1]; 	/* ®«C³Ì×¸Þ         */
	char	c_kinkyu_flg[1]; 	/* Ù}ËÌ×¸Þ         */
	char	c_add_flg[1];		/* ÇÁL³Ì×¸Þ         */
	char	c_hikensa_kbn[1];	/* ñ¸æª           */
	char	c_uketuke_kbn[1];	/* ótæª             */
	char	c_ne_kbn[1];		/* NEæª               */
	char	c_hifd_flg[1];		/* FDññÌ×¸Þ         */
	char	c_kakucho_flg[1];	/* g£®«DB¯ÊÌ×¸Þ   */
	char	c_uke_time[4];		/* ót             */
	char	c_ope_ymd[8];		/* Nú           */
	char	c_obmluke_ymd[8];	/* ³BMLótNú      */
	char	c_oirai_no[11];		/* ³ËNO           */
	char	c_eigyo_cd[3];		/* cÆº°ÄÞ           */
	char	c_syuhai_cd[2]; 	/* Wzº°ÄÞ             */
	char	c_siset_knm[40];	/* {Ý¼³®¼Ìi¿j*/
	char	c_siset_nm[20];		/* {Ý¼³®¼Ìi¶Åj */
	char	c_sisetr_knm[20];	/* {Ý¼ªÌi¿j   */
	char	c_sisetr_nm[10];	/* {Ý¼ªÌi¶Åj     */
	char	c_siset_kbn[2];		/* {ÝíÊ             */
	char	c_tokutei_flg[1];	/* Áè{ÝÌ×¸Þ         */
	char	c_riyu_cd[1];		/* Rº°ÄÞ             */
	char	c_kmax[3]; 		/* ËÚ           */
	char	c_kjlab1_cd[3];		/* ¸À{×ÎÞº°ÄÞP    */
	char	c_kjlab2_cd[3]; 	/* ¸À{×ÎÞº°ÄÞQ    */
	char	c_kjlab3_cd[3];		/* ¸À{×ÎÞº°ÄÞR    */
	char	c_hokoku_no[2]; 	/* úñNO           */
	char	c_yoyaku[12];		/* \ñÌ¨°ÙÄÞ           */
	char	c_filler[478];		/* FILLER               */
	char	c_kaigyo[1];		/* üsº°ÄÞ             */
} my_stFileKanjya ;

typedef struct  _stDbKanjya {
	char	utkymd[10+1];		// 1 alkótNú 
	char	irino[11+1];		// 2 Ëm 
	char	iriketflg[1+1];		// 3 ËmtO 
	short	zssdino;		// 4 ®«¢ãm 
	char	sstcd[7+1];		// 5 {ÝR[h 
	char	subsstcd[4+1];		// 6 Tu{ÝR[h 
	char	cdkbn1[2+1];		// 7 J[hæª1 
	char	cdkbn2[2+1];		// 8 J[hæª2 
	char	irimkey[40+1];		// 9 Ë³L[ 
	char	srkcd[3+1];		// 10 fÃÈR[h 
	char	srknm[30+1];		// 11 fÃÈ¼ 
	char	tticd[8+1];		// 12 SãR[h 
	char	ttinm[40+1];		// 13 Sã¼ 
	char	gpcd[8+1];		// 14 å¡ãR[h 
	char	gpnm[40+1];		// 15 å¡ã¼ 
	char	skicd[8+1];		// 16 ÐîãR[h 
	char	skinm[40+1];		// 17 Ðîã¼ 
	char	krtno[40+1];		// 18 Jem          
	char	knjid[15+1];		// 19 ³Òhc 
	char	knjnmn[60+1];		// 20 ³Ò¼iJij 
	char	knjnmk[30+1];		// 21 ³Ò¼i¿j 
	char	knjnmkey[60+1];		// 22 ³Ò¼L[ 
	char	sc[5+1];		// 23 g·  
	char	tj[5+1];		// 24 Ìd  
	char	tjtni[1+1];		// 25 Ìdæª 
	char	sbtkbn[1+1];		// 26 «Êæª 
	char	birthday[8+1];		// 27 ¶Nú  
	char	birthdaykbn[1+1];	// 28 ¶Núæª 
	char	age[3+1];		// 29 Nî  
	char	agekbn[1+1];		// 30 Nîæª 
	char	btcd[10+1];		// 31 aR[h 
	char	btnm[30+1];		// 32 a¼ 
	char	utkcmtcd1[2+1];		// 33 ótRg1  
	char	utkcmtcd2[2+1];		// 34 ótRg2  
	char	utkcmtcd3[2+1];		// 35 ótRg3  
	char	utkcmtfr1[70+1];	// 36 ótRgt[1  
	char	utkcmtfr2[70+1];	// 37 ótRgt[2  
	char	utkcmtfrflg[1+1];	// 38 ótRgt[tO 
	char	ngkbn[1+1];		// 39 ü@Oæª           
	char	nsssu[2+1];		// 40 DPT  
	char	hkncd[1+1];		// 41 Û¯R[h 
	char	ktshsu[2+1];		// 42 Ì{ 
	char	iniriymd[10+1];		// 43 @àËú 
	char	zssflg[1+1];		// 44 ®«C³tO 
	char	kkiriflg[1+1];		// 45 Ù}ËtO 
	char	hknskbn[1+1];		// 46 ñ¸æª 
	char	utkkbn[1+1];		// 47 ótæª 
	char	nekbn[1+1];		// 48 mdæª 
	char	inknskbn[1+1];		// 49 @à¸æª 
	char	utkjkkbn[1+1];		// 50 ótóÔæª 
	char	krflg[1+1];		// 51 ®¹tO 
	char	fdhhkkflg[1+1];		// 52 ecññtO 
	char	utkdh[8+1];		// 53 ót 
	char	mutkymd[10+1];		// 54 ³alkótú 
	char	mirino[11+1];		// 55 ³Ëm 
	char	knsjslbcd1[3+1];	// 56 ¸À{{R[hP 
	char	knsjslbcd2[3+1];	// 57 ¸À{{R[hQ 
	char	knsjslbcd3[3+1];	// 58 ¸À{{R[hR 
	char	knsjslbcd4[3+1];	// 59 ¸À{{R[hS 
	char	ymhkkflg[1+1];		// 60 ú¢ñtO 
	char	hkkkbdh[8+1];		// 61 ñó]Ô 
	char	ecd[3+1];		// 62 cÆR[h 
	char	shcd[2+1];		// 63 WzR[h 
	char	sstssnmj[40+1];		// 64 {Ý¼³®¼Ì 
	char	sstssnmn[40+1];		// 65 {Ý¼³®¼ÌiJij 
	char	sstrsj[20+1];		// 66 {Ý¼ªÌ 
	char	sstrsn[20+1];		// 67 {Ý¼ªÌiJij 
	char	sstsbt[2+1];		// 68 {ÝíÊ 
	char	ttsstflg[1+1];		// 69 Áè{ÝtO 
	char	rucd[2+1];		// 70 RR[h 
	short	irikmksu;		// 71 ËÚ 
	char	bmskn[50+1];		// 72 a¼yÑ© 
	char	irinrsbt[2+1];		// 73 ËüÍíÊ 
	char	irihsmkbn[1+1];		// 74 Ë­¶³æª 
	char	caresstflg[1+1];	// 75 ÁÊÓ{ÝtO 
	char	tktyflg[1+1];		// 76 ¡±g£tO 
	char	apkntino[13+1];		// 77 AUTO-PÌm 
	char	sdnm[20+1];		// 78 ff¼ 
	char	bko1[20+1];		// 79 õlP 
	char	bko2[20+1];		// 80 õlQ 
	char	bko3[20+1];		// 81 õlR 
	char	zstrdh[26+1];		// 82 ®«o^ú 
	char	zsssdh[26+1];		// 83 ®«C³ú 
	char	stlzsssdh[26+1];	// 84 TeCgà®«C³ú 
	char	stlzsssip[15+1];	// 85 TeCgà®«C³[IP 
	char	stlzssssyaid[8+1];	// 86 TeCgà®«C³üÍÒ 
	char	ksndh[26+1];		// 87 îñXVú 
	char	oyasstcd[7+1];		// 88 e{ÝR[h 
	char	trkdh[26+1];		// 89 o^ú 
} my_stDbKanjya ;

typedef struct _stCHKZOK
{
	char	utkymd[10+1];		// 1  alkótNú
	char	irino[11+1];		// 2  Ëm
	char	knsgrp[16+1];		// 3  ¸O[v
	char	kmkcd[7+1];		// 4  ÚR[h
	char	sc[5+1];		// 10 g·
	char	scflg[1+1];		// 11 g· `FbNtO
	char	tj[5+1];		// 12 Ìd
	char	tjflg[1+1];		// 13 Ìd  `FbNtO
	char	tjtni[1+1];		// 14 Ìdæª
	char	tjtniflg[1+1];		// 15 Ìdæª`FbNtO
	char	sbtkbn[1+1];		// 16 «Êæª
	char	sbtkbnflg[1+1];		// 17 «Êæª`FbNtO
	char	age[3+1];		// 18 Nî
	char	ageflg[1+1];		// 19 Nî`FbNtO
	char	agekbn[1+1];		// 20 Nîæª
	char	agekbnflg[1+1];		// 21 Nîæª`FbNtO
} my_stCHKZOK ;

/******************************************************************************/
/* O[oé¾                                                             */
/******************************************************************************/

/******************************************************************************/
/* vg^Cvé¾                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
int	EditPncKanjya( my_stFileKanjya *, my_stDbKanjya * ) ;
int     EditCommonKanjya( my_stDbKanjya * ) ;
int	NameKeyMake( char *, char *, int len ) ;
int	isCorrectChar( char * ) ;
int	ValidDate( int, char * ) ;
int	wa2ymd( char *, char  * , char * );                                          
void	sFncTrim( char *, char * );
#endif
/** End of File ***************************************************************/
