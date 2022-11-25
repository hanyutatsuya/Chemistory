/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：LD103.h                                                      */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _LD103_h
#define _LD103_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "bmlprm.h"
#include "bmllog.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"LD103"
#define	MYAPP_APP_NAME_JP		"LD103"
#define	MYAPP_LOGINIFILE		"LD103_LOG.ini"

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

//	属性チェックフラグ定義
#define MYAPP_ZOK_NOT_CHK		"0"	// 属性チェック対象外
#define MYAPP_ZOK_CHK			"1"	// 属性チェック対象
#define MYAPP_ZOK_ERR			"2"	// 属性チェックエラー
#define MYAPP_ZOK_NG			"3"	// 属性チェックエラー(異常値)

//	報告保留フラグ定義
#define MYAPP_HKKHR_ERR			1	// 属性情報エラー有り
#define MYAPP_HKKHR_NG			2	// 属性情報異常値有り
#define MYAPP_HKKHR_CALC		3	// 再計算待ち(属性修正済)
#define MYAPP_HKKHR_OK			0	// 保留解除
 
//	エラーコード定義
#define	MYAPP_LOG_ERRCODE_NON		"00000000"
#define	MYAPP_LOG_ERRCODE_APP		"010"
#define	MYAPP_LOG_ERRCODE_DB		"020"
#define	MYAPP_LOG_ERRCODE_ETC		"0Z0"

//	エラーコード詳細
#define MYAPP_SQL_DEADLOCK		-911
#define MYAPP_SQL_DUPLICATION		-803

//	パラメータ文字列
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


//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

#define MYAPP_LEN_FNCNM			32
#define MYAPP_LEN_MSG			3072

#define RECORDSIZE			1024

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )

#define	MYAPP_ZAIRYO			"002"
#define	MYAPP_KJSPACE10			"　　　　　　　　　　"
#define	MYAPP_SPACE10			"          "

//      日付チェックモード
#define	VALDATE_DATE			1			// DATE型
#define	VALDATE_TIME			2			// time型
#define	VALDATE_TIMESTAMP 		3			// taimestamp型

//	MAX LENGTH
#define	MYAPP_MAX_CHAR			256			// with iconv

//	MAX LENGTH
#define	RTN_NONE			100
/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
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

//	システム管理マスタ情報構造体
typedef struct  _stSYSKNR {
        char    kjnsriymd[10+1];	// 基準処理年月日
        char    iriendflg[1+1];		// 依頼ENDフラグ
        char    bchendflg[1+1];		// 分注ENDフラグ
        char    unyflg[1+1];		// 運用フラグ
} my_stSYSKNR ;

