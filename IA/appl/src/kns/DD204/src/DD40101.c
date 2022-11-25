/*******************************************************************************/
/*                                                                             */
/*     ＢＭＬ様向け検査システム                                                */
/*                                                                             */
/*     システム名：検査結果異常チェック                                        */
/*     ファイル名：DD40101.c                                                   */
/*     概要      ：分析機からの検査結果のリアルタイムチェックを行う。          */
/*                                                                             */
/*******************************************************************************/

/*******************************************************************************/
/*  Ver.     Date           Name           History                             */
/* --------------------------------------------------------------------------- */
/*  1.00     2006/01/13     S.Tsunekawa    Create                              */
/* --------------------------------------------------------------------------- */
/*  Ver.     日付           名前           修正内容                            */
/* --------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M対応初版                         */
/*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "DD204.h"
#include "DD40101.h"
/*
#include "bmllog.h"
#include "bmlprm.h"
*/

void SetKekkaDefault(Kekka *pKekka);
void SetKekkaDefaultSpace(Kekka *pKekka);
int chkInfoRead(int mode, char * kmkcd,char * fName, char **Data, char *buff);

int	RenjiChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta);
int	SoukanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta);
int	KanrenChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld,SaikenInfo * fSaiken);
int	BungaChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld,SaikenInfo * fSaiken);
int	NyubiYoketuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou);
int	NyubiYoketu(Kekka * pKekka, int KekkaCnt);
int	KisyakuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char *cKisyak, int keta);
void GetModule( char * pFrom, int * pTo ) ;

int KekkaMarume(Kekka * pKekka, int KekkaCnt, char * ReadFileName);

double StringCal_sub(char enzan,double val1,double val2);
double StringCal(char *CalStr) ;

void trim(char * dst, char *src);

int GetKenorder(SOCKET_INF* ,int, int*);        /* 検査オーダー取得処理 */
void SetKekkaData(SOCKET_INF*,int);

/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
/* 計算式拡張対応                                                           */

#ifndef MAXBUF
#define MAXBUF                   (260)
#endif									/* !define MAXBUF					*/

/* 検査オーダーに含まれる属性に関する項目のバイト サイズ                    */
#define FLDSIZE_SC         ((size_t)5)  /* 身長 (cm)                        */
#define FLDSIZE_TJ         ((size_t)5)  /* 体重                             */
#define FLDSIZE_TJTNI      ((size_t)1)  /* 体重区分                         */
#define FLDSIZE_TNTME      ((size_t)4)  /* 蓄尿時間                         */
#define FLDSIZE_TNTNI      ((size_t)1)  /* 蓄尿時間区分                     */
#define FLDSIZE_TNRYO      ((size_t)5)  /* 蓄尿量                           */
#define FLDSIZE_TNRYOTNI   ((size_t)1)  /* 蓄尿量区分                       */

#define FLDSIZE_SBTKBN     ((size_t)1)  /* 性別区分                         */
#define FLDSIZE_AGE        ((size_t)3)  /* 年齢                             */
#define FLDSIZE_AGEKBN     ((size_t)1)  /* 年齢区分                         */

/* 検査オーダーのファイル (CSV 形式) に含まれる属性情報の位置               */
#define FLDIDX_SC                 (40)  /* 身長 (cm)                        */
#define FLDIDX_TJ                 (41)  /* 体重                             */
#define FLDIDX_TJTNI              (42)  /* 体重区分                         */
#define FLDIDX_TNTME              (50)  /* 蓄尿時間                         */
#define FLDIDX_TNTNI              (51)  /* 蓄尿時間区分                     */
#define FLDIDX_TNRYO              (52)  /* 蓄尿量                           */
#define FLDIDX_TNRYOTNI           (53)  /* 蓄尿量区分                       */
#define FLDIDX_SBTKBN             (43)  /* 性別区分                         */
#define FLDIDX_AGE                (46)  /* 年齢                             */
#define FLDIDX_AGEKBN             (47)  /* 年齢区分                         */

/* 単位等を示す項目に格納される識別子                                       */
#define _VALUE_TNTNI_HOUR       ('0')   /* 蓄尿時間: 時間単位               */
#define _VALUE_TNTNI_MINUTE     ('1')   /* 蓄尿時間: 分単位                 */
#define _VALUE_TNTNI_UNKNOWN    ('9')   /* 蓄尿時間: 時間単位不明           */
#define _VALUE_TNRYO_MILLILITER ('0')   /* 蓄尿量: ミリ リットル単位        */
#define _VALUE_TNRYO_LITER      ('1')   /* 蓄尿量: リットル単位             */
#define _VALUE_TNRYO_UNKNOWN    ('9')   /* 蓄尿量: 量単位不明               */
#define _VALUE_TJTNI_GRAM       ('1')   /* 体重: グラム単位                 */
#define _VALUE_TJTNI_KILLOGRAM  ('0')   /* 体重: キログラム単位             */
#define _VALUE_SBTKBN_MALE      ('0')   /* 性別: 男性                       */
#define _VALUE_SBTKBN_FEMALE    ('1')   /* 性別: 女性                       */
#define _VALUE_SBTKBN_UNKNOWN   ('9')   /* 性別: 性別不明                   */
#define _VALUE_AGEKBN_YEAR      ('Y')   /* 年齢: 年齢                       */

/* 計算式に含まれる属性情報の値に置換する指定                               */
#define KSNSK_TNTME     ('N')           /* 蓄尿時間 (時間単位)              */
#define KSNSK_TNRYO     ('R')           /* 蓄尿量 (ミリ リットル単位)       */
#define KSNSK_SC        ('T')           /* 身長                             */
#define KSNSK_TJ        ('W')           /* 体重 (グラム単位)                */
#define KSNSK_SBTKBN    ('S')           /* 性別区分                         */
#define KSNSK_AGE       ('A')           /* 年齢                             */

char gszTransfer[MAXBUF + 1];			/* 文字列→数値 変換バッファ
										   単一の値の置換のみなので、コレで
										   足りる                           */

/* 計算式中の IF ブロック展開                                               */
extern char *OperateKSNSK(const char *);

/* 数値文字列判定                                                           */
extern int _isnumeric(const char *);

/*---<< End add source Feb 27, 2008 H.Sato >>---*/

#define		READ_BUFF_SIZE		10240

char		GetFolder[256];
char		GetFolder2[256];
char		ReadFileName[256];
char		ReadFileNameOD[256];

char		testChkValue[21];
char		NyubiCD[8];
char		NyubiCM[6];
char		NyubiCHK[21];
char		NyubiKekka[21];
char		NyubiSTS[3];
char		YoketsuCD[8];
char		YoketsuCM[6];
char		YoketsuCHK[21];
char		YoketsuKekka[21];
char		YoketsuSTS[3];
char		OudanCD[8];
char		OudanCM[6];
char		OudanCHK[21];
char		OudanKekka[21];
char		OudanSTS[3];

/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
extern XBARM_INF  sXbarm_inf[XBARM_ITEM_NUM];
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
char	aMstFolder[256];		/* ファイル名エリア */

// 希釈倍率マスタ固定長定義
typedef struct stKSKBRMST {
	char	BSKKBN[4];		/* 分析機区分 */
	char	KNSGRP[16];		/* 検査グループ */
	char	KMKCD[7];		/* 項目コード */
	char	KSBR[15];		/* 希釈倍率 */
	double	KMIN; 			/* 希釈下限値 */
	double	KMAX;			/* 希釈上限値 */
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 希釈倍率マスタの施設コード対応 ***/
    char    KAIYMD[8];      /* 開始年月日 */
    char    HAIYMD[8];      /* 廃止年月日 */
    char    HNKTNTID[8];    /* 変更担当ID */
    char    KSNDHKSNDH[12]; /* 情報更新日時 */
    char    SSTCD[8];       /* 施設コード */
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
} KSKBRMST;

KSKBRMST * gpKSKBRMST;
int		 gKSKBRMSTnum;

typedef enum myFlg {
	MY_FLG_ON,
	MY_FLG_OFF
} MY_FLG ;

typedef struct stKeisanChk_tag {
	char motoKMKCD[8];
	char KMKCD[8];
	double raw;
	MY_FLG flgRawNone ;
} STKEISANCHK;


int	KeisanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, STKEISANCHK * calbuf );

/******************************************************************************/
/*	関 数 名  ：RealTimeChkInit()											  */
/*	機能概要  ：リアルタイム再検チェック初期処理							  */
/*	入	  力  ：															  */
/*	 第１引数 ：															  */
/*	 第２引数 ：															  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int RealTimeChkInit()
{
	BMLPRM * bp;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	bp = ZbmlPrmOpen( DD40101_INI_FILE_NAME );
	ZbmlPrmGetVal(bp, "ChkInfoFileFolder", GetFolder);
	ZbmlPrmGetVal(bp, "ChkInfoFileFolder2", GetFolder2);

	/* 乳び・溶血の項目コード及び設定コメントCDの取得 */
	ZbmlPrmGetVal(bp, "NyubiCD", NyubiCD);
	ZbmlPrmGetVal(bp, "NyubiCM", NyubiCM);
	ZbmlPrmGetVal(bp, "NyubiCHK", NyubiCHK);
	ZbmlPrmGetVal(bp, "YoketsuCD", YoketsuCD);
	ZbmlPrmGetVal(bp, "YoketsuCM", YoketsuCM);
	ZbmlPrmGetVal(bp, "YoketsuCHK", YoketsuCHK);
	ZbmlPrmGetVal(bp, "OudanCD", OudanCD);
	ZbmlPrmGetVal(bp, "OudanCM", OudanCM);
	ZbmlPrmGetVal(bp, "OudanCHK", OudanCHK);

	ZbmlPrmGetVal(bp, "GetMstFolder", aMstFolder);

	ZbmlPrmClose(bp);

	/* 希釈倍率マスタをファイルより読み出す。 */


	int		iWrk;
	char	aWrkBuf[255];
	char	buff[1024];
	FILE	*fp;
	char	** pFld;
	int		cnt;
	int		offset;
	char    *adrCR;

	memset( aWrkBuf, 0, sizeof(aWrkBuf) );
	strcpy( aWrkBuf,aMstFolder );
	strcat( aWrkBuf,"kskbrmst.del" );
	adrCR = NULL;

#ifdef _DEBUG_
	printf( "ファイル名：%s\n",aWrkBuf );
#endif

	fp = fopen( aWrkBuf,"r");
	if( fp == NULL ) {
		printf("ファイルのオープンに失敗しました。\n");
		return -1;
	}
	gKSKBRMSTnum = 0;
	memset( buff,0,1024 );
	while( fgets( buff, 1024, fp ) != NULL ) {
		++gKSKBRMSTnum;
	}

	gpKSKBRMST = malloc(sizeof(KSKBRMST)*gKSKBRMSTnum);
	memset(gpKSKBRMST, 0, sizeof(KSKBRMST)*gKSKBRMSTnum);
	rewind(fp);
	iWrk = 0;
	memset( buff,0,1024 );
	pFld = malloc(sizeof(char *)*15);
	while( fgets( buff, 1024, fp ) != NULL ) {
		if( iWrk >= gKSKBRMSTnum ) {
			break;
		}
		/* 末尾の改行コードを削除 */
		adrCR = strchr(buff, ( int )'\r');
		if (adrCR != NULL) {
			*adrCR = '\0';
		}
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt++] = &buff[offset+1];
				buff[offset] = '\0';
			}
			offset++;
		}
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 希釈倍率マスタの施設コード対応 ***/
        /*if (cnt != 10) {*/
        if (cnt != 11) {
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
			// フィールド数が一致しない
			printf( "フィールド数が一致しませんでした。\n" );
			break;
		}

		// フィールドの有効期限をチェックするし、メモリへ転送する。
		strcpy( gpKSKBRMST[iWrk].BSKKBN,pFld[0] );
		strcpy( gpKSKBRMST[iWrk].KNSGRP,pFld[1] );
		strcpy( gpKSKBRMST[iWrk].KMKCD,pFld[2] );
		strcpy( gpKSKBRMST[iWrk].KSBR,pFld[3] );
		gpKSKBRMST[iWrk].KMIN = atof( pFld[4] );
		gpKSKBRMST[iWrk].KMAX = atof( pFld[5] );
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 希釈倍率マスタの施設コード対応 ***/
		strcpy( gpKSKBRMST[iWrk].SSTCD,pFld[10] );
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
		++iWrk;
		memset( buff,0,1024 );
	}
	gKSKBRMSTnum = iWrk;
	free(pFld);

	return 0;
}

/******************************************************************************/
/*	関 数 名  ：RealTimeChk()												  */
/*	機能概要  ：リアルタイム再検チェック処理								  */
/*	入	  力  ：															  */
/*	 第１引数 ：p		:	アプリケーション情報構造体ポインタ				  */
/*	 第２引数 ：pKekka	:	検査結果構造体ポインタ							  */
/*	 第３引数 ：KekkaCnt:	結果数											  */
/*	出	  力  ：fSaiken	:	再検情報ポインタ								  */
/*	復帰情報  ：int															  */
/*					0:正常													  */
/*					1:再検あり												  */
/******************************************************************************/
int	RealTimeChk(SOCKET_INF *p, SaikenInfo * fSaiken)
{
	static	int	chkCnt = 0;
	static	int	stCnt = 0;
	int		lCnt;
	int		ret = 0;
	int		ret2;
	int		flg;
	char	*pBuff;
	char	**pFld;
	char	*pBuffOD;
	char	**pFldOD;
	char	tmpBuff[11];
	int		fNyuYou;

	int		kCnt = 0;
	STKEISANCHK	kekkabuf[32];

	char	 cRawBuf[256] ;

	int 		 li_SaveKekkaNum ;
	int 		 li_KenorderCnt ;
	SaikenInfo	*nfSaiken;
	int			 li_idxC ;
	int			 li_idxK ;
	int			 li_idxO ;
	int			 li_RetSts ;
	int			iKnssu;
	char		cKsktkbn;
#ifdef _DEBUG_
	char		cMsgBuf[512];
#endif

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
#ifdef _DEBUG_
	printf("\n●●● RealTimeChk(%d回目) Start\n", chkCnt + 1);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "\n●●● RealTimeChk(%d回目) Start\n", chkCnt + 1);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	if (chkCnt > 3) return 0;
	chkCnt ++;

	pFld = malloc(sizeof(char *)*200);
	pBuff = malloc(sizeof(char) * READ_BUFF_SIZE);
	pFldOD = malloc(sizeof(char *)*200);
	pBuffOD = malloc(sizeof(char) * READ_BUFF_SIZE);
	/* ADD E.Osada 2006-07-15 */
	memset(pFld, 0, sizeof(char *)*200);
	memset(pBuff, 0, sizeof(char) * READ_BUFF_SIZE);
	memset(pFldOD, 0, sizeof(char *)*200);
	memset(pBuffOD, 0, sizeof(char) * READ_BUFF_SIZE);
	/**/
	/* 即時チェック情報のファイル名を先頭の結果情報から作成 */
	strncpy(ReadFileName, "CH_", 256);
	strncpy(tmpBuff, p->pKekka->asyrckid, 10);
	strncat(tmpBuff, "__________", 10-strlen(p->pKekka->asyrckid));
	strncat(ReadFileName, tmpBuff, 256);
	sprintf(tmpBuff, "%03d", p->pKekka->asyrckpos);
	strncat(ReadFileName, tmpBuff, 256);
	strncat(ReadFileName, ".dat", 256);

	/* オーダーファイルの名前を即時チェック情報のファイル名から作成 */
	strncpy(ReadFileNameOD, ReadFileName, 256);
	ReadFileNameOD[0] = 'O';
	ReadFileNameOD[1] = 'D';

	/* 乳び・溶血の存在チェック */
	fNyuYou = NyubiYoketu(p->pKekka, p->iKekkaNum);

	/* RAWデータの丸め処理 */
	KekkaMarume(p->pKekka, p->iKekkaNum, ReadFileName);

	for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
