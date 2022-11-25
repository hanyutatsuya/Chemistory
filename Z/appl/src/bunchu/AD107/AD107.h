/*****************************************************************************

	SYSTEM NAME:  �yNonRIA�z�T�e���C�g

	FILE NAME:    �e�s�o��M  ���ʃw�b�_

	DATE/Var:     2008/04/01 Ver.1.00

	Edited:       S.Sato (apricot)

*****************************************************************************
	#001 08/01/15 ksuzu     ����Ή�
	#002 08/01/23 ksusu     �P�~�X�g���[�Ή�
	#003 08/12/22 sekiya	�ꎞ�t�@�C���̍쐬����AD108���ꎞ�t�@�C���̏�����
							�s���Ă��܂����g���u���ɑ΂���Ή�
							�ꎞ�t�@�C���ƍ쐬�ς݃t�@�C���̓�������ʂɂ���
*****************************************************************************/

#ifndef	__LO_FTP3RDID

#define	LEN_BUFF	256

/***********************************************************************
	�]����`�t�@�C��
***********************************************************************/
/* �t�@�C����	*/
#define	MYAPP_APP_NAME		"AD107"
#define	MYAPP_APP_NAME_JP	"AD107"
#define	MYAPP_LOGINIFILE	"/home/kea00sys/bin/AD107_LOG.ini"

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

/* �^�O�̒�`	*/
#define	MYAPP_PRM_SHM_KEY		"SHM_KEY"		/* ���L�������L�[							*/
#define	MYAPP_PRM_SLEEP_SEC		"SLEEP_SEC"		/* �X���[�v									*/
#define	MYAPP_PRM_FTP_HOST		"FTP_HOST"		/* �����[�g���z�X�g��						*/
#define	MYAPP_PRM_FTP_USER		"FTP_USER"		/* �����[�g�����O�C�����[�U					*/
#define	MYAPP_PRM_FTP_PSWD		"FTP_PSWD"		/* �����[�g�����O�C���p�X���[�h 			*/
#define	MYAPP_PRM_R_PATH		"R_PATH"		/* �����[�g����M���p�X						*/
#define	MYAPP_PRM_R_FILE		"R_FILE"		/* �����[�g����M�t�@�C����					*/
#define	MYAPP_PRM_L_PATH		"L_PATH"		/* ���[�J������M��p�X						*/
#define	MYAPP_PRM_I_PATH		"I_PATH"		/* ���[�J�����W�J�p�p�X						*/
#define	MYAPP_PRM_M_PATH		"M_PATH"		/* �����Ǘ��f�B���N�g���p�X					*/
#define	MYAPP_PRM_S_PATH		"S_PATH"		/* 3ID���W�J(AD108)�̃X�L�b�v�t�@�C���p�X	*/
#define	MYAPP_PRM_ITVAL			"ITVAL"			/* FTP�����i�P�ʁF�b�j						*/

/***********************************************************************
	�R�����h�c�t�@�C���iBUNPOS�j
***********************************************************************/
/* �����Ǘ��p�t�@�C����(�P����O)	*/
#define		FNM_3RDID_BAK		"3rdid.bak"
/* �����Ǘ��p�t�@�C����(����)	*/
#define		FNM_3RDID_DAT		"3rdid.dat"
/* �������R�}���h�t�@�C����	*/
#define		FNM_3RDID_CMD		"3rdid.ftp"
/* �ʔԊǗ��t�@�C��	*/
#define		FNM_3RDID_NUM		"3rdid.num"

#define    RET_NOTH  100
#define    RET_OK    0
#define    RET_NG   -1
#define	RET_NORMAL	RET_OK
#define	RET_ERROR	RET_NG

/*********************************************
*  ���O���b�Z�[�W�֘A
*********************************************/
#define _LOG_MSG_START          1	/* �v���Z�X�J�n */
#define _LOG_MSG_STARTERR       4	/* ER �v���Z�X�N�����s */
#define _LOG_MSG_HIGAWARI       9	/* ���֏I��          */
#define _LOG_MSG_SYSTEM        10	/* �����I��          */
#define _LOG_MSG_ABORT         11	/* ��ްďI��         */
#define _LOG_MSG_RCVEND       122	/* NR �d�m�c��M�m�F */
#define _LOG_MSG_FACCESSERR   201	/* ER �t�@�C���A�N�Z�X�G���[ */
#define _LOG_MSG_FOPENERR     202	/* ER �t�@�C���I�[�v���G���[ */
#define _LOG_MSG_FREAD        205	/* NR �t�@�C���q�d�`�c */
#define _LOG_MSG_FREADERR     206	/* ER �t�@�C���q�d�`�c�G���[ */
#define _LOG_MSG_FWRITE       207	/* NR �t�@�C���v�q�h�s�d */
#define _LOG_MSG_FWRITEERR    208	/* ER �t�@�C���v�q�h�s�d�G���[ */
#define _LOG_MSG_DATAERR     5305	/* ER �f�[�^�s�� */
#define _LOG_MSG_DEBUG       9000	/* �f�o�b�O           */