//	情報構造体
typedef struct  _stFileKanjya {
	char	c_sbt[2];		/* ﾚｺｰﾄﾞ識別区分        */
	char	c_bml_ymd[8];		/* BML受付年月日        */
	char	c_irai_no[11];		/* 依頼書No             */
	char	c_siset_cd[7];		/* 施設ｺｰﾄﾞ             */
	char	c_subsiset_cd[4];	/* ｻﾌﾞ施設ｺｰﾄﾞ          */
	char	c_card1_kbn[2];		/* ｶｰﾄﾞ区分1            */
	char	c_card2_kbn[2];		/* ｶｰﾄﾞ区分2            */
	char	c_iraimoto_key[20];	/* 依頼元ｷｰ             */
	char	c_ka_cd[3]; 		/* 診療科ｺｰﾄﾞ           */
	char	c_ka_nm[15];		/* 診療科名             */
	char	c_dr_cd[8]; 		/* 担当医ｺｰﾄﾞ           */
	char	c_dr_nm[15];		/* 担当医名             */
	char	c_karte_no[15];		/* ｶﾙﾃNo                */
	char	c_kanja_id[15];		/* 患者ID               */
	char	c_kanja_nm[20];		/* 患者名               */
	char	c_kanja_knm[20];	/* 患者名（漢字）       */
	char	c_tall[5];        	/* 身長                 */
	char	c_weight[5];      	/* 体重                 */
	char	c_weight_kbn[1];  	/* 体重単位             */
	char	c_sex[1];         	/* 性別区分             */
	char	c_birth_ymd[8];   	/* 生年月日             */
	char	c_birth_kbn[1];   	/* 生年月日区分         */
	char	c_age[3];         	/* 年齢                 */
	char	c_age_kbn[1];     	/* 年齢区分             */
	char	c_byoto_cd[5];    	/* 病棟ｺｰﾄﾞ             */
	char	c_byoto_nm[15];   	/* 病棟名               */
	char	c_ukecmt1_cd[2];  	/* 受付ｺﾒﾝﾄｺｰﾄﾞ1        */
	char	c_ukecmt2_cd[2];  	/* 受付ｺﾒﾝﾄｺｰﾄﾞ2        */
	char	c_ukecmt3_cd[2];  	/* 受付ｺﾒﾝﾄｺｰﾄﾞ3        */
	char	c_ukecmt1_cmt[20];	/* 受付ｺﾒﾝﾄﾌﾘｰ1         */
	char	c_ukecmt2_cmt[20];	/* 受付ｺﾒﾝﾄﾌﾘｰ2         */
	char	c_ng_kbn[1];     	/* 入外区分             */
	char	c_ninsin_cnt[2]; 	/* 妊娠週数             */
	char	c_hoken_cd[1];   	/* 保険ｺｰﾄﾞ             */
	char	c_zairyo01_cd[3];	/* 材料ｺｰﾄﾞ1            */
	char	c_zairyo02_cd[3];	/* 材料ｺｰﾄﾞ2            */
	char	c_zairyo03_cd[3];	/* 材料ｺｰﾄﾞ3            */
	char	c_zairyo04_cd[3];	/* 材料ｺｰﾄﾞ4            */
	char	c_zairyo05_cd[3];	/* 材料ｺｰﾄﾞ5            */
	char	c_zairyo06_cd[3];	/* 材料ｺｰﾄﾞ6            */
	char	c_zairyo07_cd[3];	/* 材料ｺｰﾄﾞ7            */
	char	c_zairyo08_cd[3];	/* 材料ｺｰﾄﾞ8            */
	char	c_zairyo09_cd[3];	/* 材料ｺｰﾄﾞ9            */
	char	c_zairyo10_cd[3];	/* 材料ｺｰﾄﾞ10           */
	char	c_yokisu01[2];		/* 本数（容器数）1      */
	char	c_yokisu02[2];		/* 本数（容器数）2      */
	char	c_yokisu03[2];		/* 本数（容器数）3      */
	char	c_yokisu04[2];		/* 本数（容器数）4      */
	char	c_yokisu05[2];		/* 本数（容器数）5      */
	char	c_yokisu06[2];		/* 本数（容器数）6      */
	char	c_yokisu07[2];		/* 本数（容器数）7      */
	char	c_yokisu08[2];		/* 本数（容器数）8      */
	char	c_yokisu09[2];		/* 本数（容器数）9      */
	char	c_yokisu10[2];		/* 本数（容器数）10     */
	char	c_saisyu_time[4];	/* 採取時間             */
	char	c_saisyu_ymd[8];	/* 採取年月日           */
	char	c_nyotime[4];		/* 蓄尿時間             */
	char	c_nyotime_kbn[1];	/* 蓄尿時間（単位）     */
	char	c_nyoryo[5];		/* 蓄尿量               */
	char	c_nyoryo_kbn[1]; 	/* 蓄尿量（単位）       */
	char	c_tochak_ymd[8]; 	/* 検体到着予定日       */
	char	c_imoto_lab[3];		/* 依頼元ID             */
	char	c_hsaki_lab1[3]; 	/* 報告先ID１           */
	char	c_hsaki_lab2[3]; 	/* 報告先ID２           */
	char	c_hsaki_lab3[3]; 	/* 報告先ID３           */
	char	c_gmoto_lab1[3]; 	/* 外注元ID1            */
	char	c_gmoto_lab2[3]; 	/* 外注元ID2            */
	char	c_gmoto_lab3[3]; 	/* 外注元ID3            */
	char	c_gmoto_lab4[3]; 	/* 外注元ID4            */
	char	c_gmoto_lab5[3]; 	/* 外注元ID5            */
	char	c_gsaki_lab[3];	 	/* 外注先ID             */
	char	c_verify_kbn[1]; 	/* ﾍﾞﾘﾌｧｲ状況区分       */
	char	c_zokdel_flg[1]; 	/* 属性削除ﾌﾗｸﾞ         */
	char	c_zokupd_flg[1]; 	/* 属性修正ﾌﾗｸﾞ         */
	char	c_kinkyu_flg[1]; 	/* 緊急依頼ﾌﾗｸﾞ         */
	char	c_add_flg[1];		/* 追加有無ﾌﾗｸﾞ         */
	char	c_hikensa_kbn[1];	/* 非検査区分           */
	char	c_uketuke_kbn[1];	/* 受付区分             */
	char	c_ne_kbn[1];		/* NE区分               */
	char	c_hifd_flg[1];		/* FD非報告ﾌﾗｸﾞ         */
	char	c_kakucho_flg[1];	/* 拡張属性DB識別ﾌﾗｸﾞ   */
	char	c_uke_time[4];		/* 受付時刻             */
	char	c_ope_ymd[8];		/* 処理年月日           */
	char	c_obmluke_ymd[8];	/* 元BML受付年月日      */
	char	c_oirai_no[11];		/* 元依頼書NO           */
	char	c_eigyo_cd[3];		/* 営業所ｺｰﾄﾞ           */
	char	c_syuhai_cd[2]; 	/* 集配ｺｰﾄﾞ             */
	char	c_siset_knm[40];	/* 施設名正式名称（漢字）*/
	char	c_siset_nm[20];		/* 施設名正式名称（ｶﾅ） */
	char	c_sisetr_knm[20];	/* 施設名略称（漢字）   */
	char	c_sisetr_nm[10];	/* 施設名略称（ｶﾅ）     */
	char	c_siset_kbn[2];		/* 施設種別             */
	char	c_tokutei_flg[1];	/* 特定施設ﾌﾗｸﾞ         */
	char	c_riyu_cd[1];		/* 理由ｺｰﾄﾞ             */
	char	c_kmax[3]; 		/* 依頼項目数           */
	char	c_kjlab1_cd[3];		/* 検査実施ﾗﾎﾞｺｰﾄﾞ１    */
	char	c_kjlab2_cd[3]; 	/* 検査実施ﾗﾎﾞｺｰﾄﾞ２    */
	char	c_kjlab3_cd[3];		/* 検査実施ﾗﾎﾞｺｰﾄﾞ３    */
	char	c_hokoku_no[2]; 	/* 当日報告NO           */
	char	c_yoyaku[12];		/* 予約ﾌｨｰﾙﾄﾞ           */
	char	c_filler[478];		/* FILLER               */
	char	c_kaigyo[1];		/* 改行ｺｰﾄﾞ             */
} my_stFileKanjya ;

