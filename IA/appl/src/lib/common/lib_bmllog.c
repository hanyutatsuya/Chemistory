/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：lib_log.c                                                    */
/* 　概　　　要：ログ出力ライブラリ                                           */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2005/12/21     芳賀弘幸       新規作成                           */
/******************************************************************************/

/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <iconv.h>
#include <limits.h>

#include "bmllog.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

//  フラグ定義
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

//	ファイル名置換文字列
#define		MY_YEAR_4	"%YYYY%"
#define		MY_YEAR_2	"%YY%"
#define		MY_MON		"%MM%"
#define		MY_DAY		"%DD%"
#define		MY_HOUR		"%HH%"
#define		MY_MIN		"%MI%"
#define		MY_SEC		"%SS%"

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
static int	sFncIniFileRead ( char * ) ;
static int	sFncDbWrite ( char *, struct stcLogAPLLOG * ) ;
static void sFncFilenameRep ( char *, char *, struct tm * ) ;
void loging ( char *, ... );

/******************************************************************************/
/*  関 数 名　：ZbmlOpenLog()												  */
/*  機能概要　：ログを開始する。											  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *pcIniFileName 【必須】ｉｎｉファイル名を指定する		  */
/*  出　　力　：                                                              */
/*   なし                                                                     */
/*  復帰情報　： int                                                          */
/* 　　　　　　　 0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int 
ZbmlOpenLog( pcIniFileName )
char	*pcIniFileName ;
{
	char		*pcPath ;
	char		 cIniFileName[256];

loging ( "START - ZbmlOpenLog\n") ;

	/***
	 ***	初期処理
	 ***/
	//	引数チェック
	if ( gpstLogEnv != NULL ) {
loging ( "END   - ZbmlOpenLog[-1]\n") ;
		return ( -1 ) ;
	}
	//	 ログ環境構造体領域アロケーション
	gpstLogEnv = ( struct stcLogEnv * ) malloc ( sizeof ( struct stcLogEnv ) ) ;
	if ( gpstLogEnv == NULL ) {
loging ( "END   - ZbmlOpenLog[-1]\n") ;
		return ( -1 ) ;
	}
	memset ( gpstLogEnv, '\0', sizeof ( struct stcLogEnv ) ) ;

	//	 環境変数よりINIファイル格納ディレクトリ
	pcPath = getenv ( BML_LOGINIPATH ) ;
	if ( pcPath == NULL ) {
		strcpy ( cIniFileName, pcIniFileName ) ;
	} else {
		sprintf ( cIniFileName, "%s/%s", pcPath, pcIniFileName ) ;
	}

	/***
	 ***	文字コード変換対応（EUC->SJIS)	
	 ***/
	gpstLogEnv->cd = iconv_open ( "SHIFT-JIS", "EUC-JP" ) ;
	if ( gpstLogEnv->cd == (iconv_t)(-1) ) {
		return ( -1 ) ;
	}

	/***
	 ***	メイン処理
	 ***/
	if ( sFncIniFileRead( cIniFileName ) != 0 ) {
loging ( "END   - ZbmlOpenLog[-1]\n") ;
		return ( -1 ) ;
	}

	/***
	 ***	終了処理
	 ***/
