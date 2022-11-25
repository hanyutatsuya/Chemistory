static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,113,65,70,52,85,97,68,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,55,71,49,48,53,32,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "GD105Kkaconvknr.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FGD105Kkaconvknr.sqc
 *     �@�\�T�v  �F���ʕϊ��Ǘ����A�N�Z�X�֐�(�񍐏���)
 *
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2009-05-11                    Create
 **********************************************************************/

/********************************************************************/
/*  �C���N���[�h�錾                                                */
/********************************************************************/
#include <stdio.h>
#include "GD105Kkaconvknr.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"
#include "bmllog.h"

#define	RETRY			3		// ���g���C��
#define	ERR_LOCK		-911	// �f�b�h���b�N���G���[�R�[�h
#define	LOCK_WAIT_SEC	5		// �X���[�v�P�ʁF�b

#define	ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 33 "GD105Kkaconvknr.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 38 "GD105Kkaconvknr.sqc"

	char		knskisymd[10+1];	/* �����J�n��     */
	char		sriymd[10+1];		/* ������         */
	char		kntno[13+1];		/* ����No         */
	char		knsgrp[16+1];		/* �����O���[�v   */
	char		kmkcd[7+1];			/* ���ڃR�[�h     */
	short		knssu;				/* ������       */
	short		hkksu;				/* �񍐉�       */
	char		sstcd[7+1];			/* �{�݃R�[�h     */
	sqlint32	no;					/* No             */
	char		utkymd[10+1];		/* ��t��         */
	char		irino[11+1];		/* �˗���No       */
	char		knskka1[12+1];		/* �������ʂP     */
	char		knskka2[24+1];		/* �������ʂQ     */
	char		knskka2kbn[2+1];	/* �������ʂQ�敪 */
	char		kkahskcd[3+1];		/* �������ʕ⑫   */
	char		skkka[24+1];		/* �Ɖ��       */
	char		sbtkbn;				/* ���ʋ敪       */
	char		age[3+1];			/* �N��           */
	char		agekbn;				/* �N��敪       */
	char		sc[5+1];			/* �g��           */
	char		tj[5+1];			/* �̏d           */
	char		tjtni;				/* �̏d�敪       */
	char		tntme[4+1];			/* �~�A����       */
	char		tntni;				/* �~�A���ԋ敪   */
	char		tnryo[5+1];			/* �~�A��         */
	char		tnryotni;			/* �~�A�ʋ敪     */
	char		hnktntid[8+1];		/* �ύX�S���҂h�c */
	char		ksndh[26+1];		/* ���X�V����   */

/*
EXEC SQL END DECLARE SECTION;
*/

#line 67 "GD105Kkaconvknr.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Kkaconvknr

