/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：LD106.c                                                      */
/* 　概　　　要：ストッカー【供給】                                           */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/01/15     芳賀弘幸       新規作成                           */
/*  1.01     2006/12/16   YOON JONG JIN    エラー追加                         */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>

#include "bmllog.h"
#include "bmlprm.h"
#include "bml_misc.h"
#include "bml_date.h"
#include "bml_DBCom.h"
#include "bml_dbrc.h"

#include "sql.h"

#include "LD106.h"
#include "LD106_db.h"

/******************************************************************************/
/* Define定義                                                                 */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/
MYAPP_STSCODE		 gintErrorCode ;
struct stcLogMember	 gstLogMem ;		//	ログ出力情報

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
//	ファイル・データベース出力関数

//	共有メモリ操作関数
static	int	sFncShmCrt() ;
static	int	sFncShmGet( int *) ;
static	int	sFncShmDel() ;

static  void	endFunction();

/******************************************************************************/
/*  関 数 名　：initFunction()							*/
/*  機能概要　：初期処理関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/******************************************************************************/
int
initFunction( argc, argv )
int	 argc ;
char	*argv[] ;
{
	char	 lc_prmBuf[256] ;
	long	 ll_retSts ;
	char	*lc_login ;

	/***
	 ***	引数チェック	
	 ***/
	if ( argc != 2 ) {
		fprintf ( stderr, "%s : There is an error in a command parameter\n", MYAPP_APP_NAME ) ;
		return ( -1 ) ;
	}

	/*	ログオープン */
	if ( ZbmlOpenLog ( argv[1] ) != 0 ) {
		fprintf ( stderr, "ZbmlOpenLog NOT OPEN(%s)\n",argv[1]); 
		return ( -1 ) ;
	}

	//	ログ情報初期設定
	memset ( &gstLogMem, '\0', sizeof ( gstLogMem ) ) ;
	if ( ( lc_login = getenv( "LOGNAME" ) ) != NULL ) {
		strcpy ( gstLogMem.pcLoginId, lc_login ) ;
	}
	strcpy ( gstLogMem.pcAppName, MYAPP_APP_NAME ) ;

	//	開始ログ出力
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "プログラム起動" ) ;

	/*	初期化	*/

	//	エラーステータス変更
	gintErrorCode = 0 ;

	//	プログラム環境変数初期化
	memset ( &pAppEnv , '\0', sizeof( pAppEnv ) ) ;

	//	パラメータファイル名退避
	pAppEnv.pcFielNamePRM = argv[1] ;

	//	パラメータファイルオープン	
	pAppEnv.bp = ZbmlPrmOpen ( pAppEnv.pcFielNamePRM ) ;		
	if ( pAppEnv.bp == NULL ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmOpen", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータファイルのオープンに失敗しました[%s]", pAppEnv.pcFielNamePRM ) ;
		return ( -1 ) ;
	}
	//	共有メモリキー取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SHM_KEY, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SHM_KEY ) ;
		return ( -1 ) ;
	}
	pAppEnv.shm_Key = atoi ( lc_prmBuf ) ;
	//	データベース名
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_NAME, pAppEnv.cDb_Name ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_NAME ) ;
		return ( -1 ) ;
	}
	//	データベースユーザ
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_USER, pAppEnv.cDb_User ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_USER ) ;
		return ( -1 ) ;
	}
	//	データベースパスワード
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DB_PASSWD, pAppEnv.cDb_Passwd ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DB_PASSWD ) ;
		return ( -1 ) ;
	}
        //      計算項目取得範囲
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_DATE_RANGE, lc_prmBuf ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_DATE_RANGE ) ;
		return ( -1 ) ;
	}
	pAppEnv.DateRange = atoi ( lc_prmBuf ) ;
        //      ロックファイル。LD101(属性エラーチェック情報作成) 起動トリガー。最初の処理が終わったら作成。
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_LOCK_FILE, pAppEnv.cLockFile ) != 0 ) {
		//      異常終了        LOG
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_LOCK_FILE ) ;
		return ( -1 ) ;
	}
	//	SLEEP取得
	if ( ZbmlPrmGetVal ( pAppEnv.bp, MYAPP_PRM_SLEEP_MIN, lc_prmBuf ) != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_PRM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "パラメータが取得できませんでした[%s]", MYAPP_PRM_SLEEP_MIN ) ;
		return ( -1 ) ;
	}
	pAppEnv.SleepMin= atoi ( lc_prmBuf ) ;

	//	パラメータファイルクローズ	
	ZbmlPrmClose ( pAppEnv.bp ) ;

	/***
	 ***	共有メモリ生成	
	 ***/
	if ( sFncShmCrt() < 0 ) {
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZbmlPrmGetVal", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "共有メモリエラー") ;
		return ( -1 ) ;
	}

	/***
	 ***	データベースオープン
	 ***/
	ll_retSts = ZdbConnect( pAppEnv.cDb_Name, pAppEnv.cDb_User, pAppEnv.cDb_Passwd ) ;
	if ( ll_retSts != 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_DB ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "ZdbConnect", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "データベースオープンに失敗しました[DB=%s USER=%s PASS=%s]", pAppEnv.cDb_Name, pAppEnv.cDb_User, pAppEnv.cDb_Passwd ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ; 
}
/********************************************************************************/
/*  関 数 名　：mainFunction()							*/
/*  機能概要　：メイン処理関数							*/
/*  入　　力　：								*/
/*　 第１引数 ：struct	env *   	プログラム環境構造体。			*/
/*  出　　力　：								*/
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/********************************************************************************/
int
mainFunction()
{
	int	li_stopFlg = 0;

	int	ret = 0;
	int	min = 0;
	int	cnt_recalc = 0;
	int	cnt_calcmst = 0;
	int	cnt_calcrec = 0;
	int	max_recalc = 0;
	int	max_calcmst = 0;
	int	max_calcrec = 0;
	char	serch_date_from[11];
	char	serch_date_to[11];

	FILE	*fp = NULL ;

	my_stSYSKNR	pSysKnr; 	//
	my_stCALC	*pCalc;		/* 計算元情報 */
	my_stCALCSYSMST	*pCalcsysmst;	/* 計算マスタ情報 */

	/***
	 ***		永久ループ
	 ***		停止コマンドで終了
	 ***/
	while ( 1 ) {
		/* 1分ごとに停止コマンドを確認しながら設定された時間スリープ */
		for ( min=0; min < pAppEnv.SleepMin; min++ ) {
			/* 停止コマンド確認 */
			if ( sFncShmGet ( &li_stopFlg ) != 0 ) {
				return( RET_STOP );
			}
			if ( li_stopFlg == 1 ) {
				return ( RET_OK ) ;
			}
			/* システム管理マスタ取得 */
			if ( ZdbSelSysKnr( &pSysKnr ) !=  RET_OK ){
				return( RET_STOP );
			}
			/* 分注ＥＮＤが来ている場合、日次開始チェックを行う */
			if ( strcmp( pSysKnr.bchendflg , "1" ) == 0 ) {
				/* 日次処理が始まっていたら終了 */
				if ( strcmp( pSysKnr.unyflg , "1" ) == 0 ) {
					sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
						     "日次処理の開始を確認しました。");
					return ( RET_OK ) ;
				}
			}
			sleep ( 60 ) ;
		}

		/* システム管理マスタ取得 */
		if ( ZdbSelSysKnr( &pSysKnr ) !=  RET_OK ){
			return( RET_STOP );
		}
		/* 分注ＥＮＤがきていない場合、処理を開始しない */
		if ( strcmp( pSysKnr.bchendflg , "1" ) != 0 ) {
			continue;
		}

		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "属性修正対象　再計算処理開始" ) ;

		/* 初期化 */
		pCalc = NULL ;
		pCalcsysmst = NULL;
		/* 属性修正 再計算対象情報 取得処理 */
		ret = ZdbSelCalc( &pCalc, &max_recalc ) ;
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
			return( RET_STOP );
		}
		/* 属性修正対象　再計算処理 */
		for ( cnt_recalc = 0; cnt_recalc < max_recalc; cnt_recalc++ ){
			/* 再計算処理の実行 */
			ret = sFncCalc( &pCalc[cnt_recalc] );
			if ( ret ==  RET_OK ){
				/* 再計算済みフラグの更新 */
				ret = ZdbUpdRecalc( &pCalc[cnt_recalc] );
				if ( ret !=  RET_OK ){
					return( RET_STOP );
				}
			} 
			else if( ret !=  RET_CONTINUITY ){
				return( RET_STOP );
			}
			ZdbCommit() ;
		}
		if( pCalc != NULL){
			ZbmlFree( pCalc );
		}
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
			     "属性修正対象　再計算処理完了 [%d件]", max_recalc ) ;

		/* 他サテライト結果計算用マスタ情報 取得処理 */
		ret = ZdbSelCalcsysmst( pSysKnr.kjnsriymd, &pCalcsysmst, &max_calcmst ) ;
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
			return( RET_STOP );
		}
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
			     "他サテライト項目　計算処理開始" ) ;
		/* マスタの件数分ループ */	
		for ( cnt_calcmst = 0; cnt_calcmst < max_calcmst; cnt_calcmst++ ){
			/* 初期化 */
			pCalc = NULL ;
			max_calcrec = 0;
			sFncGetdate( serch_date_from, pSysKnr.kjnsriymd, pAppEnv.DateRange );
			if ( strcmp ( pCalcsysmst[cnt_calcmst].hkkbn , "1") == 0 ) {
				sFncGetdate( serch_date_to, pSysKnr.kjnsriymd, -1 );
			}
			else {
				sprintf( serch_date_to, "%-10.10s", pSysKnr.kjnsriymd );
			}
			/* マスタを元に 他サテライト結果計算対象情報 取得処理 */
			ret = ZdbSelCalcOther( serch_date_from, serch_date_to, &pCalcsysmst[cnt_calcmst], &pCalc, &max_calcrec ) ;
			if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
				return( RET_STOP );
			} else if ( ret == HRC_SQL_NOT_FOUND ){
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     	"他サテライト項目　計算対象無し [knsgrp:%s kmkcd:%s zaicd:%s] ", pCalcsysmst[cnt_calcmst].knsgrp, pCalcsysmst[cnt_calcmst].kmkcd, pCalcsysmst[cnt_calcmst].zaicd ) ;
				continue ;
			}
			/* 他サテライト項目計算処理の実行 */
			for ( cnt_calcrec = 0; cnt_calcrec < max_calcrec; cnt_calcrec++ ){
				ret = sFncCalc( &pCalc[cnt_calcrec] );
				if ( ret == RET_STOP ){
					return( RET_STOP );
				}

				ZdbCommit() ;
			}
			if( pCalc != NULL){
				ZbmlFree( pCalc );
			}

			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "他サテライト項目　計算処理完了 [knsgrp:%s kmkcd:%s zaicd:%s] ", pCalcsysmst[cnt_calcmst].knsgrp, pCalcsysmst[cnt_calcmst].kmkcd, pCalcsysmst[cnt_calcmst].zaicd ) ;
		}

		// LD106ロックファイルを作成(日次処理にて使用)
		if( ( fp = fopen( pAppEnv.cLockFile, "w" ) ) == NULL ){
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "mainFunction", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				     "ロックファイルの作成に失敗しました。[%s]", pAppEnv.cLockFile ) ;
		}
		fclose( fp );
	}

	if( pCalcsysmst != NULL){
		ZbmlFree( pCalcsysmst );
	}

	return ( 0 ) ;
}

