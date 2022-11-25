static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,104,66,97,69,85,87,67,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,68,49,48,51,95,68,66,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "AD103_db.sqc"
/*****************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FAD103_db.sqc                                                 */
/*   �T      �v�F�c�a�A�N�Z�X                                                 */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�e�{��,�o�^����)�Ή� */
/*  1.03     2006/06/10     INTEC.INC      ���ґ����C�����˗���񐢑�No�X�V   */
/*  1.04     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή�*/
/*                                         SelKanjya�֐��ǉ�/DelKanjya�֐��ǉ�*/
/*                                         InsShusei_Kanjya�֐��ǉ�           */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"AD103.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 30 "AD103_db.sqc"


/*
EXEC SQL INCLUDE 'tagAD103.h';
*/

#line 1 "/home/kea00sys/appl/src/irai/AD103/tagAD103.h"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FtagAD103.h                                                   */
/*   �T      �v�F���ҏ��e�[�u���\���̒�`                                   */
/*   ���L����  �FDB2�̃z�X�g�ϐ��ɂ��g�p���邽��typedef�g�p�s��               */
/*               �܂�struct�̍Ō�ŕϐ�����錾���邱��                       */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      SJIS,���ڒǉ�(�e�{��,�o�^����)�Ή� *
/******************************************************************************/
#ifndef _TAGAD103_H
#define _TAGAD103_H

/******************************************************************************/
/* �f�[�^�\���̒�`                                                           */
/******************************************************************************/
// <<   ���ҏ��e�[�u��      >>
struct	_KANJYA {
	char	utkymd[10+1];		// 1 �a�l�k��t�N���� 
	char	irino[11+1];		// 2 �˗����m�� 
	char	iriketflg[1+1];		// 3 �˗����m�������t���O 
	short	zssdino;			// 4 ��������m�� 
	char	sstcd[7+1];			// 5 �{�݃R�[�h 
	char	subsstcd[4+1];		// 6 �T�u�{�݃R�[�h 
	char	cdkbn1[2+1];		// 7 �J�[�h�敪1 
	char	cdkbn2[2+1];		// 8 �J�[�h�敪2 
	char	irimkey[40+1];		// 9 �˗����L�[ 
	char	srkcd[3+1];			// 10 �f�ÉȃR�[�h 
	char	srknm[30+1];		// 11 �f�ÉȖ� 
	char	tticd[8+1];			// 12 �S����R�[�h 
	char	ttinm[40+1];		// 13 �S���㖼 
	char	gpcd[8+1];			// 14 �厡��R�[�h 
	char	gpnm[40+1];			// 15 �厡�㖼 
	char	skicd[8+1];			// 16 �Љ��R�[�h 
	char	skinm[40+1];		// 17 �Љ�㖼 
	char	krtno[40+1];		// 18 �J���e�m��          
	char	knjid[15+1];		// 19 ���҂h�c 
	char	knjnmn[60+1];		// 20 ���Җ��i�J�i�j 
	char	knjnmk[30+1];		// 21 ���Җ��i�����j 
	char	knjnmkey[60+1];		// 22 ���Җ��L�[ 
	char	sc[5+1];			// 23 �g��  
	char	tj[5+1];			// 24 �̏d  
	char	tjtni[1+1];			// 25 �̏d�敪 
	char	sbtkbn[1+1];		// 26 ���ʋ敪 
	char	birthday[8+1];		// 27 ���N����  
	char	birthdaykbn[1+1];	// 28 ���N�����敪 
	char	age[3+1];			// 29 �N��  
	char	agekbn[1+1];		// 30 �N��敪 
	char	btcd[10+1];			// 31 �a���R�[�h 
	char	btnm[30+1];			// 32 �a���� 
	char	utkcmtcd1[2+1];		// 33 ��t�R�����g1  
	char	utkcmtcd2[2+1];		// 34 ��t�R�����g2  
	char	utkcmtcd3[2+1];		// 35 ��t�R�����g3  
	char	utkcmtfr1[70+1];	// 36 ��t�R�����g�t���[1  
	char	utkcmtfr2[70+1];	// 37 ��t�R�����g�t���[2  
	char	utkcmtfrflg[1+1];	// 38 ��t�R�����g�t���[�t���O 
	char	ngkbn[1+1];			// 39 ���@�O���敪           
	char	nsssu[2+1];			// 40 �D�P�T��  
	char	hkncd[1+1];			// 41 �ی��R�[�h 
	char	ktshsu[2+1];		// 42 ���̑��{�� 
	char	iniriymd[10+1];		// 43 �@���˗��� 
	char	zssflg[1+1];		// 44 �����C���t���O 
	char	kkiriflg[1+1];		// 45 �ً}�˗��t���O 
	char	hknskbn[1+1];		// 46 �񌟍��敪 
	char	utkkbn[1+1];		// 47 ��t�敪 
	char	nekbn[1+1];			// 48 �m�d�敪 
	char	inknskbn[1+1];		// 49 �@�������敪 
	char	utkjkkbn[1+1];		// 50 ��t��ԋ敪 
	char	krflg[1+1];			// 51 �����t���O 
	char	fdhhkkflg[1+1];		// 52 �e�c��񍐃t���O 
	char	utkdh[8+1];			// 53 ��t���� 
	char	mutkymd[10+1];		// 54 ���a�l�k��t�� 
	char	mirino[11+1];		// 55 ���˗����m�� 
	char	knsjslbcd1[3+1];	// 56 �������{���{�R�[�h�P 
	char	knsjslbcd2[3+1];	// 57 �������{���{�R�[�h�Q 
	char	knsjslbcd3[3+1];	// 58 �������{���{�R�[�h�R 
	char	knsjslbcd4[3+1];	// 59 �������{���{�R�[�h�S 
	char	ymhkkflg[1+1];		// 60 �������񍐃t���O 
	char	hkkkbdh[8+1];		// 61 �񍐊�]���� 
	char	ecd[3+1];			// 62 �c�Ə��R�[�h 
	char	shcd[2+1];			// 63 �W�z�R�[�h 
	char	sstssnmj[40+1];		// 64 �{�ݖ��������� 
	char	sstssnmn[40+1];		// 65 �{�ݖ��������́i�J�i�j 
	char	sstrsj[20+1];		// 66 �{�ݖ����� 
	char	sstrsn[20+1];		// 67 �{�ݖ����́i�J�i�j 
	char	sstsbt[2+1];		// 68 �{�ݎ�� 
	char	ttsstflg[1+1];		// 69 ����{�݃t���O 
	char	rucd[2+1];			// 70 ���R�R�[�h 
	short	irikmksu;			// 71 �˗����ڐ� 
	char	bmskn[50+1];		// 72 �a���y�я��� 
	char	irinrsbt[2+1];		// 73 �˗����͎�� 
	char	irihsmkbn[1+1];		// 74 �˗��������敪 
	char	caresstflg[1+1];	// 75 ���ʒ��ӎ{�݃t���O 
	char	tktyflg[1+1];		// 76 �����g���t���O 
	char	apkntino[13+1];		// 77 AUTO-P���̂m�� 
	char	sdnm[20+1];			// 78 �f�f�� 
	char	bko1[20+1];			// 79 ���l�P 
	char	bko2[20+1];			// 80 ���l�Q 
	char	bko3[20+1];			// 81 ���l�R 
	char	zstrdh[26+1];		// 82 �����o�^���� 
	char	zsssdh[26+1];		// 83 �����C������ 
	char	stlzsssdh[26+1];	// 84 �T�e���C�g�������C������ 
	char	stlzsssip[15+1];	// 85 �T�e���C�g�������C���[��IP 
	char	stlzssssyaid[8+1];	// 86 �T�e���C�g�������C�����͎� 
	char	ksndh[26+1];		// 87 ���X�V���� 
	char	oyasstcd[7+1];		// 1.01 ADD	88 �e�{�݃R�[�h 
	char	trkdh[26+1];		// 1.01 ADD	89 �o�^���� 
} hkanjya;	

// <<   �����g�������e�[�u��      >>
struct	_CHIKENZOK {
	char	utkymd[10+1];		// 1 �a�l�k��t�N���� 
	char	irino[11+1];		// 2 �˗����m�� 
	char	iriketflg[1+1];		// 3 �˗����m�������t���O 
	short	zssdino;			// 4 ��������m�� 
	char	prtclno[11+1];		// 5 �����E�v���g�R���m�� 
	char	kosstcd[7+1];		// 6 �����E�q�{�݃R�[�h  
	char	tytme[4+1];			// 7 �����E���^����  
	char	tyryo[5+1];			// 8 �����E���^��(��) 
	char	tyryotni[3+1];		// 9 �����E���^��(�P��) 
	char	yzfktme[4+1];		// 10 �����E��ܕ��׎��� 
	char	ikasflg[1+1];		// 11 �����E�ꊇ�A�b�Z�C�t���O 
	short	kntsu;				// 12 �����E���̐� 
	short	kmksu;				// 13 �����E���ڐ� 
	char	sspit[2+1];			// 14 �����E�̎�|�C���g 
	char	zrcd01[5+1];		// 15 �����E�ޗ��R�[�h�P 
	char	zrcd02[5+1];		// 16 �����E�ޗ��R�[�h�Q 
	char	zrcd03[5+1];		// 17 �����E�ޗ��R�[�h�R 
	char	zrcd04[5+1];		// 18 �����E�ޗ��R�[�h�S 
	char	zrcd05[5+1];		// 19 �����E�ޗ��R�[�h�T 
	char	zrcd06[5+1];		// 20 �����E�ޗ��R�[�h�U 
	char	zrkg01[2+1];		// 21 �����E�ޗ��L���P 
	char	zrkg02[2+1];		// 22 �����E�ޗ��L���Q 
	char	zrkg03[2+1];		// 23 �����E�ޗ��L���R 
	char	zrkg04[2+1];		// 24 �����E�ޗ��L���S 
	char	zrkg05[2+1];		// 25 �����E�ޗ��L���T 
	char	zrkg06[2+1];		// 26 �����E�ޗ��L���U 
	char	hrseq[4+1];			// 27 �����E�ۗ��V�[�P���X 
	char	kntksflg[1+1];		// 28 �����E���̉���t���O 
	char	gcpflg[1+1];		// 29 �����E�f�b�o�t���O 
	char	prtclnm[40+1];		// 30 �����E�v���g�R������ 
	char	ksndh[26+1];		// 31 ���X�V���� 
} hchikenzok;	

/******************************************************************************/
/* �}�X�^�\���̒�`                                                           */
/******************************************************************************/
// <<   �V�X�e���Ǘ��}�X�^     >>
struct	_SYSKNRMST {
	char	kjnsriymd[11];		// ������N����
	char	nxirisriymd[11];	// ���˗������N����
	char	iriendflg[2];		// �˗�END�t���O
} hsysknrmst;	


// <<   �c�Ə��}�X�^     >>
struct	_EIGMST {
	char	ecd[4];
	char	shcdfr[3];
	char	shcdto[3];
	char	yjhkkbn[2];
	char	kaiymd[11];
	char	haiymd[11];
} heigmst;	

#endif

#line 31 "AD103_db.sqc"

	char		hst_ymd[11];
	char		hst_utkymd[10+1]; 
    char    	hst_irino[11+1];
	sqlint32	hst_zssdino;
	short		ind_zssdino;
	sqlint32	hst_cnt;
	short		ind_cnt;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "AD103_db.sqc"


/******************************************************************************/
/*  �� �� ��  �FSelSysknrmst                                                  */
/*  �@�\�T�v  �F�V�X�e���Ǘ��}�X�^ SELECT                                     */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _SYSKNRMST *knr;   : �V�X�e���Ǘ��}�X�^               */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelSysknrmst( knr )
struct		_SYSKNRMST	*knr;
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelSysknrmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hsysknrmst,	'\0',	sizeof( struct _SYSKNRMST ));


