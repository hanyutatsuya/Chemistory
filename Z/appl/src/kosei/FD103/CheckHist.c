/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：CheckHist.c
 *     機能概要  ：ヒストグラムから二峰性・最頻チェックを行う
 **********************************************************************/

/********************************************************************/
/*  Ver.     Date           Name           History                  */
/* -----------------------------------------------------------------*/
/*  1.00     2007-04-12                    Create                   */
/* -----------------------------------------------------------------*/
/*  Ver.     Date           Name           History                  */
/* -----------------------------------------------------------------*/
/*  2.00     2008-10-09     K.Ameno        自動校正対応初版         */
/********************************************************************/

/********************************************************************/
/*  インクルード宣言                                                */
/********************************************************************/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <math.h>
#include "bml_base.h"
#include "FD103.h"

/********************************************************************/
/*  関数名      ：NihoCheck()                                       */
/*  機能概要    ：二峰性チェック                                    */
/*  入力        ：                                                  */
/*   第１引数   ：KTLIST*   kt      調査対象チャネルデータ          */
/*   第２引数   ：int*      hist    ヒスト格納先					*/
/*  出力        ：                                                  */
/*   正常：RTN_OK                                                   */
/*   異常：RTN_NG                                                   */
/********************************************************************/
int NihoCheck(KTLIST* kt, int* hist)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
	int i;
	int down = 0;

    /* トレースログ出力 */
    strcpy( func_nm, "NihoCheck" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* 二峰性チェックではヒストグラムの両端は使用しない */
	for (i = 2; i < (kt->hstkaikyu - 1); i++) {
		if (hist[i-1] > hist[i])
			down = 1;
		if ((hist[i-1] < hist[i]) && down == 1) {
    		LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
			return RTN_NG;
		}
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return RTN_OK;
}

/********************************************************************/
/*  関数名      ：SaihinCheck()                                     */
/*  機能概要    ：最頻チェック                                      */
/*  入力        ：                                                  */
/*   第１引数   ：KTLIST*   kt         調査対象チャネルデータ       */
/*   第２引数   ：int*      histBefore ヒスト格納先（校正前）		*/
/*   第２引数   ：int*      histAfter  ヒスト格納先（校正後）		*/
/*  出力        ：                                                  */
/*   正常：RTN_OK                                                   */
/*   異常：RTN_NG                                                   */
/*   double型同士の比較をしていたため、修正                         */
/********************************************************************/
int SaihinCheck(KTLIST* kt, int* histBefore, int* histAfter)
{
	char	func_nm[MYAPP_LEN_FNCNM+1]; /* 関数名称 */
	int    i;
	int    in;
	int    max;
	double srange;
	double erange;
	int    ret_srange;
	int    ret_erange;
	int    SaihinCheck_keta = 4 /* 明確な規定が無いようなので、結果値より推測 */;

    /*トレースログ出力 */
    strcpy( func_nm, "SaihinCheck" );
    LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* 校正前最頻チェック */
	in  = -1;
	max =  0;
	srange = kt->hstkjntn;
	/* 2009-03-13     H.Sekiya */
	/* 手動校正画面と条件が違うので画面に合わせる */
	/* erange = srange; */
	erange = srange - ( 1 / pow(10, (double)kt->sstnksu));
	for (i = 0; i < kt->hstkaikyu; i++) {
		/* 2009-03-13     H.Sekiya */
		/* 手動校正画面と条件が違うので画面に合わせる */
		/* srange = erange; */
		/* erange = srange + kt->hstkzmhb; */
		srange = erange + ( 1 / pow(10, (double)kt->sstnksu));
		erange = srange + kt->hstkzmhb - ( 1 / pow(10, (double)kt->sstnksu));

		/* if ((kt->shrnglwhf <= srange) && (erange <= kt->shrnghihf)) { */
		ret_srange = chkLowHigh(srange, kt->shrnglwhf, SaihinCheck_keta);
		ret_erange = chkLowHigh(erange, kt->shrnghihf, SaihinCheck_keta);
		if (((ret_srange == 0) || (ret_srange == 1)) && ((ret_erange == 0) || (ret_erange == 2))) {
			/* 範囲内 */
			if ((in < 0) || max < histBefore[i]) {  /* max <= で範囲内データ優先 */
				max = histBefore[i];
				in  = 1;
			}
		} else {
			/* 範囲外 */
			if ((in < 0) || max <= histBefore[i]) { /* max <= で範囲外データ優先 */
				max = histBefore[i];
				in  = 0;
			}
		}
		sprintf(G_msg, "BEFORE srange[%f] ret_srange[%d] erange[%f] ret_erange[%d] in[%d] max[%d] histBefore[%d]) \n", srange,ret_srange,erange,ret_erange,in,max,histBefore[i]);
		LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	if (in < 1) {
    	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
		return RTN_NG;
	}

	/* 校正後最頻チェック */
	in  = -1;
	max =  0;
	srange = kt->hstkjntn;
	/* 2009-03-13     H.Sekiya */
	/* 手動校正画面と条件が違うので画面に合わせる */
	/* erange = srangei; */
	erange = srange - ( 1 / pow(10, (double)kt->sstnksu));
	for (i = 0; i < kt->hstkaikyu; i++) {
		/* 2009-03-13     H.Sekiya */
		/* 手動校正画面と条件が違うので画面に合わせる */
		/* srange = erange; */
		/* erange = srange + kt->hstkzmhb; */
		srange = erange + ( 1 / pow(10, (double)kt->sstnksu));
		erange = srange + kt->hstkzmhb - ( 1 / pow(10, (double)kt->sstnksu));

		/* if ((kt->shrnglwhb <= srange) && (erange <= kt->shrnghihb)) { */
        ret_srange = chkLowHigh(srange, kt->shrnglwhb, SaihinCheck_keta);
        ret_erange = chkLowHigh(erange, kt->shrnghihb, SaihinCheck_keta);
		if (((ret_srange == 0) || (ret_srange == 1)) &&  ((ret_erange == 0) || (ret_erange == 2))) {
			/* 範囲内 */
			if ((in < 0) || max < histAfter[i]) {  /* max <= で範囲内データ優先 */
				max = histAfter[i];
				in  = 1;
			}
		} else {
			/* 範囲外 */
			if ((in < 0) || max <= histAfter[i]) { /* max <= で範囲外データ優先 */
				max = histAfter[i];
				in  = 0;
			}
		}
        sprintf(G_msg, "AFTER srange[%f] ret_srange[%d] erange[%f] ret_erange[%d] in[%d] max[%d] histAfter[%d]) \n", srange,ret_srange,erange,ret_erange,in,max,histAfter[i]);
        LogOut( LT_DBG, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	if (in < 1) {
    	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
		return RTN_NG;
	}

    LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return RTN_OK;
}