loging ( "END   - ZbmlOpenLog[0]\n") ;
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：ZbmlPutLog()												  */
/*  機能概要　：ログを環境情報取得											  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *pcLogName    	【任意】ログファイル名を指定する。		  */
/*									※NULLを指定した場合はINIファイルより	  */
/*									  ログ情報を取得する。					  */
/*  出　　力　：                                                              */
/*   なし                                                                     */
/*  復帰情報　： int                                                          */
/* 　　　　　　　 0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
int 
_ZbmlPutLog( pstLogMem, file, line )
struct stcLogMember *pstLogMem ;
char				*file ;
long				 line ;
{
	LC_BOOLEAN			 logdbPutFlg ;		
	LC_BOOLEAN			 logPutFlg ;		
	FILE				*fp ;
	char				 filename[256] ;
	char				 repFilename[256] ;
	char				 dbOutFilename[256] ;
	struct stcLogInfo	*seeLogInfo ;

	struct stcLogAPLLOG	 recAPLLOG ;
	char				 cHostname[256+1] ;
	pid_t				 tPid ;					 
	struct tm			*timepos ;
	struct timeb		 timebuf ;

	char			 MsgEUC[1024+1];
	char			*pMsgEUC ;
	size_t			 MsgEUClen;

	char			 MsgSJIS[1024+1];
	char			*pMsgSJIS ;
	size_t			 MsgSJISlen;

loging ( "START - ZbmlPutLog\n") ;
	/***
	 ***	初期処理
	 ***/
	//	パラメータチェック
	if ( pstLogMem == NULL ) {
loging ( "END   - ZbmlPutLog[-1]\n") ;
		return ( -1 ) ;
	}	

	//	オープンされていない場合
	if ( gpstLogEnv == NULL ) {
loging ( "END   - ZbmlPutLog[-1]\n") ;
		return ( -1 ) ;
	}

	//	日時取得
	ftime ( &timebuf ) ;
	timepos = ( struct tm * ) localtime ( &( timebuf.time ) ) ;

	//	ホスト名取得	
	gethostname ( cHostname, sizeof ( cHostname ) ) ;

	//	プロセスＩＤ
	tPid = getpid() ;

	//	変数初期化
	logdbPutFlg = LC_false ;
	logPutFlg 	= LC_false ;

	//	トレース種別よりログ情報取得
	seeLogInfo = gpstLogEnv->topLoginfo ;
	while ( seeLogInfo != NULL ) {
		if ( seeLogInfo->eTrcKind == pstLogMem->eTrcKind ) {
			break ;
		}
		seeLogInfo = seeLogInfo->next ;
	}
	if ( seeLogInfo == NULL ) {
		return ( -1 ) ;
	}
	//	ログ出力レベル判定
	if ( seeLogInfo->iLogLv >= gpstLogEnv->iLogOutLv ) {
		logPutFlg = LC_true ;
		strcpy ( filename, seeLogInfo->pcLogName ) ;
	}
	//	ログテーブル出力レベル判定
	if ( seeLogInfo->iLogLv >= gpstLogEnv->iDBOutLv ) {
		logdbPutFlg = LC_true ;
	}