/******************************************************************************/
/*  関 数 名  ：sFncCalc							*/
/*  機能概要  ：属性修正再計算対象　取得関数					*/
/*  入    力  ：								*/
/*   第１引数 ：struct my_stCALC  *pCalc    : 属性チェック情報			*/
/*  出    力  ：なし								*/
/*  復帰情報  ：INT								*/
/*		RET_OK		: 成功						*/
/*		RET_STOP	: 失敗						*/
/*		RET_CONTINUITY	: 更新結果なし					*/
/******************************************************************************/
int
sFncCalc( pCalc )
my_stCALC	*pCalc;
{
	my_stKEKKA	*pCalcKka;	/* 結果情報 */
	my_stKJNMST	pKjnmst;

	int	ret = RET_OK ;

	char	pKsnsk[128] ;
	char	pKnsflg[1+1] ;
	int	KekkaNoneFlg = 0;	/* INSERT か UPDATE かを制御するフラグ */
	int	KekkaOtherFlg = 0;	/* 計算項目マスタがどちらに存在するか制御するフラグ */
	int	i = 0;
	int	cntKka = 0;
	int	flg = RET_CONTINUITY;	/* 計算結果が更新できた場合は RET_OK */

	/* 初期処理 */
	pCalcKka = NULL ;

	/* 結果情報を取得する */
	ret = ZdbSelKekka( pCalc, &pCalcKka, &cntKka );
	if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ){
		return( RET_STOP );
	}
	if( cntKka == 0 ){
		KekkaNoneFlg = -1;
		/* 結果情報がない場合はオーダー情報から必要な情報を取得する */
		ret = ZdbSelKenorderKekka( pCalc, &pCalcKka, &cntKka );
		if( ret != RET_OK || cntKka == 0 ){
			return( RET_STOP );
		}
	}

	for (i = 0; i < cntKka ; i++) {
		/* コメント結果が入っている場合は、計算しない */
		if ( strncmp( pCalcKka[i].knskka2kbn, "  ", 2 ) != 0 ){
			sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
				     "コメント結果登録済み utkymd: %s irino:%s kmkcd:%s knskka2kbn:%s]",
				     pCalcKka[i].utkymd, pCalcKka[i].irino, pCalcKka[i].kmkcd, pCalcKka[i].knskka2kbn ) ;
			continue;
		}

		/* 初期化処理 */
		memset( pKsnsk, '\0', sizeof( pKsnsk ) );
		memset( pKnsflg, '\0', sizeof( pKnsflg ) );

		/* 基準値マスタの取得 */
	        ret = ZdbSelKjnmst(&pCalcKka[i], &pKjnmst);
		if ( ret != HRC_SQL_NORMAL ){
			return( RET_STOP );
		}

		/* 計算式を取得する */
		ret = ZdbGetKsnsk( &pCalcKka[i], pKsnsk, &KekkaOtherFlg );
		if ( ret != HRC_SQL_NORMAL ){
			if ( ret == HRC_SQL_NOT_FOUND ){
				continue;	
			}
			else {
				return( RET_STOP );
			}
		}

		/* 再計算を行う */
		ret = KeisanChk( pCalc, pKsnsk, &pCalcKka[i] , pKnsflg , pKjnmst.kjsstnksu , KekkaOtherFlg );
		if( ret != RET_OK ){
			if( ret == RET_CONTINUITY ){
				continue;	
			}
			else {
				return( RET_STOP );
			}
		}

		/* 結果フィルタチェック */
		ret = filterChk( &pCalcKka[i], &pKjnmst );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* 基準値チェック */
		ret = kjnChk( &pCalcKka[i], &pKjnmst );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* 再検レンジチェック */
		ret = rngChk( pCalc, &pCalcKka[i] );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* BMLパニックチェック */
		ret = BmlPanicChk( pCalc, &pCalcKka[i] );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* 検査室チェック */
		ret = KnsPanicChk( pCalc, &pCalcKka[i] );
		if( ret != RET_OK ){
			return( RET_STOP );
		}

		/* 計算結果がまだ登録されてない場合は INSERT */
		if( KekkaNoneFlg == -1 ){
			ret = ZdbInsCalcKekka( &pCalcKka[i], pKnsflg );
			if( ret == RET_OK ){
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					     "計算結果　新規登録[utkymd:%s irino:%s kmkcd:%s knskka:%s]",
					     pCalcKka[i].utkymd, pCalcKka[i].irino, pCalcKka[i].kmkcd, pCalcKka[i].knskka1 ) ;
				flg = RET_OK;
			} else if( ret != RET_CONTINUITY ){
				return( RET_STOP );
			} else {
				/* 処理中に結果が入ってきて重複エラーになった場合は */ 
				/* 後続処理で UPDATE を行う。*/
				KekkaNoneFlg = 0;
			}
		}
		/* 既に計算結果が登録されていた場合は UPDATE */
		if( KekkaNoneFlg == 0 ){
			ret = ZdbUpdCalcKekka( &pCalcKka[i], pKnsflg );
			if( ret == RET_OK ){
				sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, 
					     "計算結果　更新[utkymd:%s irino:%s kmkcd:%s knskka:%s]",
					     pCalcKka[i].utkymd, pCalcKka[i].irino, pCalcKka[i].kmkcd, pCalcKka[i].knskka1 ) ;
				flg = RET_OK;
			} else {
				return( RET_STOP );
			}
		}
	}
	if( pCalcKka != NULL ){
		ZbmlFree( pCalcKka );
	}
	return( flg );
}

