/******************************************************************************/
/*   ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/*   システム名：次世代システム                                               */
/*   ファイル名：KoseiKaHi.sqc                                                */
/*   概      要：ＤＢアクセス                                                 */
/*   OS        ：SUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   言語      ：DB2/C                                                        */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2007/04/08     INTEC.INC      CREATE                             */
/* -------------------------------------------------------------------------- */
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/10/09     K.Ameno        自動校正対応                       */
/*  2.01     2009/03/13     H.Sekiya       double型の比較方法修正             */
/******************************************************************************/

/******************************************************************************/
/* インクル－ド宣言                                                           */
/******************************************************************************/
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <sqlca.h>
#include    <math.h>
#include    "FD103.h"

/*********************************************************************/
/* マルチから引用(chk_kousei.c)                                      */
/* ここから ↓                                                       */
static  void    stat_calc( x,y,zz )
/*********************************************************************
*fc
*     統計処理用計算関数
*rt
*nt
    本処理にてＮ ΣＸ ΣＹ Σ（Ｘ・Ｙ） ΣＸ・Ｘ ΣＹ・Ｙ
    を計算し構造体の示すエリアへ格納します。
    但し、Ｘ or Ｙ が数値でない場合は対象としません。
*ag
*********************************************************************/
char        *x;     /* [i] Ｘ値 */
char        *y;     /* [i] Ｙ値 */
TOUKEI_CALC *zz;    /* [o] 統計用構造体のポインタ */
{
    double  dx;
    double  dy;

    dx  =   ( double )atof( x );
    dy  =   ( double )atof( y );

    zz->n   =   zz->n + 1;

    zz->sumx    =   zz->sumx + dx;
    zz->sumy    =   zz->sumy + dy;
    zz->sumxy   =   zz->sumxy + ( dx * dy );
    zz->sumxx   =   zz->sumxx + ( dx * dx );
    zz->sumyy   =   zz->sumyy + ( dy * dy );

}

static  void    kousei_func( zz,place,a,b )
/*********************************************************************
*fc
*     校正係数計算関数
*rt
*nt
    校正用ファクタ－(a)、ベ－ス(b) を求め出力する。

    ファクタ－：
                　　　　　　　　　　ΣＹ・ΣＸ
        　　　　Σ（Ｘ・Ｙ）　－    －－－－－
        　　　　　　　　　　　　　　　　Ｎ
        Ａ　＝　－－－－－－－－－－－－－－－－
         　　　　　　　　　　　　　（ΣＸ）^２
         　　　　Σ（Ｘ^２）　－　　－－－－－
        　　　　　　　　　　　　　　　　Ｎ

    ベ－ス：
        Ｂ　＝　AVE（Ｙ）　－　Ａ・AVE（Ｘ）
        （ベ－スは、項目の小数点桁数に編集を行なう。）

    （尚、分母が０の場合は、CHK_lst_hensyu() において a=1.00 b=0 に編集
    するため、"********","********"を設定しておく。")

*ag
*********************************************************************/
TOUKEI_CALC zz;         /* [i] 統計用構造体   */
int         place;      /* [i] 小数点桁数     */
char        *a;         /* [o] 校正ファクタ－ */
char        *b;         /* [o] 校正ベ－ス     */
{

    double  da;
    double  db;
    double    bunbo;

    bunbo    = zz.sumxx -  ( pow(zz.sumx,2.0) / ( zz.n + 1.0 ) ) ;

    if( bunbo == 0 ){

        sprintf(a,"********");
        sprintf(b,"********");
        return;

    }else{

        da = ( zz.sumxy - ( zz.sumx * zz.sumy )/( zz.n + 1.0 ) ) / bunbo;
        db = zz.sumy/( zz.n + 1.0 ) - da * ( zz.sumx / ( zz.n + 1.0 ) );

    }

    /* 小数点桁数編集 */
    sprintf(a,"%8.*f",2    ,da);
    sprintf(b,"%8.*f",place,db);

    /* -0.0対応 */
    if( atof(a) == 0 ){
        da = 0;
        sprintf(a,"%8.*f",2    ,da);
    }
    if( atof(b) == 0 ){
        db = 0;
        sprintf(b,"%8.*f",place,db);
    }

}
/* ここまで ↑                                                      */
/* マルチから引用(chk_kousei.c)                                     */
/********************************************************************/

