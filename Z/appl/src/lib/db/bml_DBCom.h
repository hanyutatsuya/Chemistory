/**********************************************************************
 *                                                                    
 *     ＢＭＬ様向け検査システム
 *
 *     システム名：次世代
 *     ファイル名：bml_DBCom.h
 *     概要      ：DB共通関数ヘッダファイル
 *                                                                    
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2005/06/14     E.Osada        Create
 **********************************************************************/
#ifndef _bml_DBCom_h
#define _bml_DBCom_h

#include "bml_dbrc.h"
#include "bml_base.h"

#ifdef __cplusplus
extern "C" {
#endif

long ZdbConnect ( char* dbname, char* uname, char* pswd );
BOOL ZdbDisConnect(void);

void ZdbCommit(void);
void ZdbRollback(void);
void ZdbPrintSqlErr( char* file, int line, struct sqlca* sqlca );

#ifdef __cplusplus
}
#endif

#endif
/** End of File *********************************************************/
