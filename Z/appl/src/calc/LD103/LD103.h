/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FLD103.h                                                      */
/* �@�T�@�@�@�v�F�p�����[�^�擾�w�b�_                                         */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/******************************************************************************/
#ifndef _LD103_h
#define _LD103_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <sys/shm.h>
#include "bml_base.h"
#include "bmlprm.h"
#include "bmllog.h"

/******************************************************************************/
/* Define��`                                                                */
/******************************************************************************/
#define	MYAPP_APP_NAME			"LD103"
#define	MYAPP_APP_NAME_JP		"LD103"
#define	MYAPP_LOGINIFILE		"LD103_LOG.ini"

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

//	�����`�F�b�N�t���O��`
#define MYAPP_ZOK_NOT_CHK		"0"	// �����`�F�b�N�ΏۊO
#define MYAPP_ZOK_CHK			"1"	// �����`�F�b�N�Ώ�
#define MYAPP_ZOK_ERR			"2"	// �����`�F�b�N�G���[
#define MYAPP_ZOK_NG			"3"	// �����`�F�b�N�G���[(�ُ�l)

//	�񍐕ۗ��t���O��`
#define MYAPP_HKKHR_ERR			1	// �������G���[�L��
#define MYAPP_HKKHR_NG			2	// �������ُ�l�L��
#define MYAPP_HKKHR_CALC		3	// �Čv�Z�҂�(�����C����)
#define MYAPP_HKKHR_OK			0	// �ۗ�����
 
//	�G���[�R�[�h��`
#define	MYAPP_LOG_ERRCODE_NON		"00000000"
#define	MYAPP_LOG_ERRCODE_APP		"010"
#define	MYAPP_LOG_ERRCODE_DB		"020"
#define	MYAPP_LOG_ERRCODE_ETC		"0Z0"

//	�G���[�R�[�h�ڍ�
#define MYAPP_SQL_DEADLOCK		-911
#define MYAPP_SQL_DUPLICATION		-803

//	�p�����[�^������
#define MYAPP_PRM_SHM_KEY		"SHM_KEY"
#define MYAPP_PRM_SLEEP_MIN		"SLEEP_MIN"
#define MYAPP_PRM_DB_NAME		"DB_NAME"
#define MYAPP_PRM_DB_USER		"DB_USER"
#define MYAPP_PRM_DB_PASSWD		"DB_PASSWD"
#define MYAPP_PRM_DIR_INPUT		"INPUT_DIR"
#define MYAPP_PRM_DIR_OK		"END_DIR_OK"
#define MYAPP_PRM_DIR_NG		"END_DIR_NG"
#define MYAPP_PRM_FILE_PRX		"FILE_PRX"
#define MYAPP_PRM_FILE_GET_SHELL	"FILE_GET_SHELL"
#define MYAPP_PRM_LOCK_FILE		"LOCK_FILE"
#define MYAPP_PRM_AGE_HI		"AGE_HI"
#define MYAPP_PRM_AGE_LOW		"AGE_LOW"
#define MYAPP_PRM_SC_HI			"SC_HI"
#define MYAPP_PRM_SC_LOW		"SC_LOW"
#define MYAPP_PRM_TJ_HI			"TJ_HI"
#define MYAPP_PRM_TJ_LOW		"TJ_LOW"


//	�f�B���N�g���i�[�T�C�Y
#define	MYAPP_PATH_SIZE			(1024)

#define MYAPP_LEN_FNCNM			32
#define MYAPP_LEN_MSG			3072

#define RECORDSIZE			1024

//	���L�������T�C�Y
#define	MYAPP_SHM_SIZE			sizeof ( int )

#define	MYAPP_ZAIRYO			"002"
#define	MYAPP_KJSPACE10			"�@�@�@�@�@�@�@�@�@�@"
#define	MYAPP_SPACE10			"          "

//      ���t�`�F�b�N���[�h
#define	VALDATE_DATE			1			// DATE�^
#define	VALDATE_TIME			2			// time�^
#define	VALDATE_TIMESTAMP 		3			// taimestamp�^

//	MAX LENGTH
#define	MYAPP_MAX_CHAR			256			// with iconv