/********************************************************************
    ファクタ・ベ－スの状態チェック
      double型同士の比較をしていたため、誤動作発生。
      比較方法を修正した
    0:    正常
    1:    校正可能
    2:    再測定
    3:    校正係数計算不能
*********************************************************************/
static int lst_hantei(
KTLIST *kt, char* fact, char* base)
{

    char    func_nm[MYAPP_LEN_FNCNM+1];             /* 関数名称 */
    double  fc,fc1,fc2;        /* ファクタ－ */
    double  bs,bs1,bs2;        /* ベ－ス     */
	int     ret_fc;
	int     ret_bs;

    /* 初期処理 */
    strcpy( func_nm, "lst_hantei" );

    if (strncmp(fact,"*",1) == 0){
        fc = 1.00;
        bs = 0.00;
        sprintf(fact, "%8.*f", 2, fc);
        sprintf(base, "%8.*f", kt->sstnksu, bs);
        return(3);
    }

    int     flgF, flgB;
    fc  = fabs(1.0 - (double)atof(fact)); /* ファクタ(a) ※ 1.0 - fact の絶対値 */
    fc1 = (double)atof(kt->facterjd1);    /* CTRLMST：ファクター自動1 */
    fc2 = (double)atof(kt->facterjd2);    /* CTRLMST：ファクター自動2 */
    bs  = (double)atof(base);             /* ベース(a) (VBでは絶対値を求めていない) */
    bs1 = (double)atof(kt->basejd1);      /* CTRLMST：ベース自動1 */
    bs2 = (double)atof(kt->basejd2);      /* CTRLMST：ベース自動2 */

	/* ファクタ判定 */
	ret_fc = chkLowHigh(fc1, fc, 2);
	/* ファクタ正常 : CTRLMST：ファクター自動1 >= ファクタ(a) */
	if ((ret_fc == 0) || (ret_fc == 1)) {
		flgF = 0;
	} else if (ret_fc == 2) {
		 ret_fc = chkLowHigh(fc2, fc, 2);
		/* ファクタ校正対象 : CTRLMST：ファクター自動1 < ファクタ(a) <= CTRLMST：ファクター自動2 */
		if ((ret_fc == 0) || (ret_fc == 1)) {
			flgF = 1;
	    } else if (ret_fc == 2) {
		/* ファクタ再測定 : CTRLMST：ファクター自動2 < ファクタ(a) */
			flgF = 2;
		} else {
		/* ファクタ校正異常 */
			flgF = 3;
		}
	} else {
	/* ファクタ校正異常 */
		flgF = 3;
	}

	/* ベース判定 */
	ret_bs = chkLowHigh(bs1, bs, 2);
	/* ベース正常 : CTRLMST：ベース自動1 >= ベース(a) */
	if ((ret_bs == 0) || (ret_bs == 1)) {
		flgB = 0;
	} else if (ret_bs == 2) {
		ret_bs = chkLowHigh(bs2, bs, 2);
		/* ベース校正対象  CTRLMST：ベース自動1 < ベース(a) <= CTRLMST：ベース自動2 */
		if ((ret_bs == 0) || (ret_bs == 1)) {
			flgB = 1;
		 } else if (ret_bs == 2) {
		/* ベース再測定 : CTRLMST：ベース自動2 < ベース(a) */
			flgB = 2;
		} else {
		/* ファクタ校正異常 */
			flgB = 3;
		}
	/* ベース校正異常 */
	} else {
		flgB = 3;
	}

//	/* ファクタ判定 */
//	/* CTRLMST：ファクター自動1 >= ファクタ(a) */
//	if (fc1 >= fc)
//		/* ファクタ正常 */
//	flgF = 0;
//	/* CTRLMST：ファクター自動1 < ファクタ(a) <= CTRLMST：ファクター自動2 */
//	else
//	if ( && (fc <= fc2))
//		/* ファクタ校正対象 */
//		flgF = 1;
//	/* CTRLMST：ファクター自動2 < ファクタ(a) */
//	else
//	if (fc2 < fc)
//		/* ファクタ再測定 */
//		flgF = 2;
//	else
//		/* ファクタ校正異常 */
//		flgF = 3;
//
//	/* ベース判定 */
//	/* CTRLMST：ベース自動1 >= ベース(a) */
//	if (bs1 >= bs)
//		/* ベース正常 */
//		flgB = 0;
//	/* CTRLMST：ベース自動1 < ベース(a) <= CTRLMST：ベース自動2 */
//	else
//	if ((bs1 < bs) && (bs <= bs2))
//		/* ベース校正対象 */
//		flgB = 1;
//	/* CTRLMST：ベース自動2 < ベース(a) */
//	else
//	if (bs2 < bs)
//		/* ベース再測定 */
//		flgB = 2;
//	else
//		/* ベース校正異常 */
//		flgB = 3;

        {/* DEBUG WRITE */
			sprintf(G_msg, "ファクタ[%f] ファクタ自動１[%f] ファクタ自動２[%f] ファクタフラグ｢%d] ベース[%f] ベース自動１[%f] ベース自動２[%f] ベースフラグ[%d]\n", fc, fc1, fc2, flgF, bs, bs1, bs2, flgB);
            LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        }

	/* ファクタ・ベースの判定結果からレンジの判定を行う */
	/* ファクタ正常＆ベース正常 */
	if ((flgF == 0) && (flgB == 0)) {
		return (0); /* 正常 */
	/* (ファクタ正常 or ファクタ校正対象) and (ベース正常 or ベース校正対象) */
	} else if (((flgF == 0) || (flgF == 1)) && ((flgB == 0) || (flgB == 1))) {
		return (1); /* 校正可能 */
	/* ファクタ再測定 or ベース再測定 → 仕様書では、ファクタ再測定 and ベース再測定 どっち？ */
	} else if ((flgF == 2) || (flgB == 2)) {
		return (2); /* 再測定 */
	} else {
		return (3); /* 校正ＮＧ */
	}
	
	return (0);
}

