static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,82,65,81,86,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,67,78,84,66,0,0,0,0,0,0,0,0,
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


#line 1 "A205cntBunchu.sqc"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FA205cntBunchu.sqc                                            */
/*   �T      �v�F�c�a�A�N�Z�X                                                 */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/10/24     INTEC.INC      CREATE                             */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include	<stdio.h>
#include 	<stdlib.h>
#include 	<string.h>
#include	<sqlca.h>
#include	"bmllog.h"
#include	"bmlprm.h"
#include	"AD205Buntekai.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 27 "A205cntBunchu.sqc"

	char		hst_utkymd[11];
	char		hst_irino[12];
	char		hst_smpcd[8];
	char		hst_kmkcd[8];
	char		hst_sriymd[11];
	sqlint32    hst_cnt;
	short		ind_cnt;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 35 "A205cntBunchu.sqc"


/******************************************************************************/
/*  �� �� ��  �FcntBunchuOk                                                   */
/*  �@�\�T�v  �F����OK�f�[�^�����擾                                          */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];	: 	�������                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FCOUNT����    ����I��                                         */
/*            �F0 ����       �ُ�I��                                         */
/******************************************************************************/
int		cntBunchuOk( bun )
Bunchu		*bun;	
{
	int		ret;
	struct	sqlca	sqlca;

	/* ��������	*/
	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "cntBunchuOk", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Start Function");

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_utkymd,	bun->utkymd );
	strcpy( hst_irino,	bun->irino );
	strcpy( hst_smpcd,	bun->smpcd );
	strcpy( hst_kmkcd,	bun->kmkcd );
	strcpy( hst_sriymd,	bun->sriymd );
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( bnckka )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	bunchu
	WHERE	SRIYMD = :hst_sriymd
	AND		IRINO  = :hst_irino
	AND		SMPCD  = :hst_smpcd
	AND		KMKCD  = :hst_kmkcd
	AND		UTKYMD = :hst_utkymd
	AND		BNCKKA in ('0','4')
	;
*/

{
#line 76 "A205cntBunchu.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 76 "A205cntBunchu.sqc"
  sqlaaloc(2,5,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqldata = (void*)hst_sriymd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[1].sqldata = (void*)hst_irino;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[2].sqldata = (void*)hst_smpcd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 8;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[3].sqldata = (void*)hst_kmkcd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[4].sqldata = (void*)hst_utkymd;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 76 "A205cntBunchu.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 76 "A205cntBunchu.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 76 "A205cntBunchu.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 76 "A205cntBunchu.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 76 "A205cntBunchu.sqc"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 76 "A205cntBunchu.sqc"
  sqlastop(0L);
}

#line 76 "A205cntBunchu.sqc"


	// �W���ϐ��ɂ�锻�f
	if( ind_cnt == 0 ) {
		// COUNT���ʂ�Ԃ��i0������j
		ret = hst_cnt;
		sFncPutLog( TRCKIND_DEBUG, __FILE__, "cntBunchuOk", __LINE__,
                    EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
                    "����(bunchu)�̌����擾���܂����B"
                    "[CNT:%d %s %s %s %s %s]",
                    hst_cnt, bun->sriymd, bun->utkymd,
                    bun->kntno, bun->irino,bun->kmkcd );
	} else {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "cntBunchuOk", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"����(bunchu)�̌����擾�Ɏ��s���܂����B"
                    "[%s %s %s %s %s]",
                    bun->sriymd, bun->utkymd,
                    bun->kntno, bun->irino,bun->kmkcd );
		ret=RTN_NG;
	}
	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "cntBunchuOk", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "End Function");
	return( ret );
}
// end of text