/*
EXEC SQL SELECT	
		 	kjnsriymd
			, nxirisriymd
			, iriendflg
	INTO	:hsysknrmst.kjnsriymd
			, :hsysknrmst.nxirisriymd
			, :hsysknrmst.iriendflg
	FROM	sysknrmst
	;
*/

{
#line 72 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 72 "AD103_db.sqc"
  sqlaaloc(3,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 72 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 72 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hsysknrmst.kjnsriymd;
#line 72 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 72 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 72 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hsysknrmst.nxirisriymd;
#line 72 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 72 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 72 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hsysknrmst.iriendflg;
#line 72 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 72 "AD103_db.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 72 "AD103_db.sqc"
  sqlacall((unsigned short)24,1,0,3,0L);
#line 72 "AD103_db.sqc"
  sqlastop(0L);
}

#line 72 "AD103_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
    /* many rows --> ERROR!!         SQLSTATE == '21000' */
    /* duplicate --> SQLCODE = -803                      */
    /* dead lock --> SQLCODE = -911, SQLERRD[2]== 2      */
    /* time out  --> SQLCODE = -911, SQLERRD[2]== 68     */

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT kjnsriymd FROM sysknrmst" );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		memcpy( knr, &hsysknrmst, sizeof( struct _SYSKNRMST ));
		ret = RTN_OK;
	} else if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
		/* SQLCODE +100, SQLSTATE '02000' */
		sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd)�����݂��܂���B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			
		ret=RTN_ZERO;
	} else {
		if( sqlca.sqlcode == -911 ){        // LOCK
			switch( sqlca.sqlerrd[2] ){
			case     2 :
				strcpy( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
					"DEAD LOCK ���������܂����B" );
				break;
			case    68 :
				strcpy( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
					"TIMETOUT ���������܂����B" );
				break;
			default :
				sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
					"�s����������܂����B" );
				break;
			}
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "�V�X�e���Ǘ��}�X�^(kjnsriymd) SELECT ��"
				"�s����������܂����B" );
		}
		ret=RTN_DBERR;
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}


/*
EXEC SQL COMMIT;
*/

{
#line 126 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 126 "AD103_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 126 "AD103_db.sqc"
  sqlastop(0L);
}

#line 126 "AD103_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelEigmst                                                     */
/*  �@�\�T�v  �F�c�Ə��}�X�^ SELECT                                           */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _EIGMST    *egm;   : �c�Ə��}�X�^                     */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelEigmst( egm )
struct		_EIGMST		*egm;			/* �c�Ə��}�X�^ */
{

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 144 "AD103_db.sqc"

