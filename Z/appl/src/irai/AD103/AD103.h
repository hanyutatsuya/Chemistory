/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD103.h                                                      */
/*   �T      �v�F������t�i�˗��W�J�j���ҏ��E�����g���o�^                   */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/10     INTEC.INC      Create                             */
/*  1.01     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή�*/
/*                                         SelKanjya�֐��ǉ�/DelKanjya�֐��ǉ�*/
/*                                         InsShusei_Kanjya�֐��ǉ�           */
/******************************************************************************/
#ifndef _AD103_H
#define _AD103_H
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
#include "tagAD103.h"
#include "tagPNC.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
//	ini FILE
#define		MYAPP_INIFILE		"$HOME/appl/src/irai/AD103/AD103.ini"	

//	APPLI
			// MAX LENGTH
#define		MYAPP_MAX_CHAR		256				// with iconv
#define		MYAPP_MAX_EIGMST	100
#define		MYAPP_LEN_KEY		19
#define		MYAPP_LEN_FNCNM		32
#define		MYAPP_LEN_ERR		32
#define		MYAPP_LEN_MSG		1024
			// ���L�������T�C�Y
#define		MYAPP_SHM_SIZE		sizeof ( int )

#define		MYAPP_SPACE10		"          "
#define		MYAPP_KJSPACE10		"�@�@�@�@�@�@�@�@�@�@"
#define		MYAPP_APPLNAME		"���ҏ��o�^"

#define		MYAPP_RTN_DUP		-803
#define		MYAPP_IRIKBN_AS400	"K"				// AS400����̈˗�

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

// INPUT REC SIZE
#define		NXT_RECSIZE     	1024

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �c�a�ڑ����
struct {
    char	dbp_dbAlias[15];			//  DB
    char	dbp_user[129];   			//  user
    char	dbp_pswd[15];   			//  password
	char	ifp_indir[256];				// INPUT FILE DIRECTRY
	char	ifp_infprx[10];				// INPUT FILE PREFIX
	char	ifp_endfprx[10];			// END FILE DIRECTRY
	char	lgp_comlog[256];			// LOG FILE NAME
	char	lgp_flog[256];				// LOG FILE NAME for debug
	int		myp_sleep;					// SLEEP TIME
	char	myp_exefile[256];			// LoadModuleName
	char	myp_gene[4];				// �V�X�e������(PNCorNXT)
	char	myp_kjnymd[10+1];			// �������
	char	myp_zairyo[4];				// zairyo
	int		myp_sedai;
	int		myp_debug;        			/*CODEB  debug flg       */
} stcPRM;

// �������\����
struct CNT {
    int		cnt_irai;   				//  �˗��t�@�C�� �ǂݍ��݌���
    int		cnt_irai_err;   			//  �˗��t�@�C�� �G���[����
    int		cnt_irai_del;   			//  �˗��t�@�C�� �폜����
    int		cnt_kanjya;   				//  ���ґ����f�[�^  �o�^����
    int		cnt_chiken;   				//  �����g���f�[�^�@�o�^����
    int		cnt_hd;   					//  PNC HD ���R�[�h����
    int		cnt_tr;   					//  PNC TR ���R�[�h����
    int		cnt_r1;   					//  PNC R1 ���R�[�h����
    int		cnt_r2;   					//  PNC R2 ���R�[�h����
};

// ���L�������Ǘ��\����
struct	SHM {
	int     shm_Id ;
	key_t   shm_Key ;
};

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/
// extern
extern		iconv_t		G_ic;					// with iconv
extern		char		G_fnm[256];				// InputFileName
extern		char		G_msg[MYAPP_LEN_MSG+1];	// LogMessage
extern		char		G_err[MYAPP_LEN_ERR+1];	// LogMessage(errcode)
extern		char		G_utkymd[10+1];			// LogMessage(csv)
extern		char		G_irino[13+1];			// LogMessage(csv)
extern		int			G_zssdino;				// LogMessage(csv)
extern		int			G_line;					// InputFileLineNo


/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void		DispHelpMsg( int argc, char	**argv );
int			ParamCheckProc( int argc, char **argv, struct SHM  *stcShm );
int			GetKjnymd( );
static	int	FileFilter( struct dirent *namelist );

//2006.12.08 Kim Jinsuk DB�G���[��
//int			PncProc( FILE *pfp );
int			PncProc( FILE *pfp ,int *stopValue);
//2006.12.08 Kim Jinsuk DB�G���[��

int			ReadPnc( char *rbuf, FILE *pfp	);
int			NxtProc( FILE *nfp );
int			ReadNxt( char *rbuf, FILE *nfp	);
int			EditCsvKanjya( struct _KANJYA *kan );
int			EditCsvMsg( char *msg );
int			LogOut( char *sbt, char *flg, char *ecd, char *msg, 
					char *fncnm, char *file, long line );
int			EditPncKanjya( struct Z02SJIR1 *iirai, struct _KANJYA *zok );
int			EditNxtKanjya( struct _KANJYA *zok );
int			EditCommonKanjya( struct _KANJYA *zok );
int			zoku_pr( struct _KANJYA *in );
int			NameKeyMake( char *name_key, char *kan_name, int len );
int			EditPncChikenzok( struct Z04SJIR2 *iirai, struct _CHIKENZOK *zok );
int			EditNxtChikenzok( struct _CHIKENZOK *zok );
int			EditCommonChikenzok( struct _CHIKENZOK *zok );
int			chiken_pr( struct _CHIKENZOK *in );
int			GetEigmst( char *eigyo_cd, char *syuhai_cd, char *ymd, char *kbn );
// PG�ŗL����
char		*EnvRef( char *src_cp );
char		*GetIniFile( char *section, char *key, char *profile );
int			DaemonCheckProc( int argc, char **argv );
int			sj2euc( char *bufot, char *bufin, int len );
int			to_csv( char *delim, int len, char *msg, char *col );
int			wa2ymd( char *ymd10, char *gengou, char *ymd );
int			ValidDate( int mode, char *indate );
// ���L������
int			sFncShmCrt ( struct SHM *strShm );
int			sFncShmGet ( struct SHM *strShm, int *pshmData );
int			sFncShmDel ( struct SHM *strShm);
// �c�a�֘A�֐�
int			SelSysknrmst( struct _SYSKNRMST *knr );
int			SelEigmst( struct _EIGMST *egm );
int			InsKanjya( struct _KANJYA *kan );
int			SelKanjyaZssdinoMax( struct _KANJYA *kan );
int			UpdKanjyaTktyflg( struct _KANJYA *kan );
int			UpdKinkyuKanjya( struct _KANJYA *kan );
int			SelKinkyuIrai( struct _KANJYA *kan );
int			InsChikenzok( struct _CHIKENZOK *try );
/*  1.01     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� --> */
int			SelKanjya( struct _KANJYA *kan );
int			DelKanjya( struct _KANJYA *kan );
int			InsShusei_Kanjya();
/*  1.01     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� <-- */
int			Ydbcommit();
int			Ydbrollback();
int			Ydbconn();
int			Ydbdisconn();

#endif
/** End of File ***************************************************************/
