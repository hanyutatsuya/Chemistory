static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,88,65,110,85,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,50,48,53,75,78,74,65,0,0,0,0,0,0,0,0,
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


#line 1 "A205knja.sqc"
/**********************************************************************
 *
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����F A205knja.sqc
 *     �@�\�T�v  �F���ҏ��A�N�Z�X�֐�(�����W�J����)
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006-02-13                    Create
 **********************************************************************/

/********************************************************************/
/*  �C���N���[�h�錾                                                */
/********************************************************************/
#include <stdio.h>
#include "A205knja.h"
#include "bml_misc.h"
#include "bml_db.h"
#include "bml_dmm.h"

// add 20070521 waj ���b�N�Ή�
#include "bmllog.h"
#define RETRY			3
#define	ERR_LOCK		-911
#define	LOCK_WAIT_SEC	5   // �P�ʁF�b

#define ALLOC_UNIT		1


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 33 "A205knja.sqc"


/*--------------------------------------
// DB���b�v�ϐ���`
*/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 38 "A205knja.sqc"

	char    utkymd[11];
	char    irino[12];
	char    iriketflg;
	short   zssdino;
	char    sstcd[8];
	char    subsstcd[5];
	char    cdkbn1[3];
	char    cdkbn2[3];
	char    irimkey[41];
	char    srkcd[4];
	char    srknm[31];
	char    tticd[9];
	char    ttinm[41];
	char    gpcd[9];
	char    gpnm[41];
	char    skicd[9];
	char    skinm[41];
	char    krtno[41];
	char    knjid[16];
	char    knjnmn[61];
	char    knjnmk[31];
	char    knjnmkey[61];
	char    sc[6];
	char    tj[6];
	char    tjtni;
	char    sbtkbn;
	char    birthday[9];
	char    birthdaykbn;
	char    age[4];
	char    agekbn;
	char    btcd[11];
	char    btnm[31];
	char    utkcmtcd1[3];
	char    utkcmtcd2[3];
	char    utkcmtcd3[3];
	char    utkcmtfr1[71];
	char    utkcmtfr2[71];
	char    utkcmtfrflg;
	char    ngkbn;
	char    nsssu[3];
	char    hkncd;
	char    ktshsu[3];
	char    iniriymd[11];
	char    zssflg;
	char    kkiriflg;
	char    hknskbn;
	char    utkkbn;
	char    nekbn;
	char    inknskbn;
	char    utkjkkbn;
	char    krflg;
	char    fdhhkkflg;
	char    utkdh[9];
	char    mutkymd[11];
	char    mirino[12];
	char    knsjslbcd1[4];
	char    knsjslbcd2[4];
	char    knsjslbcd3[4];
	char    knsjslbcd4[4];
	char    ymhkkflg;
	char    hkkkbdh[9];
	char    ecd[4];
	char    shcd[3];
	char    sstssnmj[41];
	char    sstssnmn[41];
	char    sstrsj[21];
	char    sstrsn[21];
	char    sstsbt[3];
	char    ttsstflg;
	char    rucd[3];
	short   irikmksu;
	char    bmskn[51];
	char    irinrsbt[3];
	char    irihsmkbn;
	char    caresstflg;
	char    tktyflg;
	char    apkntino[14];
	char    sdnm[21];
	char    bko1[21];
	char    bko2[21];
	char    bko3[21];
	char    zstrdh[27];
	char    zsssdh[27];
	char    stlzsssdh[27];
	char    stlzsssip[16];
	char    stlzssssyaid[9];
	char    ksndh[27];
	char    oyasstcd[8];
	char    trkdh[27];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 128 "A205knja.sqc"



/*--------------------------------------
// DMM��`
*/
#define DMM_STRUCT	Kanjya

