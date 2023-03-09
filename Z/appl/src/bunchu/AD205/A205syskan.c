static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,90,66,114,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,83,89,83,75,0,0,0,0,0,0,0,0,
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


#line 1 "A205syskan.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F A205syskan.sqc
 *     �@�\�T�v  �F
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-21                    Create
 **********************************************************************/
#include <stdio.h>

#include "A205syskan.h"
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


#line 24 "A205syskan.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 29 "A205syskan.sqc"

	char    lbcd[4];
	char    sateid[4];
	char    kjnsriymd[11];
	char    kkkjsriymd[11];		// add 2007.05.31 waj
	char    nxirisriymd[11];
	char    ncnsksriymd[11];
	char    nxbchsriymd[11];
	char    iriendflg;
	char    irienddh[27];
	char    nskendflg;
	char    nskenddh[27];
	char    bchendflg;
	char    bchend0dh[27];
	char    bchend1dh[27];
	char    bchend2dh[27];
	char    bchend3dh[27];
	char    bchend4dh[27];
	char    unyflg;
	sqlint32  ssntubn;
	char    labonm[41];			// add 2007.05.31 waj
	char    knsmngr[41];		// add 2007.05.31 waj
	char    telno[13];			// add 2007.05.31 waj
	char    sriknflg01;
	char    sriknflg02;
	char    sriknflg03;
	char    sriknflg04;
	char    sriknflg05;
	char    sriknflg06;
	char    sriknflg07;
	char    sriknflg08;
	char    sriknflg09;
	char    sriknflg10;
	char    sriknflg11;
	char    sriknflg12;
	char    sriknflg13;
	char    sriknflg14;
	char    sriknflg15;
	char    sriknflg16;
	char    sriknflg17;
	char    sriknflg18;
	char    sriknflg19;
	char    sriknflg20;
	char    hnktntid[9];		// add 2007.05.31 waj
	char    ksndh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 74 "A205syskan.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Sysknrmst

BmlDMMInfo	SysknrmstArray[] = {
	DMM_SSTRING( lbcd ),
	DMM_SSTRING( sateid ),
	DMM_SDATE( kjnsriymd ),
	DMM_SDATE( kkkjsriymd ),	// add 2007.05.31 waj
	DMM_SDATE( nxirisriymd ),
	DMM_SDATE( ncnsksriymd ),
	DMM_SDATE( nxbchsriymd ),
	DMM_SCHAR( iriendflg ),
	DMM_STIMESTAMP( irienddh ),
	DMM_SCHAR( nskendflg ),
	DMM_STIMESTAMP( nskenddh ),
	DMM_SCHAR( bchendflg ),
	DMM_STIMESTAMP( bchend0dh ),
	DMM_STIMESTAMP( bchend1dh ),
	DMM_STIMESTAMP( bchend2dh ),
	DMM_STIMESTAMP( bchend3dh ),
	DMM_STIMESTAMP( bchend4dh ),
	DMM_SCHAR( unyflg ),
	DMM_SLONG( ssntubn ),
    DMM_SSTRING( labonm ),		// add 2007.05.31 waj
    DMM_SSTRING( knsmngr ),		// add 2007.05.31 waj
    DMM_SSTRING( telno ),		// add 2007.05.31 waj
	DMM_SCHAR( sriknflg01 ),
	DMM_SCHAR( sriknflg02 ),
	DMM_SCHAR( sriknflg03 ),
	DMM_SCHAR( sriknflg04 ),
	DMM_SCHAR( sriknflg05 ),
	DMM_SCHAR( sriknflg06 ),
	DMM_SCHAR( sriknflg07 ),
	DMM_SCHAR( sriknflg08 ),
	DMM_SCHAR( sriknflg09 ),
	DMM_SCHAR( sriknflg10 ),
	DMM_SCHAR( sriknflg11 ),
	DMM_SCHAR( sriknflg12 ),
	DMM_SCHAR( sriknflg13 ),
	DMM_SCHAR( sriknflg14 ),
	DMM_SCHAR( sriknflg15 ),
	DMM_SCHAR( sriknflg16 ),
	DMM_SCHAR( sriknflg17 ),
	DMM_SCHAR( sriknflg18 ),
	DMM_SCHAR( sriknflg19 ),
	DMM_SCHAR( sriknflg20 ),
    DMM_SSTRING( hnktntid ),	// add 2007.05.31 waj
	DMM_STIMESTAMP( ksndh ),
	DMM_NULL
};

