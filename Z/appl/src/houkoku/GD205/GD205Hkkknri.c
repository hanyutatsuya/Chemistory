static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,113,65,67,114,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,71,68,50,48,53,72,75,75,0,0,0,0,0,0,0,0,
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


#line 1 "GD205Hkkknri.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F GD205Hkkknri.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-03-06                    Create
 *  1.12     2006-09-04                    INTEC.INC �G���[���ۗ������X�V
 **********************************************************************/
#include <stdio.h>

#include "GD205Hkkknri.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

#include "bmllog.h"					// 1.06 ADD

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 27 "GD205Hkkknri.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 32 "GD205Hkkknri.sqc"

	char    hkksjymd[11];
	sqlint32  hkksjno;
	char    hkkkbn;
	char    hkkjkn;
	char    knskisymd[11];
	char    utkymd[11];
	char    sriymd[11];
	char    knsgrp[17];
	char    kmkcd[8];
	char    bskkbn[5];
	char    bskgok[7];
	char    hkkjknst[21];
	char    hkkjkned[21];
	char    stsflnm[51];
	char    seccd[3];
	char    hkkflnm[51];
	char    hkksjtts[9];
	char    hkkdh[27];
	char    hkkstdh[27];
	char    hkkeddh[27];
	char    tnsstdh[27];
	char    tnseddh[27];
	sqlint32  hkkssknsu;
	sqlint32  hkkhrysu;
	char    ssnmtfilid[13];
	char    hkkjkflg[3];
	char    hkkerrcode[9];
	short   kkirilotno;
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 62 "GD205Hkkknri.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Hkkknri

BmlDMMInfo	HkkknriArray[] = {
	DMM_SDATE( hkksjymd ),
	DMM_SLONG( hkksjno ),
	DMM_SCHAR( hkkkbn ),
	DMM_SCHAR( hkkjkn ),
	DMM_SDATE( knskisymd ),
	DMM_SDATE( utkymd ),
	DMM_SDATE( sriymd ),
	DMM_SSTRING( knsgrp ),
	DMM_SSTRING( kmkcd ),
	DMM_SSTRING( bskkbn ),
	DMM_SSTRING( bskgok ),
	DMM_SSTRING( hkkjknst ),
	DMM_SSTRING( hkkjkned ),
	DMM_SSTRING( stsflnm ),
	DMM_SSTRING( seccd ),
	DMM_SSTRING( hkkflnm ),
	DMM_SSTRING( hkksjtts ),
	DMM_STIMESTAMP( hkkdh ),
	DMM_STIMESTAMP( hkkstdh ),
	DMM_STIMESTAMP( hkkeddh ),
	DMM_STIMESTAMP( tnsstdh ),
	DMM_STIMESTAMP( tnseddh ),
	DMM_SLONG( hkkssknsu ),
	DMM_SLONG( hkkhrysu ),
	DMM_SSTRING( ssnmtfilid ),
	DMM_SSTRING( hkkjkflg ),
	DMM_SSTRING( hkkerrcode ),
	DMM_SSHORT( kkirilotno ),
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ZdbHkkknriGD205SelectAll()
 *    HKKKNRI ���R�[�h�S���擾
 * ������
 *    [O]  Hkkknri** arrayOut   �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbHkkknriGD205SelectAll( Hkkknri** arrayOut, int* numOut )
{
    Hkkknri*    array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 119 "GD205Hkkknri.sqc"


    
/*
EXEC SQL DECLARE c1 CURSOR FOR
    SELECT
		HKKSJYMD,
		HKKSJNO,
		HKKKBN,
		HKKJKN,
		KNSKISYMD,
		UTKYMD,
		SRIYMD,
		KNSGRP,
		KMKCD,
		BSKKBN,
		BSKGOK,
		HKKJKNST,
		HKKJKNED,
		STSFLNM,
		SECCD,
		HKKFLNM,
		HKKSJTTS,
		HKKDH,
		HKKSTDH,
		HKKEDDH,
		TNSSTDH,
		TNSEDDH,
		HKKSSKNSU,
		HKKHRYSU,
		SSNMTFILID,
		HKKJKFLG,
		HKKERRCODE,
		KKIRILOTNO,
		KSNDH
	FROM
		HKKKNRI
	WHERE
/- 3.01 DELL
DEL			( HKKJKN <> '7' AND HKKJKFLG = '0' )
DEL		OR  ( HKKJKN = '8' AND HKKJKFLG = '3' )
-/
			HKKJKN = '7'				-- �ً}��
		AND HKKJKFLG in ('0','3')		-- �������A�]���҂�
		FOR READ ONLY;
*/

#line 161 "GD205Hkkknri.sqc"


    
/*
EXEC SQL OPEN c1;
*/

{
#line 163 "GD205Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 163 "GD205Hkkknri.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 163 "GD205Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 163 "GD205Hkkknri.sqc"
  sqlastop(0L);
}

#line 163 "GD205Hkkknri.sqc"


    while( 1 ) {
        Hkkknri* rec;

        
/*
EXEC SQL FETCH c1 INTO
			:hkksjymd,
			:hkksjno,
			:hkkkbn,
			:hkkjkn,
			:knskisymd,
			:utkymd,
			:sriymd,
			:knsgrp,
			:kmkcd,
			:bskkbn,
			:bskgok,
			:hkkjknst,
			:hkkjkned,
			:stsflnm,
			:seccd,
			:hkkflnm,
			:hkksjtts,
			:hkkdh,
			:hkkstdh,
			:hkkeddh,
			:tnsstdh,
			:tnseddh,
			:hkkssknsu,
			:hkkhrysu,
			:ssnmtfilid,
			:hkkjkflg,
			:hkkerrcode,
			:kkirilotno,
			:ksndh;
*/

{
#line 197 "GD205Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "GD205Hkkknri.sqc"
  sqlaaloc(3,29,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[29];
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkksjymd;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)&hkksjno;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkkbn;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqltype = 452; sql_setdlist[3].sqllen = 1;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkjkn;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)knskisymd;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)utkymd;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)sriymd;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 17;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)knsgrp;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 8;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)kmkcd;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 5;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)bskkbn;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 7;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[10].sqldata = (void*)bskgok;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 21;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[11].sqldata = (void*)hkkjknst;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 21;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[12].sqldata = (void*)hkkjkned;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 51;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[13].sqldata = (void*)stsflnm;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 3;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[14].sqldata = (void*)seccd;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 51;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[15].sqldata = (void*)hkkflnm;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 9;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[16].sqldata = (void*)hkksjtts;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[17].sqldata = (void*)hkkdh;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[18].sqldata = (void*)hkkstdh;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[19].sqldata = (void*)hkkeddh;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 27;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[20].sqldata = (void*)tnsstdh;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 27;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[21].sqldata = (void*)tnseddh;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[22].sqldata = (void*)&hkkssknsu;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[23].sqldata = (void*)&hkkhrysu;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 13;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[24].sqldata = (void*)ssnmtfilid;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[25].sqltype = 460; sql_setdlist[25].sqllen = 3;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[25].sqldata = (void*)hkkjkflg;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[26].sqldata = (void*)hkkerrcode;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[27].sqltype = 500; sql_setdlist[27].sqllen = 2;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[27].sqldata = (void*)&kkirilotno;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 27;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[28].sqldata = (void*)ksndh;
#line 197 "GD205Hkkknri.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 197 "GD205Hkkknri.sqc"
      sqlasetdata(3,0,29,sql_setdlist,0L,0L);
    }
