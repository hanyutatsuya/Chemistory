/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FFD103.h										*/
/*		�T�v		�F�����Z�����菈��								*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2007/04/06		T.Wajima		Create					*/
/* ----------------------------------------------------------------	*/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  2.00	2008/10/09		K.Ameno			�����Z���Ή�����		*/
/********************************************************************/

#ifndef _FD103_h_
#define _FD103_h_

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <math.h>
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_date.h"
#include "bml_DBCom.h"
#include "bml_misc.h"

/******************************************************************************/
/* �萔��`	                                                                  */
/******************************************************************************/

/*�v���O������ */
#define APP_NAME	"FD103"

/* ���O�t�@�C��INI�t�@�C�� */
#define LOGINIFILE "/home/kea00sys/bin/FD103_LOG.ini"

/* �G���[�R�[�h */

/* ���O�G���[�R�[�h��` */
#define MYAPP_LOG_ERRCODE_NON       "00000000"
#define MYAPP_LOG_ERRCODE_APP       "010"
#define MYAPP_LOG_ERRCODE_DB        "020"
#define MYAPP_LOG_ERRCODE_ETC       "0Z0"

/* �v���O�����G���[�R�[�h��` */
#define ERROR_CODE_NORMAL			 0
#define	ERROR_CODE_CMD_PRM_ERROR	-1
#define	ERROR_CODE_PRM_OPEN_ERROR	-2
#define ERROR_CODE_LOG_OPEN_ERROR	-3
#define ERROR_CODE_PRM_GET_ERROR	-4
#define ERROR_CODE_DB_CONNECT_ERROR	-5
#define ERROR_DB_ERROR				-6
#define ERROR_FUNC_ERROR			-7
#define ERROR_CTRL_COUNT			-8
#define ERROR_CHANNEL_HOSEI_FUYOU	-9
#define ERROR_MEMORY_ERROR			-10
#define ERROR_MULTI_RUN				-11

/* �p�����[�^�L�[ */
#define PRM_DB_NAME					"DB_NAME"
#define PRM_DB_USER_ID				"DB_USER_ID"
#define	PRM_DB_PASSWORD				"DB_PASSWORD"
#define PRM_SLEEP_SEC				"SLEEP_SEC"
#define PRM_SHM_KEY					"SHM_KEY"
#define PRM_SEL_MAX					"SEL_MAX"

#define         MYAPP_SHM_SIZE          sizeof ( int )

#define     MYAPP_LEN_MSG       1024
#define     MYAPP_LEN_ERR       32
#define     MYAPP_LEN_FNCNM     32

            /* �g���[�X��� */
#define     LT_DBG          "D"
#define     LT_TRC          "T"
#define     LT_OPT          "O"
#define     LT_WRN          "W"
#define     LT_ERR          "E"
#define     LT_SYS          "A"
#define     LT_STA          "STA"
#define     LT_END          "END"
            /* ���s�t���O */
#define     LX_SEL          "S"
#define     LX_INS          "I"
#define     LX_UPD          "U"
#define     LX_DEL          "D"
#define     LX_NON          " "
            /* �G���[�R�[�h */
#define     LE_NON          " "

struct {
    char    dbp_dbAlias[15];            /*  DB */
    char    dbp_user[129];              /*  user */
    char    dbp_pswd[15];               /*  password */
    char    lgp_comlog[256];            /* LOG FILE NAME */
    char    myp_exefile[256];           /* LoadModuleName */
    int     myp_debug;
} stcPRM;


/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
extern      char        G_msg[MYAPP_LEN_MSG+1]; /* LogMessage */
extern      char        G_err[MYAPP_LEN_ERR+1]; /* LogMessage(errcode) */

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
int         LogOut( char *sbt, char *flg, char *ecd, char *msg,
                    char *fncnm, char *file, long line );
/*/PG�ŗL���� */
char        *EnvRef( char *src_cp );
char        *GetIniFile( char *section, char *key, char *profile );
int         chkLowHigh( double  hikaku1, double  hikaku2, int ketasu );

/* �R���g���[���Ǘ��e�[�u���֘A */
#define CTRLHDFLG_SEIJOU			'S'
#define CTRLHDFLG_IJOU				'I'
#define CTRLHDFLG_KOUSEI_IJOU		'K'

#define CTRLKTFLG_KAKUTEI_MAE		'0'
#define CTRLKTFLG_KAKUTEI_SUMI		'1'

/* �̈�m�ۊ֘A */
#define ALLOC_INIT		2000	/* ����̈�m�ی��� */
#define ALLOC_ADD		200		/* �̈�m�ۑ������� */

