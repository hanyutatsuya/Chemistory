static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,99,65,121,108,84,71,77,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,65,68,49,48,56,95,48,49,0,0,0,0,0,0,0,0,
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


#line 1 "AD108_01.sqc"
/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FAD108_01. sqc                                                */
/* �@�T�@�@�@�v�F�R�h�c���W�J                                               */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2008/02/12     moriya         �V�K�쐬                           */
/*  1.01     2008/11/13     sekiya         ��܂v�r�̕��я������������Ȃ邱�� */
/*                                         �ɑ΂���Ή�                       */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sql.h"
#include "bmllog.h"
#include "AD108.h"


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 26 "AD108_01.sqc"


/******************************************************************************/
/* �O���[�o���錾                                                             */
/******************************************************************************/

/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 31 "AD108_01.sqc"

char		sel_lbcd[3+1] ;
char		sel_sateid[3+1] ;
char		upd_nskendflg ;
char		sel_utkymd[10+1] ;
char		sel_sriymd[10+1] ;
char		sel_kntno[13+1] ;
char		sel_irino[11+1] ;
char		upd_id2[8+1] ;
short		upd_id2pos ;
char		upd_id3[8+1] ;
short		upd_id3pos ;
/* 1.01 �Z���N�g�����ɃT���v�����O�R�[�h��ǉ� */
char        sel_smpcd[7+1] ;
char		upd_bnckka ;
short		upd_srtkey ;
sqlint32	rec_cnt ;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 48 "AD108_01.sqc"




/******************************************************************************/
/* �֐��錾                                                                   */
/******************************************************************************/

/******************************************************************************/
/*�@�� �� ���@�FsFncUpdSYSKNRMST()											  */
/*�@�@�\�T�v�@�F�V�X�e���Ǘ��}�X�^�e�[�u���X�V								  */
/*�@���@�@�́@�F															  */
/*�@ ��P���� �F	���{�R�[�h												  */
/*�@ ��Q���� �F	�T�e���C�g�h�c											  */
/*�@ ��R���� �F	�F���d�m�c�t���O										  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int
sFncUpdSYSKNRMST( char *sLbcd, char *sSateid, char cEndflg )
{

	memset(sel_lbcd, 0, sizeof(sel_lbcd)) ;
	memset(sel_sateid, 0, sizeof(sel_sateid)) ;
	strcpy(sel_lbcd, sLbcd) ;
	strcpy(sel_sateid, sSateid) ;
	upd_nskendflg = cEndflg ;

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound ;
*/

#line 78 "AD108_01.sqc"

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error ;
*/

#line 79 "AD108_01.sqc"


	/***
	 ***	�V�X�e���Ǘ��}�X�^�e�[�u���X�V
	 ***		�X�V����
	 ***			�F���d�m�c�t���O
	 ***			�F���d�m�c����
	 ***			���X�V����
	 ***		��������
	 ***			���{�R�[�h
	 ***			�T�e���C�g�h�c
	 ***/
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdSYSKNRMST", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE [SYSKNRMST] CLM[NSKENDFLG=(%c) NSKENDDH=CURRENT_TIMESTAMP KSNDH=CURRENT_TIMESTAMP] WHERE[LBCD=(%s) SATEID=(%s)]",
				 upd_nskendflg, sel_lbcd, sel_sateid );

	
/*
EXEC SQL UPDATE SYSKNRMST
	SET
		NSKENDFLG = :upd_nskendflg,
		NSKENDDH  = CURRENT TIMESTAMP,
		KSNDH     = CURRENT TIMESTAMP
	WHERE
		LBCD      = :sel_lbcd AND
		SATEID    = :sel_sateid ;
*/

