/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：LD106.h                                                      */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.	日付		名前		修正内容			*/
/* -------------------------------------------------------------------------- */
/*  0.00	2006/01/15	BML.Inc		新規作成			*/
/******************************************************************************/
#ifndef _LD106_db_h
#define _LD106_db_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"

#include "LD106.h"
/******************************************************************************/
/* DB用構造体定義                                                             */
/******************************************************************************/

//	システム管理マスタ情報構造体
typedef struct  _stSYSKNR 
{
        char    kjnsriymd[10+1];	// 基準処理年月日
        char    iriendflg[1+1];		// 依頼ENDフラグ
        char    bchendflg[1+1];		// 分注ENDフラグ
        char    unyflg[1+1];		// 運用フラグ
} my_stSYSKNR ;

typedef struct _stCALC
{
	char	utkymd[10+1];	// 1  ＢＭＬ受付年月日
	char	irino[11+1];	// 2  依頼書Ｎｏ
	char	knsgrp[16+1];	// 3  検査グループ
	char	kmkcd[7+1];	// 4  項目コード
	char	sstcd[7+1];	// 5  施設コード
	char	zrcd[4+1];	// 6  材料コード
	char	sc[5+1];	// 7  身長
	char	tj[5+1];	// 8  体重
	char	tjtni[1+1];	// 9  体重区分
	char	sbtkbn[1+1];	// 10 性別区分
	char	age[3+1];	// 11 年齢
	char	agekbn[1+1];	// 12 年齢区分
	char	tntme[4+1];	// 13 蓄尿時間
	char	tntni[1+1];	// 14 蓄尿時間区分
	char	tnryo[5+1];	// 15 蓄尿量
	char	tnryotni[1+1];	// 16 蓄尿量区分
} my_stCALC ;

typedef struct _stCALCSYSMST
{
	char	knsgrp[16+1];
	char	kmkcd[7+1];
	char	sstcd[7+1];
	char	zaicd[4+1];
	char	hkkbn[1+1];
	char	ksnsk[128+1];
	char	kaiymd[10+1];
	char	haiymd[10+1];
	char	hnktntid[8];
	char	ksndh[26+1];
} my_stCALCSYSMST ;

typedef struct _stKEKKA
{
	char		knskisymd[10+1];
	char		sriymd[10+1];
	char		kntno[13+1];
	char		kntketflg;
	char		knsgrp[16+1];
	char		kmkcd[7+1];
	short		knssu;
	short		knssueda;
	char		irihsmkbn;
	char		irikbn;
	char		ksktkbn;
	char		utkymd[10+1];
	char		irino[11+1];
	char		iriketflg;
	short		zssdino;
	char		sstcd[7+1];
	char		trid[10+1];
	short		trpos;
	char		asyrckid[10+1];
	short		asyrckpos;
	char		oyakmkcd[7+1];
	char		seccd[2+1];
	char		bkfkkbn;
	char		smpcd[7+1];
	char		bskkbn[4+1];
	char		bsklne[4+1];
	char		bskgok[6+1];
	sqlint32	bskseq;
	char		bskerrsts[2+1];
	char		sktdh[26+1];
	char		nbkmkcd[7+1];
	char		tstrflg;
	char		zrcd[4+1];
	char		ysnlbl[2+1];
	char		kjno[3+1];
	char		fkhkknohjkbn;
	char		tbkjno[3+1];
	char		tbkjflg;
	char		htkfkhms[24+1];
	char		skflg;
	char		tskflg[2+1];
	char		tktflg[2+1];
	char		jisksbr[15+1];
	char		kkflg;
	char		kkiriflg;
	short		kkirilotno;
	char		hsykflg;
	char		hskflg;
	char		hhkkflg;
	char		rawdata[20+1];
	char		knskka1[12+1];
	char		knskka2[24+1];
	char		knskka2kbn[2+1]; 
	char		kkahskcd[3+1];
	char		hjkka[24+1];
	char		sdi[3+1];
	char		kkacmt1[5+1];
	char		kkacmt2[5+1];
	char		kkajkcd;
	char		pncrgflg;
	char		knspncrgflg; 
	char		kkaksflg;
	char		kkassflg;
	char		ijkbnm;
	char		ijkbnf;
	char		ijkbnn;
	char		tbijkbnm;
	char		tbijkbnf;
	char		tbijkbnn;
	char		nbdolbl[2+1];
	char		nbdoerr[3+1];
	char		ykdolbl[2+1];
	char		ykdoerr[3+1];
	char		etclbl[2+1];
	char		etcerr[3+1];
	sqlint32	ctrlno;
	sqlint32	knsseq;
	short		bthno;
	sqlint32	pltno;
	sqlint32	pltseq;
	char		dtnrtts[8+1];
	char		dtnrdh[26+1];
	char		knskrdh[26+1];
	char		hkkdh[26+1];
	char		hkkkbdh[8+1];
	char		zkhkkyymd[10+1];
	char		zkhkkytme[4+1];
	char		frkkaflg;
	char		gzbsflg;
	char		hsiflg;
	char		kkaysnflg;
	char		tnyrkflg;
	char		siyflg;
	char		knsflg;
	char		renjicflg;
	char		soukn1flg;
	char		kanrenflg;
	char		bunkkuflg;
	char		kesseiflg;
	char		rirekiflg;
	char		syougoflg;
	char		keisanflg;
	char		per100flg;
	char		tousekflg;
	char		kisyakflg;
	char		kouseiflg;
	char		syoungflg;
	char		soukn2flg;
	char		fukaptflg;
	char		yobiflg01;
	char		tobiflg02;
	char		yobiflg03;
	char		yobiflg04;
	char		yobiflg05;
	char		skrycda[3+1];
	char		skrycdb[3+1];
	char		skrycdc[3+1];
	char		ksndh[26+1];
	char		trkdh[26+1];
	char		skkka[24+1];
} my_stKEKKA;