// 2009.02.18 moriya ->
		memset(pFld, 0, sizeof(char *)*200);
		memset(pBuff, 0, sizeof(char) * READ_BUFF_SIZE);
		memset(pFldOD, 0, sizeof(char *)*200);
		memset(pBuffOD, 0, sizeof(char) * READ_BUFF_SIZE);
// 2009.02.18 moriya -<
		fSaiken[lCnt].flg = 0;

		if ( p->pKekka[lCnt].knsflg == 'H' ) {
			continue;
		}
		/* 即時チェック情報ファイル読み込み */
		ret2 = chkInfoRead(0, p->pKekka[lCnt].kmkcd, ReadFileName, pFld, pBuff);
		if ( ret2 != 0 ) {
			/*  即時チェック情報なし */
			continue;
		}
		/* オーダー情報ファイル読み込み */
		ret2 = chkInfoRead(1, p->pKekka[lCnt].kmkcd, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			/* オーダー情報なし */
			continue;
		}

#ifdef _DEBUG_
		printf("チェックスタート >>>>>>>>>>>>>>\n");
		sFncSyslog ( LOG_ERR, "", "チェックスタート >>>>>>>>>>>>>>\n" ) ;
#endif
		/* 2006.08.11 Nagata 分析機アラームチェックでNGの場合、*/
		/* 結果にデフォルト値をセットしない                    */
		if(p->pKekka[lCnt].yobiflg01 != '2'){
			/* 結果情報にDefault値を設定 */
			SetKekkaDefault(&p->pKekka[lCnt]);
		}
		else{
			/* 2006.08.11 Nagata 分析機アラームチェックでNGの場合、 */
			/* 検査フラグ、結果のエラーフラグ以外にデフォルト値をセットする */
			SetKekkaDefaultSpace(&p->pKekka[lCnt]);
		}

		trim(cRawBuf, p->pKekka[lCnt].rawdata);

		if ( cRawBuf[0]  == '\0' || cRawBuf[0]  == '/' ) {
			fSaiken[lCnt].flg = 1;
			ret = 1;
			if( p->pKekka[lCnt].yobiflg01 != '2'){
				p->pKekka[lCnt].knsflg = 'A';
				p->pKekka[lCnt].yobiflg01 = '2';	/* エラーフラグ ADD 2006.08.11 */
				/* 2006.08.11 Nagata ブランクデータの場合、                      */
				/* 検査フラグ、結果のエラーフラグ以外にデフォルト値をセットする  */
				SetKekkaDefaultSpace(&p->pKekka[lCnt]);
			}
			continue ;
		}

		if (pFld[18][0] == '1') {		/* レンジチェック */
			flg = RenjiChk(pFld[38], p->pKekka, p->iKekkaNum, lCnt, pFldOD, atoi(pFld[57]));
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* データアラーム対応 */
					p->pKekka[lCnt].knsflg = 'A';
				}

			}
		}
		else {
		}
		if (pFld[19][0] == '1') {		/* 相関チェック(WS内) */
			flg = SoukanChk(pFld[39], p->pKekka, p->iKekkaNum, lCnt, pFldOD, atoi(pFld[57]));
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {/* データアラーム対応 */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
		}
		else {
		}
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 血清チェックを行い項目毎に再検を行うためここから復活---↓ ***/
		if (pFld[22][0] == '1') {		/* 乳び・溶血チェック */
			flg = NyubiYoketuChk(pFld[42], p->pKekka, p->iKekkaNum, lCnt, fNyuYou);
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* データアラーム対応 */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
		}
		else {
		}
/*** 血清チェックを行い項目毎に再検を行うためここまで復活---↑ ***/
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */

		/* 2006-08-30 Nagata 分析機アラームで希釈倍率がセットされている場合は、希釈チェックを行わない */
		if( pFld[28][0] == '1' &&
				!(p->pKekka[lCnt].yobiflg01 == '2' && strlen(fSaiken[lCnt].KSBR) != 0) ) {	/* 希釈再検チェック */
			flg = KisyakuChk(pFld[43], p->pKekka, p->iKekkaNum, lCnt, fSaiken[lCnt].KSBR, atoi(pFld[57]));
			/* CHG E.Osada 2006.07.21 再検データの場合無条件で検査フラグ:'A' */
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* データアラーム対応 */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
			else if (flg == 2) {
				fSaiken[lCnt].flg = 2;
				ret = 0;
				p->pKekka[lCnt].knsflg		= 'R';
			}
		}
		else {
		}

	}

	/* 関連・分画チェックのみすべてのチェックが終わってからチェックする。*/
	for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
// 2009.02.18 moriya ->
		memset(pFld, 0, sizeof(char *)*200);
		memset(pBuff, 0, sizeof(char) * READ_BUFF_SIZE);
		memset(pFldOD, 0, sizeof(char *)*200);
		memset(pBuffOD, 0, sizeof(char) * READ_BUFF_SIZE);
// 2009.02.18 moriya -<

		/* 即時チェック情報ファイル読み込み */
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : 即時チェック情報ファイル読み込み\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : 即時チェック情報ファイル読み込み\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		ret2 = chkInfoRead(0, p->pKekka[lCnt].kmkcd, ReadFileName, pFld, pBuff);
		if ( ret2 != 0 ) {
			/* 即時チェック情報なし */
#ifdef _DEBUG_
			printf( "RealTimeChk(%d) : 即時チェック情報ファイル読み込み - 即時チェック情報なし\n", __LINE__);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : 即時チェック情報ファイル読み込み - 即時チェック情報なし\n", __LINE__);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			continue;
		}
		/* オーダー情報ファイル読み込み */
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : オーダー情報ファイル読み込み\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : オーダー情報ファイル読み込み\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		ret2 = chkInfoRead(1, p->pKekka[lCnt].kmkcd, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			/* 即時チェック情報なし */
#ifdef _DEBUG_
			printf( "RealTimeChk(%d) : オーダー情報ファイル読み込み - 即時チェック情報なし\n", __LINE__);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : オーダー情報ファイル読み込み - 即時チェック情報なし\n", __LINE__);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n", __LINE__, p->pKekka[lCnt].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf( "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : ReadFileName          = %s\n\n", __LINE__, ReadFileName);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			continue;
		}
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : 分画チェック\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : 分画チェック\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		if (pFld[21][0] == '1') {		/* 分画チェック */
			flg = BungaChk(pFld[41], p->pKekka, p->iKekkaNum, lCnt, pFldOD, fSaiken);
			if (flg == 1) {
				fSaiken[lCnt].flg = 1;
				ret = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {	/* データアラーム対応 */
					p->pKekka[lCnt].knsflg = 'A';
				}
			}
		}
		else {
		}
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : 関連チェック\n", __LINE__);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : 関連チェック\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		if (pFld[20][0] == '1') {		/* 関連チェック */
			flg = KanrenChk(pFld[40], p->pKekka, p->iKekkaNum, lCnt, pFldOD, fSaiken);
			if( !flg )
				p->pKekka[lCnt].kanrenflg	= '0';
		}
		else {
		}
		/* 計算チェック */
#ifdef _DEBUG_
		printf( "RealTimeChk(%d) : 計算チェック\n", __LINE__ );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : 計算チェック\n", __LINE__);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : ReadFileName          = %s\n", __LINE__, ReadFileName);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : ReadFileName          = %s\n", __LINE__, ReadFileName);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[18][0] = [%c]\n", __LINE__, pFld[18][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[18][0] = [%c]\n", __LINE__, pFld[18][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[19][0] = [%c]\n", __LINE__, pFld[19][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[19][0] = [%c]\n", __LINE__, pFld[19][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[20][0] = [%c]\n", __LINE__, pFld[20][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[20][0] = [%c]\n", __LINE__, pFld[20][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[21][0] = [%c]\n", __LINE__, pFld[21][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[21][0] = [%c]\n", __LINE__, pFld[21][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[22][0] = [%c]\n", __LINE__, pFld[22][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[22][0] = [%c]\n", __LINE__, pFld[22][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[23][0] = [%c]\n", __LINE__, pFld[23][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[23][0] = [%c]\n", __LINE__, pFld[23][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[24][0] = [%c]\n", __LINE__, pFld[24][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[24][0] = [%c]\n", __LINE__, pFld[24][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[25][0] = [%c]\n", __LINE__, pFld[25][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[25][0] = [%c]\n", __LINE__, pFld[25][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[26][0] = [%c]\n", __LINE__, pFld[26][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[26][0] = [%c]\n", __LINE__, pFld[26][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[27][0] = [%c]\n", __LINE__, pFld[27][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[27][0] = [%c]\n", __LINE__, pFld[27][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : pFld[28][0] = [%c]\n", __LINE__, pFld[28][0] );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : pFld[28][0] = [%c]\n", __LINE__, pFld[28][0] );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
		printf( "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n\n", __LINE__, p->pKekka[lCnt].kmkcd);
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].kmkcd = %s\n\n", __LINE__, p->pKekka[lCnt].kmkcd);
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		if (pFld[25][0] == '1') {
#ifdef _DEBUG_
			printf( "RealTimeChk(%d) : 計算チェック入った\n", __LINE__ );
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : 計算チェック入った\n", __LINE__ );
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			kCnt += KeisanChk(pFld[45], p->pKekka, p->iKekkaNum, lCnt, pFldOD, &kekkabuf[kCnt]);
		}
	}
#ifdef _DEBUG_
	printf( "\n● RealTimeChk(%d) : kCnt = [%d]\n", __LINE__, kCnt );
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "\n● RealTimeChk(%d) : kCnt = [%d]\n", __LINE__, kCnt );
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	/***
	 ***	計算項目処理
	 ***		ここで計算項目の結果をp->pKekka変数に追加する
	 ***/
	if (kCnt > 0) {
		/*---------------------------------------------------------------------*/
		/*	追加前の結果件数を退避                                             */
		/*		この値は再検フラグ設定時に使用する                             */
		/*---------------------------------------------------------------------*/
		li_SaveKekkaNum = p->iKekkaNum ;

		/*---------------------------------------------------------------------*/
		/*  検査オーダ情報取得                                                 */
		/*		結果追加時の設定値として使用する                               */
		/*---------------------------------------------------------------------*/
		li_KenorderCnt = 0 ;
		li_RetSts = GetKenorder ( p, ORDER_DAT_1, &li_KenorderCnt );
		if( li_RetSts != RTN_OK ) {
			li_RetSts = GetKenorder ( p, ORDER_DAT_2, &li_KenorderCnt );
		}
#ifdef _DEBUG_
		printf( "\n● RealTimeChk(%d) : GetKenorder後\n", __LINE__, kCnt );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "\n● RealTimeChk(%d) : GetKenorder後\n", __LINE__, kCnt );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

		/*---------------------------------------------------------------------*/
		/*	再検フラグ設定領域作成＆設定                                       */
		/*		計算項目を結果に追加後、再度リアルチェックを行う               */
		/*---------------------------------------------------------------------*/
		nfSaiken = malloc(sizeof(SaikenInfo)*(p->iKekkaNum + kCnt));
		memset(nfSaiken, 0, sizeof(SaikenInfo)*(p->iKekkaNum + kCnt));
		memcpy(nfSaiken, fSaiken, sizeof(SaikenInfo)*(p->iKekkaNum + kCnt));
#ifdef _DEBUG_
		printf( "\n● RealTimeChk(%d) : malloc後\n", __LINE__, kCnt );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "\n● RealTimeChk(%d) : malloc後\n", __LINE__, kCnt );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

		/*---------------------------------------------------------------------*/
		/*	結果情報に計算項目を追加する                                       */
		/*		kCnt : つい数べき計算項目数                                    */
		/*---------------------------------------------------------------------*/
		for ( li_idxC = 0; li_idxC < kCnt; li_idxC ++ ) {
			if( li_idxC == 0 ) iKnssu = p->pKekka[li_idxC].knssu;	/* ADD E.Osada 2006-08-12 */
			/* ADD Nagata 2006-09-02 */
			/*     検査工程区分は、ファイルの１レコードから引き継ぐ */
			if( li_idxC == 0 ) cKsktkbn = p->pKekka[li_idxC].ksktkbn;

			/*	結果情報検索 */
			for ( li_idxK = 0; li_idxK < p->iKekkaNum ; li_idxK ++ ) {
				if ( memcmp ( kekkabuf[li_idxC].KMKCD,
							  p->pKekka[li_idxK].kmkcd, 7) == 0) {
					break;
				}
			}
			if (li_idxK < p->iKekkaNum )  {
				/*	既に存在した場合は値だけ変更する */
				if ( kekkabuf[li_idxC].flgRawNone == MY_FLG_ON ) {
					memset ( p->pKekka[li_idxK].rawdata, ' ', sizeof ( p->pKekka[li_idxK].rawdata ) - 1 ) ;
					/* MOD(S) 2006.08.11 Hiwa 計算フラグ='2'をやめてエラーフラグ='2' */
					p->pKekka[li_idxK].yobiflg01 = '2';
				}
				else {
					sprintf(p->pKekka[li_idxK].rawdata, "%f", kekkabuf[li_idxC].raw);
				}
				continue;
			}
			/*	存在しない場合はオーダ情報に存在するかチェックを行う */
			for ( li_idxO = 0; li_idxO < li_KenorderCnt ; li_idxO ++) {
				if ( memcmp( kekkabuf[li_idxC].KMKCD,
							 pKenorder[li_idxO].kmkcd, 7) == 0) {
					break;
				}
			}
			if (li_idxO >= li_KenorderCnt ) {
				/*	存在しない場合は次の計算項目に移る */
				continue;
			}
			/*	存在する場合、結果情報を追加する */
#ifdef _DEBUG_
			printf( "\n● RealTimeChk(%d) : 存在する場合、結果情報を追加する\n", __LINE__, kCnt );
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "\n● RealTimeChk(%d) : 存在する場合、結果情報を追加する\n", __LINE__, kCnt );
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
//			p->iKekkaNum++ ;
			p->pKekka = realloc ( p->pKekka, sizeof(Kekka)*(p->iKekkaNum + 1) ) ;
//			p->pKekka = realloc ( p->pKekka, sizeof(Kekka)*(p->iKekkaNum) ) ;
#ifdef _DEBUG_
			printf( "\n● RealTimeChk(%d) : realloc後\n", __LINE__, kCnt );
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "\n● RealTimeChk(%d) : realloc後\n", __LINE__, kCnt );
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			SetKekkaData ( p, li_idxO ) ;
			/* ADD E.Osada 2006-08-12 内部コードはクリアする */
			memset(p->pKekka[p->iKekkaNum].nbkmkcd, 0, sizeof(p->pKekka[p->iKekkaNum].nbkmkcd));
			memset(p->pKekka[p->iKekkaNum].jisksbr, 0, sizeof(p->pKekka[p->iKekkaNum].jisksbr));
			p->pKekka[p->iKekkaNum].knssu = iKnssu;
			/* ADD Nagata 2006-09-02 */
			/*     検査工程区分は、ファイルの１レコードから引き継ぐ */
			p->pKekka[p->iKekkaNum].ksktkbn = cKsktkbn;

			if ( kekkabuf[li_idxC].flgRawNone == MY_FLG_ON ) {
				memset ( p->pKekka[p->iKekkaNum].rawdata, ' ', sizeof ( p->pKekka[p->iKekkaNum].rawdata ) - 1 ) ;
				/* MOD(S) 2006.08.11 Hiwa 計算フラグ='2'をやめてエラーフラグ='2' */
				p->pKekka[p->iKekkaNum].yobiflg01 = '2';
			}
			else {
				sprintf(p->pKekka[p->iKekkaNum].rawdata, "%f", kekkabuf[li_idxC].raw);
			}
			p->iKekkaNum++ ;
			p->iKekkaCnt++ ;
		}
#ifdef _DEBUG_
		printf( "\n● RealTimeChk(%d) : 計算処理後\n", __LINE__, kCnt );
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "\n● RealTimeChk(%d) : 計算処理後\n", __LINE__, kCnt );
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

		free( pKenorder );
		pKenorder = NULL ;

		/*---------------------------------------------------------------------*/
		/*	リアルタイムチェックを再帰的に呼び出す                             */
		/*		追加または変更された 計算項目のチェックのため                  */
		/*---------------------------------------------------------------------*/
		ret2 = RealTimeChk(p, nfSaiken);
		/* チェック内容をマージする。 */
		/*---------------------------------------------------------------------*/
		/*	発生した再検フラグを反映する                                       */
		/*		！！重要！！ ただし計算子項目の再検フラグを更新する            */
		/*---------------------------------------------------------------------*/
		for (lCnt = 0; lCnt < li_SaveKekkaNum; lCnt++) {
			if (nfSaiken[lCnt].flg == 1) {
				fSaiken[lCnt].flg = 1;
				if (p->pKekka[lCnt].knsflg != 'R') {
					p->pKekka[lCnt].knsflg = 'A';
				} else {
					fSaiken[lCnt].flg = 2;
					p->pKekka[lCnt].knsflg = 'R';
				}
			}
		}

		free(nfSaiken);

	}

/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** Xbarm再検制御のためフラグを追加 ***/
	/* RealTimeChkの再起呼び出しを考慮して、RealTimeChk(1回目)の場合のみチェックする。 */
	/* ※何度も再起呼び出しされた場合は、一番最後でチェックする */
	if (chkCnt == 1) {
		int iPos;
		int iKekkaPos;
		int gXsaiken = 0;
		int saiken   = 0;
		int module;
		char cXmChkFlg;

#ifdef _DEBUG_
		printf("%s●●● Xbarm再検判定\n", Now());
		memset(cMsgBuf, 0, sizeof(cMsgBuf));
		sprintf(cMsgBuf, "%s●●● Xbarm再検判定\n", Now());
		sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		// RealTimeChkで再検が設定されていない事を確認
		for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
			if (fSaiken[lCnt].flg == 1) {
#ifdef _DEBUG_
				printf("%sXbarm異常データのためXbarm再検なし\n", Now());
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%sXbarm異常データのためXbarm再検なし\n", Now());
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				saiken = 1;
				break;
			}
		}
		
	    for (iPos = 0; iPos < XBARM_ITEM_NUM; iPos++) {
			// 未設定領域に達したらブレイク
			if (sXbarm_inf[iPos].knsgrp[0] == '\0')
				break;

			// 今処理しているXbarm_inf構造体の項目コードと結果情報構造体の項目コードを検索し、
			// 見つかったらiKekkaPosの添字を確保
			for (iKekkaPos = 0; iKekkaPos < p->iKekkaNum; iKekkaPos++) {
				if (memcmp(sXbarm_inf[iPos].kmkcd,  p->pKekka[iKekkaPos].kmkcd, 7) == 0) {
					break;
				}
			}
			
			/* 見つからなかった場合 */
			if (iKekkaPos == p->iKekkaNum) {
				/* sXbarm_infの次の項目コードへ */
#ifdef _DEBUG_
				printf( "RealTimeChk(%d) : 見つからなかった場合、sXbarm_infの次の項目コードへ\n", __LINE__ );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : 見つからなかった場合、sXbarm_infの次の項目コードへ\n", __LINE__ );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				continue;
			}

			/* 項目マスタからX-Mチェックフラグを取得('0':異常判定を行う、'1':異常判定を行わない) */
			cXmChkFlg = GetXmChkFlg(p->pKekka[iKekkaPos].knsgrp, p->pKekka[iKekkaPos].kmkcd, p->pKekka[iKekkaPos].knskisymd);

			/* X-Mチェックフラグ(0:異常判定を行う、1:異常判定を行わない) */
			if (cXmChkFlg == '1') {
#ifdef _DEBUG_
				printf( "RealTimeChk(%d) : p->pKekka[iKekkaPos].knsgrp    = %s\n", __LINE__, p->pKekka[iKekkaPos].knsgrp );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].knsgrp    = %s\n", __LINE__, p->pKekka[iKekkaPos].knsgrp );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf( "RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf( "RealTimeChk(%d) : cXmChkFlg == '%c' なので、X-M異常判定を行わない\n", __LINE__, cXmChkFlg );
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "RealTimeChk(%d) : cXmChkFlg == '%c' なので、X-M異常判定を行わない\n", __LINE__, cXmChkFlg );
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				continue;
			}