{
#line 102 "AD108_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 102 "AD108_01.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 102 "AD108_01.sqc"
      sql_setdlist[0].sqltype = 452; sql_setdlist[0].sqllen = 1;
#line 102 "AD108_01.sqc"
      sql_setdlist[0].sqldata = (void*)&upd_nskendflg;
#line 102 "AD108_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 102 "AD108_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 4;
#line 102 "AD108_01.sqc"
      sql_setdlist[1].sqldata = (void*)sel_lbcd;
#line 102 "AD108_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 102 "AD108_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 4;
#line 102 "AD108_01.sqc"
      sql_setdlist[2].sqldata = (void*)sel_sateid;
#line 102 "AD108_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 102 "AD108_01.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 102 "AD108_01.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 102 "AD108_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 102 "AD108_01.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 102 "AD108_01.sqc"
  sqlastop(0L);
}

#line 102 "AD108_01.sqc"


	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdSYSKNRMST", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE SYSKNRMST END" );

	return ( 0 ) ;

notfound:
	
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 110 "AD108_01.sqc"

	return 100;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 114 "AD108_01.sqc"

	sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncUpdSYSKNRMST", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "SQLCODE:%ld SQLSTATE:%5.5s UPDATE [SYSKNRMST] CLM[NSKENDFLG=(%c) NSKENDDH=CURRENT_TIMESTAMP KSNDH=CURRENT_TIMESTAMP] WHERE[LBCD=(%s) SATEID=(%s)]",
				 sqlca.sqlcode, sqlca.sqlstate, upd_nskendflg, sel_lbcd, sel_sateid ) ;
	return ( sqlca.sqlcode ) ;
}

/******************************************************************************/
/*�@�� �� ���@�FsFncSelBUNCHU()												  */
/*�@�@�\�T�v�@�F�������ʃe�[�u������										  */
/*              1.01 �T���v�����O�R�[�h���Ƃɕ������ʂ��擾����悤�ɕύX     */
/*�@���@�@�́@�F															  */
/*�@ ��P���� �F	�a�t�m�o�n�r���R�[�h									  */
/*�@ ��Q���� �F	��������												  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int
sFncSelBUNCHU( pId3Info, precSortInfo, precCnt )
ID3TB		*pId3Info ;
SORTInfo	**precSortInfo ;
int			*precCnt ;
{

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 140 "AD108_01.sqc"


	// �J�E���^
	int     irecCnt = 0 ;
	SORTInfo	sqlSortInfo ;

	/***
	 ***	�ϐ�������
	 ***/
	// �����L�[
	sprintf ( sel_utkymd, "%4.4s-%2.2s-%2.2s", pId3Info->cUtkymd, &pId3Info->cUtkymd[4], &pId3Info->cUtkymd[6] ) ;
	strcpy ( sel_irino,  pId3Info->cIrino ) ;
	sprintf ( sel_sriymd, "%4.4s-%2.2s-%2.2s", pId3Info->cSriymd, &pId3Info->cSriymd[4], &pId3Info->cSriymd[6] ) ;
	strcpy ( sel_kntno,  pId3Info->cKntno ) ;

    strcpy ( sel_smpcd,  sqlSortInfo.cSmpcd ) ;
	upd_bnckka =  sqlSortInfo.cBnckka ;
	*precSortInfo = ( SORTInfo * ) malloc ( sizeof *precSortInfo ) ;	
	
	/***
	 ***	�������ʃe�[�u������
	 ***		��������
	 ***			�T���v�����O�R�[�h
	 ***			��������
	 ***		��������
	 ***			�a�l�k��t�N����
	 ***			�˗����m��
	 ***			������
	 ***			���̂m��
	 ***/
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncSelBUNCHU", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				 "SELECT [BUNCHU]  CLM[DISITNCT SMPCD],[BNCKKA] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 sel_utkymd, sel_irino, sel_sriymd, sel_kntno );

	
/*
EXEC SQL DECLARE c_bunchu CURSOR FOR

	SELECT
		DISTINCT SMPCD,
		BNCKKA
	FROM
		BUNCHU
	WHERE
		KNTNO  = :sel_kntno AND
		IRINO  = :sel_irino AND
		SRIYMD = :sel_sriymd AND
		UTKYMD = :sel_utkymd
	FOR READ ONLY ;
*/