loging ( "      - ログファイル-INI[%s]\n", filename) ;
loging ( "                     TRC[%c]\n", seeLogInfo->eTrcKind) ;
loging ( "                     LV [%d]\n", seeLogInfo->iLogLv) ;

	/***
	 ***	ログ出力処理
	 ***/
	if ( logPutFlg == LC_true ) {
		//	ファイル名置換
		sFncFilenameRep ( filename, repFilename, timepos ) ;
		fp = fopen ( repFilename, "a" ) ;
		if ( fp == NULL ) {
			return ( -1 ) ;
		}

		fprintf ( fp , "%04d/%02d/%02d\t%02d:%02d:%02d\t%c\t%s\t%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%s\t%s\n",
						timepos->tm_year + 1900, 
						timepos->tm_mon + 1, 
						timepos->tm_mday,
						timepos->tm_hour, 
						timepos->tm_min, 
						timepos->tm_sec,
						pstLogMem->eTrcKind,
						cHostname,
						tPid,
						pstLogMem->pcLoginId,
						pstLogMem->pcAppName,
						file,
						pstLogMem->pcFncName,
						line,
						pstLogMem->pcExeFlg,
						pstLogMem->pcErrCode,
						pstLogMem->pcMsg ) ;

		fclose ( fp ) ;
	}

	/***
	 ***	ログテーブル出力	
	 ***/
	if ( logdbPutFlg == LC_true ) {
loging ( "      - ログテーブル出力\n") ;
		//	ファイル名作成(年月日時分秒ミリ秒ＰＩＤ.log)
		sprintf ( dbOutFilename, "%02d%02d%02d%02d%02d%02d%03d%06d%s",
							( timepos->tm_year + 1900 ) % 100, 
							timepos->tm_mon + 1, 
							timepos->tm_mday,
							timepos->tm_hour, 
							timepos->tm_min, 
							timepos->tm_sec,
							timebuf.millitm,
							tPid,
							BML_SFX_DBFILE ) ;

		//	データ設定
		memset ( &recAPLLOG, '\0', sizeof ( recAPLLOG ) ) ;
		sprintf ( recAPLLOG.sydate, "%04d-%02d-%02d", timepos->tm_year + 1900, 
													timepos->tm_mon + 1, 
													timepos->tm_mday ) ;
		sprintf ( recAPLLOG.sytime, "%02d:%02d:%02d", timepos->tm_hour, 
													timepos->tm_min, 
													timepos->tm_sec ) ;
		recAPLLOG.tracekbn[0] = pstLogMem->eTrcKind ;
		strcpy ( recAPLLOG.pcname, cHostname ) ;
		//recAPLLOG.proccessid = tPid ;
		sprintf ( recAPLLOG.proccessid, "%d", tPid ) ;
		strcpy ( recAPLLOG.loginid, pstLogMem->pcLoginId ) ;
		strcpy ( recAPLLOG.wkupapp, pstLogMem->pcAppName ) ;
		strncpy ( recAPLLOG.srcname, file, sizeof ( recAPLLOG.srcname ) - 1 ) ;
		strncpy ( recAPLLOG.funcname, pstLogMem->pcFncName, sizeof (recAPLLOG.funcname ) - 1 ) ;
		//recAPLLOG.getline = line ;
		sprintf ( recAPLLOG.getline, "%ld", line ) ;
		strcpy ( recAPLLOG.procflg, pstLogMem->pcExeFlg ) ;
		strcpy ( recAPLLOG.errcode, pstLogMem->pcErrCode ) ;
		//文字コード変換対応（EUC->SJIS）
		pMsgEUC  = MsgEUC ;
		pMsgSJIS = MsgSJIS ;
		memset ( MsgEUC,  '\0', sizeof ( MsgEUC ) ) ;
		memset ( MsgSJIS, '\0', sizeof ( MsgEUC ) ) ;
		strcpy ( MsgEUC, pstLogMem->pcMsg ) ;
		MsgEUClen  = strlen ( MsgEUC ) ;
		MsgSJISlen = sizeof ( MsgSJIS ) -1 ;
		if ( iconv ( gpstLogEnv->cd,
			     &pMsgEUC,  &MsgEUClen, 
			     &pMsgSJIS, &MsgSJISlen ) == -1 ) {
			return ( -1 ) ;
		}
		strcpy ( recAPLLOG.message, MsgSJIS ) ;
		//strcpy ( recAPLLOG.message.data, pstLogMem->pcMsg ) ;
		//recAPLLOG.message.length = strlen ( pstLogMem->pcMsg ) ;
		sFncDbWrite ( dbOutFilename, &recAPLLOG ) ;
	}

