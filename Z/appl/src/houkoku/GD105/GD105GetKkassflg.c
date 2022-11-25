static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,54,65,68,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,49,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105GetKkassflg.sqc"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FGD105GetKkassflg.sqc                                         */
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
#include	"GD105Kekka.h"


/******************************************************************************/
/*  �� �� ��  �FGD105GetKkassflgMax                                           */
/*  �@�\�T�v  �F���ʏC���t���O�l�`�w�擾                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fstruct  _Kekka *kek;   :���ʏ��                              */
/*   ��Q���� �Fchar cKkassflg[];      :���ʏC���t���O�l�`�w                  */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		GD105GetKkassflgMax( kek, cKkassflg )
Kekka		*kek;
char		cKkassflg[];
{
	int		ret;
	struct	sqlca			sqlca;


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 45 "GD105GetKkassflg.sqc"

	char	hst_kkassflg[1+1];
	char	hst_knskisymd[10+1];
	char	hst_sriymd[10+1];
	char	hst_kntno[13+1];
	char	hst_knsgrp[16+1];
	char	hst_kmkcd[7+1];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 52 "GD105GetKkassflg.sqc"


	/* ��������	*/
	//�g���[�X���O
#ifdef _TRACE
	sFncPutLog( TRCKIND_TRACE, __FILE__, "GD105GetKkassflgMax", __LINE__, EXEFLG_NON, "00000000",
				"Start Function");
#endif

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
#line 77 "GD105GetKkassflg.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 77 "GD105GetKkassflg.sqc"
  sqlaaloc(2,5,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[0].sqldata = (void*)hst_knskisymd;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[1].sqldata = (void*)hst_sriymd;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[2].sqldata = (void*)hst_kntno;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[3].sqldata = (void*)hst_knsgrp;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[4].sqldata = (void*)hst_kmkcd;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 77 "GD105GetKkassflg.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 77 "GD105GetKkassflg.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 2;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[0].sqldata = (void*)hst_kkassflg;
#line 77 "GD105GetKkassflg.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 77 "GD105GetKkassflg.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 77 "GD105GetKkassflg.sqc"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 77 "GD105GetKkassflg.sqc"
  sqlastop(0L);
}

#line 77 "GD105GetKkassflg.sqc"


	if ( sqlca.sqlcode == 0 ) {		/* OK */
/* del 20070613 waj ���x�A�b�v
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "GD105GetKkassflgMax", __LINE__,
					EXEFLG_SEL, "020",
					"KKASSFLG MAX[%s-%s-%s-%s-%s][%s]", 
					hst_knskisymd, hst_sriymd, hst_kntno,
					hst_knsgrp, hst_kmkcd, hst_kkassflg );
*/
		strcpy( cKkassflg,	hst_kkassflg );
		ret = RTN_OK;
	} else {
		// ERROR
		sFncPutLog( TRCKIND_WARNING, __FILE__, "GD105GetKkassflgMax", __LINE__,
					EXEFLG_SEL, "020",
					"KKASSFLG MAX SELECT ERROR [%d] [%s-%s-%s-%s-%s][%s]", 
					sqlca.sqlcode,
					hst_knskisymd, hst_sriymd, hst_kntno,
					hst_knsgrp, hst_kmkcd, hst_kkassflg );
		ret = RTN_NG;
	}
	return( ret );
}
/** End of File ***************************************************************/