#line 186 "AD108_01.sqc"


	
/*
EXEC SQL OPEN c_bunchu ;
*/

{
#line 188 "AD108_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 188 "AD108_01.sqc"
  sqlaaloc(2,4,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 188 "AD108_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 14;
#line 188 "AD108_01.sqc"
      sql_setdlist[0].sqldata = (void*)sel_kntno;
#line 188 "AD108_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 188 "AD108_01.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 12;
#line 188 "AD108_01.sqc"
      sql_setdlist[1].sqldata = (void*)sel_irino;
#line 188 "AD108_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 188 "AD108_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 11;
#line 188 "AD108_01.sqc"
      sql_setdlist[2].sqldata = (void*)sel_sriymd;
#line 188 "AD108_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 188 "AD108_01.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 11;
#line 188 "AD108_01.sqc"
      sql_setdlist[3].sqldata = (void*)sel_utkymd;
#line 188 "AD108_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 188 "AD108_01.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 188 "AD108_01.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 188 "AD108_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 188 "AD108_01.sqc"
  sqlastop(0L);
}

#line 188 "AD108_01.sqc"

    while( 1 ) {
		
/*
EXEC SQL FETCH c_bunchu INTO
			:sel_smpcd, 
			:upd_bnckka ;
*/

{
#line 192 "AD108_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 192 "AD108_01.sqc"
  sqlaaloc(3,2,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 192 "AD108_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 8;
#line 192 "AD108_01.sqc"
      sql_setdlist[0].sqldata = (void*)sel_smpcd;
#line 192 "AD108_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 192 "AD108_01.sqc"
      sql_setdlist[1].sqltype = 452; sql_setdlist[1].sqllen = 1;
#line 192 "AD108_01.sqc"
      sql_setdlist[1].sqldata = (void*)&upd_bnckka;
#line 192 "AD108_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 192 "AD108_01.sqc"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 192 "AD108_01.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 192 "AD108_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 192 "AD108_01.sqc"
  sqlastop(0L);
}

#line 192 "AD108_01.sqc"


		if ( SQLCODE == 100 ) {
			break;
		}

		memcpy ( &(sqlSortInfo.cSmpcd)  , &sel_smpcd, sizeof ( sel_smpcd ) ) ;
		sqlSortInfo.cBnckka = upd_bnckka ;

        *precSortInfo = ( SORTInfo * ) realloc ( *precSortInfo, sizeof ( SORTInfo ) * ( irecCnt + 1 ) ) ;
        if ( precSortInfo == NULL ) {
            return ( -1 ) ;
        }
		memcpy ( &(*precSortInfo)[irecCnt], &sqlSortInfo, sizeof ( sqlSortInfo ) ) ;

		irecCnt ++ ;
	}

	
/*
EXEC SQL CLOSE c_bunchu ;
*/

{
#line 210 "AD108_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 210 "AD108_01.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 210 "AD108_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 210 "AD108_01.sqc"
  sqlastop(0L);
}

#line 210 "AD108_01.sqc"


    *precCnt = irecCnt ;

	/* �J�E���^�̐����Q�Ƃ��� 0 �Ȃ�΁ANOT FOUND */
	if ( irecCnt > 0 ) {
		sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncSelBUNCHU", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
					 "SELECT BUNCHU END - BNCKKA"  );

		return ( 0 ) ;
	}
	else if (irecCnt == 0 ) {
		return 100;
	}

/*  �r�p�k���ʎ擾�����[�v�ɂ����̂ŁA�폜
/notfound:
/	EXEC SQL WHENEVER NOT FOUND CONTINUE;
/	return 100;
*/

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 232 "AD108_01.sqc"

	sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncSelBUNCHU", __LINE__, EXEFLG_SEL, MYAPP_LOG_ERRCODE_NON,
				 "SQLCODE:%ld SQLSTATE:%5.5s SELECT [BUNCHU] CLM[DISTINCT SMPCD] [BNCKKA] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 sqlca.sqlcode, sqlca.sqlstate, sel_utkymd, sel_irino, sel_sriymd, sel_kntno ) ;
	return ( sqlca.sqlcode ) ;
}

