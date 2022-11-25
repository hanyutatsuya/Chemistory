/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：GD105KkaConvChk.c								*/
/*		概要		：結果報告ファイル作成処理						*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ---------------------------------------------------------------- */
/*  2.00    2009/05/19      K.Moriya        結果変換マスタ対応      */
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <time.h>
#include <errno.h>
#include "bml_date.h"
#include "bmllog.h"
#include "bmlprm.h"
#include "GD105Main.h"
#include "GD105KkaConvChk.h"

/******************************************************************************/
/* Define定義																  */
/******************************************************************************/
// TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)	 _free(p, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* グローバル宣言															  */
/******************************************************************************/
struct stcLogMember	gstLogMem;


/******************************************************************************/
/*　関 数 名　：GD105KkaConvChk()											  */
/*　機能概要　：結果変換チェック関数										  */
/*　入　　力　：															  */
/*　　第１引数：Kekka		*pKekka			結果情報構造体					  */
/*　　第２引数：Kkaconvmst	*pKkaconvmst	結果変換マスタ構造体			  */
/*　　第３引数：char		*pSstcd			施設コード						  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	 : 正常終了(0)									  */
/*　　　　　　		RTN_NG	 : 異常終了(-1)									  */
/*　　　　　　		RTN_SKIP : 処理スキップ(-2)								  */
/******************************************************************************/
int GD105KkaConvChk(Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pSstcd)
{
	Kanjya		keyKanjya;				/* 患者情報構造体                           */
	Kanjya		*pKanjya = NULL;		/* 患者情報構造体                           */
	Kenzok		keyKenzok;				/* 検体属性情報構造体                       */
	Kenzok		*pKenzok = NULL;		/* 検体属性情報構造体                       */
//	Kkaconvmst	keyKkaconvmst;			/* 結果変換マスタ構造体                     */
	Kkaconvknr	sKkaconvknr;			/* 結果変換管理情報構造体                   */
	Kkaconvknr	*pKkaconvknr = NULL;	/* 結果変換管理情報構造体                   */
	KekkaConv	sKekkaConv;				/* 結果変換更新用構造体                     */
	KekkaConv	*pKekkaConv = NULL;		/* 結果変換更新用構造体                     */
	int			iRet;					/* 各種チェックリターン値                   */
	int			iRetKbn;				/* 区分有りの項目チェックリターン値(区分用) */
	int			iRetChk;				/* チェック結果値                           */
	int			iMstChkCnt = 0;			/* マスタのチェック項目数                   */
	int			numOut;					/* SQL件数用                                */
	char		tmp[32+1];				/* 条件式一時退避用変数                     */
	char		cShiki0;				/* 条件式の頭1バイト目                      */
	char		cDtnrtts[8+1];			/* データ入力担当者用変数                   */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105KkaConvChk - 開始" );
#endif
	/**************************************************************/
	/* SQL用KEY情報設定                                           */
	/**************************************************************/
	/* データ入力担当者   */
	memset(cDtnrtts, 0, sizeof(cDtnrtts));
	strcpy(cDtnrtts, "GD105CNV");

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ データ入力担当者" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cDtnrtts = [%s]", cDtnrtts );
#endif

	/* 患者情報キー       */
	memset(&keyKanjya, 0, sizeof(Kanjya));
	strcpy(keyKanjya.utkymd, pKekka->utkymd);			/* 受付日       */
	strcpy(keyKanjya.irino, pKekka->irino);				/* 依頼書No     */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ 患者情報キー" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKanjya.utkymd  = [%s]", keyKanjya.utkymd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKanjya.irino   = [%s]", keyKanjya.irino );
#endif

	/* 検体属性情報キー   */
	memset(&keyKenzok, 0, sizeof(Kenzok));
	strcpy(keyKenzok.sriymd, pKekka->sriymd);			/* 処理日       */
	strcpy(keyKenzok.kntno, pKekka->kntno);				/* 検体No       */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ 検体属性情報キー" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKenzok.sriymd  = [%s]", keyKenzok.sriymd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    keyKenzok.kntno   = [%s]", keyKenzok.kntno );
#endif

//	memset(&keyKkaconvmst, 0, sizeof(Kkaconvmst));
//	strcpy(keyKkaconvmst.knsgrp, pKekka->knsgrp);		/* 検査グループ */
//	strcpy(keyKkaconvmst.kmkcd, pKekka->kmkcd);			/* 項目コード   */
//	strcpy(keyKkaconvmst.sstcd, pKekka->sstcd);			/* 施設コード   */
//	strcpy(keyKkaconvmst.kaiymd, pKekka->knskisymd);	/* 検査開始日   */

#ifdef _DEBUG
	/* 結果情報キー */
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ 結果情報キー" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->knskisymd = [%s]", pKekka->knskisymd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->kntno     = [%s]", pKekka->kntno );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->knsgrp    = [%s]", pKekka->knsgrp );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->kmkcd     = [%s]", pKekka->kmkcd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->knssu     = [%d]", pKekka->knssu );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKekka->sstcd     = [%s]", pKekka->sstcd );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pSstcd            = [%s]", pSstcd );
#endif

	/**************************************************************/
	/* 情報取得                                                   */
	/**************************************************************/
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ 最新属性世代の患者情報取得関数" );
#endif

	/* 最新属性世代の患者情報取得関数 */
	/* ※ 受け日、依頼書Noで最新属性世代Noの患者情報を取得する。  */
	iRet = dGD105_KANJYA_Sel_latestZSSDINO( &keyKanjya, &pKanjya, &numOut );
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    dGD105_KANJYA_Sel_latestZSSDINO iRet = [%d]", iRet );
#endif
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND )
	{
		//異常終了
		//ログ出力
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KANJYA_Sel_latestZSSDINO ERROR [%d]", iRet );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		return RTN_NG;
	}
	/* 検索結果が0件の場合、結果変換せず既存の処理に乗せる。(ファイル作成へ行く) */
	else if (numOut == 0)
	{
		sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KANJYA_Sel_latestZSSDINO - Not Found" );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		return RTN_SKIP;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    KANJYA numOut = [%d]", numOut );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ 最新属性世代の検体属性情報取得関数" );
#endif

	/* 最新属性世代の検体属性情報取得関数 */
	/* ※ 処理日、検体Noで最新属性世代Noの検体属性情報を取得する。 */
	iRet = dGD105_KENZOK_Sel_latestZSSDINO( &keyKenzok, &pKenzok, &numOut );
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    dGD105_KENZOK_Sel_latestZSSDINO iRet = [%d]", iRet );
#endif
	if ( iRet != HRC_SQL_NORMAL && iRet != HRC_SQL_NOT_FOUND )
	{
		//異常終了
		//ログ出力
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KENZOK_Sel_latestZSSDINO ERROR [%d]", iRet );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_NG;
	}
	/* 検索結果が0件の場合、結果変換せず既存の処理に乗せる。(ファイル作成へ行く) */
	else if (numOut == 0)
	{
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105KkaConvChk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"dGD105_KENZOK_Sel_latestZSSDINO - Not Found" );

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    KENZOK numOut = [%d]", numOut );
#endif


	/**************************************************************/
	/*                                                            */
	/* 各種データチェック                                         */
	/*                                                            */
	/**************************************************************/

	/* ◆ 性別区分チェック ◆ */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆◆◆ 性別区分チェック ◆◆◆" );