/******************************************************************************
 * ABunSyskanSelKey()
 *    SYSKNRMST ���R�[�hKey�����擾
 * ������
 *    [I]  Sysknrmst* pKey      �擾���郌�R�[�h�̃L�[
 *    [O]  Sysknrmst** arrayOut �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ABunSyskanSelKey( Sysknrmst** arrayOut, int* numOut )
{

    Sysknrmst*  array = NULL;
    int         num = 0;

    
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 148 "A205syskan.sqc"


	// upd 2007.05.31 waj �ً}������N�����ɕύX KJNSRIYMD -> KKKJSRIYMD
    
/*
EXEC SQL DECLARE c2 CURSOR FOR
    SELECT
		LBCD,
		SATEID,
		KJNSRIYMD,
		KKKJSRIYMD,
		NXIRISRIYMD,
		NCNSKSRIYMD,
		NXBCHSRIYMD,
		IRIENDFLG,
		IRIENDDH,
		NSKENDFLG,
		NSKENDDH,
		BCHENDFLG,
		BCHEND0DH,
		BCHEND1DH,
		BCHEND2DH,
		BCHEND3DH,
		BCHEND4DH,
		UNYFLG,
		SSNTUBN,
		LABONM,
		KNSMNGR,
		TELNO,
		SRIKNFLG01,
		SRIKNFLG02,
		SRIKNFLG03,
		SRIKNFLG04,
		SRIKNFLG05,
		SRIKNFLG06,
		SRIKNFLG07,
		SRIKNFLG08,
		SRIKNFLG09,
		SRIKNFLG10,
		SRIKNFLG11,
		SRIKNFLG12,
		SRIKNFLG13,
		SRIKNFLG14,
		SRIKNFLG15,
		SRIKNFLG16,
		SRIKNFLG17,
		SRIKNFLG18,
		SRIKNFLG19,
		SRIKNFLG20,
		HNKTNTID,
		KSNDH
    FROM
        SYSKNRMST
	FOR READ ONLY;
*/

#line 199 "A205syskan.sqc"


    
/*
EXEC SQL OPEN c2;
*/

{
#line 201 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 201 "A205syskan.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 201 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 201 "A205syskan.sqc"
  sqlastop(0L);
}

