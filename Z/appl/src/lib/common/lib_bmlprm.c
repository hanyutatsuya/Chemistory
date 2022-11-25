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
#include <sys/stat.h>
#include <sys/timeb.h>
#include <fcntl.h>
#include <time.h>

#include "bmlprm.h" 

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

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* 関数宣言                                                                   */
/******************************************************************************/
static	void	 _ZbmlPrmDisp ( BMLPRM * ) ;

/******************************************************************************/
/*  関 数 名　：ZbmlPrmOpen												  	  */
/*  機能概要　：環境設定ファイル読み込み									  */
/*  入　　力　：                                                              */
/*　 第１引数 ：pfileName	環境設定ファイル名								  */
/*  出　　力　：                                                              */
/*   なし                                                                     */
/*  復帰情報　： BMLPRM*                                                      */
/* 　　　　　　　NULL以外 : 成功											  */
/* 　　　　　　　NULL     : 失敗											  */
/******************************************************************************/
BMLPRM *
ZbmlPrmOpen ( pfileName )
char	*pfileName ;
{
	FILE				 *fp ;
	char				  buf[ 1024 ] ;
	char				 *p ;
	char				 *pToken ;
	struct prmMem		**makeMem ;
	struct prmVal		**makeVal ;
	struct prmMem		 *pTop ;
	struct prmMem		 *ret ;

	/***
	 ***	初期処理
	 ***/
	//	ＩＮＩファイルオープン
	fp	= fopen ( pfileName, "r" ) ;
	if ( fp == NULL ) {
		return ( NULL ) ;
	}
loging ( "START - ZbmlPrmOpen\n" ) ;

	/***
	 ***	ＩＮＩファイル読み込み
	 ***/
	makeMem = &pTop ;

	while ( fgets ( buf, sizeof ( buf ), fp ) != NULL ) {
		// コメント読み飛ばし
		if ( buf[ 0 ] == '#' || buf[ 0 ] == '\n' || buf[ 0 ] == '\0' ) {
			continue ;
		}

		//	トークン分割
		p = buf ;
		while ( ( pToken = strtok ( p,     " \t\n" ) ) != NULL ) {
			// パラメータ名取得（１回目のみ）
			if ( p != NULL ) {
				*makeMem = ( struct prmMem * ) malloc ( sizeof ( struct prmMem ) ) ;
				if ( *makeMem == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				memset ( *makeMem, '\0', sizeof ( struct prmMem ) ) ;

				(*makeMem)->name = ( char * ) malloc (  strlen ( pToken ) + 1 ) ;
				if ( (*makeMem)->name == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					ZbmlPrmClose ( pTop ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				strcpy ( (*makeMem)->name, pToken ) ;
				makeVal = & ( (*makeMem)->valTop ) ;
				p = NULL ;
			} 
			else {
				*makeVal = ( struct prmVal * ) malloc ( sizeof ( struct prmVal ) ) ;
				if ( *makeVal == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					ZbmlPrmClose ( pTop ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				memset ( *makeVal, '\0', sizeof ( struct prmVal ) ) ;
				(*makeVal)->val = ( char * ) malloc ( strlen ( pToken ) + 1 ) ;
				if ( (*makeVal)->val == NULL ) {
loging ( "END   - ZbmlPrmOpen[NULL]\n" ) ;
					ZbmlPrmClose ( pTop ) ;
					fclose ( fp ) ;
					return ( NULL ) ;
				}
				strcpy ( (*makeVal)->val, pToken ) ;
				makeVal = & ( (*makeVal)->next ) ;
			}
		}
		makeMem = & ( (*makeMem)->next ) ;
	}

	/***
	 ***	ＩＮＩファイルクローズ
	 ***/
	fclose ( fp ) ;
loging ( "END   - ZbmlPrmOpen\n" ) ;
_ZbmlPrmDisp ( pTop ) ;
	return ( pTop ) ;
}
/******************************************************************************/
/*  関 数 名　：ZbmlPrmClose												  	  */
/*  機能概要　：環境設定ファイル格納領域解放								  */
/*  入　　力　：                                                              */
/*　 第１引数 ：pMem	環境設定構造体ポインタ								  */
/*  出　　力　：                                                              */
/*   なし                                                                     */
/*  復帰情報　： 															  */
/*   なし                                                                     */
/******************************************************************************/
void
ZbmlPrmClose ( pMem )
struct prmMem	*pMem ;
{
	struct prmMem	*seeMem, *freeMem ;
	struct prmVal	*seeVal, *freeVal ;

loging ( "START - ZbmlPrmClose\n" ) ;
	seeMem = pMem ;
	while ( seeMem != NULL ) {
		free ( seeMem->name ) ;
		seeVal = seeMem->valTop ;
		while ( seeVal != NULL ) {
			free ( seeVal->val ) ;
			freeVal = seeVal ;
			seeVal = seeVal->next ;
			free ( freeVal ) ;
		}
		freeMem = seeMem ;
		seeMem = seeMem->next ;
		free ( freeMem ) ;
	}
loging ( "END   - ZbmlPrmClose\n" ) ;
	return ;
}
/******************************************************************************/
/*  関 数 名　：ZbmlPrmGetVal     										  	  */
/*  機能概要　：環境取得関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：pMem	環境設定構造体ポインタ								  */
/*　 第２引数 ：name	変数名												  */
/*  出　　力　：                                                              */
/*　 第４引数 ：Val		設定値												  */
/*  復帰情報　： 															  */
/*   なし                                                                     */
/*  復帰情報　：int				                                              */
/* 　　　　　　　0 : 成功													  */
/* 　　　　　　　1 : 警告終了（変数無し）									  */
/******************************************************************************/
int 
ZbmlPrmGetVal ( pMem, name, Val )
struct prmMem	*pMem ;
char			*name ;
char			*Val ;
{
	struct prmMem	*seeMem ;
	struct prmVal	*seeVal ;
	char			*p ;
	LC_BOOLEAN		 firstFlg ;
	int				retSts ;

loging ( "START - ZbmlPrmGetVal\n" ) ;
	retSts = 1 ;
	seeMem = pMem ;
	while ( seeMem != NULL ) {
		if ( strcmp ( seeMem->name, name ) == 0 ) {
			seeVal = seeMem->valTop ;
			Val[0] = '\0' ;
			firstFlg = LC_true ;
			while ( seeVal != NULL ) {
				if ( firstFlg == LC_true ) {
					strcpy ( Val, seeVal->val ) ;
					firstFlg = LC_false ;
				}
				else {
					strcat ( Val, "\t" ) ;
					strcat ( Val, seeVal->val ) ;
				}
				seeVal = seeVal->next ;
			}
			retSts = 0 ;
			break ;
		}
		seeMem = seeMem->next ;
	}
loging ( "END   - ZbmlPrmGetVal\n" ) ;
	return retSts ;
}

/******************************************************************************/
/*  関 数 名　：ZbmlPrmGetValList  										  	  */
/*  機能概要　：環境取得関数												  */
/*  入　　力　：                                                              */
/*　 第１引数 ：pMem	環境設定構造体ポインタ								  */
/*　 第２引数 ：name	変数名												  */
/*  出　　力　：                                                              */
/*　 第３引数 ：Val		設定値												  */
/*  復帰情報　： 															  */
/*   なし                                                                     */
/*  復帰情報　：int				                                              */
/* 　　　　　　　0 : 成功													  */
/* 　　　　　　　1 : 警告終了（変数無し）									  */
/* 　　　　　　 -1 : 異常終了												  */
/******************************************************************************/
int 
ZbmlPrmGetValList ( pMem, name, cnt, Val )
struct prmMem	 *pMem ;
char			 *name ;
int				 *cnt ;
char			 ***Val ;
{
	struct prmMem	*seeMem ;
	struct prmVal	*seeVal ;
	char			*p ;
	LC_BOOLEAN		 firstFlg ;
	int				 retSts ;
	int				 idx ;

loging ( "START - ZbmlPrmGetValList\n" ) ;
	idx = 0 ;
	retSts = 1 ;
	seeMem = pMem ;
	*Val = NULL ;
	while ( seeMem != NULL ) {
		if ( strcmp ( seeMem->name, name ) == 0 ) {
			*Val = realloc ( *Val, sizeof ( char * ) * ( idx + 1 ) ) ;
			if ( *Val == NULL ) {
				return ( -1 ) ;
			}
			seeVal = seeMem->valTop ;
			(*Val)[idx] = ( char* )malloc ( sizeof ( char ) * 1024 ) ;
			if ( (*Val)[idx] == NULL ) {
				return ( -1 ) ;
			}
			memset ( (*Val)[idx], '\0', sizeof ( char ) * 1024 ) ; 
			firstFlg = LC_true ;
			while ( seeVal != NULL ) {
				if ( firstFlg == LC_true ) {
					strcpy ( (*Val)[idx], seeVal->val ) ;
					firstFlg = LC_false ;
				}
				else {
					strcat ( (*Val)[idx], "\t" ) ;
					strcat ( (*Val)[idx], seeVal->val ) ;
				}
				seeVal = seeVal->next ;
			}
			retSts = 0 ;
			idx ++ ;
		}
		seeMem = seeMem->next ;
	}
	*cnt = idx ;
loging ( "END   - ZbmlPrmGetValList\n" ) ;
	return retSts ;
}

/******************************************************************************/
/*  関 数 名　：_ZbmlPrmDisp	   										  	  */
/*  機能概要　：環境設定ファイル格納領域表示【デバッグ用】					  */
/*  入　　力　：                                                              */
/*　 第１引数 ：struct  prmMem*	環境設定構造体ポインタ						  */
/*  出　　力　：                                                              */
/*   なし                                                                     */
/*  復帰情報　： 															  */
/*   なし                                                                     */
/******************************************************************************/
void
_ZbmlPrmDisp ( pMem )
BMLPRM	*pMem ;
{
#if defined ( _TRACE )
	struct prmMem	*seeMem ;
	struct prmVal	*seeVal ;

loging ( "START - ZbmlPrmDisp\n" ) ;
	seeMem = pMem ;
	while ( seeMem != NULL ) {
loging ( "      - ##############################\n" ) ;
loging ( "        Name => [%s]\n", seeMem->name ) ;
		seeVal = seeMem->valTop ;
		while ( seeVal != NULL ) {
loging ( "        Val  => [%s]\n", seeVal->val ) ;
			seeVal = seeVal->next ;
		}
		seeMem = seeMem->next ;
	}
loging ( "END   - ZbmlPrmDisp\n" ) ;
#endif
	return ;
}
/** End of File ***************************************************************/
