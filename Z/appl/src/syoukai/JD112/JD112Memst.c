static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,67,65,74,53,81,74,77,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,74,68,49,49,50,77,69,77,0,0,0,0,0,0,0,0,
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


#line 1 "JD112Memst.sqc"
/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����FJD112Memst.sqc                                               */
/*   �T      �v�F�c�a�A�N�Z�X                                                 */
/*   OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/23     INTEC.INC      CREATE                             */
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
#include	"JD112Main.h"


/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 27 "JD112Memst.sqc"

	char		hst_ymd[11];
	char		hst_bskkbn[4+1];            // ���͋@�敪
	char		hst_bsklne[4+1];            // ���͋@���C��
	sqlint32    hst_cnt;                    // �}�X�^����
	short		ind_cnt;					// �W���ϐ�
	char		hst_timestamp[26+1];		// �N�������Z�o
	char		hst_timestamp2[26+1];		// �N�������Z�o

/*
EXEC SQL END DECLARE SECTION;
*/

#line 35 "JD112Memst.sqc"


/******************************************************************************/
/*  �� �� ��  �FSelCountMemst                                                 */
/*  �@�\�T�v  �F���͋@�}�X�^�i���ڃ}�X�^�����j�����擾                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];	: 	�������                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FCOUNT����    ����I��                                         */
/*            �F0 ����       �ُ�I��                                         */
/******************************************************************************/
int		SelCountMemst( ymd )
char		ymd[];	
{
	int		ret;
	struct	sqlca	sqlca;

	/* ��������	*/
	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelCountMemst", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Start Function");

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	strcpy( hst_ymd,	ymd );
	hst_cnt=0;
	ind_cnt=0;


/*
EXEC SQL SELECT	COUNT( * )
	INTO	:hst_cnt	INDICATOR :ind_cnt
	FROM	(	SELECT	DISTINCT BSKKBN, BSKLNE
				FROM	MEMST
				WHERE	KAIYMD <= :hst_ymd
				AND		HAIYMD >= :hst_ymd
				) me
	;
*/

