/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����Flib_log.c                                                    */
/* �@�T�@�@�@�v�F���O�o�̓��C�u����                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2005/12/21     �F��O�K       �V�K�쐬                           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <iconv.h>
#include <limits.h>

#include "bmllog.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
//	TRACE
#if defined ( _TRACE )
#define malloc(a)   _malloc(a, __FILE__, __LINE__)
#define free(p)     _free(p, __FILE__, __LINE__)
#endif

//  �t���O��`
typedef enum {
    LC_false,
    LC_true
} LC_BOOLEAN ;

//	�t�@�C�����u��������
#define		MY_YEAR_4	"%YYYY%"
#define		MY_YEAR_2	"%YY%"
#define		MY_MON		"%MM%"
#define		MY_DAY		"%DD%"
#define		MY_HOUR		"%HH%"
#define		MY_MIN		"%MI%"
#define		MY_SEC		"%SS%"

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/
static int	sFncIniFileRead ( char * ) ;
static int	sFncDbWrite ( char *, struct stcLogAPLLOG * ) ;
static void sFncFilenameRep ( char *, char *, struct tm * ) ;
void loging ( char *, ... );

/******************************************************************************/
/*  �� �� ���@�FZbmlOpenLog()												  */
/*  �@�\�T�v�@�F���O���J�n����B											  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *pcIniFileName �y�K�{�z�������t�@�C�������w�肷��		  */
/*  �o�@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���@�F int                                                          */
/* �@�@�@�@�@�@�@ 0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int 
ZbmlOpenLog( pcIniFileName )
char	*pcIniFileName ;
{
	char		*pcPath ;
	char		 cIniFileName[256];

loging ( "START - ZbmlOpenLog\n") ;

	/***
	 ***	��������
	 ***/
	//	�����`�F�b�N
	if ( gpstLogEnv != NULL ) {
loging ( "END   - ZbmlOpenLog[-1]\n") ;
		return ( -1 ) ;
	}
	//	 ���O���\���̗̈�A���P�[�V����
	gpstLogEnv = ( struct stcLogEnv * ) malloc ( sizeof ( struct stcLogEnv ) ) ;
	if ( gpstLogEnv == NULL ) {
loging ( "END   - ZbmlOpenLog[-1]\n") ;
		return ( -1 ) ;
	}
	memset ( gpstLogEnv, '\0', sizeof ( struct stcLogEnv ) ) ;

	//	 ���ϐ����INI�t�@�C���i�[�f�B���N�g��
	pcPath = getenv ( BML_LOGINIPATH ) ;
	if ( pcPath == NULL ) {
		strcpy ( cIniFileName, pcIniFileName ) ;
	} else {
		sprintf ( cIniFileName, "%s/%s", pcPath, pcIniFileName ) ;
	}

	/***
	 ***	�����R�[�h�ϊ��Ή��iEUC->SJIS)	
	 ***/
	gpstLogEnv->cd = iconv_open ( "SHIFT-JIS", "EUC-JP" ) ;
	if ( gpstLogEnv->cd == (iconv_t)(-1) ) {
		return ( -1 ) ;
	}

	/***
	 ***	���C������
	 ***/
	if ( sFncIniFileRead( cIniFileName ) != 0 ) {
loging ( "END   - ZbmlOpenLog[-1]\n") ;
		return ( -1 ) ;
	}

	/***
	 ***	�I������
	 ***/
