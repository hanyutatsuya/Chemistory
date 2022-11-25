/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FLD105.h                                                      */
/* �@�T�@�@�@�v�F�p�����[�^�擾�w�b�_                                         */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _LD105_h
#define _LD105_h
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
#define	MYAPP_APP_NAME			"LD105"
#define	MYAPP_APP_NAME_JP		"LD105"
#define	MYAPP_LOGINIFILE		"LD105_LOG.ini"

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
#define	MYAPP_PRM_SLEEP_MIN	"SLEEP_MIN"
#define	MYAPP_PRM_DB_NAME	"DB_NAME"
#define	MYAPP_PRM_DB_USER	"DB_USER"
#define	MYAPP_PRM_DB_PASSWD	"DB_PASSWD"
#define MYAPP_PRM_DIR_INPUT	"INPUT_DIR"
#define MYAPP_PRM_DIR_OK	"END_DIR_OK"
#define MYAPP_PRM_DIR_NG	"END_DIR_NG"
#define MYAPP_PRM_FILE_PRX	"FILE_PRX"
#define MYAPP_PRM_LOCK_FILE	"LOCK_FILE"

//	�f�B���N�g���i�[�T�C�Y
#define	MYAPP_PATH_SIZE		(1024)

#define MYAPP_LEN_FNCNM		32
#define MYAPP_LEN_MSG		3072

#define RECORDSIZE		1024

#define	FILE_RECSIZE		1024

//	���L�������T�C�Y
#define	MYAPP_SHM_SIZE		sizeof ( int )

