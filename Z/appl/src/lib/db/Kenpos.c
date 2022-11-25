static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,89,66,83,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,49,90,75,69,78,80,32,0,0,0,0,0,0,0,0,
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


#line 1 "Kenpos.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Kenpos.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kenpos.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 24 "Kenpos.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Kenpos.sqc"

	char    knskisymd[11];
	char    sriymd[11];
	char    kntno[14];
	char    kntketflg;
	char    knndh[27];
	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    trid[11];
	short   trpos;
	char    asyrckid[11];
	short   asyrckpos;
	char    rakitjho;
	char    rakitjhossi[7];
	char    ksndh[27];
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 47 "Kenpos.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Kenpos

BmlDMMInfo	KenposArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( kntno ),
	DMM_SCHAR( kntketflg ),
	DMM_STIMESTAMP( knndh ),
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( trid ),
	DMM_SSHORT( trpos ),
	DMM_SSTRING( asyrckid ),
	DMM_SSHORT( asyrckpos ),
	DMM_SCHAR( rakitjho ),
	DMM_SSTRING( rakitjhossi ),
	DMM_STIMESTAMP( ksndh ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKenposSelectAll()
 *    KENPOS ���R�[�h�S���擾
 * ������
 *    [O]  Kenpos** arrayOut    �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKenposSelectAll( Kenpos** arrayOut, int* numOut )
{
    Kenpos*     array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 92 "Kenpos.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNNDH,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		RAKITJHO,
		RAKITJHOSSI,
		KSNDH,
		TRKDH
    FROM
        KENPOS FOR READ ONLY;
*/

#line 114 "Kenpos.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 116 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 116 "Kenpos.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 116 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 116 "Kenpos.sqc"
  sqlastop(0L);
}

#line 116 "Kenpos.sqc"


    while( 1 ) {
        Kenpos* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knndh,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:rakitjho,
			:rakitjhossi,
			:ksndh,
			:trkdh;
*/

{
#line 138 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 138 "Kenpos.sqc"
  sqlaaloc(3,17,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[17];
#line 138 "Kenpos.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 138 "Kenpos.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 138 "Kenpos.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 138 "Kenpos.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 138 "Kenpos.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 138 "Kenpos.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 138 "Kenpos.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 138 "Kenpos.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 138 "Kenpos.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 138 "Kenpos.sqc"
      sql_setdlist[4].sqldata = (void*)knndh;
#line 138 "Kenpos.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 138 "Kenpos.sqc"
      sql_setdlist[5].sqldata = (void*)utkymd;
#line 138 "Kenpos.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 12;
#line 138 "Kenpos.sqc"
      sql_setdlist[6].sqldata = (void*)irino;
#line 138 "Kenpos.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 138 "Kenpos.sqc"
      sql_setdlist[7].sqldata = (void*)&iriketflg;
#line 138 "Kenpos.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 138 "Kenpos.sqc"
      sql_setdlist[8].sqldata = (void*)&zssdino;
#line 138 "Kenpos.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 138 "Kenpos.sqc"
      sql_setdlist[9].sqldata = (void*)trid;
#line 138 "Kenpos.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 138 "Kenpos.sqc"
      sql_setdlist[10].sqldata = (void*)&trpos;
#line 138 "Kenpos.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 138 "Kenpos.sqc"
      sql_setdlist[11].sqldata = (void*)asyrckid;
#line 138 "Kenpos.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 138 "Kenpos.sqc"
      sql_setdlist[12].sqldata = (void*)&asyrckpos;
#line 138 "Kenpos.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 138 "Kenpos.sqc"
      sql_setdlist[13].sqldata = (void*)&rakitjho;
#line 138 "Kenpos.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 138 "Kenpos.sqc"
      sql_setdlist[14].sqldata = (void*)rakitjhossi;
#line 138 "Kenpos.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 138 "Kenpos.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 138 "Kenpos.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 138 "Kenpos.sqc"
      sql_setdlist[16].sqldata = (void*)trkdh;
#line 138 "Kenpos.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 138 "Kenpos.sqc"
      sqlasetdata(3,0,17,sql_setdlist,0L,0L);
    }
#line 138 "Kenpos.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 138 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 138 "Kenpos.sqc"
  sqlastop(0L);
}

#line 138 "Kenpos.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kenpos*)ZbmlRealloc( array,
                                    sizeof( Kenpos ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kenpos ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KenposArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 153 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 153 "Kenpos.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 153 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 153 "Kenpos.sqc"
  sqlastop(0L);
}

#line 153 "Kenpos.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 161 "Kenpos.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKenposSelectKey()
 *    KENPOS ���R�[�hKey�����擾
 * ������
 *    [I]  Kenpos* pKey       �擾���郌�R�[�h�̃L�[
 *    [O]  Kenpos** arrayOut    �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKenposSelectKey( Kenpos* pKey, Kenpos** arrayOut, int* numOut )
{
    Kenpos*     array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KenposArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 187 "Kenpos.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNNDH,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		RAKITJHO,
		RAKITJHOSSI,
		KSNDH,
		TRKDH
    FROM
        KENPOS
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno
		FOR READ ONLY;
*/

#line 214 "Kenpos.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 216 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 216 "Kenpos.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 216 "Kenpos.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 216 "Kenpos.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 216 "Kenpos.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 216 "Kenpos.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 216 "Kenpos.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 216 "Kenpos.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 216 "Kenpos.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 216 "Kenpos.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 216 "Kenpos.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 216 "Kenpos.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 216 "Kenpos.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 216 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 216 "Kenpos.sqc"
  sqlastop(0L);
}

#line 216 "Kenpos.sqc"


    while( 1 ) {
        Kenpos* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:sriymd,
			:kntno,
			:kntketflg,
			:knndh,
			:utkymd,
			:irino,
			:iriketflg,
			:zssdino,
			:trid,
			:trpos,
			:asyrckid,
			:asyrckpos,
			:rakitjho,
			:rakitjhossi,
			:ksndh,
			:trkdh;
*/

{
#line 238 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 238 "Kenpos.sqc"
  sqlaaloc(3,17,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[17];
#line 238 "Kenpos.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 238 "Kenpos.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 238 "Kenpos.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 238 "Kenpos.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 238 "Kenpos.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 238 "Kenpos.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 238 "Kenpos.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 238 "Kenpos.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 238 "Kenpos.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 238 "Kenpos.sqc"
      sql_setdlist[4].sqldata = (void*)knndh;
#line 238 "Kenpos.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 238 "Kenpos.sqc"
      sql_setdlist[5].sqldata = (void*)utkymd;
#line 238 "Kenpos.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 12;
#line 238 "Kenpos.sqc"
      sql_setdlist[6].sqldata = (void*)irino;
#line 238 "Kenpos.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 238 "Kenpos.sqc"
      sql_setdlist[7].sqldata = (void*)&iriketflg;
#line 238 "Kenpos.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 238 "Kenpos.sqc"
      sql_setdlist[8].sqldata = (void*)&zssdino;
#line 238 "Kenpos.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 238 "Kenpos.sqc"
      sql_setdlist[9].sqldata = (void*)trid;
#line 238 "Kenpos.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 238 "Kenpos.sqc"
      sql_setdlist[10].sqldata = (void*)&trpos;
#line 238 "Kenpos.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 238 "Kenpos.sqc"
      sql_setdlist[11].sqldata = (void*)asyrckid;
#line 238 "Kenpos.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 238 "Kenpos.sqc"
      sql_setdlist[12].sqldata = (void*)&asyrckpos;
#line 238 "Kenpos.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 238 "Kenpos.sqc"
      sql_setdlist[13].sqldata = (void*)&rakitjho;
#line 238 "Kenpos.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 238 "Kenpos.sqc"
      sql_setdlist[14].sqldata = (void*)rakitjhossi;
#line 238 "Kenpos.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 238 "Kenpos.sqc"
      sql_setdlist[15].sqldata = (void*)ksndh;
#line 238 "Kenpos.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 238 "Kenpos.sqc"
      sql_setdlist[16].sqldata = (void*)trkdh;
#line 238 "Kenpos.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 238 "Kenpos.sqc"
      sqlasetdata(3,0,17,sql_setdlist,0L,0L);
    }
#line 238 "Kenpos.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 238 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 238 "Kenpos.sqc"
  sqlastop(0L);
}

#line 238 "Kenpos.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kenpos*)ZbmlRealloc( array,
                                    sizeof( Kenpos ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kenpos ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KenposArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 253 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 253 "Kenpos.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 253 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 253 "Kenpos.sqc"
  sqlastop(0L);
}

#line 253 "Kenpos.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 261 "Kenpos.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenposInsert()
 *    KENPOS ���R�[�h��}������
 * ������
 *    [I]  Kenpos* rec       �}�����R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKenposInsert( Kenpos* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenposArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 284 "Kenpos.sqc"


    
/*
EXEC SQL INSERT INTO KENPOS
    (
		KNSKISYMD,
		SRIYMD,
		KNTNO,
		KNTKETFLG,
		KNNDH,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		RAKITJHO,
		RAKITJHOSSI,
		KSNDH,
		TRKDH
    ) VALUES (
		:knskisymd,
		:sriymd,
		:kntno,
		:kntketflg,
		:knndh,
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:rakitjho,
		:rakitjhossi,
		CURRENT TIMESTAMP,
		CURRENT TIMESTAMP
    );
*/

{
#line 323 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 323 "Kenpos.sqc"
  sqlaaloc(2,15,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[15];
#line 323 "Kenpos.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 323 "Kenpos.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 323 "Kenpos.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 323 "Kenpos.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 323 "Kenpos.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 323 "Kenpos.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 323 "Kenpos.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 323 "Kenpos.sqc"
      sql_setdlist[3].sqldata = (void*)&kntketflg;
#line 323 "Kenpos.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 323 "Kenpos.sqc"
      sql_setdlist[4].sqldata = (void*)knndh;
#line 323 "Kenpos.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 323 "Kenpos.sqc"
      sql_setdlist[5].sqldata = (void*)utkymd;
#line 323 "Kenpos.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 12;
#line 323 "Kenpos.sqc"
      sql_setdlist[6].sqldata = (void*)irino;
#line 323 "Kenpos.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 323 "Kenpos.sqc"
      sql_setdlist[7].sqldata = (void*)&iriketflg;
#line 323 "Kenpos.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[8].sqltype = 500; sql_setdlist[8].sqllen = 2;
#line 323 "Kenpos.sqc"
      sql_setdlist[8].sqldata = (void*)&zssdino;
#line 323 "Kenpos.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 11;
#line 323 "Kenpos.sqc"
      sql_setdlist[9].sqldata = (void*)trid;
#line 323 "Kenpos.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 323 "Kenpos.sqc"
      sql_setdlist[10].sqldata = (void*)&trpos;
#line 323 "Kenpos.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 11;
#line 323 "Kenpos.sqc"
      sql_setdlist[11].sqldata = (void*)asyrckid;
#line 323 "Kenpos.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 323 "Kenpos.sqc"
      sql_setdlist[12].sqldata = (void*)&asyrckpos;
#line 323 "Kenpos.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[13].sqltype = 452; sql_setdlist[13].sqllen = 1;
#line 323 "Kenpos.sqc"
      sql_setdlist[13].sqldata = (void*)&rakitjho;
#line 323 "Kenpos.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 7;
#line 323 "Kenpos.sqc"
      sql_setdlist[14].sqldata = (void*)rakitjhossi;
#line 323 "Kenpos.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 323 "Kenpos.sqc"
      sqlasetdata(2,0,15,sql_setdlist,0L,0L);
    }
#line 323 "Kenpos.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 323 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 323 "Kenpos.sqc"
  sqlastop(0L);
}

#line 323 "Kenpos.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 328 "Kenpos.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenposUpdate()
 *    KENPOS ���R�[�h���X�V����
 * ������
 *    [I]  Kenpos* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKenposUpdate( Kenpos* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenposArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 352 "Kenpos.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 353 "Kenpos.sqc"


    
/*
EXEC SQL UPDATE KENPOS
    SET (
		KNTKETFLG,
		KNNDH,
		UTKYMD,
		IRINO,
		IRIKETFLG,
		ZSSDINO,
		TRID,
		TRPOS,
		ASYRCKID,
		ASYRCKPOS,
		RAKITJHO,
		RAKITJHOSSI,
		KSNDH,
		TRKDH
    ) = (
		:kntketflg,
		:knndh,
		:utkymd,
		:irino,
		:iriketflg,
		:zssdino,
		:trid,
		:trpos,
		:asyrckid,
		:asyrckpos,
		:rakitjho,
		:rakitjhossi,
		CURRENT TIMESTAMP,
		:trkdh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno;
*/

{
#line 389 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 389 "Kenpos.sqc"
  sqlaaloc(2,16,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[16];
#line 389 "Kenpos.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 389 "Kenpos.sqc"
      sql_setdlist[0].sqldata = (void*)&kntketflg;
#line 389 "Kenpos.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 389 "Kenpos.sqc"
      sql_setdlist[1].sqldata = (void*)knndh;
#line 389 "Kenpos.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 389 "Kenpos.sqc"
      sql_setdlist[2].sqldata = (void*)utkymd;
#line 389 "Kenpos.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 12;
#line 389 "Kenpos.sqc"
      sql_setdlist[3].sqldata = (void*)irino;
#line 389 "Kenpos.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 389 "Kenpos.sqc"
      sql_setdlist[4].sqldata = (void*)&iriketflg;
#line 389 "Kenpos.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 389 "Kenpos.sqc"
      sql_setdlist[5].sqldata = (void*)&zssdino;
#line 389 "Kenpos.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 389 "Kenpos.sqc"
      sql_setdlist[6].sqldata = (void*)trid;
#line 389 "Kenpos.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[7].sqltype = 500; sql_setdlist[7].sqllen = 2;
#line 389 "Kenpos.sqc"
      sql_setdlist[7].sqldata = (void*)&trpos;
#line 389 "Kenpos.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 389 "Kenpos.sqc"
      sql_setdlist[8].sqldata = (void*)asyrckid;
#line 389 "Kenpos.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[9].sqltype = 500; sql_setdlist[9].sqllen = 2;
#line 389 "Kenpos.sqc"
      sql_setdlist[9].sqldata = (void*)&asyrckpos;
#line 389 "Kenpos.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 389 "Kenpos.sqc"
      sql_setdlist[10].sqldata = (void*)&rakitjho;
#line 389 "Kenpos.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 7;
#line 389 "Kenpos.sqc"
      sql_setdlist[11].sqldata = (void*)rakitjhossi;
#line 389 "Kenpos.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 389 "Kenpos.sqc"
      sql_setdlist[12].sqldata = (void*)trkdh;
#line 389 "Kenpos.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 11;
#line 389 "Kenpos.sqc"
      sql_setdlist[13].sqldata = (void*)knskisymd;
#line 389 "Kenpos.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 11;
#line 389 "Kenpos.sqc"
      sql_setdlist[14].sqldata = (void*)sriymd;
#line 389 "Kenpos.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 14;
#line 389 "Kenpos.sqc"
      sql_setdlist[15].sqldata = (void*)kntno;
#line 389 "Kenpos.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 389 "Kenpos.sqc"
      sqlasetdata(2,0,16,sql_setdlist,0L,0L);
    }
#line 389 "Kenpos.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 389 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 389 "Kenpos.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 389 "Kenpos.sqc"
  sqlastop(0L);
}

#line 389 "Kenpos.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 394 "Kenpos.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 398 "Kenpos.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKenposDelete()
 *    KENPOS ���R�[�h���폜����
 * ������
 *    [I]  Kenpos* rec       �폜�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKenposDelete( Kenpos* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KenposArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 422 "Kenpos.sqc"


    
/*
EXEC SQL DELETE FROM KENPOS
    WHERE
		KNSKISYMD = :knskisymd AND
		SRIYMD = :sriymd AND
		KNTNO = :kntno;
*/

{
#line 428 "Kenpos.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 428 "Kenpos.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 428 "Kenpos.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 428 "Kenpos.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 428 "Kenpos.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 428 "Kenpos.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 428 "Kenpos.sqc"
      sql_setdlist[1].sqldata = (void*)sriymd;
#line 428 "Kenpos.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 428 "Kenpos.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 14;
#line 428 "Kenpos.sqc"
      sql_setdlist[2].sqldata = (void*)kntno;
#line 428 "Kenpos.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 428 "Kenpos.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 428 "Kenpos.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 428 "Kenpos.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 428 "Kenpos.sqc"
  sqlastop(0L);
}

#line 428 "Kenpos.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 433 "Kenpos.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
