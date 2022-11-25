static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,115,65,74,114,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,71,68,50,48,53,71,69,84,0,0,0,0,0,0,0,0,
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


#line 1 "GD205Getdb.sqc"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FGD205GetKkassflg.sqc                                         */
/*   �T      �v�F���ʏC���t���O�l�`�w�擾                                     */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.11     2006/08/29     INTEC.INC      CREATE                             */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"bml_base.h"
#include	"bmllog.h"
#include	"GD205Kekka.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 27 "GD205Getdb.sqc"

	char	hst_kkassflg[1+1];
	char	hst_knskisymd[10+1];
	char	hst_sriymd[10+1];
	char	hst_kntno[13+1];
	char	hst_knsgrp[16+1];
	char	hst_kmkcd[7+1];
	char	hst_utkymd[10+1];
	char	hst_irino[11+1];
	short	hst_zssdino;
	char	hst_sbtkbn[1+1];
struct	_KINKMMST {
	char	kmkcd[7+1];
	char	aswscd[3+1];
} hkinkmmst;


/*
EXEC SQL END DECLARE SECTION;
*/

#line 43 "GD205Getdb.sqc"


/******************************************************************************/
/*  �� �� ��  �FGD205GetKkassflgMax                                           */
/*  �@�\�T�v  �F���ʏC���t���O�l�`�w�擾                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _Kekka *kek;   :���ʏ��                              */
/*   ��Q���� �Fchar cKkassflg[];      :���ʏC���t���O�l�`�w                  */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		GD205GetKkassflgMax( kek, cKkassflg )
Kekka		*kek;
char		cKkassflg[];
{
	int		ret;
	struct	sqlca			sqlca;

	/* ��������	*/
	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "GD205GetKkassflgMax", __LINE__,
                EXEFLG_NON, "00000000",
                "Start Function");	

	// �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g
	memset( hst_kkassflg,	'\0',	sizeof( hst_kkassflg ));
	strcpy( hst_knskisymd,	kek->knskisymd );
	strcpy( hst_sriymd,		kek->sriymd );
	strcpy( hst_kntno,		kek->kntno );
	strcpy( hst_knsgrp,		kek->knsgrp );
	strcpy( hst_kmkcd,		kek->kmkcd );


/*
EXEC SQL SELECT	MAX( kkassflg )
	INTO	:hst_kkassflg
	FROM	kekka
	WHERE	knskisymd	=	:hst_knskisymd
	AND		sriymd		=	:hst_sriymd
	AND		kntno		=	:hst_kntno
	AND		knsgrp		=	:hst_knsgrp
	AND		kmkcd		=	:hst_kmkcd
	;
*/