#endif

	memset(tmp, 0, sizeof(tmp));
	if (pKkaconvmst->sbtkbn != GD105_DATA_SPACE)
	{
		tmp[0] = pKkaconvmst->sbtkbn;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->sbtkbn ==> tmp = [%s]", tmp );
#endif

	/* 初期化 GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* チェック条件入力ありの場合 */
	if ( strlen(tmp) != 0 )
	{
		/* マスタにチェック条件入力ありなのでインクリメント */
		iMstChkCnt++;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->sbtkbn     = [%c]", pKanjya->sbtkbn );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->sbtkbn = [%c]", pKkaconvmst->sbtkbn );
#endif

		/* チェック関数のReturn値を設定                   */
		/* チェック対象  ：iRetChk == GD105_CONVCHK_OK(1) */
		/* チェック対象外：iRetChk == GD105_CONVCHK_NG(0) */
		iRetChk = GD105ConvChkSbtkbn( pKanjya->sbtkbn, tmp[0] );
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkSbtkbn iRetChk = [%d]", iRetChk );
#endif

	/* ここまでで条件にHITしない場合、このチェック処理を抜ける */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105ConvChkSbtkbn - HITしないので Return！！" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* ◆ 年齢チェック ◆ */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆◆◆ 年齢チェック ◆◆◆" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->age);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->age ==> tmp = [%s]", tmp );
#endif

	/* 初期化 GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* チェック条件入力ありの場合 */
	if (strlen(tmp) != 0)
	{
		/* マスタにチェック条件入力ありなのでインクリメント */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') かどうか判断する為に退避 */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0          = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->age     = [%s]", pKanjya->age );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->age = [%s]", pKkaconvmst->age );
#endif

		/* チェック関数のReturn値を設定                   */
		/* チェック対象  ：iRet == GD105_CONVCHK_OK(1) */
		/* チェック対象外：iRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkAge( pKanjya->age, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkAge iRet = [%d]", iRet );
#endif

		/* ◆ 年齢区分チェック ◆ */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆◆◆ 年齢区分チェック ◆◆◆" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->agekbn != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->agekbn;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->agekbn ==> tmp = [%s]", tmp );
#endif

		/* チェック条件入力ありの場合 */
		if ( strlen(tmp) != 0 )
		{
			/* マスタにチェック条件入力ありなのでインクリメント */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKanjya->agekbn     = [%c]", pKanjya->agekbn );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->agekbn = [%c]", pKkaconvmst->agekbn );
#endif

			/* チェック関数のReturn値を設定                   */
			/* チェック対象  ：iRetKbn == GD105_CONVCHK_OK(1) */
			/* チェック対象外：iRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkAgekbn( pKanjya->agekbn, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkAgekbn iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"、"!=" の場合は NAND演算(AND演算の反転)する */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"、"=="、"<<"、">>"、"<="、">="の場合は AND演算する */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkAge & Agekbn iRetChk = [%d]", iRetChk );
#endif

	/* ここまでで条件にHITしない場合、このチェック処理を抜ける */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105ConvChkAge & Agekbn - HITしないので Return！！" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* ◆ 身長チェック ◆ */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆◆◆ 身長チェック ◆◆◆" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->sc);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->sc ==> tmp     = [%s]", tmp );
#endif

	/* 初期化 GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* チェック条件入力ありの場合 */
	if (strlen(tmp) != 0)
	{
		/* マスタにチェック条件入力ありなのでインクリメント */
		iMstChkCnt++;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->sc     = [%s]", pKanjya->sc );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->sc = [%s]", pKkaconvmst->sc );
#endif

		/* チェック関数のReturn値を設定                   */
		/* チェック対象  ：iRet == GD105_CONVCHK_OK(1) */
		/* チェック対象外：iRet == GD105_CONVCHK_NG(0) */
		iRetChk = GD105ConvChkSc( pKanjya->sc, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkSc iRetChk = [%d]", iRetChk );
#endif
	}

	/* ここまでで条件にHITしない場合、このチェック処理を抜ける */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105ConvChkSc - HITしないので Return！！" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* ◆ 体重チェック ◆ */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆◆◆ 体重チェック ◆◆◆" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->tj);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->tj ==> tmp = [%s]", tmp );
#endif

	/* 初期化 GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* チェック条件入力ありの場合 */
	if (strlen(tmp) != 0)
	{
		/* マスタにチェック条件入力ありなのでインクリメント */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') かどうか判断する為に退避 */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0         = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKanjya->tj     = [%s]", pKanjya->tj );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tj = [%s]", pKkaconvmst->tj );
#endif

		/* チェック関数のReturn値を設定                   */
		/* チェック対象  ：iRet == GD105_CONVCHK_OK(1) */
		/* チェック対象外：iRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkTj( pKanjya->tj, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTj iRet = [%d]", iRet );
#endif

		/* ◆ 体重区分チェック ◆ */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆◆◆ 体重区分チェック ◆◆◆" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->tjtni != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->tjtni;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tjtni ==> tmp = [%s]", tmp );
#endif

		/* チェック条件入力ありの場合 */
		if ( strlen(tmp) != 0 )
		{
			/* マスタにチェック条件入力ありなのでインクリメント */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKanjya->tjtni     = [%c]", pKanjya->tjtni );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->tjtni = [%c]", pKkaconvmst->tjtni );
#endif

			/* チェック関数のReturn値を設定                   */
			/* チェック対象  ：iRetKbn == GD105_CONVCHK_OK(1) */
			/* チェック対象外：iRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkTjtni( pKanjya->tjtni, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTjtni iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"、"!=" の場合は NAND演算(AND演算の反転)する */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"、"=="、"<<"、">>"、"<="、">="の場合は AND演算する */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTj & Tjtni iRetChk = [%d]", iRetChk );
#endif

	/* ここまでで条件にHITしない場合、このチェック処理を抜ける */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105ConvChkTj & Tjtni - HITしないので Return！！" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* ◆ 蓄尿時間チェック ◆ */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆◆◆ 蓄尿時間チェック ◆◆◆" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->tntme);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->tntme ==> tmp  = [%s]", tmp );
#endif

	/* 初期化 GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* チェック条件入力ありの場合 */
	if (strlen(tmp) != 0)
	{
		/* マスタにチェック条件入力ありなのでインクリメント */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') かどうか判断する為に退避 */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0            = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKenzok->tntme     = [%s]", pKenzok->tntme );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tntme = [%s]", pKkaconvmst->tntme );
#endif

		/* チェック関数のReturn値を設定                */
		/* チェック対象  ：iRet == GD105_CONVCHK_OK(1) */
		/* チェック対象外：iRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkTntme( pKenzok->tntme, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTntme iRet = [%d]", iRet );
#endif

		/* ◆ 蓄尿時間区分チェック ◆ */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆◆◆ 蓄尿時間区分チェック ◆◆◆" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->tntni != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->tntni;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tntni ==> tmp = [%s]", tmp );