#define	MYAPP_MAX_CHAR		256
/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �v���O�������\����
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	int	 SleepMin ;
	char	 cInputDir[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirOK[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirNG[MYAPP_PATH_SIZE] ;
	char	 cFilePrx[MYAPP_PATH_SIZE] ;
	char	 cLockFile[MYAPP_PATH_SIZE] ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ; 
} pAppEnv;

/*==============================================================*/
/* ���֌��ʏ��t�@�C��						*/
/*==============================================================*/
typedef struct file_othkekka {
	char	recid[2];			/* ���R�[�h����		 	*/
	char	utkymd[8];			/* �a�l�k��t�N����		*/
	char	irino[11];			/* �˗����m�n			*/
	char	kmkcd[7];			/* ���ڃR�[�h			*/
	char	kntno[11];			/* ���̂m�n			*/
	char	chkmj[2];			/* �`�F�b�N����			*/
	char	stzrcd[3];			/* ����ޗ��R�[�h		*/
	char	kmkrs[8];			/* ���ږ�����			*/
	char	oyakmkcd[7];			/* �e���ڃR�[�h			*/
	char	setkmkcd[7];			/* �Z�b�g���ڃR�[�h		*/
	char	hsykflg[1];			/* ��Ɖ�t���O			*/
	char	hskflg[1];			/* �񐿋��敪			*/
	char	hhkkflg[1];			/* ��񍐃t���O			*/
	char	srinycd[1];			/* �������e�R�[�h		*/
	char	seccd[2];			/* �Z�N�V�����R�[�h		*/
	char	skchkflg[1];			/* �o�׃`�F�b�N�t���O		*/
	char	bkfkkbn[1];			/* ���敉�׋敪			*/
	char	ysnlvl[2];			/* �D�惌�x��			*/
	char	tikflg[1];			/* �ǉ��t���O			*/
	char	skjflg[1];			/* �폜�t���O			*/
	char	jkntikflg[1];			/* �����t���ǉ��t���O		*/
	char	kkckkacd[1];			/* �g�����ʂc�a���ʃR�[�h	*/
	char	fdkkckkacd[1];			/* �e�c�g�����ʂc�a���ʃR�[�h	*/
	char	knslabcd[3];			/* �������{���{�R�[�h		*/
	char	uktkbn[1];			/* ��t�敪			*/
	char	kkajkcd[1];			/* ���ʏ󋵃R�[�h		*/
	char	pncrgflg[1];			/* �p�j�b�N�����W�t���O 	*/
	char	knkgrp[1];			/* �ً}�O���[�v			*/
	char	kkaksflg[1];			/* ���ʊ��Z�t���O		*/
	char	kkassflg[1];			/* ���ʏC���t���O		*/
	char	knskka1[8];			/* ���ʂP			*/
	char	knskka2[8];			/* ���ʂQ			*/
	char	knskka2kbn[1];			/* ���ʂQ�敪			*/
	char	kkahskcd[3];			/* ���ʕ⑫�R�[�h		*/
	char	kkacmt1[4];			/* ���ʃR�����g�P		*/
	char	kkacmt2[4];			/* ���ʃR�����g�Q		*/
	char	ijkbnm[1];			/* �ُ�l�敪�i�j�j		*/
	char	ijkbnf[1];			/* �ُ�l�敪�i���j		*/
	char	ijkbnn[1];			/* �ُ�l�敪�i�s���j		*/
	char	sdi[3];				/* �w�� 			*/
	char	hkkhjkka[8];			/* �񍐏��\�L����		*/
	char	hkkhjkkakj[16];			/* �񍐏��\�L����(����) 	*/
	char	kjntino[3];			/* ��l�m�n			*/
	char	hkahkkkbn[1];			/* ���ו񍐂m�n�\���敪 	*/
	char	strno[5];			/* �o�͏��V���A���m�n		*/
	char	htkihka[12];			/* ���^���׎���		*/
	char	kkatimstamp[26];		/* ���ʍX�V�^�C���X�^���v	*/
	char	knsendyti[8];			/* ���������\���		*/
	char	sriymd[8];			/* �����N����			*/
	char	gcyuskcd[1];			/* �O����R�[�h			*/
	char	ltgtcd[1];			/* �k�s�f�s�ϊ��R�[�h		*/
	char	kkaovr[1];			/* ���ʂU���I�[�o�[�t���O	*/
	char	tktfrk[1];			/* �����U�փt���O		*/
	char	kntinokkt[1];			/* ���̂m�n�m��t���O		*/
	char	labtyakuymd[8];			/* ���{����			*/
	char	wscd[4];			/* �v�^�r�R�[�h			*/
	char	seq[6];				/* �r�d�p			*/
	char	sryokktflg[1];			/* �ޗ��m��t���O		*/
	char	tikakmkhji[1];			/* �ǉ����ڕ\���t���O		*/
	char	kkaupdhji[1];			/* ���ʏC�����ڕ\���t���O	*/
	char	filler[61];			/* �\�� 			*/
} my_stFileOTHERKKA;

/******************************************************************************/
/* �f�[�^�\���̒�`                                                           */
/******************************************************************************/
//      �V�X�e���Ǘ��}�X�^���\����
typedef struct  _stSYSKNR {
	char	kjnsriymd[10+1];	// ������N����
	char	iriendflg[1+1];		// �˗�END�t���O
	char	bchendflg[1+1];		// ����END�t���O
	char	unyflg[1+1];		// �^�p�t���O
} my_stSYSKNR ;


// <<   ���T�e���C�g���ʏ��e�[�u��      >>
typedef struct	db_otherkka {
	char	utkymd[10+1];
	char	irino[11+1];
	char	kmkcd[7+1];
	char	sriymd[10+1];
	char	kntno[13+1];
	char	chkmj[4+1];
	char	stzrcd[4+1];
	char	kmkrs[16+1];
	char	oyakmkcd[7+1];
	char	seccd[2+1];
	char	bkfkkbn[1+1];
	char	knsjslbcd[3+1];
	char	kkajkcd[1+1];
	char	pncrgflg[1+1];
	char	kkaksflg[1+1];
	char	kkassflg[1+1];
	char	knskka1[12+1];
	char	knskka2[24+1];
	char	knskka2kbn[2+1];
	char	kkahskcd[3+1];
	char	kkacmt1[5+1];
	char	kkacmt2[5+1];
	char	ijkbnm[1+1];
	char	ijkbnf[1+1];
	char	ijkbnn[1+1];
	char	sdi[3+1];
	char	hkkki[24+1];
	char	hkkkiknj[24+1];
	char	kjno[3+1];
	char	smpcd[7+1];
	short	knsseq;
	char	ksndh[26+1];
	char	trkdh[26+1];
} my_stDbOTHERKKA;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
#endif
/** End of File ***************************************************************/

