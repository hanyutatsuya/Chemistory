/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：GetMaster.h                                                  */
/* 　概　　　要：マスタ情報取得ヘッダ  	                                      */
/******************************************************************************/
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/06     A.Yamada       新規作成                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     日付           名前           修正内容                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M対応初版                        */
/******************************************************************************/
#ifndef _getmaster_h
#define _getmaster_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include "DD204.h"

/**********************************************************************/
/*  外部参照関数                                                      */
/**********************************************************************/
extern int GetMaster(void);
extern int GetKmkcd( int,char*,char* );
extern int GetNbkmkcd( char*,char* );
extern int GetTstrflg( char*,char*,char* );
extern int GetKnsgrp( char*,char* );
extern int GetSmpcd( char*,char*,char* );
extern int GetOyakmkcd( char*,char*,char* );
extern int GetSeccd( char*,char*,char* );
extern int GetXmcount( char*,char*,int* );
extern int GetYkcd( char*,char* );

#define		MECHMST_FILE_NAME		"mechmst.del"
#define		KINKYU_FILE_NAME		"kinkyu.del"
#define		KMKMST_FILE_NAME		"kmkmst.del"
#define		CTRLMST_FILE_NAME		"ctrlmst.del"
#define		SYSKNRMST_FILE_NAME		"sysknrmst.del"
#define		KNSGMST_FILE_NAME		"knsgmst.del"
#define		KSKBRMST_FILE_NAME		"kskbrmst.del"
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 --> */
/*** X-Mレンジチェックのため追加 ***/
#define		XBARMMST_FILE_NAME		"xbarmmst.del"
/*** 血清レンジチェックのため追加 ***/
#define		RNGCHKMST_FILE_NAME		"rngchkmst.del"
/*	2.00	2008/09/18		K.Ameno		   X-M対応初版 <-- */

#endif /* GetMaster.h */