#endif

		/* チェック条件入力ありの場合 */
		if ( strlen(tmp) != 0 )
		{
			/* マスタにチェック条件入力ありなのでインクリメント */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKenzok->tntni     = [%c]", pKenzok->tntni );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->tntni = [%c]", pKkaconvmst->tntni );
#endif

			/* チェック関数のReturn値を設定                   */
			/* チェック対象  ：iRetKbn == GD105_CONVCHK_OK(1) */
			/* チェック対象外：iRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkTntni( pKenzok->tntni, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTntni iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"、"!=" の場合は NAND演算(AND演算の反転)する */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"、"=="、"<<"、">>"、"<="、">="の場合は AND演算する */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTn & Tntni iRetChk = [%d]", iRetChk );
#endif

	/* ここまでで条件にHITしない場合、このチェック処理を抜ける */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105ConvChkTn & Tntni - HITしないので Return！！" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/* ◆ 蓄尿量チェック ◆ */
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆◆◆ 蓄尿量チェック ◆◆◆" );
#endif

	memset(tmp, 0, sizeof(tmp));
	GD105Trim(tmp, pKkaconvmst->tnryo);

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmst->tnryo ==> tmp  = [%s]", tmp );
#endif

	/* 初期化 GD105_CONVCHK_SKIP (-1) */
	iRetChk = GD105_CONVCHK_SKIP;

	/* チェック条件入力ありの場合 */
	if (strlen(tmp) != 0)
	{
		/* マスタにチェック条件入力ありなのでインクリメント */
		iMstChkCnt++;

		/* cShiki0 == GD105_EXCLAMATION_MARK ('!') かどうか判断する為に退避 */
		cShiki0 = tmp[0];

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cShiki0            = [%c]", cShiki0 );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKenzok->tnryo     = [%s]", pKenzok->tnryo );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tnryo = [%s]", pKkaconvmst->tnryo );
#endif

		/* チェック関数のReturn値を設定                   */
		/* チェック対象  ：iRet == GD105_CONVCHK_OK(1) */
		/* チェック対象外：iRet == GD105_CONVCHK_NG(0) */
		iRet = GD105ConvChkTnryo( pKenzok->tnryo, tmp );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTnryo iRet = [%d]", iRet );
#endif

		/* ◆ 蓄尿量区分チェック ◆ */
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆◆◆ 蓄尿量区分チェック ◆◆◆" );
#endif

		memset(tmp, 0, sizeof(tmp));
		if (pKkaconvmst->tnryotni != GD105_DATA_SPACE)
		{
			tmp[0] = pKkaconvmst->tnryotni;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvmst->tnryotni ==> tmp = [%s]", tmp );
#endif

		/* チェック条件入力ありの場合 */
		if ( strlen(tmp) != 0 )
		{
			/* マスタにチェック条件入力ありなのでインクリメント */
			iMstChkCnt++;

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKenzok->tnryotni     = [%c]", pKenzok->tnryotni );
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"    pKkaconvmst->tnryotni = [%c]", pKkaconvmst->tnryotni );
#endif

			/* チェック関数のReturn値を設定                   */
			/* チェック対象  ：iRetKbn == GD105_CONVCHK_OK(1) */
			/* チェック対象外：iRetKbn == GD105_CONVCHK_NG(0) */
			iRetKbn = GD105ConvChkTnryotni( pKenzok->tnryotni, tmp[0] );

#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTnryotni iRetKbn = [%d]", iRetKbn );
#endif

			/* "!B"、"!=" の場合は NAND演算(AND演算の反転)する */
			if (cShiki0 == GD105_EXCLAMATION_MARK)
			{
				if ( (iRet & iRetKbn) == GD105_CONVCHK_NG )
				{
					iRetChk = GD105_CONVCHK_OK;
				}
				else
				{
					iRetChk = GD105_CONVCHK_NG;
				}
			}
			/* "BW"、"=="、"<<"、">>"、"<="、">="の場合は AND演算する */
			else
			{
				iRetChk = iRet & iRetKbn;
			}
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"★★★★★★★★★★★★★★★★★★★★ GD105ConvChkTnryo & Tnryotni iRetChk = [%d]", iRetChk );
#endif

	/* ここまでで条件にHITしない場合、このチェック処理を抜ける */
	if ( iRetChk == GD105_CONVCHK_NG )
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105ConvChkTnryo & Tnryotni - HITしないので Return！！" );
#endif

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

		return RTN_SKIP;
	}

	/**************************************************************/
	/*                                                            */
	/* 結果コメント化                                             */
	/* ※ ここまでチェックを通ってきた場合は、更新対象            */
	/*    ただし、1つもチェックを通ってないもの(iMstChkCnt = 0)   */
	/*    は対象外                                                */
	/*                                                            */
	/**************************************************************/
	/* 少なくとも1つはチェックを通ってきた場合 */
	if (iMstChkCnt > 0)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ 結果コメント化処理に入る" );
#endif

		/* 結果変換管理情報テーブル用構造体設定                                        */
		/* ※ コメント化する前に現在の情報を結果変換管理情報テーブル用構造体に格納する */
		memset(&sKkaconvknr, 0, sizeof(sKkaconvknr));
		sKkaconvknr.no = pKkaconvmst->no;							/* 結果変換マスタのNO */

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    sKkaconvknr.no       = [%d]", sKkaconvknr.no );
#endif

		memcpy(sKkaconvknr.hnktntid, cDtnrtts, sizeof(sKkaconvknr.hnktntid));	/* 変更担当者ＩＤ     */

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    sKkaconvknr.hnktntid = [%s]", sKkaconvknr.hnktntid );
#endif

		pKkaconvknr = &sKkaconvknr;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvknr->no       = [%d]", pKkaconvknr->no );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pKkaconvknr->hnktntid = [%s]", pKkaconvknr->hnktntid );

		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105SetKkaconvknr  - 前" );
#endif

		iRet = GD105SetKkaconvknr( pKkaconvknr, pKekka, pKanjya, pKenzok, pSstcd );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105SetKkaconvknr  - 後 (iRet = [%d])", iRet );

		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ dGD105InsKkaconvknr - 前" );
#endif

		/* 結果変換管理情報テーブルにINSERT                                      */
		/* ※ コメント化する前に現在の情報を結果変換管理情報テーブルにINSERTする */
		iRet = dGD105InsKkaconvknr( pKkaconvknr );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ dGD105InsKkaconvknr - 後 (iRet = [%d])", iRet );
#endif

		if ( iRet != HRC_SQL_NORMAL )
		{
			//異常終了
			//ログ出力
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_INS, MYAPP_LOG_ERRCODE_NON,
						"dGD105InsKkaconvknr ERROR [%d]", iRet );

			// ロールバック
			ZdbRollback();

			if (pKanjya != NULL)
			{
				ZbmlFree( pKanjya );
				pKanjya = NULL;
			}

			if (pKenzok != NULL)
			{
				ZbmlFree( pKenzok );
				pKenzok = NULL;
			}

			return RTN_NG;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105SetKekkaConv   - 前" );