#line 201 "A205syskan.sqc"


    while( 1 ) {
        Sysknrmst* rec;

		// upd 2007.05.31 waj �ً}������N�����ɕύX KJNSRIYMD -> KKKJSRIYMD
        
/*
EXEC SQL FETCH c2 INTO
			:lbcd,
			:sateid,
			:kjnsriymd,
			:kkkjsriymd,
			:nxirisriymd,
			:ncnsksriymd,
			:nxbchsriymd,
			:iriendflg,
			:irienddh,
			:nskendflg,
			:nskenddh,
			:bchendflg,
			:bchend0dh,
			:bchend1dh,
			:bchend2dh,
			:bchend3dh,
			:bchend4dh,
			:unyflg,
			:ssntubn,
			:labonm,
			:knsmngr,
			:telno,
			:sriknflg01,
			:sriknflg02,
			:sriknflg03,
			:sriknflg04,
			:sriknflg05,
			:sriknflg06,
			:sriknflg07,
			:sriknflg08,
			:sriknflg09,
			:sriknflg10,
			:sriknflg11,
			:sriknflg12,
			:sriknflg13,
			:sriknflg14,
			:sriknflg15,
			:sriknflg16,
			:sriknflg17,
			:sriknflg18,
			:sriknflg19,
			:sriknflg20,
			:hnktntid,
			:ksndh;
*/

{
#line 251 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 251 "A205syskan.sqc"
  sqlaaloc(3,44,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[44];
#line 251 "A205syskan.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 4;
#line 251 "A205syskan.sqc"
      sql_setdlist[0].sqldata = (void*)lbcd;
#line 251 "A205syskan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 251 "A205syskan.sqc"
      sql_setdlist[1].sqldata = (void*)sateid;
#line 251 "A205syskan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 251 "A205syskan.sqc"
      sql_setdlist[2].sqldata = (void*)kjnsriymd;
#line 251 "A205syskan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 251 "A205syskan.sqc"
      sql_setdlist[3].sqldata = (void*)kkkjsriymd;
#line 251 "A205syskan.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 11;
#line 251 "A205syskan.sqc"
      sql_setdlist[4].sqldata = (void*)nxirisriymd;
#line 251 "A205syskan.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 251 "A205syskan.sqc"
      sql_setdlist[5].sqldata = (void*)ncnsksriymd;
#line 251 "A205syskan.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 251 "A205syskan.sqc"
      sql_setdlist[6].sqldata = (void*)nxbchsriymd;
#line 251 "A205syskan.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[7].sqltype = 452; sql_setdlist[7].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[7].sqldata = (void*)&iriendflg;
#line 251 "A205syskan.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[8].sqldata = (void*)irienddh;
#line 251 "A205syskan.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[9].sqldata = (void*)&nskendflg;
#line 251 "A205syskan.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[10].sqldata = (void*)nskenddh;
#line 251 "A205syskan.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[11].sqldata = (void*)&bchendflg;
#line 251 "A205syskan.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[12].sqldata = (void*)bchend0dh;
#line 251 "A205syskan.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[13].sqldata = (void*)bchend1dh;
#line 251 "A205syskan.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[14].sqldata = (void*)bchend2dh;
#line 251 "A205syskan.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[15].sqldata = (void*)bchend3dh;
#line 251 "A205syskan.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[16].sqldata = (void*)bchend4dh;
#line 251 "A205syskan.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[17].sqltype = 452; sql_setdlist[17].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[17].sqldata = (void*)&unyflg;
#line 251 "A205syskan.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 251 "A205syskan.sqc"
      sql_setdlist[18].sqldata = (void*)&ssntubn;
#line 251 "A205syskan.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 41;
#line 251 "A205syskan.sqc"
      sql_setdlist[19].sqldata = (void*)labonm;
#line 251 "A205syskan.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 41;
#line 251 "A205syskan.sqc"
      sql_setdlist[20].sqldata = (void*)knsmngr;
#line 251 "A205syskan.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 13;
#line 251 "A205syskan.sqc"
      sql_setdlist[21].sqldata = (void*)telno;
#line 251 "A205syskan.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[22].sqltype = 452; sql_setdlist[22].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[22].sqldata = (void*)&sriknflg01;
#line 251 "A205syskan.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[23].sqltype = 452; sql_setdlist[23].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[23].sqldata = (void*)&sriknflg02;
#line 251 "A205syskan.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[24].sqldata = (void*)&sriknflg03;
#line 251 "A205syskan.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[25].sqldata = (void*)&sriknflg04;
#line 251 "A205syskan.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[26].sqltype = 452; sql_setdlist[26].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[26].sqldata = (void*)&sriknflg05;
#line 251 "A205syskan.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[27].sqldata = (void*)&sriknflg06;
#line 251 "A205syskan.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[28].sqltype = 452; sql_setdlist[28].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[28].sqldata = (void*)&sriknflg07;
#line 251 "A205syskan.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[29].sqldata = (void*)&sriknflg08;
#line 251 "A205syskan.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[30].sqltype = 452; sql_setdlist[30].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[30].sqldata = (void*)&sriknflg09;
#line 251 "A205syskan.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[31].sqltype = 452; sql_setdlist[31].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[31].sqldata = (void*)&sriknflg10;
#line 251 "A205syskan.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[32].sqltype = 452; sql_setdlist[32].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[32].sqldata = (void*)&sriknflg11;
#line 251 "A205syskan.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[33].sqltype = 452; sql_setdlist[33].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[33].sqldata = (void*)&sriknflg12;
#line 251 "A205syskan.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[34].sqltype = 452; sql_setdlist[34].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[34].sqldata = (void*)&sriknflg13;
#line 251 "A205syskan.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[35].sqltype = 452; sql_setdlist[35].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[35].sqldata = (void*)&sriknflg14;
#line 251 "A205syskan.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[36].sqltype = 452; sql_setdlist[36].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[36].sqldata = (void*)&sriknflg15;
#line 251 "A205syskan.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[37].sqldata = (void*)&sriknflg16;
#line 251 "A205syskan.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[38].sqldata = (void*)&sriknflg17;
#line 251 "A205syskan.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[39].sqltype = 452; sql_setdlist[39].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[39].sqldata = (void*)&sriknflg18;
#line 251 "A205syskan.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[40].sqldata = (void*)&sriknflg19;
#line 251 "A205syskan.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[41].sqltype = 452; sql_setdlist[41].sqllen = 1;
#line 251 "A205syskan.sqc"
      sql_setdlist[41].sqldata = (void*)&sriknflg20;
#line 251 "A205syskan.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 9;
#line 251 "A205syskan.sqc"
      sql_setdlist[42].sqldata = (void*)hnktntid;
#line 251 "A205syskan.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sql_setdlist[43].sqltype = 460; sql_setdlist[43].sqllen = 27;
#line 251 "A205syskan.sqc"
      sql_setdlist[43].sqldata = (void*)ksndh;
#line 251 "A205syskan.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 251 "A205syskan.sqc"
      sqlasetdata(3,0,44,sql_setdlist,0L,0L);
    }
#line 251 "A205syskan.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 251 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 251 "A205syskan.sqc"
  sqlastop(0L);
}

#line 251 "A205syskan.sqc"


        if( SQLCODE == 100 )
            break;

        if( num % ALLOC_UNIT == 0 ) {
            array = (Sysknrmst*)ZbmlRealloc( array,
                                    sizeof( Sysknrmst ) * ( num + ALLOC_UNIT ) );
            memset( array + num, 0, sizeof( Sysknrmst ) * ALLOC_UNIT );
        }

        rec = array + num++;
        ZbmlMapHostToStruct( (char*)rec, SysknrmstArray );

		// add 2007.05.31 waj ��������ɋً}����������R�s�[
		memcpy(rec->kjnsriymd, rec->kkkjsriymd, sizeof(rec->kkkjsriymd));
    }

    