#line 197 "GD205Hkkknri.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 197 "GD205Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "GD205Hkkknri.sqc"
  sqlastop(0L);
}

#line 197 "GD205Hkkknri.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Hkkknri*)ZbmlRealloc( array,
                                    sizeof( Hkkknri ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Hkkknri ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, HkkknriArray );
    }

    
/*
EXEC SQL CLOSE c1;
*/

{
#line 212 "GD205Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 212 "GD205Hkkknri.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 212 "GD205Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 212 "GD205Hkkknri.sqc"
  sqlastop(0L);
}

#line 212 "GD205Hkkknri.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 220 "GD205Hkkknri.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ZdbHkkknriGD205UpdateNormal()
 *    HKKKNRI ���R�[�h���X�V����
 * ������
 *    [I]  Hkkknri* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbHkkknriGD205UpdateNormal( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 244 "GD205Hkkknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 245 "GD205Hkkknri.sqc"


    
/*
EXEC SQL UPDATE HKKKNRI
    SET (
		STSFLNM,
		HKKFLNM,
		HKKSTDH,
		HKKEDDH,
		HKKSSKNSU,
		HKKHRYSU,
		SSNMTFILID,
		HKKJKFLG,
		KSNDH
    ) = (
		:stsflnm,
		:hkkflnm,
		:hkkstdh,
		:hkkeddh,
		:hkkssknsu,
		:hkkhrysu,
		:ssnmtfilid,
		:hkkjkflg,
		current timestamp
    ) WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno;
*/

{
#line 270 "GD205Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 270 "GD205Hkkknri.sqc"
  sqlaaloc(2,10,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)stsflnm;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 51;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)hkkflnm;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 27;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)hkkstdh;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 27;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)hkkeddh;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)&hkkssknsu;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)&hkkhrysu;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[6].sqldata = (void*)ssnmtfilid;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[7].sqldata = (void*)hkkjkflg;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 11;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[8].sqldata = (void*)hkksjymd;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[9].sqldata = (void*)&hkksjno;
