static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,67,66,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,50,90,77,69,77,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Memst.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Memst.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Memst.h"
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


#line 24 "Memst.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Memst.sqc"

	char    bskkbn[5];
	char    bsklne[5];
	char    bskgok[7];
	char    bsknm[41];
	char    bskrs[21];
	char    goknm[21];
	sqlint32  sktmax;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 41 "Memst.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Memst

BmlDMMInfo	MemstArray[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bsklne ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( bsknm ),
	DMM_SSTRING( bskrs ),
	DMM_SSTRING( goknm ),
	DMM_SLONG( sktmax ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbMemstSelectAll()
 *    MEMST ���R�[�h�S���擾
 * ������
 *    [O]  Memst** arrayOut     �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMemstSelectAll( Memst** arrayOut, int* numOut )
{
    Memst*      array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 80 "Memst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKNM,
		BSKRS,
		GOKNM,
		SKTMAX,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        MEMST FOR READ ONLY;
*/

#line 96 "Memst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 98 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Memst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 98 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Memst.sqc"
  sqlastop(0L);
}

#line 98 "Memst.sqc"


    while( 1 ) {
        Memst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:bskkbn,
			:bsklne,
			:bskgok,
			:bsknm,
			:bskrs,
			:goknm,
			:sktmax,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 114 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 114 "Memst.sqc"
  sqlaaloc(3,11,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 114 "Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 114 "Memst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 114 "Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 114 "Memst.sqc"
      sql_setdlist[1].sqldata = (void*)bsklne;
#line 114 "Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 114 "Memst.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 114 "Memst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 114 "Memst.sqc"
      sql_setdlist[3].sqldata = (void*)bsknm;
#line 114 "Memst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 114 "Memst.sqc"
      sql_setdlist[4].sqldata = (void*)bskrs;
#line 114 "Memst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 114 "Memst.sqc"
      sql_setdlist[5].sqldata = (void*)goknm;
#line 114 "Memst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 114 "Memst.sqc"
      sql_setdlist[6].sqldata = (void*)&sktmax;
#line 114 "Memst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 114 "Memst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 114 "Memst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 114 "Memst.sqc"
      sql_setdlist[8].sqldata = (void*)haiymd;
#line 114 "Memst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 114 "Memst.sqc"
      sql_setdlist[9].sqldata = (void*)hnktntid;
#line 114 "Memst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 114 "Memst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 114 "Memst.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 114 "Memst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 114 "Memst.sqc"
      sqlasetdata(3,0,11,sql_setdlist,0L,0L);
    }
#line 114 "Memst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 114 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 114 "Memst.sqc"
  sqlastop(0L);
}

#line 114 "Memst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Memst*)ZbmlRealloc( array,
                                    sizeof( Memst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Memst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MemstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 129 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 129 "Memst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 129 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 129 "Memst.sqc"
  sqlastop(0L);
}

#line 129 "Memst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 137 "Memst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbMemstSelectKey()
 *    MEMST ���R�[�hKey�����擾
 * ������
 *    [I]  Memst* pKey       �擾���郌�R�[�h�̃L�[
 *    [O]  Memst** arrayOut     �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMemstSelectKey( Memst* pKey, Memst** arrayOut, int* numOut )
{
    Memst*      array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, MemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 163 "Memst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKNM,
		BSKRS,
		GOKNM,
		SKTMAX,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        MEMST
    WHERE
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 184 "Memst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 186 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 186 "Memst.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 186 "Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 186 "Memst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 186 "Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 186 "Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 186 "Memst.sqc"
      sql_setdlist[1].sqldata = (void*)bsklne;
#line 186 "Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 186 "Memst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 186 "Memst.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 186 "Memst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 186 "Memst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 186 "Memst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 186 "Memst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 186 "Memst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 186 "Memst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 186 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 186 "Memst.sqc"
  sqlastop(0L);
}

#line 186 "Memst.sqc"


    while( 1 ) {
        Memst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:bsklne,
			:bskgok,
			:bsknm,
			:bskrs,
			:goknm,
			:sktmax,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 202 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 202 "Memst.sqc"
  sqlaaloc(3,11,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 202 "Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 202 "Memst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 202 "Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 202 "Memst.sqc"
      sql_setdlist[1].sqldata = (void*)bsklne;
#line 202 "Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 202 "Memst.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 202 "Memst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 202 "Memst.sqc"
      sql_setdlist[3].sqldata = (void*)bsknm;
#line 202 "Memst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 202 "Memst.sqc"
      sql_setdlist[4].sqldata = (void*)bskrs;
#line 202 "Memst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 202 "Memst.sqc"
      sql_setdlist[5].sqldata = (void*)goknm;
#line 202 "Memst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 202 "Memst.sqc"
      sql_setdlist[6].sqldata = (void*)&sktmax;
#line 202 "Memst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 202 "Memst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 202 "Memst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 202 "Memst.sqc"
      sql_setdlist[8].sqldata = (void*)haiymd;
#line 202 "Memst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 202 "Memst.sqc"
      sql_setdlist[9].sqldata = (void*)hnktntid;
#line 202 "Memst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 202 "Memst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 202 "Memst.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 202 "Memst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 202 "Memst.sqc"
      sqlasetdata(3,0,11,sql_setdlist,0L,0L);
    }
#line 202 "Memst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 202 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 202 "Memst.sqc"
  sqlastop(0L);
}

#line 202 "Memst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Memst*)ZbmlRealloc( array,
                                    sizeof( Memst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Memst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MemstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 217 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 217 "Memst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 217 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 217 "Memst.sqc"
  sqlastop(0L);
}

#line 217 "Memst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 225 "Memst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMemstInsert()
 *    MEMST ���R�[�h��}������
 * ������
 *    [I]  Memst* rec       �}�����R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMemstInsert( Memst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 248 "Memst.sqc"


    
/*
EXEC SQL INSERT INTO MEMST
    (
		BSKKBN,
		BSKLNE,
		BSKGOK,
		BSKNM,
		BSKRS,
		GOKNM,
		SKTMAX,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:bskkbn,
		:bsklne,
		:bskgok,
		:bsknm,
		:bskrs,
		:goknm,
		:sktmax,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 275 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 275 "Memst.sqc"
  sqlaaloc(2,11,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 275 "Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 275 "Memst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 275 "Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 275 "Memst.sqc"
      sql_setdlist[1].sqldata = (void*)bsklne;
#line 275 "Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 275 "Memst.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 275 "Memst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 41;
#line 275 "Memst.sqc"
      sql_setdlist[3].sqldata = (void*)bsknm;
#line 275 "Memst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 275 "Memst.sqc"
      sql_setdlist[4].sqldata = (void*)bskrs;
#line 275 "Memst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 275 "Memst.sqc"
      sql_setdlist[5].sqldata = (void*)goknm;
#line 275 "Memst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 275 "Memst.sqc"
      sql_setdlist[6].sqldata = (void*)&sktmax;
#line 275 "Memst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 275 "Memst.sqc"
      sql_setdlist[7].sqldata = (void*)kaiymd;
#line 275 "Memst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 275 "Memst.sqc"
      sql_setdlist[8].sqldata = (void*)haiymd;
#line 275 "Memst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 9;
#line 275 "Memst.sqc"
      sql_setdlist[9].sqldata = (void*)hnktntid;
#line 275 "Memst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 275 "Memst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 275 "Memst.sqc"
      sql_setdlist[10].sqldata = (void*)ksndh;
#line 275 "Memst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 275 "Memst.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 275 "Memst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 275 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 275 "Memst.sqc"
  sqlastop(0L);
}

#line 275 "Memst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 280 "Memst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMemstUpdate()
 *    MEMST ���R�[�h���X�V����
 * ������
 *    [I]  Memst* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMemstUpdate( Memst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 304 "Memst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 305 "Memst.sqc"


    
/*
EXEC SQL UPDATE MEMST
    SET (
		BSKNM,
		BSKRS,
		GOKNM,
		SKTMAX,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:bsknm,
		:bskrs,
		:goknm,
		:sktmax,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		KAIYMD = :kaiymd;
*/

{
#line 328 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 328 "Memst.sqc"
  sqlaaloc(2,11,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 328 "Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 328 "Memst.sqc"
      sql_setdlist[0].sqldata = (void*)bsknm;
#line 328 "Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 328 "Memst.sqc"
      sql_setdlist[1].sqldata = (void*)bskrs;
#line 328 "Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 328 "Memst.sqc"
      sql_setdlist[2].sqldata = (void*)goknm;
#line 328 "Memst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 328 "Memst.sqc"
      sql_setdlist[3].sqldata = (void*)&sktmax;
#line 328 "Memst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 328 "Memst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 328 "Memst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 328 "Memst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 328 "Memst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 328 "Memst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 328 "Memst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 328 "Memst.sqc"
      sql_setdlist[7].sqldata = (void*)bskkbn;
#line 328 "Memst.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 5;
#line 328 "Memst.sqc"
      sql_setdlist[8].sqldata = (void*)bsklne;
#line 328 "Memst.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 7;
#line 328 "Memst.sqc"
      sql_setdlist[9].sqldata = (void*)bskgok;
#line 328 "Memst.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 328 "Memst.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 11;
#line 328 "Memst.sqc"
      sql_setdlist[10].sqldata = (void*)kaiymd;
#line 328 "Memst.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 328 "Memst.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 328 "Memst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 328 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 328 "Memst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 328 "Memst.sqc"
  sqlastop(0L);
}

#line 328 "Memst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 333 "Memst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 337 "Memst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMemstDelete()
 *    MEMST ���R�[�h���폜����
 * ������
 *    [I]  Memst* rec       �폜�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMemstDelete( Memst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 361 "Memst.sqc"


    
/*
EXEC SQL DELETE FROM MEMST
    WHERE
		BSKKBN = :bskkbn AND
		BSKLNE = :bsklne AND
		BSKGOK = :bskgok AND
		KAIYMD = :kaiymd;
*/

{
#line 368 "Memst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 368 "Memst.sqc"
  sqlaaloc(2,4,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 368 "Memst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 368 "Memst.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 368 "Memst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 368 "Memst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 368 "Memst.sqc"
      sql_setdlist[1].sqldata = (void*)bsklne;
#line 368 "Memst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 368 "Memst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 7;
#line 368 "Memst.sqc"
      sql_setdlist[2].sqldata = (void*)bskgok;
#line 368 "Memst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 368 "Memst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 368 "Memst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 368 "Memst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 368 "Memst.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 368 "Memst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 368 "Memst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 368 "Memst.sqc"
  sqlastop(0L);
}

#line 368 "Memst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 373 "Memst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
