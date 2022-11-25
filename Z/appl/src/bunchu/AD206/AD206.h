/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FAD206.h                                                      */
/* �@�T�@�@�@�v�F�ً}�������ʃ��C�A�E�g�ϊ�����                               */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2007/06/01     INTEC          �V�K�쐬                           */
/*  1.00     2009/01/06     Merits K.Ameno �{�݃R�[�h���� �ʐM�d�l�ύX�Ή�    */
/******************************************************************************/
#ifndef _AD206_H
#define _AD206_H
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"
#include "Sysknrmst.h"

#include "tagDB.h"
/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"AD206"
#define	MYAPP_APP_NAME_JP		"AD206"
#define	MYAPP_LOGINIFILE		"AD206_LOG.ini"

//  �����X�e�[�^�X�R�[�h��`
typedef enum {
	MYAPP_STSCODE_NML,
	MYAPP_STSCODE_ERR_USEGE,
	MYAPP_STSCODE_ERR_PRM,
	MYAPP_STSCODE_ERR_SHM,
	MYAPP_STSCODE_ERR_DIR,
	MYAPP_STSCODE_ERR_TR_FILE,
	MYAPP_STSCODE_ERR_DB,
	MYAPP_STSCODE_NML_START,
	MYAPP_STSCODE_NML_END
} MYAPP_STSCODE ;

//	�G���[�R�[�h��`
#define	MYAPP_LOG_ERRCODE_NON		"00000000"

//	�G���[�R�[�h�ڍ�
#define MYAPP_SQL_DEADLOCK          -911
#define MYAPP_SQL_DUPLICATION       -803

//	������V�X�e���ؑ֒�`
typedef enum {
	MYAPP_SYSTEM_NEW,
	MYAPP_SYSTEM_OLD
} MYAPP_SYSTEM_VERSION ;

//	�p�����[�^������
#define	MYAPP_PRM_DIR_BUNCHU		"DIR_BUNCHU"
#define	MYAPP_PRM_DIR_BUNCHU_OK		"DIR_BUNCHU_OK"
#define	MYAPP_PRM_DIR_BUNCHU_ERR	"DIR_BUNCHU_ERR"
#define	MYAPP_PRM_DIR_NR_LOG		"DIR_NR_LOG"		//���g�p
#define	MYAPP_PRM_DIR_TRAY_INFO		"DIR_TRAY_INFO"
#define	MYAPP_PRM_DIR_TRAY_INFO_OK	"DIR_TRAY_INFO_OK"
#define	MYAPP_PRM_DIR_TRAY_INFO_NG	"DIR_TRAY_INFO_NG"
#define	MYAPP_PRM_SHM_KEY			"SHM_KEY"
#define	MYAPP_PRM_SLEEP_SEC			"SLEEP_SEC"
#define	MYAPP_PRM_DB_NAME			"DB_NAME"
#define	MYAPP_PRM_DB_USER			"DB_USER"
#define	MYAPP_PRM_DB_PASSWD			"DB_PASSWD"
#define	MYAPP_PRM_VERSION			"VERSION"			//���g�p
#define	MYAPP_PRM_DIR_IA_DAT		"DIR_IA_DAT"
#define	MYAPP_PRM_DIR_IA_IDX		"DIR_IA_IDX"
#define	MYAPP_PRM_FILE_RETRY		"FILE_RETRY"


//	�f�B���N�g���i�[�T�C�Y
#define	MYAPP_PATH_SIZE			(1024)

//	���L�������T�C�Y
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	��M�t�@�C���֘A
#define	MYAPP_RECV_KIND			"RE"					//���g�p
#define	MYAPP_RECV_SFX			".dat"					//���g�p
#define	MYAPP_RECV_RECSIZE		(63 + 1)				/* 1���R�[�h�̃T�C�Y - FILLER(12) - LF(1) + 1�R�[�h*/

//  ���M�t�@�C���֘A
#define MYAPP_SEND_KIND_CH		"CHK"					//OUTPUT�擪������
#define MYAPP_SEND_SFX          ".dat"					//OUTPUT�g���q(AD205INPUT����)

