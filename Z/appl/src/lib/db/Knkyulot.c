static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,88,66,84,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,52,50,90,75,78,75,89,32,0,0,0,0,0,0,0,0,
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


#line 1 "Knkyulot.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Knkyulot.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "Knkyulot.h"
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


#line 24 "Knkyulot.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Knkyulot.sqc"

	char    knskisymd[11];
	char    seccd[3];
	short   kkirilotno;
	char    jsndh[27];
	char    hkkdh[27];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 36 "Knkyulot.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Knkyulot

BmlDMMInfo	KnkyulotArray[] = {
	DMM_SDATE( knskisymd ),
	DMM_SSTRING( seccd ),
	DMM_SSHORT( kkirilotno ),
	DMM_STIMESTAMP( jsndh ),
	DMM_STIMESTAMP( hkkdh ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKnkyulotSelectAll()
 *    KNKYULOT ���R�[�h�S���擾
 * ������
 *    [O]  Knkyulot** arrayOut  �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnkyulotSelectAll( Knkyulot** arrayOut, int* numOut )
{
    Knkyulot*   array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 70 "Knkyulot.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSKISYMD,
		SECCD,
		KKIRILOTNO,
		JSNDH,
		HKKDH,
		KSNDH
    FROM
        KNKYULOT FOR READ ONLY;
*/

#line 81 "Knkyulot.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 83 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 83 "Knkyulot.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 83 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 83 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 83 "Knkyulot.sqc"


    while( 1 ) {
        Knkyulot* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knskisymd,
			:seccd,
			:kkirilotno,
			:jsndh,
			:hkkdh,
			:ksndh;
*/

{
#line 94 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 94 "Knkyulot.sqc"
  sqlaaloc(3,6,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 94 "Knkyulot.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 94 "Knkyulot.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 94 "Knkyulot.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 94 "Knkyulot.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 94 "Knkyulot.sqc"
      sql_setdlist[1].sqldata = (void*)seccd;
#line 94 "Knkyulot.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 94 "Knkyulot.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 94 "Knkyulot.sqc"
      sql_setdlist[2].sqldata = (void*)&kkirilotno;
#line 94 "Knkyulot.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 94 "Knkyulot.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 94 "Knkyulot.sqc"
      sql_setdlist[3].sqldata = (void*)jsndh;
#line 94 "Knkyulot.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 94 "Knkyulot.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 94 "Knkyulot.sqc"
      sql_setdlist[4].sqldata = (void*)hkkdh;
#line 94 "Knkyulot.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 94 "Knkyulot.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 94 "Knkyulot.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 94 "Knkyulot.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 94 "Knkyulot.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 94 "Knkyulot.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 94 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 94 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 94 "Knkyulot.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knkyulot*)ZbmlRealloc( array,
                                    sizeof( Knkyulot ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knkyulot ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnkyulotArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 109 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 109 "Knkyulot.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 109 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 109 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 109 "Knkyulot.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 117 "Knkyulot.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbKnkyulotSelectKey()
 *    KNKYULOT ���R�[�hKey�����擾
 * ������
 *    [I]  Knkyulot* pKey       �擾���郌�R�[�h�̃L�[
 *    [O]  Knkyulot** arrayOut  �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnkyulotSelectKey( Knkyulot* pKey, Knkyulot** arrayOut, int* numOut )
{
    Knkyulot*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KnkyulotArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 143 "Knkyulot.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSKISYMD,
		SECCD,
		KKIRILOTNO,
		JSNDH,
		HKKDH,
		KSNDH
    FROM
        KNKYULOT
    WHERE
		KNSKISYMD = :knskisymd AND
		SECCD = :seccd AND
		KKIRILOTNO = :kkirilotno FOR READ ONLY;
*/

#line 158 "Knkyulot.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 160 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 160 "Knkyulot.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 160 "Knkyulot.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 160 "Knkyulot.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 160 "Knkyulot.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 160 "Knkyulot.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 160 "Knkyulot.sqc"
      sql_setdlist[1].sqldata = (void*)seccd;
#line 160 "Knkyulot.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 160 "Knkyulot.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 160 "Knkyulot.sqc"
      sql_setdlist[2].sqldata = (void*)&kkirilotno;
#line 160 "Knkyulot.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 160 "Knkyulot.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 160 "Knkyulot.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 160 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 160 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 160 "Knkyulot.sqc"


    while( 1 ) {
        Knkyulot* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knskisymd,
			:seccd,
			:kkirilotno,
			:jsndh,
			:hkkdh,
			:ksndh;
*/

{
#line 171 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 171 "Knkyulot.sqc"
  sqlaaloc(3,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 171 "Knkyulot.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 171 "Knkyulot.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 171 "Knkyulot.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 171 "Knkyulot.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 171 "Knkyulot.sqc"
      sql_setdlist[1].sqldata = (void*)seccd;
#line 171 "Knkyulot.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 171 "Knkyulot.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 171 "Knkyulot.sqc"
      sql_setdlist[2].sqldata = (void*)&kkirilotno;
#line 171 "Knkyulot.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 171 "Knkyulot.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 171 "Knkyulot.sqc"
      sql_setdlist[3].sqldata = (void*)jsndh;
#line 171 "Knkyulot.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 171 "Knkyulot.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 171 "Knkyulot.sqc"
      sql_setdlist[4].sqldata = (void*)hkkdh;
#line 171 "Knkyulot.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 171 "Knkyulot.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 171 "Knkyulot.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 171 "Knkyulot.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 171 "Knkyulot.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 171 "Knkyulot.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 171 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 171 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 171 "Knkyulot.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Knkyulot*)ZbmlRealloc( array,
                                    sizeof( Knkyulot ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Knkyulot ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KnkyulotArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 186 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 186 "Knkyulot.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 186 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 186 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 186 "Knkyulot.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 194 "Knkyulot.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnkyulotInsert()
 *    KNKYULOT ���R�[�h��}������
 * ������
 *    [I]  Knkyulot* rec       �}�����R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnkyulotInsert( Knkyulot* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnkyulotArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 217 "Knkyulot.sqc"


    
/*
EXEC SQL INSERT INTO KNKYULOT
    (
		KNSKISYMD,
		SECCD,
		KKIRILOTNO,
		JSNDH,
		HKKDH,
		KSNDH
    ) VALUES (
		:knskisymd,
		:seccd,
		:kkirilotno,
		:jsndh,
		:hkkdh,
		:ksndh
    );
*/

{
#line 234 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 234 "Knkyulot.sqc"
  sqlaaloc(2,6,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 234 "Knkyulot.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 234 "Knkyulot.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 234 "Knkyulot.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 234 "Knkyulot.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 234 "Knkyulot.sqc"
      sql_setdlist[1].sqldata = (void*)seccd;
#line 234 "Knkyulot.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 234 "Knkyulot.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 234 "Knkyulot.sqc"
      sql_setdlist[2].sqldata = (void*)&kkirilotno;
#line 234 "Knkyulot.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 234 "Knkyulot.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 234 "Knkyulot.sqc"
      sql_setdlist[3].sqldata = (void*)jsndh;
#line 234 "Knkyulot.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 234 "Knkyulot.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 234 "Knkyulot.sqc"
      sql_setdlist[4].sqldata = (void*)hkkdh;
#line 234 "Knkyulot.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 234 "Knkyulot.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 234 "Knkyulot.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 234 "Knkyulot.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 234 "Knkyulot.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 234 "Knkyulot.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 234 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 234 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 234 "Knkyulot.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 239 "Knkyulot.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnkyulotUpdate()
 *    KNKYULOT ���R�[�h���X�V����
 * ������
 *    [I]  Knkyulot* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnkyulotUpdate( Knkyulot* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnkyulotArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 263 "Knkyulot.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 264 "Knkyulot.sqc"


    
/*
EXEC SQL UPDATE KNKYULOT
    SET (
		JSNDH,
		HKKDH,
		KSNDH
    ) = (
		:jsndh,
		:hkkdh,
		:ksndh
    ) WHERE
		KNSKISYMD = :knskisymd AND
		SECCD = :seccd AND
		KKIRILOTNO = :kkirilotno;
*/

{
#line 278 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 278 "Knkyulot.sqc"
  sqlaaloc(2,6,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 278 "Knkyulot.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 27;
#line 278 "Knkyulot.sqc"
      sql_setdlist[0].sqldata = (void*)jsndh;
#line 278 "Knkyulot.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 278 "Knkyulot.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 27;
#line 278 "Knkyulot.sqc"
      sql_setdlist[1].sqldata = (void*)hkkdh;
#line 278 "Knkyulot.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 278 "Knkyulot.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 278 "Knkyulot.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 278 "Knkyulot.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 278 "Knkyulot.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 278 "Knkyulot.sqc"
      sql_setdlist[3].sqldata = (void*)knskisymd;
#line 278 "Knkyulot.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 278 "Knkyulot.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 3;
#line 278 "Knkyulot.sqc"
      sql_setdlist[4].sqldata = (void*)seccd;
#line 278 "Knkyulot.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 278 "Knkyulot.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 278 "Knkyulot.sqc"
      sql_setdlist[5].sqldata = (void*)&kkirilotno;
#line 278 "Knkyulot.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 278 "Knkyulot.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 278 "Knkyulot.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 278 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 278 "Knkyulot.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 278 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 278 "Knkyulot.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 283 "Knkyulot.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 287 "Knkyulot.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbKnkyulotDelete()
 *    KNKYULOT ���R�[�h���폜����
 * ������
 *    [I]  Knkyulot* rec       �폜�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKnkyulotDelete( Knkyulot* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, KnkyulotArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 311 "Knkyulot.sqc"


    
/*
EXEC SQL DELETE FROM KNKYULOT
    WHERE
		KNSKISYMD = :knskisymd AND
		SECCD = :seccd AND
		KKIRILOTNO = :kkirilotno;
*/

{
#line 317 "Knkyulot.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 317 "Knkyulot.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 317 "Knkyulot.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 317 "Knkyulot.sqc"
      sql_setdlist[0].sqldata = (void*)knskisymd;
#line 317 "Knkyulot.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 317 "Knkyulot.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 317 "Knkyulot.sqc"
      sql_setdlist[1].sqldata = (void*)seccd;
#line 317 "Knkyulot.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 317 "Knkyulot.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 317 "Knkyulot.sqc"
      sql_setdlist[2].sqldata = (void*)&kkirilotno;
#line 317 "Knkyulot.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 317 "Knkyulot.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 317 "Knkyulot.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 317 "Knkyulot.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 317 "Knkyulot.sqc"
  sqlastop(0L);
}

#line 317 "Knkyulot.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 322 "Knkyulot.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
