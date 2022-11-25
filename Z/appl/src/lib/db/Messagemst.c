static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,79,66,85,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,53,51,90,77,69,83,83,32,0,0,0,0,0,0,0,0,
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


#line 1 "Messagemst.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Messagemst.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Messagemst.h"
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


#line 24 "Messagemst.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "Messagemst.sqc"

	char    msgcd[9];
	char    status;
	char    msgniyo[101];
	sqlint32  msgbtn;
	sqlint32  msgico;
	char    hnktntid[9];
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 37 "Messagemst.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Messagemst

BmlDMMInfo	MessagemstArray[] = {
	DMM_SSTRING( msgcd ),
	DMM_SCHAR( status ),
	DMM_SSTRING( msgniyo ),
	DMM_SLONG( msgbtn ),
	DMM_SLONG( msgico ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbMessagemstSelectAll()
 *    MESSAGEMST ���R�[�h�S���擾
 * ������
 *    [O]  Messagemst** arrayOu �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMessagemstSelectAll( Messagemst** arrayOut, int* numOut )
{
    Messagemst* array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 72 "Messagemst.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		MSGCD,
		STATUS,
		MSGNIYO,
		MSGBTN,
		MSGICO,
		HNKTNTID,
		KSNDH
    FROM
        MESSAGEMST FOR READ ONLY;
*/

#line 84 "Messagemst.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 86 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "Messagemst.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 86 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 86 "Messagemst.sqc"
  sqlastop(0L);
}

#line 86 "Messagemst.sqc"


    while( 1 ) {
        Messagemst* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:msgcd,
			:status,
			:msgniyo,
			:msgbtn,
			:msgico,
			:hnktntid,
			:ksndh;
*/

{
#line 98 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 98 "Messagemst.sqc"
  sqlaaloc(3,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 98 "Messagemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 98 "Messagemst.sqc"
      sql_setdlist[0].sqldata = (void*)msgcd;
#line 98 "Messagemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 98 "Messagemst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 98 "Messagemst.sqc"
      sql_setdlist[1].sqldata = (void*)&status;
#line 98 "Messagemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 98 "Messagemst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 101;
#line 98 "Messagemst.sqc"
      sql_setdlist[2].sqldata = (void*)msgniyo;
#line 98 "Messagemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 98 "Messagemst.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 98 "Messagemst.sqc"
      sql_setdlist[3].sqldata = (void*)&msgbtn;
#line 98 "Messagemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 98 "Messagemst.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 98 "Messagemst.sqc"
      sql_setdlist[4].sqldata = (void*)&msgico;
#line 98 "Messagemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 98 "Messagemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 98 "Messagemst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 98 "Messagemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 98 "Messagemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 98 "Messagemst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 98 "Messagemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 98 "Messagemst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 98 "Messagemst.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 98 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 98 "Messagemst.sqc"
  sqlastop(0L);
}

#line 98 "Messagemst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Messagemst*)ZbmlRealloc( array,
                                    sizeof( Messagemst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Messagemst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MessagemstArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 113 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 113 "Messagemst.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 113 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 113 "Messagemst.sqc"
  sqlastop(0L);
}

#line 113 "Messagemst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 121 "Messagemst.sqc"

    return sqlca.sqlcode;
}
/******************************************************************************
 * ZdbMessagemstSelectKey()
 *    MESSAGEMST ���R�[�hKey�����擾
 * ������
 *    [I]  Messagemst* pKey     �擾���郌�R�[�h�̃L�[
 *    [O]  Messagemst** arrayOu �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMessagemstSelectKey( Messagemst* pKey, Messagemst** arrayOut, int* numOut )
{
    Messagemst* array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, MessagemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 147 "Messagemst.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		MSGCD,
		STATUS,
		MSGNIYO,
		MSGBTN,
		MSGICO,
		HNKTNTID,
		KSNDH
    FROM
        MESSAGEMST
    WHERE
		MSGCD = :msgcd FOR READ ONLY;
*/

#line 161 "Messagemst.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 163 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 163 "Messagemst.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 163 "Messagemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 163 "Messagemst.sqc"
      sql_setdlist[0].sqldata = (void*)msgcd;
#line 163 "Messagemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 163 "Messagemst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 163 "Messagemst.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 163 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 163 "Messagemst.sqc"
  sqlastop(0L);
}

#line 163 "Messagemst.sqc"


    while( 1 ) {
        Messagemst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:msgcd,
			:status,
			:msgniyo,
			:msgbtn,
			:msgico,
			:hnktntid,
			:ksndh;
*/

{
#line 175 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 175 "Messagemst.sqc"
  sqlaaloc(3,7,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 175 "Messagemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 175 "Messagemst.sqc"
      sql_setdlist[0].sqldata = (void*)msgcd;
#line 175 "Messagemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 175 "Messagemst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 175 "Messagemst.sqc"
      sql_setdlist[1].sqldata = (void*)&status;
#line 175 "Messagemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 175 "Messagemst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 101;
#line 175 "Messagemst.sqc"
      sql_setdlist[2].sqldata = (void*)msgniyo;
#line 175 "Messagemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 175 "Messagemst.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 175 "Messagemst.sqc"
      sql_setdlist[3].sqldata = (void*)&msgbtn;
#line 175 "Messagemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 175 "Messagemst.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 175 "Messagemst.sqc"
      sql_setdlist[4].sqldata = (void*)&msgico;
#line 175 "Messagemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 175 "Messagemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 175 "Messagemst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 175 "Messagemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 175 "Messagemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 175 "Messagemst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 175 "Messagemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 175 "Messagemst.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 175 "Messagemst.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 175 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 175 "Messagemst.sqc"
  sqlastop(0L);
}

#line 175 "Messagemst.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Messagemst*)ZbmlRealloc( array,
                                    sizeof( Messagemst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Messagemst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, MessagemstArray );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 190 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 190 "Messagemst.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 190 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 190 "Messagemst.sqc"
  sqlastop(0L);
}

#line 190 "Messagemst.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 198 "Messagemst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMessagemstInsert()
 *    MESSAGEMST ���R�[�h��}������
 * ������
 *    [I]  Messagemst* rec      �}�����R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMessagemstInsert( Messagemst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MessagemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 221 "Messagemst.sqc"


    
/*
EXEC SQL INSERT INTO MESSAGEMST
    (
		MSGCD,
		STATUS,
		MSGNIYO,
		MSGBTN,
		MSGICO,
		HNKTNTID,
		KSNDH
    ) VALUES (
		:msgcd,
		:status,
		:msgniyo,
		:msgbtn,
		:msgico,
		:hnktntid,
		:ksndh
    );
*/

{
#line 240 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 240 "Messagemst.sqc"
  sqlaaloc(2,7,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 240 "Messagemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 240 "Messagemst.sqc"
      sql_setdlist[0].sqldata = (void*)msgcd;
#line 240 "Messagemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 240 "Messagemst.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 240 "Messagemst.sqc"
      sql_setdlist[1].sqldata = (void*)&status;
#line 240 "Messagemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 240 "Messagemst.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 101;
#line 240 "Messagemst.sqc"
      sql_setdlist[2].sqldata = (void*)msgniyo;
#line 240 "Messagemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 240 "Messagemst.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 240 "Messagemst.sqc"
      sql_setdlist[3].sqldata = (void*)&msgbtn;
#line 240 "Messagemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 240 "Messagemst.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 240 "Messagemst.sqc"
      sql_setdlist[4].sqldata = (void*)&msgico;
#line 240 "Messagemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 240 "Messagemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 9;
#line 240 "Messagemst.sqc"
      sql_setdlist[5].sqldata = (void*)hnktntid;
#line 240 "Messagemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 240 "Messagemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 27;
#line 240 "Messagemst.sqc"
      sql_setdlist[6].sqldata = (void*)ksndh;
#line 240 "Messagemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 240 "Messagemst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 240 "Messagemst.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 240 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 240 "Messagemst.sqc"
  sqlastop(0L);
}

#line 240 "Messagemst.sqc"


    return HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 245 "Messagemst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMessagemstUpdate()
 *    MESSAGEMST ���R�[�h���X�V����
 * ������
 *    [I]  Messagemst* rec      �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMessagemstUpdate( Messagemst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MessagemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 269 "Messagemst.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 270 "Messagemst.sqc"


    
/*
EXEC SQL UPDATE MESSAGEMST
    SET (
		STATUS,
		MSGNIYO,
		MSGBTN,
		MSGICO,
		HNKTNTID,
		KSNDH
    ) = (
		:status,
		:msgniyo,
		:msgbtn,
		:msgico,
		:hnktntid,
		:ksndh
    ) WHERE
		MSGCD = :msgcd;
*/

{
#line 288 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 288 "Messagemst.sqc"
  sqlaaloc(2,7,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 288 "Messagemst.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 288 "Messagemst.sqc"
      sql_setdlist[0].sqldata = (void*)&status;
#line 288 "Messagemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 288 "Messagemst.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 101;
#line 288 "Messagemst.sqc"
      sql_setdlist[1].sqldata = (void*)msgniyo;
#line 288 "Messagemst.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 288 "Messagemst.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 288 "Messagemst.sqc"
      sql_setdlist[2].sqldata = (void*)&msgbtn;
#line 288 "Messagemst.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 288 "Messagemst.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 288 "Messagemst.sqc"
      sql_setdlist[3].sqldata = (void*)&msgico;
#line 288 "Messagemst.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 288 "Messagemst.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 9;
#line 288 "Messagemst.sqc"
      sql_setdlist[4].sqldata = (void*)hnktntid;
#line 288 "Messagemst.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 288 "Messagemst.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 27;
#line 288 "Messagemst.sqc"
      sql_setdlist[5].sqldata = (void*)ksndh;
#line 288 "Messagemst.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 288 "Messagemst.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 9;
#line 288 "Messagemst.sqc"
      sql_setdlist[6].sqldata = (void*)msgcd;
#line 288 "Messagemst.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 288 "Messagemst.sqc"
      sqlasetdata(2,0,7,sql_setdlist,0L,0L);
    }
#line 288 "Messagemst.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 288 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 288 "Messagemst.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 288 "Messagemst.sqc"
  sqlastop(0L);
}

#line 288 "Messagemst.sqc"


    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 293 "Messagemst.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 297 "Messagemst.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbMessagemstDelete()
 *    MESSAGEMST ���R�[�h���폜����
 * ������
 *    [I]  Messagemst* rec      �폜�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbMessagemstDelete( Messagemst* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, MessagemstArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 321 "Messagemst.sqc"


    
/*
EXEC SQL DELETE FROM MESSAGEMST
    WHERE
		MSGCD = :msgcd;
*/

{
#line 325 "Messagemst.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 325 "Messagemst.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 325 "Messagemst.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 325 "Messagemst.sqc"
      sql_setdlist[0].sqldata = (void*)msgcd;
#line 325 "Messagemst.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 325 "Messagemst.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 325 "Messagemst.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 325 "Messagemst.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 325 "Messagemst.sqc"
  sqlastop(0L);
}

#line 325 "Messagemst.sqc"


    return SQLCODE == 100 ? HRC_SQL_NOT_FOUND : HRC_SQL_NORMAL;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 330 "Messagemst.sqc"

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
