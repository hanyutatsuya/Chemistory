static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,78,65,76,106,84,81,70,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,57,90,84,85,78,69,50,32,0,0,0,0,0,0,0,0,
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


#line 1 "KskbrmstChk.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F Kskbrmst.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-04-11                    Create
 **********************************************************************/
#include <stdio.h>

#include "Kskbrmst.h"
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


#line 24 "KskbrmstChk.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "KskbrmstChk.sqc"

	char    bskkbn[5];
	char    knsgrp[17];
	char    kmkcd[8];
	char    ksbr[16];
	char    kmin[21];
	char    kmax[21];
	char    kaiymd[11];
	char    haiymd[11];
	char    hnktntid[9];
	char    ksndh[27];
// ADD 2006-08-31 S.Ueda >>
	char	hKnskisymd[11+1];
	char	hSriymd[11+1];
	char	hKntno[11+1];
	char	hKnsgrp[16+1];
	char	hKmkcd[7+1];
	sqlint32	num_Irai;
// ADD 2006-08-31 S.Ueda <<

/*
EXEC SQL END DECLARE SECTION;
*/

#line 48 "KskbrmstChk.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Kskbrmst

BmlDMMInfo	KskbrmstArrayChk[] = {
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( ksbr ),
	DMM_SSTRING( kmin ),
	DMM_SSTRING( kmax ),
	DMM_SDATE( kaiymd ),
	DMM_SDATE( haiymd ),
	DMM_SSTRING( hnktntid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbKskbrmstSelectKey()
 *    KSKBRMST ���R�[�hKey�����擾
 * ������
 *    [I]  Kskbrmst* pKey       �擾���郌�R�[�h�̃L�[
 *    [O]  Kskbrmst** arrayOut  �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbKskbrmstSelectChk( Kskbrmst* pKey, Kskbrmst** arrayOut, int* numOut )
{
    Kskbrmst*   array = NULL;
    int         num = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KskbrmstArrayChk ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 93 "KskbrmstChk.sqc"


    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		BSKKBN,
		KNSGRP,
		KMKCD,
		KSBR,
		KMIN,
		KMAX,
		KAIYMD,
		HAIYMD,
		HNKTNTID,
		KSNDH
    FROM
        KSKBRMST
    WHERE
		BSKKBN = :bskkbn AND
		KNSGRP = :knsgrp AND
		KMKCD = :kmkcd AND
		DOUBLE(:ksbr) BETWEEN DOUBLE(KMIN) AND DOUBLE(KMAX) AND
		CURRENT DATE BETWEEN KAIYMD and HAIYMD FOR READ ONLY;
*/

#line 114 "KskbrmstChk.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 116 "KskbrmstChk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 116 "KskbrmstChk.sqc"
  sqlaaloc(2,4,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 16;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[3].sqldata = (void*)ksbr;
#line 116 "KskbrmstChk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 116 "KskbrmstChk.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 116 "KskbrmstChk.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 116 "KskbrmstChk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 116 "KskbrmstChk.sqc"
  sqlastop(0L);
}

#line 116 "KskbrmstChk.sqc"


    while( 1 ) {
        Kskbrmst* rec;

        
/*
EXEC SQL FETCH c2 INTO
			:bskkbn,
			:knsgrp,
			:kmkcd,
			:ksbr,
			:kmin,
			:kmax,
			:kaiymd,
			:haiymd,
			:hnktntid,
			:ksndh;
*/

{
#line 131 "KskbrmstChk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 131 "KskbrmstChk.sqc"
  sqlaaloc(3,10,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 5;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[0].sqldata = (void*)bskkbn;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 17;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[1].sqldata = (void*)knsgrp;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 8;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[2].sqldata = (void*)kmkcd;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 16;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[3].sqldata = (void*)ksbr;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[4].sqldata = (void*)kmin;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[5].sqldata = (void*)kmax;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[6].sqldata = (void*)kaiymd;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[7].sqldata = (void*)haiymd;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 9;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[8].sqldata = (void*)hnktntid;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 27;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[9].sqldata = (void*)ksndh;
#line 131 "KskbrmstChk.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 131 "KskbrmstChk.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 131 "KskbrmstChk.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 131 "KskbrmstChk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 131 "KskbrmstChk.sqc"
  sqlastop(0L);
}

#line 131 "KskbrmstChk.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Kskbrmst*)ZbmlRealloc( array,
                                    sizeof( Kskbrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Kskbrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, KskbrmstArrayChk );
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 146 "KskbrmstChk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 146 "KskbrmstChk.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 146 "KskbrmstChk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 146 "KskbrmstChk.sqc"
  sqlastop(0L);
}

#line 146 "KskbrmstChk.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 154 "KskbrmstChk.sqc"

    return sqlca.sqlcode;
}
// ADD 2006-08-31 S.Ueda >>
/******************************************************************************
 * 
 *    ���݂��錋�ʂ��������āA���ׂĂ����񍐊����ł��A���Ԃł��邩�B
 * ������
 *	[I] char * aUtkymd		��t��
 *  [I] char * aKntno		�˗���No
 *  [I] char * aKnsgrp		�����O���[�v
 *  [I] char * aKmkcd		���ڃR�[�h
 * ���߂�l
 *		0�ȏ�	�˗����
 *		0����	SQL Error
 * UPD Nagata 2006-09-01
 * UPD Nagata 2007-05-10 ���݂��錋�ʂ��������A�ŏI�񍐌��ʐ����J�E���g����
 *                       (���񍐊����̏������폜�j
 ******************************************************************************/
long ZdbSelectMihoKekka( char * aKnskisymd,char * aSriymd, char * aKntno,  char * aKnsgrp, char * aKmkcd )
{
	memcpy( hKnskisymd, aKnskisymd, sizeof(hKnskisymd)-1 );
	memcpy( hSriymd, aSriymd, sizeof(hSriymd)-1 );
	memcpy( hKntno, aKntno, sizeof(hKntno)-1 );
	memcpy( hKnsgrp, aKnsgrp, sizeof(hKnsgrp)-1 );
	memcpy( hKmkcd, aKmkcd, sizeof(aKmkcd)-1 );

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 181 "KskbrmstChk.sqc"


	
/*
EXEC SQL
		SELECT	COUNT(*)
		INTO	:num_Irai
		FROM	KEKKA
		WHERE	KNSKISYMD	= :hKnskisymd
		 AND    SRIYMD  = :hSriymd
		 AND	KNTNO	= :hKntno
		 AND	KNSGRP	= :hKnsgrp
		 AND	KMKCD	= :hKmkcd
		 AND	KKAJKCD != '1'
	;
*/

{
#line 193 "KskbrmstChk.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 193 "KskbrmstChk.sqc"
  sqlaaloc(2,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[0].sqldata = (void*)hKnskisymd;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[1].sqldata = (void*)hSriymd;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 12;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[2].sqldata = (void*)hKntno;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 17;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[3].sqldata = (void*)hKnsgrp;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[4].sqldata = (void*)hKmkcd;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 193 "KskbrmstChk.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 193 "KskbrmstChk.sqc"
  sqlaaloc(3,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[0].sqldata = (void*)&num_Irai;
#line 193 "KskbrmstChk.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 193 "KskbrmstChk.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 193 "KskbrmstChk.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 193 "KskbrmstChk.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 193 "KskbrmstChk.sqc"
  sqlastop(0L);
}

#line 193 "KskbrmstChk.sqc"


		/*  AND	(KNSFLG	!= 'M' OR KKAJKCD != '1') */
	return num_Irai;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 199 "KskbrmstChk.sqc"

    return sqlca.sqlcode;
}
// ADD 2006-08-31 S.Ueda <<
/** End of File *********************************************************/