#endif

		/* 結果情報テーブル更新用構造体設定     */
		/* ※ pKkaconvmstをpKekkaConvに設定する */
		memset(&sKekkaConv, 0, sizeof(sKekkaConv));
		pKekkaConv = &sKekkaConv;
	
		iRet = GD105SetKekkaConv( pKekkaConv, pKekka, pKkaconvmst, cDtnrtts );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105SetKekkaConv   - 後 (iRet = [%d])", iRet );

		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ dGD105UpdKekkaConv  - 前" );
#endif

		/* 結果テーブルをコメント化する                          */
		/* ※ 結果フィルタ変換された時と同じ状態にUPDATEすること */
		iRet = dGD105UpdKekkaConv( pKekkaConv );

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ dGD105UpdKekkaConv  - 後 (iRet = [%d])", iRet );
#endif

		if ( iRet != HRC_SQL_NORMAL )
		{
			//異常終了
			//ログ出力
			sFncPutLog( TRCKIND_ERROR, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
						"dGD105UpdKekkaConv ERROR [%d]", iRet );

			// ロールバック
			ZdbRollback();

			if (pKanjya != NULL)
			{
				ZbmlFree( pKanjya );
				pKanjya = NULL;
			}

			if (pKenzok != NULL)
			{
				ZbmlFree( pKenzok );
				pKenzok = NULL;
			}

			return RTN_NG;
		}

		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105KkaConvChk - 変換ありで終了" );
#endif

		return RTN_OK;
	}
	/* 1つもチェックを通らなかった場合                                      */
	/* ※ マスタにレコードはあるが、チェック条件が1つも設定されていない場合 */
	else
	{
		if (pKanjya != NULL)
		{
			ZbmlFree( pKanjya );
			pKanjya = NULL;
		}

		if (pKenzok != NULL)
		{
			ZbmlFree( pKenzok );
			pKenzok = NULL;
		}

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105KkaConvChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"● GD105KkaConvChk - 変換なしで終了" );
#endif

		return RTN_SKIP;
	}
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkSbtkbn()										  */
/*　機能概要　：性別区分チェック関数										  */
/*　入　　力　：															  */
/*　　第１引数：char cKanjyaSbtkbn			患者情報の性別区分				  */
/*　　第２引数：char cKkaconvmstSbtkbn		結果変換マスタの性別区分		  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkSbtkbn(char cKanjyaSbtkbn, char cKkaconvmstSbtkbn)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkSbtkbn - 開始" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKanjyaSbtkbn     = [%c]", cKanjyaSbtkbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstSbtkbn = [%c]", cKkaconvmstSbtkbn );
#endif

	if (cKanjyaSbtkbn == cKkaconvmstSbtkbn)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ★ 性別区分でチェック対象になった" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSbtkbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkSbtkbn - 終了" );
#endif

	return iRet;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkAge()											  */
/*　機能概要　：年齢チェック関数											  */
/*　入　　力　：															  */
/*　　第１引数：char *pKanjyaAge			患者情報の年齢					  */
/*　　第２引数：char *pKkaconvmstAge		結果変換マスタの年齢			  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkAge(char *pKanjyaAge, char *pKkaconvmstAge)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* 判定元の値用 */
	char	cTmp2[32+1];	/* 条件式用     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkAge - 開始" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKanjyaAge        = [%s]", pKanjyaAge );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstAge    = [%s]", pKkaconvmstAge );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKanjyaAge);
	/* 判定元がスペースだったら、'@' に変換する */
	/* ※ 基本的に '@' は "==" の場合だけ。     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1に値が入っている場合 */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 開始" );
#endif

		/* cTmp1が数値かどうか判断 */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 終了 iRet = [%d]", iRet );
#endif

		/* cTmp1が数値ではない場合 */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"● pKanjyaAgeが数値ではない - 終了" );
#endif

			/* 何も処理せずチェック対象外として抜ける */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstAge);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* 結果変換マスタ条件式展開 */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* 条件式数値チェック */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAge", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkAge - 終了" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkAgekbn()										  */
/*　機能概要　：年齢区分チェック関数										  */
/*　入　　力　：															  */
/*　　第１引数：char cKanjyaAgekbn			患者情報の年齢区分				  */
/*　　第２引数：char cKkaconvmstAgekbn		結果変換マスタの年齢区分		  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkAgekbn(char cKanjyaAgekbn, char cKkaconvmstAgekbn)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkAgekbn - 開始" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKanjyaAgekbn     = [%c]", cKanjyaAgekbn );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstAgekbn = [%c]", cKkaconvmstAgekbn );
#endif

	if (cKanjyaAgekbn == cKkaconvmstAgekbn)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ★ 年齢区分でチェック対象になった" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkAgekbn", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkAgekbn - 終了" );
#endif

	return iRet;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkSc()											  */
/*　機能概要　：身長チェック関数											  */
/*　入　　力　：															  */
/*　　第１引数：char *pKanjyaSc				患者情報の身長					  */
/*　　第２引数：char *pKkaconvmstSc			結果変換マスタの身長			  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkSc(char *pKanjyaSc, char *pKkaconvmstSc)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* 判定元の値用 */
	char	cTmp2[32+1];	/* 条件式用     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkSc - 開始" );


	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKanjyaSc      = [%s]", pKanjyaSc );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstSc  = [%s]", pKkaconvmstSc );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKanjyaSc);
	/* 判定元がスペースだったら、'@' に変換する */
	/* ※ 基本的に '@' は "==" の場合だけ。     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1に値が入っている場合 */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 開始" );
#endif

		/* cTmp1が数値かどうか判断 */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 終了 iRet = [%d]", iRet );
#endif

		/* cTmp1が数値でない場合 */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"● pKanjyaScが数値でない - 終了" );
#endif

			/* 何も処理せずチェック対象外として抜ける */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstSc);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* 結果変換マスタ条件式展開 */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* 条件式数値チェック */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkSc", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkSc - 終了" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkTj()											  */
/*　機能概要　：体重チェック関数											  */
/*　入　　力　：															  */
/*　　第１引数：char *pKanjyaTj				患者情報の体重					  */
/*　　第２引数：char *pKkaconvmstTj			結果変換マスタの体重			  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkTj(char *pKanjyaTj, char *pKkaconvmstTj)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* 判定元の値用 */
	char	cTmp2[32+1];	/* 条件式用     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTj - 開始" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKanjyaTj        = [%s]", pKanjyaTj );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstTj    = [%s]", pKkaconvmstTj );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKanjyaTj);
	/* 判定元がスペースだったら、'@' に変換する */
	/* ※ 基本的に '@' は "==" の場合だけ。     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1に値が入っている場合 */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 開始" );
#endif

		/* cTmp1が数値かどうか判断 */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 終了 iRet = [%d]", iRet );
#endif

		/* cTmp1が数値でない場合 */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"● pKanjyaTjが数値でない - 終了" );
#endif

			/* 何も処理せずチェック対象外として抜ける */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstTj);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* 結果変換マスタ条件式展開 */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* 条件式数値チェック */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTj", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTj - 終了" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkTjtni()											  */