/*
EXEC SQL CLOSE c2;
*/

{
#line 269 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 269 "A205syskan.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 269 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 269 "A205syskan.sqc"
  sqlastop(0L);
}

#line 269 "A205syskan.sqc"


    *arrayOut = array;
    *numOut   = num;

    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 277 "A205syskan.sqc"

    return sqlca.sqlcode;
}

/******************************************************************************
 * ABunSyskanUpdate()
 *    SYSKNRMST ���R�[�h���X�V����
 * ������
 *    [I]  Sysknrmst* rec       �X�V�Ώۃ��R�[�h
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I��
 *           HRC_SQL_NOT_FOUND  �Ώۃ��R�[�h�Ȃ�
 *           HRC_NULL_POINTER   �p�����[�^�G���[
 *           HRC_INVALID_VALUE  �ݒ�l�s��
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ABunSyskanUpdate( char *sLbcd, char *sSateid, char flg, char cEndflg )
{
	memset(lbcd, 0, sizeof(lbcd));
	memset(sateid, 0, sizeof(sateid));
	strcpy(lbcd, sLbcd);
	strcpy(sateid, sSateid);
	bchendflg = cEndflg;

    
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 301 "A205syskan.sqc"

    
/*
EXEC SQL WHENEVER SQLERROR  GO TO error;
*/