#ifdef _DEBUG_
			printf("RealTimeChk(%d) : gXsaiken 前                    = %d\n", __LINE__, gXsaiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : gXsaiken 前                    = %d\n", __LINE__, gXsaiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
			gXsaiken = sXbarm_inf[iPos].saiken;

			GetModule(p->pKekka[iKekkaPos].bskgok, &module);
#ifdef _DEBUG_
			printf("RealTimeChk(%d) : gXsaiken 後                    = %d\n", __LINE__, gXsaiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : gXsaiken 後                    = %d\n", __LINE__, gXsaiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : saiken                         = %d\n", __LINE__, saiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : saiken                         = %d\n", __LINE__, saiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].kntno     = %s\n", __LINE__, p->pKekka[iKekkaPos].kntno);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].kntno     = %s\n", __LINE__, p->pKekka[iKekkaPos].kntno);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].kmkcd     = %s\n", __LINE__, p->pKekka[iKekkaPos].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].knssu     = %d\n", __LINE__, p->pKekka[iKekkaPos].knssu);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].knssu     = %d\n", __LINE__, p->pKekka[iKekkaPos].knssu);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].bskgok    = %s\n", __LINE__, p->pKekka[iKekkaPos].bskgok);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].bskgok    = %s\n", __LINE__, p->pKekka[iKekkaPos].bskgok);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : p->pKekka[iKekkaPos].irikbn    = %c\n\n", __LINE__, p->pKekka[iKekkaPos].irikbn);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[iKekkaPos].irikbn    = %c\n\n", __LINE__, p->pKekka[iKekkaPos].irikbn);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

			// Xbarm再検発生検体処理中なら、ステータスを進める
			if (gXsaiken == 1 && (p->pKekka[iKekkaPos].knssu >= 2 || saiken == 0)) {
#ifdef _DEBUG_
				printf("%s ●●● Xbarm再検フラグ2設定(kntno  = %s)\n", Now(), p->pKekka[iKekkaPos].kntno);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s ●●● Xbarm再検フラグ2設定(kntno  = %s)\n", Now(), p->pKekka[iKekkaPos].kntno);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (knsgrp = %s)\n", Now(), p->pKekka[iKekkaPos].knsgrp);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (knsgrp = %s)\n", Now(), p->pKekka[iKekkaPos].knsgrp);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (kmkcd  = %s)\n", Now(), p->pKekka[iKekkaPos].kmkcd);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (kmkcd  = %s)\n", Now(), p->pKekka[iKekkaPos].kmkcd);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf("%s                            (module = %d)\n\n", Now(), module);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "%s                            (module = %d)\n\n", Now(), module);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				gXsaiken = 2;
				// 1:Xbarm再検設定、2:設定時のチェック終了・次回分から再検処理開始、3:Xbarm再検処理済
			} else
			// Xbarm再検指示後の正常検体の場合、対象グループ・項目があればそれを再検する
		   	if (gXsaiken == 2 && saiken == 0 && p->pKekka[iKekkaPos].knssu <= 1 && p->pKekka[iKekkaPos].irikbn != 'Z') {
				// Xbarm再検中で、且つ再検フラグが立っていない（正常）場合
				for (lCnt = stCnt; lCnt < p->iKekkaNum; lCnt ++) {
					if ((memcmp(sXbarm_inf[iPos].knsgrp, p->pKekka[lCnt].knsgrp, 16) == 0) &&
					    (memcmp(sXbarm_inf[iPos].kmkcd,  p->pKekka[lCnt].kmkcd,   7) == 0) &&
					    (sXbarm_inf[iPos].iModuleNum == module)) {
#ifdef _DEBUG_
						printf("%s ●●● Xbarm再検フラグ3設定(kntno  = %s)\n", Now(), p->pKekka[lCnt].kntno);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s ●●● Xbarm再検フラグ3設定(kntno  = %s)\n", Now(), p->pKekka[lCnt].kntno);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (knsgrp = %s)\n", Now(), p->pKekka[lCnt].knsgrp);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (knsgrp = %s)\n", Now(), p->pKekka[lCnt].knsgrp);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (kmkcd  = %s)\n", Now(), p->pKekka[lCnt].kmkcd);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (kmkcd  = %s)\n", Now(), p->pKekka[lCnt].kmkcd);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (knssu  = %d)\n", Now(), p->pKekka[iKekkaPos].knssu);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
						printf("%s                            (module = %d)\n\n", Now(), module);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "%s                            (module = %d)\n\n", Now(), module);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
						fSaiken[lCnt].flg = 1;
						ret = 1;
						gXsaiken = 3; // 再検設定したら結果情報・予備２にXbarm再検を設定
						p->pKekka[lCnt].tobiflg02 = '1';
#ifdef _DEBUG_
						printf( "RealTimeChk(%d) : p->pKekka[lCnt].tobiflg02 = %c\n\n", __LINE__, p->pKekka[lCnt].tobiflg02 );
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "RealTimeChk(%d) : p->pKekka[lCnt].tobiflg02 = %c\n\n", __LINE__, p->pKekka[lCnt].tobiflg02 );
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
						if (p->pKekka[lCnt].knsflg != 'R') {
							p->pKekka[lCnt].knsflg = 'A';
						}
					}
				}
			}
			sXbarm_inf[iPos].saiken = gXsaiken;
#ifdef _DEBUG_
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].knsgrp        = %s\n", __LINE__, sXbarm_inf[iPos].knsgrp);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].knsgrp        = %s\n", __LINE__, sXbarm_inf[iPos].knsgrp);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].kmkcd         = %s\n", __LINE__, sXbarm_inf[iPos].kmkcd);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : sXbarm_inf[iPos].iModuleNum    = %d\n", __LINE__, sXbarm_inf[iPos].iModuleNum);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : module                         = %d\n", __LINE__, module);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
			printf("RealTimeChk(%d) : gXsaiken                       = %d\n\n", __LINE__, gXsaiken);
			memset(cMsgBuf, 0, sizeof(cMsgBuf));
			sprintf(cMsgBuf, "RealTimeChk(%d) : gXsaiken                       = %d\n\n", __LINE__, gXsaiken);
			sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
		}
	}
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */

	free(pFld);
	free(pBuff);
	free(pFldOD);
	free(pBuffOD);

	stCnt = 0;
	chkCnt --;
#ifdef _DEBUG_
	printf("\n●●● RealTimeChk(%d回目) End ret(%d)\n", chkCnt + 1, ret);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "\n●●● RealTimeChk(%d回目) End ret(%d)\n", chkCnt + 1, ret);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	return ret;
}
/******************************************************************************/
/*	関 数 名  ：SetKekkaDefault()											  */
/*	機能概要  ：結果情報Default設定											  */
/*	入	  力  ：															  */
/*	 第１引数 ：pKekka	: 結果情報構造体ポインタ							  */
/*	出	  力  ：pKekka	: 													  */
/*	復帰情報  ：void														  */
/******************************************************************************/
void SetKekkaDefault(Kekka *pKekka)
{
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	pKekka->pncrgflg		= '0';				// パニックレンジフラグ
	pKekka->knspncrgflg		= '0';				// 検査室パニックレンジフラグ
	pKekka->kkaksflg		= '0';				// 結果換算フラグ

	pKekka->kkajkcd			= '3';				// 結果状況コード

	pKekka->frkkaflg		= '0';				// フリー結果フラグ
	pKekka->gzbsflg			= '0';				// 画像別紙フラグ

	pKekka->kkaysnflg		= '1';				// 結果優先フラグ
	pKekka->tnyrkflg		= ' ';				// 手入力フラグ
	pKekka->siyflg			= '1';				// 採用フラグ
	pKekka->kkassflg		= '0';				// 結果修正フラグ

	pKekka->knsflg			= 'X';				// 検査フラグ
	pKekka->renjicflg		= '0';				// レンジチェック
	pKekka->soukn1flg		= '0';				// 相関チェック(WS内)
	pKekka->kanrenflg		= '0';				// 関連チェック
	pKekka->bunkkuflg		= '0';				// 分画チェック
	pKekka->kesseiflg		= '0';				// 乳び・溶血チェック
	pKekka->rirekiflg		= '0';				// 履歴チェック
	pKekka->syougoflg		= '0';				// 照合チェック
	pKekka->keisanflg		= '0';				// 計算チェック
	pKekka->per100flg		= '0';				// １００％チェック
	pKekka->tousekflg		= '0';				// 透析前後チェック
	pKekka->kisyakflg		= '0';				// 希釈再検チェック
	pKekka->kouseiflg		= '0';				// 校正処理
	pKekka->syoungflg		= '0';				// 照合NG確定処理
	pKekka->soukn2flg		= '0';				// 相関チェック(WS間)
	pKekka->fukaptflg		= '0';				// 負荷パターンチェック
	pKekka->yobiflg01		= '1';				//
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*	pKekka->tobiflg02		= '1';				// Xbarm再検指示 */
	pKekka->tobiflg02		= '0';				// Xbarm再検指示
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
	pKekka->yobiflg03		= '1';				//
	pKekka->yobiflg04		= '1';				//
	pKekka->yobiflg05		= '1';				//
}