/*　機能概要　：体重区分チェック関数										  */
/*　入　　力　：															  */
/*　　第１引数：char cKanjyaTjtni			患者情報の体重区分				  */
/*　　第２引数：char cKkaconvmstTjtni		結果変換マスタの体重区分		  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkTjtni(char cKanjyaTjtni, char cKkaconvmstTjtni)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTjtni - 開始" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKanjyaTjtni     = [%c]", cKanjyaTjtni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstTjtni = [%c]", cKkaconvmstTjtni );
#endif

	if (cKanjyaTjtni == cKkaconvmstTjtni)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ★ 体重区分でチェック対象になった" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTjtni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTjtni - 終了" );
#endif

	return iRet;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkTntme()											  */
/*　機能概要　：蓄尿時間チェック関数										  */
/*　入　　力　：															  */
/*　　第１引数：char *pKenzokTntme			検体属性情報の蓄尿時間			  */
/*　　第２引数：char *pKkaconvmstTntme		結果変換マスタの蓄尿時間		  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkTntme(char *pKenzokTntme, char *pKkaconvmstTntme)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* 判定元の値用 */
	char	cTmp2[32+1];	/* 条件式用     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTntme - 開始" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKenzokTntme     = [%s]", pKenzokTntme );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstTntme = [%s]", pKkaconvmstTntme );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKenzokTntme);
	/* 判定元がスペースだったら、'@' に変換する */
	/* ※ 基本的に '@' は "==" の場合だけ。     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1に値が入っている場合 */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 開始" );
#endif

		/* cTmp1が数値かどうか判断 */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 終了 iRet = [%d]", iRet );
#endif

		/* cTmp1が数値でない場合 */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"● pKenzokTntmeが数値でない - 終了" );
#endif

			/* 何も処理せずチェック対象外として抜ける */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstTntme);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* 結果変換マスタ条件式展開 */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* 条件式数値チェック */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntme", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTntme - 終了" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkTntni()											  */
/*　機能概要　：蓄尿時間区分チェック関数									  */
/*　入　　力　：															  */
/*　　第１引数：char cKenzokTntni			患者情報の蓄尿時間区分			  */
/*　　第２引数：char cKkaconvmstTntni		結果変換マスタの蓄尿時間区分	  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkTntni(char cKenzokTntni, char cKkaconvmstTntni)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTntni - 開始" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKenzokTntni     = [%c]", cKenzokTntni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstTntni = [%c]", cKkaconvmstTntni );
#endif

	if (cKenzokTntni == cKkaconvmstTntni)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ★ 蓄尿時間区分でチェック対象になった" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTntni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTntni - 終了" );
#endif

	return iRet;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkTnryo()											  */
/*　機能概要　：蓄尿量チェック関数											  */
/*　入　　力　：															  */
/*　　第１引数：char *pKenzokTnryo			検体属性情報の蓄尿量			  */
/*　　第２引数：char *pKkaconvmstTnryo		結果変換マスタの蓄尿量			  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkTnryo(char *pKenzokTnryo, char *pKkaconvmstTnryo)
{
	Calc	*pCalc = NULL;
	int		iRet;
	int		iRetChk;
	char	cTmp1[5+1];		/* 判定元の値用 */
	char	cTmp2[32+1];	/* 条件式用     */


#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTnryo - 開始" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKenzokTnryo        = [%s]", pKenzokTnryo );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pKkaconvmstTnryo    = [%s]", pKkaconvmstTnryo );
#endif

	iRetChk = 0;

	memset(cTmp1, 0, sizeof(cTmp1));
	memset(cTmp2, 0, sizeof(cTmp2));

	GD105Trim(cTmp1, pKenzokTnryo);
	/* 判定元がスペースだったら、'@' に変換する */
	/* ※ 基本的に '@' は "==" "!=" の場合だけ。     */
	if (cTmp1[0] == GD105_NULL)
	{
		cTmp1[0] = GD105_SPACE_MARK;

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cTmp1          = [%s]", cTmp1 );
#endif
	}
	/* cTmp1に値が入っている場合 */
	else
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 開始" );
#endif

		/* cTmp1が数値かどうか判断 */
		iRet = GD105IsNumeric(cTmp1);

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    GD105IsNumeric - 終了 iRet = [%d]", iRet );
#endif

		/* cTmp1が数値でない場合 */
		if (iRet == 0)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"● pKenzokTnryoが数値でない - 終了" );
#endif

			/* 何も処理せずチェック対象外として抜ける */
			return iRet;
		}
	}

	GD105Trim(cTmp2, pKkaconvmstTnryo);
	pCalc = realloc( pCalc, sizeof(Calc));
	memset(pCalc, 0, sizeof(Calc));

	/* 結果変換マスタ条件式展開 */
	iRet = GD105CalcConv(pCalc, cTmp2);

#ifdef _DEBUG
	if ( iRet == RTN_OK)
	{
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cShiki = [%s]", pCalc->cShiki );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom  = [%s]", pCalc->cFrom );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cTo    = [%s]", pCalc->cTo );
	}
#endif

	/* 条件式数値チェック */
	iRetChk = GD105NumChk( pCalc, cTmp1 );

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ iRetChk = [%d]", iRetChk );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryo", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTnryo - 終了" );
#endif

	return iRetChk;
}

