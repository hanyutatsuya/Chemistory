/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：FD101IjouChk.c								*/
/*		概要		：精度管理異常チェック							*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/27		J.Iijima		Create					*/
/*  1.01	2006/04/20		INTEC   		Update基準処理日読み込み*/
/*                                          SHM-KEY、構造体見直し   */
/*  1.02    2006/12/15      INTEC           SELECT失敗する時続く　  */
/********************************************************************/

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <sys/ipc.h>					// 1.01 INTEC ADD
#include <sys/shm.h>					// 1.01 INTEC ADD
#include <errno.h>						// 1.01 INTEC ADD
#include "bml_base.h"
#include "FD101IjouChk.h"

//ループ制御用フラグ(0:ループ停止、1:ループ継続)
static int gloopFlag;

/********************************************************************/
/*	関数名		：handleSignal()									*/
/*	機能概要	：ループの終了要求をセット							*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv	プログラム管理構造体			*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
void
handleSignal
(
	int sig 
)
{
	gloopFlag = 0;
}

/********************************************************************/
/*	関数名		：sleepFunction()									*/
/*	機能概要	：指定秒数スリープ									*/
/* 	入力		：													*/
/*	 第１引数   ：													*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
void
sleepFunction
(
	int second
)
{
	int cnt;

	//トレースログ出力
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sleepFunction", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//プロセスの終了要求に対応するため
	//１秒ごとにスリープする
	for(cnt = 0; cnt < second; cnt++)
	{
		if(gloopFlag == 0)
		{
			return;
		}

		sleep(1);
	}
}

/*:KH-------------------------------------------------------------------------*/
/*:K  関数名   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  機能概要 : ＄環境変数を展開する                                         */
/*----------------------------------------------------------------------------*/
/*:I  入力     : char    *src_cp  : 展開前文字列                              */
/*:O  出力     : 無し             : 無し                                      */
/*:R  戻り値   : char *           : 展開後文字列                              */
/*:C  特記事項 :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char		*src_cp;
{
static char	value[256];     			/* 展開後文字列 */
    char	*dst_cp;        			/* 展開後文字列 */
    char	buf[256];       			/* ＄環境変数 */
    char	*env_cp;        			/* ＄環境変数 */

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0 
                && *src_cp != ' ' && *src_cp != '\t' 
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

    return( value );
}