/******************************************************************************/
/*	関 数 名  ：SetKekkaDefaultSpace()										  */
/*	機能概要  ：結果情報Default設定(スペースもしくは、"/"結果対応）			  */
/*	入	  力  ：															  */
/*	 第１引数 ：pKekka	: 結果情報構造体ポインタ							  */
/*	出	  力  ：pKekka	: 													  */
/*	復帰情報  ：void														  */
/******************************************************************************/
void SetKekkaDefaultSpace(Kekka *pKekka)
{
#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	pKekka->pncrgflg		= '0';				// パニックレンジフラグ
	pKekka->knspncrgflg		= '0';				// 検査室パニックレンジフラグ
	pKekka->kkaksflg		= '0';				// 結果換算フラグ

	pKekka->kkajkcd			= '3';				// 結果状況コード

	pKekka->frkkaflg		= '0';				// フリー結果フラグ
	pKekka->gzbsflg			= '0';				// 画像別紙フラグ

	pKekka->kkaysnflg		= '1';				// 結果優先フラグ
	pKekka->tnyrkflg		= ' ';				// 手入力フラグ
	pKekka->siyflg			= '1';				// 採用フラグ
	pKekka->kkassflg		= '0';				// 結果修正フラグ

	// 2006/08/12 nagata フラグ類は空白の時にデフォルト値をセットする
	if(pKekka->knsflg  == '\0'){
		pKekka->knsflg			= 'R';				// 検査フラグ
	}
	if(pKekka->renjicflg == '\0'){
		pKekka->renjicflg		= '0';				// レンジチェック
	}
	if(pKekka->soukn1flg == '\0'){
		pKekka->soukn1flg		= '0';				// 相関チェック(WS内)
	}
	if(pKekka->kanrenflg == '\0'){
		pKekka->kanrenflg		= '0';				// 関連チェック
	}
	if(pKekka->bunkkuflg == '\0'){
		pKekka->bunkkuflg		= '0';				// 分画チェック
	}
	if(pKekka->kesseiflg == '\0'){
		pKekka->kesseiflg		= '0';				// 乳び・溶血チェック
	}
	if(pKekka->rirekiflg == '\0'){
		pKekka->rirekiflg		= '0';				// 履歴チェック
	}
	if(pKekka->syougoflg == '\0'){
		pKekka->syougoflg		= '0';				// 照合チェック
	}
	if(pKekka->keisanflg == '\0'){
		pKekka->keisanflg		= '0';				// 計算チェック
	}
	if(pKekka->per100flg == '\0'){
		pKekka->per100flg		= '0';				// １００％チェック
	}
	if(pKekka->tousekflg == '\0'){
		pKekka->tousekflg		= '0';				// 透析前後チェック
	}
	if(pKekka->kisyakflg == '\0'){
		pKekka->kisyakflg		= '0';				// 希釈再検チェック
	}
	if(pKekka->kouseiflg == '\0'){
		pKekka->kouseiflg		= '0';				// 校正処理
	}
	if(pKekka->syoungflg == '\0'){
		pKekka->syoungflg		= '0';				// 照合NG確定処理
	}
	if(pKekka->soukn2flg == '\0'){
		pKekka->soukn2flg		= '0';				// 相関チェック(WS間)
	}
	if(pKekka->fukaptflg == '\0'){
		pKekka->fukaptflg		= '0';				// 負荷パターンチェック
	}
	if(pKekka->yobiflg01 == '\0'){
		pKekka->yobiflg01		= '1';				//
	}
	if(pKekka->tobiflg02 == '\0'){
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
	/*	pKekka->tobiflg02		= '1';				//*/
		pKekka->tobiflg02		= '0';				// Xbarm再検指示
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
	}
	if(pKekka->yobiflg03 == '\0'){
		pKekka->yobiflg03		= '1';				//
	}
	if(pKekka->yobiflg04 == '\0'){
		pKekka->yobiflg04		= '1';				//
	}
	if(pKekka->yobiflg05 == '\0'){
		pKekka->yobiflg05		= '1';				//
	}
}

/******************************************************************************/
/*	関 数 名  ：chkInfoRead()												  */
/*	機能概要  ：ファイル情報読み出し										  */
/*	入	  力  ：															  */
/*	 第１引数 ：モード	: 0:即時チェックファイル/ 1:オーダーファイル		  */
/*	 第２引数 ：kmkcd	:	項目コード										  */
/*	 第３引数 ：fName	:	ファイル名										  */
/*	出	  力  ：Data	:	情報（指定項目コード）							  */
/*			  ：buff	:	出力用バッファ									  */
/*	復帰情報  ：int															  */
/*					0:正常													  */
/*					1:異常(項目コード無し)									  */
/*					2:異常（その他）										  */
/******************************************************************************/
int chkInfoRead(int mode, char * kmkcd,char * fName, char **Data, char *buff)
{
	FILE * fp;

	char		** pFld;
	int			cnt;
	int			offset;
	int			ret = 1;
	int			hitFlg = 0;

	char		fPath[256];
#ifdef _DEBUG_
	char		cMsgBuf[512];
#endif

#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : オーダー情報ファイル読み込み\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : オーダー情報ファイル読み込み\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
	strncpy(fPath, GetFolder, 256);
	if (mode == 1) {
		strcat(fPath, "local/");
	}
	strncat(fPath, fName, 256);
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : fPath = [%s]\n", __LINE__, fPath);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : fPath = [%s]\n", __LINE__, fPath);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	fp = fopen(fPath, "r");
	if (fp == NULL) {
		// ローカルから取得できないときは2番目のパスを探す。
		strncpy(fPath, GetFolder2, 256);
		strncat(fPath, fName, 256);

		fp = fopen(fPath, "r");
		if (fp == NULL) {
			return 2;
		}
	}

	pFld = malloc(sizeof(char *)*200);
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : pFld = malloc\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : pFld = malloc\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
	while (fgets(buff, READ_BUFF_SIZE, fp)) {
		// カンマ区切りのレコードを分割し、
		hitFlg = 0;
		cnt = 0;
		offset = 0;;
		pFld[cnt] = &buff[cnt];
		cnt++;
		while (buff[offset] != '\0') {
			if (buff[offset] == ',') {
				pFld[cnt] = &buff[offset+1];
				buff[offset] = '\0';
				if (cnt == 5) {
					if (strncmp(kmkcd, pFld[5], 7) == 0) {
						hitFlg = 1;
#ifdef _DEBUG_
						printf( "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
						memset(cMsgBuf, 0, sizeof(cMsgBuf));
						sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
						sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
					}
					else {
						break;
					}
				}
				cnt++;
			}
			offset++;
		}
		if (hitFlg == 0) {
			continue;
		}
		if (mode == 0) {
			if (cnt != 59) {
				// CSVフィールド数不正（読み飛ばす）
				continue;
			}
			if (strncmp(kmkcd, pFld[5], 7) == 0) {
				// 指定項目コードを見つけた
				memcpy(Data, pFld, sizeof(char *) * 118);
#ifdef _DEBUG_
				printf( "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5] = [%s]\n", __LINE__, pFld[5]);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
				printf( "chkInfoRead(%d) : Data = [%s]\n", __LINE__, Data);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : Data = [%s]\n", __LINE__, Data);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				ret = 0;
				break;
			}
		}
		else {
			if (cnt != 58) {
				// CSVフィールド数不正（読み飛ばす）
				continue;
			}
			if (strncmp(kmkcd, pFld[5], 7) == 0) {
#ifdef _DEBUG_
				printf( "chkInfoRead(%d) : pFld[5]前\n", __LINE__);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5]前\n", __LINE__);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				// 指定項目コードを見つけた
				memcpy(Data, pFld, sizeof(char *) * 118);
#ifdef _DEBUG_
				printf( "chkInfoRead(%d) : pFld[5]後\n", __LINE__);
				memset(cMsgBuf, 0, sizeof(cMsgBuf));
				sprintf(cMsgBuf, "chkInfoRead(%d) : pFld[5]後\n", __LINE__);
				sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif
				ret = 0;
				break;
			}
		}
	}
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : free(pFld)前\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : free(pFld)前\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	free(pFld);
#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : free(pFld)後\n", __LINE__);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : free(pFld)後\n", __LINE__);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	fclose(fp);

#ifdef _DEBUG_
	printf( "chkInfoRead(%d) : ret = [%d]\n", __LINE__, ret);
	memset(cMsgBuf, 0, sizeof(cMsgBuf));
	sprintf(cMsgBuf, "chkInfoRead(%d) : ret = [%d]\n", __LINE__, ret);
	sFncSyslog ( LOG_ERR, "", cMsgBuf ) ;
#endif

	return (ret);
}

/******************************************************************************/
/*	関 数 名  ：KekkaMarume()												  */
/*	機能概要  ：RAWDATAの丸め処理を行い、表示結果に格納する。				  */
/*	入	  力  ：															  */
/*	 第１引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第２引数 ：KekkaCnt:	結果情報構造体数								  */
/*	出	  力  ：pKekka	:	結果情報構造体配列								  */
/*	復帰情報  ：int															  */
/*					0:正常													  */
/*					1:異常（その他）										  */
/******************************************************************************/
int KekkaMarume(Kekka * pKekka, int KekkaCnt, char * ReadFileName)
{
	int		lCnt;
	char	*pBuff;
	char	**pFld;
	int		ret2;
	int		ketasuu;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	pFld = malloc(sizeof(char *)*200);
	pBuff = malloc(sizeof(char) * READ_BUFF_SIZE);

	for (lCnt = 0; lCnt < KekkaCnt; lCnt ++){
		// 即時チェック情報ファイル読み込み
		ret2 = chkInfoRead(0, pKekka[lCnt].kmkcd, ReadFileName, pFld, pBuff);
		if ( ret2 != 0 ) {
			// 即時チェック情報なし
			ketasuu = 9;
		}
		else {
			ketasuu = atoi(pFld[57]);
		}

		// 丸め処理

		if (ketasuu == 9) {
			strncpy(pKekka[lCnt].hjkka, pKekka[lCnt].rawdata, 20);
		}
		else {
			double		rawData;
			rawData = atof(pKekka[lCnt].rawdata) + 0.00001;
			sprintf(pKekka[lCnt].hjkka, "%.*f", ketasuu, rawData);
		}
	}
	free(pFld);
	free(pBuff);

	return 0;
}
/******************************************************************************/
/*	関 数 名  ：RenjiChk()													  */
/*	機能概要  ：レンジチェック												  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第３引数 ：lCnt	:	処理中位置										  */
/*	 第３引数 ：ODFld	:	オーダー情報									  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/******************************************************************************/
int	RenjiChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta)
{
	int			ret = 0;
	double		rawData;
	double		rawData2;
	double		hiData;
	double		loData;
//	int			iCnt;
	int			lpCnt;
	char		tmp[32];
//	char		tmp2[32];
//	char		*chk;
	struct stRNGCHKMST {
		char	HNIKBN; 				//範囲区分
		char	KNSGRP[16]; 			//検査グループ
		char	KMKCD[7];				//項目コード
		char	ZAICD[4];				//材料コード
		char	KRKNSGRP[7];			//施設コード
		char	SBT;					//性別
		char	SSA;					//上下限区分
		char	ZEN_KYOYOU;				//許容区分
		char	HRNG[20];				//レンジ上限
		char	LRNG [20];				//レンジ下限
		char	KAIYMD[8];				//開始年月日
		char	HAIYMD[8];				//廃止年月日
		char	HNKTNTID[8];			//変更担当ID
		char	KSNDH[12];				//情報更新日時
	} *pRNGCHKMST;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
#ifdef _DEBUG_
	printf("レンジチェック");
#endif

	if (pKekka[lCnt].renjicflg == '1' || pKekka[lCnt].renjicflg == '2') {
		// 既にチェック済みの時は処理しない
		return 0;
	}

	// レンジマスタの情報
	pRNGCHKMST = (struct stRNGCHKMST *)chkPara;

/*
	memset(tmp, 0, sizeof(tmp));
	strncpy(tmp, pKekka[lCnt].rawdata, 20);
	rawData = atof(tmp);
*/
	memset(tmp, 0, sizeof(tmp));
	strncpy(tmp, pKekka[lCnt].hjkka, 20);
	rawData = atof(tmp);
	//rawData +=  0.00001;
	sprintf(tmp, "%.*f", keta, rawData);
	rawData2 = atof(tmp);

	ret = 0;

	for (lpCnt = 0; lpCnt < (strlen(chkPara) / sizeof(struct stRNGCHKMST)); lpCnt++, pRNGCHKMST++) {
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pRNGCHKMST->HRNG, 20);
		hiData = atof(tmp);

		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pRNGCHKMST->LRNG, 20);
		loData = atof(tmp);

/*		// レンジマスタの値から丸め桁数を求める。
		memset(tmp, 0, sizeof(tmp));
		if (pRNGCHKMST->SSA == '1') {
			// 高値側の時
			memset(tmp2, 0, sizeof(tmp2));
			strncpy(tmp2, pRNGCHKMST->HRNG, 20);
			trim(tmp, tmp2);
		}
		else {
			// 低値側のとき
			memset(tmp2, 0, sizeof(tmp2));
			strncpy(tmp2, pRNGCHKMST->LRNG, 20);
			trim(tmp, tmp2);
		}
		// 小数点桁数を求める
		iCnt = 0;
		if ((chk = strchr(tmp, '.')) != (char *)NULL) {
			iCnt = strlen(chk + 1);
		}
		// 丸め処理
		// 追加 osada
		rawData +=  0.00001;

		sprintf(tmp, "%.*f", iCnt, rawData);
		rawData2 = atof(tmp);
*/
		// レンジチェック時は測定値が範囲内かチェックする。
		if ((hiData < rawData2) || (rawData2 < loData)) {
#ifdef _DEBUG_
			printf(" (raw = %f, raw2 = %f, hi = %f, lo = %f)", rawData, rawData2, hiData, loData); 
#endif
			ret = 1;
			break;
		}
	}
//	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pRNGCHKMST->ZEN_KYOYOU, 4);
//	switch (atoi(tmp)) {
//	case 1:		// 比(%)
//		if ((hiData < rawData) || (rawData < loData)) {
//			ret = 1;
//		}
//		break;
//	case 2:		// 差(絶対)
//		if ((hiData < rawData) || (rawData < loData)) {
//			ret = 1;
//		}
//		break;
//	default:
//		ret = 0;
//		break;
//	}

	if (ret != 0) {
		if (pRNGCHKMST->SSA == '1') {
			pKekka[lCnt].renjicflg = '3';
		}
		else {
			pKekka[lCnt].renjicflg = '4';
		}
#ifdef _DEBUG_
		printf("NG\n");
#endif
	}
	else {
		pKekka[lCnt].renjicflg = '1';
#ifdef _DEBUG_
		printf("OK\n");
#endif
	}
	return ret;
}

