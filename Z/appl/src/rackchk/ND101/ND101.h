/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FND101.h                                                      */
/* �@�T�@�@�@�v�F�p�����[�^�擾�w�b�_                                         */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _ND101_h
#define _ND101_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include <stdbool.h>

#include "bmlprm.h"
#include "bmllog.h"
#include "bml_dbrc.h"
#include "bml_DBCom.h"
#include "bml_misc.h"
#include "bml_date.h"

#include "sql.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"ND101"

//  �����X�e�[�^�X�R�[�h��`
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

//	�G���[�R�[�h��`
#define	MYAPP_LOG_ERRCODE_NON	"00000000"
#define	MYAPP_LOG_ERRCODE_APP	"010"
#define	MYAPP_LOG_ERRCODE_DB	"020"
#define	MYAPP_LOG_ERRCODE_ETC	"0Z0"

//	�G���[�R�[�h�ڍ�
#define MYAPP_SQL_DEADLOCK	-911
#define MYAPP_SQL_DUPLICATION	-803

//	�p�����[�^������
#define	MYAPP_PRM_SHM_KEY	"SHM_KEY"
#define	MYAPP_PRM_DB_NAME	"DB_NAME"
#define	MYAPP_PRM_DB_USER	"DB_USER"
#define	MYAPP_PRM_DB_PASSWD	"DB_PASSWD"
#define MYAPP_PRM_DIR_INPUT	"INPUT_DIR"
#define MYAPP_PRM_DIR_OK	"END_DIR_OK"
#define MYAPP_PRM_DIR_NG	"END_DIR_NG"
#define MYAPP_PRM_DIR_SKIP	"END_DIR_SKIP"
#define MYAPP_PRM_FILE_EXT	"FILE_EXT"
#define MYAPP_PRM_FILE_EXT_TRG	"FILE_EXT_TRG"
#define MYAPP_PRM_SKIP_FILE_PRE	"SKIP_FILE_PRE"

//	�d�m�c���R�[�h��`
#define MYAPP_RECORD_END	"END"

//	�f�B���N�g���i�[�T�C�Y
#define	MYAPP_PATH_SIZE		(1024)

//	�ő僌�R�[�h��
#define MYAPP_RECORD_SIZE	1024

//	���L�������T�C�Y
#define	MYAPP_SHM_SIZE		sizeof ( int )

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �v���O�������\����
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	char	 cInputDir[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirOK[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirNG[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirSKIP[MYAPP_PATH_SIZE] ;
	char	 cFileExt[MYAPP_PATH_SIZE] ;
	char	 cFileExtTrg[MYAPP_PATH_SIZE] ;
	char	 cSkipFilePre[MYAPP_PATH_SIZE] ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ; 
} pAppEnv;
/******************************************************************************/
/* �t�@�C���\���̒�`                                                           */
/******************************************************************************/
// <<   �t�����e�B�A���b�N���t�@�C��      >>
typedef struct file_fronrack {
	char	sriymd[10+1];
	char	hkkbn[3+1];
	char	asyrckid[10+1];
	char	irino[11+1];
} my_stFileFRONRACK;

/******************************************************************************/
/* �f�[�^�\���̒�`                                                           */
/******************************************************************************/
// <<   �t�����e�B�A���b�N���e�[�u��      >>
typedef struct	db_fronrack {
	char	knskisymd[10+1];
	char	asyrckid[10+1];
	int	asyrckpos;
	char	utkymd[10+1];
	char	irino[11+1];
	char	knsgrp[16+1];
	char	hkkbn[3+1];
	char	ksndh[26+1];
	char	trkdh[26+1];
} my_stDbFRONRACK;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;

int	sFncGetFileRecord( char *, my_stFileFRONRACK * );
int	sFncSelKenOrder( char *, char *, char *, my_stDbFRONRACK **, int * );
int	sFncInsFronRack( my_stDbFRONRACK * );
int	sFncMakeEndFileName( char *, char *, char *, char * ) ;
int	sFncMakeSkipFile( char *, char *, char * );
int	sFncInsEnd( char *, char *, char * );

int	mainProc( FILE *, bool, int * );

/** End of File ***************************************************************/

#endif
