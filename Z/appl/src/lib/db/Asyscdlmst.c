static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,112,65,81,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,51,90,65,83,89,83,32,32,0,0,0,0,0,0,0,0,
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


#line 1 "Asyscdlmst.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Asyscdlmst.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Asyscdlmst.h"
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


#line 24 "Asyscdlmst.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Asyscdlmst.sqc"

	char    knsgrp[17];
	char    asystartymd[11];
	char    asyendymd[11];
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 35 "Asyscdlmst.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Asyscdlmst

BmlDMMInfo	AsyscdlmstArray[] = {
	DMM_SSTRING( knsgrp ),
	DMM_SDATE( asystartymd ),
	DMM_SDATE( asyendymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbAsyscdlmstSelectAll()
 *    ASYSCDLMST ���R�[�h�S���擾
 * ������
 *    [O]  Asyscdlmst** arrayOu �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbAsyscdlmstSelectAll( Asyscdlmst** arrayOut, int* numOut )
{
    Asyscdlmst* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 68 "Asyscdlmst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		KNSGRP,
		ASYSTARTYMD,
		ASYENDYMD,
		HNKTNTID,
		KSNDH
    FROM
        ASYSCDLMST FOR READ ONLY;
*/

#line 78 "Asyscdlmst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 80 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 80 "Asyscdlmst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 80 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 80 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 80 "Asyscdlmst.sqc"


    while( 1 ) {
        Asyscdlmst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:knsgrp,
			:asystartymd,
			:asyendymd,
			:hnktntid,
			:ksndh;
*/

{
#line 90 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 90 "Asyscdlmst.sqc"
  sqlaaloc(3,5,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[1].sqldata = (void*)asystartymd;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[2].sqldata = (void*)asyendymd;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 90 "Asyscdlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 90 "Asyscdlmst.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 90 "Asyscdlmst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 90 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 90 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 90 "Asyscdlmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Asyscdlmst*)ZbmlRealloc( array,
                                    sizeof( Asyscdlmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Asyscdlmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, AsyscdlmstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 105 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 105 "Asyscdlmst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 105 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 105 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 105 "Asyscdlmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 113 "Asyscdlmst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbAsyscdlmstSelectKey()
 *    ASYSCDLMST ���R�[�hKey�����擾
 * ������
 *    [I]  Asyscdlmst* pKey     �擾���郌�R�[�h�̃L�[
 *    [O]  Asyscdlmst** arrayOu �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbAsyscdlmstSelectKey( Asyscdlmst* pKey, Asyscdlmst** arrayOut, int* numOut )
{
    Asyscdlmst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, AsyscdlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 139 "Asyscdlmst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		KNSGRP,
		ASYSTARTYMD,
		ASYENDYMD,
		HNKTNTID,
		KSNDH
    FROM
        ASYSCDLMST
    WHERE
		KNSGRP = :knsgrp AND
		ASYSTARTYMD = :asystartymd FOR READ ONLY;
*/

#line 152 "Asyscdlmst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 154 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 154 "Asyscdlmst.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 154 "Asyscdlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 154 "Asyscdlmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 154 "Asyscdlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 154 "Asyscdlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 154 "Asyscdlmst.sqc"
      sql_setdlist[1].sqldata = (void*)asystartymd;
#line 154 "Asyscdlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 154 "Asyscdlmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 154 "Asyscdlmst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 154 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 154 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 154 "Asyscdlmst.sqc"


    while( 1 ) {
        Asyscdlmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:knsgrp,
			:asystartymd,
			:asyendymd,
			:hnktntid,
			:ksndh;
*/

{
#line 164 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "Asyscdlmst.sqc"
  sqlaaloc(3,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[1].sqldata = (void*)asystartymd;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[2].sqldata = (void*)asyendymd;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 164 "Asyscdlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 164 "Asyscdlmst.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 164 "Asyscdlmst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 164 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 164 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 164 "Asyscdlmst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Asyscdlmst*)ZbmlRealloc( array,
                                    sizeof( Asyscdlmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Asyscdlmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, AsyscdlmstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 179 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 179 "Asyscdlmst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 179 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 179 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 179 "Asyscdlmst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 187 "Asyscdlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbAsyscdlmstInsert()
 *    ASYSCDLMST ���R�[�h��}������
 * ������
 *    [I]  Asyscdlmst* rec      �}�����R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbAsyscdlmstInsert( Asyscdlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, AsyscdlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 210 "Asyscdlmst.sqc"


    
/*
EXEC SQL INSERT INTO ASYSCDLMST
    (
		KNSGRP,
		ASYSTARTYMD,
		ASYENDYMD,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:knsgrp,
		:asystartymd,
		:asyendymd,
		:hnktntid,
		:ksndh
    );
*/

{
#line 225 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 225 "Asyscdlmst.sqc"
  sqlaaloc(2,5,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[1].sqldata = (void*)asystartymd;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[2].sqldata = (void*)asyendymd;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 9;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[3].sqldata = (void*)hnktntid;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 27;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[4].sqldata = (void*)ksndh;
#line 225 "Asyscdlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 225 "Asyscdlmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 225 "Asyscdlmst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 225 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 225 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 225 "Asyscdlmst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 230 "Asyscdlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbAsyscdlmstUpdate()
 *    ASYSCDLMST ���R�[�h���X�V����
 * ������
 *    [I]  Asyscdlmst* rec      �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbAsyscdlmstUpdate( Asyscdlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, AsyscdlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 254 "Asyscdlmst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 255 "Asyscdlmst.sqc"


    
/*
EXEC SQL UPDATE ASYSCDLMST
    SET (
		ASYENDYMD,
		HNKTNTID,
		KSNDH
    ) = (
		:asyendymd,
		:hnktntid,
		:ksndh
    ) WHERE
		KNSGRP = :knsgrp AND
		ASYSTARTYMD = :asystartymd;
*/

{
#line 268 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 268 "Asyscdlmst.sqc"
  sqlaaloc(2,5,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[0].sqldata = (void*)asyendymd;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[1].sqldata = (void*)hnktntid;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[2].sqldata = (void*)ksndh;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[3].sqldata = (void*)knsgrp;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[4].sqldata = (void*)asystartymd;
#line 268 "Asyscdlmst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 268 "Asyscdlmst.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 268 "Asyscdlmst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 268 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 268 "Asyscdlmst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 268 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 268 "Asyscdlmst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 273 "Asyscdlmst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 277 "Asyscdlmst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbAsyscdlmstDelete()
 *    ASYSCDLMST ���R�[�h���폜����
 * ������
 *    [I]  Asyscdlmst* rec      �폜�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbAsyscdlmstDelete( Asyscdlmst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, AsyscdlmstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 301 "Asyscdlmst.sqc"


    
/*
EXEC SQL DELETE FROM ASYSCDLMST
    WHERE
		KNSGRP = :knsgrp AND
		ASYSTARTYMD = :asystartymd;
*/

{
#line 306 "Asyscdlmst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 306 "Asyscdlmst.sqc"
  sqlaaloc(2,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 306 "Asyscdlmst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 17;
#line 306 "Asyscdlmst.sqc"
      sql_setdlist[0].sqldata = (void*)knsgrp;
#line 306 "Asyscdlmst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 306 "Asyscdlmst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 306 "Asyscdlmst.sqc"
      sql_setdlist[1].sqldata = (void*)asystartymd;
#line 306 "Asyscdlmst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 306 "Asyscdlmst.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 306 "Asyscdlmst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 306 "Asyscdlmst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 306 "Asyscdlmst.sqc"
  sqlastop(0L);
}

#line 306 "Asyscdlmst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 311 "Asyscdlmst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
