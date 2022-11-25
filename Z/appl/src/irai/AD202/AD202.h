/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD202.h                                                      */
/*   �T      �v�F������t�i�ً}�����˗��W�J�j�ً}�������W�J                 */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/10     INTEC.INC      Create                             */
/*  2.00     2009/01/06     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/******************************************************************************/
#ifndef _AD202_H
#define _AD202_H
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
#include "tagAD202.h"
#include "tagKINQ.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
//	ini FILE
#define		MYAPP_INIFILE		"$HOME/appl/src/irai/AD202/AD202.ini"	

//	APPLI
			// MAX LENGTH
#define		MYAPP_MAX_CHAR		256				// with iconv
#define		MYAPP_LEN_KEY		19
#define		MYAPP_LEN_KJN		14
#define		MYAPP_LEN_FNCNM		32
#define		MYAPP_LEN_ERR		32
#define		MYAPP_LEN_MSG		1024
			// ���L�������T�C�Y
#define		MYAPP_SHM_SIZE		sizeof ( int )

#define		MYAPP_SPACE10		"          "
#define		MYAPP_KJSPACE10		"�@�@�@�@�@�@�@�@�@�@"
#define		MYAPP_APPLNAME		"�ً}�˗��W�J"


#define		MYAPP_RTN_DUP		-803
#define		MYAPP_DEF_ZRCD		"023"			// 3.01 ����
#define		MYAPP_ZRCD_ASDEF	"0  "			/* �ޗ��R�[�h���Ȃ�(AS���œ���0��t���đ��M���Ă����)�ꍇ�̒l */

#define		MYAPP_DEF_ERR01		"00000001"		// 3.01 �ً}��������ƈ�v����

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
// �c�a�ڑ����
struct {
    char	dbp_dbAlias[15];			//  DB
    char	dbp_user[129];   			//  user
    char	dbp_pswd[15];   			//  password
	char	ifp_indir[256];				// INPUT FILE DIRECTRY
	char	ifp_infprx[10];				// INPUT FILE PREFIX
	char	ifp_endfprx[10];			// END FILE DIRECTRY
	char	lgp_comlog[256];			// LOG FILE NAME
	int		myp_sleep;					// SLEEP TIME
	char	myp_exefile[256];			// LoadModuleName
	char	myp_kjnymd[10+1];			// �������
	char	myp_zairyo[4];				// zairyo
	int		myp_sedai;
	int		myp_debug;        			/*CODEB  debug flg       */
} stcPRM;

// �������\����
struct CNT {
    int		cnt_irai;   				//  �˗��t�@�C�� �ǂݍ��݌���
    int		cnt_irai_err;   			//  �˗��t�@�C�� �G���[����
    int		cnt_skip;   				//  �˗��t�@�C�� SKIP����
    int		cnt_exc;   					//  �˗��t�@�C�� SKIP���� �ΏۊO
    int		cnt_sumi;   				//  �˗��t�@�C�� SKIP���� ������
    int		cnt_kanjya;   				//  ���ґ����f�[�^  �o�^����
    int		cnt_dbirai;   				//  �˗����f�[�^�@�o�^����
};

// ���L�������Ǘ��\����
struct	SHM {
	int     shm_Id ;
	key_t   shm_Key ;
};

// <<   ��lNO�擾�p�\����
struct  stcKJNO {
	char	kjno[3+1];					// O ��lNO
	char	kmkcd[7+1];				 	// I ���ڃR�[�h
	char	zrcd[4+1];				  	// I �ޗ��R�[�h
	char	age[3+1];					// I �N��
	char	agekbn[1+1];				// I �N��敪
};

// �˗����ڏ��\����
struct KOMST {
    char	kmkcd[7+1];					// I ���ڃR�[�h
    char	knsgrp[16+1];				// 1.04 O �����O���[�v		
    char	kmkrs[16+1];				// O ���ڗ���
	char    oyakmkcd[7+1];      		// O �e���ڃR�[�h
	char    fkbnkkb[1+1];       		// O ���敉�׋敪
	char    seccd[2+1];       			// O �Z�N�V�����R�[�h
	char    smpcd[7+1];         		// O �T���v�����O�R�[�h
	char    kjno[3+1];       			// O ��l�m�n
};

// 1.04 ADD
// ���������˗����
struct  JIDOIRAI {
    struct  _JDKMKMST   sJdm;
    struct  _KMKMST     sKmk;
    struct  _IRAI       sIri;
    char    age[3+1];                   // I �N��
    char    agekbn[1+1];                // I �N��敪
};


// �f�ÉȖ�	
struct  sinryo_rec {
    int     scode;
    char    sname[30+1];
};

