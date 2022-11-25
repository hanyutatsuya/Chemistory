/**********************************************************************
 *
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：A205syskan.h
 *     機能概要  ：
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#ifndef _A205syskan_h_
#define _A205syskan_h_

#include "bml_DBCom.h"

/*--------------------------------------
// テーブル構造体定義
*/
typedef struct _Sysknrmst {
	char    lbcd[4];
	char    sateid[4];
	char    kjnsriymd[11];
	char    kkkjsriymd[11];		// add 2007.05.31 waj
	char    nxirisriymd[11];
	char    ncnsksriymd[11];
	char    nxbchsriymd[11];
	char    iriendflg;
	char    irienddh[27];
	char    nskendflg;
	char    nskenddh[27];
	char    bchendflg;
	char    bchend0dh[27];
	char    bchend1dh[27];
	char    bchend2dh[27];
	char    bchend3dh[27];
	char    bchend4dh[27];
	char    unyflg;
	sqlint32  ssntubn;
	char    labonm[41];			// add 2007.05.31 waj
    char    knsmngr[41];		// add 2007.05.31 waj
    char    telno[13];			// add 2007.05.31 waj
	char    sriknflg01;
	char    sriknflg02;
	char    sriknflg03;
	char    sriknflg04;
	char    sriknflg05;
	char    sriknflg06;
	char    sriknflg07;
	char    sriknflg08;
	char    sriknflg09;
	char    sriknflg10;
	char    sriknflg11;
	char    sriknflg12;
	char    sriknflg13;
	char    sriknflg14;
	char    sriknflg15;
	char    sriknflg16;
	char    sriknflg17;
	char    sriknflg18;
	char    sriknflg19;
	char    sriknflg20;
    char    hnktntid[9];		// add 2007.05.31 waj
	char    ksndh[27];
}	Sysknrmst;

/*--------------------------------------
 * 関数プロトタイプ
 */
#ifdef __cplusplus
extern "C" {
#endif

long ABunSyskanSelKey( Sysknrmst** arrayOut, int* numOut );
long ABunSyskanUpdate( char *sLbcd, char *sSateid, char flg, char cEndflg );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