{
#line 70 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 70 "JD112Memst.sqc"
  sqlaaloc(2,2,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 70 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 70 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 70 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 70 "JD112Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 70 "JD112Memst.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 70 "JD112Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 70 "JD112Memst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 70 "JD112Memst.sqc"
  sqlaaloc(3,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 70 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 497; sql_setdlist[0].sqllen = 4;
#line 70 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)&hst_cnt;
#line 70 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = &ind_cnt;
#line 70 "JD112Memst.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 70 "JD112Memst.sqc"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 70 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 70 "JD112Memst.sqc"


	// �W���ϐ��ɂ�锻�f
	if( ind_cnt == 0 ) {
		// COUNT���ʂ�Ԃ��i0������j
		ret = hst_cnt;
	} else {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "SelCountMemst", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"���͋@�}�X�^(memst)�̌����擾�Ɏ��s���܂����B"
					"�N����[%s] SELECT INDICATOR[%d]"
					,ymd, ind_cnt );
		ret=RTN_NG;
	}
	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelCountMemst", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "End Function");
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelMemst                                                     */
/*  �@�\�T�v  �F���͋@�}�X�^ SELECT                                           */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	ymd[];   : ���                                     */
/*   ��Q���� �Fint		kensu;   : malloc����                                 */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelMemst( ymd, kensu, pMe )
char		ymd[];	
int			kensu;
struct		_MEMST	*pMe;
{
	int		ret;
	int		i;
	struct	sqlca	sqlca;

	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelMemst", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Start Function");

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( hst_bskkbn,	'\0', sizeof( hst_bskkbn ));
	memset( hst_bsklne,	'\0', sizeof( hst_bsklne ));
	strcpy( hst_ymd,	ymd );


/*
EXEC SQL DECLARE    me_cur CURSOR  FOR
	SELECT	BSKKBN
			, BSKLNE
	FROM	(	SELECT	DISTINCT BSKKBN, BSKLNE
				FROM	MEMST
				WHERE	KAIYMD <= :hst_ymd
				AND		HAIYMD >= :hst_ymd
				) me
	ORDER BY BSKKBN, BSKLNE
	FOR	READ ONLY
	;
*/

#line 130 "JD112Memst.sqc"



/*
EXEC SQL OPEN me_cur;
*/

{
#line 132 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 132 "JD112Memst.sqc"
  sqlaaloc(2,2,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 132 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 132 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_ymd;
#line 132 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 132 "JD112Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 132 "JD112Memst.sqc"
      sql_setdlist[1].sqldata = (void*)hst_ymd;
#line 132 "JD112Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 132 "JD112Memst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 132 "JD112Memst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 132 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 132 "JD112Memst.sqc"


	i=0;

	while( sqlca.sqlcode == 0 ){
		
/*
EXEC SQL    FETCH   me_cur
					INTO	  :hst_bskkbn
							, :hst_bsklne
					;
*/

{
#line 140 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 140 "JD112Memst.sqc"
  sqlaaloc(3,2,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 140 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 140 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_bskkbn;
#line 140 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 140 "JD112Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 140 "JD112Memst.sqc"
      sql_setdlist[1].sqldata = (void*)hst_bsklne;
#line 140 "JD112Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 140 "JD112Memst.sqc"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 140 "JD112Memst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 140 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 140 "JD112Memst.sqc"

		if( i >= kensu ){
			break;
		}
		strcpy( pMe[i].bskkbn,	hst_bskkbn );
		strcpy( pMe[i].bsklne,	hst_bsklne );
		i++;
	}

	if ( sqlca.sqlcode == 100 ) {	// NOT FOUND or END
		if( i > 0 ){
			ret = RTN_OK;
		} else {
			sFncPutLog( TRCKIND_ERROR, __FILE__, "SelMemst", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				"���͋@�}�X�^���擾�ł��܂���B���[%s]", ymd );
		ret=RTN_NG;
		}
	} else {
		/* SQLCODE > 0 -> WARNING */
		/* SQLCODE < 0 -> ERROR */
		sFncPutLog( TRCKIND_ERROR, __FILE__, "SelMemst", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"���͋@�}�X�^ FETCH �ŕs����������܂����B���[%s]"	
					, ymd );
		ret=RTN_NG;
	}

/*
EXEC SQL    CLOSE   me_cur;
*/

{
#line 167 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 167 "JD112Memst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 167 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 167 "JD112Memst.sqc"


/*
EXEC SQL	COMMIT;
*/

{
#line 168 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 168 "JD112Memst.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 168 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 168 "JD112Memst.sqc"


	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelMemst", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "End Function");
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelStaTimestamp                                               */
/*  �@�\�T�v  �F�N������ SELECT(�V�X�e����������1���Ԃ��������l���擾�j       */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	dh[];   : �N�������̈�                                */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelStaTimestamp( dh )
char		dh[];	
{
	int		ret;
	int		i;
	struct	sqlca	sqlca;

	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelStaTimestamp", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Start Function");

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( hst_timestamp,	'\0', sizeof( hst_timestamp ));

	if( dh[0] == '\0' ){
		
/*
EXEC SQL VALUES( CURRENT TIMESTAMP - 1  HOUR )
			INTO    :hst_timestamp
			;
*/

{
#line 204 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 204 "JD112Memst.sqc"
  sqlaaloc(3,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 204 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 204 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_timestamp;
#line 204 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 204 "JD112Memst.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 204 "JD112Memst.sqc"
  sqlacall((unsigned short)24,3,0,3,0L);
#line 204 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 204 "JD112Memst.sqc"

	} else {
			// ����TIMESTAMP�̑Ó����`�F�b�N
		strcpy( hst_timestamp, dh );
		
/*
EXEC SQL VALUES( TIMESTAMP( :hst_timestamp ))
			INTO    :hst_timestamp
			;
*/

{
#line 210 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 210 "JD112Memst.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 210 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 210 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_timestamp;
#line 210 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 210 "JD112Memst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 210 "JD112Memst.sqc"
  sqlaaloc(3,1,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 210 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 210 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_timestamp;
#line 210 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 210 "JD112Memst.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 210 "JD112Memst.sqc"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 210 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 210 "JD112Memst.sqc"

	}

	if ( sqlca.sqlcode == 0 ) {	// NOT FOUND or END
		strcpy( dh, hst_timestamp );
		ret=RTN_OK;
	} else {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "SelStaTimestamp", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"CURRENT TIMESTAMP - 1 HOUR[%s] �ŕs����������܂����B"
					, dh );
		ret=RTN_NG;
	}

/*
EXEC SQL	COMMIT;
*/

{
#line 223 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 223 "JD112Memst.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 223 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 223 "JD112Memst.sqc"


	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelStaTimestamp", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "End Function");
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FSelPlus10Minutes                                              */
/*  �@�\�T�v  �F������TIMESTAMP��10���𑫂����������擾����                   */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar	dh[];   : �N�������̈�                                */
/*   ��Q���� �Fint		mode;   : 0:MINUS 1:PLUS                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		SelPlus10Minutes( dh, mode )
char		dh[];	
int			mode;	
{
	int		ret;
	int		i;
	struct	sqlca	sqlca;

	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelPlusMinutes", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "Start Function");

	/* �z�X�g�ϐ��ւ̃L�[���ڃZ�b�g	*/
	memset( hst_timestamp,	'\0', sizeof( hst_timestamp ));
	memset( hst_timestamp2,	'\0', sizeof( hst_timestamp2 ));
	strcpy( hst_timestamp, dh );

	if( mode == MYAPP_FUNC_MINUS ){
		
/*
EXEC SQL VALUES( TIMESTAMP( :hst_timestamp ) - 10 MINUTES )
				INTO    :hst_timestamp2
			;
*/

{
#line 263 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 263 "JD112Memst.sqc"
  sqlaaloc(2,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 263 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 263 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_timestamp;
#line 263 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 263 "JD112Memst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 263 "JD112Memst.sqc"
  sqlaaloc(3,1,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 263 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 263 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_timestamp2;
#line 263 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 263 "JD112Memst.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 263 "JD112Memst.sqc"
  sqlacall((unsigned short)24,5,2,3,0L);
#line 263 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 263 "JD112Memst.sqc"

	} else {
		
/*
EXEC SQL VALUES( TIMESTAMP( :hst_timestamp ) + 10 MINUTES )
				INTO    :hst_timestamp2
				;
*/

{
#line 267 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 267 "JD112Memst.sqc"
  sqlaaloc(2,1,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 267 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 267 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_timestamp;
#line 267 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 267 "JD112Memst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 267 "JD112Memst.sqc"
  sqlaaloc(3,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 267 "JD112Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 267 "JD112Memst.sqc"
      sql_setdlist[0].sqldata = (void*)hst_timestamp2;
#line 267 "JD112Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 267 "JD112Memst.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 267 "JD112Memst.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 267 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 267 "JD112Memst.sqc"

	}

	if ( sqlca.sqlcode == 0 ) {
		strcpy( dh, hst_timestamp2 );
		ret=RTN_OK;
	} else {
		sFncPutLog( TRCKIND_ERROR, __FILE__, "SelPlus10Minutes", __LINE__,
					EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					"[%s][%d]10 MINUTES PROC �ŕs����������܂����B{%d]"
					, dh, mode, sqlca.sqlcode );
		strcpy( dh, hst_timestamp );
		ret=RTN_NG;
	}

/*
EXEC SQL	COMMIT;
*/

{
#line 281 "JD112Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 281 "JD112Memst.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 281 "JD112Memst.sqc"
  sqlastop(0L);
}

#line 281 "JD112Memst.sqc"


	//�g���[�X���O
    sFncPutLog( TRCKIND_TRACE, __FILE__, "SelPlus10Minutes", __LINE__,
                EXEFLG_NON, MYAPP_LOG_ERRCODE_NON,
                "End Function");
	return( ret );
}
// end of text
