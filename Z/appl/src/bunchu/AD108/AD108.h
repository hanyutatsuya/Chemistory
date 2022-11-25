/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FAD108.h                                                      */
/* �@�T�@�@�@�v�F�R�h�c���W�J                                               */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2008/02/12     moriya         �V�K�쐬                           */
/*  1.01     2008/11/13     sekiya         ��܂v�r�̕��я������������Ȃ邱�� */
/*                                         �ɑ΂���Ή�                       */
/*  1.02     2008/12/22     sekiya         SKIP�t�@�C�����o�͂��Ă��鎞�ɁA   */
/*                                         AD107���A�N�Z�X���Ȃ��悤��        */
/*                                         �P�x�Atmp�ɏo�͂��ă��l�[������    */
/*                                         �悤�Ɏd�l��ύX                   */
/******************************************************************************/
#ifndef _stocker_h
#define _stocker_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bmlprm.h"
#include "bmllog.h"
#include "bml_DBCom.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"AD108"
#define	MYAPP_APP_NAME_JP		"AD108"
#define	MYAPP_LOGINIFILE		"/home/kea00sys/bin/AD108_LOG.ini"
#define	MYAPP_AD105SORTINIFILE	"/home/kea00sys/bin/AD105_SORT.ini"

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
#define MYAPP_SQL_DEADLOCK			-911
#define MYAPP_SQL_DUPLICATION		-803
#define MYAPP_SQL_NOTFOUND			100

//	������V�X�e���ؑ֒�`
typedef enum {
	MYAPP_SYSTEM_NEW,
	MYAPP_SYSTEM_OLD
} MYAPP_SYSTEM_VERSION ;

//	�p�����[�^������
#define	MYAPP_PRM_DIR_3ID			"DIR_3ID"
#define	MYAPP_PRM_DIR_3ID_OK		"DIR_3ID_OK"
#define	MYAPP_PRM_DIR_3ID_NG		"DIR_3ID_NG"
#define	MYAPP_PRM_DIR_3ID_SKIP		"DIR_3ID_SKIP"
#define	MYAPP_PRM_SHM_KEY			"SHM_KEY"
#define	MYAPP_PRM_SLEEP_SEC			"SLEEP_SEC"
#define	MYAPP_PRM_DB_NAME			"DB_NAME"
#define	MYAPP_PRM_DB_USER			"DB_USER"
#define	MYAPP_PRM_DB_PASSWD			"DB_PASSWD"
#define	MYAPP_PRM_LABOCD			"LABOCD"
#define	MYAPP_PRM_SATECD			"SATECD"
#define	MYAPP_PRM_FILE_RETRY		"FILE_RETRY"


//	�f�B���N�g���i�[�T�C�Y
#define	MYAPP_PATH_SIZE			(1024)

//	���L�������T�C�Y
#define	MYAPP_SHM_SIZE			sizeof ( int )

//	��M�t�@�C���֘A
#define	MYAPP_RECV_KIND_POS		"POS"
#define	MYAPP_RECV_KIND_SKIP	"SKIP"
/* 1.02 �ꎞ�t�@�C���̏o�͖� */
#define MYAPP_RECV_KIND_TMP    "TMP"
#define	MYAPP_RECV_SFX			".dat"
#define	MYAPP_RECV_RECSIZE		(512)
#define	MYAPP_RECV_COLCNT		(23)
#define	MYAPP_RACK_MAXCNT		(20)

//  ���M�t�@�C���֘A
#define MYAPP_SEND_KIND_OD		"OD"		//�����I�[�_�[���
#define MYAPP_SEND_KIND_CH		"CH"		//�����`�F�b�N���
#define MYAPP_SEND_SFX          ".dat"

//	�f�[�^�T�C�Y
#define	MYAPP_TRNO_SIZE			(10+1)	
#define	MYAPP_STKNO_SIZE		(6+1)	
#define	MYAPP_DATE_SIZE			(10+1)	
#define	MYAPP_RKNO_SIZE			(10+1)	
#define	MYAPP_DEOF_SIZE			(20+1)	

//	������V�X�e��
#define	MYAPP_VERSION			"NEXTGENE"

#define	MYAPP_COMMAND_RM		"/bin/rm"

#define		RECLEN_3RDID		65		/* �P���R�[�h��	*/

#define		RECEND_3RDID		"END"	/* �d�m�c���R�[�h	*/


/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
/* AD105_SORT.ini�t�@�C���p�\���� */
typedef struct {
	char	sData[4+1] ;
	char	sKey[3+1] ;
} BUNSORT;

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
	char				 cLbcd[3+1] ;
	char				 cSateid[3+1] ;
	char	 			 cDir3Id[MYAPP_PATH_SIZE] ;
	char				 cDir3IdOk[MYAPP_PATH_SIZE] ;
	char				 cDir3IdNg[MYAPP_PATH_SIZE] ;
	char				 cDir3IdSkip[MYAPP_PATH_SIZE] ;
	int					 pSortNo ;
	BUNSORT				*pSort ;
} ;

/* ��M�t�@�C���̃f�[�^���R�[�h(�Œ蒷) */
typedef struct {
	char	cUtkymd[8] ;
	char	cIrino[11] ;
	char	cSriymd[8] ;
	char	cKntno[11] ;
	char	cRackId[8] ;
	char	cRackPos[3] ;
	char	cYobi[15] ;
	char	cLf[1] ;
} ID3Info;

/* �e�[�u���X�V�p�\���� */
/* �T���v�����O�R�[�h���݂邱�ƂɂȂ����̂� */
/* �\�[�g�L�[�̂݁A�ʂɍ\���̂��쐬���� */
typedef struct {
	char	cUtkymd[8+1] ;
	char	cIrino[11+1] ;
	char	cSriymd[8+1] ;
	char	cKntno[11+1] ;
	char	cRackId[8+1] ;
	char	cRackPos[3+1] ;
	char	cYobi[15+1] ;
	char	cLf[1+1] ;
} ID3TB;

/* �\�[�g�L�[�X�V�p�\���� */
typedef struct {
	char	cSmpcd[7+1] ;
	char	cBnckka ;
	int     iSrtkey ;
} SORTInfo;


/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/