/******************************************************************************/
/*  関 数 名　：endFunction()							*/
/*  機能概要　：終了処理関数							*/
/*  入　　力　：                                                              */
/*　 第１引数 ：struct	env *   	プログラム環境構造体。		 	*/
/*  出　　力　：                                                              */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/******************************************************************************/
void
endFunction()
{
	/*	ロックファイル削除 */
	remove( pAppEnv.cLockFile ) ;

	/*	データベースクローズ */
	ZdbDisConnect() ;

	/*	共有メモリ削除	*/
	sFncShmDel() ;

	/*	終了ログ出力 */
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__, EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "プログラム終了" ) ;
	/*	ログクローズ */
	ZbmlCloseLog() ;
	
	return ;
}

/******************************************************************************/
/*  関 数 名　：sFncGetdate()                                                   */
/*  機能概要　：日付演算関数                                                    */
/*  入　　力　：                                                              */
/*　 第２引数 ：char *  基準日付文字列( yyyy-mm-dd )                            */
/*　 第３引数 ：int     差分日数(普通に指定すると何日後。－指定で何日前となる)  */
/*  出　　力　：                                                              */
/*　 第１引数 ：char *  取得日付文字列( yyyy-mm-dd )                            */
/******************************************************************************/
void sFncGetdate( newdate, date, days )
char *newdate ;
char *date ;
int days ;
{
	int y, m, d;

	sscanf(date, "%d-%d-%d", &y, &m, &d);
	struct tm tm = { 0, 0, 0, d, m-1, y-1900 };
	time_t time = mktime(&tm) + 86400 * days;
	struct tm *ltime = localtime(&time);

	sprintf(newdate, "%d-%02d-%02d", ltime->tm_year+1900, ltime->tm_mon+1, ltime->tm_mday);
}