/******************************************************************************/
/*�@�� �� ���@�FsFncUpdBUNCHU()												  */
/*�@�@�\�T�v�@�F�������ʃe�[�u���X�V										  */
/*              1.01 �X�V�P�ʂ�����NO + �T���v�����O�R�[�h �ɕύX             */
/*�@���@�@�́@�F															  */
/*�@ ��P���� �F	�a�t�m�o�n�r���R�[�h									  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int
sFncUpdBUNCHU( pId3Info, pSortInfo )
ID3TB		*pId3Info ;
SORTInfo	*pSortInfo ;
{

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO notfound;
*/

#line 256 "AD108_01.sqc"

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 257 "AD108_01.sqc"


	/***
	 ***	�ϐ�������
	 ***/
	// �����L�[
	sprintf ( sel_utkymd, "%4.4s-%2.2s-%2.2s", pId3Info->cUtkymd, &pId3Info->cUtkymd[4], &pId3Info->cUtkymd[6] ) ;
	strcpy ( sel_irino,  pId3Info->cIrino ) ;
	sprintf ( sel_sriymd, "%4.4s-%2.2s-%2.2s", pId3Info->cSriymd, &pId3Info->cSriymd[4], &pId3Info->cSriymd[6] ) ;
	strcpy ( sel_kntno,  pId3Info->cKntno ) ;
	strcpy ( sel_smpcd,  pSortInfo->cSmpcd) ;

	// �X�V�l
	strcpy ( upd_id2, pId3Info->cRackId ) ;
	upd_id2pos = atoi ( pId3Info->cRackPos ) ;
	upd_srtkey = pSortInfo->iSrtkey ;

	/***
	 ***	�������ʃe�[�u���X�V
	 ***		�X�V����
	 ***			�Q���h�c
	 ***			�Q���o�n�r
	 ***			�\�[�g�L�[
	 ***		��������
	 ***			�a�l�k��t�N����
	 ***			�˗����m��
	 ***			������
	 ***			���̂m��
	 ***			�T���v�����O�R�[�h
	 ***/
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdBUNCHU", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE [BUNCHU]  CLM[ID2=(%s) ID2POS=(%d) SRTKEY=(%d) KSNDH=CURRENT_TIMESTAMP] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 upd_id2, upd_id2pos, upd_srtkey, sel_utkymd, sel_irino, sel_sriymd, sel_kntno );

	
/*
EXEC SQL UPDATE BUNCHU
	SET
		ID2    = :upd_id2,
		ID2POS = :upd_id2pos,
		SRTKEY = :upd_srtkey,
		KSNDH  = CURRENT TIMESTAMP
	WHERE
		KNTNO  = :sel_kntno AND
		IRINO  = :sel_irino AND
		SRIYMD = :sel_sriymd AND
		UTKYMD = :sel_utkymd AND
		SMPCD  = :sel_smpcd ;
*/

