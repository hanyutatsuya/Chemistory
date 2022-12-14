/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：bmlprm.h                                                     */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2005/12/26     芳賀弘幸       新規                               */
/******************************************************************************/
#ifndef _bmlprm_h
#define _bmlprm_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/

/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// パラメータ設定値値格納構造体
struct prmVal {
	char			*val ;
	struct prmVal	*next ;
} ;

// パラメータメンバー格納構造体
struct prmMem {
	char			*name ;
	struct prmVal	*valTop ;
	struct prmMem	*next ;
} ;

typedef	struct prmMem	BMLPRM ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
// パラメータオープン関数
BMLPRM *	ZbmlPrmOpen ( char * ) ;
// パラメータクローズ関数
void	 	ZbmlPrmClose ( struct prmMem * ) ;
// パラメータ取得関数
int 		ZbmlPrmGetVal ( struct prmMem * , char *, char *) ;
int			ZbmlPrmGetValList ( struct prmMem *, char *, int *, char *** ) ;

#endif
/** End of File ***************************************************************/