/**********************************************
*   �v���Z�X�����\����
***********************************************/
typedef struct _LM_FILED {
	char    name[ LEN_BUFF +1 ] ;   /* �v���Z�X�� */
	int     pno ;                   /* �v���Z�XNo */
} LM_FILED ;
LM_FILED  LM ;    /* ��۾������\����    */

#define		MYAPP_PATH_SIZE		(1024)	/* �f�B���N�g���i�[�T�C�Y */

/* �v���O�������\���� */
struct	appEnv	{
	BMLPRM				*bp ;
	char				*pcFielNamePRM ;
	int					 shm_Id ;
	key_t				 shm_Key ;						/* ���L�������L�[							*/
	int					 sleep_Sec ;					/* �X���[�v									*/
	char	 			 cFtpHost[32+1] ;				/* �����[�g���z�X�g��						*/
	char				 cFtpUser[32+1] ;				/* �����[�g�����O�C�����[�U					*/
	char				 cFtpPswd[32+1] ;				/* �����[�g�����O�C���p�X���[�h 			*/
	char				 cR_Path[MYAPP_PATH_SIZE] ;		/* �����[�g����M���p�X						*/
	char				 cR_File[64+1] ;				/* �����[�g����M�t�@�C����					*/
	char				 cL_Path[MYAPP_PATH_SIZE] ;		/* ���[�J������M��p�X						*/
	char				 cI_Path[MYAPP_PATH_SIZE] ;		/* ���[�J�����W�J�p�p�X						*/
	char				 cM_Path[MYAPP_PATH_SIZE] ;		/* �����Ǘ��f�B���N�g���p�X					*/
	char				 cS_Path[MYAPP_PATH_SIZE] ;		/* 3ID���W�J(AD108)�̃X�L�b�v�t�@�C���p�X	*/
	int					 iItval ;						/* FTP�����i�P�ʁF�b�j						*/
} ;

/* ��M�t�@�C���̃f�[�^���R�[�h(�Œ蒷) */
typedef	struct	_3rdid {
	char	szUkeymd[8];
	char	szIraino[11];
	char	szSriymd[8];
	char	szKentaino[11];
	char	szRuckid[8];
	char	szPos[3];
	char	szYobi[15];
	char	lf[1];
} TXT_3RDID;

/* ��M�t�@�C���̂d�m�c���R�[�h(�Œ蒷) */
typedef	struct	_3rdid_end {
	char	szEnd[3];
	char	szYobi[61];
	char	lf[1];
} TXT_3RDID_END;

#define		RECLEN_3RDID		65		/* �P���R�[�h�� */

#define		RECEND_3RDID		"END"	/* �d�m�c���R�[�h */

#define		SEND_BUNPOS			"POS"	/* BUNPOS�W�J�p�t�@�C�������� */

#define		SKIP_BUNPOS			"SKIP"	/* BUNPOS�W�JSKIP�t�@�C�������� */

/* #003 �Ή� */
#define		TMP_BUNPOS			"TMP"	/* BUNPOS�W�J�ꎞ�t�@�C�������� */

/***********************************************************************
	�}�N����`
***********************************************************************/

/* �g���[�X��� */
#define		LT_DBG			"D"	
#define		LT_TRC			"T"	
#define		LT_OPT			"O"	
#define		LT_WRN			"W"	
#define		LT_ERR			"E"	
#define		LT_SYS			"A"	
#define		LT_STA			"STA"	
#define		LT_END			"END"	
/* ���s�t���O */
#define		LX_SEL			"S"	
#define		LX_INS			"I"	
#define		LX_UPD			"U"	
#define		LX_DEL			"D"	
#define		LX_NON			" "	

#define		MYAPP_SHM_SIZE		sizeof ( int )


#define	__LO_FTP3RDID
#endif