loging ( "END   - ZbmlOpenLog[0]\n") ;
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FZbmlPutLog()												  */
/*  �@�\�T�v�@�F���O�������擾											  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *pcLogName    	�y�C�Ӂz���O�t�@�C�������w�肷��B		  */
/*									��NULL���w�肵���ꍇ��INI�t�@�C�����	  */
/*									  ���O�����擾����B					  */
/*  �o�@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���@�F int                                                          */
/* �@�@�@�@�@�@�@ 0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
int 
_ZbmlPutLog( pstLogMem, file, line )
struct stcLogMember *pstLogMem ;
char				*file ;
long				 line ;
{
	LC_BOOLEAN			 logdbPutFlg ;		
	LC_BOOLEAN			 logPutFlg ;		
	FILE				*fp ;
	char				 filename[256] ;
	char				 repFilename[256] ;
	char				 dbOutFilename[256] ;
	struct stcLogInfo	*seeLogInfo ;

	struct stcLogAPLLOG	 recAPLLOG ;
	char				 cHostname[256+1] ;
	pid_t				 tPid ;					 
	struct tm			*timepos ;
	struct timeb		 timebuf ;

	char			 MsgEUC[1024+1];
	char			*pMsgEUC ;
	size_t			 MsgEUClen;

	char			 MsgSJIS[1024+1];
	char			*pMsgSJIS ;
	size_t			 MsgSJISlen;

loging ( "START - ZbmlPutLog\n") ;
	/***
	 ***	��������
	 ***/
	//	�p�����[�^�`�F�b�N
	if ( pstLogMem == NULL ) {
loging ( "END   - ZbmlPutLog[-1]\n") ;
		return ( -1 ) ;
	}	

	//	�I�[�v������Ă��Ȃ��ꍇ
	if ( gpstLogEnv == NULL ) {
loging ( "END   - ZbmlPutLog[-1]\n") ;
		return ( -1 ) ;
	}

	//	�����擾
	ftime ( &timebuf ) ;
	timepos = ( struct tm * ) localtime ( &( timebuf.time ) ) ;

	//	�z�X�g���擾	
	gethostname ( cHostname, sizeof ( cHostname ) ) ;

	//	�v���Z�X�h�c
	tPid = getpid() ;

	//	�ϐ�������
	logdbPutFlg = LC_false ;
	logPutFlg 	= LC_false ;

	//	�g���[�X��ʂ�胍�O���擾
	seeLogInfo = gpstLogEnv->topLoginfo ;
	while ( seeLogInfo != NULL ) {
		if ( seeLogInfo->eTrcKind == pstLogMem->eTrcKind ) {
			break ;
		}
		seeLogInfo = seeLogInfo->next ;
	}
	if ( seeLogInfo == NULL ) {
		return ( -1 ) ;
	}
	//	���O�o�̓��x������
	if ( seeLogInfo->iLogLv >= gpstLogEnv->iLogOutLv ) {
		logPutFlg = LC_true ;
		strcpy ( filename, seeLogInfo->pcLogName ) ;
	}
	//	���O�e�[�u���o�̓��x������
	if ( seeLogInfo->iLogLv >= gpstLogEnv->iDBOutLv ) {
		logdbPutFlg = LC_true ;
	}
