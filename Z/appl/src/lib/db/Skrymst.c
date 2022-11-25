static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,54,65,86,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,54,51,90,83,75,82,89,32,0,0,0,0,0,0,0,0,
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


#line 1 "Skrymst.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Skrymst.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Skrymst.h"
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


#line 24 "Skrymst.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Skrymst.sqc"

	char    skerr[4];
	char    skry[21];
	char    tkhkkbn;
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "Skrymst.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Skrymst

BmlDMMInfo	SkrymstArray[] = {
	DMM_SSTRING( skerr ),
	DMM_SSTRING( skry ),
	DMM_SCHAR( tkhkkbn ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbSkrymstSelectAll()
 *    SKRYMST ���R�[�h�S���擾
 * ������
 *    [O]  Skrymst** arrayOut   �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbSkrymstSelectAll( Skrymst** arrayOut, int* numOut )
{
    Skrymst*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 72 "Skrymst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		SKERR,
		SKRY,
		TKHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SKRYMST FOR READ ONLY;
*/

#line 84 "Skrymst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 86 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "Skrymst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 86 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 86 "Skrymst.sqc"
  sqlastop(0L);
}

#line 86 "Skrymst.sqc"


    while( 1 ) {
        Skrymst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:skerr,
			:skry,
			:tkhkkbn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 98 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Skrymst.sqc"
  sqlaaloc(3,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 98 "Skrymst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 98 "Skrymst.sqc"
      sql_setdlist[0].sqldata = (void*)skerr;
#line 98 "Skrymst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 98 "Skrymst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 98 "Skrymst.sqc"
      sql_setdlist[1].sqldata = (void*)skry;
#line 98 "Skrymst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 98 "Skrymst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 98 "Skrymst.sqc"
      sql_setdlist[2].sqldata = (void*)&tkhkkbn;
#line 98 "Skrymst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 98 "Skrymst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 98 "Skrymst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 98 "Skrymst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 98 "Skrymst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 98 "Skrymst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 98 "Skrymst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 98 "Skrymst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 98 "Skrymst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 98 "Skrymst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 98 "Skrymst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 98 "Skrymst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 98 "Skrymst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 98 "Skrymst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 98 "Skrymst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 98 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Skrymst.sqc"
  sqlastop(0L);
}

#line 98 "Skrymst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Skrymst*)ZbmlRealloc( array,
                                    sizeof( Skrymst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Skrymst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SkrymstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 113 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Skrymst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 113 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Skrymst.sqc"
  sqlastop(0L);
}

#line 113 "Skrymst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 121 "Skrymst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbSkrymstSelectKey()
 *    SKRYMST ���R�[�hKey�����擾
 * ������
 *    [I]  Skrymst* pKey       �擾���郌�R�[�h�̃L�[
 *    [O]  Skrymst** arrayOut   �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbSkrymstSelectKey( Skrymst* pKey, Skrymst** arrayOut, int* numOut )
{
    Skrymst*    array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, SkrymstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 147 "Skrymst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		SKERR,
		SKRY,
		TKHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        SKRYMST
    WHERE
		SKERR = :skerr AND
		KAIYMD <= :kaiymd FOR READ ONLY;
*/

#line 162 "Skrymst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 164 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "Skrymst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 164 "Skrymst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 164 "Skrymst.sqc"
      sql_setdlist[0].sqldata = (void*)skerr;
#line 164 "Skrymst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 164 "Skrymst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 164 "Skrymst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 164 "Skrymst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 164 "Skrymst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 164 "Skrymst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 164 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 164 "Skrymst.sqc"
  sqlastop(0L);
}

#line 164 "Skrymst.sqc"


    while( 1 ) {
        Skrymst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:skerr,
			:skry,
			:tkhkkbn,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 176 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 176 "Skrymst.sqc"
  sqlaaloc(3,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 176 "Skrymst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 176 "Skrymst.sqc"
      sql_setdlist[0].sqldata = (void*)skerr;
#line 176 "Skrymst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 176 "Skrymst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 176 "Skrymst.sqc"
      sql_setdlist[1].sqldata = (void*)skry;
#line 176 "Skrymst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 176 "Skrymst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 176 "Skrymst.sqc"
      sql_setdlist[2].sqldata = (void*)&tkhkkbn;
#line 176 "Skrymst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 176 "Skrymst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 176 "Skrymst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 176 "Skrymst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 176 "Skrymst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 176 "Skrymst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 176 "Skrymst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 176 "Skrymst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 176 "Skrymst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 176 "Skrymst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 176 "Skrymst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 176 "Skrymst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 176 "Skrymst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 176 "Skrymst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 176 "Skrymst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 176 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 176 "Skrymst.sqc"
  sqlastop(0L);
}

#line 176 "Skrymst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Skrymst*)ZbmlRealloc( array,
                                    sizeof( Skrymst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Skrymst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SkrymstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 191 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 191 "Skrymst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 191 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 191 "Skrymst.sqc"
  sqlastop(0L);
}

#line 191 "Skrymst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 199 "Skrymst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSkrymstInsert()
 *    SKRYMST ���R�[�h��}������
 * ������
 *    [I]  Skrymst* rec       �}�����R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbSkrymstInsert( Skrymst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SkrymstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 222 "Skrymst.sqc"


    
/*
EXEC SQL INSERT INTO SKRYMST
    (
		SKERR,
		SKRY,
		TKHKKBN,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:skerr,
		:skry,
		:tkhkkbn,
		:kaiymd,
		:haiymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 241 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 241 "Skrymst.sqc"
  sqlaaloc(2,7,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 241 "Skrymst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 241 "Skrymst.sqc"
      sql_setdlist[0].sqldata = (void*)skerr;
#line 241 "Skrymst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 241 "Skrymst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 241 "Skrymst.sqc"
      sql_setdlist[1].sqldata = (void*)skry;
#line 241 "Skrymst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 241 "Skrymst.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 241 "Skrymst.sqc"
      sql_setdlist[2].sqldata = (void*)&tkhkkbn;
#line 241 "Skrymst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 241 "Skrymst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 241 "Skrymst.sqc"
      sql_setdlist[3].sqldata = (void*)kaiymd;
#line 241 "Skrymst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 241 "Skrymst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 241 "Skrymst.sqc"
      sql_setdlist[4].sqldata = (void*)haiymd;
#line 241 "Skrymst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 241 "Skrymst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 241 "Skrymst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 241 "Skrymst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 241 "Skrymst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 241 "Skrymst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 241 "Skrymst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 241 "Skrymst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 241 "Skrymst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 241 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 241 "Skrymst.sqc"
  sqlastop(0L);
}

#line 241 "Skrymst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 246 "Skrymst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSkrymstUpdate()
 *    SKRYMST ���R�[�h���X�V����
 * ������
 *    [I]  Skrymst* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbSkrymstUpdate( Skrymst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SkrymstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 270 "Skrymst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 271 "Skrymst.sqc"


    
/*
EXEC SQL UPDATE SKRYMST
    SET (
		SKRY,
		TKHKKBN,
		HAIYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:skry,
		:tkhkkbn,
		:haiymd,
		:hnktntid,
		:ksndh
    ) WHERE
		SKERR = :skerr AND
		KAIYMD = :kaiymd;
*/

{
#line 288 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 288 "Skrymst.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 288 "Skrymst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 21;
#line 288 "Skrymst.sqc"
      sql_setdlist[0].sqldata = (void*)skry;
#line 288 "Skrymst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 288 "Skrymst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 288 "Skrymst.sqc"
      sql_setdlist[1].sqldata = (void*)&tkhkkbn;
#line 288 "Skrymst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 288 "Skrymst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 288 "Skrymst.sqc"
      sql_setdlist[2].sqldata = (void*)haiymd;
#line 288 "Skrymst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 288 "Skrymst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 288 "Skrymst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 288 "Skrymst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 288 "Skrymst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 288 "Skrymst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 288 "Skrymst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 288 "Skrymst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 4;
#line 288 "Skrymst.sqc"
      sql_setdlist[5].sqldata = (void*)skerr;
#line 288 "Skrymst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 288 "Skrymst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 288 "Skrymst.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 288 "Skrymst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 288 "Skrymst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 288 "Skrymst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 288 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 288 "Skrymst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 288 "Skrymst.sqc"
  sqlastop(0L);
}

#line 288 "Skrymst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 293 "Skrymst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Skrymst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbSkrymstDelete()
 *    SKRYMST ���R�[�h���폜����
 * ������
 *    [I]  Skrymst* rec       �폜�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbSkrymstDelete( Skrymst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, SkrymstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 321 "Skrymst.sqc"


    
/*
EXEC SQL DELETE FROM SKRYMST
    WHERE
		SKERR = :skerr AND
		KAIYMD = :kaiymd;
*/

{
#line 326 "Skrymst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 326 "Skrymst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 326 "Skrymst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 326 "Skrymst.sqc"
      sql_setdlist[0].sqldata = (void*)skerr;
#line 326 "Skrymst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 326 "Skrymst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 326 "Skrymst.sqc"
      sql_setdlist[1].sqldata = (void*)kaiymd;
#line 326 "Skrymst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 326 "Skrymst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 326 "Skrymst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 326 "Skrymst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 326 "Skrymst.sqc"
  sqlastop(0L);
}

#line 326 "Skrymst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 331 "Skrymst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
