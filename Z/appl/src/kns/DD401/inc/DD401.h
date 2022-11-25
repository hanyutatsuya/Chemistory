/**********************************************************************
 *                                                                    
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F��������DB�o�^
 *     �t�@�C�����FDD401.h
 *     �T�v      �F���͋@�����M�����������ʂ�CSV�t�@�C����DB�ɓo�^���� 
 *                                                                    
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006/01/12     S.Tsunekawa    Create
 **********************************************************************/
#ifndef _dd401_h_
#define _dd401_h_

#include <signal.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <syslog.h>
#include <time.h>
#include <stdlib.h>


#include <sql.h>
//#include "bml_DBCom.h"
#include "Kekka.h"
#include "Ctrlkka.h"
#include "Realchk.h"
#include "Kkafltmst.h"
#include "Kkafltmst2.h"
#include "Chk100mst.h"
#include "Kenorder.h"
#include "Rngchkmst.h"
#include "Xbarm.h"
#include "Xbarmmst.h"
#include "Kanjya.h"
#include "Rireki.h"
#include "Tschkmst.h"
#include "Kmkmst.h"
#include "Calckmkmst.h"
#include "Irai.h"
#include "Kjnmst.h"
#include "Skchkmst.h"
#include "Soukan.h"
#include "Kskbrmst.h"
#include "Ctrlmst.h"
#include "Krkmkmst.h"


#include "bmllog.h"
#include "bmlprm.h"

#define 	MYAPP_LOG_ERRCODE_NON 	"00000000"

#define  	SQL_ERR_DUPLICATION 	-803
#define 	SQL_ERR_LOCK			-911

#define 	RET_CONTINUITY			2
#define		RET_STOP				-1


// ���[�J���֐�
int main_proc(void);		// ���C������
void sigcatch(int sig);		// �V�O�i����M
int readline(int fd, char * buff, int size);
//CHG E.Osada 2006-08-15
//int insertDB(char * buff);
int EntryKekka(Kekka *pSrc, int iKcnt);
//
int insertDBCtrl(char * buff);
int insertDBX_M(char * buff);

int TourokuChk(Kekka *pKekka, int *iKesseFlg);
int kjnChk(Kekka *pKekka, Kjnmst *pKjnmst);
int filterChk(Kekka *pKekka, Kjnmst *pKjnmst);
int filterChk2(Kekka *pKekka, Kjnmst *pKjnmst);
int per100Chk(Kekka *pKekka);
int BmlPanicChk(Kekka *pKekka, Kenorder *pKenorder);
int KnsPanicChk(Kekka *pKekka, Kenorder *pKenorder);
int rirekiChk(Kekka *pKekka);
int keisanChk(Kekka *pKekka);
int tousekiChk(Kekka *pKekka);
int bungaChk(Kekka *pKekka, int *iKesseFlg);
int shougoChk(Kekka *pKekka, Kenorder *pKenorder, int *iKesseFlg);
int soukanChk(Kekka *pKekka, Kenorder *pKenorder);
//CHG E.Osada 2006-08-16
//int kanrenChk(Kekka *pKekka);
int kanrenChk(Kekka *pKekka, int iTcnt, int iCrcnt);
int lngChk(Kekka *pKekka, Kenorder *pKenorder);
Krkmkmst *gKrkmkmst;
int		gKrkCnt;
double StringCal_sub(char enzan,double val1,double val2);
double StringCal(char *CalStr);
// ADD 2006/08/03 OSADA
// MOD 2006/08/10 Hiwa
//int getOdrLast(Kekka *pKekka);
int getOdrLast(Kekka *pKekka, Kenorder *p_Order);

//ADD 2006-11-21 �����񁨊��Z�l�ϊ�
int CHG_Mojikjn(char *input,char kbn);

//ADD 2006-11-21 �ُ�l�}�[�N����R�����g�̃`�F�b�N
int CHK_Kkacmt(char *input);

//	���L����������֐�
static	int		sFncShmCrt ( int ) ;
static	int		sFncShmGet ( int , int *) ;
static	int		sFncShmDel ( int ) ;
static	int		sFncRebind ( int ) ;

#define sFncSyslog(p, f, m) _sFncSyslog(p, f, m, "", EXEFLG_NON, __FILE__, __LINE__)
//  �V�X�e�����O�o��
static  void    _sFncSyslog (int piPri, char * pcFncname,char * pcMsg , char * pcErrCode, char * pcExeFlg, char * file, long lineno) ;
//static  void    sFncSyslog (int piPri, char * pcFncname,char * pcMsg , char * pcExeFlg = EXEFLG_NON, char * file = __FILE__, long lineno = __LINE__) ;

void sFncPutLog(LOG_TRCKIND peTrcKind, char *pcSrcName, char *pcFncName, int plLineNo, 
	char *pcExeFlg, char *pcErrCode, char *pcfmt, ... );

//	�p�����[�^������	2006-09-06
#define	MYAPP_PRM_REBIND_SHELL	"REBIND_SHELL"

// DB�A�N�Z�X�̒ǉ��֐�
long ZdbKkafltmstSelectGRPKMKKey( Kkafltmst* pKey, Kkafltmst** arrayOut, int* numOut );
long ZdbChk100mstSelectGrp( Chk100mst* pKey, Chk100mst** arrayOut, int* numOut );
extern long ZdbKkafltmstSelectGRPKMKKey2( Kkafltmst2* pKey, Kkafltmst2** arrayOut, int* numOut );
int GetKrkmkmst();

//ADD E.Osada 2006-08-15
int getKekkaData(char *buff, Kekka *pSrcKka);
#endif

long ZdbRngchkmstSelectHnikbn( char * aKnskisymd, Rngchkmst* pKey, Rngchkmst** arrayOut, int* numOut );