loging ( "      - ���O�t�@�C��-INI[%s]\n", filename) ;
loging ( "                     TRC[%c]\n", seeLogInfo->eTrcKind) ;
loging ( "                     LV [%d]\n", seeLogInfo->iLogLv) ;

	/***
	 ***	���O�o�͏���
	 ***/
	if ( logPutFlg == LC_true ) {
		//	�t�@�C�����u��
		sFncFilenameRep ( filename, repFilename, timepos ) ;
		fp = fopen ( repFilename, "a" ) ;
		if ( fp == NULL ) {
			return ( -1 ) ;
		}

		fprintf ( fp , "%04d/%02d/%02d\t%02d:%02d:%02d\t%c\t%s\t%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%s\t%s\n",
						timepos->tm_year + 1900, 
						timepos->tm_mon + 1, 
						timepos->tm_mday,
						timepos->tm_hour, 
						timepos->tm_min, 
						timepos->tm_sec,
						pstLogMem->eTrcKind,
						cHostname,
						tPid,
						pstLogMem->pcLoginId,
						pstLogMem->pcAppName,
						file,
						pstLogMem->pcFncName,
						line,
						pstLogMem->pcExeFlg,
						pstLogMem->pcErrCode,
						pstLogMem->pcMsg ) ;

		fclose ( fp ) ;
	}

	/***
	 ***	���O�e�[�u���o��	
	 ***/
	if ( logdbPutFlg == LC_true ) {
loging ( "      - ���O�e�[�u���o��\n") ;
		//	�t�@�C�����쐬(�N���������b�~���b�o�h�c.log)
		sprintf ( dbOutFilename, "%02d%02d%02d%02d%02d%02d%03d%06d%s",
							( timepos->tm_year + 1900 ) % 100, 
							timepos->tm_mon + 1, 
							timepos->tm_mday,
							timepos->tm_hour, 
							timepos->tm_min, 
							timepos->tm_sec,
							timebuf.millitm,
							tPid,
							BML_SFX_DBFILE ) ;

		//	�f�[�^�ݒ�
		memset ( &recAPLLOG, '\0', sizeof ( recAPLLOG ) ) ;
		sprintf ( recAPLLOG.sydate, "%04d-%02d-%02d", timepos->tm_year + 1900, 
													timepos->tm_mon + 1, 
													timepos->tm_mday ) ;
		sprintf ( recAPLLOG.sytime, "%02d:%02d:%02d", timepos->tm_hour, 
													timepos->tm_min, 
													timepos->tm_sec ) ;
		recAPLLOG.tracekbn[0] = pstLogMem->eTrcKind ;
		strcpy ( recAPLLOG.pcname, cHostname ) ;
		//recAPLLOG.proccessid = tPid ;
		sprintf ( recAPLLOG.proccessid, "%d", tPid ) ;
		strcpy ( recAPLLOG.loginid, pstLogMem->pcLoginId ) ;
		strcpy ( recAPLLOG.wkupapp, pstLogMem->pcAppName ) ;
		strncpy ( recAPLLOG.srcname, file, sizeof ( recAPLLOG.srcname ) - 1 ) ;
		strncpy ( recAPLLOG.funcname, pstLogMem->pcFncName, sizeof (recAPLLOG.funcname ) - 1 ) ;
		//recAPLLOG.getline = line ;
		sprintf ( recAPLLOG.getline, "%ld", line ) ;
		strcpy ( recAPLLOG.procflg, pstLogMem->pcExeFlg ) ;
		strcpy ( recAPLLOG.errcode, pstLogMem->pcErrCode ) ;
		//�����R�[�h�ϊ��Ή��iEUC->SJIS�j
		pMsgEUC  = MsgEUC ;
		pMsgSJIS = MsgSJIS ;
		memset ( MsgEUC,  '\0', sizeof ( MsgEUC ) ) ;
		memset ( MsgSJIS, '\0', sizeof ( MsgEUC ) ) ;
		strcpy ( MsgEUC, pstLogMem->pcMsg ) ;
		MsgEUClen  = strlen ( MsgEUC ) ;
		MsgSJISlen = sizeof ( MsgSJIS ) -1 ;
		if ( iconv ( gpstLogEnv->cd,
			     &pMsgEUC,  &MsgEUClen, 
			     &pMsgSJIS, &MsgSJISlen ) == -1 ) {
			return ( -1 ) ;
		}
		strcpy ( recAPLLOG.message, MsgSJIS ) ;
		//strcpy ( recAPLLOG.message.data, pstLogMem->pcMsg ) ;
		//recAPLLOG.message.length = strlen ( pstLogMem->pcMsg ) ;
		sFncDbWrite ( dbOutFilename, &recAPLLOG ) ;
	}

