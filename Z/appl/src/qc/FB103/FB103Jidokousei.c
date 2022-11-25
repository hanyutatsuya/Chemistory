/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：FB103Jidokousei.c								*/
/*		概要		：自動校正処理									*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/27		J.Iijima		Create					*/
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include "FB103Jidokousei.h"

/********************************************************************/
/*	関数名		：kekkaUpdate()										*/
/*	機能概要	：検査結果情報更新									*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv		プログラム管理構造体		*/
/*	 第２引数   ：Ctrlkka*	pCtrlkka	コントロール結果管理情報	*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
kekkaUpdate
(
	 PENV		pEnv
	,Ctrlkka*	pCtrlkka
)
{
	/*
	*	ローカル変数定義
	*/
	Kekka		key;
	Kekka*		arrayOut;
	int			numOut;
	int			index;
	int			rc;
	double		factor;
	double		base;
	double		kouiseiKekka;

	//プログラム開始ログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_NON,  "Start Function");

	/*
	*	初期化
	*/
	factor	= atof(pCtrlkka->facter);	
	base	= atof(pCtrlkka->base); 


	/*
	*	検査結果情報更新処理
	*/
	
	//検索条件をセット
	memset(&key, 0, sizeof(Kekka));
	strcpy(key.knskisymd, pCtrlkka->knskisymd);
	strcpy(key.knsgrp, pCtrlkka->knsgrp);
	strcpy(key.kmkcd, pCtrlkka->kmkcd);
	strcpy(key.bskkbn, pCtrlkka->bskkbn);
	strcpy(key.bsklne, pCtrlkka->bsklne);
	strcpy(key.bskgok, pCtrlkka->bskgok);
	key.bskseq = pCtrlkka->bskseq;
	key.ctrlno = pCtrlkka->ctrlno;

	//検査結果情報を検索
	rc = FKekkaSelectByKey(&key, &arrayOut, &numOut);
	if(rc == HRC_SQL_NOT_FOUND)
	{
		//該当データが無い場合
		mcrPutTrace(pEnv, TRCKIND_TRACE, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_NON,  "自動校正対象のデータはありません。");
		return(ERROR_CODE_NORMAL);

	}
	else if(rc != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_DB,  "検査結果情報の検索に失敗しました。");
		return(ERROR_DB_ERROR);
	}
	
	for(index = 0; index < numOut; index++)
	{
		//校正結果を計算
		//	コントロール結果情報のファクター × 検査結果情報の生データ ＋ コントロール結果情報のベース
		kouiseiKekka = factor * atof(arrayOut[index].rawdata) + base;

		//検査結果情報を更新
		snprintf(arrayOut[index].knskka1, 12, "%f", kouiseiKekka);
		rc = FKnskkaUpdate(&arrayOut[index]);
		if(rc != 0)
		{
			mcrPutTrace(pEnv, TRCKIND_ERROR, "kekkaUpdate", "", MYAPP_LOG_ERRCODE_DB,  "検査結果情報の更新に失敗しました。");
			ZbmlFree(arrayOut);
			return(ERROR_DB_ERROR);
		}
	}

	ZbmlFree(arrayOut);

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	関数名		：ctrlknrUpdate()									*/
/*	機能概要	：コントロール管理情報更新							*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv		プログラム管理構造体		*/
/*	 第２引数   ：Ctrlkka*	pCtrlkka	コントロール結果管理情報	*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
ctrlknrUpdate
(
	 PENV		pEnv
	,Ctrlkka*	pCtrlkka
)
{
	/*
	*	ローカル変数定義
	*/
	Ctrlknr		key;
	int			rc;

	//トレース出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "ctrlknrUpdate", "", MYAPP_LOG_ERRCODE_NON,  "Start Function");

	/*
	*	コントロール管理情報更新処理
	*/
	
	//検索条件をセット
	memset(&key, 0, sizeof(Ctrlknr));
	strcpy(key.knskisymd, pCtrlkka->knskisymd);
	strcpy(key.bskkbn, pCtrlkka->bskkbn);
	strcpy(key.bskgok, pCtrlkka->bskgok);
	key.ctrlno = pCtrlkka->ctrlno;

	//更新
	rc = FKtflgUpdate(&key);
	if(rc != 0 && rc != HRC_SQL_NOT_FOUND)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "ctrlknrUpdate", "", MYAPP_LOG_ERRCODE_DB,  "コントロール管理情報の更新に失敗しました。");
		return(ERROR_DB_ERROR);
	}

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	関数名		：jidouKousei()										*/
/*	機能概要	：自動校正処理										*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv	プログラム管理構造体			*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
jidouKousei
(
	PENV	pEnv
)
{
	/*
	*	ローカル変数定義
	*/
	Ctrlkka*	arrayOut;
	int			numOut;
	int			index;
	int			rc;

	//トレース出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "jidouKousei", "", MYAPP_LOG_ERRCODE_NON,  "Start Function");

	/*
	*	初期化
	*/
	
	/*
	*	コントロール結果情報テーブル検索
	*/
	rc = FCtrlkkkaSelectAll(&arrayOut, &numOut);
	if(rc == HRC_SQL_NOT_FOUND)
	{
		//該当データが無い場合
		mcrPutTrace(pEnv, TRCKIND_TRACE, "jidouKousei", "", MYAPP_LOG_ERRCODE_NON,  "自動校正対象のデータはありません。");
		return(ERROR_CODE_NORMAL);

	}
	else if(rc != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "jidouKousei", "", MYAPP_LOG_ERRCODE_DB,  "コントロール情報の検索に失敗しました。");
		return(ERROR_DB_ERROR);
	}

	/*
	*	校正情報更新
	*/
	for(index = 0; index < numOut; index++)
	{
		//検査結果情報を更新
		rc = kekkaUpdate(pEnv, &arrayOut[index]);
		if(rc != 0)
		{
			ZbmlFree(arrayOut);
			return(rc);		
		}

		//コントロール管理テーブル更新
		rc = ctrlknrUpdate(pEnv, &arrayOut[index]);
		if(rc != 0)
		{
			ZbmlFree(arrayOut);
			return(rc);		
		}

		//コントロール結果情報テーブル更新
		rc = FKsidhUpdate(&arrayOut[index]);
		if(rc != 0)
		{
			ZbmlFree(arrayOut);
			return(rc);		
		}
	}

	ZbmlFree(arrayOut);

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	関数名		：initFunction()									*/
/*	機能概要	：初期化処理										*/
/* 	入力		：													*/
/*	 第１引数   ：int		argc	パラメータ数					*/
/*	 第２引数	：char**	argv	パラメータ値					*/
/*	 第３引数   ：PENV		pEnv	プログラム管理構造体			*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
initFunction
(
	 int	argc
	,char**	argv
	,PENV	pEnv
)
{
	/*
	*	ローカル変数定義
	*/
	int		rc;


	/*
	*	初期化
	*/

	//プログラム管理構造体初期化
	memset(pEnv, 0, sizeof(ENV));

	//ログファイルオープン
	rc = ZbmlOpenLog(LOGINIFILE);
	if(rc != 0)
	{
		return(ERROR_CODE_LOG_OPEN_ERROR);
	}
	
	//ログ情報初期化設定
    memset(&pEnv->stLogMem, '\0', sizeof(pEnv->stLogMem)) ;
	
	//プログラム名セット
	strcpy(pEnv->stLogMem.pcAppName, APP_NAME);

	//プログラム開始ログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "自動校正処理起動");

	//コマンドライン引数チェック
	//	※第2引数にパラメータファイルのパスが入力されていなければエラー
	if(argc != 2)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "コマンドライン引数が不正です。");
		return(ERROR_CODE_CMD_PRM_ERROR);
	}

	//パラメータファイルオープン
	pEnv->bp = ZbmlPrmOpen(argv[1]) ;
	if(pEnv->bp == NULL)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "パラメータファイルのオープンに失敗しました。");
		return(ERROR_CODE_PRM_OPEN_ERROR);
	}
	
	/*
	*	パラメータ取得
	*/
	
	//データベース名取得
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_NAME, pEnv->cDbName) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//ＤＢユーザＩＤ取得
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_USER_ID, pEnv->cDbUserId) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//ＤＢパスワード取得
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_PASSWORD, pEnv->cDbPassword) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}

	//パラメータファイルクローズ	
	ZbmlPrmClose(pEnv->bp);

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	関数名		：mainFunction()									*/
/*	機能概要	：メイン処理										*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv	プログラム管理構造体			*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
mainFunction
(
	PENV	pEnv
)
{
	/*
	*	ローカル変数定義
	*/
	int		rc;

	//トレースログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "mainFunction", "T", MYAPP_LOG_ERRCODE_NON,  "Start Function.");
	
	/*
	*	初期化
	*/
	
	
	/*
	*	自動校正処理
	*/
	rc = jidouKousei(pEnv);
	if(rc)
	{
		//ロールバック
		ZdbRollback();

		mcrPutTrace(pEnv, TRCKIND_ERROR, "mainFunction", "", MYAPP_LOG_ERRCODE_NON,  "自動校正処理に失敗しました。");
		return(ERROR_FUNC_ERROR);
	}
	
	//コミット
	ZdbCommit();

	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	関数名		：endFunction()										*/
