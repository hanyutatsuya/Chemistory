/************************************************************************/
/*																		*/
/*		ＢＭＬ様向け検査システム										*/
/*																		*/
/*		システム名：次世代												*/
/*		ファイル名：bml_misc.c											*/
/*		概要      ：その他共通関数										*/
/************************************************************************/

/************************************************************************/
/*	Ver.	日付			名前			修正内容					*/
/* --------------------------------------------------------------------	*/
/*	1.00	2005/06/14		E.Osada			Create						*/
/*			2006/01/31		E.Osada			bmlStrCpy()追加				*/
/************************************************************************/

/************************************************************************/
/*	インクルード定義													*/
/************************************************************************/
#include <stdlib.h>
#include <memory.h>
#include <bml_misc.h>

/************************************************************************/
/*	関数名		：ZbmlMalloc()											*/
/*	機能概要	：指定されたサイズ分の領域を確保する					*/
/*	入力																*/
/*	 第１引数   :　size_t size   領域確保サイズ							*/
/*	出力 																*/
/*	 確保した領域のアドレスを返す										*/
/************************************************************************/
void * ZbmlMalloc( size_t size )
{
		return( malloc( size ) );
}

/************************************************************************/
/*	関数名		：ZbmlMalloc()											*/
/*	機能概要	：指定されたサイズ分の領域を指定された個数分確保する	*/
/*	入力																*/
/*	 第１引数	：size_t count	領域確保個数							*/
/*	 第２引数	：size_t size	領域確保サイズ							*/
/*	出力 																*/
/*	 確保した領域のアドレスを返す										*/
/************************************************************************/
void * ZbmlCalloc( size_t count,size_t size )
{
		return( calloc( count,size ) );
}

/************************************************************************/
/*	関数名		：ZbmlRealloc()											*/
/*	機能概要	：指定された領域を指定サイズに変更確保する				*/
/*	入力																*/
/*	 第１引数	：void*		area   領域ポインタ							*/
/*	 第２引数	：size_t	size   領域確保サイズ						*/
/*	出力																*/
/*	 確保した領域のアドレスを返す										*/
/************************************************************************/
void * ZbmlRealloc( void *area, size_t size )
{
		return( realloc( area, size ) );
}

/************************************************************************/
/*	関数名		：ZbmlFree()											*/
/*	機能概要	：指定された領域を解放する								*/
/*	入力																*/
/*	 第１引数   :　void* area   領域ポインタ							*/
/*	出力																*/
/*	 なし																*/
/************************************************************************/
void ZbmlFree( void *area )
{
		free( area );
		return;
}

/************************************************************************/
/*	全角→半角変換関数用のｄｅｆｉｎｅ＆配列定義						*/
/************************************************************************/
#define	SPACE1	0x81
#define	SPACE2	0x40
#define	YEN1	0x81
#define	YEN2	0x8f
#define	A_YEN	0x5c
#define	OPAR1	0x81
#define	OPAR2	0x69
#define	A_OPAR	0x28
#define	CPAR1	0x81
#define	CPAR2	0x6a
#define	A_CPAR	0x29

typedef unsigned char uc;

uc ztable1[256] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x00 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x10 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x20 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x30 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x20, 0xff, 0xff, 0x2c, 0x2e, 0xff, 0x3a, 0x3b,	/* 0x40 */
	0x3f, 0x21, 0xff, 0xff, 0xff, 0xff, 0xff, 0x5e,
	0x7e, 0x5f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x50 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x2f, 0x5c,
	0xff, 0xff, 0x7c, 0xff, 0xff, 0x60, 0x27, 0xff,	/* 0x60 */
	0x22, 0xff, 0xff, 0xff, 0xff, 0x5b, 0x5d, 0x7b,
	0x7d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x70 */
	0xff, 0xff, 0xff, 0x2b, 0x2d, 0xff, 0xff, 0xff,
	0xff, 0x3d, 0xff, 0x3c, 0x3e, 0xff, 0xff, 0xff,	/* 0x80 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x24, 0xff, 0xff, 0x25, 0x23, 0x26, 0x2a, 0x40,	/* 0x90 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xa0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xb0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xc0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xd0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xe0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xf0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

uc ztable2[256] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x00 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x10 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x20 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x30 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0x40 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x30,
	0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,	/* 0x50 */
	0x39, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,	/* 0x60 */
	0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,	/* 0x70 */
	0x59, 0x5a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,	/* 0x80 */
	0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,	/* 0x90 */
	0x78, 0x79, 0x7a, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xa0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xb0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xc0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xd0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xe0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	/* 0xf0 */
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};
#define	isAscii(c)	(((c) >= 0x20 && (c) <= 0x7e) ? 1 : 0)