loging ( "END   - ZbmlPutLog[0]\n") ;

	/***
	 ***	�I������
	 ***/
	return ( 0 ) ;

}
/******************************************************************************/
/*  �� �� ���@�FZbmlCloseLog												  */
/*  �@�\�T�v�@�F���O�������J��											  */
/*  ���@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  �o�@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���@�F ����                                                         */
/******************************************************************************/
void 
ZbmlCloseLog()
{
	struct stcLogInfo	*seeLogInfo ;
	struct stcLogInfo	*freeLogInfo ;

	/***
	 ***	�����R�[�h�ϊ��N���[�Y
	 ***/
	iconv_close ( gpstLogEnv->cd ) ;

loging ( "START - ZbmlCloseLog\n") ;
	/***
	 ***	�A���P�[�g�̈�J��
	 ***/
	//	�I�[�v������Ă��Ȃ��ꍇ
	if ( gpstLogEnv == NULL ) {
loging ( "END   - ZbmlCloseLog\n") ;
		return ;
	}

	//	���O�\���̕�
	seeLogInfo = gpstLogEnv->topLoginfo ;
	while ( seeLogInfo != NULL ) {
		freeLogInfo = seeLogInfo ;
		seeLogInfo = seeLogInfo->next ;
		free ( freeLogInfo ) ;
	}

	//	���O���\����
	free ( gpstLogEnv ) ;
	gpstLogEnv = NULL ;
loging ( "END   - ZbmlCloseLog\n") ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncDbWrite													  */
/*  �@�\�T�v�@�F�c�a�o�^�t�@�C�����o�͂���									  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fchar *pcLogName    	�y�C�Ӂz���O�t�@�C�������w�肷��B		  */
/*									��NULL���w�肵���ꍇ��INI�t�@�C�����	  */
/*									  ���O�����擾����B					  */
/*  �o�@�@�́@�F                                                              */
/*   �Ȃ�                                                                     */
/*  ���A���@�F int                                                          */
/* �@�@�@�@�@�@�@ 0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
static int	
sFncDbWrite ( pdbOutFilename, precApllog )
char				 *pdbOutFilename ;
struct stcLogAPLLOG	 *precApllog ;
{

	FILE					*fp ;
	char					 dbOutPath[256] ;


	/***
	 ***	��������
	 ***/
	//	�t�@�C�����쐬
	if ( gpstLogEnv->pcDBOutFilePath[0] == '\0' ) {
		strcpy ( dbOutPath, pdbOutFilename ) ;
	} else {
		sprintf ( dbOutPath, "%s/%s", gpstLogEnv->pcDBOutFilePath, pdbOutFilename ) ;
	}

	/***
	 ***	�t�@�C���I�[�v��
	 ***/
	fp = fopen ( dbOutPath, "ab" ) ;
	if ( fp == NULL ) {
		return ( -1 ) ;
	}


	/***
	 ***	�t�@�C���o��
	 ***/
	if ( fwrite ( precApllog, sizeof ( struct stcLogAPLLOG ), 1, fp ) <= 0 ) {
		return ( -1 ) ;
	}


	/***
	 ***	�t�@�C���N���[�Y
	 ***/
	fclose ( fp ) ;

	return( 0 ) ;

}
/******************************************************************************/
/*  �� �� ���@�FsFncIniFileRead												  */
/*  �@�\�T�v�@�F���O�����t�@�C���ǂݍ���									  */
/*  ���@�@�́@�F ����                                                         */
/*  �o�@�@�́@�F ����                                                         */
/*  ���A���@�F int                                                          */
/* �@�@�@�@�@�@�@ 0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
static	int
sFncIniFileRead ( pcIniFileName )
char	*pcIniFileName ;
{
	FILE				 *fp ;
	int					  idx ;
	char				  buf[ 1024 ] ;
	char				 *cp[ 10 ] ;
	char				 *p ;
	struct stcLogInfo	**make ;
	struct stcLogInfo	 *see ;

loging ( "      - �h�m�h�t�@�C���Ǎ�[sFncIniFileRead]\n") ;
	/***
	 ***	��������
	 ***/
	//	�o�̓��x��������
	gpstLogEnv->iLogOutLv = INT_MAX ;
	gpstLogEnv->iDBOutLv = INT_MAX ;

	make = &( gpstLogEnv->topLoginfo ) ;

	/***
	 ***	�h�m�h�t�@�C���I�[�v��
	 ***/
	fp	= fopen ( pcIniFileName, "r" ) ;
	if ( fp == NULL ) {
		return ( -1 ) ;
	}


	/***
	 ***	�h�m�h�t�@�C���ǂݍ���
	 ***/
	while ( fgets ( buf, sizeof ( buf ), fp ) != NULL ) {
		// �R�����g�ǂݔ�΂�
		if ( buf[ 0 ] == '#' || buf[ 0 ] == '\n' || buf[ 0 ] == '\0' ) {
			continue ;
		}

		//	�g�[�N������
		idx = 0 ;
		p = buf ;
		memset ( cp, '\0', sizeof ( cp ) ) ;
		while ( ( cp[ idx ] = strtok ( p,     " \t\n" ) ) != NULL ) {
			p = NULL ;
			idx ++ ;
		}
		if ( cp[0] == NULL ) {
			continue ;
		}

		//	���O���\���ݒ��
		if ( strcmp ( cp[0], BML_LOGINI_ENV1 ) == 0 ) {
			if ( cp[1] == NULL ) {
				gpstLogEnv->iLogOutLv = INT_MAX ;
			} else if ( cp[1][0] == '\0' ) {
				gpstLogEnv->iLogOutLv = INT_MAX ;
			} else {
				gpstLogEnv->iLogOutLv = atoi ( cp[1] ) ;
			}  
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV2 ) == 0 ) {
			if ( cp[1] == NULL ) {
				gpstLogEnv->iDBOutLv = INT_MAX ;
			} else if ( cp[1][0] == '\0' ) {
				gpstLogEnv->iDBOutLv = INT_MAX ;
			} else {
				gpstLogEnv->iDBOutLv = atoi ( cp[1] ) ;
			}
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV3 ) == 0 ) {
			strcpy ( gpstLogEnv->pcDBConnect, cp[1] ) ;
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV4 ) == 0 ) {
			strcpy ( gpstLogEnv->pcLogPath, cp[1] ) ;
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV5 ) == 0 ) {
			gpstLogEnv->pcDBPort = atoi ( cp[1] ) ;	
		} else
		if ( strcmp ( cp[0], BML_LOGINI_ENV6 ) == 0 ) {
			strcpy ( gpstLogEnv->pcDBOutFilePath, cp[1] ) ;
		} else
		if ( strcmp ( cp[0], BML_LOGINI_INFO ) == 0 ) {
			*make = ( struct stcLogInfo * ) malloc ( sizeof ( struct stcLogInfo ) ) ;
			if ( *make == NULL ) {
				return ( -1 ) ;
			}
			memset ( ( void * ) *make, '\0', sizeof ( struct stcLogInfo ) ) ;
			(*make)->eTrcKind = cp[1][0] ;
			(*make)->iLogLv = atoi ( cp[2] ) ;
			strcpy ( (*make)->pcLogName, cp[3] ) ;
			make = &( (*make)->next )  ;
		} 
	}

	/***
	 ***	�h�m�h�t�@�C���N���[�Y
	 ***/
	fclose ( fp ) ;