/******************************************************************************/
/*　関 数 名　：GD105ConvChkTnryotni()										  */
/*　機能概要　：蓄尿量区分チェック関数										  */
/*　入　　力　：															  */
/*　　第１引数：char cKenzokTnryotni		患者情報の蓄尿量区分			  */
/*　　第２引数：char cKkaconvmstTnryotni	結果変換マスタの蓄尿量区分		  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105ConvChkTnryotni(char cKenzokTnryotni, char cKkaconvmstTnryotni)
{
	int		iRet;

	iRet = 0;

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTnryotni - 開始" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKenzokTnryotni     = [%c]", cKenzokTnryotni );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    cKkaconvmstTnryotni = [%c]", cKkaconvmstTnryotni );
#endif

	if (cKenzokTnryotni == cKkaconvmstTnryotni)
	{

#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ★ 蓄尿量区分でチェック対象になった" );
#endif

		iRet = 1;
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105ConvChkTnryotni", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105ConvChkTnryotni - 終了" );
#endif

	return iRet;
}

/******************************************************************************/
/*　関 数 名　：GD105SetKkaconvknr()										  */
/*　機能概要　：結果変換管理情報テーブル用構造体設定関数					  */
/*　入　　力　：															  */
/*　　第１引数：Kkaconvknr	*pKkaconvknr	結果変換管理情報				  */
/*　　第２引数：Kekka		*pKekka			結果情報						  */
/*　　第３引数：Kanjya		*pKanjya		患者情報						  */
/*　　第４引数：Kenzok		*pKenzok		検体属性情報					  */
/*　　第５引数：char		*pSstcd			施設コード						  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了(0)									  */
/*　　　　　　		RTN_NG	: 異常終了(-1)									  */
/******************************************************************************/
int GD105SetKkaconvknr(Kkaconvknr *pKkaconvknr, Kekka *pKekka, Kanjya *pKanjya, Kenzok *pKenzok, char *pSstcd)
{
	char	cBuf[2];
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKkaconvknr", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105SetKkaconvknr - 開始" );
#endif

	/* 結果変換管理情報テーブル用構造体設定 */
	memcpy(pKkaconvknr->knskisymd, pKekka->knskisymd, sizeof(pKkaconvknr->knskisymd));		/* 検査開始日     */
	memcpy(pKkaconvknr->sriymd, pKekka->sriymd, sizeof(pKkaconvknr->sriymd));				/* 処理日         */
	memcpy(pKkaconvknr->kntno, pKekka->kntno, sizeof(pKkaconvknr->kntno));					/* 検体No         */
	memcpy(pKkaconvknr->knsgrp, pKekka->knsgrp, sizeof(pKkaconvknr->knsgrp));				/* 検査グループ   */
	memcpy(pKkaconvknr->kmkcd, pKekka->kmkcd, sizeof(pKkaconvknr->kmkcd));					/* 項目コード     */
	pKkaconvknr->knssu = pKekka->knssu;														/* 検査回数       */
	memset(cBuf, 0, sizeof(cBuf));
	sprintf(cBuf, "%c", pKekka->kkassflg);
	pKkaconvknr->hkksu = atoi(cBuf);														/* 報告回数       */
	memcpy(pKkaconvknr->sstcd, pSstcd, sizeof(pKkaconvknr->sstcd));							/* 施設コード     */
	memcpy(pKkaconvknr->utkymd, pKekka->utkymd, sizeof(pKkaconvknr->utkymd));				/* 受付日         */
	memcpy(pKkaconvknr->irino, pKekka->irino, sizeof(pKkaconvknr->irino));					/* 依頼書No       */
	memcpy(pKkaconvknr->knskka1, pKekka->knskka1, sizeof(pKkaconvknr->knskka1));			/* 検査結果１     */
	memcpy(pKkaconvknr->knskka2, pKekka->knskka2, sizeof(pKkaconvknr->knskka2));			/* 検査結果２     */
	memcpy(pKkaconvknr->knskka2kbn, pKekka->knskka2kbn, sizeof(pKkaconvknr->knskka2kbn));	/* 検査結果２区分 */
	memcpy(pKkaconvknr->kkahskcd, pKekka->kkahskcd, sizeof(pKkaconvknr->kkahskcd));			/* 検査結果補足   */
	memcpy(pKkaconvknr->skkka, pKekka->skkka, sizeof(pKkaconvknr->skkka));					/* 照会結果       */
	pKkaconvknr->sbtkbn = pKanjya->sbtkbn;													/* 性別区分       */
	memcpy(pKkaconvknr->age, pKanjya->age, sizeof(pKkaconvknr->age));						/* 年齢           */
	pKkaconvknr->agekbn = pKanjya->agekbn;													/* 年齢区分       */
	memcpy(pKkaconvknr->sc, pKanjya->sc, sizeof(pKkaconvknr->sc));							/* 身長           */
	memcpy(pKkaconvknr->tj, pKanjya->tj, sizeof(pKkaconvknr->tj));							/* 体重           */
	pKkaconvknr->tjtni = pKanjya->tjtni;													/* 体重区分       */
	memcpy(pKkaconvknr->tntme, pKenzok->tntme, sizeof(pKkaconvknr->tntme));					/* 蓄尿時間       */
	pKkaconvknr->tntni = pKenzok->tntni;													/* 蓄尿時間区分   */
	memcpy(pKkaconvknr->tnryo, pKenzok->tnryo, sizeof(pKkaconvknr->tnryo));					/* 蓄尿量         */
	pKkaconvknr->tnryotni = pKenzok->tnryotni;												/* 蓄尿量区分     */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKkaconvknr", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105SetKkaconvknr - 終了" );
#endif

	return RTN_OK;
}

/******************************************************************************/
/*　関 数 名　：GD105SetKekkaConv()											  */
/*　機能概要　：結果情報テーブル更新用構造体設定関数						  */
/*　入　　力　：															  */
/*　　第１引数：KekkaConv	*pKekkaConv		更新用結果情報					  */
/*　　第２引数：Kekka		*pKekka			結果情報						  */
/*　　第３引数：Kkaconvmst	*pKkaconvmst	結果変換マスタ情報				  */
/*　　第４引数：char		*pDtnrtts		データ入力担当者				  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了(0)									  */
/*　　　　　　		RTN_NG	: 異常終了(-1)									  */
/******************************************************************************/
int GD105SetKekkaConv(KekkaConv *pKekkaConv, Kekka *pKekka, Kkaconvmst *pKkaconvmst, char *pDtnrtts)
{
#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKekkaConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105SetKekkaConv - 開始" );
#endif

	/* 更新対象の結果情報キー */
	memcpy(pKekkaConv->knskisymd, pKekka->knskisymd, sizeof(pKekka->knskisymd));	/* 検査開始日       */
	memcpy(pKekkaConv->sriymd, pKekka->sriymd, sizeof(pKekka->sriymd));				/* 処理日           */
	memcpy(pKekkaConv->kntno, pKekka->kntno, sizeof(pKekka->kntno));				/* 検体No           */
	memcpy(pKekkaConv->knsgrp, pKekka->knsgrp, sizeof(pKekka->knsgrp));				/* 検査グループ     */
	memcpy(pKekkaConv->kmkcd, pKekka->kmkcd, sizeof(pKekka->kmkcd));				/* 項目コード       */
	pKekkaConv->knssu = pKekka->knssu;												/* 検査回数         */
	pKekkaConv->knssueda = pKekka->knssueda;										/* 検査回数枝番     */

	/* ファイル作成用構造体更新部分設定 */
	memcpy(pKekka->knskka1, pKkaconvmst->knskka1, sizeof(pKekka->knskka1));						/* 検査結果１       */
	memcpy(pKekka->knskka2, pKkaconvmst->knskka2, sizeof(pKekka->knskka2));						/* 検査結果２       */
	memcpy(pKekka->knskka2kbn, pKkaconvmst->knskka2kbn, sizeof(pKekka->knskka2kbn));			/* 検査結果２区分   */
	memcpy(pKekka->kkahskcd, pKkaconvmst->kkahskcd, sizeof(pKekka->kkahskcd));					/* 検査結果補足     */
//	memcpy(pKekka->dtnrtts, pDtnrtts, sizeof(pKekka->dtnrtts));									/* データ入力担当者 */
	memcpy(pKekka->skkka, pKkaconvmst->hjkka, sizeof(pKekka->skkka));							/* 照会結果         */

	/* テーブル行進用構造体設定 */
	memcpy(pKekkaConv->knskka1, pKkaconvmst->knskka1, sizeof(pKekkaConv->knskka1));				/* 検査結果１       */
	memcpy(pKekkaConv->knskka2, pKkaconvmst->knskka2, sizeof(pKekkaConv->knskka2));				/* 検査結果２       */
	memcpy(pKekkaConv->knskka2kbn, pKkaconvmst->knskka2kbn, sizeof(pKekkaConv->knskka2kbn));	/* 検査結果２区分   */
	memcpy(pKekkaConv->kkahskcd, pKkaconvmst->kkahskcd, sizeof(pKekkaConv->kkahskcd));			/* 検査結果補足     */
	memcpy(pKekkaConv->dtnrtts, pDtnrtts, sizeof(pKekkaConv->dtnrtts));							/* データ入力担当者 */
	memcpy(pKekkaConv->skkka, pKkaconvmst->hjkka, sizeof(pKekkaConv->skkka));					/* 照会結果         */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105SetKekkaConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105SetKekkaConv - 終了" );
#endif

	return RTN_OK;
}