/************************************************************************/
/*	関数名		：bmlZen2Han()											*/
/*	機能概要	：文字列内の全角文字を半角文字に変換する				*/
/*                変換できない文字はスキップする						*/
/*	入力																*/
/*	 第１引数	：char* psString   変換対象文字列						*/
/*	 第２引数	：int nMasLen      文字列バッファ格納最大長				*/
/*	出力																*/
/*	 変換後のpStringを返す												*/
/************************************************************************/
char* ZbmlZen2Han( char* psString, int nMaxLen )
{
	char	sBuf[4096] = "";
	char*	pDest = sBuf;
	char*	p = psString;
	uc		*ztable;

	if(!psString) {
		return NULL;
	}

	while(*p){
		register short int	c1;
		register short int	c2;

		c1 = *p & 0xff;
		if(isAscii(c1)){		/* ascii */
			memcpy(pDest++, p++, 1);
			continue;
		}
		if(c1 != 0x81 && c1 != 0x82){	/* not a target */
			memcpy(pDest, p, 2);
			p += 2;
			pDest += 2;
			continue;
		}
		c2 = *(++p) & 0xff;
		if(c1 == YEN1 && c2 == YEN2){ /* convert YEN */
			*(pDest++) = A_YEN;
			p++;
			continue;
		}
		if(c1 == OPAR1 && c2 == OPAR2){ /* convert PARENTHESIS */
			*(pDest++) = A_OPAR;
			p++;
			continue;
		}
		if(c1 == CPAR1 && c2 == CPAR2){ /* convert PARENTHESIS */
			*(pDest++) = A_CPAR;
			p++;
			continue;
		}
		if(c1 == 0x81)
			ztable = ztable1;
		else
			ztable = ztable2;
		if(ztable[c2] == 0xff){
			*(pDest++) = (char)c1;
			*(pDest++) = (char)c2;
		}
		else
			*(pDest++) = ztable[c2];
		p++;
	}

	nMaxLen -= nMaxLen % 2;
	strncpy( psString, sBuf, nMaxLen );

	return psString;
}
/************************************************************************/
/*	関数名		：ZbmlStrCpy()											*/
/*	機能概要	：指定バイト数文字列をコピーする(後ろスペース詰め)		*/
/*	入力																*/
/*	 第１引数   :　char*	pStrOut		文字列のコピー先				*/
/*	 第２引数   :　char*	pStrIN		文字列のコピー元				*/
/*	 第３引数   :　int		Num			文字列のコピーバイト数			*/
/*	出力																*/
/*	 無し																*/
/************************************************************************/
void ZbmlStrCpy(char* pStrOut, char *pStrIn, int Num)
{
	int		i;

	memset( pStrOut, ' ', Num ); 
	for( i = 0 ;i < Num; i++ ){
		if( *pStrIn == '\0' ){
			return;
		}
		*pStrOut = *pStrIn;
		pStrOut++;
		pStrIn++;
	}
	return;
}
/************************************************************************/
/*	関数名		：ZbmlChgDBDate()										*/
/*	機能概要	：データの日付YYYYMMDDをYYYY-MM-DDに変換する			*/
/*	入力																*/
/*	 第１引数   :　char    *pStrOut		変換日付を格納するバッファ		*/
/*	 第２引数   :　char    *pStrIn		変換元日付						*/
/*	 第３引数   :　int		iStrSize	変換元日付のサイズ				*/
/*	出力																*/
/*	 無し																*/
/************************************************************************/
void ZbmlChgDBDate(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 8 ){
		return;
	}
	if( memcmp( pStrIn,"00000000",8 ) == 0 ){
		strcpy( pStrOut, "1000-01-01" );
		return;
	}
	ZbmlInfocpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' && buff[0] != ' ' ){
		sprintf(pStrOut, "%4.4s-%2.2s-%2.2s", buff, &buff[4], &buff[6] );
	}else{
		strcpy( pStrOut, "1000-01-01" );
	}

    return;
}

