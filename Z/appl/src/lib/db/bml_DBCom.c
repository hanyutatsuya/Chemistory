static char sqla_program_id[292] = 
{
 0,172,69,65,85,65,73,65,82,65,88,72,80,82,74,106,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,0,8,68,66,50,73,78,83,
 84,49,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,8,56,49,90,68,66,67,79,32,0,0,0,0,0,0,0,0,
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


#line 1 "bml_DBCom.sqc"
/**********************************************************************
 *                                                                    
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����Fbml_DBCom.sqc
 *     �T�v      �FDB���ʊ֐��\�[�X�t�@�C��
 **********************************************************************/
#include <stdio.h>
#include <string.h>

#include <sqlca.h>
#include <sqlenv.h>

#include "bml_db.h"
#include "bml_dmm.h"
/*
#include "ifLog.h"	�����͌�񂵁@2005/06/14�@���c
*/
#include "bml_DBCom.h"


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 22 "bml_DBCom.sqc"


/*
EXEC SQL INCLUDE SQLDA;
*/

/* SQL Descriptor Area - Variable descriptor */
#include "sqlda.h"


#line 23 "bml_DBCom.sqc"



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 25 "bml_DBCom.sqc"

	char wd_dbname[16];
	char wd_uname[16];
	char wd_pswd[16];

/*
EXEC SQL END DECLARE SECTION;
*/

#line 29 "bml_DBCom.sqc"


/******************************************************************************
 *�@�@�@�@ZdbConnect()
 * ���@�\�T�v    :�@DB�R�l�N�g����
 * ���h�m�o�t�s�@
 ******************************************************************************
 *    ��P����   :�@char* dbname	   DB��
 *�@�@��Q����   :�@char* uname 	   ���[�U��
 *�@�@��R����   :�@char* pswd		   �p�X���[�h
 * ���n�t�s�o�t�s
 ******************************************************************************
 *    long�i�G���[�R�[�h�j
 ******************************************************************************/
long ZdbConnect ( char* dbname, char* uname, char* pswd )
{

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 46 "bml_DBCom.sqc"


	strcpy( wd_dbname, dbname);
	strcpy( wd_uname,  uname);
	strcpy( wd_pswd,   pswd);

	
/*
EXEC SQL connect to :wd_dbname user :wd_uname using :wd_pswd ;
*/

{
#line 52 "bml_DBCom.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 52 "bml_DBCom.sqc"
  sqlaaloc(2,3,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 52 "bml_DBCom.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 16;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[0].sqldata = (void*)wd_dbname;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 16;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[1].sqldata = (void*)wd_uname;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 16;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[2].sqldata = (void*)wd_pswd;
#line 52 "bml_DBCom.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 52 "bml_DBCom.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 52 "bml_DBCom.sqc"
  sqlacall((unsigned short)29,5,2,0,0L);
#line 52 "bml_DBCom.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 52 "bml_DBCom.sqc"
  sqlastop(0L);
}

#line 52 "bml_DBCom.sqc"


	return 0;

	error:
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 57 "bml_DBCom.sqc"


	ZdbPrintSqlErr( __FILE__, __LINE__, &sqlca );
    return SQLCODE;
}

/******************************************************************************
 *�@�@�@�@ZdbDisConnect()
 * ���@�\�T�v    :�@DB�f�B�X�R�l�N�g����
 * ���h�m�o�t�s�@
 *******************************************************************************
 * ���n�t�s�o�t�s
 ******************************************************************************
 *    BOOL
 ******************************************************************************/
BOOL ZdbDisConnect()
{

	
/*
EXEC SQL connect reset;
*/

{
#line 75 "bml_DBCom.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 75 "bml_DBCom.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 75 "bml_DBCom.sqc"
  sqlastop(0L);
}

#line 75 "bml_DBCom.sqc"
			

	return TRUE;
}


/*******************************************************************************
 *�@�@�@�@ZdbDbCommit()
 * ���@�\�T�v    :�@DB�R�~�b�g����
 * ���h�m�o�t�s�@
 *******************************************************************************
 * ���n�t�s�o�t�s
 *******************************************************************************
 *******************************************************************************/
void ZdbCommit()
{
	
/*
EXEC SQL commit;
*/

{
#line 91 "bml_DBCom.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 91 "bml_DBCom.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 91 "bml_DBCom.sqc"
  sqlastop(0L);
}

#line 91 "bml_DBCom.sqc"

}

/*******************************************************************************
 *�@�@�@�@ZdbbRollback()
 * ���@�\�T�v    :�@���[���o�b�N����
 * ���h�m�o�t�s�@
 *******************************************************************************
 * ���n�t�s�o�t�s
 *******************************************************************************
 *******************************************************************************/
void ZdbRollback()
{
	
/*
EXEC SQL ROLLBACK;
*/

{
#line 104 "bml_DBCom.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 104 "bml_DBCom.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 104 "bml_DBCom.sqc"
  sqlastop(0L);
}

#line 104 "bml_DBCom.sqc"

}

/*******************************************************************************
 * ZdbPrintSqlErr()
 * ���@�\�T�v    :�@�@SQL�G���[�ɂ��Ă̏ڍ׏���\������B
 * ���h�m�o�t�s�@
 *******************************************************************************
 *�@�@��P����   :�@�@�@char* file            �\�[�X�̃t�@�C����
 *�@�@��Q����   :�@�@�@int   line            �\�[�X�̍s�ԍ�
 *�@�@��R����   :�@�@�@struct sqlca* sqlca   SQLCA �\���̂̃A�h���X
 * ���n�t�s�o�t�s
 *******************************************************************************
 *    �Ȃ�
 *�@�@�@
 *******************************************************************************
 *******************************************************************************/
void ZdbPrintSqlErr( char* file, int line, struct sqlca* sqlca )
{
	char	sbuff[1024];
	char	sbuff2[1252];
	int		rc;

//	fprintf(stderr, "SQLCODE %d\n", sqlca->sqlcode);
	if(sqlca->sqlcode == 0){
		return;
	}
	rc = sqlogstt(sbuff, 1024, 80, sqlca->sqlstate);
	sprintf ( sbuff2, "<<%s>>,<<%d>>, SQLCODE:%ld, SQLSTATE:%5.5s",
					file, line, sqlca->sqlcode, sqlca->sqlstate );
	if(rc!=0){
		strcat( sbuff2, ", " );
		strcat( sbuff2, sbuff );
	}
/* ��񂵁@2005/06/14�@���c
	ifErrLog( sbuff2 );
	fprintf(stderr, "%s\n", sbuff2);
*/
}

int bmlTestSub( char *a, int *b )
{
	strcpy(a, "abcdef");
	*b = 12;
	return 1;
}
