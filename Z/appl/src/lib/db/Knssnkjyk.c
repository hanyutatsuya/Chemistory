static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,81,65,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,54,90,75,78,83,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Knssnkjyk.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Knssnkjyk.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Knssnkjyk.h"
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


#line 24 "Knssnkjyk.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Knssnkjyk.sqc"

	char    knskisymd[11];
	sqlint32  keikseq;
	char    koteikbn;
	char    datazok;
	char    bskkbn[5];
	char    bskgok[7];
	sqlint32  syukka;
	char    jikan[5];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 39 "Knssnkjyk.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Knssnkjyk

BmlDMMInfo	KnssnkjykArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SLONG( keikseq ),
	DMM_SCHAR( koteikbn ),
	DMM_SCHAR( datazok ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bskgok ),
	DMM_SLONG( syukka ),
	DMM_SSTRING( jikan ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKnssnkjykSelectAll()
 *    KNSSNKJYK ���R�[�h�S���擾
 * ������
 *    [O]  Knssnkjyk** arrayOut �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnssnkjykSelectAll( Knssnkjyk** arrayOut, int* numOut )
{
    Knssnkjyk*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 76 "Knssnkjyk.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		KEIKSEQ,
		KOTEIKBN,
		DATAZOK,
		BSKKBN,
		BSKGOK,
		SYUKKA,
		JIKAN,
		KSNDH
    FROM
        KNSSNKJYK FOR READ ONLY;
*/

#line 90 "Knssnkjyk.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 92 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 92 "Knssnkjyk.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 92 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 92 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 92 "Knssnkjyk.sqc"


    while( 1 ) {
        Knssnkjyk* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:keikseq,
			:koteikbn,
			:datazok,
			:bskkbn,
			:bskgok,
			:syukka,
			:jikan,
			:ksndh;
*/

{
#line 106 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 106 "Knssnkjyk.sqc"
  sqlaaloc(3,9,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[6].sqldata = (void*)&syukka;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[7].sqldata = (void*)jikan;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 106 "Knssnkjyk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 106 "Knssnkjyk.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 106 "Knssnkjyk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 106 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 106 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 106 "Knssnkjyk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knssnkjyk*)ZbmlRealloc( array,
                                    sizeof( Knssnkjyk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knssnkjyk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnssnkjykArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 121 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 121 "Knssnkjyk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 121 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 121 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 121 "Knssnkjyk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 129 "Knssnkjyk.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKnssnkjykSelectKey()
 *    KNSSNKJYK ���R�[�hKey�����擾
 * ������
 *    [I]  Knssnkjyk* pKey      �擾���郌�R�[�h�̃L�[
 *    [O]  Knssnkjyk** arrayOut �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnssnkjykSelectKey( Knssnkjyk* pKey, Knssnkjyk** arrayOut, int* numOut )
{
    Knssnkjyk*  array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 155 "Knssnkjyk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		KEIKSEQ,
		KOTEIKBN,
		DATAZOK,
		BSKKBN,
		BSKGOK,
		SYUKKA,
		JIKAN,
		KSNDH
    FROM
        KNSSNKJYK
    WHERE
		KNSKISYMD = :knskisymd AND
		KEIKSEQ = :keikseq AND
		KOTEIKBN = :koteikbn AND
		DATAZOK = :datazok AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok FOR READ ONLY;
*/

#line 176 "Knssnkjyk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 178 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 178 "Knssnkjyk.sqc"
  sqlaaloc(2,6,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 178 "Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 178 "Knssnkjyk.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 178 "Knssnkjyk.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 178 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 178 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 178 "Knssnkjyk.sqc"


    while( 1 ) {
        Knssnkjyk* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:keikseq,
			:koteikbn,
			:datazok,
			:bskkbn,
			:bskgok,
			:syukka,
			:jikan,
			:ksndh;
*/

{
#line 192 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 192 "Knssnkjyk.sqc"
  sqlaaloc(3,9,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[6].sqldata = (void*)&syukka;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[7].sqldata = (void*)jikan;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 192 "Knssnkjyk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 192 "Knssnkjyk.sqc"
      sqlasetdata(3,0,9,sql_setdlist,0L,0L);
    }
#line 192 "Knssnkjyk.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 192 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 192 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 192 "Knssnkjyk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knssnkjyk*)ZbmlRealloc( array,
                                    sizeof( Knssnkjyk ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knssnkjyk ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnssnkjykArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 207 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 207 "Knssnkjyk.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 207 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 207 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 207 "Knssnkjyk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 215 "Knssnkjyk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnssnkjykInsert()
 *    KNSSNKJYK ���R�[�h��}������
 * ������
 *    [I]  Knssnkjyk* rec       �}�����R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnssnkjykInsert( Knssnkjyk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 238 "Knssnkjyk.sqc"


    
/*
EXEC SQL INSERT INTO KNSSNKJYK
    (
		KNSKISYMD,
		KEIKSEQ,
		KOTEIKBN,
		DATAZOK,
		BSKKBN,
		BSKGOK,
		SYUKKA,
		JIKAN,
		KSNDH
    ) VALUES (
		:knskisymd,
		:keikseq,
		:koteikbn,
		:datazok,
		:bskkbn,
		:bskgok,
		:syukka,
		:jikan,
		:ksndh
    );
*/

{
#line 261 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 261 "Knssnkjyk.sqc"
  sqlaaloc(2,9,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[6].sqldata = (void*)&syukka;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[7].sqldata = (void*)jikan;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[8].sqldata = (void*)ksndh;
#line 261 "Knssnkjyk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 261 "Knssnkjyk.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 261 "Knssnkjyk.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 261 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 261 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 261 "Knssnkjyk.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 266 "Knssnkjyk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnssnkjykUpdate()
 *    KNSSNKJYK ���R�[�h���X�V����
 * ������
 *    [I]  Knssnkjyk* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnssnkjykUpdate( Knssnkjyk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 290 "Knssnkjyk.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 291 "Knssnkjyk.sqc"


    
/*
EXEC SQL UPDATE KNSSNKJYK
    SET (
		SYUKKA,
		JIKAN,
		KSNDH
    ) = (
		:syukka,
		:jikan,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		KEIKSEQ = :keikseq AND
		KOTEIKBN = :koteikbn AND
		DATAZOK = :datazok AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok;
*/

{
#line 308 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 308 "Knssnkjyk.sqc"
  sqlaaloc(2,9,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)&syukka;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 5;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)jikan;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)knskisymd;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)&keikseq;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 452; sql_setdlist[5].sqllen = 1;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)&koteikbn;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[6].sqltype = 452; sql_setdlist[6].sqllen = 1;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[6].sqldata = (void*)&datazok;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 5;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[7].sqldata = (void*)bskkbn;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 7;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[8].sqldata = (void*)bskgok;
#line 308 "Knssnkjyk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 308 "Knssnkjyk.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 308 "Knssnkjyk.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 308 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 308 "Knssnkjyk.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 308 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 308 "Knssnkjyk.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 313 "Knssnkjyk.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 317 "Knssnkjyk.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnssnkjykDelete()
 *    KNSSNKJYK ���R�[�h���폜����
 * ������
 *    [I]  Knssnkjyk* rec       �폜�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnssnkjykDelete( Knssnkjyk* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnssnkjykArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 341 "Knssnkjyk.sqc"


    
/*
EXEC SQL DELETE FROM KNSSNKJYK
    WHERE
		KNSKISYMD = :knskisymd AND
		KEIKSEQ = :keikseq AND
		KOTEIKBN = :koteikbn AND
		DATAZOK = :datazok AND
		BSKKBN = :bskkbn AND
		BSKGOK = :bskgok;
*/

{
#line 350 "Knssnkjyk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 350 "Knssnkjyk.sqc"
  sqlaaloc(2,6,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[1].sqldata = (void*)&keikseq;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[2].sqldata = (void*)&koteikbn;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[3].sqldata = (void*)&datazok;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[4].sqldata = (void*)bskkbn;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 7;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[5].sqldata = (void*)bskgok;
#line 350 "Knssnkjyk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 350 "Knssnkjyk.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 350 "Knssnkjyk.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 350 "Knssnkjyk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 350 "Knssnkjyk.sqc"
  sqlastop(0L);
}

#line 350 "Knssnkjyk.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 355 "Knssnkjyk.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