/************************************************************************/
/*	関数名		：ZbmlChgAPDate()									*/
/*	機能概要	：DBデータの日付けYYYY-MM-DDをYYYYMMDDに変換する		*/
/*	入力																*/
/*	 第１引数   :　char    *pStrOut	変換日付を格納するバッファ			*/
/*	 第２引数   :　char    *pStrIn		変換元日付						*/
/*	出力																*/
/*	 無し																*/
/************************************************************************/
void ZbmlChgAPDate(char* pStrOut, char* pStrIn)
{
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	pStrOut[0] = '\0';
	if( pStrIn[0] != '\0' ){
		sprintf(pStrOut, "%4.4s%2.2s%2.2s", pStrIn, &pStrIn[5], &pStrIn[8] );
	}

    return;
}

/************************************************************************/
/*	関数名		：ZbmlChgDBtime()										*/
/*	機能概要	：データの時間HHMMSSをHH:MM:SSに変換する				*/
/*	入力																*/
/*	 第１引数   :　char    *pStrOut	変換時間を格納するバッファ			*/
/*	 第２引数   :　char    *pStrIn		変換元時間						*/
/*	 第３引数   :　int		iStrSize	変換元時間のサイズ				*/
/*	出力																*/
/*	 無し																*/
/************************************************************************/
void ZbmlChgDBTime(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 6 ){
		return;
	}
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	if( memcmp( pStrIn,"00000000",6 ) == 0 ){
		strcpy( pStrOut, "00:00:01" );
		return;
	}
	ZbmlInfocpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%2.2s:%2.2s:%2.2s", buff, &buff[2], &buff[4] );
	} else {
		strcpy( pStrOut, "00:00:01" );
	}

    return;
}
/************************************************************************/
/*	関数名		：ZbmlChgAPtime()										*/
/*	機能概要	：データの時間HH:MM:SSをHHMMSSに変換する				*/
/*	入力																*/
/*	 第１引数   :　char    *pStrOut	変換時間を格納するバッファ			*/
/*	 第２引数   :　char    *pStrIn		変換元時間						*/
/*	出力																*/
/*	 無し																*/
/************************************************************************/
void ZbmlChgAPTime(char* pStrOut, char* pStrIn)
{
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	pStrOut[0] = '\0';
	if( pStrIn[0] != '\0' ){
		sprintf(pStrOut, "%2.2s%2.2s%2.2s", pStrIn, &pStrIn[3], &pStrIn[6] );
	}

    return;
}
/************************************************************************/
/*	関数名		：ZbmlInfocpy()											*/
/*	機能概要	：指定バイト数コピー処理								*/
/*				  (不要なスペースを削除し、'\0'を付加する)				*/
/*	入力																*/
/*	 第１引数   :　char* pStrOut	コピー先バッファ					*/
/*	 第２引数   :　char *pStrIn	コピー元バッファ						*/
/*	 第３引数   :　int Num			コピーするバイト数					*/
/*	出力																*/
/*	 無し																*/
/************************************************************************/
void ZbmlInfocpy(char* pStrOut, char *pStrIn, int Num)
{
	int		i;
	BOOL	bSpace;

	memset( pStrOut, '\0', Num );
	bSpace = FALSE;	
	for( i = Num-2 ;i >= 0; i-- ){
		//余分なスペースをカット
		if( pStrIn[i] == ' ' && bSpace == FALSE ){	
			pStrOut[i] = '\0';
			continue;
		}
		bSpace = TRUE;	
		pStrOut[i] = pStrIn[i];
	}
	return;
}

/** End of File *********************************************************/