#line 302 "A205syskan.sqc"


	if( flg == '0' ) {
    	
/*
EXEC SQL UPDATE SYSKNRMST
    	SET (
			BCHENDFLG,
			BCHEND0DH,
			KSNDH
    	) = (
			:bchendflg,
			CURRENT TIMESTAMP,
			CURRENT TIMESTAMP
    	) WHERE
			LBCD = :lbcd AND
			SATEID = :sateid;
*/

{
#line 316 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 316 "A205syskan.sqc"
  sqlaaloc(2,3,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 316 "A205syskan.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 316 "A205syskan.sqc"
      sql_setdlist[0].sqldata = (void*)&bchendflg;
#line 316 "A205syskan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 316 "A205syskan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 316 "A205syskan.sqc"
      sql_setdlist[1].sqldata = (void*)lbcd;
#line 316 "A205syskan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 316 "A205syskan.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 316 "A205syskan.sqc"
      sql_setdlist[2].sqldata = (void*)sateid;
#line 316 "A205syskan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 316 "A205syskan.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 316 "A205syskan.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 316 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 316 "A205syskan.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 316 "A205syskan.sqc"
  sqlastop(0L);
}

#line 316 "A205syskan.sqc"

	}
	if( flg == '1' ) {
    	
/*
EXEC SQL UPDATE SYSKNRMST
    	SET (
			BCHENDFLG,
			BCHEND1DH,
			KSNDH
    	) = (
			:bchendflg,
			CURRENT TIMESTAMP,
			CURRENT TIMESTAMP
    	) WHERE
			LBCD = :lbcd AND
			SATEID = :sateid;
*/

{
#line 330 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 330 "A205syskan.sqc"
  sqlaaloc(2,3,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 330 "A205syskan.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 330 "A205syskan.sqc"
      sql_setdlist[0].sqldata = (void*)&bchendflg;
#line 330 "A205syskan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 330 "A205syskan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 330 "A205syskan.sqc"
      sql_setdlist[1].sqldata = (void*)lbcd;
#line 330 "A205syskan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 330 "A205syskan.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 330 "A205syskan.sqc"
      sql_setdlist[2].sqldata = (void*)sateid;
#line 330 "A205syskan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 330 "A205syskan.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 330 "A205syskan.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 330 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 330 "A205syskan.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 330 "A205syskan.sqc"
  sqlastop(0L);
}

#line 330 "A205syskan.sqc"

	}
	if( flg == '2' ) {
    	
/*
EXEC SQL UPDATE SYSKNRMST
    	SET (
			BCHENDFLG,
			BCHEND2DH,
			KSNDH
    	) = (
			:bchendflg,
			CURRENT TIMESTAMP,
			CURRENT TIMESTAMP
    	) WHERE
			LBCD = :lbcd AND
			SATEID = :sateid;
*/

{
#line 344 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 344 "A205syskan.sqc"
  sqlaaloc(2,3,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 344 "A205syskan.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 344 "A205syskan.sqc"
      sql_setdlist[0].sqldata = (void*)&bchendflg;
#line 344 "A205syskan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 344 "A205syskan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 344 "A205syskan.sqc"
      sql_setdlist[1].sqldata = (void*)lbcd;
#line 344 "A205syskan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 344 "A205syskan.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 344 "A205syskan.sqc"
      sql_setdlist[2].sqldata = (void*)sateid;
#line 344 "A205syskan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 344 "A205syskan.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 344 "A205syskan.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 344 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 344 "A205syskan.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 344 "A205syskan.sqc"
  sqlastop(0L);
}

#line 344 "A205syskan.sqc"

	}
	if( flg == '3' ) {
    	
/*
EXEC SQL UPDATE SYSKNRMST
    	SET (
			BCHENDFLG,
			BCHEND3DH,
			KSNDH
    	) = (
			:bchendflg,
			CURRENT TIMESTAMP,
			CURRENT TIMESTAMP
    	) WHERE
			LBCD = :lbcd AND
			SATEID = :sateid;
*/

{
#line 358 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 358 "A205syskan.sqc"
  sqlaaloc(2,3,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 358 "A205syskan.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 358 "A205syskan.sqc"
      sql_setdlist[0].sqldata = (void*)&bchendflg;
#line 358 "A205syskan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 358 "A205syskan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 358 "A205syskan.sqc"
      sql_setdlist[1].sqldata = (void*)lbcd;
#line 358 "A205syskan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 358 "A205syskan.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 358 "A205syskan.sqc"
      sql_setdlist[2].sqldata = (void*)sateid;
#line 358 "A205syskan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 358 "A205syskan.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 358 "A205syskan.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 358 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 358 "A205syskan.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 358 "A205syskan.sqc"
  sqlastop(0L);
}

#line 358 "A205syskan.sqc"

	}
	if( flg == '4' ) {
    	
/*
EXEC SQL UPDATE SYSKNRMST
    	SET (
			BCHENDFLG,
			BCHEND4DH,
			KSNDH
    	) = (
			:bchendflg,
			CURRENT TIMESTAMP,
			CURRENT TIMESTAMP
    	) WHERE
			LBCD = :lbcd AND
			SATEID = :sateid;
*/

{
#line 372 "A205syskan.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 372 "A205syskan.sqc"
  sqlaaloc(2,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 372 "A205syskan.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 372 "A205syskan.sqc"
      sql_setdlist[0].sqldata = (void*)&bchendflg;
#line 372 "A205syskan.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 372 "A205syskan.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 372 "A205syskan.sqc"
      sql_setdlist[1].sqldata = (void*)lbcd;
#line 372 "A205syskan.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 372 "A205syskan.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 372 "A205syskan.sqc"
      sql_setdlist[2].sqldata = (void*)sateid;
#line 372 "A205syskan.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 372 "A205syskan.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 372 "A205syskan.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 372 "A205syskan.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 372 "A205syskan.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 372 "A205syskan.sqc"
  sqlastop(0L);
}

#line 372 "A205syskan.sqc"

	}
    return HRC_SQL_NORMAL;

notfound:
    
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 377 "A205syskan.sqc"

    return HRC_SQL_NOT_FOUND;

error:
    
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 381 "A205syskan.sqc"

    return sqlca.sqlcode;
}

/** End of File *********************************************************/