//	MAX LENGTH
#define	RTN_NONE			100
/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/
// �v���O�������\����
struct	appEnv {
	BMLPRM	*bp	;
	char	*pcFielNamePRM ;
	int	 shm_Id ;
	key_t	 shm_Key ;
	char	 cDb_Name[32+1] ; 
	char	 cDb_User[32+1] ; 
	char	 cDb_Passwd[32+1] ; 
	char	 cInputDir[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirOK[MYAPP_PATH_SIZE] ;
	char	 cEndFileDirNG[MYAPP_PATH_SIZE] ;
	char	 cFilePrx[MYAPP_PATH_SIZE] ;
	char	 cFileGetSH[MYAPP_PATH_SIZE] ;
	char	 cLockFile[MYAPP_PATH_SIZE] ;
	int	 AgeHi;
	int	 AgeLow;
	double	 ScHi;
	double	 ScLow;
	double	 TjHi;
	double	 TjLow;
	int	 SleepMin ;
} pAppEnv ;

//	�V�X�e���Ǘ��}�X�^���\����
typedef struct  _stSYSKNR {
        char    kjnsriymd[10+1];	// ������N����
        char    iriendflg[1+1];		// �˗�END�t���O
        char    bchendflg[1+1];		// ����END�t���O
        char    unyflg[1+1];		// �^�p�t���O
} my_stSYSKNR ;

//	���\����
typedef struct  _stFileKanjya {
	char	c_sbt[2];		/* ں��ގ��ʋ敪        */
	char	c_bml_ymd[8];		/* BML��t�N����        */
	char	c_irai_no[11];		/* �˗���No             */
	char	c_siset_cd[7];		/* �{�ݺ���             */
	char	c_subsiset_cd[4];	/* ��ގ{�ݺ���          */
	char	c_card1_kbn[2];		/* ���ދ敪1            */
	char	c_card2_kbn[2];		/* ���ދ敪2            */
	char	c_iraimoto_key[20];	/* �˗�����             */
	char	c_ka_cd[3]; 		/* �f�ÉȺ���           */
	char	c_ka_nm[15];		/* �f�ÉȖ�             */
	char	c_dr_cd[8]; 		/* �S���㺰��           */
	char	c_dr_nm[15];		/* �S���㖼             */
	char	c_karte_no[15];		/* ���No                */
	char	c_kanja_id[15];		/* ����ID               */
	char	c_kanja_nm[20];		/* ���Җ�               */
	char	c_kanja_knm[20];	/* ���Җ��i�����j       */
	char	c_tall[5];        	/* �g��                 */
	char	c_weight[5];      	/* �̏d                 */
	char	c_weight_kbn[1];  	/* �̏d�P��             */
	char	c_sex[1];         	/* ���ʋ敪             */
	char	c_birth_ymd[8];   	/* ���N����             */
	char	c_birth_kbn[1];   	/* ���N�����敪         */
	char	c_age[3];         	/* �N��                 */
	char	c_age_kbn[1];     	/* �N��敪             */
	char	c_byoto_cd[5];    	/* �a������             */
	char	c_byoto_nm[15];   	/* �a����               */
	char	c_ukecmt1_cd[2];  	/* ��t���ĺ���1        */
	char	c_ukecmt2_cd[2];  	/* ��t���ĺ���2        */
	char	c_ukecmt3_cd[2];  	/* ��t���ĺ���3        */
	char	c_ukecmt1_cmt[20];	/* ��t�����ذ1         */
	char	c_ukecmt2_cmt[20];	/* ��t�����ذ2         */
	char	c_ng_kbn[1];     	/* ���O�敪             */
	char	c_ninsin_cnt[2]; 	/* �D�P�T��             */
	char	c_hoken_cd[1];   	/* �ی�����             */
	char	c_zairyo01_cd[3];	/* �ޗ�����1            */
	char	c_zairyo02_cd[3];	/* �ޗ�����2            */
	char	c_zairyo03_cd[3];	/* �ޗ�����3            */
	char	c_zairyo04_cd[3];	/* �ޗ�����4            */
	char	c_zairyo05_cd[3];	/* �ޗ�����5            */
	char	c_zairyo06_cd[3];	/* �ޗ�����6            */
	char	c_zairyo07_cd[3];	/* �ޗ�����7            */
	char	c_zairyo08_cd[3];	/* �ޗ�����8            */
	char	c_zairyo09_cd[3];	/* �ޗ�����9            */
	char	c_zairyo10_cd[3];	/* �ޗ�����10           */
	char	c_yokisu01[2];		/* �{���i�e�퐔�j1      */
	char	c_yokisu02[2];		/* �{���i�e�퐔�j2      */
	char	c_yokisu03[2];		/* �{���i�e�퐔�j3      */
	char	c_yokisu04[2];		/* �{���i�e�퐔�j4      */
	char	c_yokisu05[2];		/* �{���i�e�퐔�j5      */
	char	c_yokisu06[2];		/* �{���i�e�퐔�j6      */
	char	c_yokisu07[2];		/* �{���i�e�퐔�j7      */
	char	c_yokisu08[2];		/* �{���i�e�퐔�j8      */
	char	c_yokisu09[2];		/* �{���i�e�퐔�j9      */
	char	c_yokisu10[2];		/* �{���i�e�퐔�j10     */
	char	c_saisyu_time[4];	/* �̎掞��             */
	char	c_saisyu_ymd[8];	/* �̎�N����           */
	char	c_nyotime[4];		/* �~�A����             */
	char	c_nyotime_kbn[1];	/* �~�A���ԁi�P�ʁj     */
	char	c_nyoryo[5];		/* �~�A��               */
	char	c_nyoryo_kbn[1]; 	/* �~�A�ʁi�P�ʁj       */
	char	c_tochak_ymd[8]; 	/* ���̓����\���       */
	char	c_imoto_lab[3];		/* �˗���ID             */
	char	c_hsaki_lab1[3]; 	/* �񍐐�ID�P           */
	char	c_hsaki_lab2[3]; 	/* �񍐐�ID�Q           */
	char	c_hsaki_lab3[3]; 	/* �񍐐�ID�R           */
	char	c_gmoto_lab1[3]; 	/* �O����ID1            */
	char	c_gmoto_lab2[3]; 	/* �O����ID2            */
	char	c_gmoto_lab3[3]; 	/* �O����ID3            */
	char	c_gmoto_lab4[3]; 	/* �O����ID4            */
	char	c_gmoto_lab5[3]; 	/* �O����ID5            */
	char	c_gsaki_lab[3];	 	/* �O����ID             */
	char	c_verify_kbn[1]; 	/* ���̧��󋵋敪       */
	char	c_zokdel_flg[1]; 	/* �����폜�׸�         */
	char	c_zokupd_flg[1]; 	/* �����C���׸�         */
	char	c_kinkyu_flg[1]; 	/* �ً}�˗��׸�         */
	char	c_add_flg[1];		/* �ǉ��L���׸�         */
	char	c_hikensa_kbn[1];	/* �񌟍��敪           */
	char	c_uketuke_kbn[1];	/* ��t�敪             */
	char	c_ne_kbn[1];		/* NE�敪               */
	char	c_hifd_flg[1];		/* FD����׸�         */
	char	c_kakucho_flg[1];	/* �g������DB�����׸�   */
	char	c_uke_time[4];		/* ��t����             */
	char	c_ope_ymd[8];		/* �����N����           */
	char	c_obmluke_ymd[8];	/* ��BML��t�N����      */
	char	c_oirai_no[11];		/* ���˗���NO           */
	char	c_eigyo_cd[3];		/* �c�Ə�����           */
	char	c_syuhai_cd[2]; 	/* �W�z����             */
	char	c_siset_knm[40];	/* �{�ݖ��������́i�����j*/
	char	c_siset_nm[20];		/* �{�ݖ��������́i�Łj */
	char	c_sisetr_knm[20];	/* �{�ݖ����́i�����j   */
	char	c_sisetr_nm[10];	/* �{�ݖ����́i�Łj     */
	char	c_siset_kbn[2];		/* �{�ݎ��             */
	char	c_tokutei_flg[1];	/* ����{���׸�         */
	char	c_riyu_cd[1];		/* ���R����             */
	char	c_kmax[3]; 		/* �˗����ڐ�           */
	char	c_kjlab1_cd[3];		/* �������{��޺��ނP    */
	char	c_kjlab2_cd[3]; 	/* �������{��޺��ނQ    */
	char	c_kjlab3_cd[3];		/* �������{��޺��ނR    */
	char	c_hokoku_no[2]; 	/* ������NO           */
	char	c_yoyaku[12];		/* �\��̨����           */
	char	c_filler[478];		/* FILLER               */
	char	c_kaigyo[1];		/* ���s����             */
} my_stFileKanjya ;

typedef struct  _stDbKanjya {
	char	utkymd[10+1];		// 1 �a�l�k��t�N���� 
	char	irino[11+1];		// 2 �˗����m�� 
	char	iriketflg[1+1];		// 3 �˗����m�������t���O 
	short	zssdino;		// 4 ��������m�� 
	char	sstcd[7+1];		// 5 �{�݃R�[�h 
	char	subsstcd[4+1];		// 6 �T�u�{�݃R�[�h 
	char	cdkbn1[2+1];		// 7 �J�[�h�敪1 
	char	cdkbn2[2+1];		// 8 �J�[�h�敪2 
	char	irimkey[40+1];		// 9 �˗����L�[ 
	char	srkcd[3+1];		// 10 �f�ÉȃR�[�h 
	char	srknm[30+1];		// 11 �f�ÉȖ� 
	char	tticd[8+1];		// 12 �S����R�[�h 
	char	ttinm[40+1];		// 13 �S���㖼 
	char	gpcd[8+1];		// 14 �厡��R�[�h 
	char	gpnm[40+1];		// 15 �厡�㖼 
	char	skicd[8+1];		// 16 �Љ��R�[�h 
	char	skinm[40+1];		// 17 �Љ�㖼 
	char	krtno[40+1];		// 18 �J���e�m��          
	char	knjid[15+1];		// 19 ���҂h�c 
	char	knjnmn[60+1];		// 20 ���Җ��i�J�i�j 
	char	knjnmk[30+1];		// 21 ���Җ��i�����j 
	char	knjnmkey[60+1];		// 22 ���Җ��L�[ 
	char	sc[5+1];		// 23 �g��  
	char	tj[5+1];		// 24 �̏d  
	char	tjtni[1+1];		// 25 �̏d�敪 
	char	sbtkbn[1+1];		// 26 ���ʋ敪 
	char	birthday[8+1];		// 27 ���N����  
	char	birthdaykbn[1+1];	// 28 ���N�����敪 
	char	age[3+1];		// 29 �N��  
	char	agekbn[1+1];		// 30 �N��敪 
	char	btcd[10+1];		// 31 �a���R�[�h 
	char	btnm[30+1];		// 32 �a���� 
	char	utkcmtcd1[2+1];		// 33 ��t�R�����g1  
	char	utkcmtcd2[2+1];		// 34 ��t�R�����g2  
	char	utkcmtcd3[2+1];		// 35 ��t�R�����g3  
	char	utkcmtfr1[70+1];	// 36 ��t�R�����g�t���[1  
	char	utkcmtfr2[70+1];	// 37 ��t�R�����g�t���[2  
	char	utkcmtfrflg[1+1];	// 38 ��t�R�����g�t���[�t���O 
	char	ngkbn[1+1];		// 39 ���@�O���敪           
	char	nsssu[2+1];		// 40 �D�P�T��  
	char	hkncd[1+1];		// 41 �ی��R�[�h 
	char	ktshsu[2+1];		// 42 ���̑��{�� 
	char	iniriymd[10+1];		// 43 �@���˗��� 
	char	zssflg[1+1];		// 44 �����C���t���O 
	char	kkiriflg[1+1];		// 45 �ً}�˗��t���O 
	char	hknskbn[1+1];		// 46 �񌟍��敪 
	char	utkkbn[1+1];		// 47 ��t�敪 
	char	nekbn[1+1];		// 48 �m�d�敪 
	char	inknskbn[1+1];		// 49 �@�������敪 
	char	utkjkkbn[1+1];		// 50 ��t��ԋ敪 
	char	krflg[1+1];		// 51 �����t���O 
	char	fdhhkkflg[1+1];		// 52 �e�c��񍐃t���O 
	char	utkdh[8+1];		// 53 ��t���� 
	char	mutkymd[10+1];		// 54 ���a�l�k��t�� 
	char	mirino[11+1];		// 55 ���˗����m�� 
	char	knsjslbcd1[3+1];	// 56 �������{���{�R�[�h�P 
	char	knsjslbcd2[3+1];	// 57 �������{���{�R�[�h�Q 
	char	knsjslbcd3[3+1];	// 58 �������{���{�R�[�h�R 
	char	knsjslbcd4[3+1];	// 59 �������{���{�R�[�h�S 
	char	ymhkkflg[1+1];		// 60 �������񍐃t���O 
	char	hkkkbdh[8+1];		// 61 �񍐊�]���� 
	char	ecd[3+1];		// 62 �c�Ə��R�[�h 
	char	shcd[2+1];		// 63 �W�z�R�[�h 
	char	sstssnmj[40+1];		// 64 �{�ݖ��������� 
	char	sstssnmn[40+1];		// 65 �{�ݖ��������́i�J�i�j 
	char	sstrsj[20+1];		// 66 �{�ݖ����� 
	char	sstrsn[20+1];		// 67 �{�ݖ����́i�J�i�j 
	char	sstsbt[2+1];		// 68 �{�ݎ�� 
	char	ttsstflg[1+1];		// 69 ����{�݃t���O 
	char	rucd[2+1];		// 70 ���R�R�[�h 
	short	irikmksu;		// 71 �˗����ڐ� 
	char	bmskn[50+1];		// 72 �a���y�я��� 
	char	irinrsbt[2+1];		// 73 �˗����͎�� 
	char	irihsmkbn[1+1];		// 74 �˗��������敪 
	char	caresstflg[1+1];	// 75 ���ʒ��ӎ{�݃t���O 
	char	tktyflg[1+1];		// 76 �����g���t���O 
	char	apkntino[13+1];		// 77 AUTO-P���̂m�� 
	char	sdnm[20+1];		// 78 �f�f�� 
	char	bko1[20+1];		// 79 ���l�P 
	char	bko2[20+1];		// 80 ���l�Q 
	char	bko3[20+1];		// 81 ���l�R 
	char	zstrdh[26+1];		// 82 �����o�^���� 
	char	zsssdh[26+1];		// 83 �����C������ 
	char	stlzsssdh[26+1];	// 84 �T�e���C�g�������C������ 
	char	stlzsssip[15+1];	// 85 �T�e���C�g�������C���[��IP 
	char	stlzssssyaid[8+1];	// 86 �T�e���C�g�������C�����͎� 
	char	ksndh[26+1];		// 87 ���X�V���� 
	char	oyasstcd[7+1];		// 88 �e�{�݃R�[�h 
	char	trkdh[26+1];		// 89 �o�^���� 
} my_stDbKanjya ;

typedef struct _stCHKZOK
{
	char	utkymd[10+1];		// 1  �a�l�k��t�N����
	char	irino[11+1];		// 2  �˗����m��
	char	knsgrp[16+1];		// 3  �����O���[�v
	char	kmkcd[7+1];		// 4  ���ڃR�[�h
	char	sc[5+1];		// 10 �g��
	char	scflg[1+1];		// 11 �g�� �`�F�b�N�t���O
	char	tj[5+1];		// 12 �̏d
	char	tjflg[1+1];		// 13 �̏d  �`�F�b�N�t���O
	char	tjtni[1+1];		// 14 �̏d�敪
	char	tjtniflg[1+1];		// 15 �̏d�敪�`�F�b�N�t���O
	char	sbtkbn[1+1];		// 16 ���ʋ敪
	char	sbtkbnflg[1+1];		// 17 ���ʋ敪�`�F�b�N�t���O
	char	age[3+1];		// 18 �N��
	char	ageflg[1+1];		// 19 �N��`�F�b�N�t���O
	char	agekbn[1+1];		// 20 �N��敪
	char	agekbnflg[1+1];		// 21 �N��敪�`�F�b�N�t���O
} my_stCHKZOK ;

/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/******************************************************************************/
/* �v���g�^�C�v�錾                                                           */
/******************************************************************************/
void    sFncPutLog ( LOG_TRCKIND, char *, char *, int, char *, char *, char *, ... )  ;
int	EditPncKanjya( my_stFileKanjya *, my_stDbKanjya * ) ;
int     EditCommonKanjya( my_stDbKanjya * ) ;
int	NameKeyMake( char *, char *, int len ) ;
int	isCorrectChar( char * ) ;
int	ValidDate( int, char * ) ;
int	wa2ymd( char *, char  * , char * );                                          
void	sFncTrim( char *, char * );
#endif
/** End of File ***************************************************************/