/******************************************************************************/
/*	関 数 名  ：SoukanChk()													  */
/*	機能概要  ：相関チェック(WS内)											  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第３引数 ：lCnt	:	処理中位置										  */
/*	 第３引数 ：ODFld	:	オーダー情報									  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/******************************************************************************/
int	SoukanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, int keta)
{
	int			ret = 0;
	char		calBuff[256];
/*	struct stSKCHKMST {
		char	KNSGRP[16];			//検査グループ
		char	KMKCD[7];           //項目コード
		char	SSTCD[7];           //施設コード
		char	ZAIKBN[4];          //材料区分(調整)
		char	KRKNSGRP[4];        //不等号
		char	SOUKAN[128];        //相関式
		char	KAIYMD[8];          //開始年月日
		char	HAIYMD[8];          //廃止年月日
		char	HNKTNTID[8];		//変更担当ID
		char	KSNDH[12];          //情報更新日時
	} sSKCHKMST, *pSKCHKMST;
*/	struct stSKCHKMST {
		int		KRKNSGRP;           //不等号
		char	SOUKAN[128];        //相関式
	} sSKCHKMST;
	int			iCnt;	// ループカウンタ
	int			paraCnt;
	int			i;
	int			setCnt;
	int			tmpCnt;
	char		tmp[32];
	double		calNum;
	double		rawData;

#ifdef _DEBUG_
	printf("SoukanChk(%d)\n", __LINE__);
#endif

	/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/

	char *pszExpandKSNSK = (char *) NULL;
										/* IF 文展開後の計算式              */
	double dTransferLimit;

	/*----<< End add source Feb 27, 2008 H.Sato >>----*/

	if (pKekka[lCnt].soukn1flg == '1' || pKekka[lCnt].soukn1flg == '2') {
		// 既にチェック済みの時は処理しない
		return 0;
	}

	paraCnt = 0;
	while (paraCnt < strlen(chkPara)) {
		memset(&sSKCHKMST, 0, sizeof(sSKCHKMST));
		memset(tmp, 0, sizeof(tmp));
		memcpy(tmp, &chkPara[paraCnt], 4);
		sSKCHKMST.KRKNSGRP = atoi(tmp);
		paraCnt += 4;
		for (i = paraCnt + 1; i < 50; i++ ) if (chkPara[i] == '!') break;
		memcpy(sSKCHKMST.SOUKAN, &chkPara[paraCnt+1], i-paraCnt-1);
		paraCnt += (i-paraCnt+1);

		// 結果値の値文字列を数値化する
/*		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
		rawData = atof(tmp);
*/		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].hjkka, 20);
		rawData = atof(tmp);

		// 式中の項目コードを数値に置き換える。
		memset(calBuff, 0, sizeof(calBuff));
		for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
			// 項目コードの始まり'['を検索する。
			if (sSKCHKMST.SOUKAN[iCnt] == '[') {
				// 項目値を検索
				memset(tmp, 0, sizeof(tmp));
				tmpCnt = 0;
				iCnt++;
				// 項目コードを転送（終了位置の]かNullまで）
				while (sSKCHKMST.SOUKAN[iCnt] != ']' && sSKCHKMST.SOUKAN[iCnt] != '\0') {
					tmp[tmpCnt++] = sSKCHKMST.SOUKAN[iCnt++];
				}
				// 結果情報から指定の項目コードを検索し、置き換える。
				for (tmpCnt = 0; tmpCnt < KekkaCnt; tmpCnt++) {
					if (strncmp(pKekka[tmpCnt].kmkcd, tmp, strlen(tmp)) == 0) {
//						strncat(calBuff, pKekka[tmpCnt].rawdata, 21);
						strncat(calBuff, pKekka[tmpCnt].hjkka, 20);
						setCnt = strlen(calBuff);
						break;
					}
				}
				if (tmpCnt == KekkaCnt) {
					// 関連項目が見つからない。
//					pKekka[lCnt].soukn1flg = '1';
					break;
				}
			}
			else if (KSNSK_SC == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// 身長

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

				//strncat(calBuff, ODFld[40], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_SC], FLDSIZE_SC);
				gszTransfer[FLDSIZE_SC] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TJ == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// POWと区別するため、前の文字がOで無いかチェックする。
				if (0 < iCnt &&
				    (sSKCHKMST.SOUKAN[iCnt-1] == 'o' ||
				     sSKCHKMST.SOUKAN[iCnt-1] == 'O')) {
					break;
				}
				else {
					// 体重

					/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
					// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

					//if (ODFld[41][0] == '0') {
					//	// 体重がKgの時はグラムで計算
					//	memset(tmp, 0, sizeof(tmp));
					//	strncpy(tmp, ODFld[41], 5);
					//	sprintf(tmp,"%-lf",(atof(tmp)*1000));
					//	strcat(calBuff, tmp);
					//}
					//else {
					//	strncat(calBuff, ODFld[41], 5);
					//}

					strncpy(gszTransfer, ODFld[FLDIDX_TJ], FLDSIZE_TJ);
					gszTransfer[FLDSIZE_TJ] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					else {
						switch ((int) ODFld[FLDIDX_TJTNI][0]) {
						case _VALUE_TJTNI_KILLOGRAM:
							dTransferLimit = 
									atof(gszTransfer) * (double) 1000.0;
							if ((double) 0.0 < dTransferLimit) {
								sprintf(gszTransfer, "%f", dTransferLimit);
							}
							else {
								gszTransfer[0] = (char) '0';
								gszTransfer[1] = (char) '\0';
							}

						case _VALUE_TJTNI_GRAM:
							break;		/* NOP                              */

						default:
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					}
					strcat(calBuff, gszTransfer);

					/*---<< End modified source May 27, 2008 H.Sato >>---*/

					setCnt = strlen(calBuff);
				}
			}
			else if (KSNSK_TNTME == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// 蓄尿時間

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

				//strncat(calBuff, ODFld[50], 4);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNTME], FLDSIZE_TNTME);
				gszTransfer[FLDSIZE_TNTME] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNTNI][0]) {
					/* 2014/02/06 sekiya 時間単位以外の場合は計算しないように仕様変更
					case _VALUE_TNTNI_MINUTE:
						sprintf(gszTransfer,
						        "%-lf",
						        (atof(gszTransfer) / (double) 60.0));
						gszTransfer[FLDSIZE_TNTME] = (char) '\0';
					*/
					case _VALUE_TNTNI_HOUR:
						break;			/* NOP                             */

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TNRYO == (int) sSKCHKMST.SOUKAN[iCnt]) {
				// 蓄尿量

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

				//strncat(calBuff, ODFld[52], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNRYO], FLDSIZE_TNRYO);
				gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNRYOTNI][0]) {
					/* 2014/02/06 sekiya ミリリットル単位以外の場合は計算しないように仕様変更
					case _VALUE_TNRYO_LITER:
						dTransferLimit = atof(gszTransfer) * (double) 1000.0;
						if ((double) 0.0 < dTransferLimit) {
							sprintf(gszTransfer, "%-lf", dTransferLimit);
						}
						else {
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					*/
					case _VALUE_TNRYO_MILLILITER:
						break;

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}

			/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
			/* 計算式拡張対応                                               */

			else if (KSNSK_SBTKBN == sSKCHKMST.SOUKAN[iCnt]) {
				/* 性別区分                                                 */
				if (_VALUE_SBTKBN_MALE == (int) ODFld[FLDIDX_SBTKBN][0] ||
						_VALUE_SBTKBN_FEMALE == (int) ODFld[FLDIDX_SBTKBN][0]) {
					calBuff[setCnt++] = ODFld[FLDIDX_SBTKBN][0];
					calBuff[setCnt] = (char) '\0';
				}
				else {
					calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
					calBuff[setCnt] = (char) '\0';
										/* 展開不可							*/
				}
			}
			else if (KSNSK_AGE == sSKCHKMST.SOUKAN[iCnt]) {
				/* 年齢                                                     */
				if (_VALUE_AGEKBN_YEAR != (int) ODFld[FLDIDX_AGEKBN][0]) {
					calBuff[setCnt++] = (char) '0';
					calBuff[setCnt] = (char) '\0';
										/* 展開不可							*/
				}
				else {
					memcpy((void *) gszTransfer, ODFld[FLDIDX_AGE], FLDSIZE_AGE);
					gszTransfer[FLDSIZE_AGE] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					strcat(calBuff, gszTransfer);
					setCnt = strlen(calBuff);
				}
			}

			/*----<< End add source Feb 27, 2008 H.Sato >>----*/

			else if (sSKCHKMST.SOUKAN[iCnt] == '\0') {
				break;
			}
			else {
				calBuff[setCnt++] = sSKCHKMST.SOUKAN[iCnt];
			}
		}
		// CHG 2006/08/03 E.Osada 相関相手の結果がスペースの場合、計算しない
		if (tmpCnt == KekkaCnt) {
			// 関連項目が見つからない。
			break;
		}

		/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
		/* 計算式に含まれる IF 文の展開                                     */
#ifdef _DEBUG_
		printf("SoukanChk(%d) : calBuff =【%s】\n", __LINE__, calBuff);
		printf("SoukanChk(%d) : pKekka[lCnt].kmkcd =【%s】\n", __LINE__, pKekka[lCnt].kmkcd);
#endif
		if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
			if ('\0' != (int) *pszExpandKSNSK) {
				strcpy(calBuff, pszExpandKSNSK);
			}
			free((void *) pszExpandKSNSK);
			pszExpandKSNSK = (char *) NULL;
		}

		/*----<< End add source Feb 27, 2008 H.Sato >>----*/

		// 文字列の計算式を計算する。
		calNum = StringCal(calBuff);
#ifdef _DEBUG_
		printf("SoukanChk(%d) : calNum =【%.9f】\n", __LINE__, calNum);
#endif

		// 計算結果を丸める
		if (keta != 9) {
			sprintf(tmp, "%.*f", keta, calNum);
			calNum = atof(tmp);
		}
		// 不等号の設定に従い、値を判定する。
		switch (sSKCHKMST.KRKNSGRP) {
		case 0:	// =
			if (rawData == calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 1:	// !=
			if (rawData != calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 2:	// >=
			if (rawData >= calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 3:	// <=
			if (rawData <= calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 4:	// >
			if (rawData > calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		case 5:	// <
			if (rawData < calNum) {
				ret = 0;
			} else {
				ret = 1;
			}
			break;
		}
//		if (ret == 1) {
//			break;
//		}
	}

	// CHG E.Osada 2006-07-23
	//if (ret == 1) {
	//if( (ret == 1) || (ret == 0) ) {
	if ( ret == 0 ) {
		pKekka[lCnt].soukn1flg = '1';
		//ret = 0;
	}
	else {
		pKekka[lCnt].soukn1flg = '2';
		//ret = 1;
	}

	return ret;
}
/******************************************************************************/
/*	関 数 名  ：KanrenChk()													  */
/*	機能概要  ：関連チェック												  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第３引数 ：lCnt	:	処理中位置										  */
/*	 第３引数 ：ODFld	:	オーダー情報									  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/******************************************************************************/
int	KanrenChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, SaikenInfo * fSaiken)
{
	int			ret = 0;
//	struct stKRKMKMST {
////		char	KNSGRP[16];		// 検査グループ
//		char	KMKCD[7];		// 項目コード
////		char	KRKNSGRP[4];	// 関連検査グループ
//		char	KRKMKCD[7]; 	// 関連項目コード
//		char	KAIYMD[8];		// 開始年月日
//		char	HAIYMD[8];		// 廃止年月日
//		char	HNKTNTID[8];	//変更担当ID
//		char	KSNDH[12];		// 情報更新日時
//	} *pKRKMKMST;
	int			iCnt;	// ループカウンタ
	char		*kmkcd;
	int			paraCnt;
//	int	iHit;	// ADD E.Osada 2006-07-21
//	char	cFlg;	// ADD E.Osada 2006-07-21

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	if (pKekka[lCnt].kanrenflg == '1' || pKekka[lCnt].kanrenflg == '2') {
		// 既にチェック済みの時は処理しない
		return 1;
	}

//	pKRKMKMST = (struct stKRKMKMST *)chkPara;
	kmkcd = chkPara;

//	memset(kmkcd, 0, sizeof(kmkcd));
//	strncpy(kmkcd, pKRKMKMST->KRKMKCD, 7);

	if (pKekka[lCnt].renjicflg < '2' &&
		pKekka[lCnt].soukn1flg < '2' &&
		pKekka[lCnt].kesseiflg < '2' &&
		pKekka[lCnt].rirekiflg < '2' &&
		pKekka[lCnt].syougoflg < '2' &&
		pKekka[lCnt].keisanflg < '2' &&
		pKekka[lCnt].per100flg < '2' &&
		pKekka[lCnt].tousekflg < '2' &&
		pKekka[lCnt].kisyakflg < '2' &&
		pKekka[lCnt].kouseiflg < '2' &&
		pKekka[lCnt].syoungflg < '2' &&
		pKekka[lCnt].soukn2flg < '2' &&
		pKekka[lCnt].fukaptflg < '2' &&
		// DEL E.Osada 2006-08-21 ブランク結果に '連' が付いてしまう対応
		//pKekka[lCnt].yobiflg01 < '2' &&
		pKekka[lCnt].tobiflg02 < '2' &&
		pKekka[lCnt].yobiflg03 < '2' &&
		pKekka[lCnt].yobiflg04 < '2' &&
		pKekka[lCnt].yobiflg05 < '2') {
		// 自分が正常のときは、何もしない
		return 0;
	}

//	iHit = 0;	//ADD E.Osada 2006-07-21
	//CHG E.Osada 2006-08-06 E.Osada
	//for (paraCnt = 0; kmkcd[paraCnt*50] != 0; paraCnt++ ) [
	//	if( !memcmp(&kmkcd[paraCnt*50], "       ", 7) ) break;
	for (paraCnt = 0; kmkcd[paraCnt*7] != 0; paraCnt++ ) {
		if( !memcmp(&kmkcd[paraCnt*7], "       ", 7) ) break;
	//
		for (iCnt = 0; iCnt < KekkaCnt; iCnt++) {
			if (iCnt == lCnt) {
				continue;
			}

			//CHG E.Osada 2006-08-06 E.Osada
			//if(  strncmp(pKekka[iCnt].kmkcd, &kmkcd[(paraCnt*50)+7], 7) == 0 ) [
			if(  strncmp(pKekka[iCnt].kmkcd, &kmkcd[paraCnt*7], 7) == 0 ) {
				ret = 1;
				pKekka[iCnt].kanrenflg = '2';

//CHG E.Osada 2006-08-07
#if 0
				if( (pKekka[lCnt].knsflg == 'R') && (pKekka[iCnt].knsflg != 'R') ) {
					pKekka[iCnt].knsflg = 'R';
					// 検査フラグが再検「Ｒ」の場合、自動再検を行わない
					//		２：用手再検
					fSaiken[iCnt].flg = 2;
					ret = 2;
				}
				else {
					// 検査フラグが再検「Ｒ」でなければ自動再検を行う
					//		１：自動再検
					fSaiken[iCnt].flg = 1;
					// 2006/08/06 nagata
					// 検査フラグで自動再検オーダ有無を
					// 切り分けるようにしたため、
					// この部分に相手を'A'にする行為が必要となる。
					pKekka[iCnt].knsflg = 'A';
				}

				iHit = 1; //ADD E.Osada 2006-07-21
				//もしそいつが関連エラーの場合は自分も関連エラーとなる。
				if( pKekka[iCnt].kanrenflg == '2' ) {
					pKekka[lCnt].kanrenflg = '2';
					if( pKekka[iCnt].knsflg == 'R' ) {
						pKekka[lCnt].knsflg = 'R';
					//ret = 1;
					// 検査フラグが再検「Ｒ」の場合、自動再検を行わない
					//		２：用手再検
						ret = 2;
					}
				}
#endif
                ret = 1;
                pKekka[iCnt].kanrenflg = '2';
                pKekka[lCnt].kanrenflg = '2';
//DEL E.Osada 2006-08-21
//自分が用手希釈の場合は相手を'A'にする
                if( pKekka[lCnt].knsflg == 'R' ) {
					if( pKekka[lCnt].kisyakflg == '2' ) {
						//CHG Nagata 2006-09-27 自分が用手再検の時、
						//		相手が"R"だったら、相手に対して何もしない。
                    	if(pKekka[iCnt].knsflg != 'R'){
                        	pKekka[iCnt].knsflg = 'A';
                        	fSaiken[iCnt].flg = 1;
                        	ret = 1;
						}
					} else {
                    	pKekka[iCnt].knsflg = 'R';
                    	fSaiken[iCnt].flg = 2;
                    	ret = 2;
					}
                }
                if(pKekka[lCnt].knsflg == 'A'){
                    if(pKekka[iCnt].knsflg != 'R'){
                        pKekka[iCnt].knsflg = 'A';
                        fSaiken[iCnt].flg = 1;
                        ret = 1;
                    }
                }
			}
		}
	}
#if 0
	//一人「連」封じ
	//もし自分がNGでも他関連項目が存在しなかった場合は関連フラグを落とす
	if( !iHit ) ret = 0;
#endif

	return ret;
}
/******************************************************************************/
/*	関 数 名  ：BungaChk()													  */
/*	機能概要  ：分画チェック												  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第３引数 ：lCnt	:	処理中位置										  */
/*	 第３引数 ：ODFld	:	オーダー情報									  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/******************************************************************************/
int	BungaChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld,SaikenInfo * fSaiken)
{
	int			ret = 0;
	int			ret2;
	int			iCnt;	// ループカウンタ
	char		*pBuffOD;
	char		**pFldOD;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	if (pKekka[lCnt].bunkkuflg == '1' || pKekka[lCnt].bunkkuflg == '2') {
		// 既にチェック済みの時は処理しない
		return 0;
	}

	pFldOD = malloc(sizeof(char *)*200);
	pBuffOD = malloc(sizeof(char) * READ_BUFF_SIZE);

	if (ODFld[22][0] != '2') {
		// 分画子でないとき
		free(pFldOD);
		free(pBuffOD);
		pKekka[lCnt].bunkkuflg = '1';
		return 0;
	}

	if (pKekka[lCnt].renjicflg >= '2' ||
		pKekka[lCnt].soukn1flg == '2' ||
		pKekka[lCnt].kesseiflg == '2' ||
		pKekka[lCnt].rirekiflg == '2' ||
		pKekka[lCnt].syougoflg == '2' ||
		pKekka[lCnt].keisanflg == '2' ||
		pKekka[lCnt].per100flg == '2' ||
		pKekka[lCnt].tousekflg == '2' ||
		pKekka[lCnt].kisyakflg == '2' ||
		pKekka[lCnt].kouseiflg == '2' ||
		pKekka[lCnt].syoungflg == '2' ||
		pKekka[lCnt].soukn2flg == '2' ||
		pKekka[lCnt].fukaptflg == '2' ||
		pKekka[lCnt].yobiflg01 == '2' ||
		pKekka[lCnt].tobiflg02 == '2' ||
		pKekka[lCnt].yobiflg03 == '2' ||
		pKekka[lCnt].yobiflg04 == '2' ||
		pKekka[lCnt].yobiflg05 == '2') {
//		cFlg = 1;
	}
	else {
		// エラーでないとき
		free(pFldOD);
		free(pBuffOD);
		pKekka[lCnt].bunkkuflg = '1';
		return 0;
	}

	for (iCnt = 0; iCnt < KekkaCnt; iCnt++) {
//		if (iCnt == lCnt) {
//			continue;
//		}
		ret2 = chkInfoRead(1, pKekka[iCnt].kmkcd, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			// オーダー情報なし
			continue;
		}
		if (pFldOD[22][0] == '2') {
			// 分画子
			if (strncmp(ODFld[20],pFldOD[20],7) == 0) {
				// 親コードが同じとき
				fSaiken[iCnt].flg = 1;
				ret = 1;
				pKekka[iCnt].bunkkuflg = '2';
				if (pKekka[iCnt].knsflg != 'R') {
					pKekka[iCnt].knsflg = 'A';
				}
//				break;
			}
		}
	}

	if (ret != 0) {
		pKekka[lCnt].bunkkuflg = '2';
	}
	else {
		pKekka[lCnt].bunkkuflg = '1';
	}

	free(pFldOD);
	free(pBuffOD);

	return ret;
}
/******************************************************************************/
/*	関 数 名  ：NyubiYoketuChk()											  */
/*	機能概要  ：乳び・溶血チェック											  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第４引数 ：lCnt	:	処理中位置										  */
/*	 第５引数 ：fNyuYou	:	乳び・溶血フラグ								  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/******************************************************************************/
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 血清チェック・再検対応                           ***/
/*** 修正版関数を下に作成し、ここからコメントアウトする---↓ ***/
#if 0

int	NyubiYoketuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou)
{
	int			ret = 0;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	if (pKekka[lCnt].kesseiflg == '1' || pKekka[lCnt].kesseiflg == '2') {
		// 既にチェック済みの時は処理しない
		return 0;
	}

	if (fNyuYou == 0) {
		// 乳び・溶血出ないときは処理しない
		return 0;
	}

	if (chkPara[1] == '1') {
		switch (chkPara[0]) {
		case '0':
			break;
		case '1':	// 乳びのみ
			if (fNyuYou & 1) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 乳び溶血の場合
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			//
			break;
		case '2':	// 溶血のみ
			if (fNyuYou & 2) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 乳び溶血の場合
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//
			break;
		case '3':	// 乳び優先
			if (fNyuYou & 1) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			else if (fNyuYou & 2) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 乳び溶血の場合
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				strncpy( pKekka[lCnt].kkacmt2, YoketsuCM, 5);
				ret = 1;
			}
			//
			break;
		case '4':	// 溶血優先
			if (fNyuYou & 2) {
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			else if (fNyuYou & 1) {
				strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				ret = 1;
			}
			//ADD E.Osada 2006-07-21 乳び溶血の場合
			if( (fNyuYou & 1) && (fNyuYou & 2) ) {
				strncpy( pKekka[lCnt].kkacmt2, NyubiCM, 5);
				strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				ret = 1;
			}
			//
			break;
		}
	}
	ret = 0;		// 乳び溶血では再検を行わないので、0を設定 2006.06.15
	if (ret != 0) {
		pKekka[lCnt].kesseiflg = '2';
	}
	else {
		pKekka[lCnt].kesseiflg = '1';
	}
	return ret;
}
#endif
/*** 修正版関数を下に作成し、ここまでコメントアウトする---↑ ***/
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */

/******************************************************************************/
/*	関 数 名  ：NyubiYoketu()												  */
/*	機能概要  ：乳び・溶血存在チェック										  */
/*	入	  力  ：															  */
/*	 第１引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第２引数 ：KekkaCnt:	結果情報構造体数								  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:乳び・溶血無し										  */
/*					1:乳びあり												  */
/*					2:溶血あり												  */
/*					3:乳び・溶血あり										  */
/******************************************************************************/
void trim(char * dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0;
		src[srcCnt] != '\0';
		srcCnt ++) {
		if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
			continue;
		}
		dst[dstCnt++] = src[srcCnt];
		if (src[srcCnt] != '\x20') {
			Flg = dstCnt;
		}
	}
	dst[Flg] = '\0';
}
int	NyubiYoketu( Kekka * pKekka, int KekkaCnt)
{
	int			ret = 0;
//	double		rawData;
	char		tmp[22];
	int			lCnt;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	ret = 0;
	for (lCnt = 0; lCnt < KekkaCnt; lCnt++ ) {
		// 結果値の値文字列を数値化する
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
//		rawData = atof(tmp);

		// 乳びチェック
		if (strncmp( pKekka[lCnt].kmkcd , NyubiCD, 7) == 0 ) {
//			strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
			printf("乳びデータあり\n");
			ret |= 0x10;
			memset( NyubiKekka, 0, sizeof(NyubiKekka));
			trim( NyubiKekka, pKekka[lCnt].rawdata );
			memset( NyubiSTS, 0, sizeof(NyubiSTS));
			strncpy( NyubiSTS, pKekka[lCnt].bskerrsts, 2);
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 血清でも再検を行うため処理を削除 ***/
			/* pKekka[lCnt].knsflg = 'H';*/
			/* if ( rawData > atof(NyubiCHK) ) { */
			/* 	ret |= 0x01;*/
			/* }*/
			ret |= 0x01; // upd 20070623 waj
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
		}
		// 溶血チェック
		else if (strncmp( pKekka[lCnt].kmkcd , YoketsuCD, 7) == 0 ) {
//			strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
			printf("溶血データあり\n");
			ret |= 0x20;
			memset( YoketsuKekka, 0, sizeof(YoketsuKekka));
			trim( YoketsuKekka, pKekka[lCnt].rawdata );
			memset( YoketsuSTS, 0, sizeof(YoketsuSTS));
			strncpy( YoketsuSTS, pKekka[lCnt].bskerrsts, 2);
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 血清でも再検を行うため処理を削除 ***/
			/* pKekka[lCnt].knsflg = 'H';*/
			/* if ( rawData > atof(YoketsuCHK) ) {*/
			/* 	ret |= 0x02;*/
			/* }*/
			ret |= 0x02; // upd 20070623 waj
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
		}
		// 黄だんチェック
		else if (strncmp( pKekka[lCnt].kmkcd , OudanCD, 7) == 0 ) {
//			strncpy( pKekka[lCnt].kkacmt1, OudanCM, 5);
			printf("黄だんデータあり\n");
			ret |= 0x40;
			memset( OudanKekka, 0, sizeof(OudanKekka));
			trim( OudanKekka, pKekka[lCnt].rawdata );
			memset( OudanSTS, 0, sizeof(OudanSTS));
			strncpy( OudanSTS, pKekka[lCnt].bskerrsts, 2);
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 血清でも再検を行うため処理を削除 ***/
		/*	pKekka[lCnt].knsflg = 'H';*/
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
		}
	}
	return ret;
}
/******************************************************************************/
/*	関 数 名  ：KeisanChk()													  */
/*	機能概要  ：計算チェック(WS内)											  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第３引数 ：lCnt	:	処理中位置										  */
/*	 第３引数 ：ODFld	:	オーダー情報									  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/******************************************************************************/
int	KeisanChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char **ODFld, STKEISANCHK * calbuf)
{
	int			ret = 0;
	int			ret2;
	char		calBuff[256];
	struct stKEISANCHK {
		char	KMKCD[7+1];	   // 項目コード
		char	KSNSK[128];	   // 計算式
	} sKEISANCHK;
	int			iCnt;	// ループカウンタ
	int			paraCnt;
	int			i;
	int			setCnt;
	int			tmpCnt;
	char		tmp[32];
	double		calNum;
//	double		rawData;
	char		*pBuffOD;
	char		**pFldOD;
	char		*pBuffRealchk ;
	char		**pFldRealchk;
	int			li_Keta ;
	char		lc_RawBuf[256] ;
	char		*lcp_RawBuf ;
	MY_FLG		 myFlg_RawNone ;

	/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
	char *pszExpandKSNSK = (char *) NULL;
										/* IF 文展開後の計算式              */
    double dTransferLimit = (double) 0.0;
	/*----<< End add source Feb 27, 2008 H.Sato >>----*/

	if (pKekka[lCnt].keisanflg == '1' || pKekka[lCnt].keisanflg == '2') {
		// 既にチェック済みの時は処理しない
		return 0;
	}

	pFldOD = malloc(sizeof(char *)*200);
	pBuffOD = malloc(sizeof(char) * READ_BUFF_SIZE);

	paraCnt = 0;
	while (paraCnt < strlen(chkPara)) {
		memset(&sKEISANCHK, 0, sizeof(sKEISANCHK));
		memcpy(sKEISANCHK.KMKCD, &chkPara[paraCnt], 7);
		paraCnt += 7;
		for (i = paraCnt + 1; i < strlen(chkPara) ; i++ ) if (chkPara[i] == '!') break;
		memcpy(sKEISANCHK.KSNSK, &chkPara[paraCnt+1], i-paraCnt-1);
		paraCnt += (i-paraCnt+1);
		ret2 = chkInfoRead(1, sKEISANCHK.KMKCD, ReadFileNameOD, pFldOD, pBuffOD);
		if ( ret2 != 0 ) {
			// オーダーに計算項目無し
			continue;
		}

		//--------------------------------------------------------
		// 結果値の値文字列を数値化する
		//	結果値がブランクの場合、計算は行わず、計算項目には
		//	ブランクを設定する
		//--------------------------------------------------------
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
//		rawData = atof(tmp);

		myFlg_RawNone = MY_FLG_OFF ;

		// 式中の項目コードを数値に置き換える。
		memset(calBuff, 0, sizeof(calBuff));
		for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
			// 項目コードの始まり'['を検索する。
			if (sKEISANCHK.KSNSK[iCnt] == '[') {
				// 項目値を検索
				memset(tmp, 0, sizeof(tmp));
				tmpCnt = 0;
				iCnt++;
				// 項目コードを転送（終了位置の]かNullまで）
				while (sKEISANCHK.KSNSK[iCnt] != ']' && sKEISANCHK.KSNSK[iCnt] != '\0') {
					tmp[tmpCnt++] = sKEISANCHK.KSNSK[iCnt++];
				}
				// 結果情報から指定の項目コードを検索し、置き換える。
				for (tmpCnt = 0; tmpCnt < KekkaCnt; tmpCnt++) {
					if (strncmp(pKekka[tmpCnt].kmkcd, tmp, strlen(tmp)) == 0) {
						strcpy ( lc_RawBuf, pKekka[tmpCnt].rawdata ) ;
						lcp_RawBuf = strtok ( lc_RawBuf, " " ) ;
						if ( lcp_RawBuf == NULL || pKekka[tmpCnt].rawdata[0] == '/' ) {
							//	値がブランク場合
							myFlg_RawNone = MY_FLG_ON ;
						}
						else {
							//	値が設定されている場合
							strncat(calBuff, pKekka[tmpCnt].rawdata, 21);
							setCnt = strlen(calBuff);
						}
						break;
					}
				}
				if (tmpCnt == KekkaCnt) {
					// 関連項目が見つからない。
					pKekka[lCnt].keisanflg = '0';
					break;
				}
			}
			else if (KSNSK_SC == (int) sKEISANCHK.KSNSK[iCnt]) {
				// 身長

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

				//strncat(calBuff, ODFld[40], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_SC], FLDSIZE_SC);
				gszTransfer[FLDSIZE_SC] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TJ == (int) sKEISANCHK.KSNSK[iCnt]) {
				// POWと区別するため、前の文字がOで無いかチェックする。
                if (0 < iCnt &&
				    (sKEISANCHK.KSNSK[iCnt - 1] == 'o' ||
				     sKEISANCHK.KSNSK[iCnt - 1] == 'O')) {
                    break;
                }
                else {
					// 体重

					/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
					// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

					//if (ODFld[41][0] == '0') {
					//	// 体重がKgの時はグラムで計算
					//	memset(tmp, 0, sizeof(tmp));
					//	strncpy(tmp, ODFld[41], 5);
					//	sprintf(tmp,"%-lf",(atof(tmp)*1000));
					//	strcat(calBuff, tmp);
					//}
					//else {
					//	strncat(calBuff, ODFld[41], 5);
					//}

					strncpy(gszTransfer, ODFld[FLDIDX_TJ], FLDSIZE_TJ);
					gszTransfer[FLDSIZE_TJ] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					else {
						switch ((int) ODFld[FLDIDX_TJTNI][0]) {
						case _VALUE_TJTNI_KILLOGRAM:
							dTransferLimit = 
									atof(gszTransfer) * (double) 1000.0;
							if ((double) 0.0 < dTransferLimit) {
								sprintf(gszTransfer, "%f", dTransferLimit);
							}
							else {
								gszTransfer[0] = (char) '0';
								gszTransfer[1] = (char) '\0';
							}

						case _VALUE_TJTNI_GRAM:
							break;		/* NOP                              */

						default:
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					}
					strcat(calBuff, gszTransfer);

					/*---<< End modified source May 27, 2008 H.Sato >>---*/

					setCnt = strlen(calBuff);
				}
			}
			else if (KSNSK_TNTME == (int) sKEISANCHK.KSNSK[iCnt]) {
				// 蓄尿時間

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

				//strncat(calBuff, ODFld[50], 4);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNTME], FLDSIZE_TNTME);
				gszTransfer[FLDSIZE_TNTME] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNTNI][0]) {
					/* 2014/02/06 sekiya 時間単位以外の場合は計算しないように仕様変更
					case _VALUE_TNTNI_MINUTE:
						sprintf(gszTransfer,
						        "%-lf",
						        (atof(gszTransfer) / (double) 60.0));
						gszTransfer[FLDSIZE_TNTME] = (char) '\0';
					*/
					case _VALUE_TNTNI_HOUR:
						break;			/* NOP                             */

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}
			else if (KSNSK_TNRYO == (int) sKEISANCHK.KSNSK[iCnt]) {
				// 蓄尿量

				/*---<< Begin modified source May 27, 2008 H.Sato >>---*/
				// 利用可能な値以外が指定されていた場合、値 0 が指定されたものとする

				//strncat(calBuff, ODFld[52], 5);
				//setCnt = strlen(calBuff);

				memcpy((void *) gszTransfer, ODFld[FLDIDX_TNRYO], FLDSIZE_TNRYO);
				gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) ODFld[FLDIDX_TNRYOTNI][0]) {
					/* 2014/02/06 sekiya ミリリットル単位以外の場合は計算しないように仕様変更
					case _VALUE_TNRYO_LITER:
						dTransferLimit = atof(gszTransfer) * (double) 1000.0;
						if ((double) 0.0 < dTransferLimit) {
							sprintf(gszTransfer, "%-lf", dTransferLimit);
						}
						else {
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}
					*/
					case _VALUE_TNRYO_MILLILITER:
						break;

					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);

				/*---<< End modified source May 27, 2008 H.Sato >>---*/

			}

			/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
			/* 計算式拡張対応                                               */

			else if (KSNSK_SBTKBN == (int) sKEISANCHK.KSNSK[iCnt]) {
				/* 性別区分                                                 */
				if (_VALUE_SBTKBN_MALE == (int) ODFld[FLDIDX_SBTKBN][0] ||
						_VALUE_SBTKBN_FEMALE == (int) ODFld[FLDIDX_SBTKBN][0]) {
					calBuff[setCnt++] = ODFld[FLDIDX_SBTKBN][0];
					calBuff[setCnt] = (char) '\0';
				}
				else {
					calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
					calBuff[setCnt] = (char) '\0';
										/* 展開不可							*/
				}
			}
			else if (KSNSK_AGE == (int) sKEISANCHK.KSNSK[iCnt]) {
				/* 年齢                                                     */
				if (_VALUE_AGEKBN_YEAR != (int) ODFld[FLDIDX_AGEKBN][0]) {
					calBuff[setCnt++] = (char) '0';
					calBuff[setCnt] = (char) '\0';
										/* 展開不可							*/
				}
				else {
					memcpy((void *) gszTransfer, ODFld[FLDIDX_AGE], FLDSIZE_AGE);
					gszTransfer[FLDSIZE_AGE] = (char) '\0';
					if (0 == _isnumeric(gszTransfer)) {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
					strcat(calBuff, gszTransfer);
					setCnt = strlen(calBuff);
				}
			}

			/*----<< End add source Feb 27, 2008 H.Sato >>----*/

			else if (sKEISANCHK.KSNSK[iCnt] == '\0') {
				break;
			}
			else {
				calBuff[setCnt++] = sKEISANCHK.KSNSK[iCnt];
			}
		}

		//--------------------------------------------------------
		// 計算項目を配列に退避する
		//	計算元の項目のいずれかがブランクの場合は
		//	結果値フラグを設定し、上位で結果値にブランクを設定する
		//--------------------------------------------------------
		if (iCnt == 128 || iCnt == strlen ( sKEISANCHK.KSNSK ) ) {
			//	桁数取得
			pFldRealchk = malloc(sizeof(char *)*200);
			pBuffRealchk = malloc(sizeof(char) * READ_BUFF_SIZE);
			ret2 = chkInfoRead(0, sKEISANCHK.KMKCD, ReadFileName, pFldRealchk, pBuffRealchk);
			if ( ret2 != 0 ) {
				// オーダーに計算項目無し
				free ( pFldRealchk ) ;
				free ( pBuffRealchk ) ;
				continue;
			}
			li_Keta = atoi(pFldRealchk[57]) ;
			free ( pFldRealchk ) ;
			free ( pBuffRealchk ) ;

			//	項目コード設定
			memcpy(calbuf[ret].motoKMKCD, pKekka[lCnt].kmkcd,8);
			memcpy(calbuf[ret].KMKCD, sKEISANCHK.KMKCD,8);

			/*----<< Begin add source Feb 27, 2008 H.Sato >>----*/
			/* 計算式に含まれる IF 文の展開                                     */
			if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
				if ('\0' != (int) *pszExpandKSNSK) {
					strcpy(calBuff, pszExpandKSNSK);
				}
				free((void *) pszExpandKSNSK);
				pszExpandKSNSK = (char *) NULL;
			}

			/*----<< End add source Feb 27, 2008 H.Sato >>----*/

			// 文字列の計算式を計算する。
			calNum = StringCal(calBuff);
			if (li_Keta != 9) {
				//ADD E.Osada 2006-08-06 丸め処理変更
				//calNum += + 0.00001;
				//sprintf(tmp, "%.*f", li_Keta, calNum);
				sprintf(tmp, "%f", calNum);
				calNum = atof(tmp);
			}
			calbuf[ret].raw = calNum;
			calbuf[ret].flgRawNone = myFlg_RawNone ;
			ret ++;
		}
	}
	pKekka[lCnt].keisanflg = '1';

	free(pFldOD);
	free(pBuffOD);

	return ret;
}
/******************************************************************************/
/*	関 数 名  ：KisyakuChk()												  */
/*	機能概要  ：希釈再検チェック											  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第３引数 ：lCnt	:	処理中位置										  */
/*	 第３引数 ：ODFld	:	オーダー情報									  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/*					2:再検なし・希釈エラー									  */
/******************************************************************************/
int	KisyakuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, char *cKisyak, int keta)
{
	int			ret = 0;
	char		tmp[32];
	double		rawData;
//	double		DataMax;
//	double		DataMin;
	int			lpCnt;
	int			flg;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
//	if (pKekka[lCnt].kisyakflg == '1' || pKekka[lCnt].kisyakflg == '2') {
		// 既にチェック済みの時は処理しない
//		return 0;
//	}

//	pKSKBRMST = (struct stKSKBRMST *)chkPara;

	// 検査結果及び、下限、上限値を文字列から数値に変換
	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pKekka[lCnt].rawdata, 20);
	strncpy(tmp, pKekka[lCnt].hjkka, 20);
	rawData = atof(tmp);