/******************************************************************************/
/*  関 数 名　：sFncPutLog()  			 				*/
/*  機能概要　：アプリケーションログ出力					*/
/*  入　　力　：                                                              */
/*　 第１引数 ：char *   	編集文字列					*/
/*  出　　力　：                                                              */
/*  復帰情報　：無し								*/
/******************************************************************************/
void
sFncPutLog ( LOG_TRCKIND peTrcKind, char * pcSrcName, char * pcFncName, int plLineNo, char * pcExeFlg, char * pcErrCode, char * pcfmt, ... ) 
{
	va_list	 ap ;

	/***
	 ***	ログ初期値設定
	 ***/
	gstLogMem.eTrcKind = peTrcKind ;
	strcpy ( gstLogMem.pcFncName, pcFncName ) ;
	strcpy ( gstLogMem.pcExeFlg,  pcExeFlg ) ;
	strcpy ( gstLogMem.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( gstLogMem.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***
	 ***	ログ出力
	 ***/
	_ZbmlPutLog ( &gstLogMem, pcSrcName, plLineNo) ;
	return ;
	
}
/********************************************************************************/
/*  関 数 名　：sFncShmCrt()							*/
/*  機能概要　：共有メモリ生成							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *   	プログラム環境構造体			*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncShmCrt()
{
	int	*shmData ;

	//	取得
	pAppEnv.shm_Id = shmget ( (key_t)pAppEnv.shm_Key, 
							MYAPP_SHM_SIZE, 
							0666 | IPC_CREAT ) ;
	if ( pAppEnv.shm_Id < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmget", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*shmData = 0 ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  関 数 名　：sFncShmGet()							*/
/*  機能概要　：共有メモリ取得							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *	プログラム環境構造体	 			*/
/*　 第２引数 ：int *   	値						*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncShmGet ( pshmData )
int	*pshmData ;
{
	int		*shmData ;

	//	アタッチ	
	shmData = ( int * ) shmat ( pAppEnv.shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmat", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}

	//	値設定	
	*pshmData = *shmData ;

	//	デタッチ	
	if ( shmdt ( shmData ) == -1 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		sFncPutLog ( TRCKIND_ERROR, __FILE__, "shmdt", __LINE__,
				 	 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
				 	 "共有メモリの操作に失敗しました" ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/********************************************************************************/
/*  関 数 名　：sFncShmDel()							*/
/*  機能概要　：共有メモリ削除							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：struct appEnv *	プログラム環境構造体。		 		*/
/*  出　　力　：                                                                */
/*  復帰情報　：int								*/
/*		 0	正常							*/
/*		-1	異常							*/
/********************************************************************************/
static int
sFncShmDel()
{
	//	削除	
	if ( shmctl ( pAppEnv.shm_Id, IPC_RMID, NULL) < 0 ) {
		//	異常終了	LOG
		gintErrorCode = MYAPP_STSCODE_ERR_SHM ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}	

/********************************************************************************/
/*  関 数 名　：main()								*/
/*  機能概要　：メイン関数							*/
/*  入　　力　：                                                                */
/*　 第１引数 ：char *pcLogName	【任意】ログファイル名を指定する。		*/
/*		※NULLを指定した場合はINIファイルよりログ情報を取得する		*/
/*  出　　力　：                                                                */
/*  復帰情報　：  0     : 成功							*/
/* 　　　　　　　-1     : 失敗							*/
/********************************************************************************/
int 
main( argc, argv )
int	 argc ;
char	*argv[] ;
{
	/***
	 ***    バックグラウンド実行
	 ***/
	if ( daemon ( 0, 1 ) < 0 ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "", __LINE__,
                 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                 "daemon起動失敗" ) ;
		exit ( 9 ) ;
	}

	/***
	 ***	初期処理	
	 ***/
	if ( initFunction ( argc, argv )  != 0 ) {
		endFunction() ;
		exit ( 9 ) ;
	}
	
	/***
	 ***	主処理	
	 ***/
	if ( mainFunction()  != 0 ) {
		endFunction() ;
		exit ( 9 ) ;
	}

	/***
	 ***	終了処理	
	 ***/
	endFunction() ;
	exit ( 0 ) ;
}