/******************************************************************************/
/*  関 数 名　：sFncShmCrt()				 								  */
/*  機能概要　：共有メモリ生成								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *   	共有メモリ構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int		sFncShmCrt ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;

	//トレースログ出力
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sFncShmCrt", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//	取得
	stcShm->shm_Id = shmget ( (key_t)stcShm->shm_Key, 
					MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
	if ( stcShm->shm_Id < 0 ) {
		//	異常終了	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "共有メモリの取得(shmget)に失敗しました。");
		return ( RTN_NG ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
		 MYAPP_LOG_ERRCODE_APP,"共有メモリのアタッチ(shmat)に失敗しました。");
		return ( RTN_NG ) ;
	}

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "共有メモリの値設定(shmdt)に失敗しました。");
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmGet()				 								  */
/*  機能概要　：共有メモリ取得								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *   	共有メモリ構造体                          */
/*　 第２引数 ：int *   				値							 	      */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int		sFncShmGet ( stcShm, pshmData )
struct		SHM		*stcShm;
int			*pshmData ;
{
	int		*shmData ;

	//トレースログ出力
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sFncShmGet", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//	アタッチ	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "共有メモリの操作(shmget)に失敗しました。");
		return ( RTN_NG ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "共有メモリの操作(shmget)に失敗しました。");
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  関 数 名　：sFncShmDel()				 								  */
/*  機能概要　：共有メモリ削除								  	 			  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct stcShm *   	共有メモリ構造体                          */
/*  出　　力　：                                                              */
/*  復帰情報　：int															  */
/*					 0	正常												  */
/*					-1	異常												  */
/******************************************************************************/
int		sFncShmDel ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;

	//トレースログ出力
	mcrPutTrace( &stEnv, TRCKIND_TRACE, "sFncShmDel", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	//	削除	
	if ( shmctl ( stcShm->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		mcrPutTrace( &stEnv, TRCKIND_WARNING, "sFncShmCrt", "", 
			MYAPP_LOG_ERRCODE_APP, "共有メモリの操作(shmget)に失敗しました。");
		return ( RTN_NG ) ;
	}
	return ( RTN_OK ) ;
}

/********************************************************************/
/*	関数名		：checkCtrljti()									*/
/*	機能概要	：コントロール状態チェック							*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv	プログラム管理構造体			*/
/*	 第２引数	：Ctrlkka*	pCtrlkka								*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
checkCtrljti
(
	 PENV		pEnv
	,Ctrlkka*	pCtrlkka
)
{
	/*
	*	ローカル変数定義
	*/
	Ctrlijhmst		key;
	Ctrlijhmst*		arrayOut;
	int				numOut;
	int				rc;
	int				kyoyosu;
	
	//トレースログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "checkCtrljti", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

	memset(&key, 0, sizeof(Ctrlijhmst));
	strcpy(key.bskkbn, pCtrlkka->bskkbn);
	strcpy(key.nbkmkcd, pCtrlkka->nbkmkcd);
	strcpy(key.kaiymd, pCtrlkka->knskisymd);		// 1.01 INTEC ADD
	
	rc = FCtrlijhmstSelectByKey(&key, &arrayOut, &numOut);

	if(rc != 0){
		{
			char	buf[1024];
			memset(buf, '\0', sizeof( buf ));
			sprintf(buf, "コントロール異常判定マスタの検索に失敗しました。"
						"分析機区分：%s 内部項目コード%s ret[%d]", 
					key.bskkbn, key.nbkmkcd, rc);
			mcrPutTrace(pEnv, TRCKIND_WARNING, "checkCtrljti", "", 
				MYAPP_LOG_ERRCODE_DB, buf);
		}
		
		return(rc);
	}
	
	/*
	*	コントロール結果情報のコントロール状態コントロール異常判定マスタの
	*	許容範囲外の場合は、コントロール異常にする。
	*/
	kyoyosu = atoi(&arrayOut->kyuhniflg);
	if( kyoyosu < abs(pCtrlkka->ctrljti) ){
		return(CV_ABNORMAL);
	}
	
	ZbmlFree(arrayOut);
	
	return(CV_NORMAL);
}


/********************************************************************/
/*	関数名		：checkSeidoKanri()									*/
/*	機能概要	：精度管理異常チェック								*/
/* 	入力		：													*/
/*	 第１引数   ：PENV		pEnv	プログラム管理構造体			*/
/*	出力		：													*/
/*   正常：0														*/
/*	 異常：0以外													*/
/********************************************************************/
int
checkSeidoKanri
(
	PENV	pEnv
)
{
	/*
	*	ローカル変数定義
	*/
	Ctrlkka*		arrayOut;
	int				numOut;
	int				rc;
	int				index;
	char			buf[256];
	
	/*
	*	初期化
	*/
	//トレースログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
		MYAPP_LOG_ERRCODE_NON, "Start Function.");

/* 1.01 INTEC DELL SELECT MAX はiniファイル設定に
DEL	rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, 100);
*/
	rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, pEnv->sel_Max);
	if(rc == 100){
		mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
			MYAPP_LOG_ERRCODE_NON, "該当データがありません。");
		// 1.01 ADD INTEC	念のためにfree
		if( arrayOut != NULL ){
			free( arrayOut );
		}

		return(ERROR_CODE_NORMAL);
	}
	else if(rc != 0){
		//トレースログ出力

		//==> 2007.01.09 Kim Jinsuk SQLCODE 出力 
		sprintf(buf, "SQLCODE [%d] コントロール結果情報の検索に失敗しました", rc);
		mcrPutTrace(pEnv, TRCKIND_ERROR, "checkSeidoKanri", "", 
			MYAPP_LOG_ERRCODE_DB,buf);
		//mcrPutTrace(pEnv, TRCKIND_ERROR, "checkSeidoKanri", "", 
		//	MYAPP_LOG_ERRCODE_DB,"コントロール結果情報の検索に失敗しました。");
		//<== 2007.01.09 Kim Jinsuk SQLCODE	出力	

		// 1.01 ADD INTEC	念のためにfree
		//==> 2006.12.15 Kim Jinsuk SELECT　失敗する時　続く
		if( arrayOut != NULL ){
			free( arrayOut );
		}
		//<== 2006.12.15 Kim Jinsuk SELECT　失敗する時　続く
		
		return(rc);
	}
	
	do{
		
		for(index=0; index<numOut; index++){
			
			/*
			*	コントロール異常判定マスタを、分析機区分・内部項目コードで
			*	検索し、許容範囲フラグを判定する。
			*/
			rc = checkCtrljti(pEnv, &arrayOut[index]);

			if(rc == CV_NORMAL){
				/* チェック済み */
				arrayOut[index].chkzmflg	= '1';
			}
			else{
				/* コントロール異常 */
				arrayOut[index].chkzmflg	= '2';
			}
			
			// INTEC ADD DEBUG LOG OUT
//			sprintf(buf,"index[%d] --->許容範囲フラグ判定 rc[%d] flg[%c]"
//					,index,rc,arrayOut[index].chkzmflg );
//			mcrPutTrace(pEnv, TRCKIND_DEBUG, "checkSeidoKanri", "", 
//					MYAPP_LOG_ERRCODE_NON,buf );

			/* コントロール結果情報更新 */
			rc = FCtrlUpdate(&arrayOut[index]);
			if(rc != 0){
				// 1.01 INTEC ADD LOG OUT
				memset( buf, '\0', sizeof( buf ));
				sprintf( buf, "コントロール結果情報の更新に失敗しました。"
					"開始日[%s]分析機[%s]号機[%s]項目[%s]CTRLNO[%d]"
					, arrayOut[index].knskisymd	,arrayOut[index].bskkbn
					, arrayOut[index].bskgok	,arrayOut[index].kmkcd
					, arrayOut[index].ctrlno );
				mcrPutTrace(pEnv, TRCKIND_WARNING, "checkSeidoKanri", "", 
						MYAPP_LOG_ERRCODE_NON, buf );
				// mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
				//		MYAPP_LOG_ERRCODE_NON, 
				//		"コントロール結果情報の更新に失敗しました。");

				// 1.01 INTEC DEL １件失敗しても処理を継続
				// ZbmlFree(arrayOut);
				continue;
			}
			
			//コミット
			ZdbCommit();
			
		}

		ZbmlFree(arrayOut);

/* 1.01 INTEC DELL		
DEL		rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, 100);
*/
		rc = FCtrlkkaSelectByKey(&arrayOut, &numOut, pEnv->sel_Max);
		if(rc == 100){
			mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
				MYAPP_LOG_ERRCODE_NON, "該当データがありません。");
			// 1.01 ADD INTEC	念のためにfree
			
			if( arrayOut != NULL ){
				free( arrayOut );
			}
			break;
		}
		else if(rc != 0){

			//==> 2007.01.09 Kim Jinsuk SQLCODE 出力
			//トレースログ出力
			sprintf(buf, "SQLCODE [%d] コントロール結果情報の検索に失敗しました。", rc);
			mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
				MYAPP_LOG_ERRCODE_NON, buf); 
			
			//mcrPutTrace(pEnv, TRCKIND_TRACE, "checkSeidoKanri", "", 
			//	MYAPP_LOG_ERRCODE_NON, 
			//	"コントロール結果情報の検索に失敗しました。");
			// 1.01 ADD INTEC	念のためにfree
			//<== 2007.01.09 Kim Jinsuk SQLCODE 出力

			//==> 2006.12.15 Kim Jinsuk SELECT 失敗するとき　続き
			if( arrayOut != NULL ){
				free( arrayOut );
			}
			//<== 2006.12.15 Kim Jinsuk SELECT 失敗するとき　続き

			return(rc);
		}

	} while(!rc);

	// 1.01 ADD INTEC	念のためにfree
	if( arrayOut != NULL ){
		free( arrayOut );
	}

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
	char	tmp[12];

	/*
	*	初期化
	*/

	//プログラム管理構造体初期化
	memset(pEnv, 0, sizeof(ENV));

	//ログファイルオープン
	//rc = ZbmlOpenLog( LOGINIFILE );
	rc = ZbmlOpenLog( EnvRef(LOGINIFILE) );
	if(rc != 0)
	{
		return(ERROR_CODE_LOG_OPEN_ERROR);
	}
	
	//ログ情報初期化設定
    memset(&pEnv->stLogMem, '\0', sizeof(pEnv->stLogMem)) ;
	
	//プログラム名セット
	strcpy(pEnv->stLogMem.pcAppName, APP_NAME);

	//プログラム開始ログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "精度管理異常チェック処理起動");

	//コマンドライン引数チェック
	//	※第2引数にパラメータファイルのパスが入力されていなければエラー
	if(argc != 2)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "コマンドライン引数が不正です。");
		return(ERROR_CODE_CMD_PRM_ERROR);
	}

	//パラメータファイルオープン
	pEnv->bp = ZbmlPrmOpen(argv[1]) ;
	if(pEnv->bp == NULL)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
		 MYAPP_LOG_ERRCODE_NON,"パラメータファイルのオープンに失敗しました。");
		return(ERROR_CODE_PRM_OPEN_ERROR);
	}
	
	/*
	*	パラメータ取得
	*/
	
	//データベース名取得
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_NAME, pEnv->cDbName) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//ＤＢユーザＩＤ取得
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_USER_ID, pEnv->cDbUserId) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//ＤＢパスワード取得
	if(ZbmlPrmGetVal(pEnv->bp, PRM_DB_PASSWORD, pEnv->cDbPassword) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	
	//スリープ時間(秒)を取得
	if(ZbmlPrmGetVal(pEnv->bp, PRM_SLEEP_SEC, tmp) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	//スリープ
	pEnv->sleepInterval = atoi(tmp);
	
	// 1.01 SHM_KEY GET
	if(ZbmlPrmGetVal(pEnv->bp, PRM_SHM_KEY, tmp) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	// SHM_KEY
	pEnv->shm_Key = atoi(tmp);
	
	// 1.01 コントロール結果情報　SELECT最大件数
	if(ZbmlPrmGetVal(pEnv->bp, PRM_SEL_MAX, tmp) != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_ERROR, "initFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "パラメータの取得に失敗しました。");
		return(ERROR_CODE_PRM_GET_ERROR);
	}
	// SEL_MAX
	pEnv->sel_Max = atoi(tmp);
	
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
	struct  SHM stcShm;                 // 1.01 終了判断共有メモリ
    int     li_stopFlg = 0;             // 1.01 終了判断

	//トレースログ出力
	mcrPutTrace(pEnv, TRCKIND_TRACE, "mainFunction", "", 
			MYAPP_LOG_ERRCODE_NON,  "Start Function.");
	
	/*
	*	初期化
	*/
	
    // 1.01 共有メモリ生成
	stcShm.shm_Key = pEnv->shm_Key;
    if( sFncShmCrt ( &stcShm ) < 0 ) {
		char ebuf[10];
		sprintf( ebuf, "shmkey[%d]", errno );
		mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
			ebuf);
		mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
			"共有メモリ生成に失敗しました。");
        return( ERROR_FUNC_ERROR );
    }
	
	/* 1.01 INTEC ADD  DB CONNECTは FOR文の外で実行
	*	データベース接続
	*/
	rc = ZdbConnect(pEnv->cDbName, pEnv->cDbUserId, pEnv->cDbPassword);
	if(rc != 0)
	{
		mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
			"データベースの接続に失敗しました。");
		return(ERROR_CODE_DB_CONNECT_ERROR);
	}

	/*
	*	精度管理異常チェック処理
	*/
	//ループ制御用のフラグを(1:実行中にセット)
	gloopFlag = 1;
	//シグナルハンドラをセット
	signal(SIGINT, handleSignal);
	signal(SIGTERM, handleSignal);

	
	while(gloopFlag)
	{

		/* 1.01 INTEC DELL
		*	データベース接続
		*/
		// rc = ZdbConnect(pEnv->cDbName, pEnv->cDbUserId, pEnv->cDbPassword);
		// if(rc != 0)
		// {
		// 	mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
		// 		"データベースの接続に失敗しました。");
		// 	return(ERROR_CODE_DB_CONNECT_ERROR);
		//}

		//精度管理異常チェック
		rc = checkSeidoKanri(pEnv);
		if(rc)
		{

			//==> Test Code 2006.12.15 Kim Jinsuk SELECT 失敗するとき続く
			//mcrPutTrace(pEnv, TRCKIND_ERROR, "mainFunction", "", 
			//	MYAPP_LOG_ERRCODE_NON,  
			//	"えん。。。。エラー");
			//<== Test Code 2006.12.15 Kim Jinsuk SELECT失敗するとき続く

			//ロールバック
			ZdbRollback();

			mcrPutTrace(pEnv, TRCKIND_ERROR, "mainFunction", "", 
				MYAPP_LOG_ERRCODE_NON,  
				"精度管理異常チェック処理に失敗しました。");

			
			return(ERROR_FUNC_ERROR);

		}
		
		//コミット
		// 1.01 INTEC DELL	commit はcheckSeidoKanri内で実施
		// ZdbCommit();

		//データベース切断
/* 1.01 INTEC DELL	DISCONNECT は せめてFOR文の外で実行
DEL		ZdbDisConnect();
*/

		// 1.01 INTEC ADD STA
        //------------------
        // 終了判断
        //------------------
            // 共有メモリ取得
        if( sFncShmGet ( &stcShm, &li_stopFlg ) < 0 ){
			mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
				"共有メモリ取得に失敗しました。");
            break;
        }
        if( li_stopFlg == 1 ){
            // TRACE
			mcrPutTrace(pEnv, TRCKIND_TRACE, "main", "", MYAPP_LOG_ERRCODE_NON,
				"終了指示が出たため、処理を終了します。");
            break;
        }
		// 1.01 INTEC ADD END

		sleepFunction(pEnv->sleepInterval);
	}

	// 1.01 INTEC ADD データベース切断
	ZdbDisConnect();

	//  1.01 INTEC ADD 共有メモリ削除
	sFncShmDel ( &stcShm ) ;

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

	// 1.01 INTEC ADD LOG CLOSE
	ZbmlCloseLog( );

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

	// 1.01 INTEC ADD
	// 		.sqcに構造体を渡すため
	memcpy( &stEnv,	&Env, sizeof( ENV ));

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