{
#line 302 "AD108_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 302 "AD108_01.sqc"
  sqlaaloc(2,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 302 "AD108_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 302 "AD108_01.sqc"
      sql_setdlist[0].sqldata = (void*)upd_id2;
#line 302 "AD108_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 302 "AD108_01.sqc"
      sql_setdlist[1].sqldata = (void*)&upd_id2pos;
#line 302 "AD108_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 302 "AD108_01.sqc"
      sql_setdlist[2].sqldata = (void*)&upd_srtkey;
#line 302 "AD108_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 14;
#line 302 "AD108_01.sqc"
      sql_setdlist[3].sqldata = (void*)sel_kntno;
#line 302 "AD108_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 12;
#line 302 "AD108_01.sqc"
      sql_setdlist[4].sqldata = (void*)sel_irino;
#line 302 "AD108_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 11;
#line 302 "AD108_01.sqc"
      sql_setdlist[5].sqldata = (void*)sel_sriymd;
#line 302 "AD108_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 302 "AD108_01.sqc"
      sql_setdlist[6].sqldata = (void*)sel_utkymd;
#line 302 "AD108_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 8;
#line 302 "AD108_01.sqc"
      sql_setdlist[7].sqldata = (void*)sel_smpcd;
#line 302 "AD108_01.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 302 "AD108_01.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 302 "AD108_01.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 302 "AD108_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 302 "AD108_01.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto notfound;
  }
#line 302 "AD108_01.sqc"
  sqlastop(0L);
}

#line 302 "AD108_01.sqc"


	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdBUNCHU", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE BUNCHU END" );

	return ( 0 ) ;

notfound:
	
/*
EXEC SQL WHENEVER NOT FOUND CONTINUE;
*/

#line 310 "AD108_01.sqc"

	return 100;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 314 "AD108_01.sqc"

	sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncUpdBUNCHU", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "SQLCODE:%ld SQLSTATE:%5.5s UPDATE [BUNCHU] CLM[ID2=(%s) ID2POS=(%d) KSNDH=CURRENT_TIMESTAMP] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 sqlca.sqlcode, sqlca.sqlstate, upd_id2, upd_id2pos, sel_utkymd, sel_irino, sel_sriymd, sel_kntno ) ;
	return ( sqlca.sqlcode ) ;
}

/******************************************************************************/
/*�@�� �� ���@�FsFncUpdKENZOK()												  */
/*�@�@�\�T�v�@�F���̑������e�[�u���X�V									  */
/*�@���@�@�́@�F															  */
/*�@ ��P���� �F	�a�t�m�o�n�r���R�[�h									  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int
sFncUpdKENZOK( pId3Info )
ID3TB	*pId3Info ;
{

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 336 "AD108_01.sqc"


	/***
	 ***	�ϐ�������
	 ***/
	// �����L�[
	sprintf ( sel_utkymd, "%4.4s-%2.2s-%2.2s", pId3Info->cUtkymd, &pId3Info->cUtkymd[4], &pId3Info->cUtkymd[6] ) ;
	strcpy ( sel_irino,  pId3Info->cIrino ) ;
	sprintf ( sel_sriymd, "%4.4s-%2.2s-%2.2s", pId3Info->cSriymd, &pId3Info->cSriymd[4], &pId3Info->cSriymd[6] ) ;
	strcpy ( sel_kntno,  pId3Info->cKntno ) ;
	// �X�V�l
	strcpy ( upd_id2, pId3Info->cRackId ) ;
	upd_id2pos = atoi ( pId3Info->cRackPos ) ;
	strcpy ( upd_id3, pId3Info->cRackId ) ;
	upd_id3pos = atoi ( pId3Info->cRackPos ) ;

	/***
	 ***	���̑������e�[�u���X�V
	 ***		�X�V����
	 ***			�Q���h�c
	 ***			�Q���o�n�r
	 ***			�R���h�c
	 ***			�R���o�n�r
	 ***		��������
	 ***			�a�l�k��t�N����
	 ***			�˗����m��
	 ***			������
	 ***			���̂m��
	 ***/
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdKENZOK", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE [KENZOK]  CLM[ID2=(%s) ID2POS=(%d) ID3=(%s) ID3POS=(%d) KSNDH=CURRENT_TIMESTAMP] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 upd_id2, upd_id2pos, upd_id3, upd_id3pos, sel_utkymd, sel_irino, sel_sriymd, sel_kntno );

	
/*
EXEC SQL UPDATE KENZOK
	SET
		ID2    = :upd_id2,
		ID2POS = :upd_id2pos,
		ID3    = :upd_id3,
		ID3POS = :upd_id3pos,
		KSNDH  = CURRENT TIMESTAMP
	WHERE
		KNTNO  = :sel_kntno AND
		IRINO  = :sel_irino AND
		SRIYMD = :sel_sriymd AND
		UTKYMD = :sel_utkymd ;
*/