static struct	sinryo_rec	kanm[]= {
{    0," ", },
{    1,"����", },
{    2,"�����", },
{    3,"�����", },
{    4,"�O����", },
{    5,"�ċz���", },
{    6,"�������", },
{    7,"�z���", },
{    8,"������", },
{    9,"���_��", },
{    10,"�_�o��", },
{    11,"�O��", },
{    12,"��O��", },
{    13,"��O��", },
{    14,"�O�O��", },
{    15,"���`��", },
{    16,"�]�O��", },
{    17,"�S���O��", },
{    18,"�畆��", },
{    19,"��A���", },
{    20,"���ː���", },
{    21,"���͉�", },
{    22,"�Y��", },
{    23,"�w�l��", },
{    24,"���@��", },
{    25,"������", },
{    26,"������", },
{    27,"����", },
{    28,"���", },
{    29,"�h�b�N", },
{    30,"���f��", },
{    31,"������", },
{    32,"������", },
{    33,"���̑�", },
{    34,"�`���O��", },
{    35,"�u����", },
{    36,"�����O��", },
{    37,"�S�Ó���", },
{    38,"�]�_�o����", },
{    39,"�����O��", },
{    40,"���㌤����", },
{    41,"���㌤�O��", },
{    42,"���m��w��", },
{    43,"�_�o����", },
{    44,"��S����", },
{    45,"�������", },
{    46,"�V�N����", },
{    47,"���o�O��", },
{    48,"���E�}�`�Z���^�[", },
{    49,"�Y�w�l��", },
{    50,"�Q�`", },
{    51,"�Q�a", },
{    52,"�R�`", },
{    53,"�R�a", },
{    54,"�S�`", },
{    55,"�S�a", },
{    56,"�T�`", },
{    57,"�T�a", },
{    58,"�U�`", },
{    59,"�U�a", },
{    60,"�z��", },
{    61,"�ċz��P", },
{    62,"�ċz��Q", },
{    63,"�ݒ���", },
{    64,"���n�r����", },
{    65,"���������f", },
{    66,"��w���f", },
{    67,"�W��", },
{    68,"�t", },
{    69,"�S������", },
{    70,"�~�}��", },
{    71,"��f", },
{    72,"�Ɖu��", },
{    73,"���������", },
{    74,"���t����", },
{    75,"�V�l��", },
{    76,"�Տ��a����", },
{    77,"����", },
{    78,"���A", },
{    79,"���O", },
{    80,"����", },
{    81,"�a��", },
{    82,"�t���O��", },
{    83,"���P�C��", },
{    84,"���w�Ö@��", },
{    85,"������", },
{    86,"�ی��w����", },
{    87,"�������a����", },
{    88,"�s�D�O��", },
{    89,"��񏬎���", },
{    90,"�ċz��O��", },
{    91,"�̑���", },
{    92,"������O��", },
{    93,"�f�Ï�", },
{    94,"�_�o���@��", },
{    95,"�t�ڐA��", },
{    96,"���`�O��", },
{    97,"�v�h�b", },
{    98,"�A�����M�[��", },
{    99," ", },
{    -1,"" }
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
extern		char		G_irino[11+1];			// LogMessage(csv)
extern		int			G_zssdino;				// LogMessage(csv)
extern		char		G_kntno[13+1];			// LogMessage(csv)
extern		char		G_kmkcd[7+1];			// LogMessage(csv)
extern		int			G_line;					// InputFileLineNo

extern		struct		_KJNMST     *pKjn;

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void		DispHelpMsg( int argc, char	**argv );
int			ParamCheckProc( int argc, char **argv, struct SHM  *stcShm );
int			GetKjnymd( );
static	int	FileFilter( struct dirent *namelist );
//int			KinqProc( FILE *pfp );
int			KinqProc( FILE *pfp, int *stopValue );
int			ReadKinq( char *rbuf, FILE *pfp	);
int			EditCsvMsg( char *msg );
int			LogOut( char *sbt, char *flg, char *ecd, char *msg, 
					char *fncnm, char *file, long line );
int			EditKinqKanjya( struct AS4IRAI *iirai, struct _KANJYA *zok );
int         EditKinqIrai( struct AS4IRAI *inp, struct _KANJYA *kan, struct _IRAI *iri );
int			zoku_pr( struct _KANJYA *in );
int			irai_pr( struct _IRAI *in );
int			NameKeyMake( char *name_key, char *kan_name, int len );
int         GetKjnmst( struct stcKJNO   *in );
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
int         SelCountKjnmst( char *ymd );
int         SelKjnmst( char *ymd , int kensu );
int			InsKanjya( struct _KANJYA *kan );
int         InsIrai( struct _IRAI *iri );
int			Ydbcommit();
int			Ydbrollback();
int			Ydbconn();
int			Ydbdisconn();

#endif
/** End of File ***************************************************************/