typedef struct  _stDbKanjya {
	char	utkymd[10+1];		// 1 ＢＭＬ受付年月日 
	char	irino[11+1];		// 2 依頼書Ｎｏ 
	char	iriketflg[1+1];		// 3 依頼書Ｎｏ桁数フラグ 
	short	zssdino;		// 4 属性世代Ｎｏ 
	char	sstcd[7+1];		// 5 施設コード 
	char	subsstcd[4+1];		// 6 サブ施設コード 
	char	cdkbn1[2+1];		// 7 カード区分1 
	char	cdkbn2[2+1];		// 8 カード区分2 
	char	irimkey[40+1];		// 9 依頼元キー 
	char	srkcd[3+1];		// 10 診療科コード 
	char	srknm[30+1];		// 11 診療科名 
	char	tticd[8+1];		// 12 担当医コード 
	char	ttinm[40+1];		// 13 担当医名 
	char	gpcd[8+1];		// 14 主治医コード 
	char	gpnm[40+1];		// 15 主治医名 
	char	skicd[8+1];		// 16 紹介医コード 
	char	skinm[40+1];		// 17 紹介医名 
	char	krtno[40+1];		// 18 カルテＮｏ          
	char	knjid[15+1];		// 19 患者ＩＤ 
	char	knjnmn[60+1];		// 20 患者名（カナ） 
	char	knjnmk[30+1];		// 21 患者名（漢字） 
	char	knjnmkey[60+1];		// 22 患者名キー 
	char	sc[5+1];		// 23 身長  
	char	tj[5+1];		// 24 体重  
	char	tjtni[1+1];		// 25 体重区分 
	char	sbtkbn[1+1];		// 26 性別区分 
	char	birthday[8+1];		// 27 生年月日  
	char	birthdaykbn[1+1];	// 28 生年月日区分 
	char	age[3+1];		// 29 年齢  
	char	agekbn[1+1];		// 30 年齢区分 
	char	btcd[10+1];		// 31 病棟コード 
	char	btnm[30+1];		// 32 病棟名 
	char	utkcmtcd1[2+1];		// 33 受付コメント1  
	char	utkcmtcd2[2+1];		// 34 受付コメント2  
	char	utkcmtcd3[2+1];		// 35 受付コメント3  
	char	utkcmtfr1[70+1];	// 36 受付コメントフリー1  
	char	utkcmtfr2[70+1];	// 37 受付コメントフリー2  
	char	utkcmtfrflg[1+1];	// 38 受付コメントフリーフラグ 
	char	ngkbn[1+1];		// 39 入院外来区分           
	char	nsssu[2+1];		// 40 妊娠週数  
	char	hkncd[1+1];		// 41 保険コード 
	char	ktshsu[2+1];		// 42 検体総本数 
	char	iniriymd[10+1];		// 43 院内依頼日 
	char	zssflg[1+1];		// 44 属性修正フラグ 
	char	kkiriflg[1+1];		// 45 緊急依頼フラグ 
	char	hknskbn[1+1];		// 46 非検査区分 
	char	utkkbn[1+1];		// 47 受付区分 
	char	nekbn[1+1];		// 48 ＮＥ区分 
	char	inknskbn[1+1];		// 49 院内検査区分 
	char	utkjkkbn[1+1];		// 50 受付状態区分 
	char	krflg[1+1];		// 51 完了フラグ 
	char	fdhhkkflg[1+1];		// 52 ＦＤ非報告フラグ 
	char	utkdh[8+1];		// 53 受付時刻 
	char	mutkymd[10+1];		// 54 元ＢＭＬ受付日 
	char	mirino[11+1];		// 55 元依頼書Ｎｏ 
	char	knsjslbcd1[3+1];	// 56 検査実施ラボコード１ 
	char	knsjslbcd2[3+1];	// 57 検査実施ラボコード２ 
	char	knsjslbcd3[3+1];	// 58 検査実施ラボコード３ 
	char	knsjslbcd4[3+1];	// 59 検査実施ラボコード４ 
	char	ymhkkflg[1+1];		// 60 翌日未報告フラグ 
	char	hkkkbdh[8+1];		// 61 報告希望時間 
	char	ecd[3+1];		// 62 営業所コード 
	char	shcd[2+1];		// 63 集配コード 
	char	sstssnmj[40+1];		// 64 施設名正式名称 
	char	sstssnmn[40+1];		// 65 施設名正式名称（カナ） 
	char	sstrsj[20+1];		// 66 施設名略称 
	char	sstrsn[20+1];		// 67 施設名略称（カナ） 
	char	sstsbt[2+1];		// 68 施設種別 
	char	ttsstflg[1+1];		// 69 特定施設フラグ 
	char	rucd[2+1];		// 70 理由コード 
	short	irikmksu;		// 71 依頼項目数 
	char	bmskn[50+1];		// 72 病名及び所見 
	char	irinrsbt[2+1];		// 73 依頼入力種別 
	char	irihsmkbn[1+1];		// 74 依頼発生元区分 
	char	caresstflg[1+1];	// 75 特別注意施設フラグ 
	char	tktyflg[1+1];		// 76 治験拡張フラグ 
	char	apkntino[13+1];		// 77 AUTO-P検体Ｎｏ 
	char	sdnm[20+1];		// 78 診断名 
	char	bko1[20+1];		// 79 備考１ 
	char	bko2[20+1];		// 80 備考２ 
	char	bko3[20+1];		// 81 備考３ 
	char	zstrdh[26+1];		// 82 属性登録日時 
	char	zsssdh[26+1];		// 83 属性修正日時 
	char	stlzsssdh[26+1];	// 84 サテライト内属性修正日時 
	char	stlzsssip[15+1];	// 85 サテライト内属性修正端末IP 
	char	stlzssssyaid[8+1];	// 86 サテライト内属性修正入力者 
	char	ksndh[26+1];		// 87 情報更新日時 
	char	oyasstcd[7+1];		// 88 親施設コード 
	char	trkdh[26+1];		// 89 登録日時 
} my_stDbKanjya ;

typedef struct _stCHKZOK
{
	char	utkymd[10+1];		// 1  ＢＭＬ受付年月日
	char	irino[11+1];		// 2  依頼書Ｎｏ
	char	knsgrp[16+1];		// 3  検査グループ
	char	kmkcd[7+1];		// 4  項目コード
	char	sc[5+1];		// 10 身長
	char	scflg[1+1];		// 11 身長 チェックフラグ
	char	tj[5+1];		// 12 体重
	char	tjflg[1+1];		// 13 体重  チェックフラグ
	char	tjtni[1+1];		// 14 体重区分
	char	tjtniflg[1+1];		// 15 体重区分チェックフラグ
	char	sbtkbn[1+1];		// 16 性別区分
	char	sbtkbnflg[1+1];		// 17 性別区分チェックフラグ
	char	age[3+1];		// 18 年齢
	char	ageflg[1+1];		// 19 年齢チェックフラグ
	char	agekbn[1+1];		// 20 年齢区分
	char	agekbnflg[1+1];		// 21 年齢区分チェックフラグ
} my_stCHKZOK ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
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