loging ( "END   - ZbmlPutLog[0]\n") ;

	/***
	 ***	終了処理
	 ***/
	return ( 0 ) ;

}
/******************************************************************************/
/*  関 数 名　：ZbmlCloseLog												  */
/*  機能概要　：ログを環境情報開放											  */
/*  入　　力　：                                                              */
/*   なし                                                                     */
/*  出　　力　：                                                              */
/*   なし                                                                     */
/*  復帰情報　： 無し                                                         */
/******************************************************************************/
void 
ZbmlCloseLog()
{
	struct stcLogInfo	*seeLogInfo ;
	struct stcLogInfo	*freeLogInfo ;

	/***
	 ***	文字コード変換クローズ
	 ***/
	iconv_close ( gpstLogEnv->cd ) ;

loging ( "START - ZbmlCloseLog\n") ;
	/***
	 ***	アロケート領域開放
	 ***/
	//	オープンされていない場合
	if ( gpstLogEnv == NULL ) {
loging ( "END   - ZbmlCloseLog\n") ;
		return ;
	}

	//	ログ構造体報
	seeLogInfo = gpstLogEnv->topLoginfo ;
	while ( seeLogInfo != NULL ) {
		freeLogInfo = seeLogInfo ;
		seeLogInfo = seeLogInfo->next ;
		free ( freeLogInfo ) ;
	}

	//	ログ環境構造体
	free ( gpstLogEnv ) ;
	gpstLogEnv = NULL ;
loging ( "END   - ZbmlCloseLog\n") ;
}
/******************************************************************************/
/*  関 数 名　：sFncDbWrite													  */
/*  機能概要　：ＤＢ登録ファイルを出力する									  */
/*  入　　力　：                                                              */
/*　 第１引数 ：char *pcLogName    	【任意】ログファイル名を指定する。		  */
/*									※NULLを指定した場合はINIファイルより	  */
/*									  ログ情報を取得する。					  */
/*  出　　力　：                                                              */
/*   なし                                                                     */
/*  復帰情報　： int                                                          */
/* 　　　　　　　 0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
static int	
sFncDbWrite ( pdbOutFilename, precApllog )
char				 *pdbOutFilename ;
struct stcLogAPLLOG	 *precApllog ;
{

	FILE					*fp ;
	char					 dbOutPath[256] ;


	/***
	 ***	初期処理
	 ***/
	//	ファイル名作成
	if ( gpstLogEnv->pcDBOutFilePath[0] == '\0' ) {
		strcpy ( dbOutPath, pdbOutFilename ) ;
	} else {
		sprintf ( dbOutPath, "%s/%s", gpstLogEnv->pcDBOutFilePath, pdbOutFilename ) ;
	}

	/***
	 ***	ファイルオープン
	 ***/
	fp = fopen ( dbOutPath, "ab" ) ;
	if ( fp == NULL ) {
		return ( -1 ) ;
	}


	/***
	 ***	ファイル出力
	 ***/
	if ( fwrite ( precApllog, sizeof ( struct stcLogAPLLOG ), 1, fp ) <= 0 ) {
		return ( -1 ) ;
	}


	/***
	 ***	ファイルクローズ
	 ***/
	fclose ( fp ) ;

	return( 0 ) ;

}
/******************************************************************************/
/*  関 数 名　：sFncIniFileRead												  */
/*  機能概要　：ログ初期ファイル読み込み									  */
/*  入　　力　： 無し                                                         */
/*  出　　力　： 無し                                                         */
/*  復帰情報　： int                                                          */
/* 　　　　　　　 0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
static	int
sFncIniFileRead ( pcIniFileName )
char	*pcIniFileName ;
{
	FILE				 *fp ;
	int					  idx ;
	char				  buf[ 1024 ] ;
	char				 *cp[ 10 ] ;
	char				 *p ;
	struct stcLogInfo	**make ;
	struct stcLogInfo	 *see ;

loging ( "      - ＩＮＩファイル読込[sFncIniFileRead]\n") ;
	/***
	 ***	初期処理
	 ***/
	//	出力レベル初期化
	gpstLogEnv->iLogOutLv = INT_MAX ;
	gpstLogEnv->iDBOutLv = INT_MAX ;

	make = &( gpstLogEnv->topLoginfo ) ;

	/***
	 ***	ＩＮＩファイルオープン
	 ***/
	fp	= fopen ( pcIniFileName, "r" ) ;
	if ( fp == NULL ) {
		return ( -1 ) ;
	}


	/***
	 ***	ＩＮＩファイル読み込み
	 ***/
	while ( fgets ( buf, sizeof ( buf ), fp ) != NULL ) {
		// コメント読み飛ばし
		if ( buf[ 0 ] == '#' || buf[ 0 ] == '\n' || buf[ 0 ] == '\0' ) {
			continue ;
		}

		//	トークン分割
		idx = 0 ;
		p = buf ;
		memset ( cp, '\0', sizeof ( cp ) ) ;
		while ( ( cp[ idx ] = strtok ( p,     " \t\n" ) ) != NULL ) {
			p = NULL ;
			idx ++ ;
		}
		if ( cp[0] == NULL ) {
			continue ;
		}

		//	ログ環境構造設定体
		if ( strcmp ( cp[0], BML_LOGINI_ENV1 ) == 0 ) {
			if ( cp[1] == NULL ) {
				gpstLogEnv->iLogOutLv = INT_MAX ;
			} else if ( cp[1][0] == '\0' ) {
				gpstLogEnv->iLogOutLv = INT_MAX ;
			} else {
				gpstLogEnv->iLogOutLv = atoi ( cp[1] ) ;
			}  
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV2 ) == 0 ) {
			if ( cp[1] == NULL ) {
				gpstLogEnv->iDBOutLv = INT_MAX ;
			} else if ( cp[1][0] == '\0' ) {
				gpstLogEnv->iDBOutLv = INT_MAX ;
			} else {
				gpstLogEnv->iDBOutLv = atoi ( cp[1] ) ;
			}
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV3 ) == 0 ) {
			strcpy ( gpstLogEnv->pcDBConnect, cp[1] ) ;
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV4 ) == 0 ) {
			strcpy ( gpstLogEnv->pcLogPath, cp[1] ) ;
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV5 ) == 0 ) {
			gpstLogEnv->pcDBPort = atoi ( cp[1] ) ;	
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV6 ) == 0 ) {
			strcpy ( gpstLogEnv->pcDBOutFilePath, cp[1] ) ;
		} else
		if ( strcmp ( cp[0], BML_LOGINI_INFO ) == 0 ) {
			*make = ( struct stcLogInfo * ) malloc ( sizeof ( struct stcLogInfo ) ) ;
			if ( *make == NULL ) {
				return ( -1 ) ;
			}
			memset ( ( void * ) *make, '\0', sizeof ( struct stcLogInfo ) ) ;
			(*make)->eTrcKind = cp[1][0] ;
			(*make)->iLogLv = atoi ( cp[2] ) ;
			strcpy ( (*make)->pcLogName, cp[3] ) ;
			make = &( (*make)->next )  ;
		} 
	}

	/***
	 ***	ＩＮＩファイルクローズ
	 ***/
	fclose ( fp ) ;