{
#line 380 "AD108_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 380 "AD108_01.sqc"
  sqlaaloc(2,8,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 380 "AD108_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 380 "AD108_01.sqc"
      sql_setdlist[0].sqldata = (void*)upd_id2;
#line 380 "AD108_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 380 "AD108_01.sqc"
      sql_setdlist[1].sqldata = (void*)&upd_id2pos;
#line 380 "AD108_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 380 "AD108_01.sqc"
      sql_setdlist[2].sqldata = (void*)upd_id3;
#line 380 "AD108_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 380 "AD108_01.sqc"
      sql_setdlist[3].sqldata = (void*)&upd_id3pos;
#line 380 "AD108_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 14;
#line 380 "AD108_01.sqc"
      sql_setdlist[4].sqldata = (void*)sel_kntno;
#line 380 "AD108_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 12;
#line 380 "AD108_01.sqc"
      sql_setdlist[5].sqldata = (void*)sel_irino;
#line 380 "AD108_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 380 "AD108_01.sqc"
      sql_setdlist[6].sqldata = (void*)sel_sriymd;
#line 380 "AD108_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 380 "AD108_01.sqc"
      sql_setdlist[7].sqldata = (void*)sel_utkymd;
#line 380 "AD108_01.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 380 "AD108_01.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 380 "AD108_01.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 380 "AD108_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 380 "AD108_01.sqc"
  sqlastop(0L);
}

#line 380 "AD108_01.sqc"


	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdKENZOK", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE KENZOK END" );

	return ( 0 ) ;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 388 "AD108_01.sqc"

	sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncUpdKENZOK", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "SQLCODE:%ld SQLSTATE:%5.5s UPDATE [KENZOK] CLM[ID2=(%s) ID2POS=(%d) ID3=(%s) ID3POS=(%d) KSNDH=CURRENT_TIMESTAMP] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 sqlca.sqlcode, sqlca.sqlstate, upd_id2, upd_id2pos, upd_id3, upd_id3pos, sel_utkymd, sel_irino, sel_sriymd, sel_kntno ) ;
	return ( sqlca.sqlcode ) ;
}

/******************************************************************************/
/*�@�� �� ���@�FsFncUpdNINSIKI()											  */
/*�@�@�\�T�v�@�F���̔F�����e�[�u���X�V									  */
/*�@���@�@�́@�F															  */
/*�@ ��P���� �F	�a�t�m�o�n�r���R�[�h									  */
/*�@�o�@�@�́@�F															  */
/*�@���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int
sFncUpdNINSIKI( pId3Info )
ID3TB	*pId3Info ;
{

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 410 "AD108_01.sqc"


	/***
	 ***	�ϐ�������
	 ***/
	// �����L�[
	sprintf ( sel_utkymd, "%4.4s-%2.2s-%2.2s", pId3Info->cUtkymd, &pId3Info->cUtkymd[4], &pId3Info->cUtkymd[6] ) ;
	strcpy ( sel_irino,  pId3Info->cIrino ) ;
	sprintf ( sel_sriymd, "%4.4s-%2.2s-%2.2s", pId3Info->cSriymd, &pId3Info->cSriymd[4], &pId3Info->cSriymd[6] ) ;
	strcpy ( sel_kntno,  pId3Info->cKntno ) ;
	// �X�V�l
	strcpy ( upd_id2, pId3Info->cRackId ) ;
	upd_id2pos = atoi ( pId3Info->cRackPos ) ;
	strcpy ( upd_id3, pId3Info->cRackId ) ;
	upd_id3pos = atoi ( pId3Info->cRackPos ) ;

	/***
	 ***	���̔F�����e�[�u���X�V
	 ***		�X�V����
	 ***			�����̃��b�N�h�c
	 ***			�����̃��b�N�|�W�V����
	 ***			�R�h�c���b�N
	 ***			�R�h�c���b�N�|�W�V����
	 ***		��������
	 ***			�a�l�k��t�N����
	 ***			�˗����m��
	 ***			������
	 ***			���̂m��
	 ***/
	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdNINSIKI", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE [NINSIKI] CLM[ID2=(%s) ID2POS=(%d) ID3=(%s) ID3POS=(%d) KSNDH=CURRENT_TIMESTAMP] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 upd_id2, upd_id2pos, upd_id3, upd_id3pos, sel_utkymd, sel_irino, sel_sriymd, sel_kntno );

	