BmlDMMInfo	KkaconvknrArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSHORT( knssu ),
	DMM_SSHORT( hkksu ),
	DMM_SSTRING( sstcd ),
	DMM_SLONG( no ),
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SSTRING( knskka1 ),
	DMM_SSTRING( knskka2 ),
	DMM_SSTRING( knskka2kbn ),
	DMM_SSTRING( kkahskcd ),
	DMM_SSTRING( skkka ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_SSTRING( sc ),
	DMM_SSTRING( tj ),
	DMM_SCHAR( tjtni ),
	DMM_SSTRING( tntme ),
	DMM_SCHAR( tntni ),
	DMM_SSTRING( tnryo ),
	DMM_SCHAR( tnryotni ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * dGD105InsKkaconvknr()
 *    KKACONVKNR �C���T�[�g����
 * ������
 *    [I]    Kkaconvknr** arrayIn   �擾���R�[�h�z��i�[�̈�
 * ���߂�l
 *    (long) HRC_SQL_NORMAL(0)      ����I��
 *           HRC_NULL_POINTER(-3)   �p�����[�^�G���[
 *           HRC_INVALID_VALUE(-1)  �ݒ�l�s��
 *           HRC_SQL_ERR(-2)        DB�G���[
 ******************************************************************************/
long dGD105InsKkaconvknr( Kkaconvknr* arrayIn )
{
#ifdef _DEBUG
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				 "�� dGD105InsKkaconvknr ������" ) ;
#endif

	if( !arrayIn ) {
		return HRC_NULL_POINTER;
	}

	if( !ZbmlMapStructToHost( (char*)arrayIn, KkaconvknrArray ) ) {
		return HRC_INVALID_VALUE;
	}

#ifdef _DEBUG
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    knskisymd  = [%s]", knskisymd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    sriymd     = [%s]", sriymd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    kntno      = [%s]", kntno ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    knsgrp     = [%s]", knsgrp ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    kmkcd      = [%s]", kmkcd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    knssu      = [%d]", knssu ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    hkksu      = [%d]", hkksu ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    sstcd      = [%s]", sstcd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    no         = [%d]", no ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    utkymd     = [%s]", utkymd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    irino      = [%s]", irino ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    knskka1    = [%s]", knskka1 ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    knskka2    = [%s]", knskka2 ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    knskka2kbn = [%s]", knskka2kbn ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    kkahskcd   = [%s]", kkahskcd ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    skkka      = [%s]", skkka ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    sbtkbn     = [%c]", sbtkbn ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    age        = [%s]", age ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    agekbn     = [%c]", agekbn ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    sc         = [%s]", sc ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    tj         = [%s]", tj ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    tjtni      = [%c]", tjtni ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    tntme      = [%s]", tntme ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    tntni      = [%c]", tntni ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    tnryo      = [%s]", tnryo ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    tnryotni   = [%c]", tnryotni ) ;
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				"    hnktntid   = [%s]", hnktntid ) ;
#endif

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 190 "GD105Kkaconvknr.sqc"


    
/*
EXEC SQL INSERT INTO KKACONVKNR
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNSGRP,
		KMKCD,
		KNSSU,
		HKKSU,
		SSTCD,
		NO,
		UTKYMD,
		IRINO,
		KNSKKA1,
		KNSKKA2,
		KNSKKA2KBN,
		KKAHSKCD,
		SKKKA,
		SBTKBN,
		AGE,
		AGEKBN,
		SC,
		TJ,
		TJTNI,
		TNTME,
		TNTNI,
		TNRYO,
		TNRYOTNI,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knskisymd,
		:sriymd,
		:kntno,
		:knsgrp,
		:kmkcd,
		:knssu,
		:hkksu,
		:sstcd,
		:no,
		:utkymd,
		:irino,
		:knskka1,
		:knskka2,
		:knskka2kbn,
		:kkahskcd,
		:skkka,
		:sbtkbn,
		:age,
		:agekbn,
		:sc,
		:tj,
		:tjtni,
		:tntme,
		:tntni,
		:tnryo,
		:tnryotni,
		:hnktntid,
		CURRENT TIMESTAMP
    );
*/

{
#line 251 "GD105Kkaconvknr.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 251 "GD105Kkaconvknr.sqc"
  sqlaaloc(2,27,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[27];
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[4].sqldata = (void*)kmkcd;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[5].sqldata = (void*)&knssu;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[6].sqldata = (void*)&hkksu;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[7].sqldata = (void*)sstcd;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[8].sqldata = (void*)&no;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[9].sqldata = (void*)utkymd;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 12;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[10].sqldata = (void*)irino;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 13;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[11].sqldata = (void*)knskka1;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 25;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[12].sqldata = (void*)knskka2;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 3;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[13].sqldata = (void*)knskka2kbn;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 4;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[14].sqldata = (void*)kkahskcd;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 25;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[15].sqldata = (void*)skkka;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[16].sqltype = 452; sql_setdlist[16].sqllen = 1;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[16].sqldata = (void*)&sbtkbn;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 4;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[17].sqldata = (void*)age;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[18].sqltype = 452; sql_setdlist[18].sqllen = 1;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[18].sqldata = (void*)&agekbn;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 6;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[19].sqldata = (void*)sc;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 6;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[20].sqldata = (void*)tj;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[21].sqltype = 452; sql_setdlist[21].sqllen = 1;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[21].sqldata = (void*)&tjtni;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 5;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[22].sqldata = (void*)tntme;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[23].sqldata = (void*)&tntni;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 6;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[24].sqldata = (void*)tnryo;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[25].sqldata = (void*)&tnryotni;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[26].sqldata = (void*)hnktntid;
#line 251 "GD105Kkaconvknr.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 251 "GD105Kkaconvknr.sqc"
      sqlasetdata(2,0,27,sql_setdlist,0L,0L);
    }
#line 251 "GD105Kkaconvknr.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 251 "GD105Kkaconvknr.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 251 "GD105Kkaconvknr.sqc"
  sqlastop(0L);
}

#line 251 "GD105Kkaconvknr.sqc"


#ifdef _DEBUG
	sFncPutLog ( TRCKIND_DEBUG, __FILE__, "dGD105InsKkaconvknr", __LINE__, EXEFLG_INS, "020",
				 "dGD105InsKkaconvknr �o��" ) ;
#endif

    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 261 "GD105Kkaconvknr.sqc"

    return sqlca.sqlcode;

}

/** End of File *********************************************************/
