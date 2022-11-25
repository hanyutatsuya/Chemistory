/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD301.h                                                      */
/*   �T      �v�F������t�i�v���J�[�h���M�j�v���J�[�h�쐬                     */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/04/03     INTEC.INC      Create                             */
/******************************************************************************/
#ifndef _AD301_H
#define _AD301_H
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <errno.h>
#include <iconv.h>
#include <dirent.h>
#include "bml_base.h"
#include "tagAD301.h"
#include "tagPNC.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
//	ini FILE
#define		MYAPP_INIFILE		"$HOME/appl/src/irai/AD301/AD301.ini"	

//	APPLI
			// MAX LENGTH
#define     MYAPP_MAX_CHAR      256             // with iconv
#define		MYAPP_LEN_FNCNM		32
#define		MYAPP_LEN_ERR		32
#define		MYAPP_LEN_MSG		3014
			// ���L�������T�C�Y
#define		MYAPP_SHM_SIZE		sizeof ( int )

#define		MYAPP_SPACE10		"          "
#define		MYAPP_KJSPACE10		"�@�@�@�@�@�@�@�@�@�@"
#define		MYAPP_APPLNAME		"�v���J�[�h�쐬"

#define		MYAPP_BUN			1
#define		MYAPP_IRI			2
#define		MYAPP_KAN			3

#define		MYAPP_RTN_DUP		-803
#define		MYAPP_RTN_LOCK		-911
#define		MYAPP_RTN_NTFND		 100

			// �g���[�X���
#define		LT_DBG			"D"	
#define		LT_TRC			"T"	
#define		LT_OPT			"O"	
#define		LT_WRN			"W"	
#define		LT_ERR			"E"	
#define		LT_SYS			"A"	
#define		LT_STA			"STA"	
#define		LT_END			"END"	
			// ���s�t���O
#define		LX_SEL			"S"	
#define		LX_INS			"I"	
#define		LX_UPD			"U"	
#define		LX_DEL			"D"	
#define		LX_NON			" "	
			// �G���[�R�[�h
#define		LE_NON			" "	

//	���t�`�F�b�N���[�h
#define		VALDATE_DATE		1			// DATE�^
#define		VALDATE_TIME		2			// time�^
#define		VALDATE_TIMESTAMP	3			// taimestamp�^

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
struct {
    char	dbp_dbAlias[15];			//  DB
    char	dbp_user[129];   			//  user
    char	dbp_pswd[15];   			//  password
	char	lgp_comlog[256];			// LOG FILE NAME
	char	ifp_kan_otdir[256];			// REQ KANJYA OUT DIRECTRY
	char	ifp_kan_ext[10];			// REQ KANJYA FILE EXTENSION
	char	ifp_kan_ykkbn[10];			// REQ KANJYA YOKYU KBN
	int		ifp_kan_time;				// REQ KANJYA SLEEP TIME
	char	ifp_kan_dflow[11];			// KAN �f�[�^�t���[�h�c
	char	ifp_iri_otdir[256];			// REQ IRAI OUT DIRECTRY
	char	ifp_iri_ext[10];			// REQ IRAI FILE EXTENSION
	char	ifp_iri_ykkbn[10];			// REQ IRAI YOKYU KBN
	int		ifp_iri_time;				// REQ IRAI SLEEP TIME
	char	ifp_iri_dflow[11];			// IRI �f�[�^�t���[�h�c
	char	ifp_bun_otdir[256];			// REQ BUNCYU OUT DIRECTRY
	char	ifp_bun_ext[10];			// REQ BUNCYU FILE EXTENSION
	char	ifp_bun_ykkbn[10];			// REQ BUNCYU YOKYU KBN
	int		ifp_bun_time;				// REQ KANJYA SLEEP TIME
	char	ifp_bun_dflow[11];			// BUN �f�[�^�t���[�h�c
	char	ifp_sosinsaki[10];			// HDTR ���M��
	char	ifp_sosinmoto[10];			// HDTR ���M��
	char	ifp_fprefix[10];			// OUTPUT FILE PREFIX
	int		myp_sleep;					// SLEEP TIME
	char	myp_exefile[256];			// LoadModuleName
	char	myp_gene[10];				// Generation kbn
	char	myp_kjnymd[10+1];			// �������
	int		myp_debug;        			/*CODEB  debug flg       */
} stcPRM;

// ���L�������Ǘ��\����
struct  SHM {
	int		shm_Id ;
	key_t	shm_Key ;
};

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
// extern
extern      iconv_t     G_ic;                   // with iconv
extern		char		G_msg[MYAPP_LEN_MSG+1];	// LogMessage
extern		char		G_err[MYAPP_LEN_ERR+1];	// LogMessage(errcode)
extern		int			G_line;					// InputFileLineNo

extern		struct      _SYSKNRMST		pKnr;

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void		DispHelpMsg( int argc, char	**argv );
int			ParamCheckProc( int argc, char **argv, struct SHM  *stcShm );
int			EditInitRequest( struct Z00SJHD *z00, 
				struct Z01SJTR *z01, struct Z12SJR1 *z12 );
int			WriteRequestFile( int kbn, struct Z00SJHD *z00, 
				struct Z01SJTR *z01, struct Z12SJR1 *z12 );
static	int	FileFilter( struct dirent *namelist );
int			LogOut( char *sbt, char *flg, char *ecd, char *msg, 
					char *fncnm, char *file, long line );
// PG�ŗL����
char		*EnvRef( char *src_cp );
char		*GetIniFile( char *section, char *key, char *profile );
int			DaemonCheckProc( int argc, char **argv );
int			sj2euc( char *bufot, char *bufin, int len );
int			to_csv( char *delim, int len, char *msg, char *col );
int			wa2ymd( char *ymd10, char *gengou, char *ymd );
int			ValidDate( int mode, char *indate );
// ���L������
int         sFncShmCrt ( struct SHM *strShm );
int         sFncShmGet ( struct SHM *strShm, int *pshmData );
int         sFncShmDel ( struct SHM *strShm);
// �c�a�֘A�֐�
int			SelSysknrmst( struct _SYSKNRMST *pknr );
int			UpdSysknrmstSsntubn( );
int			Ydbcommit();
int			Ydbrollback();
int			Ydbconn();
int			Ydbdisconn();

#endif
/** End of File ***************************************************************/