/*�Z���ΏۊO���R�R�[�h */
typedef enum
{
	 KSTS_OK 		=	0		/* �Z���Ώۃf�[�^ */
	,KSTS_NORMAL	=	1		/* ����l�i�Z���̕K�v�Ȃ��j */
	,KSTS_CTRLNO	=	2		/* �ΏۊO�R���g���[��NO */
	,KSTS_CTRLNONE	=	3		/* �R���g���[���{�����B�i�ŐV�f�[�^�ȊO��NG�Ƃ���j */
	,KSTS_CTRLNG	=	4		/* �ΏۊO�R���g���[���i�O�j */
	,KSTS_HIST		=	5		/* �q�X�g�K�����G���[�i�T�����j */
	,KSTS_RENGE		=	6		/* �ΏۊO�����W */
	,KSTS_FB_OVER	=	7		/* �ΏۊO�t�@�N�^/�x�[�X�͈͊O�E��� */
	,KSTS_FB_CALC	=	8		/* �ΏۊO�t�@�N�^/�x�[�X�v�Z�s�� */
	,KSTS_2HOUSEI	=	9		/* ������f�[�^ */
	,KSTS_SAIHIN	=  10		/* �ŕp�l�G���[ */
	,KSTS_COUNT		=  11		/* �T���v�������B 2009.2.3 Nagata */
	,KSTS_SAISOKU	=  12		/* �đ���̕K�v�L��i�Z�����Ȃ��j 2009.2.6 Nagata */
} KSTSERR;

typedef enum
{
	 CV_NORMAL
	,CV_ABNORMAL
} CTRLVALUE;

typedef enum
{
	 KJ_KOUSEI_KA
	,KJ_KOUSEI_FUYOU
	,KJ_KOUSEI_FUKA
}KOUSEIJISSI;

typedef enum
{
	 RH_NORMAL
	,RH_KOUSEI
	,RH_SAIKEN
	,KOUSEI_IJOU
}RANGE_HANTEI;

/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/

/* �v���O�����Ǘ��\���� */
typedef struct
{
	BMLPRM*		bp;				
	struct		stcLogMember      stLogMem;
	char		cDbName[128];
	char		cDbUserId[128];
	char		cDbPassword[128];
	char		cUpdateId[128];						/* �X�V��ID */
	char		cUpdateName[128];					/* �X�V�� */
	char		cLogName[128];						/* ���O */
	int			sleepInterval;						/* ���s�Ԋu(�~���b) */
	int			shm_Key;							/* ���L������KEY */
	int			sel_Max;							/* CTRL���ʓǍ��ő匏�� */
	
} ENV, *PENV;

ENV		stEnv;

/* ���L�������Ǘ��\���� */
struct  SHM {
    int     shm_Id ;
    key_t   shm_Key ;
};

/* �Z���Ώۃ��X�g */
typedef struct
{
	char   knskisymd[11];		/* �����J�n�� */
	char   bskkbn[5];			/* ���͋@�敪 */
	char   bsklne[5];			/* ���͋@���C�� */
	char   bskgok[7];			/* ���͋@���@ */
	int    ctrlno;				/* �R���g���[���ԍ� */
	char   nbkmkcd[8];			/* �������ڃR�[�h */
	char   ctrlsbt[21];			/* �R���g���[����� */
	char   sktti[25];			/* ����l */
	char   ctrlx[13];			/* ���ϒl */
	int    sstnksu;				/* �����_���� */
	char   facterjd1[13];		/* �t�@�N�^�[�����P */
	char   facterjd2[13];		/* �t�@�N�^�[�����Q */
	char   basejd1[13];			/* �x�[�X�����P */
	char   basejd2[13];			/* �x�[�X�����Q */
	int    nonecnt;				/* �R���g���[�����x����i�O�ȊO�͖{�����B�j */
	int    ngcnt;				/* �R���g���[�����x����i�O�ȊO�͐��x�ُ�j */
    double shrnglwhf;           /* �ŕp�����W�����l�␳�O */
    double shrnghihf;           /* �ŕp�����W����l�␳�O */
    double shrnglwhb;           /* �ŕp�����W�����l�␳�� */
    double shrnghihb;           /* �ŕp�����W����l�␳�� */
    double hstkjntn;            /* �q�X�g�쐬��_ */
    double hstkzmhb;            /* �q�X�g���ݕ� */
    int    hstkaikyu;           /* �q�X�g�K���� */
    int    ksikjnspsu;          /* �Z����T���v���� */
} KTLIST;

/* �����Z���ΏۃR���g���[���e�[�u�� */
typedef struct
{
	int    seq;
    char   knskisymd[11];
    char   bskkbn[5];
    char   bsklne[5];
    char   bskgok[7];
    char   nbkmkcd[8];
    int    ctrlnoFrom;
    int    ctrlnoTo;
	int    sstnksu;
    double facter;
    double base;
	char   autokosiflg[2];
	char   kosizmflg[2];
	char   causecd[9];
	char   kosierrcd[9];
	int    kensu;
	char   yobi1[11];
	char   yobi2[11];
	char   yobi3[11];
	char   termid[16];
	char   kosidh[22];
	char   sksdh[22];
	char   ksndh[22];
} ATKSTS;

/* �Z���W���Z�o�p�p�����[�^ */
typedef struct  toukei_stat_area{
    int     n;
    double  sumx;
    double  sumy;
    double  sumxy;
    double  sumxx;
    double  sumyy;
}   TOUKEI_CALC;

#endif
/** End of File ***************************************************************/