//	�f�[�^�T�C�Y
#define	MYAPP_TRNO_SIZE			(10+1)	
#define	MYAPP_STKNO_SIZE		(6+1)	
#define	MYAPP_DATE_SIZE			(10+1)	
#define	MYAPP_RKNO_SIZE			(10+1)	
#define	MYAPP_DEOF_SIZE			(20+1)	


#define MYAPP_PNC_MAX_SIZE			1024
#define MYAPP_KMKCD_START_POS		63
//	������V�X�e��
#define	MYAPP_VERSION			"NEXTGENE"

#define	MYAPP_COMMAND_RM		"/bin/rm"


/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �v���O�������\����
struct	appEnv	{
	BMLPRM				*bp	;
	char				*pcFielNamePRM ;
	int					 fileRetry ;
	int					 shm_Id ;
	key_t				 shm_Key ;
	int					 sleep_Sec ;
	char				 cDb_Name[32+1] ; 
	char				 cDb_User[32+1] ; 
	char				 cDb_Passwd[32+1] ; 
	char	 			 cDirNR_Col[MYAPP_PATH_SIZE] ;	
	char				 cDirNR_ColOk[MYAPP_PATH_SIZE] ;
	char				 cDirNR_ColErr[MYAPP_PATH_SIZE] ;
	char				 cDirIA_Dat[MYAPP_PATH_SIZE] ;
	char				 cDirIA_Idx[MYAPP_PATH_SIZE] ;
//	char				 cDirNR_Log[MYAPP_PATH_SIZE] ;		//���g�p
	char				 cDirTryinfo[MYAPP_PATH_SIZE] ;		//���g�p
	char				 cDirTryinfoOK[MYAPP_PATH_SIZE] ;		//���g�p
	char				 cDirTryinfoNG[MYAPP_PATH_SIZE] ;		//���g�p


//	char				 cVersion[32+1] ;					//���g�p
} ;

// �ً}��������
typedef struct my_stINPUT
{
	char 	utkymd[9];				/* ��t���t 8��+1�R�[�h		 */
	char 	kntno[12];				/* ����No 11��+1�R�[�h		 */
	char	eda[3];					/* �\�� 2��+1�R�[�h			 */
	char	sincode[8];				/* �e���ڃR�[�h 7��+1�R�[�h	 */
	char 	kmkcd[8];				/* ���ڃR�[�h 7��+1�R�[�h	 */
	char	wscd[5];				/* WS�R�[�h 4��+1�R�[�h		 */
	char 	scheduleno[5];			/* SEQ�ԍ� 4��+1�R�[�h		 */
	char 	motorackid[9];			/* �����b�NID 8��+1�R�[�h	 */
	char 	motorackpos[3];			/* ���|�W�V���� 2��+1�R�[�h	 */
	char 	bunchurackid[9];		/* ���b�NID 8��+1�R�[�h		 */
	char 	bunchurackpos[3];		/* �|�W�V���� 2+1�R�[�h		 */

}stINPUT_DATA;
// �ً}��������
typedef struct my_stOUTPUT
{
    char    syokubetumozi[2];
    char    transactionID[6];
    char    altuseiRackID[8];
    char    utkymd[8];
    char    iti1[3];
    char    BMLutkymd[8];
    char    iraino[11];
    char    kntno[11];
    char    kntchkmozi[2];
    char    WS[1];
    char    sbkbn[1];
    char    nrkbn[1];
    char    nr[3];
    char    nyoutime[4];
    char    nyoutime_tan[1];
    char    nyouryou[5];
    char    nyouryou_tan[1];
    char    sstcd[7];
    char    egyoucd[3];
    char    motoRackID[8];
    char    motoRackPos[3];
    char    wscd[4];
    char    kmkcd[64][7];
    char    bckID[3];
    char    jtflg[1];
    char    kssr[1];
    char    tgennflg[1];
    char    kkirflg[1];
    char    btkka[1];
    char    Filler[466];
	char 	LF;

	short	nPos;	//����POSITION
	char	KeyKntno[12];//�ŏ�����������̔ԍ�
	char	KeyEda[3];//�ŏ�����������̎}��
	FILE	*fp;		//Output File	
}stOUTPUT_DATA;
/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/