loging ( "      - gpstLogEnv->iLogOutLv  [%d]\n", gpstLogEnv->iLogOutLv) ;
loging ( "        gpstLogEnv->iDBOutLv   [%d]\n", gpstLogEnv->iDBOutLv) ;
loging ( "        gpstLogEnv->pcDBConnect[%s]\n", gpstLogEnv->pcDBConnect) ;
loging ( "        gpstLogEnv->pcLogPath  [%s]\n", gpstLogEnv->pcLogPath) ;
loging ( "        gpstLogEnv->pcDBOutFilePath  [%s]\n", gpstLogEnv->pcDBOutFilePath) ;
loging ( "        gpstLogEnv->Loginfo\n") ;
see =  gpstLogEnv->topLoginfo ;
while ( see != NULL ) {
loging ( "                               [%c][%d][%s]\n", see->eTrcKind,
								                     	  see->iLogLv,
													      see->pcLogName) ;
	see = see->next ;
}
	return ( 0 ) ;
}
/******************************************************************************/
/*  �� �� ���@�FsFncIniFileRead												  */
/*  �@�\�T�v�@�F���O�����t�@�C���ǂݍ���									  */
/*  ���@�@�́@�F ����                                                         */
/*  �o�@�@�́@�F ����                                                         */
/*  ���A���@�F int                                                          */
/* �@�@�@�@�@�@�@ 0     : ����												  */
/* �@�@�@�@�@�@�@-1     : ���s												  */
/******************************************************************************/
static	void
sFncFilenameRep ( pInBuf, pOutBuf, psTm )
char		*pInBuf ;
char		*pOutBuf ;
struct tm	*psTm ;
{
	
	char			*hPos ;
	char			*tPos ;
	char			*cPos ;

	strcpy ( pOutBuf, pInBuf ) ;
	hPos = pOutBuf ;

	//	�N�S�u��
	if ( ( cPos = strstr ( pOutBuf, MY_YEAR_4 ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_YEAR_4 ) ;
		sprintf ( pOutBuf, "%s%04d%s", hPos, psTm->tm_year + 1900, tPos ) ;
	}

	//	�N�Q�u��
	if ( ( cPos = strstr ( pOutBuf, MY_YEAR_2 ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_YEAR_2 ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, ( psTm->tm_year + 1900 ) % 100, tPos ) ;
	}

	//	���u��
	if ( ( cPos = strstr ( pOutBuf, MY_MON ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_MON ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_mon + 1, tPos ) ;
	}

	//	���u��
	if ( ( cPos = strstr ( pOutBuf, MY_DAY ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_DAY ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_mday, tPos ) ;
	}

	//	���u��
	if ( ( cPos = strstr ( pOutBuf, MY_HOUR ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_HOUR ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_hour, tPos ) ;
	}

	//	���u��
	if ( ( cPos = strstr ( pOutBuf, MY_MIN ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_MIN ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_min, tPos ) ;
	}

	//	�b�u��
	if ( ( cPos = strstr ( pOutBuf, MY_SEC ) ) != NULL ) {
		*cPos = '\0' ;
		tPos = cPos + strlen ( MY_SEC ) ;
		sprintf ( pOutBuf, "%s%02d%s", hPos, psTm->tm_sec, tPos ) ;
	}

}
/** End of File ***************************************************************/