//	分析機から帰ってきた値に対し、掛け率計算を行わない
//DEL	if (strcmp(&(pKekka[lCnt].jisksbr[1]), "0D") != 0) {
//DEL		if (pKekka[lCnt].jisksbr[0] != ' ') {
//DEL			rawData *= atof(&(pKekka[lCnt].jisksbr[1]));
//DEL		}
//DEL	}

//	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pKSKBRMST->KMAX, 20);
//	DataMax = atof(tmp);

//	memset(tmp, 0, sizeof(tmp));
//	strncpy(tmp, pKSKBRMST->KMIN, 20);
//	DataMin = atof(tmp);

	flg = -1;
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 施設コードが該当なしの時は0000000を検索 ***/
	int i;
	for (i = 0; i < 2 && flg < 0; i++) {
		char wrkSST[8];
		memset(wrkSST, 0, sizeof(wrkSST));
		memcpy(wrkSST, (i==0?pKekka[lCnt].sstcd:"0000000"), 7);

	for (lpCnt = 0; lpCnt < gKSKBRMSTnum; lpCnt ++ ){
			if ((strncmp(gpKSKBRMST[lpCnt].BSKKBN, pKekka[lCnt].bskkbn,  4) == 0) &&
				(strncmp(gpKSKBRMST[lpCnt].KNSGRP, pKekka[lCnt].knsgrp, 16) == 0) &&
				(strncmp(gpKSKBRMST[lpCnt].KMKCD,  pKekka[lCnt].kmkcd,   7) == 0) &&
/*** 希釈レンジ施設別対応 施設コードを条件に追加 ***/
				(strncmp(gpKSKBRMST[lpCnt].SSTCD,  wrkSST,               7) == 0)) {
#ifdef _DEBUG_
printf("希釈レンジ施設別対応\n");
				char wwww[20];
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].BSKKBN,4); printf("BSKKBN  %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].KNSGRP,16);printf("KNSGRP  %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].KMKCD,7);  printf("KMKCD   %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,pKekka[lCnt].sstcd,7);       printf("SSTCD.1 %s\n", wwww);
				memset(wwww,0,20); memcpy(wwww,gpKSKBRMST[lpCnt].SSTCD,7);  printf("SSTCD.2 %s\n", wwww);
#endif
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */
				//UPD 2006-09-09 Nagata
				// 比較条件を上限値以下、下限値以上とする
				// if ((gpKSKBRMST[lpCnt].KMIN <= rawData) && (rawData < gpKSKBRMST[lpCnt].KMAX)) {
				if ((gpKSKBRMST[lpCnt].KMIN <= rawData) && (rawData <= gpKSKBRMST[lpCnt].KMAX)) {
					flg = 0; /* これで該当データありを表す */
					ret = 1;
					break;
				}
			}
#if 0		// DEL E.Osada 2006-07-21
		if ((strncmp(gpKSKBRMST[lpCnt].BSKKBN, "YOUS", 4) == 0) &&
			(strncmp(gpKSKBRMST[lpCnt].KNSGRP, pKekka[lCnt].knsgrp, 16) == 0) &&
			(strncmp(gpKSKBRMST[lpCnt].KMKCD, pKekka[lCnt].kmkcd, 7) == 0)) {
			if ((gpKSKBRMST[lpCnt].KMIN <= rawData) && (rawData < gpKSKBRMST[lpCnt].KMAX)) {
				flg = lpCnt;
			}
		}
#endif
		}
	}

//DEL	if ((lpCnt == gKSKBRMSTnum) && (flg > -1)) {
//DEL		ret = 2;
//DEL		lpCnt = flg;
//DEL	}

	// 下限値、上限値の確認
//	if (rawData < DataMin) {
//		ret = 1;
//	}
//	else if (rawData > DataMax) {
//		ret = 1;
//	}

	// 出力情報の設定
	if (ret != 0) {
		memset(cKisyak, 0, 15+1);
		// CHG E.Osada 2006-07-21 用手希釈の場合は　'R' であ～る
#if 0
		// 再検用に返す希釈倍率には、先頭の1文字は入れない
		trim(tmp, gpKSKBRMST[lpCnt].KSBR);
		strncpy(cKisyak, &tmp[1], 15);
		pKekka[lCnt].kisyakflg = '2';
#endif
		if( gpKSKBRMST[lpCnt].KSBR[0] == 'Y' ) {
			pKekka[lCnt].kisyakflg = '2';
			ret = 2;
		} else {
			// 再検用に返す希釈倍率には、先頭の1文字は入れない
			trim(tmp, gpKSKBRMST[lpCnt].KSBR);
			strncpy(cKisyak, &tmp[1], 15);
			pKekka[lCnt].kisyakflg = '2';
		}
		//
	}
	else {
		memset(cKisyak, 0, 15+1);
		pKekka[lCnt].kisyakflg = '1';
	}

	return ret;
}

/******************************************************************************/
/*	関 数 名  ：StringCal_sub()												  */
/*	機能概要  ：指定された演算子と値で四則演算行う							  */
/*	入	  力  ：															  */
/*	 第１引数 ：enzan	:	演算子											  */
/*	 第２引数 ：val1	:	値１											  */
/*	 第３引数 ：val2	:	値２											  */
/*	出	  力  ：															  */
/*	復帰情報  ：double	計算結果											  */
/******************************************************************************/
double StringCal_sub(char enzan,double val1,double val2)
{
	switch ( enzan ) {
	case '+':
		return (val1 + val2);
		break;
	case '-':
		return (val1 - val2);
		break;
	case '/':
		if (val2 == 0.0) {
			return 0;
		}
		return (val1 / val2);
		break;
	case '*':
		return (val1 * val2);
		break;
	}
	return 0;
}

/******************************************************************************/
/*	関 数 名  ：StringCal()													  */
/*	機能概要  ：渡された文字列の計算式を行う								  */
/*	入	  力  ：															  */
/*	 第１引数 ：CalStr	:	計算文字列										  */
/*	出	  力  ：															  */
/*	復帰情報  ：double	計算結果											  */
/*																			  */
/*	注意：	対応する演算子は「+ - / *」が可能である。							  */
/*			それ以外にLOG、LOG10、POWの3つの計算を行う。					  */
/*			計算の優先順位は、四則演算の優先順位に従い*と/が優先される。	  */
/******************************************************************************/
double StringCal(char *CalStr)
{
	char		StacEn;
	double		StacNum;
	int			flg;
	int			loopCnt, strCnt;
	double		ret;
	char		cStacNum[32];
	char		cStacNum2[32];
	char		cChk[16];
	int			i, c;
	double		StacRet[10];
	char		StacEnc[10];
	char		StacFlg[10];
	int			StacCnt;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
	ret = 0.0;
	StacEn = '+';
	flg = FALSE;
	strCnt = 0;
	StacCnt = 0;
	for(loopCnt = 0; loopCnt < strlen(CalStr); loopCnt ++) {
		switch (CalStr[loopCnt]) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
			// 数値の時
			break;

		case '+': case '-': case '/': case '*':
			// 演算子の時
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

//			if ((loopCnt == strCnt) && ((CalStr[loopCnt] == '+') || (CalStr[loopCnt] == '-'))) {
//				break;
//			}
//			else
			if ((StacEn == '+' || StacEn == '-') && (CalStr[loopCnt] == '*' || CalStr[loopCnt] == '/')) {
				StacFlg[StacCnt] = StacEn;
				StacRet[StacCnt] = ret;
				StacEnc[StacCnt] = StacEn;
				StacCnt += 1;

				flg = FALSE;
				ret = StacNum;
				StacEn = CalStr[loopCnt];
				strCnt = loopCnt + 1;
			}
			else if ((StacEn == '*' || StacEn == '/') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else if ((StacCnt > 0) && (StacEnc[StacCnt-1] == '+' || StacEnc[StacCnt-1] == '-') &&
					 (StacFlg[StacCnt-1] != '(') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEnc[StacCnt-1], StacRet[StacCnt-1], ret);
				StacCnt -= 1;
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}

//			ret = StringCal_sub(StacEn, ret, StacNum);
//			flg = FALSE;
//			StacEn = CalStr[loopCnt];
			strCnt = loopCnt + 1;
			break;

		case 'L': case 'l':
			// LOG及びLOG10の時
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk , "LOG10") == 0) {
				for (c = 0, i = loopCnt + 6; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = log10(atof(cStacNum));
				flg = TRUE;
				loopCnt += i;
			}
			else if (strcmp(cChk , "LOG") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = atof(cStacNum);
				StacNum = log(StacNum);
				flg = TRUE;
				loopCnt += i;
			}
			break;

		case 'P': case 'p':
			// POWの時
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk, "POW") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				for (c = 0, i += 1; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum2[c] = CalStr[i];
				}
				cStacNum2[c] = '\0';
				StacNum = pow(atof(cStacNum), atof(cStacNum2));
				flg = TRUE;
				loopCnt = i;
			}
			break;

		case '(':
			StacFlg[StacCnt] = '(';
			StacRet[StacCnt] = ret;
			StacEnc[StacCnt] = StacEn;
			StacCnt++;
			ret = 0.0;
			StacEn = '+';
			strCnt = loopCnt + 1;
			break;

		case ')':
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

			StacNum = StringCal_sub(StacEn, ret, StacNum);
			flg = TRUE;

			StacCnt--;
			StacEn = StacEnc[StacCnt];
			ret = StacRet[StacCnt];
			strCnt = loopCnt + 1;
			break;
		}
	}
	if (flg == FALSE) {
		for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
			cStacNum[c] = CalStr[i];
		}
		cStacNum[c] = '\0';
		StacNum = atof(cStacNum);
	}
	ret = StringCal_sub(StacEn, ret, StacNum);
	if (StacCnt > 0) {
		while (StacCnt > 0) {
			StacCnt -= 1;
			StacEn = StacEnc[StacCnt];
			StacNum = StacRet[StacCnt];
			ret = StringCal_sub(StacEn, StacNum, ret);
		}
	}
	return ret;
}