	char		hst_shcd[3];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 146 "AD103_db.sqc"

	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelEigmst" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &heigmst,		'\0', sizeof( struct _EIGMST ));
	strcpy( heigmst.ecd,	egm->ecd );
	strcpy( hst_shcd,		egm->shcdfr );
	strcpy( hst_ymd,		egm->kaiymd );


/*
EXEC SQL SELECT	
			  shcdfr
			, shcdto
			, yjhkkbn
			, kaiymd
			, haiymd
	INTO	  :heigmst.shcdfr
		  	, :heigmst.shcdto
		  	, :heigmst.yjhkkbn
			, :heigmst.kaiymd
			, :heigmst.haiymd
	FROM	eigmst
	WHERE	ecd		=  :heigmst.ecd
	AND		shcdfr	<= :hst_shcd
	AND		shcdto	>= :hst_shcd
	AND		kaiymd	<= :hst_ymd
	AND		haiymd	>= :hst_ymd
	;
*/

{
#line 178 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "AD103_db.sqc"
  sqlaaloc(2,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)heigmst.ecd;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_shcd;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_shcd;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hst_ymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hst_ymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 178 "AD103_db.sqc"
  sqlaaloc(3,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)heigmst.shcdfr;
#line 178 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)heigmst.shcdto;
#line 178 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)heigmst.yjhkkbn;
#line 178 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)heigmst.kaiymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)heigmst.haiymd;
#line 178 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "AD103_db.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 178 "AD103_db.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 178 "AD103_db.sqc"
  sqlastop(0L);
}

#line 178 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT eigmst : ecd[%s]shcd[%s]ymd[%s]",
		egm->ecd, egm->shcdfr, egm->kaiymd );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		memcpy( egm, &heigmst,	sizeof( struct _EIGMST ));
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			/* SQLCODE +100, SQLSTATE '02000' */
			sprintf( G_msg,
				"�c�Ə��}�X�^�����݂��܂���B�c�Ə�[%s]�W�z[%s]���[%s]"
				,egm->ecd, egm->shcdfr, egm->kaiymd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

			ret=RTN_ZERO;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"�c�ƃ}�X�^ SELECT �ŕs����������܂����B"
				"�c�Ə�[%s]�W�z[%s]���[%s]"
				,egm->ecd, egm->shcdfr, egm->kaiymd );
			EditCsvMsg( G_msg );
			LogOut( LT_WRN, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			 
			ret=RTN_DBERR;
		}
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FInsKanjya                                                     */
/*  �@�\�T�v  �F���������@INSERT                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA     *zok;   : ���ҏ��                        */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		InsKanjya( kan )
struct		_KANJYA	*kan;			/* �����f�[�^ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int	ret;

	/* ��������	*/
	strcpy(func_nm, "InsKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃Z�b�g	*/
	memcpy( &hkanjya, kan, sizeof( struct _KANJYA ));


/*
EXEC SQL INSERT	INTO	kanjya
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, sstcd
		, subsstcd
		, cdkbn1
		, cdkbn2
		, irimkey
		, srkcd
		, srknm
		, tticd
		, ttinm
		, gpcd
		, gpnm
		, skicd
		, skinm
		, krtno
		, knjid
		, knjnmn
		, knjnmk
		, knjnmkey
		, sc
		, tj
		, tjtni
		, sbtkbn
		, birthday
		, birthdaykbn
		, age
		, agekbn
		, btcd
		, btnm
		, utkcmtcd1
		, utkcmtcd2
		, utkcmtcd3
		, utkcmtfr1
		, utkcmtfr2
		, utkcmtfrflg
		, ngkbn
		, nsssu
		, hkncd
		, ktshsu
		, iniriymd
		, zssflg
		, kkiriflg
		, hknskbn
		, utkkbn
		, nekbn
		, inknskbn
		, utkjkkbn
		, krflg
		, fdhhkkflg
		, utkdh
		, mutkymd
		, mirino
		, knsjslbcd1
		, knsjslbcd2
		, knsjslbcd3
		, knsjslbcd4
		, ymhkkflg
		, hkkkbdh
		, ecd
		, shcd
		, sstssnmj
		, sstssnmn
		, sstrsj
		, sstrsn
		, sstsbt
		, ttsstflg
		, rucd
		, irikmksu
		, bmskn
		, irinrsbt
		, irihsmkbn
		, caresstflg
		, tktyflg
		, apkntino
		, sdnm
		, bko1
		, bko2
		, bko3
		, zstrdh
		, zsssdh
		, stlzsssdh
		, stlzsssip
		, stlzssssyaid
		, ksndh
		, oyasstcd				-- 1.01 ADD
		, trkdh					-- 1.01 ADD
		)
	VALUES	( :hkanjya.utkymd
		, :hkanjya.irino
		, :hkanjya.iriketflg
		, :hkanjya.zssdino
		, :hkanjya.sstcd
		, :hkanjya.subsstcd
		, :hkanjya.cdkbn1
		, :hkanjya.cdkbn2
		, :hkanjya.irimkey
		, :hkanjya.srkcd
		, :hkanjya.srknm
		, :hkanjya.tticd
		, :hkanjya.ttinm
		, :hkanjya.gpcd
		, :hkanjya.gpnm
		, :hkanjya.skicd
		, :hkanjya.skinm
		, :hkanjya.krtno
		, :hkanjya.knjid
		, :hkanjya.knjnmn
		, :hkanjya.knjnmk
		, :hkanjya.knjnmkey
		, :hkanjya.sc
		, :hkanjya.tj
		, :hkanjya.tjtni
		, :hkanjya.sbtkbn
		, :hkanjya.birthday
		, :hkanjya.birthdaykbn
		, :hkanjya.age
		, :hkanjya.agekbn
		, :hkanjya.btcd
		, :hkanjya.btnm
		, :hkanjya.utkcmtcd1
		, :hkanjya.utkcmtcd2
		, :hkanjya.utkcmtcd3
		, :hkanjya.utkcmtfr1
		, :hkanjya.utkcmtfr2
		, :hkanjya.utkcmtfrflg
		, :hkanjya.ngkbn
		, :hkanjya.nsssu
		, :hkanjya.hkncd
		, :hkanjya.ktshsu
		, :hkanjya.iniriymd
		, :hkanjya.zssflg
		, :hkanjya.kkiriflg
		, :hkanjya.hknskbn
		, :hkanjya.utkkbn
		, :hkanjya.nekbn
		, :hkanjya.inknskbn
		, :hkanjya.utkjkkbn
		, :hkanjya.krflg
		, :hkanjya.fdhhkkflg
		, :hkanjya.utkdh
		, :hkanjya.mutkymd
		, :hkanjya.mirino
		, :hkanjya.knsjslbcd1
		, :hkanjya.knsjslbcd2
		, :hkanjya.knsjslbcd3
		, :hkanjya.knsjslbcd4
		, :hkanjya.ymhkkflg
		, :hkanjya.hkkkbdh
		, :hkanjya.ecd
		, :hkanjya.shcd
		, :hkanjya.sstssnmj
		, :hkanjya.sstssnmn
		, :hkanjya.sstrsj
		, :hkanjya.sstrsn
		, :hkanjya.sstsbt
		, :hkanjya.ttsstflg
		, :hkanjya.rucd
		, :hkanjya.irikmksu
		, :hkanjya.bmskn
		, :hkanjya.irinrsbt
		, :hkanjya.irihsmkbn
		, :hkanjya.caresstflg
		, :hkanjya.tktyflg
		, :hkanjya.apkntino
		, :hkanjya.sdnm
		, :hkanjya.bko1
		, :hkanjya.bko2
		, :hkanjya.bko3
		, :hkanjya.zstrdh
		, :hkanjya.zsssdh
		, :hkanjya.stlzsssdh
		, :hkanjya.stlzsssip
		, :hkanjya.stlzssssyaid
		, CURRENT TIMESTAMP
		, :hkanjya.oyasstcd				-- 1.01 ADD
		, CURRENT TIMESTAMP				-- 1.01 ADD
		)
	;
*/

{
#line 424 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 424 "AD103_db.sqc"
  sqlaaloc(2,87,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 424 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 424 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 424 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 424 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 424 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 424 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 424 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 424 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 424 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 424 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 424 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 424 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 424 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 424 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 424 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 424 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 424 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 424 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 424 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 424 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 424 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 424 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 424 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 424 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 424 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 424 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 424 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 424 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 424 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 424 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 424 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 424 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 424 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 424 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 424 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 424 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 424 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 424 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 424 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 424 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 424 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 424 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 424 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 424 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 424 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 424 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 424 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 8;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.oyasstcd;
#line 424 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 424 "AD103_db.sqc"
      sqlasetdata(2,64,23,sql_setdlist,0L,0L);
    }
#line 424 "AD103_db.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 424 "AD103_db.sqc"
  sqlastop(0L);
}

#line 424 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {	// duplicate
			sprintf( G_msg,
				"���ҏ��(kanjya)�͊��ɑ��݂��Ă��܂��B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
			/* ERROR */
			ret=MYAPP_RTN_DUP;
		} else {
			sprintf( G_msg,
				"���ҏ��(kanjya)�� INSERT �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
			/* ERROR */
			ret=RTN_DBERR;
		}
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelKanjyaZssdinoMax                                           */
/*  �@�\�T�v  �F���ҏ��D��������NO�@MAX�擾                                 */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �F�ȊO         �ُ�I��                                         */
/******************************************************************************/
int		SelKanjyaZssdinoMax( kan )
struct		_KANJYA		*kan;			// ���ҏ��
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelKanjyaZssdinoMax" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memcpy( &hkanjya, kan, sizeof( struct _KANJYA ));
	hst_zssdino=0;
	ind_zssdino=0;


/*
EXEC SQL SELECT	MAX( zssdino )
	INTO	  :hst_zssdino	INDICATOR :ind_zssdino
	FROM	kanjya
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	;
*/

{
#line 491 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 491 "AD103_db.sqc"
  sqlaaloc(2,2,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 491 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 491 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 491 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 491 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 491 "AD103_db.sqc"
  sqlaaloc(3,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_zssdino;
#line 491 "AD103_db.sqc"
      sql_setdlist[0].sqlind = &ind_zssdino;
#line 491 "AD103_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 491 "AD103_db.sqc"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 491 "AD103_db.sqc"
  sqlastop(0L);
}

#line 491 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT MAX(zssdino) FROM kanjya : "
		"utkymd[%s]irino[%s] indicator[%d] sqlcode[%s]",
		kan->utkymd, kan->irino, ind_zssdino, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// �W���ϐ��ɂ�锻�f
		// sqlcode=0 indicator=0  -> FOUND
		// sqlcode=0 indicator=-1 -> NOT FOUND
		// sqlcode<>0 -> DB ERROR
	if (sqlca.sqlcode == 0) {		/* OK */
		if( ind_zssdino == 0 ) {
			kan->zssdino=hst_zssdino;
			ret = RTN_OK;
		} else if( ind_zssdino == -1 ){	/* NOT FOUND */
			kan->zssdino=0;
			ret = RTN_ZERO;
		}
	} else {
		sprintf( G_msg,
			"�C���Ώۂ̊��ҏ��(kanjya)��MAX( ��������NO )�擾�Ɏ��s���܂����B"
			"BML��t�N����[%s]�˗���NO[%s] SELECT INDICATOR[%d]"
			,kan->utkymd, kan->irino, ind_zssdino );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		kan->zssdino=0;
		ret=RTN_NG;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FUpdKanjyaTktyflg                                              */
/*  �@�\�T�v  �F���ҏ��.�����g���t���O UPDATE                                */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/*  ���L����  �FINSERT �Ɓ@����transaction����update�̂���select���Ȃ�        */
/******************************************************************************/
int		UpdKanjyaTktyflg( kan )
struct		_KANJYA		*kan;			/* ���ҏ�� */
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];				/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "UpdKanjyaTktyflg" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memcpy( &hkanjya, kan, sizeof( struct _KANJYA ));


/*
EXEC SQL UPDATE	kanjya	
	SET		tktyflg = '1'
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	AND		zssdino	= :hkanjya.zssdino
	;
*/

{
#line 559 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 559 "AD103_db.sqc"
  sqlaaloc(2,3,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 559 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 559 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 559 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 559 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 559 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 559 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 559 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 559 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)&hkanjya.zssdino;
#line 559 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 559 "AD103_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 559 "AD103_db.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 559 "AD103_db.sqc"
  sqlastop(0L);
}

#line 559 "AD103_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "UPDATE kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
		/* SQLCODE > 0 -> WARNING */
		/* SQLCODE < 0 -> ERROR */
		sprintf( G_msg,
			"���ҏ��(kanjya)�� UPDATE �Ɏ��s���܂����B"
			"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
			,kan->utkymd, kan->irino, kan->zssdino );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_DBERR;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FUpdKinkyuKanjya                                               */
/*  �@�\�T�v  �FAS400����˗��Ή��@���ҏ�� UPDATE                            */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		UpdKinkyuKanjya( kan )
struct		_KANJYA		*kan;			/* ���ҏ�� */
{
	int		ret;
	char	func_nm[30];				/* �֐�����	*/
	char	wbuf[30];					// 1.01 �o�^�����ޔ�p
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "UpdKinkyuKanjya" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hkanjya, '\0', sizeof( struct _KANJYA ));
	strcpy( hkanjya.utkymd,	kan->utkymd );
	strcpy( hkanjya.irino,	kan->irino );
	hkanjya.zssdino=kan->zssdino;

// ----- SELECT  ------------------------------------------------------------
	// �Ώۃf�[�^��SELECT

/*
EXEC SQL SELECT	* INTO
		  :hkanjya.utkymd
		, :hkanjya.irino
		, :hkanjya.iriketflg
		, :hkanjya.zssdino
		, :hkanjya.sstcd
		, :hkanjya.subsstcd
		, :hkanjya.cdkbn1
		, :hkanjya.cdkbn2
		, :hkanjya.irimkey
		, :hkanjya.srkcd
		, :hkanjya.srknm
		, :hkanjya.tticd
		, :hkanjya.ttinm
		, :hkanjya.gpcd
		, :hkanjya.gpnm
		, :hkanjya.skicd
		, :hkanjya.skinm
		, :hkanjya.krtno
		, :hkanjya.knjid
		, :hkanjya.knjnmn
		, :hkanjya.knjnmk
		, :hkanjya.knjnmkey
		, :hkanjya.sc
		, :hkanjya.tj
		, :hkanjya.tjtni
		, :hkanjya.sbtkbn
		, :hkanjya.birthday
		, :hkanjya.birthdaykbn
		, :hkanjya.age
		, :hkanjya.agekbn
		, :hkanjya.btcd
		, :hkanjya.btnm
		, :hkanjya.utkcmtcd1
		, :hkanjya.utkcmtcd2
		, :hkanjya.utkcmtcd3
		, :hkanjya.utkcmtfr1
		, :hkanjya.utkcmtfr2
		, :hkanjya.utkcmtfrflg
		, :hkanjya.ngkbn
		, :hkanjya.nsssu
		, :hkanjya.hkncd
		, :hkanjya.ktshsu
		, :hkanjya.iniriymd
		, :hkanjya.zssflg
		, :hkanjya.kkiriflg
		, :hkanjya.hknskbn
		, :hkanjya.utkkbn
		, :hkanjya.nekbn
		, :hkanjya.inknskbn
		, :hkanjya.utkjkkbn
		, :hkanjya.krflg
		, :hkanjya.fdhhkkflg
		, :hkanjya.utkdh
		, :hkanjya.mutkymd
		, :hkanjya.mirino
		, :hkanjya.knsjslbcd1
		, :hkanjya.knsjslbcd2
		, :hkanjya.knsjslbcd3
		, :hkanjya.knsjslbcd4
		, :hkanjya.ymhkkflg
		, :hkanjya.hkkkbdh
		, :hkanjya.ecd
		, :hkanjya.shcd
		, :hkanjya.sstssnmj
		, :hkanjya.sstssnmn
		, :hkanjya.sstrsj
		, :hkanjya.sstrsn
		, :hkanjya.sstsbt
		, :hkanjya.ttsstflg
		, :hkanjya.rucd
		, :hkanjya.irikmksu
		, :hkanjya.bmskn
		, :hkanjya.irinrsbt
		, :hkanjya.irihsmkbn
		, :hkanjya.caresstflg
		, :hkanjya.tktyflg
		, :hkanjya.apkntino
		, :hkanjya.sdnm
		, :hkanjya.bko1
		, :hkanjya.bko2
		, :hkanjya.bko3
		, :hkanjya.zstrdh
		, :hkanjya.zsssdh
		, :hkanjya.stlzsssdh
		, :hkanjya.stlzsssip
		, :hkanjya.stlzssssyaid
		, :hkanjya.ksndh
		, :hkanjya.oyasstcd				-- 1.01 ADD
		, :hkanjya.trkdh				-- 1.01 ADD
	FROM	kanjya
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	AND		zssdino	= :hkanjya.zssdino
	;
*/

{
#line 715 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 715 "AD103_db.sqc"
  sqlaaloc(2,3,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)&hkanjya.zssdino;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 715 "AD103_db.sqc"
  sqlaaloc(3,89,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 715 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 715 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 715 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 715 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 715 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 715 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 715 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 715 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 715 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 715 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 715 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 715 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 715 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 715 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 715 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 715 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 715 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 715 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 715 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 715 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 715 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 715 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 715 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 715 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 715 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 715 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 715 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 715 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 715 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 715 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 715 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 715 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 715 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 715 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 715 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 715 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 715 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 715 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 715 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 715 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 715 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 715 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.ksndh;
#line 715 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.oyasstcd;
#line 715 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.trkdh;
#line 715 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 715 "AD103_db.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 715 "AD103_db.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 715 "AD103_db.sqc"
  sqlastop(0L);
}

#line 715 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT * FROM kanjya before update: "
		"utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if ( sqlca.sqlcode == 0 ) {		/* OK */
		// �X�V�O����LOG�o��
		EditCsvKanjya( &hkanjya );
		LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	} else {
		if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			/* SQLCODE +100, SQLSTATE '02000' */
			sprintf( G_msg, "�X�V�Ώۂ̊��ҏ��(kanjya)�����݂��܂���B" );
			// NOT FOUND
			ret=RTN_ZERO;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "�X�V�Ώۂ̊��ҏ��(kanjya) SELECT ��"
				"�s����������܂����B" );
			ret=RTN_DBERR;
		}
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	/* �z�X�g�ϐ��Z�b�g	*/
		// 1.01 ADD �o�^�����͍X�V�O�̒l�������p��
	strcpy( wbuf,			hkanjya.trkdh );
	memcpy( &hkanjya, kan,	sizeof( struct _KANJYA ));
	strcpy( hkanjya.trkdh,	wbuf );				// 1.01 ADD
	if( stcPRM.myp_debug == 1 ){
		zoku_pr( &hkanjya );
	}

// ----- UPDATE ------------------------------------------------------------

/*
EXEC SQL UPDATE	kanjya	
	SET	  iriketflg	= :hkanjya.iriketflg
		, sstcd		= :hkanjya.sstcd
		, subsstcd	= :hkanjya.subsstcd
		, cdkbn1	= :hkanjya.cdkbn1
		, cdkbn2	= :hkanjya.cdkbn2
		, irimkey	= :hkanjya.irimkey
		, srkcd		= :hkanjya.srkcd
		, srknm		= :hkanjya.srknm
		, tticd		= :hkanjya.tticd
		, ttinm		= :hkanjya.ttinm
		, gpcd		= :hkanjya.gpcd
		, gpnm		= :hkanjya.gpnm
		, skicd		= :hkanjya.skicd
		, skinm		= :hkanjya.skinm
		, krtno		= :hkanjya.krtno
		, knjid		= :hkanjya.knjid
		, knjnmn	= :hkanjya.knjnmn
		, knjnmk	= :hkanjya.knjnmk
		, knjnmkey	= :hkanjya.knjnmkey
		, sc		= :hkanjya.sc
		, tj		= :hkanjya.tj
		, tjtni		= :hkanjya.tjtni
		, sbtkbn	= :hkanjya.sbtkbn
		, birthday	= :hkanjya.birthday
		, birthdaykbn	= :hkanjya.birthdaykbn
		, age		= :hkanjya.age
		, agekbn	= :hkanjya.agekbn
		, btcd		= :hkanjya.btcd
		, btnm		= :hkanjya.btnm
		, utkcmtcd1	= :hkanjya.utkcmtcd1
		, utkcmtcd2	= :hkanjya.utkcmtcd2
		, utkcmtcd3	= :hkanjya.utkcmtcd3
		, utkcmtfr1	= :hkanjya.utkcmtfr1
		, utkcmtfr2	= :hkanjya.utkcmtfr2
		, utkcmtfrflg	= :hkanjya.utkcmtfrflg
		, ngkbn		= :hkanjya.ngkbn
		, nsssu		= :hkanjya.nsssu
		, hkncd		= :hkanjya.hkncd
		, ktshsu	= :hkanjya.ktshsu
		, iniriymd	= :hkanjya.iniriymd
		, zssflg	= :hkanjya.zssflg
		, kkiriflg	= :hkanjya.kkiriflg
		, hknskbn	= :hkanjya.hknskbn
		, utkkbn	= :hkanjya.utkkbn
		, nekbn		= :hkanjya.nekbn
		, inknskbn	= :hkanjya.inknskbn
		, utkjkkbn	= :hkanjya.utkjkkbn
		, krflg		= :hkanjya.krflg
		, fdhhkkflg	= :hkanjya.fdhhkkflg
		, utkdh		= :hkanjya.utkdh
		, mutkymd	= :hkanjya.mutkymd
		, mirino	= :hkanjya.mirino
		, knsjslbcd1= :hkanjya.knsjslbcd1
		, knsjslbcd2= :hkanjya.knsjslbcd2
		, knsjslbcd3= :hkanjya.knsjslbcd3
		, knsjslbcd4= :hkanjya.knsjslbcd4
		, ymhkkflg	= :hkanjya.ymhkkflg
		, hkkkbdh	= :hkanjya.hkkkbdh
		, ecd		= :hkanjya.ecd
		, shcd		= :hkanjya.shcd
		, sstssnmj	= :hkanjya.sstssnmj
		, sstssnmn	= :hkanjya.sstssnmn
		, sstrsj	= :hkanjya.sstrsj
		, sstrsn	= :hkanjya.sstrsn
		, sstsbt	= :hkanjya.sstsbt
		, ttsstflg	= :hkanjya.ttsstflg
		, rucd		= :hkanjya.rucd
		, irikmksu	= :hkanjya.irikmksu
		, bmskn		= :hkanjya.bmskn
		, irinrsbt	= :hkanjya.irinrsbt
		, irihsmkbn	= :hkanjya.irihsmkbn
		, caresstflg= :hkanjya.caresstflg
		, tktyflg	= :hkanjya.tktyflg
		, apkntino	= :hkanjya.apkntino
		, sdnm		= :hkanjya.sdnm
		, bko1		= :hkanjya.bko1
		, bko2		= :hkanjya.bko2
		, bko3		= :hkanjya.bko3
		, zstrdh	= :hkanjya.zstrdh
		, zsssdh	= :hkanjya.zsssdh
		, stlzsssdh	= :hkanjya.stlzsssdh
		, stlzsssip	= :hkanjya.stlzsssip
		, stlzssssyaid= :hkanjya.stlzssssyaid
		, ksndh		= CURRENT TIMESTAMP
		, oyasstcd	= :hkanjya.oyasstcd			-- 1.01 ADD
		, trkdh		= :hkanjya.trkdh			-- 1.01 ADD
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	AND		zssdino	= :hkanjya.zssdino
	;
*/

{
#line 849 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 849 "AD103_db.sqc"
  sqlaaloc(2,88,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.iriketflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 5;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.subsstcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.cdkbn1;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.cdkbn2;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.irimkey;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.srkcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 31;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.srknm;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.tticd;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.ttinm;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.gpcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.gpnm;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.skicd;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.skinm;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.krtno;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 16;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.knjid;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 61;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.knjnmn;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 31;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.knjnmk;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 61;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjnmkey;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.sc;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 6;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.tj;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.tjtni;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sbtkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.birthday;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.birthdaykbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.age;
#line 849 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.agekbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.btcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 31;
#line 849 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.btnm;
#line 849 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.utkcmtcd1;
#line 849 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.utkcmtcd2;
#line 849 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.utkcmtcd3;
#line 849 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 71;
#line 849 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtfr1;
#line 849 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 71;
#line 849 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtfr2;
#line 849 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.ngkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.nsssu;
#line 849 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.hkncd;
#line 849 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ktshsu;
#line 849 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.iniriymd;
#line 849 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.zssflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.kkiriflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.hknskbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.utkkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.nekbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.inknskbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkjkkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.krflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.fdhhkkflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.mutkymd;
#line 849 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 12;
#line 849 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.mirino;
#line 849 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.knsjslbcd1;
#line 849 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.knsjslbcd2;
#line 849 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.knsjslbcd3;
#line 849 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd4;
#line 849 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.ymhkkflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.hkkkbdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 849 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.ecd;
#line 849 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.shcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.sstssnmj;
#line 849 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 41;
#line 849 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.sstssnmn;
#line 849 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.sstrsj;
#line 849 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstrsn;
#line 849 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[24];
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstsbt;
#line 849 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.ttsstflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.rucd;
#line 849 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.irikmksu;
#line 849 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 51;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.bmskn;
#line 849 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.irinrsbt;
#line 849 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.irihsmkbn;
#line 849 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.caresstflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.tktyflg;
#line 849 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 14;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.apkntino;
#line 849 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.sdnm;
#line 849 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.bko1;
#line 849 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.bko2;
#line 849 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.bko3;
#line 849 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.zstrdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.zsssdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.stlzsssdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 16;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.stlzsssip;
#line 849 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 9;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.stlzssssyaid;
#line 849 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 8;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.oyasstcd;
#line 849 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.trkdh;
#line 849 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 11;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.utkymd;
#line 849 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 12;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.irino;
#line 849 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 500; sql_setdlist[23].sqllen = 2;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)&hkanjya.zssdino;
#line 849 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 849 "AD103_db.sqc"
      sqlasetdata(2,64,24,sql_setdlist,0L,0L);
    }
#line 849 "AD103_db.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 849 "AD103_db.sqc"
  sqlastop(0L);
}

#line 849 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "UPDATE kanjya kinkyu : "
		"utkymd[%s]irino[%s]zssdino[%d]",
		kan->utkymd, kan->irino, kan->zssdino );
	LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
        if( sqlca.sqlcode == -911 ){        // LOCK
            switch( sqlca.sqlerrd[2] ){
            case     2 :
                strcpy( G_msg, "AS400����˗����Ή��̊��ҏ��(kanjya)�� "
					"UPDATE �� DEAD LOCK ���������܂����B" );
                break;
            case    68 :
                strcpy( G_msg, "AS400����˗����Ή��̊��ҏ��(kanjya)�� "
                    "UPDATE �� TIMETOUT ���������܂����B" );
                break;
            default :
                strcpy( G_msg, "AS400����˗����Ή��̊��ҏ��(kanjya)�� "
                    "�s����������܂����B" );
                break;
            }
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
			"AS400����˗����Ή��̊��ҏ��(kanjya)�� UPDATE �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,kan->utkymd, kan->irino, kan->zssdino );
		}
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret=RTN_DBERR;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FInsChikenzok                                                  */
/*  �@�\�T�v  �F�����g���@INSERT                                              */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _CHIKENZOK     *try;   : �F�����g��                   */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		InsChikenzok( try )
struct		_CHIKENZOK	*try;			/* �����f�[�^ */
{
	struct	sqlca	sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int	ret;

	/* ��������	*/
	strcpy(func_nm, "InsChikenzok" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃Z�b�g	*/
	memcpy( &hchikenzok, try, sizeof( struct _CHIKENZOK ));
	strcpy( hchikenzok.ksndh, "2006/02/08 19:40:00" );


/*
EXEC SQL INSERT	INTO	chikenzok
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, prtclno
		, kosstcd
		, tytme
		, tyryo
		, tyryotni
		, yzfktme
		, ikasflg
		, kntsu
		, kmksu
		, sspit
		, zrcd01
		, zrcd02
		, zrcd03
		, zrcd04
		, zrcd05
		, zrcd06
		, zrkg01
		, zrkg02
		, zrkg03
		, zrkg04
		, zrkg05
		, zrkg06
		, hrseq
		, kntksflg
		, gcpflg
		, prtclnm
		, ksndh
		)
	VALUES	( :hchikenzok.utkymd
		, :hchikenzok.irino
		, :hchikenzok.iriketflg
		, :hchikenzok.zssdino
		, :hchikenzok.prtclno
		, :hchikenzok.kosstcd
		, :hchikenzok.tytme
		, :hchikenzok.tyryo
		, :hchikenzok.tyryotni
		, :hchikenzok.yzfktme
		, :hchikenzok.ikasflg
		, :hchikenzok.kntsu
		, :hchikenzok.kmksu
		, :hchikenzok.sspit
		, :hchikenzok.zrcd01
		, :hchikenzok.zrcd02
		, :hchikenzok.zrcd03
		, :hchikenzok.zrcd04
		, :hchikenzok.zrcd05
		, :hchikenzok.zrcd06
		, :hchikenzok.zrkg01
		, :hchikenzok.zrkg02
		, :hchikenzok.zrkg03
		, :hchikenzok.zrkg04
		, :hchikenzok.zrkg05
		, :hchikenzok.zrkg06
		, :hchikenzok.hrseq
		, :hchikenzok.kntksflg
		, :hchikenzok.gcpflg
		, :hchikenzok.prtclnm
		, CURRENT TIMESTAMP
		)
	;
*/

{
#line 986 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 986 "AD103_db.sqc"
  sqlaaloc(2,30,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[30];
#line 986 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 986 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hchikenzok.utkymd;
#line 986 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 986 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hchikenzok.irino;
#line 986 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hchikenzok.iriketflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hchikenzok.zssdino;
#line 986 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 12;
#line 986 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hchikenzok.prtclno;
#line 986 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 8;
#line 986 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hchikenzok.kosstcd;
#line 986 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 5;
#line 986 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hchikenzok.tytme;
#line 986 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hchikenzok.tyryo;
#line 986 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 4;
#line 986 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hchikenzok.tyryotni;
#line 986 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 986 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hchikenzok.yzfktme;
#line 986 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hchikenzok.ikasflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)&hchikenzok.kntsu;
#line 986 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)&hchikenzok.kmksu;
#line 986 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hchikenzok.sspit;
#line 986 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hchikenzok.zrcd01;
#line 986 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hchikenzok.zrcd02;
#line 986 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hchikenzok.zrcd03;
#line 986 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hchikenzok.zrcd04;
#line 986 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hchikenzok.zrcd05;
#line 986 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 986 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hchikenzok.zrcd06;
#line 986 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hchikenzok.zrkg01;
#line 986 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hchikenzok.zrkg02;
#line 986 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hchikenzok.zrkg03;
#line 986 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hchikenzok.zrkg04;
#line 986 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hchikenzok.zrkg05;
#line 986 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 986 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hchikenzok.zrkg06;
#line 986 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 5;
#line 986 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hchikenzok.hrseq;
#line 986 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hchikenzok.kntksflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 2;
#line 986 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hchikenzok.gcpflg;
#line 986 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 41;
#line 986 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hchikenzok.prtclnm;
#line 986 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 986 "AD103_db.sqc"
      sqlasetdata(2,0,30,sql_setdlist,0L,0L);
    }
#line 986 "AD103_db.sqc"
  sqlacall((unsigned short)24,8,2,0,0L);
#line 986 "AD103_db.sqc"
  sqlastop(0L);
}

#line 986 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "INSERT chikenzok : utkymd[%s]irino[%s]zssdino[%d]",
		try->utkymd, try->irino, try->zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if (sqlca.sqlcode == 0) {		/* OK */
		ret = RTN_OK;
	} else {
		if ( sqlca.sqlcode == -803 ) {	// duplicate
			sprintf( G_msg,
				"�����g������(chikenzok)�͊��ɑ��݂��Ă��܂��B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,try->utkymd, try->irino, try->zssdino );
			ret=RTN_NG;
		} else {
			sprintf( G_msg,
				"�����g������(chikenzok)�� INSERT �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,try->utkymd, try->irino, try->zssdino );
			ret=RTN_DBERR;
		}
		// ERROR
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelKinkyuIrai                                                 */
/*  �@�\�T�v  �FAS/400����̈˗����ڂ����݂��邩�`�F�b�N����                  */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �F                                                              */
/*  ���A���  �FCOUNT����    ����I��                                         */
/*            �F0 ����       �ُ�I��                                         */
/******************************************************************************/
int		SelKinkyuIrai( kan )
struct		_KANJYA		*kan;			// ���ҏ��
{
	int		ret;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "SelKinkyuIrai" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_utkymd,	kan->utkymd );
	strcpy( hst_irino,	kan->irino );
	hst_cnt=0;
	ind_cnt=0;

	// �폜�t���O�͍l�����Ȃ�

/*
EXEC SQL SELECT	COUNT( irikbn )
	INTO	  :hst_cnt	INDICATOR :ind_cnt
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
	AND		irikbn	= 'K'
	;
*/

{
#line 1057 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1057 "AD103_db.sqc"
  sqlaaloc(2,2,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1057 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1057 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1057 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1057 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1057 "AD103_db.sqc"
  sqlaaloc(3,1,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1057 "AD103_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1057 "AD103_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1057 "AD103_db.sqc"
  sqlacall((unsigned short)24,9,2,3,0L);
#line 1057 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1057 "AD103_db.sqc"


    /* not found --> SQLCODE = +100, SQLSTATE == '02000' */
	/* many rows --> ERROR!!         SQLSTATE == '21000' */

	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( irikbn ) FROM irai WHERE ___ irikbn='K' : "
		"utkymd[%s]irino[%s] indicator[%d] sqlcode[%s]",
		kan->utkymd, kan->irino, ind_cnt, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	// �W���ϐ��ɂ�锻�f
	if( ind_cnt == 0 ) {
		// COUNT���ʂ�Ԃ��i0������j
		ret = hst_cnt;
	} else {
		sprintf( G_msg,
			"AS400�˗����ڏ��(irai)�擾�Ɏ��s���܂����B"
			"BML��t�N����[%s]�˗���NO[%s] SELECT INDICATOR[%d]"
			,kan->utkymd, kan->irino, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		ret=RTN_NG;
	}
	// DEBUG
	sprintf( G_msg, "AS400 irai COUNT[%d]", ret );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FUpdIraiZssdino                                                */
/*  �@�\�T�v  �F�����C���ΏۂɕR�Â��˗����.����No�X�V(�I�[�_���쐬�̂�)     */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		UpdIraiZssdino( kan )
struct		_KANJYA		*kan;			/* ���ҏ�� */
{

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 1108 "AD103_db.sqc"

	char		hst_kmkcd[7+1];
	char		hst_smpcd[7+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 1111 "AD103_db.sqc"

	int		ret;
	int		i;
	char	func_nm[30];				/* �֐�����	*/
	char	wbuf[30];
	struct	sqlca	sqlca;

	/* ��������	*/
	strcpy( func_nm, "UpdIraiZssdino" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_utkymd,	kan->utkymd );
	strcpy( hst_irino,	kan->irino );
	hst_zssdino = kan->zssdino;
	hst_cnt=0;
	ind_cnt=0;
	hkanjya.zssdino = kan->zssdino;

	// �I�[�_���쐬�̈˗����̑��݃`�F�b�N

/*
EXEC SQL SELECT	COUNT( zssdino )
	INTO	  :hst_cnt	INDICATOR :ind_cnt
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
--	AND		knsgrp  = ' '			// �˗��W�J�ł̌���G�t���ɔ��������O
	AND		odrssflg= ' '
	;
*/

{
#line 1138 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1138 "AD103_db.sqc"
  sqlaaloc(2,2,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1138 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1138 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1138 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1138 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1138 "AD103_db.sqc"
  sqlaaloc(3,1,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 1138 "AD103_db.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 1138 "AD103_db.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 1138 "AD103_db.sqc"
  sqlacall((unsigned short)24,10,2,3,0L);
#line 1138 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1138 "AD103_db.sqc"


	/* SQLCODE */
	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	sprintf( G_msg, "SELECT COUNT( zssdino ) FROM irai WHERE _ odrssflg=' ' : "
		"utkymd[%s]irino[%s] indicator[%d] sqlcod[%s]",
		kan->utkymd, kan->irino, ind_cnt, G_err );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );

	if( sqlca.sqlcode == 0 ) {
		// �����ɂ�锻�f
		if( hst_cnt == 0 ){
			// �Y������
			return( RTN_OK );
		}
    } else {
		sprintf( G_msg,
			"���ґ����X�V�Ώۈ˗����ڏ��(irai)�擾�Ɏ��s���܂����B"
			"BML��t�N����[%s]�˗���NO[%s] SELECT INDICATOR[%d]"
			,kan->utkymd, kan->irino, ind_cnt );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return( RTN_NG );
	}
	// �X�V�Ώۑ���
// ----- UPDATE  ------------------------------------------------------------


/*
EXEC SQL DECLARE    iri_cur CURSOR  FOR
    SELECT  zssdino
            , kmkcd
            , smpcd
	FROM	irai
	WHERE	utkymd	= :hst_utkymd
	AND		irino	= :hst_irino
--	AND		knsgrp  = ' '				// �˗��W�J�ł̌���G�t���ɔ��������O
	AND		odrssflg= ' '
	FOR UPDATE
	;
*/

#line 1178 "AD103_db.sqc"


/*
EXEC SQL OPEN iri_cur;
*/

{
#line 1179 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1179 "AD103_db.sqc"
  sqlaaloc(2,2,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1179 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1179 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 1179 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1179 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1179 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 1179 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1179 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1179 "AD103_db.sqc"
  sqlacall((unsigned short)26,11,2,0,0L);
#line 1179 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1179 "AD103_db.sqc"


    i=0;

    while( sqlca.sqlcode == 0 ){
        
/*
EXEC SQL    FETCH   iri_cur
                    INTO      :hst_zssdino
                            , :hst_kmkcd
                            , :hst_smpcd
                    ;
*/

{
#line 1188 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1188 "AD103_db.sqc"
  sqlaaloc(3,3,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1188 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1188 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_zssdino;
#line 1188 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1188 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 8;
#line 1188 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hst_kmkcd;
#line 1188 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1188 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 1188 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hst_smpcd;
#line 1188 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1188 "AD103_db.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 1188 "AD103_db.sqc"
  sqlacall((unsigned short)25,11,0,3,0L);
#line 1188 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1188 "AD103_db.sqc"


		/* SQLCODE */
		// edit sqlcacode for LogOut errcode
		sprintf( G_err, "%d", sqlca.sqlcode );
		// DEBUG
		sprintf( G_msg, "FETCH irai zssdino : "
			"utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]smpcd[%s]"
			, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd, hst_smpcd );
		LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		if (sqlca.sqlcode == 0) {		
			ret=RTN_OK;
		} else if (sqlca.sqlcode == 100) {		
			ret=RTN_OK;
			break;
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"�˗����(irai)��FETCH �Ɏ��s���܂����B"
				"��t��[%s]�˗���NO[%s]������No[%d]����[%s]"
				, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd );
        	EditCsvMsg( G_msg );
			LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
        	ret=RTN_DBERR;
			break;
       }

		
/*
EXEC SQL    UPDATE  irai
					SET     zssdino   = :hkanjya.zssdino
					WHERE	CURRENT OF iri_cur
					;
*/

{
#line 1220 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1220 "AD103_db.sqc"
  sqlaaloc(2,1,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1220 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 500; sql_setdlist[0].sqllen = 2;
#line 1220 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)&hkanjya.zssdino;
#line 1220 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1220 "AD103_db.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 1220 "AD103_db.sqc"
  sqlacall((unsigned short)24,12,2,0,0L);
#line 1220 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1220 "AD103_db.sqc"

/* =================================================
            WHERE   utkymd  = :hst_utkymd
            AND     irino   = :hst_irino
			AND		zssdino	= :hst_zssdino
			AND		knsgrp  = ' '
			AND		kmkcd	= :hst_kmkcd
			AND		odrssflg= ' '
            ;
===================================================*/

		/* SQLCODE */
		// edit sqlcacode for LogOut errcode
		sprintf( G_err, "%d", sqlca.sqlcode );
		// DEBUG
		sprintf( G_msg, "UPDATE irai zssdino : "
			"utkymd[%s]irino[%s]zssdino[%d]kmkcd[%s]smpcd[%s]"
			, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd, hst_smpcd );
		LogOut( LT_DBG, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );

		if (sqlca.sqlcode == 0) {
			// TRACE
			sprintf( G_msg, "�����C���ɍ��킹�˗����̐���No���X�V���܂��� : "
				"��t��[%s]�˗���NO[%s]������No[%d]����[%s]"
				, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd );
			ret=RTN_OK;
			EditCsvMsg( G_msg );
			LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		} else {
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg,
				"�˗����(irai)�̑�������No UPDATE �Ɏ��s���܂����B"
				"��t��[%s]�˗���NO[%s]������No[%d]����[%s]"
				, hst_utkymd, hst_irino, hst_zssdino, hst_kmkcd );
        	ret=RTN_DBERR;
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
       }
    }

/*
EXEC SQL CLOSE iri_cur;
*/

{
#line 1260 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1260 "AD103_db.sqc"
  sqlacall((unsigned short)20,11,0,0,0L);
#line 1260 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1260 "AD103_db.sqc"


	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/*  1.04     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� --> */

/******************************************************************************/
/*  �� �� ��  �FSelKanjya                                                     */
/*  �@�\�T�v  �F���ҏ�񂩂瓯�����ҏ�񂪊��ɂ��邩���`�F�b�N����            */
/*  ��    ��  �F                                                              */
/*  ��P����  �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �F�擾�o�����SELECT���ʂ�hkanjya�Ɋi�[���ĉ���(RTN_OK)         */
/*            �F�擾�ł��Ȃ�������A�����i�[���Ȃ�                            */
/*  ���A���  �FRTN_OK       ����I��(�擾����)                               */
/*            �FRTN_ZERO     ����I��(�Y�����R�[�h�Ȃ�)                       */
/*            �FRTN_DBERR    �ُ�I��(DB�G���[����)                           */
/******************************************************************************/
int		SelKanjya( kan )
struct		_KANJYA		*kan;							/* ���ҏ�� */
{
	int		ret;										/* ���s���� */
	char	func_nm[30];								/* �֐�����	*/
	char	wbuf[30];									/* ���[�N�o�b�t�@ */
	struct	sqlca	sqlca;								/* SQL���s�R�[�h */

	/* ��������	*/
	strcpy( func_nm, "SelKanjya" );						/* ���s�֐�����ݒ� */
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG�o�� */

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hkanjya, '\0', sizeof( struct _KANJYA ));	/* �ϐ������� */
	strcpy( hkanjya.utkymd,	kan->utkymd );				/* �󂯓���ݒ� */
	strcpy( hkanjya.irino,	kan->irino );				/* �˗���No��ݒ� */

/*----- SELECT �������� ------------------------------------------------------------*/
	/* �Ώۃf�[�^(�󂯓�,�˗���No)��SELECT */
	/* 2016.04.18 �Q���q�b�g���ăG���[�ƂȂ�s��ɑ΂���Ή� */
	/* FETCH FIRST �� ORDER BY ��g�ݍ��킹�āA�����C���t���O 1 �̃��R�[�h�̂� SELECT �ΏۂƂ���B*/

/*
EXEC SQL SELECT	* INTO
		  :hkanjya.utkymd
		, :hkanjya.irino
		, :hkanjya.iriketflg
		, :hkanjya.zssdino
		, :hkanjya.sstcd
		, :hkanjya.subsstcd
		, :hkanjya.cdkbn1
		, :hkanjya.cdkbn2
		, :hkanjya.irimkey
		, :hkanjya.srkcd
		, :hkanjya.srknm
		, :hkanjya.tticd
		, :hkanjya.ttinm
		, :hkanjya.gpcd
		, :hkanjya.gpnm
		, :hkanjya.skicd
		, :hkanjya.skinm
		, :hkanjya.krtno
		, :hkanjya.knjid
		, :hkanjya.knjnmn
		, :hkanjya.knjnmk
		, :hkanjya.knjnmkey
		, :hkanjya.sc
		, :hkanjya.tj
		, :hkanjya.tjtni
		, :hkanjya.sbtkbn
		, :hkanjya.birthday
		, :hkanjya.birthdaykbn
		, :hkanjya.age
		, :hkanjya.agekbn
		, :hkanjya.btcd
		, :hkanjya.btnm
		, :hkanjya.utkcmtcd1
		, :hkanjya.utkcmtcd2
		, :hkanjya.utkcmtcd3
		, :hkanjya.utkcmtfr1
		, :hkanjya.utkcmtfr2
		, :hkanjya.utkcmtfrflg
		, :hkanjya.ngkbn
		, :hkanjya.nsssu
		, :hkanjya.hkncd
		, :hkanjya.ktshsu
		, :hkanjya.iniriymd
		, :hkanjya.zssflg
		, :hkanjya.kkiriflg
		, :hkanjya.hknskbn
		, :hkanjya.utkkbn
		, :hkanjya.nekbn
		, :hkanjya.inknskbn
		, :hkanjya.utkjkkbn
		, :hkanjya.krflg
		, :hkanjya.fdhhkkflg
		, :hkanjya.utkdh
		, :hkanjya.mutkymd
		, :hkanjya.mirino
		, :hkanjya.knsjslbcd1
		, :hkanjya.knsjslbcd2
		, :hkanjya.knsjslbcd3
		, :hkanjya.knsjslbcd4
		, :hkanjya.ymhkkflg
		, :hkanjya.hkkkbdh
		, :hkanjya.ecd
		, :hkanjya.shcd
		, :hkanjya.sstssnmj
		, :hkanjya.sstssnmn
		, :hkanjya.sstrsj
		, :hkanjya.sstrsn
		, :hkanjya.sstsbt
		, :hkanjya.ttsstflg
		, :hkanjya.rucd
		, :hkanjya.irikmksu
		, :hkanjya.bmskn
		, :hkanjya.irinrsbt
		, :hkanjya.irihsmkbn
		, :hkanjya.caresstflg
		, :hkanjya.tktyflg
		, :hkanjya.apkntino
		, :hkanjya.sdnm
		, :hkanjya.bko1
		, :hkanjya.bko2
		, :hkanjya.bko3
		, :hkanjya.zstrdh
		, :hkanjya.zsssdh
		, :hkanjya.stlzsssdh
		, :hkanjya.stlzsssip
		, :hkanjya.stlzssssyaid
		, :hkanjya.ksndh
		, :hkanjya.oyasstcd
		, :hkanjya.trkdh
	FROM	KANJYA
	WHERE	utkymd	= :hkanjya.utkymd
	AND		irino	= :hkanjya.irino
	ORDER BY zssflg DESC, zssdino DESC
	FETCH FIRST 1 ROWS ONLY
	;
*/

{
#line 1396 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1396 "AD103_db.sqc"
  sqlaaloc(2,2,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1396 "AD103_db.sqc"
  sqlaaloc(3,89,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 1396 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 1396 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 1396 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 1396 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 1396 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 1396 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 1396 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 1396 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 1396 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 1396 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 1396 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 1396 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 1396 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 1396 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 1396 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 1396 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 1396 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 1396 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 1396 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 1396 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 1396 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 1396 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 1396 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 1396 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.ksndh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.oyasstcd;
#line 1396 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.trkdh;
#line 1396 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1396 "AD103_db.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 1396 "AD103_db.sqc"
  sqlacall((unsigned short)24,13,2,3,0L);
#line 1396 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1396 "AD103_db.sqc"

/*----- SELECT �����܂� ------------------------------------------------------------*/
	sprintf( G_err, "%d", sqlca.sqlcode );
	sprintf( G_msg, "SELECT * FROM KANJYA : "
		"utkymd[%s]irino[%s]zssdino[%d]",
		hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
	LogOut( LT_DBG, LX_SEL, G_err, G_msg, func_nm, __FILE__, __LINE__ );
														/* LOG�o�� */
	if ( sqlca.sqlcode == 0 ) {							/* SQL���sOK */
		EditCsvKanjya( &hkanjya );						/* �X�V�O����LOG�o�� */
		LogOut( LT_TRC, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret = RTN_OK;									/* ���s���� OK */
	}
	else{												/* SQL���sNG */
		if ( sqlca.sqlcode == 100 ){					/* �Ώۃ��R�[�h��������Ȃ�����(NOT FOUND) */
			/* SQLCODE +100, SQLSTATE '02000' */
			sprintf( G_msg, "���ҏ��(KANJYA)�����݂��܂���B" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_ZERO;								/* ���s���� NOT FOUND */
		}
		else{
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "���ҏ��(KANJYA) SELECT ��"
				"�s����������܂����B" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_DBERR;							/* ���s���� DB ERROR */
		}

	}
	return(ret);										/* ���s���ʂ����� */
}

/******************************************************************************/
/*  �� �� ��  �FInsShusei_Kanjya                                              */
/*  �@�\�T�v  �F�C������ INSERT                                               */
/*  ��    ��  �F�z�X�g�ϐ��Fhkanjya                                           */
/*            �F�R�[���O��hkanjya�Ɋ��ҏ����擾���邱��                     */
/*  ��P����  �FNONE                                                          */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK        ����I��                                        */
/*            �FMYAPP_RTN_DUP �ُ�I��(�d���G���[����) *����͂��肦�Ȃ�      */
/*            �FRTN_DBERR     �ُ�I��(DB�G���[����)                          */
/******************************************************************************/
int		InsShusei_Kanjya()
{
	struct	sqlca	sqlca;								/* SQL���s�R�[�h */
	char	func_nm[MYAPP_LEN_FNCNM+1];					/* �֐�����	*/
	int	ret;											/* ���s���� */

	/* ��������	*/
	strcpy(func_nm, "InsShusei_Kanjya" );				/* ���s�֐�����ݒ� */
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG�o�� */
/*----- INSERT �������� ------------------------------------------------------------*/

/*
EXEC SQL INSERT	INTO	SHUSEI_KANJYA
		( utkymd
		, irino
		, iriketflg
		, zssdino
		, sstcd
		, subsstcd
		, cdkbn1
		, cdkbn2
		, irimkey
		, srkcd
		, srknm
		, tticd
		, ttinm
		, gpcd
		, gpnm
		, skicd
		, skinm
		, krtno
		, knjid
		, knjnmn
		, knjnmk
		, knjnmkey
		, sc
		, tj
		, tjtni
		, sbtkbn
		, birthday
		, birthdaykbn
		, age
		, agekbn
		, btcd
		, btnm
		, utkcmtcd1
		, utkcmtcd2
		, utkcmtcd3
		, utkcmtfr1
		, utkcmtfr2
		, utkcmtfrflg
		, ngkbn
		, nsssu
		, hkncd
		, ktshsu
		, iniriymd
		, zssflg
		, kkiriflg
		, hknskbn
		, utkkbn
		, nekbn
		, inknskbn
		, utkjkkbn
		, krflg
		, fdhhkkflg
		, utkdh
		, mutkymd
		, mirino
		, knsjslbcd1
		, knsjslbcd2
		, knsjslbcd3
		, knsjslbcd4
		, ymhkkflg
		, hkkkbdh
		, ecd
		, shcd
		, sstssnmj
		, sstssnmn
		, sstrsj
		, sstrsn
		, sstsbt
		, ttsstflg
		, rucd
		, irikmksu
		, bmskn
		, irinrsbt
		, irihsmkbn
		, caresstflg
		, tktyflg
		, apkntino
		, sdnm
		, bko1
		, bko2
		, bko3
		, zstrdh
		, zsssdh
		, stlzsssdh
		, stlzsssip
		, stlzssssyaid
		, ksndh
		, oyasstcd
		, trkdh
		)
	VALUES	( :hkanjya.utkymd
		, :hkanjya.irino
		, :hkanjya.iriketflg
		, :hkanjya.zssdino
		, :hkanjya.sstcd
		, :hkanjya.subsstcd
		, :hkanjya.cdkbn1
		, :hkanjya.cdkbn2
		, :hkanjya.irimkey
		, :hkanjya.srkcd
		, :hkanjya.srknm
		, :hkanjya.tticd
		, :hkanjya.ttinm
		, :hkanjya.gpcd
		, :hkanjya.gpnm
		, :hkanjya.skicd
		, :hkanjya.skinm
		, :hkanjya.krtno
		, :hkanjya.knjid
		, :hkanjya.knjnmn
		, :hkanjya.knjnmk
		, :hkanjya.knjnmkey
		, :hkanjya.sc
		, :hkanjya.tj
		, :hkanjya.tjtni
		, :hkanjya.sbtkbn
		, :hkanjya.birthday
		, :hkanjya.birthdaykbn
		, :hkanjya.age
		, :hkanjya.agekbn
		, :hkanjya.btcd
		, :hkanjya.btnm
		, :hkanjya.utkcmtcd1
		, :hkanjya.utkcmtcd2
		, :hkanjya.utkcmtcd3
		, :hkanjya.utkcmtfr1
		, :hkanjya.utkcmtfr2
		, :hkanjya.utkcmtfrflg
		, :hkanjya.ngkbn
		, :hkanjya.nsssu
		, :hkanjya.hkncd
		, :hkanjya.ktshsu
		, :hkanjya.iniriymd
		, :hkanjya.zssflg
		, :hkanjya.kkiriflg
		, :hkanjya.hknskbn
		, :hkanjya.utkkbn
		, :hkanjya.nekbn
		, :hkanjya.inknskbn
		, :hkanjya.utkjkkbn
		, :hkanjya.krflg
		, :hkanjya.fdhhkkflg
		, :hkanjya.utkdh
		, :hkanjya.mutkymd
		, :hkanjya.mirino
		, :hkanjya.knsjslbcd1
		, :hkanjya.knsjslbcd2
		, :hkanjya.knsjslbcd3
		, :hkanjya.knsjslbcd4
		, :hkanjya.ymhkkflg
		, :hkanjya.hkkkbdh
		, :hkanjya.ecd
		, :hkanjya.shcd
		, :hkanjya.sstssnmj
		, :hkanjya.sstssnmn
		, :hkanjya.sstrsj
		, :hkanjya.sstrsn
		, :hkanjya.sstsbt
		, :hkanjya.ttsstflg
		, :hkanjya.rucd
		, :hkanjya.irikmksu
		, :hkanjya.bmskn
		, :hkanjya.irinrsbt
		, :hkanjya.irihsmkbn
		, :hkanjya.caresstflg
		, :hkanjya.tktyflg
		, :hkanjya.apkntino
		, :hkanjya.sdnm
		, :hkanjya.bko1
		, :hkanjya.bko2
		, :hkanjya.bko3
		, :hkanjya.zstrdh
		, :hkanjya.zsssdh
		, :hkanjya.stlzsssdh
		, :hkanjya.stlzsssip
		, :hkanjya.stlzssssyaid
		, CURRENT TIMESTAMP
		, :hkanjya.oyasstcd
		, CURRENT TIMESTAMP
		)
	;
*/

{
#line 1634 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1634 "AD103_db.sqc"
  sqlaaloc(2,87,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.iriketflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)&hkanjya.zssdino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.sstcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.subsstcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)hkanjya.cdkbn1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.cdkbn2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irimkey;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.srkcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.srknm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tticd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.ttinm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.gpcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.gpnm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.skicd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.skinm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.krtno;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.knjid;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.knjnmn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.knjnmk;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.knjnmkey;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.sc;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 1634 "AD103_db.sqc"
      sql_setdlist[23].sqldata = (void*)hkanjya.tj;
#line 1634 "AD103_db.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[24].sqldata = (void*)hkanjya.tjtni;
#line 1634 "AD103_db.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[25].sqldata = (void*)hkanjya.sbtkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[26].sqldata = (void*)hkanjya.birthday;
#line 1634 "AD103_db.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[27].sqltype = 460; sql_setdlist[27].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[27].sqldata = (void*)hkanjya.birthdaykbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[28].sqldata = (void*)hkanjya.age;
#line 1634 "AD103_db.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[29].sqltype = 460; sql_setdlist[29].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[29].sqldata = (void*)hkanjya.agekbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[30].sqldata = (void*)hkanjya.btcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 1634 "AD103_db.sqc"
      sql_setdlist[31].sqldata = (void*)hkanjya.btnm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[32].sqldata = (void*)hkanjya.utkcmtcd1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[33].sqldata = (void*)hkanjya.utkcmtcd2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[34].sqldata = (void*)hkanjya.utkcmtcd3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 1634 "AD103_db.sqc"
      sql_setdlist[35].sqldata = (void*)hkanjya.utkcmtfr1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 1634 "AD103_db.sqc"
      sql_setdlist[36].sqldata = (void*)hkanjya.utkcmtfr2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[37].sqltype = 460; sql_setdlist[37].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[37].sqldata = (void*)hkanjya.utkcmtfrflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[38].sqltype = 460; sql_setdlist[38].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[38].sqldata = (void*)hkanjya.ngkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[39].sqldata = (void*)hkanjya.nsssu;
#line 1634 "AD103_db.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[40].sqltype = 460; sql_setdlist[40].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[40].sqldata = (void*)hkanjya.hkncd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[41].sqldata = (void*)hkanjya.ktshsu;
#line 1634 "AD103_db.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[42].sqldata = (void*)hkanjya.iniriymd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[43].sqldata = (void*)hkanjya.zssflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[44].sqltype = 460; sql_setdlist[44].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[44].sqldata = (void*)hkanjya.kkiriflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[45].sqltype = 460; sql_setdlist[45].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[45].sqldata = (void*)hkanjya.hknskbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[46].sqltype = 460; sql_setdlist[46].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[46].sqldata = (void*)hkanjya.utkkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[47].sqltype = 460; sql_setdlist[47].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[47].sqldata = (void*)hkanjya.nekbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[48].sqltype = 460; sql_setdlist[48].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[48].sqldata = (void*)hkanjya.inknskbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[49].sqltype = 460; sql_setdlist[49].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[49].sqldata = (void*)hkanjya.utkjkkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[50].sqltype = 460; sql_setdlist[50].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[50].sqldata = (void*)hkanjya.krflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[51].sqltype = 460; sql_setdlist[51].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[51].sqldata = (void*)hkanjya.fdhhkkflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[52].sqldata = (void*)hkanjya.utkdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 1634 "AD103_db.sqc"
      sql_setdlist[53].sqldata = (void*)hkanjya.mutkymd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 1634 "AD103_db.sqc"
      sql_setdlist[54].sqldata = (void*)hkanjya.mirino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[55].sqldata = (void*)hkanjya.knsjslbcd1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[56].sqldata = (void*)hkanjya.knsjslbcd2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[57].sqldata = (void*)hkanjya.knsjslbcd3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[58].sqldata = (void*)hkanjya.knsjslbcd4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[59].sqltype = 460; sql_setdlist[59].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[59].sqldata = (void*)hkanjya.ymhkkflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[60].sqldata = (void*)hkanjya.hkkkbdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 1634 "AD103_db.sqc"
      sql_setdlist[61].sqldata = (void*)hkanjya.ecd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[62].sqldata = (void*)hkanjya.shcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[63].sqldata = (void*)hkanjya.sstssnmj;
#line 1634 "AD103_db.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sqlasetdata(2,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[23];
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.sstssnmn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.sstrsj;
#line 1634 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)hkanjya.sstrsn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqldata = (void*)hkanjya.sstsbt;
#line 1634 "AD103_db.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqldata = (void*)hkanjya.ttsstflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqldata = (void*)hkanjya.rucd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqldata = (void*)&hkanjya.irikmksu;
#line 1634 "AD103_db.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqldata = (void*)hkanjya.bmskn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqldata = (void*)hkanjya.irinrsbt;
#line 1634 "AD103_db.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqldata = (void*)hkanjya.irihsmkbn;
#line 1634 "AD103_db.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqldata = (void*)hkanjya.caresstflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqldata = (void*)hkanjya.tktyflg;
#line 1634 "AD103_db.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqldata = (void*)hkanjya.apkntino;
#line 1634 "AD103_db.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqldata = (void*)hkanjya.sdnm;
#line 1634 "AD103_db.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqldata = (void*)hkanjya.bko1;
#line 1634 "AD103_db.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqldata = (void*)hkanjya.bko2;
#line 1634 "AD103_db.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqldata = (void*)hkanjya.bko3;
#line 1634 "AD103_db.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqldata = (void*)hkanjya.zstrdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqldata = (void*)hkanjya.zsssdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqldata = (void*)hkanjya.stlzsssdh;
#line 1634 "AD103_db.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqldata = (void*)hkanjya.stlzsssip;
#line 1634 "AD103_db.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqldata = (void*)hkanjya.stlzssssyaid;
#line 1634 "AD103_db.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 8;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqldata = (void*)hkanjya.oyasstcd;
#line 1634 "AD103_db.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 1634 "AD103_db.sqc"
      sqlasetdata(2,64,23,sql_setdlist,0L,0L);
    }
#line 1634 "AD103_db.sqc"
  sqlacall((unsigned short)24,14,2,0,0L);
#line 1634 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1634 "AD103_db.sqc"

/*----- INSERT �����܂� ------------------------------------------------------------*/

	sprintf( G_err, "%d", sqlca.sqlcode );
	sprintf( G_msg, "INSERT kanjya : utkymd[%s]irino[%s]zssdino[%d]",
		hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
	LogOut( LT_DBG, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
														/* LOG�o�� */
	if ( sqlca.sqlcode == 0 ) {							/* SQL���sOK */
		ret = RTN_OK;
	}
	else {
		if ( sqlca.sqlcode == MYAPP_RTN_DUP ) {			/* SQL���s �d���G���[ */
														/* ���A���A�����ł͐�΂ɂ��肦�Ȃ��͂��I�� */
			sprintf( G_msg,
				"�����C�����(SHUSEI_KANJYA)�͊��ɑ��݂��Ă��܂��B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
			/* ERROR */
			ret=MYAPP_RTN_DUP;							/* ���s���� �d���G���[ */
		}
		else{
			sprintf( G_msg,
				"�����C�����(SHUSEI_KANJYA)�� INSERT �Ɏ��s���܂����B"
				"BML��t�N����[%s]�˗���NO[%s]��������NO[%d]"
				,hkanjya.utkymd, hkanjya.irino, hkanjya.zssdino );
			/* ERROR */
			ret=RTN_DBERR;								/* ���s���� DB ERROR */
		}
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_INS, G_err, G_msg, func_nm, __FILE__, __LINE__ );
														/* LOG�o�� */

	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG�o�� */
	return( ret );										/* ���s���ʂ����� */
}

/******************************************************************************/
/*  �� �� ��  �FDelKanjya                                                     */
/*  �@�\�T�v  �F�����C���̂��������ҏ����폜����                            */
/*  ��    ��  �F                                                              */
/*  ��P����  �Fstruct  _KANJYA    *kan;   : ���ҏ��                         */
/*  �o    ��  �FNODE                                                          */
/*  ���A���  �FRTN_OK       ����I��(DELETE����)                             */
/*            �FRTN_ZERO     �ُ�I��(�Y�����R�[�h�Ȃ�)                       */
/*            �FRTN_DBERR    �ُ�I��(DB�G���[����)                           */
/******************************************************************************/
int		DelKanjya( kan )
struct		_KANJYA		*kan;							/* ���ҏ�� */
{
	int		ret;										/* ���s���� */
	char	func_nm[30];								/* �֐�����	*/
	char	wbuf[30];									/* ���[�N�o�b�t�@ */
	struct	sqlca	sqlca;								/* SQL���s�R�[�h */

	/* ��������	*/
	strcpy( func_nm, "DelKanjya" );						/* ���s�֐�����ݒ� */
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
														/* LOG�o�� */

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( &hkanjya, '\0', sizeof( struct _KANJYA ));	/* �ϐ������� */
	strcpy( hkanjya.utkymd,	kan->utkymd );				/* �󂯓���ݒ� */
	strcpy( hkanjya.irino,	kan->irino );				/* �˗���No��ݒ� */

/*----- DELETE �������� ------------------------------------------------------------*/
	/* �Ώۃf�[�^(�󂯓�,�˗���No)��DELETE */
	
/*
EXEC SQL DELETE FROM KANJYA
		WHERE	utkymd	= :hkanjya.utkymd
		AND		irino	= :hkanjya.irino
		;
*/

{
#line 1706 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1706 "AD103_db.sqc"
  sqlaaloc(2,2,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1706 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 1706 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)hkanjya.utkymd;
#line 1706 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1706 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 1706 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)hkanjya.irino;
#line 1706 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1706 "AD103_db.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1706 "AD103_db.sqc"
  sqlacall((unsigned short)24,15,2,0,0L);
#line 1706 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1706 "AD103_db.sqc"


/*----- DELETE �����܂� ------------------------------------------------------------*/
	if ( sqlca.sqlcode == 0 ) {							/* SQL���sOK */
		ret = RTN_OK;									/* ���s���� OK */
	}
	else{												/* SQL���sNG */
		if ( sqlca.sqlcode == 100 ){					/* �Ώۃ��R�[�h��������Ȃ�����(NOT FOUND) */
		/* SQLCODE +100, SQLSTATE '02000' */
		sprintf( G_msg, "�폜���ҏ��(KANJYA)�����݂��܂���B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret = RTN_ZERO;									/* ���s���� NOT FOUND */
		}
		else{											/* SQL���sNG */
			/* SQLCODE > 0 -> WARNING */
			/* SQLCODE < 0 -> ERROR */
			sprintf( G_msg, "���ҏ��(KANJYA) DELETE ��"
								"�s����������܂����B" );
			EditCsvMsg( G_msg );
			LogOut( LT_ERR, LX_UPD, G_err, G_msg, func_nm, __FILE__, __LINE__ );
			ret = RTN_DBERR;							/* ���s���� DB ERROR */
		}
	}
	return(ret);										/* ���s���ʂ����� */
}

/*  1.04     2009/06/29     Merits K.Ameno ��Q�Ǘ�No:0904031814/0904031719�Ή� <-- */

//****************************************************************************
//-----<Ydbcommit>----------------------------------------------------------
int Ydbcommit()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;

	strcpy( func_nm, "Ydbcommit" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	
/*
EXEC SQL COMMIT;
*/

{
#line 1746 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1746 "AD103_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1746 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1746 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "COMMIT", func_nm, __FILE__, __LINE__ );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );

} /* DbDisconn */

//-----<Ydbrollback>----------------------------------------------------------
int Ydbrollback()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;

	strcpy( func_nm, "Ydbrollback" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* rollback the transaction */
	
/*
EXEC SQL ROLLBACK;
*/

{
#line 1772 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1772 "AD103_db.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 1772 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1772 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//		sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[2] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "ROLLBACK", func_nm, __FILE__, __LINE__ );
/*  SqlInfoPrint("ROLLBACK", &sqlca, __LINE__, __FILE__);*/

	if (sqlca.sqlcode == 0) {
		sprintf( G_msg, "The transaction was rolled back." );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );
} /* TransRollback */

//-----<Ydbconn>----------------------------------------------------------
int Ydbconn()
{
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int		ret=RTN_OK;
	struct	sqlca sqlca;


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 1799 "AD103_db.sqc"

	char	dbAlias[15];
	char	user[129];
	char	pswd[15];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 1803 "AD103_db.sqc"


	strcpy( func_nm, "Ydbconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( dbAlias,	stcPRM.dbp_dbAlias );
	strcpy( user,		stcPRM.dbp_user );
	strcpy( pswd,		stcPRM.dbp_pswd );

	
/*
EXEC SQL CONNECT TO :dbAlias USER :user USING :pswd;
*/

{
#line 1812 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1812 "AD103_db.sqc"
  sqlaaloc(2,3,23,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 1812 "AD103_db.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 15;
#line 1812 "AD103_db.sqc"
      sql_setdlist[0].sqldata = (void*)dbAlias;
#line 1812 "AD103_db.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1812 "AD103_db.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 129;
#line 1812 "AD103_db.sqc"
      sql_setdlist[1].sqldata = (void*)user;
#line 1812 "AD103_db.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1812 "AD103_db.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 15;
#line 1812 "AD103_db.sqc"
      sql_setdlist[2].sqldata = (void*)pswd;
#line 1812 "AD103_db.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1812 "AD103_db.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 1812 "AD103_db.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 1812 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1812 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "CONNECT", func_nm, __FILE__, __LINE__ );

	/* �{����"00000"��cmpare������	*/
	if( memcmp( sqlca.sqlstate, "00000", 5 ) != 0 ){
		/* ERROR  */
		sprintf( G_msg, "�c�a�Q�ւ̐ڑ��Ɏ��s���܂����B" );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		ret = RTN_NG;
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( ret );
} /* DbConn */

//-----<Ydbdisconn>----------------------------------------------------------
int Ydbdisconn()
{
	struct sqlca sqlca;
	char	func_nm[MYAPP_LEN_FNCNM+1];
	int	ret=RTN_OK;

	strcpy( func_nm, "Ydbdisconn" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

  	/* Commit all non-committed transactions to release database locks */
	
/*
EXEC SQL COMMIT;
*/

{
#line 1845 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1845 "AD103_db.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1845 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1845 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
//	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
//			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );

	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "COMMIT BEFORE CONNECT RESET"
			, func_nm, __FILE__, __LINE__ );

	
/*
EXEC SQL CONNECT RESET;
*/

{
#line 1856 "AD103_db.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1856 "AD103_db.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 1856 "AD103_db.sqc"
  sqlastop(0L);
}

#line 1856 "AD103_db.sqc"


	// edit sqlcacode for LogOut errcode
	sprintf( G_err, "sql:cd[%d]sta[%.5s]erd[%d]",
			sqlca.sqlcode, sqlca.sqlstate , sqlca.sqlerrd[3] );
	sprintf( G_err, "%d", sqlca.sqlcode );
	// DEBUG
	LogOut( LT_DBG, LX_NON, G_err, "CONNECT RESET",func_nm, __FILE__, __LINE__);

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
  	return( RTN_OK );
} /* DbDisconn */
/** End of File ***************************************************************/