BmlDMMInfo	KanjyaArray[] = {
	DMM_SDATE( utkymd ),
	DMM_SSTRING( irino ),
	DMM_SCHAR( iriketflg ),
	DMM_SSHORT( zssdino ),
	DMM_SSTRING( sstcd ),
	DMM_SSTRING( subsstcd ),
	DMM_SSTRING( cdkbn1 ),
	DMM_SSTRING( cdkbn2 ),
	DMM_SSTRING( irimkey ),
	DMM_SSTRING( srkcd ),
	DMM_SSTRING( srknm ),
	DMM_SSTRING( tticd ),
	DMM_SSTRING( ttinm ),
	DMM_SSTRING( gpcd ),
	DMM_SSTRING( gpnm ),
	DMM_SSTRING( skicd ),
	DMM_SSTRING( skinm ),
	DMM_SSTRING( krtno ),
	DMM_SSTRING( knjid ),
	DMM_SSTRING( knjnmn ),
	DMM_SSTRING( knjnmk ),
	DMM_SSTRING( knjnmkey ),
	DMM_SSTRING( sc ),
	DMM_SSTRING( tj ),
	DMM_SCHAR( tjtni ),
	DMM_SCHAR( sbtkbn ),
	DMM_SSTRING( birthday ),
	DMM_SCHAR( birthdaykbn ),
	DMM_SSTRING( age ),
	DMM_SCHAR( agekbn ),
	DMM_SSTRING( btcd ),
	DMM_SSTRING( btnm ),
	DMM_SSTRING( utkcmtcd1 ),
	DMM_SSTRING( utkcmtcd2 ),
	DMM_SSTRING( utkcmtcd3 ),
	DMM_SSTRING( utkcmtfr1 ),
	DMM_SSTRING( utkcmtfr2 ),
	DMM_SCHAR( utkcmtfrflg ),
	DMM_SCHAR( ngkbn ),
	DMM_SSTRING( nsssu ),
	DMM_SCHAR( hkncd ),
	DMM_SSTRING( ktshsu ),
	DMM_SDATE( iniriymd ),
	DMM_SCHAR( zssflg ),
	DMM_SCHAR( kkiriflg ),
	DMM_SCHAR( hknskbn ),
	DMM_SCHAR( utkkbn ),
	DMM_SCHAR( nekbn ),
	DMM_SCHAR( inknskbn ),
	DMM_SCHAR( utkjkkbn ),
	DMM_SCHAR( krflg ),
	DMM_SCHAR( fdhhkkflg ),
	DMM_STIME( utkdh ),
	DMM_SDATE( mutkymd ),
	DMM_SSTRING( mirino ),
	DMM_SSTRING( knsjslbcd1 ),
	DMM_SSTRING( knsjslbcd2 ),
	DMM_SSTRING( knsjslbcd3 ),
	DMM_SSTRING( knsjslbcd4 ),
	DMM_SCHAR( ymhkkflg ),
	DMM_STIME( hkkkbdh ),
	DMM_SSTRING( ecd ),
	DMM_SSTRING( shcd ),
	DMM_SSTRING( sstssnmj ),
	DMM_SSTRING( sstssnmn ),
	DMM_SSTRING( sstrsj ),
	DMM_SSTRING( sstrsn ),
	DMM_SSTRING( sstsbt ),
	DMM_SCHAR( ttsstflg ),
	DMM_SSTRING( rucd ),
	DMM_SSHORT( irikmksu ),
	DMM_SSTRING( bmskn ),
	DMM_SSTRING( irinrsbt ),
	DMM_SCHAR( irihsmkbn ),
	DMM_SCHAR( caresstflg ),
	DMM_SCHAR( tktyflg ),
	DMM_SSTRING( apkntino ),
	DMM_SSTRING( sdnm ),
	DMM_SSTRING( bko1 ),
	DMM_SSTRING( bko2 ),
	DMM_SSTRING( bko3 ),
	DMM_STIMESTAMP( zstrdh ),
	DMM_STIMESTAMP( zsssdh ),
	DMM_STIMESTAMP( stlzsssdh ),
	DMM_SSTRING( stlzsssip ),
	DMM_SSTRING( stlzssssyaid ),
	DMM_STIMESTAMP( ksndh ),
	DMM_SSTRING( oyasstcd ),
	DMM_STIMESTAMP( trkdh ),
	DMM_NULL
};

/******************************************************************************
 * ABunKnjSel()
 *    KANJYA ���R�[�hKey�����擾
 * ������
 *    [I]  Kanjya* pKey       �擾���郌�R�[�h�̃L�[
 *    [O]  Kanjya** arrayOut    �擾���R�[�h�z��i�[�̈�
 *    [O]  int* numOut          �擾����
 * ���߂�l
 *    (long) HRC_SQL_NORMAL     ����I���i���R�[�h����j
 *           HRC_SQL_NOT_FOUND  ���R�[�h�Ȃ�
 *           HRC_SQL_ERR        DB�G���[
 ******************************************************************************/