/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** 血清チェック・再検対応 ***/
/******************************************************************************/
/*	関 数 名  ：NyubiYoketuChk()											  */
/*	機能概要  ：乳び・溶血チェック											  */
/*	入	  力  ：															  */
/*	 第１引数 ：chkPara	:	チェック用パラメータ							  */
/*	 第２引数 ：pKekka	:	結果情報構造体配列								  */
/*	 第３引数 ：KekkaCnt:	結果情報構造体数								  */
/*	 第４引数 ：lCnt	:	処理中位置										  */
/*	 第５引数 ：fNyuYou	:	乳び・溶血フラグ								  */
/*	出	  力  ：															  */
/*	復帰情報  ：int															  */
/*					0:再検無し												  */
/*					1:再検あり												  */
/******************************************************************************/
int	NyubiYoketuChk(char * chkPara, Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou)
{
	int			ret = 0;

#ifdef _DEBUG_TRACE_
	printf("%s %s\n", Now(), __func__);
#endif
#ifdef _DEBUG_
		printf("NyubiYoketuChk(%d)\n", __LINE__);
#endif
	if (pKekka[lCnt].kesseiflg == '1' || pKekka[lCnt].kesseiflg == '2') {
		// 既にチェック済みの時は処理しない
#ifdef _DEBUG_
		printf("NyubiYoketuChk(%d) : 既にチェック済みの時は処理しない\n", __LINE__);
#endif
		return 0;
	}

	if (fNyuYou == 0) {
		// 乳び・溶血でないときは処理しない
#ifdef _DEBUG_
		printf("NyubiYoketuChk(%d) : 乳び・溶血でないときは処理しない\n", __LINE__);
#endif
		return 0;
	}

    // add 20070623 waj 上・下限値を取得
    int i;
    double hLimit = 0;
    double lLimit = 0;
    char   sw = 0;
    for (i = 0; i < iRngchkmstNum; i++) {
        if ((memcmp(pKekka[lCnt].knsgrp, pRngchkmst[i].knsgrp, 16) == 0) &&
            (memcmp(pKekka[lCnt].kmkcd,  pRngchkmst[i].kmkcd,   7) == 0) &&
            ((memcmp(pKekka[lCnt].zrcd,  pRngchkmst[i].zaicd,   4) == 0) ||
             (memcmp("000 ",             pRngchkmst[i].zaicd,   4) == 0)) &&
            ((memcmp(pKekka[lCnt].sstcd, pRngchkmst[i].sstcd,   7) == 0) ||
             (memcmp("0000000",          pRngchkmst[i].sstcd,   7) == 0))) {
            hLimit = atof(pRngchkmst[i].hrng);
            lLimit = atof(pRngchkmst[i].lrng);
            sw = 1;
#ifdef _DEBUG_
			printf("血清 H:%f, L:%f\n", hLimit, lLimit);
#endif
            break;
        }
    }
	// add 20070623 waj 乳び・溶血・黄疸の測定値
	double datNyubi  = 0;
	double datYoketu = 0;
//	double datOdan   = 0;
	for (i = 0; i < KekkaCnt; i++) {
		if (memcmp(pKekka[i].kmkcd, NyubiCD,   7) == 0)
			datNyubi  = atof(pKekka[i].rawdata);
		if (memcmp(pKekka[i].kmkcd, YoketsuCD, 7) == 0)
			datYoketu = atof(pKekka[i].rawdata);
//		if (memcmp(pKekka[i].kmkcd, OudanCD,   7) == 0)
//			datOdan   = atof(pKekka[i].rawdata);
	}
#ifdef _DEBUG_
	printf("血清 乳び:%f, 溶血:%f, 黄疸:%f\n", datNyubi, datYoketu, datOdan);
	printf("fNyuYou=%d, chkPara=%c%c\n", fNyuYou, chkPara[0], chkPara[1]);
#endif

	if (chkPara[1] == '1') {
		switch (chkPara[0]) {
		case '0':
			break;
		case '1':	// 乳びのみ
			// upd 20070623 waj
            // if (fNyuYou & 1) {
            if ((fNyuYou & 1) && ((sw == 1) && ((datNyubi < lLimit) || (hLimit < datNyubi)))) {
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    // 結果コメント１に何もセットされていなかったら0105を入れる
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
                    // もし、結果コメントに乳びコメントが入っていたらなにもしない
                }
                else {
                    // 結果コメント１にコメントがセットされていたら、１の内容を２に移し、
                    // １に0105を入れる
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                //
                ret = 1;
            }
			//
			break;
		case '2':	// 溶血のみ
			// upd 20070623 waj
            // if (fNyuYou & 2) {
            if ((fNyuYou & 2) && ((sw == 1) && ((datYoketu < lLimit) || (hLimit < datYoketu)))) {
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
                    // もし、結果コメントに溶血コメントが入っていたらなにもしない
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                ret = 1;
            }
			//
			break;
		case '3':	// 乳び優先
			// upd 20070623 waj
            // if (fNyuYou & 2) {      //溶血
            if ((fNyuYou & 2) && ((sw == 1) && ((datYoketu < lLimit) || (hLimit < datYoketu)))) { //溶血
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
                    // もし、結果コメントに溶血コメントが入っていたらなにもしない
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                ret = 1;
            }
			// upd 20070623 waj
            // if (fNyuYou & 1) {      //乳び
            if ((fNyuYou & 1) && ((sw == 1) && ((datNyubi < lLimit) || (hLimit < datNyubi)))) { //乳び
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
                    // もし、結果コメントに乳びコメントが入っていたらなにもしない
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                ret = 1;
            }
			//
			break;
		case '4':	// 溶血優先
			// upd 20070623 waj
            // if (fNyuYou & 1) {      //乳び
            if ((fNyuYou & 1) && ((sw == 1) && ((datNyubi < lLimit) || (hLimit < datNyubi)))) { //乳び
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
                    // もし、結果コメントに乳びコメントが入っていたらなにもしない
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
                }
                ret = 1;
            }
			// upd 20070623 waj
            // if (fNyuYou & 2) {      //溶血
            if ((fNyuYou & 2) && ((sw == 1) && ((datYoketu < lLimit) || (hLimit < datYoketu)))) { //溶血
                if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0
                        || memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
                    // もし、結果コメントに溶血コメントが入っていたらなにもしない
                }
                else {
                    memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
                    strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
                    memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
                    strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
                }
                ret = 1;
            }
			//
			break;
		}
	}
#ifdef _DEBUG_
	printf("結果コメント１ %s\n", pKekka[lCnt].kkacmt1);
	printf("NyubiYoketuChk(%d) : ret = %d\n", __LINE__, ret);
#endif
	// del 2007.05.16 waj やっぱり項目毎に再検することになったので、ここをコメントアウト
	// ret = 0;		// 乳び溶血では再検を行わないので、0を設定 2006.06.15
	if (ret != 0) {
		pKekka[lCnt].kesseiflg = '2';
	}
	else {
		pKekka[lCnt].kesseiflg = '1';
	}
	return ret;
}

/******************************************************************************/
/*  関 数 名　：GetModule()				 									  */
/*  機能概要　：分析機号機→モジュールNo変換								  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   変換元												  */
/*　 第２引数 ：char *   変換先												  */
/*  出　　力　：                                                              */
/*  復帰情報　：static void													  */
/******************************************************************************/
void GetModule ( char *pFrom, int *pTo )
{
#ifdef _DEBUG_
    printf("GetModule(%d)\n", __LINE__);
#endif

	*pTo = atoi(&pFrom[3]) ;

	return ;
}

/******************************************************************************/
/*  関 数 名　：GetXmSkFlg()												  */
/*  機能概要　：X-M集計フラグ取得											  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   検査グループ										  */
/*　 第２引数 ：char *   項目コード											  */
/*　 第３引数 ：char *   検査開始日(YYYY-MM-DD形式)							  */
/*  出　　力　：                                                              */
/*  復帰情報　：static void													  */
/******************************************************************************/
char GetXmSkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd)
{
	int		iKmkCnt;
	char	cXmSkFlg;
	char	cWrkKnskisymd[9];

#ifdef _DEBUG_
	printf( "GetXmSkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
	printf( "GetXmSkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
	printf( "GetXmSkFlg(%d) : pKnskisymd                     = %s\n\n", __LINE__, pKnskisymd );
#endif

	memset( cWrkKnskisymd, 0, sizeof(cWrkKnskisymd) );
	cWrkKnskisymd[0] = pKnskisymd[0];
	cWrkKnskisymd[1] = pKnskisymd[1];
	cWrkKnskisymd[2] = pKnskisymd[2];
	cWrkKnskisymd[3] = pKnskisymd[3];
	cWrkKnskisymd[4] = pKnskisymd[5];
	cWrkKnskisymd[5] = pKnskisymd[6];
	cWrkKnskisymd[6] = pKnskisymd[8];
	cWrkKnskisymd[7] = pKnskisymd[9];

	/* 初期化 */
	cXmSkFlg = '1';

	for( iKmkCnt = 0; iKmkCnt < iKmkmstNum; iKmkCnt++ ) {
		/* オーダーの項目コードと項目マスタの項目コードが一致した場合 */
		if( (memcmp(pKmkmst[iKmkCnt].knsgrp, pKnsgrp, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kmkcd, pKmkcd, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kaiymd, cWrkKnskisymd, 8) <= 0) &&
			(memcmp(pKmkmst[iKmkCnt].haiymd, cWrkKnskisymd, 8) >= 0) ) {
			/* X-M集計フラグを取得(0:集計する、1:集計しない) */
			cXmSkFlg = pKmkmst[iKmkCnt].xmskflg;
#ifdef _DEBUG_
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].knsgrp        = %s\n", __LINE__, pKmkmst[iKmkCnt].knsgrp );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].kmkcd         = %s\n", __LINE__, pKmkmst[iKmkCnt].kmkcd );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].kaiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].kaiymd );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].haiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].haiymd );
			printf( "GetXmSkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
			printf( "GetXmSkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
			printf( "GetXmSkFlg(%d) : cWrkKnskisymd                  = %s\n", __LINE__, cWrkKnskisymd );
			printf( "GetXmSkFlg(%d) : pKmkmst[iKmkCnt].xmskflg       = %c\n", __LINE__, pKmkmst[iKmkCnt].xmskflg );
			printf( "GetXmSkFlg(%d) : cXmSkFlg                       = %c\n\n", __LINE__, cXmSkFlg );
#endif
			break;
		}
	}

	return cXmSkFlg;

}

/******************************************************************************/
/*  関 数 名　：GetXmChkFlg()												  */
/*  機能概要　：X-Mチェックフラグ取得										  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   検査グループ										  */
/*　 第２引数 ：char *   項目コード											  */
/*　 第３引数 ：char *   検査開始日(YYYY-MM-DD形式)							  */
/*  出　　力　：                                                              */
/*  復帰情報　：static void													  */
/******************************************************************************/
char GetXmChkFlg(char *pKnsgrp, char *pKmkcd, char *pKnskisymd)
{
	int		iKmkCnt;
	char	cXmChkFlg;
	char	cWrkKnskisymd[9];

#ifdef _DEBUG_
	printf( "GetXmChkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
	printf( "GetXmChkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
	printf( "GetXmChkFlg(%d) : pKnskisymd                     = %s\n\n", __LINE__, pKnskisymd );
#endif

	memset( cWrkKnskisymd, 0, sizeof(cWrkKnskisymd) );
	cWrkKnskisymd[0] = pKnskisymd[0];
	cWrkKnskisymd[1] = pKnskisymd[1];
	cWrkKnskisymd[2] = pKnskisymd[2];
	cWrkKnskisymd[3] = pKnskisymd[3];
	cWrkKnskisymd[4] = pKnskisymd[5];
	cWrkKnskisymd[5] = pKnskisymd[6];
	cWrkKnskisymd[6] = pKnskisymd[8];
	cWrkKnskisymd[7] = pKnskisymd[9];

	/* 初期化 */
	cXmChkFlg = '1';

	for( iKmkCnt = 0; iKmkCnt < iKmkmstNum; iKmkCnt++ ) {
		/* オーダーの項目コードと項目マスタの項目コードが一致した場合 */
		if( (memcmp(pKmkmst[iKmkCnt].knsgrp, pKnsgrp, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kmkcd, pKmkcd, 7) == 0) &&
			(memcmp(pKmkmst[iKmkCnt].kaiymd, cWrkKnskisymd, 8) <= 0) &&
			(memcmp(pKmkmst[iKmkCnt].haiymd, cWrkKnskisymd, 8) >= 0) ) {

			/* X-Mチェックフラグを取得(0:異常判定を行う、1:異常判定を行わない) */
			cXmChkFlg = pKmkmst[iKmkCnt].xmchkflg;
#ifdef _DEBUG_
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].knsgrp        = %s\n", __LINE__, pKmkmst[iKmkCnt].knsgrp );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].kmkcd         = %s\n", __LINE__, pKmkmst[iKmkCnt].kmkcd );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].kaiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].kaiymd );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].haiymd        = %s\n", __LINE__, pKmkmst[iKmkCnt].haiymd );
			printf( "GetXmChkFlg(%d) : pKnsgrp                        = %s\n", __LINE__, pKnsgrp );
			printf( "GetXmChkFlg(%d) : pKmkcd                         = %s\n", __LINE__, pKmkcd );
			printf( "GetXmChkFlg(%d) : cWrkKnskisymd                  = %s\n", __LINE__, cWrkKnskisymd );
			printf( "GetXmChkFlg(%d) : pKmkmst[iKmkCnt].xmchkflg      = %c\n", __LINE__, pKmkmst[iKmkCnt].xmchkflg );
			printf( "GetXmChkFlg(%d) : cXmChkFlg                      = %c\n\n", __LINE__, cXmChkFlg );
#endif
			break;
		}
	}

	return cXmChkFlg;

}

//******************************************************************************
//
//	トレース関数
//
//******************************************************************************
#if 0
my_trace(Kekka *pKekka, int KekkaCnt, int KenorderCnt )
{
  int      idx ;

  my_loging ( "MY_TRACE\n", idx ) ;
  // オーダ情報
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  my_loging ( "■■■オーダ情報[%d]■■■\n", KenorderCnt ) ;
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  for ( idx = 0 ; idx <  KenorderCnt ; idx ++ ) {
      my_loging ( "\%d --------------------------------------\n", idx ) ;
      my_loging ( "\t検体No       : [%s]\n", pKenorder[idx].kntno ) ;
      my_loging ( "\t検査グループ : [%s]\n", pKenorder[idx].knsgrp ) ;
      my_loging ( "\t項目コード   : [%s]\n", pKenorder[idx].kmkcd ) ;
      my_loging ( "\t検査回数     : [%d]\n", pKenorder[idx].knssu ) ;
      my_loging ( "\tラックID     : [%s]\n", pKenorder[idx].asyrckid ) ;
      my_loging ( "\tラックPOS    : [%d]\n", pKenorder[idx].asyrckpos ) ;
  }

  // 結果情報
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  my_loging ( "■■■ 結果情報 [%d]■■■\n", KekkaCnt ) ;
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  my_loging ( "■■■■■■■■■■■■■\n" ) ;
  for ( idx = 0 ; idx <  KekkaCnt ; idx ++ ) {
      my_loging ( "\%d --------------------------------------\n", idx ) ;
      my_loging ( "\t検体No       : [%s]\n", pKekka[idx].kntno ) ;
      my_loging ( "\t検査グループ : [%s]\n", pKekka[idx].knsgrp ) ;
      my_loging ( "\t項目コード   : [%s]\n", pKekka[idx].kmkcd ) ;
      my_loging ( "\t検査回数     : [%d]\n", pKekka[idx].knssu ) ;
      my_loging ( "\tラックID     : [%s]\n", pKekka[idx].asyrckid ) ;
      my_loging ( "\tラックPOS    : [%d]\n", pKekka[idx].asyrckpos ) ;
      my_loging ( "\tRAWデータ    : [%s]\n", pKekka[idx].rawdata ) ;
  }
  return ;
}
#endif
