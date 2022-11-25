/******************************************************************************/
/* 　ＢＭＬ様向け検査システム                                                 */
/*                                                                            */
/* 　システム名：次世代システム                                               */
/* 　ファイル名：LD106.h                                                      */
/* 　概　　　要：パラメータ取得ヘッダ                                         */
/******************************************************************************/
/*  Ver.	日付		名前		修正内容			*/
/* -------------------------------------------------------------------------- */
/*  0.00	2016/01/15	BML.Inc		新規作成			*/
/******************************************************************************/
#ifndef _LD106_h
#define _LD106_h
/******************************************************************************/
/* インクルード宣言                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"

#include "LD106_db.h"

/******************************************************************************/
/* Define定義                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"LD101"
#define	MYAPP_APP_NAME_JP		"LD101"
#define	MYAPP_LOGINIFILE		"LD101_LOG.ini"

//  内部ステータスコード定義
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	エラーコード定義
#define	MYAPP_LOG_ERRCODE_NON		"00000000"
#define	MYAPP_LOG_ERRCODE_APP		"010"
#define	MYAPP_LOG_ERRCODE_DB		"020"
#define	MYAPP_LOG_ERRCODE_ETC		"0Z0"

//	パラメータ文字列
#define	MYAPP_PRM_SHM_KEY		"SHM_KEY"
#define	MYAPP_PRM_SLEEP_MIN		"SLEEP_MIN"
#define	MYAPP_PRM_DB_NAME		"DBNAME"
#define	MYAPP_PRM_DB_USER		"DBUSER"
#define	MYAPP_PRM_DB_PASSWD		"DBPASS"
#define	MYAPP_PRM_LOCK_FILE		"LOCK_FILE"
#define MYAPP_PRM_DATE_RANGE		"DATE_RANGE"

//	ディレクトリ格納サイズ
#define	MYAPP_PATH_SIZE			(1024)

//	共有メモリサイズ
#define	MYAPP_SHM_SIZE			sizeof ( int )


#define         SQL_ERR_DUPLICATION	-803
#define         SQL_ERR_LOCK		-911

#define		RET_OK			0
#define         RET_STOP		-1
#define         RET_CONTINUITY		2


#ifndef TRUE
#define FALSE                      (0)  
#ifndef TRUE
#define TRUE            (!FALSE)        
                                        
#endif                                  
#endif                                  

#ifndef _EOS
#define _EOS            ('\0')          
#endif                                  

#ifndef _MAXBUF
#define _MAXBUF                 (4096)  
                                        
                                        
#endif                                  

#define STR_BEGIN_IFBLOCK \
                        ("IF(")         
#define STR_BEGIN_POW	("POW(")
#define STR_BEGIN_LOG	("LOG(")
#define STR_BEGIN_LOG10	("LOG10(")

#define PARENT_BEGIN    ('(')
#define PARENT_END      (')')
#define SPLITTER_COMMA  (':')           
#define OPERATOR_LT     ('<')           
#define OPERATOR_GT     ('>')           
#define OPERATOR_EQ     ('=')           
#define STR_NE          ("<>")          

#define MAXCNT_ITEM_IFBLOCK          5  

struct _IFBLOCK {
    char *pszConditionLeft;             
    char *pszOperator;                  
    char *pszConditionRight;            
    char *pszValueTrue;                 
    char *pszValueFalse;                
    char *pszEndOfList;                 
                                        
};
/******************************************************************************/
/* 構造体定義                                                                 */
/******************************************************************************/
// プログラム環境構造体
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	int	 SleepMin ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ; 
	int	 DateRange;
	char	 cLockFile[MYAPP_PATH_SIZE] ; 
} pAppEnv ;

/******************************************************************************/
/* グローバル宣言                                                             */
/******************************************************************************/

/******************************************************************************/
/* プロトタイプ宣言                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;

double	StringCal_sub(char enzan,double val1,double val2);
double	StringCal(char *CalStr);
int	CHK_Kkacmt(char *);
int	chk_Mojikjn(char *, char);
void	trim(char *, char *);

int	sFncCalc( my_stCALC * );
void	sFncGetdate( char *, char *, int );

int	rngChk(my_stCALC *, my_stKEKKA *);
int	KeisanChk( my_stCALC *, char * , my_stKEKKA * , char * , int , int );
int	filterChk( my_stKEKKA *, my_stKJNMST * );
int	kjnChk( my_stKEKKA *, my_stKJNMST * );
int	BmlPanicChk( my_stCALC *, my_stKEKKA * );
int	KnsPanicChk( my_stCALC *, my_stKEKKA * );

int	ZdbSelCalc( my_stCALC **, int * ) ;
int	ZdbSelCalcOther( char *, char *, my_stCALCSYSMST *, my_stCALC **precCALC, int * ) ;
int	ZdbSelKenorderKekka( my_stCALC *, my_stKEKKA **, int * ) ;
int	ZdbSelKekka( my_stCALC *, my_stKEKKA **, int * ) ;
int	ZdbSelCalcSource ( char *, char *, char *, char *, char *, char *, char *, char *, int ) ;
int	ZdbSelSysKnr ( my_stSYSKNR *) ;
int	ZdbSelCalcsysmst( char *, my_stCALCSYSMST **precCalcsysmst, int * ) ;
int	ZdbSelKjnmst(my_stKEKKA *, my_stKJNMST * );
int	ZdbRngchkmstSelectHnikbn( char *, my_stRNGCHKMST *, my_stRNGCHKMST **, int * ) ;
int	ZdbKkafltmstSelectGRPKMKKey(char *, my_stKKAFLTMST *, my_stKKAFLTMST **, int *);
int	ZdbUpdRecalc( my_stCALC * );
int	ZdbInsNotCalc( my_stCALC * );
int	ZdbGetKsnsk( my_stKEKKA *, char *, int * );
int	ZdbInsCalcKekka( my_stKEKKA * , char *);
int	ZdbUpdCalcKekka( my_stKEKKA * , char *);

#endif
/** End of File ***************************************************************/