/******************************************************************************/
/*　関 数 名　：GD105CalcConv()												  */
/*　機能概要　：結果変換マスタ条件式展開関数								  */
/*　入　　力　：															  */
/*　　第１引数：Calc *pCalc			条件式を展開した構造体					  */
/*　　第２引数：char *pstrCalc		条件式									  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		RTN_OK	: 正常終了										  */
/*　　　　　　		RTN_NG	: 異常終了										  */
/******************************************************************************/
int GD105CalcConv(Calc *pCalc, char *pstrCalc)
{
	int		iLoopCnt;	/* pstrCalcの文字列長分のループカウンタ */
	int		iCalcCnt;	/*  */
	int		iFromToFlg;	/* cFromに設定か、cToに設定かのフラグ */

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CalcConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105CalcConv - 開始" );
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CalcConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"    pstrCalc      = [%s]", pstrCalc );
#endif

	/* 条件式を設定(BW、==、<<、>=など) */
	memcpy(pCalc->cShiki, pstrCalc, GD105_CALC_KEY); 

	iCalcCnt = 0;
	iFromToFlg = 0;
	for (iLoopCnt = GD105_CALC_KEY; iLoopCnt < strlen(pstrCalc); iLoopCnt++)
	{
		/* 条件式の最後ならループ抜ける */
		if (pstrCalc[iLoopCnt] == GD105_NULL)
		{
			break;
		}
		/* コロンなら(BW、!Bの場合)格納する変数をcFromからcToに切り替える */
		else if (pstrCalc[iLoopCnt] == ':')
		{
			iCalcCnt = 0;
			iFromToFlg = 1;
			continue;
		}
		
		/* 条件式の次の数値を格納(通常はこちらに設定される) */
		if (iFromToFlg == 0)
		{
			pCalc->cFrom[iCalcCnt++] = pstrCalc[iLoopCnt];
		}
		/* "BW"、"!B" の場合のみcToに設定 */
		else
		{
			pCalc->cTo[iCalcCnt++] = pstrCalc[iLoopCnt];
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105CalcConv", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105CalcConv - 終了" );
#endif

	return RTN_OK;
}

/******************************************************************************/
/*　関 数 名　：GD105IsNumeric()											  */
/*　機能概要　：数値判断関数												  */
/*　入　　力　：															  */
/*　　第１引数：const char *pstrTarget	数値チェックする文字列				  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : 数値でない											  */
/*　　　　　　		1 : 数値												  */
/******************************************************************************/
int GD105IsNumeric(const char *pstrTarget)
{
	int nResult = 0;
	int nIndex;

	/* pstrTargetが数値かどうか判断する */
	if (NULL != (void *) pstrTarget)
	{
		/* Trim start         */
		for (nIndex = 0; isspace(*(pstrTarget + nIndex)); nIndex++);

		if ((int) *(pstrTarget + nIndex) == '-')
		{
			for (++nIndex; isspace(*(pstrTarget + nIndex)); nIndex++);
		}

		/* Integer part       */
		for ( ; isdigit(*(pstrTarget + nIndex)); nIndex++);

		if ((int) *(pstrTarget + nIndex) == '.')
		{
			/* uner decimal point */
			for (++nIndex; isspace(*(pstrTarget + nIndex)); nIndex++);
		}

		/* Trim end           */
		for ( ; isspace(*(pstrTarget + nIndex)); nIndex++);

		if ((int) *(pstrTarget + nIndex) == GD105_NULL)
		{
			nResult = 1;
		}
	}

	return nResult;
}

/******************************************************************************/
/*　関 数 名　：GD105NumChk()												  */
/*　機能概要　：条件式数値チェック関数										  */
/*　入　　力　：															  */
/*　　第１引数：Calc *pCalc			条件式を展開した構造体					  */
/*　　第２引数：char *pstrNum		比較文字列								  */
/*　出　　力　：なし														  */
/*　復帰情報　：int															  */
/*　　　　　　		0 : チェック条件対象外									  */
/*　　　　　　		1 : チェック条件対象									  */
/******************************************************************************/
int GD105NumChk(Calc *pCalc, char *pstrNum)
{
	int		iRetChk = 0;
	char	cBuf[15+1];

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105NumChk - 開始" );

	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"  ◆ pstrNum = [%s]", pstrNum );
#endif

	/* 一時領域に退避 */
	memset(cBuf, 0, sizeof(cBuf));
	sprintf(cBuf, "%s", pstrNum);

	/* ◆ 範囲指定の場合 || 範囲指定以外 ◆ */
	if (memcmp(pCalc->cShiki, "BW", sizeof(pCalc->cShiki) - 1) == 0 || memcmp(pCalc->cShiki, "!B", sizeof(pCalc->cShiki) - 1) == 0)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105NumChk - [BW || !B] でチェック" );
		if (memcmp(pCalc->cShiki, "BW", sizeof(pCalc->cShiki) - 1) == 0)
		{
			if (cBuf[0] == GD105_SPACE_MARK)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    pCalc->cFrom[%d] <= cBuf[%c] <= pCalc->cTo[%d] ??",
							atoi(pCalc->cFrom), cBuf[0], atoi(pCalc->cTo) );
			}
			else
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    pCalc->cFrom[%d] <= cBuf[%d] <= pCalc->cTo[%d] ??",
							atoi(pCalc->cFrom), atoi(cBuf), atoi(pCalc->cTo) );
			}
		}
		else
		{
			if (cBuf[0] == GD105_SPACE_MARK)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    cBuf[%c] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%c] ??",
							cBuf[0], atoi(pCalc->cFrom), atoi(pCalc->cTo), cBuf[0] );
			}
			else
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"    cBuf[%d] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%d] ??",
							atoi(cBuf), atoi(pCalc->cFrom), atoi(pCalc->cTo), atoi(cBuf) );
			}
		}
#endif

		if (cBuf[0] == GD105_SPACE_MARK)
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  ◆ iRetChk = 0 を設定" );
#endif
			iRetChk = 0;
		}
		else if ( (atoi(pCalc->cFrom) <= atoi(cBuf)) && (atoi(cBuf) <= atoi(pCalc->cTo)) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  ◆ iRetChk = 1 を設定" );
#endif

			/* チェック条件対象 */
			iRetChk = 1;
		}

