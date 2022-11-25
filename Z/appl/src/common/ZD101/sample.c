#include <stdio.h>
#include "bmllog.h"

main ( argc, argv )
int		 argc ;
char	*argv[] ;
{

	int	a ;

	struct stcLogMember	mem ;
	//ZbmlCloseLog() ;

	// ログ出力開始
/*
	if ( ZbmlOpenLog(NULL) != 0 ) {
		fprintf ( stderr, "ZbmlOpenLog Error\n" ) ;
		exit ( -1 ) ;
	}

*/

	if ( ZbmlOpenLog(argv[1]) != 0 ) {
		fprintf ( stderr, "ZbmlOpenLog Error\n" ) ;
		exit ( -1 ) ;
	}

	// ログ出力
	memset ( &mem, '\0', sizeof(mem)) ;
	mem.eTrcKind = 'D' ;
	strcpy ( mem.pcFncName,"D_functionName" ) ;
	strcpy ( mem.pcLoginId,"D_login" ) ;
	strcpy ( mem.pcAppName,"D_appName" ) ;
	strcpy ( mem.pcExeFlg,EXEFLG_SEL ) ;
	strcpy ( mem.pcErrCode,"D_000000" ) ;
	strcpy ( mem.pcMsg,"D_Message" ) ;
	ZbmlPutLog ( &mem ) ;

	memset ( &mem, '\0', sizeof(mem)) ;
	mem.eTrcKind = 'T' ;
	strcpy ( mem.pcFncName,"T_functionName" ) ;
	strcpy ( mem.pcLoginId,"T_login" ) ;
	strcpy ( mem.pcAppName,"T_appName" ) ;
	strcpy ( mem.pcExeFlg,EXEFLG_INS ) ;
	strcpy ( mem.pcErrCode,"T_000000" ) ;
	strcpy ( mem.pcMsg,"T_Message" ) ;
	ZbmlPutLog ( &mem ) ;

	memset ( &mem, '\0', sizeof(mem)) ;
	mem.eTrcKind = 'O' ;
	strcpy ( mem.pcFncName,"O_functionName" ) ;
	strcpy ( mem.pcLoginId,"O_login" ) ;
	strcpy ( mem.pcAppName,"O_appName" ) ;
	strcpy ( mem.pcExeFlg,EXEFLG_UPD ) ;
	strcpy ( mem.pcErrCode,"O_000000" ) ;
	strcpy ( mem.pcMsg,"O_Message" ) ;
	ZbmlPutLog ( &mem ) ;

	memset ( &mem, '\0', sizeof(mem)) ;
	mem.eTrcKind = 'W' ;
	strcpy ( mem.pcFncName,"W_functionName" ) ;
	strcpy ( mem.pcLoginId,"W_login" ) ;
	strcpy ( mem.pcAppName,"W_appName" ) ;
	strcpy ( mem.pcExeFlg,EXEFLG_DEL ) ;
	strcpy ( mem.pcErrCode,"W_000000" ) ;
	strcpy ( mem.pcMsg,"W_Message" ) ;
	ZbmlPutLog ( &mem ) ;

	memset ( &mem, '\0', sizeof(mem)) ;
	mem.eTrcKind = 'E' ;
	strcpy ( mem.pcFncName,"E_functionName" ) ;
	strcpy ( mem.pcLoginId,"E_login" ) ;
	strcpy ( mem.pcAppName,"E_appName" ) ;
	strcpy ( mem.pcExeFlg,EXEFLG_DEL ) ;
	strcpy ( mem.pcErrCode,"E_000000" ) ;
	strcpy ( mem.pcMsg,"E_Message" ) ;
	ZbmlPutLog ( &mem ) ;

	memset ( &mem, '\0', sizeof(mem)) ;
	mem.eTrcKind = 'A' ;
	strcpy ( mem.pcFncName,"A_functionName" ) ;
	strcpy ( mem.pcLoginId,"A_login" ) ;
	strcpy ( mem.pcAppName,"A_appName" ) ;
	strcpy ( mem.pcExeFlg,EXEFLG_DEL ) ;
	strcpy ( mem.pcErrCode,"A_000000" ) ;
	strcpy ( mem.pcMsg,"A_Message" ) ;
	ZbmlPutLog ( &mem ) ;

	// ログ出力終了
	ZbmlCloseLog() ;
}
