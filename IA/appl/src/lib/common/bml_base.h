/********************************************************************/
/*																	*/
/*		ＢＭＬ様向け検査システム									*/
/*																	*/
/*		システム名	：次世代システム								*/
/*		ファイル名	：bml_base.h									*/
/*		概要		：次世代プロジェクトのベースヘッダーファイル	*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	作成日			名前			修正内容				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2005/06/14		E.Osada			Create					*/
/*  		2006/02/20		H.Haga			define追加				*/
/*											関数リターン値			*/
/*											日付初期値				*/
/********************************************************************/
#ifndef _bml_base_h
#define _bml_base_h

/********************************************************************/
/*	インクルード宣言												*/
/********************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef DEBUG
#include <unistd.h>
#endif
#include <time.h>
#include <fcntl.h>
#include <sql.h>

/********************************************************************/
/*	ｄｅｆｉｎｅ宣言												*/
/********************************************************************/
#define FALSE  0
#define TRUE   1
#define DLLEXPORT
#define DLLIMPORT
#define STRDUP(s) (s) ? strdup(s) : NULL
#define STRFREE(s) if (s) free(s)
#define HNEW(type)   (type*)huCalloc(sizeof(type), 1)
#define HDELETE(ptr) huFree(ptr)

/*	<< 関数リターン値 >>	*/
#define	RTN_OK			  0							/* 正常終了     */
#define	RTN_NG			 -1							/* 異常終了     */
#define	RTN_SKIP		 -2							/* 処理スキップ */
#define	RTN_DBERR		-10							/* ＤＢエラー   */
#define	RTN_MEMERR		-20							/* メモリエラー */
#define	RTN_ZERO		100							/* ０件         */

/*	<< 日付初期値 >>	*/
#define	INIT_DATE		"1000-01-01"				/* DATE　初期値 */
#define	INIT_TIME		"00:00:01"					/* TIME  初期値 */
#define	INIT_TIMESTAMP	"1000-01-01 00:00:01"	 	/* TIMESTAMP初期値 */

//  性別区分
#define	SEX_MALE		"0"							// 男性
#define	SEX_FEMALE		"1"							// 女性
#define	SEX_UNKNOWN		"9"							// 不明

//  年齢区分
#define	AGEKBN_YEAR		"Y"							// 年齢
#define	AGEKBN_MONTH	"M"							// 月齢
#define	AGEKBN_WEEK		"W"							// 週齢
#define	AGEKBN_DAY		"D"							// 日齢
#define	AGEKBN_UNKNOWN	"Z"							// 不明

/********************************************************************/
/*	ｔｙｐｅｄｅｆ宣言												*/
/********************************************************************/
typedef char					CHAR;
typedef unsigned char			BYTE;
typedef short					SHORT;
typedef unsigned short			USHORT;
typedef int						INT;
typedef unsigned int			UINT;
typedef long					LONG;
typedef unsigned long			ULONG;
typedef long long				LONGLONG;
typedef unsigned long long		ULONGLONG;
typedef float					FLOAT;
typedef double					DOUBLE;
typedef long double				DDOUBLE;
typedef _Bool					BOOL;
typedef void*					HANDLE;

#endif
/** End of File *****************************************************/