/******************************************************************************/
/*  関 数 名  ：KoseiKaHi                                                     */
/*  機能概要  ：校正可否判定                                                  */
/*  入    力  ：                                                              */
/*   第１引数 ：KTLIST * allKt	: 校正対象リスト                              */
/*   第２引数 ：int      tPos	: 校正対象リスト該当データ位置                */
/*   第３引数 ：int      pPos	: 校正対象リスト前コントロール位置            */
/*   第４引数 ：ATKSTS * at		: 自動校正情報                                */
/*   第５引数 ：int      kensu  : 校正対象リスト件数                          */
/*  出    力  ：                                                              */
/*  復帰情報  ：RH_NORMAL    正常終了                                         */
/*            ：RH_KOUSEI	 校正対象                                         */
/*            ：KOUSEI_IJOU  異常終了                                         */
/******************************************************************************/
int KoseiKaHi(
	KTLIST*	allKt,
	int		tPos,
	int		pPos,
	ATKSTS* at,
	int*    histCnt,
	int		kensu)
{
    char    	func_nm[MYAPP_LEN_FNCNM+1];             /* 関数名称 */
	TOUKEI_CALC zz;    									/* 統計用構造体 */
	KTLIST* 	kt		= allKt+tPos;					/* 対象コントロール */
	KTLIST* 	prevKt	= allKt+pPos;					/* 前コントロール */
    int     	ret		= RH_NORMAL;
	int			top		= 0;
	int			next	= 0;
	int			pos;
	
	char		fact[9];
	char		base[9];

    /* 初期処理 */
    strcpy( func_nm, "KoseiKaHi" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	if (kt->ctrlno - 1 != prevKt->ctrlno) {
		/* コントロ－ル番号が連番になっていない */
		/* 現状では特にチェック対象とはしない */
	}

	/* 前のコントロ－ルが異常なら非対称 */
	if (prevKt->nonecnt != 0 || prevKt->ngcnt != 0) {
		/* autokosiflg(自動校正対象フラグ) = '0' (校正対象外) */
		/* causecd(校正対象外事由コード)   = KSTS_CTRLNG (4)  */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_CTRLNG);

        sprintf(G_msg, "前のコントロ－ルが異常（%s,%s,%d）：%d",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno,prevKt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		/* KOUSEI_IJOU (3) */
		return KOUSEI_IJOU;
	}

	/* ヒスト階級数チェック : 階級数は５以上でないと判定処理が出来ない */
	if (kt->hstkaikyu < 5) {
		/* autokosiflg(自動校正対象フラグ) = '0' (校正対象外) */
		/* causecd(校正対象外事由コード)   = KSTS_HIST (5)    */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_HIST);

        sprintf(G_msg, "ヒスト階級数が５未満（%s,%s,%d）：%d",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno,kt->hstkaikyu);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
		/* KOUSEI_IJOU (3) */
		return KOUSEI_IJOU;
	}

	/* レンジ判定 */

	/* 集計 */
	/* 校正対象コントロール及び校正対象(前)コントロールの測定値と */
	/* 平均値(同じチャネルのもの)の集計をチャネルで行う */
	/* Xをコントロール測定値とし、Yを平均値とした場合の以下の総和をとる。 */
	/* ◎ ΣX、ΣY、Σ(X・Y)、Σ(X・X)、Σ(Y・Y) */
	{
		/* 統計処理構造体初期化 */
		memset(&zz, 0, sizeof(zz));

		/* まずは前コントロールから */
		top  = SearchTopControlPosition(allKt, pPos, 0);
		next = SearchNextControlPosition(allKt, pPos, kensu, 0);
		for (pos = top; pos < next; pos++)
			/* void stat_calc(x, y, zz)                           */
			/* (i)x  : 測定値(コントロールの測定値)               */
			/* (i)y  : 平均値(コントロールマスタテーブルの平均値) */
			/* (o)zz : 集計用構造体                               */
			stat_calc((allKt+pos)->sktti, (allKt+pos)->ctrlx, &zz);

		/* 続いて対象コントロールを処理 */
		top  = SearchTopControlPosition(allKt, tPos, 0);
		next = SearchNextControlPosition(allKt, tPos, kensu, 0);
		for (pos = top; pos < next; pos++)
			/* void stat_calc(x, y, zz)                           */
			/* (i)x  : 測定値(コントロールの測定値)               */
			/* (i)y  : 平均値(コントロールマスタテーブルの平均値) */
			/* (o)zz : 集計用構造体                               */
			stat_calc((allKt+pos)->sktti, (allKt+pos)->ctrlx, &zz);
	}

	/* 校正係数算出 */
	/* 上記の集計で算出した集計値(zz)と小数点桁数(同じチャネルのもの)でファクタ及びベースを算出する。 */
	memset(fact, 0, sizeof(fact));
	memset(base, 0, sizeof(base));
	/* void kousei_func(zz, place, a, b)                 */
	/* (i)zz    : 集計値                                 */
	/* (i)place : 小数点桁数(コントロールマスタテーブル) */
	/* (o)a     : ファクタ                               */
	/* (o)b     : ベース                                 */
	kousei_func(&zz, kt->sstnksu, fact, base);
	at->facter = atof(fact);
	at->base   = atof(base);

/* #	ifdef DEBUG_DET */
	{/* DEBUG WRITE */
		sprintf(G_msg, "校正係数 %s %s %s %d : FACTER = %8.2f BASE = %8.*f\n",
				 kt->bskkbn, kt->bskgok, kt->nbkmkcd, kt->ctrlno, at->facter, kt->sstnksu, at->base);
        LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
/* #	endif */

	/* 判定 */
	ret = lst_hantei(kt, fact, base);

	switch (ret) {
	case 0: /* 正常 */
#	ifdef DEBUG_HIST
		/* ヒスト関連チェックのため強制的に正常データを校正対象として処理する */
        sprintf(G_msg, "校正対象 DEBUG HIST（%s,%s,%d）",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_KOUSEI (1) */
		return RH_KOUSEI;
#	endif
		/* 正常値のため校正対象外 */
		/* autokosiflg(自動校正対象フラグ) = '0' (校正対象外) */
		/* causecd(校正対象外事由コード)   = KSTS_NORMAL (1)  */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_NORMAL);

        sprintf(G_msg, "正常値のため校正対象外（%s,%s,%d）",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_NORMAL (0) */
		return RH_NORMAL;
	case 1:
		/* 校正対象 */
        sprintf(G_msg, "校正対象（%s,%s,%d）",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_KOUSEI (1) */
		return RH_KOUSEI;
	case 2:
		/* 再検が必要なデータのため、ここはスキップ（次回処理にまわす） */
        sprintf(G_msg, "再検が必要なデータ（%s,%s,%d）",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* RH_SAIKEN (2) */
		return RH_SAIKEN;
	case 3: /* 校正異常 */
	default:
		/* 校正異常・その他 */
		/* autokosiflg(自動校正対象フラグ) = '0' (校正対象外)  */
		/* causecd(校正対象外事由コード)   = KSTS_FB_CALC (8)  */
		strcpy(at->autokosiflg, "0");
		sprintf(at->causecd, "%d", KSTS_FB_CALC);

        sprintf(G_msg, "校正異常・その他（%s,%s,%d）",
            kt->bskgok,kt->nbkmkcd,kt->ctrlno);
        LogOut( LT_WRN, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
        /* KOUSEI_IJOU (3) */
        return KOUSEI_IJOU;
	}

	/* 実際には通らない */
    LogOut(LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__);
	/* RH_NORMAL (0) */
	return RH_NORMAL;
}

/**********************************************************************/
/*	関 数 名	：chkLowHigh                                          */
/*	機能概要	：double型の値の大小チェック                          */
/*	 第１引数	:double	: hikaku1	: 比較対象１                      */
/*	 第２引数	:double	: hikaku2	: 比較対象２                      */
/*	 第３引数	:int	: ketasu	: 比較する対象の桁数              */
/*   戻り値		: 0 : 比較対象１ ＝ 比較対象２                        */
/*				: 1 : 比較対象１ ＞ 比較対象２                        */
/*				: 2 : 比較対象１ ＜ 比較対象２                        */
/**********************************************************************/
int chkLowHigh(
	double	hikaku1,
	double	hikaku2,
    int     ketasu)
{
	int val1;
	int val2;
	int ret;

	char    func_nm[MYAPP_LEN_FNCNM+1];             /* 関数名称 */

	/* 初期処理 */
	strcpy( func_nm, "chkLowHigh" );

	/* 桁数 + 1 の位で四捨五入してint型に変換 */
	val1 = (int)floor((hikaku1 * pow(10, ketasu)) + 0.5);
	val2 = (int)floor((hikaku2 * pow(10, ketasu)) + 0.5);

	/* 比較結果を返す */
	if (val1 == val2)
        ret = 0;
	else
	if (val1 > val2)
		ret = 1;
	else
	if (val1 < val2)
		ret = 2;
	else
		ret = 3;

	{/* DEBUG WRITE */
		sprintf(G_msg, "比較桁数｢%d] 比較元[%f]→比較元[%d] 比較先[%f]→比較先[%d] リターン｢%d]\n", ketasu, hikaku1, val1, hikaku2, val2, ret);
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}

	return ret;

}