long ABunKnjSel( Kanjya* pKey, Kanjya** arrayOut, int* numOut )
{
    Kanjya*     array = NULL;
    int         num = 0;
    // add 20070521 waj ���b�N�Ή�
	int			error = 0;

    if( !pKey )
        return HRC_NULL_POINTER;

    if( !ZbmlMapStructToHost( (char*)pKey, KanjyaArray ) )
        return HRC_INVALID_VALUE;
/*** ameno ***/
	sFncPutLog ( TRCKIND_WARNING, __FILE__, "ABunKnjSel", __LINE__,
		EXEFLG_NON, "00000000",
		"����SELECT ��t��(%s) �˗���No(%s)", utkymd, irino );
/*** ameno ***/

    // del 20070521 waj ���g���C���s�����ߊ����݂��֎~����
    //                  FETCH�ŃG���[�����������CLOSE�����s����Ȃ�
    // EXEC SQL WHENEVER SQLERROR GO TO error;

    // add 20070521 waj ���g���C�p���[�v�ݒ�
    int i;
    for (i = 0; i <= RETRY; i++) {
		error = 0;

	    
/*
EXEC SQL DECLARE c1 CURSOR FOR
	    SELECT
			UTKYMD,
			IRINO,
			IRIKETFLG,
			ZSSDINO,
			SSTCD,
			SUBSSTCD,
			CDKBN1,
			CDKBN2,
			IRIMKEY,
			SRKCD,
			SRKNM,
			TTICD,
			TTINM,
			GPCD,
			GPNM,
			SKICD,
			SKINM,
			KRTNO,
			KNJID,
			KNJNMN,
			KNJNMK,
			KNJNMKEY,
			SC,
			TJ,
			TJTNI,
			SBTKBN,
			BIRTHDAY,
			BIRTHDAYKBN,
			AGE,
			AGEKBN,
			BTCD,
			BTNM,
			UTKCMTCD1,
			UTKCMTCD2,
			UTKCMTCD3,
			UTKCMTFR1,
			UTKCMTFR2,
			UTKCMTFRFLG,
			NGKBN,
			NSSSU,
			HKNCD,
			KTSHSU,
			INIRIYMD,
			ZSSFLG,
			KKIRIFLG,
			HKNSKBN,
			UTKKBN,
			NEKBN,
			INKNSKBN,
			UTKJKKBN,
			KRFLG,
			FDHHKKFLG,
			UTKDH,
			MUTKYMD,
			MIRINO,
			KNSJSLBCD1,
			KNSJSLBCD2,
			KNSJSLBCD3,
			KNSJSLBCD4,
			YMHKKFLG,
			HKKKBDH,
			ECD,
			SHCD,
			SSTSSNMJ,
			SSTSSNMN,
			SSTRSJ,
			SSTRSN,
			SSTSBT,
			TTSSTFLG,
			RUCD,
			IRIKMKSU,
			BMSKN,
			IRINRSBT,
			IRIHSMKBN,
			CARESSTFLG,
			TKTYFLG,
			APKNTINO,
			SDNM,
			BKO1,
			BKO2,
			BKO3,
			ZSTRDH,
			ZSSSDH,
			STLZSSSDH,
			STLZSSSIP,
			STLZSSSSYAID,
			KSNDH,
			OYASSTCD,
			TRKDH
	    FROM
	        KANJYA
	    WHERE
			IRINO = :irino AND
			UTKYMD = :utkymd
			ORDER BY ZSSDINO DESC FOR READ ONLY;
*/

#line 364 "A205knja.sqc"

	
	    
/*
EXEC SQL OPEN c1;
*/

{
#line 366 "A205knja.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 366 "A205knja.sqc"
  sqlaaloc(2,2,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 366 "A205knja.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 12;
#line 366 "A205knja.sqc"
      sql_setdlist[0].sqldata = (void*)irino;
#line 366 "A205knja.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 366 "A205knja.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 11;
#line 366 "A205knja.sqc"
      sql_setdlist[1].sqldata = (void*)utkymd;
#line 366 "A205knja.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 366 "A205knja.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 366 "A205knja.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 366 "A205knja.sqc"
  sqlastop(0L);
}

#line 366 "A205knja.sqc"

	
	    while( 1 ) {
	        Kanjya* rec;
	
	        
/*
EXEC SQL FETCH c1 INTO
				:utkymd,
				:irino,
				:iriketflg,
				:zssdino,
				:sstcd,
				:subsstcd,
				:cdkbn1,
				:cdkbn2,
				:irimkey,
				:srkcd,
				:srknm,
				:tticd,
				:ttinm,
				:gpcd,
				:gpnm,
				:skicd,
				:skinm,
				:krtno,
				:knjid,
				:knjnmn,
				:knjnmk,
				:knjnmkey,
				:sc,
				:tj,
				:tjtni,
				:sbtkbn,
				:birthday,
				:birthdaykbn,
				:age,
				:agekbn,
				:btcd,
				:btnm,
				:utkcmtcd1,
				:utkcmtcd2,
				:utkcmtcd3,
				:utkcmtfr1,
				:utkcmtfr2,
				:utkcmtfrflg,
				:ngkbn,
				:nsssu,
				:hkncd,
				:ktshsu,
				:iniriymd,
				:zssflg,
				:kkiriflg,
				:hknskbn,
				:utkkbn,
				:nekbn,
				:inknskbn,
				:utkjkkbn,
				:krflg,
				:fdhhkkflg,
				:utkdh,
				:mutkymd,
				:mirino,
				:knsjslbcd1,
				:knsjslbcd2,
				:knsjslbcd3,
				:knsjslbcd4,
				:ymhkkflg,
				:hkkkbdh,
				:ecd,
				:shcd,
				:sstssnmj,
				:sstssnmn,
				:sstrsj,
				:sstrsn,
				:sstsbt,
				:ttsstflg,
				:rucd,
				:irikmksu,
				:bmskn,
				:irinrsbt,
				:irihsmkbn,
				:caresstflg,
				:tktyflg,
				:apkntino,
				:sdnm,
				:bko1,
				:bko2,
				:bko3,
				:zstrdh,
				:zsssdh,
				:stlzsssdh,
				:stlzsssip,
				:stlzssssyaid,
				:ksndh,
				:oyasstcd,
				:trkdh;
*/

{
#line 460 "A205knja.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 460 "A205knja.sqc"
  sqlaaloc(3,89,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[64];
#line 460 "A205knja.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 11;
#line 460 "A205knja.sqc"
      sql_setdlist[0].sqldata = (void*)utkymd;
#line 460 "A205knja.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 460 "A205knja.sqc"
      sql_setdlist[1].sqldata = (void*)irino;
#line 460 "A205knja.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[2].sqltype = 452; sql_setdlist[2].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[2].sqldata = (void*)&iriketflg;
#line 460 "A205knja.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 460 "A205knja.sqc"
      sql_setdlist[3].sqldata = (void*)&zssdino;
#line 460 "A205knja.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 8;
#line 460 "A205knja.sqc"
      sql_setdlist[4].sqldata = (void*)sstcd;
#line 460 "A205knja.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 460 "A205knja.sqc"
      sql_setdlist[5].sqldata = (void*)subsstcd;
#line 460 "A205knja.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[6].sqldata = (void*)cdkbn1;
#line 460 "A205knja.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[7].sqldata = (void*)cdkbn2;
#line 460 "A205knja.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 41;
#line 460 "A205knja.sqc"
      sql_setdlist[8].sqldata = (void*)irimkey;
#line 460 "A205knja.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 4;
#line 460 "A205knja.sqc"
      sql_setdlist[9].sqldata = (void*)srkcd;
#line 460 "A205knja.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 31;
#line 460 "A205knja.sqc"
      sql_setdlist[10].sqldata = (void*)srknm;
#line 460 "A205knja.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[11].sqltype = 460; sql_setdlist[11].sqllen = 9;
#line 460 "A205knja.sqc"
      sql_setdlist[11].sqldata = (void*)tticd;
#line 460 "A205knja.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 41;
#line 460 "A205knja.sqc"
      sql_setdlist[12].sqldata = (void*)ttinm;
#line 460 "A205knja.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 9;
#line 460 "A205knja.sqc"
      sql_setdlist[13].sqldata = (void*)gpcd;
#line 460 "A205knja.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 41;
#line 460 "A205knja.sqc"
      sql_setdlist[14].sqldata = (void*)gpnm;
#line 460 "A205knja.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 9;
#line 460 "A205knja.sqc"
      sql_setdlist[15].sqldata = (void*)skicd;
#line 460 "A205knja.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 41;
#line 460 "A205knja.sqc"
      sql_setdlist[16].sqldata = (void*)skinm;
#line 460 "A205knja.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 41;
#line 460 "A205knja.sqc"
      sql_setdlist[17].sqldata = (void*)krtno;
#line 460 "A205knja.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 16;
#line 460 "A205knja.sqc"
      sql_setdlist[18].sqldata = (void*)knjid;
#line 460 "A205knja.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 61;
#line 460 "A205knja.sqc"
      sql_setdlist[19].sqldata = (void*)knjnmn;
#line 460 "A205knja.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 31;
#line 460 "A205knja.sqc"
      sql_setdlist[20].sqldata = (void*)knjnmk;
#line 460 "A205knja.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 61;
#line 460 "A205knja.sqc"
      sql_setdlist[21].sqldata = (void*)knjnmkey;
#line 460 "A205knja.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 6;
#line 460 "A205knja.sqc"
      sql_setdlist[22].sqldata = (void*)sc;
#line 460 "A205knja.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 6;
#line 460 "A205knja.sqc"
      sql_setdlist[23].sqldata = (void*)tj;
#line 460 "A205knja.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[24].sqltype = 452; sql_setdlist[24].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[24].sqldata = (void*)&tjtni;
#line 460 "A205knja.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[25].sqltype = 452; sql_setdlist[25].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[25].sqldata = (void*)&sbtkbn;
#line 460 "A205knja.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[26].sqltype = 460; sql_setdlist[26].sqllen = 9;
#line 460 "A205knja.sqc"
      sql_setdlist[26].sqldata = (void*)birthday;
#line 460 "A205knja.sqc"
      sql_setdlist[26].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[27].sqltype = 452; sql_setdlist[27].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[27].sqldata = (void*)&birthdaykbn;
#line 460 "A205knja.sqc"
      sql_setdlist[27].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[28].sqltype = 460; sql_setdlist[28].sqllen = 4;
#line 460 "A205knja.sqc"
      sql_setdlist[28].sqldata = (void*)age;
#line 460 "A205knja.sqc"
      sql_setdlist[28].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[29].sqltype = 452; sql_setdlist[29].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[29].sqldata = (void*)&agekbn;
#line 460 "A205knja.sqc"
      sql_setdlist[29].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[30].sqltype = 460; sql_setdlist[30].sqllen = 11;
#line 460 "A205knja.sqc"
      sql_setdlist[30].sqldata = (void*)btcd;
#line 460 "A205knja.sqc"
      sql_setdlist[30].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[31].sqltype = 460; sql_setdlist[31].sqllen = 31;
#line 460 "A205knja.sqc"
      sql_setdlist[31].sqldata = (void*)btnm;
#line 460 "A205knja.sqc"
      sql_setdlist[31].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[32].sqltype = 460; sql_setdlist[32].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[32].sqldata = (void*)utkcmtcd1;
#line 460 "A205knja.sqc"
      sql_setdlist[32].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[33].sqltype = 460; sql_setdlist[33].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[33].sqldata = (void*)utkcmtcd2;
#line 460 "A205knja.sqc"
      sql_setdlist[33].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[34].sqltype = 460; sql_setdlist[34].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[34].sqldata = (void*)utkcmtcd3;
#line 460 "A205knja.sqc"
      sql_setdlist[34].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[35].sqltype = 460; sql_setdlist[35].sqllen = 71;
#line 460 "A205knja.sqc"
      sql_setdlist[35].sqldata = (void*)utkcmtfr1;
#line 460 "A205knja.sqc"
      sql_setdlist[35].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[36].sqltype = 460; sql_setdlist[36].sqllen = 71;
#line 460 "A205knja.sqc"
      sql_setdlist[36].sqldata = (void*)utkcmtfr2;
#line 460 "A205knja.sqc"
      sql_setdlist[36].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[37].sqltype = 452; sql_setdlist[37].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[37].sqldata = (void*)&utkcmtfrflg;
#line 460 "A205knja.sqc"
      sql_setdlist[37].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[38].sqltype = 452; sql_setdlist[38].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[38].sqldata = (void*)&ngkbn;
#line 460 "A205knja.sqc"
      sql_setdlist[38].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[39].sqltype = 460; sql_setdlist[39].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[39].sqldata = (void*)nsssu;
#line 460 "A205knja.sqc"
      sql_setdlist[39].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[40].sqltype = 452; sql_setdlist[40].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[40].sqldata = (void*)&hkncd;
#line 460 "A205knja.sqc"
      sql_setdlist[40].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[41].sqltype = 460; sql_setdlist[41].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[41].sqldata = (void*)ktshsu;
#line 460 "A205knja.sqc"
      sql_setdlist[41].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[42].sqltype = 460; sql_setdlist[42].sqllen = 11;
#line 460 "A205knja.sqc"
      sql_setdlist[42].sqldata = (void*)iniriymd;
#line 460 "A205knja.sqc"
      sql_setdlist[42].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[43].sqltype = 452; sql_setdlist[43].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[43].sqldata = (void*)&zssflg;
#line 460 "A205knja.sqc"
      sql_setdlist[43].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[44].sqltype = 452; sql_setdlist[44].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[44].sqldata = (void*)&kkiriflg;
#line 460 "A205knja.sqc"
      sql_setdlist[44].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[45].sqltype = 452; sql_setdlist[45].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[45].sqldata = (void*)&hknskbn;
#line 460 "A205knja.sqc"
      sql_setdlist[45].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[46].sqltype = 452; sql_setdlist[46].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[46].sqldata = (void*)&utkkbn;
#line 460 "A205knja.sqc"
      sql_setdlist[46].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[47].sqltype = 452; sql_setdlist[47].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[47].sqldata = (void*)&nekbn;
#line 460 "A205knja.sqc"
      sql_setdlist[47].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[48].sqltype = 452; sql_setdlist[48].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[48].sqldata = (void*)&inknskbn;
#line 460 "A205knja.sqc"
      sql_setdlist[48].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[49].sqltype = 452; sql_setdlist[49].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[49].sqldata = (void*)&utkjkkbn;
#line 460 "A205knja.sqc"
      sql_setdlist[49].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[50].sqltype = 452; sql_setdlist[50].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[50].sqldata = (void*)&krflg;
#line 460 "A205knja.sqc"
      sql_setdlist[50].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[51].sqltype = 452; sql_setdlist[51].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[51].sqldata = (void*)&fdhhkkflg;
#line 460 "A205knja.sqc"
      sql_setdlist[51].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[52].sqltype = 460; sql_setdlist[52].sqllen = 9;
#line 460 "A205knja.sqc"
      sql_setdlist[52].sqldata = (void*)utkdh;
#line 460 "A205knja.sqc"
      sql_setdlist[52].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[53].sqltype = 460; sql_setdlist[53].sqllen = 11;
#line 460 "A205knja.sqc"
      sql_setdlist[53].sqldata = (void*)mutkymd;
#line 460 "A205knja.sqc"
      sql_setdlist[53].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[54].sqltype = 460; sql_setdlist[54].sqllen = 12;
#line 460 "A205knja.sqc"
      sql_setdlist[54].sqldata = (void*)mirino;
#line 460 "A205knja.sqc"
      sql_setdlist[54].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[55].sqltype = 460; sql_setdlist[55].sqllen = 4;
#line 460 "A205knja.sqc"
      sql_setdlist[55].sqldata = (void*)knsjslbcd1;
#line 460 "A205knja.sqc"
      sql_setdlist[55].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[56].sqltype = 460; sql_setdlist[56].sqllen = 4;
#line 460 "A205knja.sqc"
      sql_setdlist[56].sqldata = (void*)knsjslbcd2;
#line 460 "A205knja.sqc"
      sql_setdlist[56].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[57].sqltype = 460; sql_setdlist[57].sqllen = 4;
#line 460 "A205knja.sqc"
      sql_setdlist[57].sqldata = (void*)knsjslbcd3;
#line 460 "A205knja.sqc"
      sql_setdlist[57].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[58].sqltype = 460; sql_setdlist[58].sqllen = 4;
#line 460 "A205knja.sqc"
      sql_setdlist[58].sqldata = (void*)knsjslbcd4;
#line 460 "A205knja.sqc"
      sql_setdlist[58].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[59].sqltype = 452; sql_setdlist[59].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[59].sqldata = (void*)&ymhkkflg;
#line 460 "A205knja.sqc"
      sql_setdlist[59].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[60].sqltype = 460; sql_setdlist[60].sqllen = 9;
#line 460 "A205knja.sqc"
      sql_setdlist[60].sqldata = (void*)hkkkbdh;
#line 460 "A205knja.sqc"
      sql_setdlist[60].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[61].sqltype = 460; sql_setdlist[61].sqllen = 4;
#line 460 "A205knja.sqc"
      sql_setdlist[61].sqldata = (void*)ecd;
#line 460 "A205knja.sqc"
      sql_setdlist[61].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[62].sqltype = 460; sql_setdlist[62].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[62].sqldata = (void*)shcd;
#line 460 "A205knja.sqc"
      sql_setdlist[62].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[63].sqltype = 460; sql_setdlist[63].sqllen = 41;
#line 460 "A205knja.sqc"
      sql_setdlist[63].sqldata = (void*)sstssnmj;
#line 460 "A205knja.sqc"
      sql_setdlist[63].sqlind = 0L;
#line 460 "A205knja.sqc"
      sqlasetdata(3,0,64,sql_setdlist,0L,0L);
    }
    {
      struct sqla_setdata_list sql_setdlist[25];
#line 460 "A205knja.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 41;
#line 460 "A205knja.sqc"
      sql_setdlist[0].sqldata = (void*)sstssnmn;
#line 460 "A205knja.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 21;
#line 460 "A205knja.sqc"
      sql_setdlist[1].sqldata = (void*)sstrsj;
#line 460 "A205knja.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 21;
#line 460 "A205knja.sqc"
      sql_setdlist[2].sqldata = (void*)sstrsn;
#line 460 "A205knja.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[3].sqldata = (void*)sstsbt;
#line 460 "A205knja.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[4].sqltype = 452; sql_setdlist[4].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[4].sqldata = (void*)&ttsstflg;
#line 460 "A205knja.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[5].sqldata = (void*)rucd;
#line 460 "A205knja.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 460 "A205knja.sqc"
      sql_setdlist[6].sqldata = (void*)&irikmksu;
#line 460 "A205knja.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 460 "A205knja.sqc"
      sql_setdlist[7].sqldata = (void*)bmskn;
#line 460 "A205knja.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 3;
#line 460 "A205knja.sqc"
      sql_setdlist[8].sqldata = (void*)irinrsbt;
#line 460 "A205knja.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[9].sqltype = 452; sql_setdlist[9].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[9].sqldata = (void*)&irihsmkbn;
#line 460 "A205knja.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[10].sqltype = 452; sql_setdlist[10].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[10].sqldata = (void*)&caresstflg;
#line 460 "A205knja.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[11].sqltype = 452; sql_setdlist[11].sqllen = 1;
#line 460 "A205knja.sqc"
      sql_setdlist[11].sqldata = (void*)&tktyflg;
#line 460 "A205knja.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[12].sqltype = 460; sql_setdlist[12].sqllen = 14;
#line 460 "A205knja.sqc"
      sql_setdlist[12].sqldata = (void*)apkntino;
#line 460 "A205knja.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[13].sqltype = 460; sql_setdlist[13].sqllen = 21;
#line 460 "A205knja.sqc"
      sql_setdlist[13].sqldata = (void*)sdnm;
#line 460 "A205knja.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[14].sqltype = 460; sql_setdlist[14].sqllen = 21;
#line 460 "A205knja.sqc"
      sql_setdlist[14].sqldata = (void*)bko1;
#line 460 "A205knja.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[15].sqltype = 460; sql_setdlist[15].sqllen = 21;
#line 460 "A205knja.sqc"
      sql_setdlist[15].sqldata = (void*)bko2;
#line 460 "A205knja.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[16].sqltype = 460; sql_setdlist[16].sqllen = 21;
#line 460 "A205knja.sqc"
      sql_setdlist[16].sqldata = (void*)bko3;
#line 460 "A205knja.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[17].sqltype = 460; sql_setdlist[17].sqllen = 27;
#line 460 "A205knja.sqc"
      sql_setdlist[17].sqldata = (void*)zstrdh;
#line 460 "A205knja.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[18].sqltype = 460; sql_setdlist[18].sqllen = 27;
#line 460 "A205knja.sqc"
      sql_setdlist[18].sqldata = (void*)zsssdh;
#line 460 "A205knja.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[19].sqltype = 460; sql_setdlist[19].sqllen = 27;
#line 460 "A205knja.sqc"
      sql_setdlist[19].sqldata = (void*)stlzsssdh;
#line 460 "A205knja.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[20].sqltype = 460; sql_setdlist[20].sqllen = 16;
#line 460 "A205knja.sqc"
      sql_setdlist[20].sqldata = (void*)stlzsssip;
#line 460 "A205knja.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[21].sqltype = 460; sql_setdlist[21].sqllen = 9;
#line 460 "A205knja.sqc"
      sql_setdlist[21].sqldata = (void*)stlzssssyaid;
#line 460 "A205knja.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[22].sqltype = 460; sql_setdlist[22].sqllen = 27;
#line 460 "A205knja.sqc"
      sql_setdlist[22].sqldata = (void*)ksndh;
#line 460 "A205knja.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[23].sqltype = 460; sql_setdlist[23].sqllen = 8;
#line 460 "A205knja.sqc"
      sql_setdlist[23].sqldata = (void*)oyasstcd;
#line 460 "A205knja.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 460 "A205knja.sqc"
      sql_setdlist[24].sqltype = 460; sql_setdlist[24].sqllen = 27;
#line 460 "A205knja.sqc"
      sql_setdlist[24].sqldata = (void*)trkdh;
#line 460 "A205knja.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 460 "A205knja.sqc"
      sqlasetdata(3,64,25,sql_setdlist,0L,0L);
    }
#line 460 "A205knja.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 460 "A205knja.sqc"
  sqlastop(0L);
}

#line 460 "A205knja.sqc"

	
	        if( SQLCODE == 100 )
	            break;
	
            // add 20070521 waj ���b�N���̃��g���C�Ή�
            if (sqlca.sqlcode < 0) {
                // �G���[�������͗̈������ău���C�N
                if (array != NULL) {
                    ZbmlFree(array);
                    array = NULL;
                    num   = 0;
                }
				error = sqlca.sqlcode;
				sFncPutLog ( TRCKIND_ERROR, __FILE__, "ABunKnjSel", __LINE__,
							 EXEFLG_NON, "020", "DB�G���[���� [sqlcode : %d]", sqlca.sqlcode ) ;
                break;
            }

	        if( num % ALLOC_UNIT == 0 ) {
	            array = (Kanjya*)ZbmlRealloc( array,
	                                    sizeof( Kanjya ) * ( num + ALLOC_UNIT ) );
	            memset( array + num, 0, sizeof( Kanjya ) * ALLOC_UNIT );
	        }
	
	        rec = array + num++;
	        ZbmlMapHostToStruct( (char*)rec, KanjyaArray );
	    }
	
	    
/*
EXEC SQL CLOSE c1;
*/

{
#line 489 "A205knja.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 489 "A205knja.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 489 "A205knja.sqc"
  sqlastop(0L);
}

#line 489 "A205knja.sqc"

	
        // add 20070521 waj ���b�N���̃��g���C�Ή�
        //                  ���b�N�̏ꍇ�̓��g���C�A���b�N�ȊO�̃G���[�̓f�[�^�����ŏI��
        //                  ���g���C�͂T�b�҂��Ă���
        if (error == ERR_LOCK) {
			sFncPutLog ( TRCKIND_ERROR, __FILE__, "ABunKnjSel", __LINE__,
						 EXEFLG_NON, "020", "���b�N�ɂ�郊�g���C[%d]���", i ) ;
            sleep(LOCK_WAIT_SEC);
            continue;
        }

	    *arrayOut = array;
	    *numOut   = num;
	
	    return num ? HRC_SQL_NORMAL : HRC_SQL_NOT_FOUND;

    // add 20070521 waj ���g���C�p���[�v�I�[
    }

    // add 20070521 waj ���g���C���Ă��G���[�̏ꍇ�A�f�[�^�����ŏI��
	*arrayOut = NULL;
	*numOut   = 0;
	return HRC_SQL_NOT_FOUND;

// del 20070521 waj ���g���C���s�����ߊ����݂��֎~����
// error:
//     EXEC SQL WHENEVER SQLERROR CONTINUE;
//     return sqlca.sqlcode;
}

/** End of File *********************************************************/