#line 270 "GD205Hkkknri.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 270 "GD205Hkkknri.sqc"
      sqlasetdata(2,0,10,sql_setdlist,0L,0L);
    }
#line 270 "GD205Hkkknri.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 270 "GD205Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 270 "GD205Hkkknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 270 "GD205Hkkknri.sqc"
  sqlastop(0L);
}

#line 270 "GD205Hkkknri.sqc"


//1.06 DELL printf("Update HRC_SQL_NORMAL\n");
		// 1.06 DEBUG    LOG
        sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbHkkknriGD205UpdateNormal", 
					__LINE__,
                    EXEFLG_UPD, "00000000",
                    "Update HRC_SQL_NORMAL" );

    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 282 "GD205Hkkknri.sqc"

//1.06 DELL printf("Update HRC_SQL_NOT_FOUND\n");
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbHkkknriGD205UpdateNormal", 
				__LINE__,
                EXEFLG_UPD, "020",
                "Update HRC_SQL_NOT_FOUND" );

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 293 "GD205Hkkknri.sqc"

//1.06 DELL printf("Update %d-%s\n", sqlca.sqlcode, sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbHkkknriGD205UpdateNormal", 
				__LINE__,
                EXEFLG_UPD, "020",
                "Update [%d-%s]", sqlca.sqlcode, sqlca.sqlerrmc );

    return sqlca.sqlcode;
}


/******************************************************************************
 * ZdbHkkknriGD205UpdateSts()
 *    HKKKNRI ���R�[�h���X�V����
 * ������
 *    [I]  Hkkknri* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ZdbHkkknriGD205UpdateSts( Hkkknri* rec )
{
    if( !rec )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)rec, HkkknriArray ) )
        return HRC_INVALID_VALUE;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 325 "GD205Hkkknri.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 326 "GD205Hkkknri.sqc"


    
/*
EXEC SQL UPDATE HKKKNRI
    SET (
		HKKJKFLG,
		HKKERRCODE,
		HKKSSKNSU,
		HKKHRYSU,
		KSNDH
    ) = (
		:hkkjkflg,
		:hkkerrcode,
		:hkkssknsu,
		:hkkhrysu,
		current timestamp
    ) WHERE
		HKKSJYMD = :hkksjymd AND
		HKKSJNO = :hkksjno;
*/

{
#line 343 "GD205Hkkknri.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 343 "GD205Hkkknri.sqc"
  sqlaaloc(2,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqldata = (void*)hkkjkflg;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 9;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqldata = (void*)hkkerrcode;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqldata = (void*)&hkkssknsu;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqldata = (void*)&hkkhrysu;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqldata = (void*)hkksjymd;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqldata = (void*)&hkksjno;
#line 343 "GD205Hkkknri.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 343 "GD205Hkkknri.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 343 "GD205Hkkknri.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 343 "GD205Hkkknri.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 343 "GD205Hkkknri.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 343 "GD205Hkkknri.sqc"
  sqlastop(0L);
}

#line 343 "GD205Hkkknri.sqc"


//1.06 DELL printf("Update HRC_SQL_NORMAL\n");
		// 1.06 DEBUG    LOG
        sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbHkkknriGD205UpdateSts", 
					__LINE__,
                    EXEFLG_UPD, "00000000",
                    "Update HRC_SQL_NORMAL" );

    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 355 "GD205Hkkknri.sqc"

//1.06 DELL printf("Update HRC_SQL_NOT_FOUND\n");
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_ERROR, __FILE__, "ZdbHkkknriGD205UpdateSts", 
				__LINE__,
                EXEFLG_UPD, "020",
                "Update HRC_SQL_NOT_FOUND" );

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 366 "GD205Hkkknri.sqc"

//1.06 DELL printf("Update %d-%s\n", sqlca.sqlcode, sqlca.sqlerrmc);
	// 1.06 DEBUG    LOG
    sFncPutLog( TRCKIND_DEBUG, __FILE__, "ZdbHkkknriGD205UpdateSts", 
				__LINE__,
                EXEFLG_UPD, "020",
                "Update [%d-%s]", sqlca.sqlcode, sqlca.sqlerrmc );

    return sqlca.sqlcode;
}
/** End of File *********************************************************/
