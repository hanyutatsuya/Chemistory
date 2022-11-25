/********************************************************************/
/*																	*/
/*		�a�l�k�l���������V�X�e��									*/
/*																	*/
/*		�V�X�e����	�F������V�X�e��								*/
/*		�t�@�C����	�FFB103Jidokousei.h								*/
/*		�T�v		�F�����Z������									*/
/*																	*/
/********************************************************************/

/********************************************************************/
/*  Ver.	�쐬��			���O			�C�����e				*/
/* ----------------------------------------------------------------	*/
/*  1.00	2006/02/27		E.Osada			Create					*/
/********************************************************************/

#ifndef _FB103Jidokousei_h_
#define _FB103Jidokousei_h_

/********************************************************************/
/*	�C���N���[�h�錾												*/
/********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmllog.h"
#include "bmlprm.h"
#include "bml_date.h"
#include "bml_DBCom.h"
#include "bml_misc.h"
#include "F103ctrlkka.h"
#include "F103ctrlknr.h"
#include "F103kekka.h"

/******************************************************************************/
/* �萔��`	                                                                  */
/******************************************************************************/

//�v���O������
#define APP_NAME	"FB103"

//���O�t�@�C��INI�t�@�C��
#ifdef WIN32
#define LOGINIFILE ".\\FB103_LOG.log"
#else
#define LOGINIFILE "./FB103_LOG.ini"
#endif

//�G���[�R�[�h

//  ���O�G���[�R�[�h��`
#define MYAPP_LOG_ERRCODE_NON       "00000000"
#define MYAPP_LOG_ERRCODE_APP       "010"
#define MYAPP_LOG_ERRCODE_DB        "020"
#define MYAPP_LOG_ERRCODE_ETC       "0Z0"

//	�v���O�����G���[�R�[�h��`
#define ERROR_CODE_NORMAL			 0
#define	ERROR_CODE_CMD_PRM_ERROR	-1
#define	ERROR_CODE_PRM_OPEN_ERROR	-2
#define ERROR_CODE_LOG_OPEN_ERROR	-3
#define ERROR_CODE_PRM_GET_ERROR	-4
#define ERROR_CODE_DB_CONNECT_ERROR	-5
#define ERROR_DB_ERROR				-6
#define ERROR_FUNC_ERROR			-7

//�p�����[�^�L�[
#define PRM_DB_NAME					"DB_NAME"
#define PRM_DB_USER_ID				"DB_USER_ID"
#define	PRM_DB_PASSWORD				"DB_PASSWORD"

#ifdef WIN32
#define snprintf _snprintf
#endif

//�g���[�X
#ifdef _TEST
#define mcrPutTrace(p, tt, fn, ef, ec, msg)		{	(p)->stLogMem.eTrcKind = (tt);														\
													printf("%c %s %s %s %s\n", (tt), (fn), (ef), (ec), (msg));	\
												}
#else
#define mcrPutTrace(p, tt, fn, ef, ec, msg)		{	(p)->stLogMem.eTrcKind = (tt) ;				\
													strcpy((p)->stLogMem.pcFncName, (fn)) ;		\
													strcpy((p)->stLogMem.pcExeFlg,  (ef)) ;		\
													strcpy((p)->stLogMem.pcErrCode, (ec)) ;		\
													strcpy((p)->stLogMem.pcMsg, (msg)) ;		\
													ZbmlPutLog(&(p)->stLogMem) ;				\
												}
#endif


/******************************************************************************/
/* �\���̒�`                                                                 */
/******************************************************************************/

/* �v���O�����Ǘ��\���� */
typedef struct
{
	BMLPRM*		bp;				
	struct		stcLogMember      stLogMem;
	char		cDbName[128];
	char		cDbUserId[128];
	char		cDbPassword[128];
	char		cUpdateId[128];						//�X�V��ID
	char		cUpdateName[128];					//�X�V��
	char		cLogName[128];						//���O
} ENV, *PENV;


#endif
/** End of File ***************************************************************/
