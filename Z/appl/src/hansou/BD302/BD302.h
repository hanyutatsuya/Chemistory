/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FBD302.h                                                      */
/* �@�T�@�@�@�v�F�X�g�b�J�[�y����z                                           */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  x.xx     2006/01/15     �F��O�K       �V�K�쐬                           */
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

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"BD302"
#define	MYAPP_APP_NAME_JP		"BD302"
#define	MYAPP_LOGINIFILE		"BD302_LOG.ini"

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
#define	MYAPP_PRM_DIR_NR_COL		"DIR_NR_COL"
#define	MYAPP_PRM_DIR_NR_COL_OK		"DIR_NR_COL_OK"
#define	MYAPP_PRM_DIR_NR_COL_ERR	"DIR_NR_COL_ERR"
#define	MYAPP_PRM_DIR_NR_LOG		"DIR_NR_LOG"		//���g�p
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
#define	MYAPP_RECV_KIND			"RE"
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
//	char				 cVersion[32+1] ;					//���g�p
} ;

//	�g���[�E���b�N�R�t������`�\����
struct	trInfo	{
	char	 trid[MYAPP_TRNO_SIZE] ;
	char	 stkno[MYAPP_STKNO_SIZE] ;
	char	 knskisymd[MYAPP_DATE_SIZE] ;
	char	 asyrckid[MYAPP_RACK_MAXCNT][MYAPP_RKNO_SIZE] ;
	char	 createDate[MYAPP_DEOF_SIZE] ;
} ;

//	�����I�[�_�[���\����
struct my_stKENORDER
{
  char knskisymd[11];
  char sriymd[11];
  char kntno[14];
  char kntketflg[2];
  char knsgrp[17];
  char kmkcd[8];
  short knssu;
  short knssueda;
  char irihsmkbn[2];
  char irikbn[2];
  char ksktkbn[2];
  char utkymd[11];
  char irino[12];
  char iriketflg[2];
  short zssdino;
  char sstcd[8];
  char trid[11];
  short trpos;
  char asyrckid[11];
  short asyrckpos;
  char oyakmkcd[8];
  char seccd[3];
  char bkfkkbn[2];
  char smpcd[8];
  char bskkbn[5];
  char nbkmkcd[8];
  char zrcd[4];
  char ysnlbl[3];
  char kjno[4];
  char fkhkknohjkbn[2];
  char tbkjno[4];
  char tbkjflg[2];
  char htkfkhms[25];
  char skflg[2];
  char tskflg[3];
  char tktflg[3];
  char ytiksbr[16];
  char kkflg[2];
  char kkiriflg[2];
  short kkirilotno;
  char sc[6];
  char tj[6];
  char tjtni[2];
  char sbtkbn[2];
  char birthday[9];
  char birthdaykbn[2];
  char age[4];
  char agekbn[2];
  char sstme[9];
  char ssymd[11];
  char tntme[5];
  char tntni[2];
  char tnryo[6];
  char tnryotni[2];
  sqlint32 knsseq;
  short bthno;
  char knsjkflg[2];
  char ksndh[27];
} ;

//	�����`�F�b�N���\����
struct my_stREALCHK
{
  char knskisymd[11];
  char sriymd[11];
  char kntno[14];
  char kntketflg[2];
  char knsgrp[17];
  char kmkcd[8];
  short knssu;
  short knssueda;
  char utkymd[11];
  char irino[12];
  char iriketflg[2];
  short zssdino;
  char trid[11];
  short trpos;
  char asyrckid[11];
  short asyrckpos;
  char bskkbn[5];
  char nbkmkcd[8];
  char genkaiflg[2];
  char soukn1flg[2];
  char kanrenflg[2];
  char bunkkuflg[2];
  char kesseiflg[2];
  char rirekiflg[2];
  char syougoflg[2];
  char keisanflg[2];
  char per100flg[2];
  char tousekflg[2];
  char kisyakflg[2];
  char kouseiflg[2];
  char syoungflg[2];
  char soukn2flg[2];
  char fukaptflg[2];
  char yobiflg01[2];
  char tobiflg02[2];
  char yobiflg03[2];
  char yobiflg04[2];
  char yobiflg05[2];
  struct
  {
    short length;
    char  data[256];
  } genkaipara;
  struct
  {
    short length;
    char  data[256];
  } soukn1para;
  struct
  {
    short length;
    char  data[256];
  } kanrenpara;
  struct
  {
    short length;
    char  data[256];
  } bunkkupara;
  struct
  {
    short length;
    char  data[256];
  } kesseipara;
  struct
  {
    short length;
    char  data[256];
  } rirekipara;
  struct
  {
    short length;
    char  data[256];
  } syougopara;
  struct
  {
    short length;
    char  data[256];
  } keisanpara;
  struct
  {
    short length;
    char  data[256];
  } per100para;
  struct
  {
    short length;
    char  data[256];
  } tousekpara;
  struct
  {
    short length;
    char  data[256];
  } kisyakpara;
  struct
  {
    short length;
    char  data[256];
  } kouseipara;
  struct
  {
    short length;
    char  data[256];
  } syoungpara;
  struct
  {
    short length;
    char  data[256];
  } soukn2para;
  struct
  {
    short length;
    char  data[256];
  } fukaptpara;
  struct
  {
    short length;
    char  data[256];
  } yobipara01;
  struct
  {
    short length;
    char  data[256];
  } yobipara02;
  struct
  {
    short length;
    char  data[256];
  } yobipara03;
  struct
  {
    short length;
    char  data[256];
  } yobipara04;
  struct
  {
    short length;
    char  data[256];
  } yobipara05;
  char ksndh[27];
} ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/