#ifdef _DEBUG
		if (memcmp(pCalc->cShiki, "BW", sizeof(pCalc->cShiki) - 1) == 0)
		{
			if (iRetChk == 1)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  ★ GD105NumChk - [BW] でチェック対象になった" );
			}
		}
		else
		{
			if (iRetChk == 0)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  ★ GD105NumChk - [!B] でチェック対象になった" );
			}
		}
#endif
	}
//	/* ◆ 範囲指定以外の場合 ◆ */
//	else if (memcmp(pCalc->cShiki, "!B", sizeof(pCalc->cShiki) - 1) == 0)
//	{
//#ifdef _DEBUG
//		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					"  ◆ GD105NumChk - [!B] でチェック" );
//		if (cBuf[0] == GD105_SPACE_MARK)
//		{
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"    cBuf[%c] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%c] ??",
//						cBuf[0], atoi(pCalc->cFrom), atoi(pCalc->cTo), cBuf[0] );
//		}
//		else
//		{
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"    cBuf[%d] < pCalc->cFrom[%d] || pCalc->cTo[%d] < cBuf[%d] ??",
//						atoi(cBuf), atoi(pCalc->cFrom), atoi(pCalc->cTo), atoi(cBuf) );
//		}
//#endif
//
//		/* cBuf が '@' の場合 */
//		if (cBuf[0] == GD105_SPACE_MARK)
//		{
//#ifdef _DEBUG
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"  ★ GD105NumChk - [!B] でチェック対象になった" );
//#endif
//
//			/* チェック条件対象 */
//			iRetChk = 1;
//		}
//		/* cBuf が数値の場合 */
//		else if ( (atoi(cBuf) < atoi(pCalc->cFrom)) || (atoi(pCalc->cTo) < atoi(cBuf)) )
//		{
//#ifdef _DEBUG
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"  ★ GD105NumChk - [!B] でチェック対象になった" );
//#endif
//
//			/* チェック条件対象 */
//			iRetChk = 1;
//		}
//	}
	/* ◆ 等しい場合 || 等しくない場合 ◆ */
	else if (memcmp(pCalc->cShiki, "==", sizeof(pCalc->cShiki) - 1) == 0 || memcmp(pCalc->cShiki, "!=", sizeof(pCalc->cShiki) - 1) == 0)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105NumChk - [== || !=] でチェック" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    pCalc->cFrom[%s] == cBuf[%s] ?? || pCalc->cFrom[%s] != cBuf[%s] ??",
					pCalc->cFrom, cBuf, pCalc->cFrom, cBuf );
#endif

		if ( memcmp(pCalc->cFrom, cBuf, sizeof(cBuf)) == 0 )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  ★ GD105NumChk - [==] でチェック対象になった" );
#endif

			/* チェック条件対象 */
			iRetChk = 1;
		}
#ifdef _DEBUG
		if (memcmp(pCalc->cShiki, "==", sizeof(pCalc->cShiki) - 1) == 0)
		{
			if (iRetChk == 1)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  ★ GD105NumChk - [==] でチェック対象になった" );
			}
		}
		else
		{
			if (iRetChk == 0)
			{
				sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
							"  ★ GD105NumChk - [!=] でチェック対象になった" );
			}
		}
#endif
	}
//	/* ◆ 等しくない場合 ◆ */
//	else if (memcmp(pCalc->cShiki, "!=", sizeof(pCalc->cShiki) - 1) == 0)
//	{
//#ifdef _DEBUG
//		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					"  ◆ GD105NumChk - [!=] でチェック" );
//		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//					"    pCalc->cFrom[%s] != cBuf[%s] ??", pCalc->cFrom, cBuf );
//#endif
//
//		if ( memcmp(pCalc->cFrom, cBuf, sizeof(cBuf)) != 0 )
//		{
//#ifdef _DEBUG
//			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
//						"  ★ GD105NumChk - [!=] でチェック対象になった" );
//#endif
//
//			/* チェック条件対象 */
//			iRetChk = 1;
//		}
//	}
	/* ◆ より大きい場合(ただし、'@'ではない場合) ◆ */
	else if (memcmp(pCalc->cShiki, ">>", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105NumChk - [>>] でチェック" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] > pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif

		if ( atoi(pCalc->cFrom) < atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  ★ GD105NumChk - [>>] でチェック対象になった" );
#endif

			/* チェック条件対象 */
			iRetChk = 1;
		}
	}
	/* ◆ 未満の場合(ただし、'@'ではない場合) ◆ */
	else if (memcmp(pCalc->cShiki, "<<", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105NumChk - [<<] でチェック" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] < pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif


		if ( atoi(pCalc->cFrom) > atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  ★ GD105NumChk - [<<] でチェック対象になった" );
#endif

			/* チェック条件対象 */
			iRetChk = 1;
		}
	}
	/* ◆ 以上の場合(ただし、'@'ではない場合) ◆ */
	else if (memcmp(pCalc->cShiki, ">=", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105NumChk - [>=] でチェック" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] >= pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif

		if ( atoi(pCalc->cFrom) <= atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  ★ GD105NumChk - [>=] でチェック対象になった" );
#endif

			/* チェック条件対象 */
			iRetChk = 1;
		}
	}
	/* ◆ 以下の場合(ただし、'@'ではない場合) ◆ */
	else if (memcmp(pCalc->cShiki, "<=", sizeof(pCalc->cShiki) - 1) == 0 && cBuf[0] != GD105_SPACE_MARK)
	{
#ifdef _DEBUG
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"  ◆ GD105NumChk - [<=] でチェック" );
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
					"    cBuf[%d] <= pCalc->cFrom[%d] ??", atoi(cBuf), atoi(pCalc->cFrom) );
#endif

		if ( atoi(pCalc->cFrom) >= atoi(cBuf) )
		{
#ifdef _DEBUG
			sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						"  ★ GD105NumChk - [<=] でチェック対象になった" );
#endif

			/* チェック条件対象 */
			iRetChk = 1;
		}
	}

#ifdef _DEBUG
	sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105NumChk", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				"● GD105NumChk - 終了 iRetChk = [%d]", iRetChk );
#endif

	return iRetChk;
}

/******************************************************************************/
/*　関 数 名　：GD105Trim()													  */
/*　機能概要　：指定文字列の前後のスペースを取り除いて文字列をコピーする	  */
/*　入　　力　：															  */
/*　　第１引数：char *dst		Trim後の文字列								  */
/*　　第２引数：char *src		Trim前の文字列								  */
/*　出　　力　：なし														  */
/*　復帰情報　：なし														  */
/******************************************************************************/
void GD105Trim(char *dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0; src[srcCnt] != GD105_NULL; srcCnt ++)
	{
		/* srcの左側がスペースの場合、文字が見つかるまで進む */
		if ((dstCnt == 0) && (src[srcCnt] == '\x20'))
		{
			continue;
		}

		dst[dstCnt++] = src[srcCnt];

		if (src[srcCnt] != '\x20')
		{
			Flg = dstCnt;
		}
	}

	/* 最後に '\0' を付ける                                        */
	/* ※ srcが全てスペースの場合、dstはNULL(dst[0] == '\0')となる */
	dst[Flg] = GD105_NULL;
}