{
#line 84 "GD205Getdb.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 84 "GD205Getdb.sqc"
  sqlaaloc(2,5,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 84 "GD205Getdb.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[0].sqldata = (void*)hst_knskisymd;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[1].sqldata = (void*)hst_sriymd;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[2].sqldata = (void*)hst_kntno;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[3].sqldata = (void*)hst_knsgrp;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[4].sqldata = (void*)hst_kmkcd;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 84 "GD205Getdb.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 84 "GD205Getdb.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 84 "GD205Getdb.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 2;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[0].sqldata = (void*)hst_kkassflg;
#line 84 "GD205Getdb.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 84 "GD205Getdb.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 84 "GD205Getdb.sqc"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 84 "GD205Getdb.sqc"
  sqlastop(0L);
}

#line 84 "GD205Getdb.sqc"


	if ( sqlca.sqlcode == 0 ) {		/* OK */
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD205GetKkassflgMax", __LINE__,
					EXEFLG_SEL, "020",
					"KKASSFLG MAX[%s-%s-%s-%s-%s][%s]", 
					hst_knskisymd, hst_sriymd, hst_kntno,
					hst_knsgrp, hst_kmkcd, hst_kkassflg );
		strcpy( cKkassflg,	hst_kkassflg );
		ret = RTN_OK;
	} else {
		// ERROR
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD205GetKkassflgMax", __LINE__,
					EXEFLG_SEL, "020",
					"KKASSFLG MAX SELECT ERROR [%d] [%s-%s-%s-%s-%s][%s]", 
					sqlca.sqlcode,
					hst_knskisymd, hst_sriymd, hst_kntno,
					hst_knsgrp, hst_kmkcd, hst_kkassflg );
		ret = RTN_NG;
	}
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FGD205_GetWscd                                                 */
/*  �@�\�T�v  �FAS400��WS�R�[�h�擾                                           */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar  aswscd;          :(O)AS��WS�R�[�h                       */
/*   ��Q���� �Fchar  kmkcd;           :(I)���ڃR�[�h                         */
/*   ��R���� �Fchar  knskisymd;       :(I)���ʁD�����J�n��                   */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		GD205_GetWscd( aswscd, kmkcd, knskisymd )
char	aswscd[];
char	kmkcd[];
char	knskisymd[];
{
	int		ret;
	struct	sqlca			sqlca;

	/* ��������	*/
	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "GD205_GetWscd", __LINE__,
                EXEFLG_NON, "00000000",
                "Start Function");	

	/* ======================== */
	/*	�{�ݕʏ����}�X�^�̎擾	*/
	/* ======================== */
		// �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g
	memset( &hkinkmmst,		'\0',	sizeof( struct	_KINKMMST ));
	memset( hst_knskisymd,	'\0',	sizeof( hst_knskisymd	 ));
	memset( aswscd,			'\0',	sizeof( aswscd	 ));
	strcpy( hkinkmmst.kmkcd			,kmkcd );
	strcpy( hst_knskisymd			,knskisymd );


/*
EXEC SQL DECLARE ssr_cur CURSOR FOR
	SELECT	aswscd
	FROM	kinkmmst
	WHERE	kmkcd	=	:hkinkmmst.kmkcd
	AND		kaiymd	<=	:hst_knskisymd
	AND		haiymd	>=	:hst_knskisymd
	ORDER BY smpcd DESC
	FOR READ ONLY;
*/

#line 149 "GD205Getdb.sqc"

	;


/*
EXEC SQL OPEN ssr_cur;
*/

{
#line 152 "GD205Getdb.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 152 "GD205Getdb.sqc"
  sqlaaloc(2,3,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 152 "GD205Getdb.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[0].sqldata = (void*)hkinkmmst.kmkcd;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[1].sqldata = (void*)hst_knskisymd;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[2].sqldata = (void*)hst_knskisymd;
#line 152 "GD205Getdb.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 152 "GD205Getdb.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 152 "GD205Getdb.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 152 "GD205Getdb.sqc"
  sqlastop(0L);
}

#line 152 "GD205Getdb.sqc"


	while( sqlca.sqlcode == 0 ){

/*
EXEC SQL FETCH ssr_cur
		INTO	:hkinkmmst.aswscd
		;
*/

{
#line 157 "GD205Getdb.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 157 "GD205Getdb.sqc"
  sqlaaloc(3,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 157 "GD205Getdb.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 157 "GD205Getdb.sqc"
      sql_setdlist[0].sqldata = (void*)hkinkmmst.aswscd;
#line 157 "GD205Getdb.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 157 "GD205Getdb.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 157 "GD205Getdb.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 157 "GD205Getdb.sqc"
  sqlastop(0L);
}

#line 157 "GD205Getdb.sqc"

		if ( sqlca.sqlcode == 0 ) {		/* OK */
			strcpy( aswscd, hkinkmmst.aswscd );
			ret = RTN_OK;
			break;
		} else  if ( sqlca.sqlcode == 100 ){	/* NOT FOUND */
			ret = RTN_ZERO;
			break;
		} else {
			// ERROR
			sFncPutLog( TRCKIND_WARNING, __FILE__, "GD205_GetWscd", __LINE__,
						EXEFLG_SEL, "020",
						"KINKMMST SELECT ERROR [%d][%s]", 
						sqlca.sqlcode, hkinkmmst.kmkcd);	
			ret = RTN_DBERR;
			break;
		}
		// �P���ǂݍ��񂾂甲����
		break;
	}

/*
EXEC SQL CLOSE	ssr_cur;
*/

{
#line 177 "GD205Getdb.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 177 "GD205Getdb.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 177 "GD205Getdb.sqc"
  sqlastop(0L);
}

#line 177 "GD205Getdb.sqc"


	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FGD205GetSbtkbn                                                */
/*  �@�\�T�v  �F���ʋ敪�擾                                                  */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _Kekka *kek;   :���ʏ��                              */
/*   ��Q���� �Fchar cSbtkbn[];        :���ʋ敪                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		GD205GetSbtkbn( kek, cSbtkbn )
Kekka		*kek;
char		cSbtkbn[];
{
	int		ret;
	int		i;
	struct	sqlca	sqlca;

	/* ��������	*/
	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "GD205GetSbtkbn", __LINE__,
                EXEFLG_NON, "00000000",
                "Start Function");	

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( hst_utkymd,	'\0', sizeof( hst_utkymd ));
	memset( hst_irino,	'\0', sizeof( hst_irino ));
	memset( hst_sbtkbn,	'\0', sizeof( hst_sbtkbn ));
	strcpy( hst_utkymd,	kek->utkymd );
	strcpy( hst_irino,	kek->irino );
	hst_zssdino=kek->zssdino;


/*
EXEC SQL	SELECT	sbtkbn
			INTO	:hst_sbtkbn
			FROM	kanjya
			WHERE	utkymd	=  :hst_utkymd
			AND		irino	=  :hst_irino
			AND		zssdino	=  :hst_zssdino
			;
*/

{
#line 220 "GD205Getdb.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 220 "GD205Getdb.sqc"
  sqlaaloc(2,3,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 220 "GD205Getdb.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[0].sqldata = (void*)hst_utkymd;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[2].sqldata = (void*)&hst_zssdino;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 220 "GD205Getdb.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 220 "GD205Getdb.sqc"
  sqlaaloc(3,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 220 "GD205Getdb.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 2;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[0].sqldata = (void*)hst_sbtkbn;
#line 220 "GD205Getdb.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 220 "GD205Getdb.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 220 "GD205Getdb.sqc"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 220 "GD205Getdb.sqc"
  sqlastop(0L);
}

#line 220 "GD205Getdb.sqc"


	if ( sqlca.sqlcode == 0 ) {
		strcpy( cSbtkbn		, hst_sbtkbn );
		ret=RTN_OK;
	} else {
		if ( sqlca.sqlcode == 100 ) {
			ret=RTN_ZERO;
		} else {
			sFncPutLog( TRCKIND_WARNING, __FILE__, "GD205GetSbtkbn", __LINE__,
					EXEFLG_SEL, "020",
					"���ҏ��擾���ɕs����������܂����B"
					"utkymd[%s]irino[%s]zssdino[%d]",
					kek->utkymd, kek->irino, kek->zssdino );
			ret=RTN_DBERR;
		}
	}

	return( ret );
}

/** End of File ***************************************************************/
