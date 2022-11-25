/************************************************************************/
/*																		*/
/*		ＢＭＬ様向け検査システム										*/
/*																		*/
/*		システム名	：次世代システム									*/
/*		ファイル名	：bml_com.c											*/
/*		概要		：その他共通関数									*/
/*																		*/
/************************************************************************/

/************************************************************************/
/*  Ver.	日付			名前			修正内容					*/
/* -------------------------------------------------------------------- */
/*  1.00	2005/07/21		E.Osada			Create						*/
/************************************************************************/

/************************************************************************/
/*	インクルード宣言													*/
/************************************************************************/
#include	"bml_base.h
#include	<time.h>
#include	"bml_com.h"

/************************************************************************/
/*	関数宣言															*/
/************************************************************************/

/************************************************************************/
/*	関数名		：ZbmlStrnCpy()											*/
/*	機能概要	：指定バイト数文字列をコピーする						*/
/* 	入力		：														*/
/*	 第１引数   ：char*	pStrOut		文字列のコピー先					*/
/*	 第２引数	：char*	pStrIN		文字列のコピー元					*/
/*	 第３引数	：int	Num			文字列のコピーバイト数				*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlStrnCpy(char* pStrOut, char *pStrIn, int Num)
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
/*	関数名		：ZbmlCharCpy()											*/
/*	機能概要	：キャラクターをコピーする								*/
/*	入力		：														*/
/*	 第１引数	：char*	pCharOut	キャラクターのコピー先				*/
/*	 第２引数	：char*	pCharIN		キャラクターのコピー元				*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlCharCpy(char* pCharOut, char *pCharIn)
{
	if( *pCharIn == '\0' ){
		*pCharOut = ' ';
	}else{
		*pCharOut = *pCharIn;
	}
	return;
}

/************************************************************************/
/*	関数名		：ZbmlGetDateTime()										*/
/*	機能概要	：日付け時間を取得する									*/
/*	入力		：														*/
/*	 第１引数	：char    *pStrOut	日付け時間をセットする				*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlGetDateTime(char *pStrOut)
{
    time_t ltime;
	struct tm *today;
    char			buff[20];

    ltime = time(NULL);
    today = localtime( &ltime );
	strftime( buff, sizeof(buff), "%Y%m%d%H%M%S", today );
    strncpy( pStrOut, buff, 14 );

    return;
}

/************************************************************************/
/*	関数名		：ZbmlGetToday()										*/
/*	機能概要	：本日日付を取得する									*/
/*	入力		：														*/
/*	 第１引数	：char    *pStrOut	本日日付をセットする				*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlGetToday(char *pStrOut)
{
    time_t ltime;
	struct tm *today;

    ltime = time(NULL);
    today = localtime( &ltime );
	strftime( pStrOut, 11, "%Y-%m-%d", today );

    return;
}

/************************************************************************/
/*	関数名		：ZbmlChangeDateDBFormat()								*/
/*	機能概要	：送信データの日付けYYYYMMDDをYYYY-MM-DDに変換する		*/
/*	入力		：														*/
/*	 第１引数	：char	*pStrOut	変換日付を格納するバッファ			*/
/*	 第２引数	：char	*pStrIn		変換元日付							*/
/*	 第３引数	：int	iStrSize	変換元日付のサイズ					*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlChangeDateDBFormat(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];
	void ifInfocpy();

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 8 ){
		return;
	}
	if( memcmp( pStrIn,"00000000",8 ) == 0 ){
		strcpy( pStrOut, "1000-01-01" );
		return;
	}
	bmlInfoCpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%4.4s-%2.2s-%2.2s", buff, &buff[4], &buff[6] );
	}else{
		strcpy( pStrOut, "1000-01-01" );
	}

    return;
}

/************************************************************************/
/*	関数名		：ZbmlChangeYukoDateDBFormat()							*/
/*	機能概要	：送信データの有効日付けYYYYMMDDをYYYY-MM-DDに変換する	*/
/*	入力		：														*/
/*	 第１引数	：char	*pStrOut	変換日付を格納するバッファ			*/
/*	 第２引数	：char	*pStrIn		変換元日付							*/
/*	 第３引数	：int	iStrSize	変換元日付のサイズ					*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlChangeYukoDateDBFormat(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 8 ){
		return;
	}
	if( memcmp( pStrIn,"00000000",8 ) == 0 ){
		strcpy( pStrOut, "9999-12-31" );
		return;
	}
	bmlInfoCpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%4.4s-%2.2s-%2.2s", buff, &buff[4], &buff[6] );
	}else{
		strcpy( pStrOut, "9999-12-31" );
	}

    return;
}

/************************************************************************/
/*	関数名		：ZbmlChangeDateFormat()								*/
/*	機能概要	：DBデータの日付けYYYY-MM-DDをYYYYMMDDに変換する		*/
/*	入力		：														*/
/*	 第１引数	：char    *pStrOut	変換日付を格納するバッファ			*/
/*	 第２引数	：char    *pStrIn		変換元日付						*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlChangeDateFormat(char* pStrOut, char* pStrIn)
{
	pStrOut[0] = '\0';
	if( pStrOut == NULL || pStrIn == NULL ){
		return;
	}
	if( pStrIn[0] != '\0' ){
		sprintf(pStrOut, "%4.4s%2.2s%2.2s", pStrIn, &pStrIn[5], &pStrIn[8] );
	}

    return;
}

/************************************************************************/
/*	関数名		：ZbmlChangeTime()										*/
/*	機能概要	：送信データの時間HHMMSSをHH:MM:SSに変換する			*/
/*	入力		：														*/
/*	 第１引数	：char	*pStrOut	変換時間を格納するバッファ			*/
/*	 第２引数	：char	*pStrIn		変換元時間							*/
/*	 第３引数	：int	iStrSize	変換元時間のサイズ					*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlChangeTime(char* pStrOut, char* pStrIn, int iStrSize)
{
    char			buff[20];
	void ifInfocpy();

	memset( pStrOut, '\0', iStrSize );
	if( pStrOut == NULL || pStrIn == NULL || iStrSize < 6 ){
		return;
	}
	ifInfocpy(buff, pStrIn, iStrSize+1);
	if( buff[0] != '\0' ){
		sprintf(pStrOut, "%2.2s:%2.2s:%2.2s", buff, &buff[2], &buff[4] );
	}

    return;
}

/************************************************************************/
/*	関数名		：ZbmlInfoCpy()											*/
/*	機能概要	：指定バイト数コピー処理（不要なスペースを削除し、		*/
/* 				  '\0'を付加する										*/
/*	入力		：														*/
/*	 第１引数	：char*	pStrOut		コピー先バッファ					*/
/*	 第２引数	：char	*pStrIn		コピー元バッファ					*/
/*	 第３引数	：int	Num			コピーするバイト数					*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
void ZbmlInfoCpy(char* pStrOut, char *pStrIn, int Num)
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

/************************************************************************/
/*	関数名		：ZbmlSetSpace()										*/
/*	機能概要	：指定バイト数スペース詰め処理                          */
/*	入力		：														*/
/*	 第１引数	：char*	pStrOut		セットするバッファ					*/
/*	 第２引数	：int	Num			セットするバイト数					*/
/*	出力		：														*/
/*   なし																*/
/************************************************************************/
DLLEXPORT void bmlSetSpace(char* pStrOut, int Num)
{
	memset( pStrOut, '\0', Num );
	memset( pStrOut, ' ', Num - 1 );
}

/** End of File *********************************************************/