typedef struct _stKjnmst {
	char		kmkcd[8];
	char		kjno[4];
	char		kjsdino[3];
	char		zrcd[5];
	char		agerngkbn[3];
	char		etckbn[4];
	char		nichilw[6];
	char		nichihi[6];
	char		kjnmlw[9];
	char		kjnmhi[9];
	char		kjnflw[9];
	char		kjnfhi[9];
	char		kjnelw[9];
	char		kjnehi[9];
	char		genmlw[9];
	char		genmhi[9];
	char		genflw[9];
	char		genfhi[9];
	char		genelw[9];
	char		genehi[9];
	short		kjsstnksu;
	char		kjnmhkn[25];
	char		kjnmhkj[25];
	char		kjnfhkn[25];
	char		kjnfhkj[25];
	char		kjnohkn[25];
	char		kjnohkj[25];
	char		lwm1[9];
	char		lwm2[9];
	char		kjm1[9];
	char		kjm2[9];
	char		him1[9];
	char		him2[9];
	char		lwf1[9];
	char		lwf2[9];
	char		kjnnaf1[9];
	char		kjnnaf2[9];
	char		hif1[9];
	char		hif2[9];
	char		lwe1[9];
	char		lwe2[9];
	char		kje1[9];
	char		kje2[9];
	char		hie1[9];
	char		hie2[9];
	char		tankn[17];
	char		tankj[17];
	char		stjyken[61];
	char		kymstjn;
	char		kaiymd[11];
	char		haiymd[11];
	char		hnktntid[9];
	char		ksndh[27];
} my_stKJNMST;

typedef struct _stRngchkmst {
	char		hnikbn;
	char		knsgrp[17];
	char		kmkcd[8];
	char		zaicd[5];
	char		sstcd[8];
	char		sbt;
	char		ssa;
	char		zen_kyoyou;
	char		hrng[21];
	char		lrng[21];
	char		kaiymd[11];
	char		haiymd[11];
	char		hnktntid[9];
	char		ksndh[27];
} my_stRNGCHKMST;

typedef struct _stKkafltmst {
        char		knsgrp[17];
        char		kmkcd[8];
        char		fltkka[25];
        char		minval[13];
        char		maxval[13];
        char		knskka1[13];
        char		knskka2[25];
        char		knskka2kbn[3];
        char		kkahskcd[4];
        char		hjkka[25];
        char		kaiymd[11];
        char		haiymd[11];
        char		hnktntid[9];
        char		ksndh[27];
        char		sstcd[8];
        char		tkykbn[2];
} my_stKKAFLTMST;

#endif
/** End of File *********************************************************/