loging ( "      - gpstLogEnv->iLogOutLv  [%d]\n", gpstLogEnv->iLogOutLv) ;
loging ( "        gpstLogEnv->iDBOutLv   [%d]\n", gpstLogEnv->iDBOutLv) ;
loging ( "        gpstLogEnv->pcDBConnect[%s]\n", gpstLogEnv->pcDBConnect) ;
loging ( "        gpstLogEnv->pcLogPath  [%s]\n", gpstLogEnv->pcLogPath) ;
loging ( "        gpstLogEnv->pcDBOutFilePath  [%s]\n", gpstLogEnv->pcDBOutFilePath) ;
loging ( "        gpstLogEnv->Loginfo\n") ;
see =  gpstLogEnv->topLoginfo ;
while ( see != NULL ) {
loging ( "                               [%c][%d][%s]\n", see->eTrcKind,
								                     	  see->iLogLv,
													      see->pcLogName) ;
	see = see->next ;
}
	return ( 0 ) ;
}
/******************************************************************************/
/*  関 数 名　：sFncIniFileRead												  */
/*  機能概要　：ログ初期ファイル読み込み									  */
/*  入　　力　： 無し                                                         */
/*  出　　力　： 無し                                                         */
/*  復帰情報　： int                                                          */
/* 　　　　　　　 0     : 成功												  */
/* 　　　　　　　-1     : 失敗												  */
/******************************************************************************/
static	void
sFncFilenameRep ( pInBuf, pOutBuf, psTm )
char		*pInBuf ;
char		*pOutBuf ;
struct tm	*psTm ;
{
	
	char			*hPos ;
	char			*tPos ;
	char			*cPos ;

	strcpy ( pOutBuf, pInBuf ) ;
	hPos = pOutBuf ;

	//	年４置換
	if ( ( cPos = strstr ( pOutBuf, MY_YEAR_4 ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_YEAR_4 ) ;
		sprintf ( pOutBuf, "%s%04d%s", hPos, psTm->tm_year + 1900, tPos ) ;
	}

	//	年２置換
	if ( ( cPos = strstr ( pOutBuf, MY_YEAR_2 ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_YEAR_2 ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, ( psTm->tm_year + 1900 ) % 100, tPos ) ;
	}

	//	月置換
	if ( ( cPos = strstr ( pOutBuf, MY_MON ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_MON ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_mon + 1, tPos ) ;
	}

	//	日置換
	if ( ( cPos = strstr ( pOutBuf, MY_DAY ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_DAY ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_mday, tPos ) ;
	}

	//	時置換
	if ( ( cPos = strstr ( pOutBuf, MY_HOUR ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_HOUR ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_hour, tPos ) ;
	}

	//	分置換
	if ( ( cPos = strstr ( pOutBuf, MY_MIN ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_MIN ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_min, tPos ) ;
	}

	//	秒置換
	if ( ( cPos = strstr ( pOutBuf, MY_SEC ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_SEC ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_sec, tPos ) ;
	}

}
/** End of File ***************************************************************/