/*	機能概要	：終了処理											*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv	プログラム管理構造体			*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
endFunction
(
	PENV	pEnv
)
{
	/*
	*	ローカル変数定義
	*/

	//トレースログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "endFunction", "", MYAPP_LOG_ERRCODE_NON,  "Start Function.");

	/*
	*	初期化
	*/


	return(ERROR_CODE_NORMAL);
}

/********************************************************************/
/*	関数名		：main()											*/
/*	機能概要	：自動校正処理メイン								*/
/* 	入力		：													*/
/*	 第１引数   ：int		argc	パラメータ数					*/
/*	 第２引数	：char**	argv	パラメータ値					*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：1以上													*/
/********************************************************************/
int 
main
(
	 int	argc
	,char** argv
)
{
	/*
	*	ローカル変数定義
	*/
	ENV		Env;	
	int		rc;

	/*
	*	初期化処理
	*/
	rc = initFunction(argc, argv, &Env);
	if(rc != ERROR_CODE_NORMAL)
	{
		fprintf(stderr, "jidokousei : Error initFunction [%d]\n", rc);
		return(rc);
	}

	/*
	*	データベース接続
	*/
	rc = ZdbConnect(Env.cDbName, Env.cDbUserId, Env.cDbPassword);
	if(rc != 0)
	{
		mcrPutTrace(&Env, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,  "データベースの接続に失敗しました。");
		return(ERROR_CODE_DB_CONNECT_ERROR);
	}

	/*
	*	メイン処理
	*/
	rc = mainFunction(&Env);
	if(rc != ERROR_CODE_NORMAL)
	{
		//データベース切断
		ZdbDisConnect();
		fprintf(stderr, "jidokousei : Error mainFunction [%d]\n", rc);
		return(rc);
	}
	//データベース切断
	ZdbDisConnect();
	
	/*
	*	終了処理
	*/
	rc = endFunction(&Env);
	if(rc != ERROR_CODE_NORMAL)
	{
		fprintf(stderr, "jidokousei : Error endFunction [%d]\n", rc);
		return(rc);
	}

	return(ERROR_CODE_NORMAL);
}
/** End of File ***************************************************************/