/*
EXEC SQL UPDATE NINSIKI
	SET
		ID2    = :upd_id2,
		ID2POS = :upd_id2pos,
		ID3    = :upd_id3,
		ID3POS = :upd_id3pos,
		KSNDH  = CURRENT TIMESTAMP
	WHERE
		KNTNO  = :sel_kntno AND
		IRINO  = :sel_irino AND
		SRIYMD = :sel_sriymd AND
		UTKYMD = :sel_utkymd ;
*/

{
#line 454 "AD108_01.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 454 "AD108_01.sqc"
  sqlaaloc(2,8,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 454 "AD108_01.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 9;
#line 454 "AD108_01.sqc"
      sql_setdlist[0].sqldata = (void*)upd_id2;
#line 454 "AD108_01.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sql_setdlist[1].sqltype = 500; sql_setdlist[1].sqllen = 2;
#line 454 "AD108_01.sqc"
      sql_setdlist[1].sqldata = (void*)&upd_id2pos;
#line 454 "AD108_01.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 9;
#line 454 "AD108_01.sqc"
      sql_setdlist[2].sqldata = (void*)upd_id3;
#line 454 "AD108_01.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 454 "AD108_01.sqc"
      sql_setdlist[3].sqldata = (void*)&upd_id3pos;
#line 454 "AD108_01.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 14;
#line 454 "AD108_01.sqc"
      sql_setdlist[4].sqldata = (void*)sel_kntno;
#line 454 "AD108_01.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 12;
#line 454 "AD108_01.sqc"
      sql_setdlist[5].sqldata = (void*)sel_irino;
#line 454 "AD108_01.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 11;
#line 454 "AD108_01.sqc"
      sql_setdlist[6].sqldata = (void*)sel_sriymd;
#line 454 "AD108_01.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 11;
#line 454 "AD108_01.sqc"
      sql_setdlist[7].sqldata = (void*)sel_utkymd;
#line 454 "AD108_01.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 454 "AD108_01.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 454 "AD108_01.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 454 "AD108_01.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 454 "AD108_01.sqc"
  sqlastop(0L);
}

#line 454 "AD108_01.sqc"


	sFncPutLog ( TRCKIND_TRACE, __FILE__, "sFncUpdNINSIKI", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "UPDATE NINSIKI END" );

	return ( 0 ) ;

error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 462 "AD108_01.sqc"

	sFncPutLog ( TRCKIND_ERROR, __FILE__, "sFncUpdNINSIKI", __LINE__, EXEFLG_UPD, MYAPP_LOG_ERRCODE_NON,
				 "SQLCODE:%ld SQLSTATE:%5.5s UPDATE [NINSIKI] CLM[ID2=(%s) ID2POS=(%d) ID3=(%s) ID3POS=(%d) KSNDH=CURRENT_TIMESTAMP] WHERE[UTKYMD=(%s) IRINO=(%s) SRIYMD=(%s) KNTNO=(%s)]",
				 sqlca.sqlcode, sqlca.sqlstate, upd_id2, upd_id2pos, upd_id3, upd_id3pos, sel_utkymd, sel_irino, sel_sriymd, sel_kntno ) ;
	return ( sqlca.sqlcode ) ;
}
/** End of File *********************************************************/
