/**********************************************************************
 *
 *	   �a�l�k�l���������V�X�e��
 *
 *	   �V�X�e�����F��������DB�o�^
 *	   �t�@�C�����FMD105.c
 *	   �T�v 	 �F���͋@�����M�����������ʂ�CSV�t�@�C����DB�ɓo�^����
 *
 **********************************************************************/

/**********************************************************************
 *	Ver.	 Date			Name		   History
 * --------------------------------------------------------------------
 **********************************************************************/

#include "MD105.h"

#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <ctype.h>

/* �O���[�o���ϐ� */
char	dbname[16];
char	dbuser[16];
char	dbpass[16];

char	GetFolder[256];
char	GetFolderErr[256];
char	GetFolderEnd[256];

char	iniName[256];

int 	SleepTime;

int 	EndFlg = 0;

int 	shm_Key = 0;
int 	shm_Id;

Kmkmst		sKmkmst;
Kmkmst		*pKmkmst;
int 		cntKmkmst;

char		gLogFile[256];
char		gMsgBuff[128];
void LogFileOut(char * msg);

static int chkRawdata( char *, char * );

/* ��ߔ{���ϊ�(�}�X�^�Ɛ���������邱��) */
char		KskbrB10HY[16+1] ;
char		KskbrB10CD[16+1] ;
char		KskbrB2HY[16+1] ;
char		KskbrB2CD[16+1] ;

/* ���сE�n���`�F�b�N >> */
char		NyubiCD[8];
char		NyubiCM[6];
char		NyubiCHK[21];
char		NyubiKekka[21];
char		NyubiSTS[3];
char		YoketsuCD[8];
char		YoketsuCM[6];
char		YoketsuCHK[21];
char		YoketsuKekka[21];
char		YoketsuSTS[3];
char		OudanCD[8];
char		OudanCM[6];
char		OudanCHK[21];
char		OudanKekka[21];
char		OudanSTS[3];
int 		gfNyuYou;		/* ���сE�n���t���O */
static int	NyubiYoketuChk(Kekka *, int, int, int);
static int	NyubiYoketu( Kekka *, int );

int chkDenkai( Kekka *p );
int kesseiCHK(Kekka *pSrc, int iKcnt);

int sFncSel_REALCHK( char *,char *, char * , char * , short);
long ZdbSelectMihoKekka( char *,char *, char *, char *, char * );

long updKkaYsn( Kekka* pKey );
/* RIBIND�V�F���p�X */
char		gcMyRebindShell[256];

/* �萫�l��l����ׂ̈̊��Z�e�[�u�� */
char		KZN_Teisei[25][5];
char		KZN_Coment[25][5];
char		IJOU_KKACMT[100][5];

/* �v�Z���g���Ή�
 * ���֎����̌v�Z���ɂ̂ݓK�p�A�v�Z���ڂ̌v�Z�́A MD105 �ł͍s��Ȃ��B
 */

#ifndef MAXBUF
#define MAXBUF                   (260)
#endif									/* !define MAXBUF					*/

/* �����I�[�_�[�Ɋ܂܂�鑮���Ɋւ��鍀�ڂ̃o�C�g �T�C�Y                    */
#define FLDSIZE_SC         ((size_t)5)  /* �g�� (cm)                        */
#define FLDSIZE_TJ         ((size_t)5)  /* �̏d                             */
#define FLDSIZE_TJTNI      ((size_t)1)  /* �̏d�敪                         */
#define FLDSIZE_TNTME      ((size_t)4)  /* �~�A����                         */
#define FLDSIZE_TNTNI      ((size_t)1)  /* �~�A���ԋ敪                     */
#define FLDSIZE_TNRYO      ((size_t)5)  /* �~�A��                           */
#define FLDSIZE_TNRYOTNI   ((size_t)1)  /* �~�A�ʋ敪                       */

#define FLDSIZE_SBTKBN     ((size_t)1)  /* ���ʋ敪                         */
#define FLDSIZE_AGE        ((size_t)3)  /* �N��                             */
#define FLDSIZE_AGEKBN     ((size_t)1)  /* �N��敪                         */

/* �P�ʓ����������ڂɊi�[����鎯�ʎq                                       */
#define _VALUE_TNTNI_HOUR       ('0')   /* �~�A����: ���ԒP��               */
#define _VALUE_TNTNI_MINUTE     ('1')   /* �~�A����: ���P��                 */
#define _VALUE_TNTNI_UNKNOWN    ('9')   /* �~�A����: ���ԒP�ʕs��           */
#define _VALUE_TNRYO_LITER      ('0')   /* �~�A��: ���b�g���P��             */
#define _VALUE_TNRYO_MILLILITER ('1')   /* �~�A��: �~�� ���b�g���P��        */
#define _VALUE_TNRYO_UNKNOWN    ('9')   /* �~�A��: �ʒP�ʕs��               */
#define _VALUE_TJTNI_GRAM       ('1')   /* �̏d: �O�����P��                 */
#define _VALUE_TJTNI_KILLOGRAM  ('0')   /* �̏d: �L���O�����P��             */
#define _VALUE_SBTKBN_MALE      ('0')   /* ����: �j��                       */
#define _VALUE_SBTKBN_FEMALE    ('1')   /* ����: ����                       */
#define _VALUE_SBTKBN_UNKNOWN   ('9')   /* ����: ���ʕs��                   */
#define _VALUE_AGEKBN_YEAR      ('Y')   /* �N��: �N��                       */

/* �v�Z���Ɋ܂܂�鑮�����̒l�ɒu������w��                               */
#define KSNSK_TNTME     ('N')           /* �~�A���� (���ԒP��)              */
#define KSNSK_TNRYO     ('R')           /* �~�A�� (�~�� ���b�g���P��)       */
#define KSNSK_SC        ('T')           /* �g��                             */
#define KSNSK_TJ        ('W')           /* �̏d (�O�����P��)                */
#define KSNSK_SBTKBN    ('S')           /* ���ʋ敪                         */
#define KSNSK_AGE       ('A')           /* �N��                             */

char gszTransfer[MAXBUF + 1];			/* �����񁨐��l �ϊ��o�b�t�@
										   �P��̒l�̒u���݂̂Ȃ̂ŁA�R����
										   �����                           */

/* �v�Z������ IF �u���b�N�W�J                                               */
extern char *OperateKSNSK(const char *);

/* ���l�����񔻒�                                                           */
extern int _isnumeric(const char *);

/*----<< End add source Feb 27, 2008 H.Sato >>----*/

/* �ƍ��`�F�b�N�ɂčČ��l�ɂ��Ă����ꍇ�A�p��Č��ւƗ��Ƃ����͋@�G���[�R�[�h */
int		errsts_sai_cnt = 33;
char	errsts_sai[33][3] = {
			"1", "2", "4", "5", "6", "7", "8", "9", "10", "11", 
			"18", "19", "23", "24", "25", "26", "27",  
			"37", "38", "39", "40", "41", "42", "43", "44", "45", "46", 
			"56", "57", "58", "59", "60", "73"
		};

int		errsts_ng_cnt = 3;
char	errsts_ng[3][3] = {
			"3","47","72"
		};
/* �����W�`�F�b�N�}�X�^ �͈͋敪��` */
#define BML_PANIC	('2') 
#define KNS_PANIC	('3')
#define SYOGO_CHK	('4')

/******************************************************************************/
/*	�� �� ��  �Fmain()							*/
/*	�@�\�T�v  �F�v���Z�X���C������						*/
/*	��	  ��  �F							*/
/*	 ��P���� �Fargc	�p�����^��					*/
/*	 ��Q���� �Fargv	�p�����^�z��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int main(int argc, char **argv)
{
	long db_ret;
	BMLPRM * bp;
	char	wk[16];
	int 	daemonFlg = 0;
	int 	lcnt;
	int 	cnt;
	char	wk_key[30];
	strncpy(iniName, "MD105.ini", 32);
	/* �p�����[�^�`�F�b�N */
	if (argc > 1) {
		for (lcnt = 1; lcnt < argc; lcnt++) {
			if (argv[lcnt][0] == '-') {
				switch (argv[lcnt][1]) {
				case 'S': case 's':
					daemonFlg = 0;
					break;
				case 'N': case 'n':
					daemonFlg = 1;
					break;
				}
			}
			else {
				strncpy(iniName, argv[lcnt], 256);
			}
		}
	}
	else {
		printf("%s iniFileName [-n]\n", argv[0]);
		printf("Option -n : Non Daemon Exec\n");
		exit(0);
	}

	if (daemonFlg == 0) {
		/***
		 ***	�o�b�N�O���E���h���s
		 ***/
		if ( daemon ( 0, 1 ) < 0 ) {
			exit ( 9 ) ;
		}
	}

	/* ������ */
	if (ZbmlOpenLog( iniName )	!= 0 ) {
		printf("ZbmlOpenLog Error\n");
	}

	sFncSyslog(TRCKIND_TRACE, "main", "Process Start");
	bp = ZbmlPrmOpen(iniName);
	ZbmlPrmGetVal(bp, "DBNAME", dbname);
	ZbmlPrmGetVal(bp, "USER", dbuser);
	ZbmlPrmGetVal(bp, "PASS", dbpass);

	ZbmlPrmGetVal(bp, "GetFolder", GetFolder);
	ZbmlPrmGetVal(bp, "GetFolderErr", GetFolderErr);
	ZbmlPrmGetVal(bp, "GetFolderEnd", GetFolderEnd);

	ZbmlPrmGetVal(bp, "SleepTime", wk);
	SleepTime = atoi(wk);

	if ( ZbmlPrmGetVal ( bp, "SHM_KEY", wk ) != 0 ) {
		/* �ُ�I��	LOG */
		return ( -1 ) ;
	}
	shm_Key = atoi ( wk ) ;

	ZbmlPrmGetVal(bp, "LogFileName", gLogFile);
	/* ��ߔ{���ϊ�(�}�X�^�Ɛ���������邱��) */
	ZbmlPrmGetVal(bp, "KSKBR_B10_HYOJI", KskbrB10HY);
	ZbmlPrmGetVal(bp, "KSKBR_B10_CODE", KskbrB10CD);
	ZbmlPrmGetVal(bp, "KSKBR_B2_HYOJI", KskbrB2HY);
	ZbmlPrmGetVal(bp, "KSKBR_B2_CODE", KskbrB2CD);

	/* ���сE�n���̍��ڃR�[�h�y�ѐݒ�R�����gCD�̎擾 */
	ZbmlPrmGetVal(bp, "NyubiCD", NyubiCD);
	ZbmlPrmGetVal(bp, "NyubiCM", NyubiCM);
	ZbmlPrmGetVal(bp, "NyubiCHK", NyubiCHK);
	ZbmlPrmGetVal(bp, "YoketsuCD", YoketsuCD);
	ZbmlPrmGetVal(bp, "YoketsuCM", YoketsuCM);
	ZbmlPrmGetVal(bp, "YoketsuCHK", YoketsuCHK);
	ZbmlPrmGetVal(bp, "OudanCD", OudanCD);
	ZbmlPrmGetVal(bp, "OudanCM", OudanCM);
	ZbmlPrmGetVal(bp, "OudanCHK", OudanCHK);

	/* �萫�l��l����ׂ̈̊��Z�e�[�u�� >> */
	for (cnt = 1; cnt < 25 ; cnt++) {
		sprintf(wk_key,"KANZAN_TEISEI_%02d",cnt);
		/* ini�t�@�C�����犷�Z����������擾 */
		ZbmlPrmGetVal(bp, wk_key, KZN_Teisei[cnt]);
		if(memcmp(KZN_Teisei[cnt],"END",3) == 0){
			/* END�Ȃ甲���� */
			break;
		}
		/* ini�t�@�C�����犷�Z���R�����g�R�[�h���擾 */
		sprintf(wk_key,"KANZAN_COMENT_%02d",cnt);
		ZbmlPrmGetVal(bp, wk_key, KZN_Coment[cnt]);
		if(memcmp(KZN_Coment[cnt],"END",3) == 0){
			/* END�Ȃ甲���� */
			break;
		}
    }

	/* �ُ�l�}�[�N����R�����g >> */
	for (cnt = 1; cnt < 100; cnt++) {
		sprintf(wk_key,"IJOU_KKACMT_%02d",cnt);
		/* ini�t�@�C�����犷�Z����������擾 */
		ZbmlPrmGetVal(bp, wk_key, IJOU_KKACMT[cnt]);
		if(memcmp(IJOU_KKACMT[cnt],"END",3) == 0){
			/* END�Ȃ甲���� */
			break;
		}
	}
	ZbmlPrmClose(bp);

	if ( sFncShmCrt ( shm_Key ) < 0 ) {
		return ( -1 ) ;
	}

	/* man 7 signal �Ŋm�F */
	if(SIG_ERR == signal(SIGINT,sigcatch)){
		exit(1);
	}

	/* DB�̐ڑ� */
	db_ret = ZdbConnect(dbname, dbuser, dbpass);
	if (db_ret != 0L) {
		sprintf(gMsgBuff,"DB Connect OK [%s]\n", dbname);
		sFncSyslog(TRCKIND_TRACE, "main", gMsgBuff);
	}
	/* �}�X�^�ǂݍ��� */
	if(GetKrkmkmst() != 0){
		/* 2006-12-18 YOON */
		/* Nagata �֘A���ڃ}�X�^�擾���s!! �g���[�X���c���ďI������ */
		sFncSyslog(TRCKIND_TRACE, "GetKrkmkmst Can't get and Process End", gMsgBuff);
		ZdbDisConnect();
		ZbmlCloseLog();
		return 0;
	}

	/* ���C������ */
	main_proc();

	/* DB�̐ؒf */
	ZdbDisConnect();

	sFncSyslog(TRCKIND_TRACE, "main", "Process End");
	ZbmlCloseLog() ;
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �Fmain_proc() 						*/
/*	�@�\�T�v  �F���C��������						*/
/*	��	  ��  �F							*/
/*	 ��P���� �F								*/
/*	 ��Q���� �F								*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
char	gFileMsgBuff[256];
int main_proc()
{
	struct dirent	**entp; 
	FILE *		fd;
	char		*fname;
	char		*fname2;
	char		*buff;
	int 		err_flg;
	int 		li_stopFlg ;
	int 		flgCtrl;
	int 		ret;
	struct stat 	fst;
	int 		iKkaCnt;
	Kekka		strKekka[100];
	int 		num_file, n;
	int		fname_len;

	fname = (char *)malloc(sizeof(char)*256);
	fname2 = (char *)malloc(sizeof(char)*256);
	buff = (char *)malloc(sizeof(char)*1024);

	/* �I���V�O�i�����󂯂�܂Ń��[�v */
	for (;;) {
		/*** ��~�R�}���h�m�F ***/
		if ( sFncShmGet ( shm_Key, &li_stopFlg ) < 0 ) {
			return ( -1 ) ;
		}
		if ( li_stopFlg == 1 ) {
			sFncShmDel ( shm_Key ) ;
			break ;
		}
		/* �I���V�O�i�����`�F�b�N */
		if ( EndFlg ) {
			break;
		}
		/* ��M�t�@�C�������邩�m�F */
		num_file = scandir( GetFolder, &entp, 0 , alphasort );
		for( n = 0; n < num_file; n++ ) {
			/* .dat �t�@�C���ȊO�͏��O���� */
			fname_len = strlen( entp[n]->d_name );
			if ( memcmp ( &(entp[n]->d_name[fname_len-strlen(MYAPP_RECV_SFX)]),
					MYAPP_RECV_SFX,
					strlen ( MYAPP_RECV_SFX ) ) != 0 ) {
				free( entp[n] );
				continue;
			}
			/***
			 *** ��~�R�}���h�m�F
			 ***/
			if ( sFncShmGet ( shm_Key, &li_stopFlg ) < 0 ) {
				return ( -1 ) ;
			}
			if ( li_stopFlg == 1 ) {
				sFncShmDel ( shm_Key ) ;
				break ;
			}

			/* �I���V�O�i�����`�F�b�N */
			if ( EndFlg ) {
				break;
			}
			/* �t�@�C�����̃t���p�X�𐶐�����B */
			strncpy(fname, GetFolder, 256);
			strncat(fname, entp[n]->d_name, 256);

			if (stat(fname, &fst) != 0) {
				/* �t�@�C���ُ�H */
				continue;
			}

			if (!S_ISREG(fst.st_mode)) {
				/* �ʏ�̃t�@�C���łȂ� */
				continue;
			}

			strncpy(fname2, GetFolderEnd, 256);
			strncat(fname2, entp[n]->d_name, 256);

			/* End�t�H���_�̃t�@�C���m�F */
			ret = stat(fname2, &fst);
			if (ret == 0) {
				/* ���Ƀt�@�C�������݂���B�����t�@�C���������� */
				int cnt = 1;
				char buf[4];
				while (ret == 0) {
					sprintf(buf, ".%d", cnt);
					strncpy(fname2, GetFolderEnd, 256);
					strncat(fname2, entp[n]->d_name, 256);
					strncat(fname2, buf, 256);
					ret = stat(fname2, &fst);
					cnt ++;
				}
			}

			/* �t�@�C���� End �t�H���_�ֈړ� */
			if (rename(fname, fname2) != 0) {
				continue;
			}

			/* �t�@�C�������o�� */
			LogFileOut(entp[n]->d_name);

			/* �t�@�C�����̓�3������CT_�̎��̓R���g���[����� */
			/*/						XM_�̎���X_M��� */
			if (strncmp(entp[n]->d_name, "CT_",3) == 0) {
				flgCtrl = 1;
			}
			else if (strncmp(entp[n]->d_name, "XM_",3) == 0) {
				flgCtrl = 2;
			}
			else {
				flgCtrl = 0;
			}

			fd = fopen(fname2, "r");
			if ( fd == NULL ) {
				/* error */
				continue;
			}

			err_flg = 0;
			for( iKkaCnt=0; iKkaCnt < 100 ;++iKkaCnt ) {
				memset(&strKekka[iKkaCnt], 0, sizeof(Kekka));
			}
			iKkaCnt = 0;
			while (fgets(buff, 1024, fd) != NULL) {
				/* �ǂݏo�����t�@�C����DB�֓o�^ */
				if (flgCtrl == 0) {
					/* ���ʓo�^�����̓t�@�C���Ǎ��݌�ɍs���悤�ɂ��� */
					if( getKekkaData(buff, &strKekka[iKkaCnt]) != 0 ) {
						err_flg = 1;
						break;
					} else {
						++iKkaCnt;
					}
				}
				else if (flgCtrl == 1) {
					if( (ret = insertDBCtrl(buff)) != 0)
					{
						/* �R���g���[�����ʂ̃C���T�[�g���s */
						if( ret == RET_STOP ) {
							ZdbRollback();
							err_flg = 1;
							break;
						}
						else if(ret == RET_CONTINUITY){
							ZdbRollback();
						}
					}
				}
				else {
					if ((ret=insertDBX_M(buff)) != 0) {
						/* X_M���ʂ̃C���T�[�g���s */
						if( ret == RET_STOP ) {
							ZdbRollback();
							err_flg = 1;
							break;
						}
						else if(ret == RET_CONTINUITY){
							ZdbRollback();
						}
					}
				}
			}
			fclose(fd);
			/* ���ʓo�^�������Ō�ɍs�� */
			if( (flgCtrl == 0) && (err_flg == 0) ) {
				ret = EntryKekka( strKekka, iKkaCnt);
				/* �������ʂ̃C���T�[�g */
				if( ret == RET_STOP ) {
					ZdbRollback();
					err_flg = 1;
				}
				else if(ret == RET_CONTINUITY){
					ZdbRollback();
				}
			}
			/* �������Ή������ǉ� */
			if( (flgCtrl == 0) && (err_flg == 0) ) {
				if( (kesseiCHK( strKekka, iKkaCnt )) != 0 ) {
					/* �������X�V */
					if( ret == RET_STOP ) {
						ZdbRollback();
						err_flg = 1;
					}
					else if(ret == RET_CONTINUITY){
						ZdbRollback();
					}
				}
			}

			if (err_flg == 1) {
				/* �G���[���� */
				char errmsg[128];
				sprintf(errmsg, "%s %s", fname2, "[[DB ERROR]] File Data DB Rollback.");
				sFncSyslog ( LOG_ERR, "main_proc()", errmsg ) ;

				return 0;	/* �I��*/
			} else {
				ZdbCommit();
			}

			free( entp[n] );
		}
		free( entp );
		/* ��莞�ԑҋ@ */
		sleep(SleepTime);
	}

	free(fname);
	free(fname2);
	free(buff);

	return 0;
}
/******************************************************************************/
/*	�� �� ��  �F()								*/
/*	�@�\�T�v  �F���C��������						*/
/*	��	  ��  �F							*/
/*	 ��P���� �F								*/
/*	 ��Q���� �F								*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint								*/
/*			 0			����			 	*/
/*			RET_STOP(-1)		�ُ�				*/
/*			RET_CONTINUITY(2) �ُ�B���̏�������B			*/
/******************************************************************************/
int EntryKekka(Kekka *pSrc, int iKcnt)
{
	int 		i;
	Kekka		* pKekka;
	Kenorder	wOrder;
	int 		ret;
	int 		ret1;
	int 		iKesseiflg;
	short		rKnssu;
	long		num_irai;
	char		errMsg[1024] = {0,};
	int			iFukusuflg = 0; 
	/* iKesseiflg ... �������I�[�_�L�� */
	/*	  �������˗��Ȃ�	... 0 */
	/*	  �������˗��L��	... 1 */
	iKesseiflg = 0;
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			/* �������̉e��������([����No�{�����O���[�v]�̏����� */
			/* ���A���`�F�b�N���������A�����p�����[�^��"00"�ȊO�̕��� */
			/* �ꌏ�ł�����΁A������񂠂�Ƃ���B */
			/* 2006-09-01 Nagata �����J�n���ǉ� */
			/* 2007-05-22 Nagata �����ǉ��i�A�b�Z�C���b�NID,�A�b�Z�C���b�NPOS�j*/
			/* �����J�n��+����No+�����O���[�v+�A�b�Z�C���b�NID+�A�b�Z�C���b�NPOS�̏����� */
			/* ���A���`�F�b�N���������A�����p�����[�^��"00"�ȊO�̕��� */
			/* �ꌏ�ł�����΁A������񂠂�Ƃ���B */
			ret = sFncSel_REALCHK( pKekka->knskisymd, pKekka->kntno, pKekka->knsgrp,
									pKekka->asyrckid,pKekka->asyrckpos );

			if(ret<0)
			{
				sprintf(errMsg,"SQLCODE:%d Input knskirymd(%s) kntno(%s) knsgrp(%s)"
					,ret,pKekka->knskisymd, pKekka->kntno, pKekka->knsgrp);

				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK)
				{
					sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog (TRCKIND_ERROR, "EntryKekka()", errMsg);
				return(RET_STOP);
			}
			else if( ret > 0 ) {
				iKesseiflg = 1;
			}
		}
	}
	/* �e�폈���`�F�b�N���[�v */
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			/* �����t���O���ۗ����ݒ肳��Ă��鎞�ȊO */

			if (pKekka->irikbn != 'Y') {	/* �L�����u���[�V�����ȊO�̂Ƃ� */
				if (pKekka->knssu == 1) {
					/* ���񌟍����́A���ʗD��t���O��D��ɐݒ� */
					pKekka->kkaysnflg = '1';
					pKekka->siyflg = '1';
				}
				/* ����͌������ʂ����邩�`�F�b�N	*/
				/* ����̓t���O  ���P�i����͌��ʁj	*/
				/* ���ʗD��t���O���P�i�D�挋�ʁj	*/
				Kekka	ssKekka;
				memcpy(&ssKekka, pKekka, sizeof(ssKekka));
				ssKekka.knssu = 0;
				ssKekka.knssueda = 0;
				ret = ZdbKekkaSelectTnyrkCount(&ssKekka);
				if (ret < 0){
					sprintf(errMsg,"SQLCODE:%d ZdbKekkaSelectTnyrkCount",ret);
					/* 2006-12-13	YOON */
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog (TRCKIND_ERROR, "EntryKekka()", errMsg);
					return(RET_STOP);
				}
				else if(ret ==0)
					;
				else if(ret > 0){
					/* ����͂̌��ʂ����݂���Ƃ��́A���ʂ𖢕񍐊����ɐݒ� */
					pKekka->siyflg	  = '0';
					pKekka->kkajkcd   = '1';
					pKekka->kkaysnflg = ' ';
					pKekka->knsflg	  = 'M';
				}

				/* 2.03 ����˗��ł��ʌ��̂̌��ʂ����݂��Ă���ꍇ�͖��񍐊����ɐݒ肷��B */
				ret = ZdbKekkaSelectFukusuCount(pKekka);
				if (ret < 0){
					sprintf(errMsg,"SQLCODE:%d ZdbKekkaSelectFukusuCount",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog (TRCKIND_ERROR, "EntryKekka()", errMsg);
					return(RET_STOP);
				}
				else if(ret ==0){
					;
				}
				else if(ret > 0){
					sprintf(errMsg,"�ʌ��̂ő���ς� sriymd(%s) kntno(%s) knsgrp(%s)"
							,pKekka->sriymd, pKekka->kntno, pKekka->knsgrp);
					sFncSyslog (TRCKIND_ERROR, "EntryKekka", errMsg);

					pKekka->siyflg    = '0';
					pKekka->kkajkcd   = '1';
					pKekka->kkaysnflg = ' ';
					pKekka->knsflg    = 'M';
					iFukusuflg        =  1 ;
				}

				if (pKekka->knsflg != 'M') {
					/* ���ڃ}�X�^�[�ǂݏo�� */
					memset(&sKmkmst, 0, sizeof(Kmkmst));
					strncpy(sKmkmst.knsgrp, pKekka->knsgrp, 16);
					strncpy(sKmkmst.kmkcd, pKekka->kmkcd, 7);
					ret = ZdbKmkmstSelectKey(&sKmkmst, &pKmkmst, &cntKmkmst);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND))
					{
						sprintf(errMsg,"SQLCODE:%d ZdbKmkmstSelectKey",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog(LOG_ERR,"EntryKekka()",errMsg);
						return(RET_STOP);

					}
					else if (ret == HRC_SQL_NOT_FOUND) {
						cntKmkmst = 0;
					}
					/* �o�^�`�F�b�N */
					if( (ret = TourokuChk(pKekka, &iKesseiflg)) != 0 ) {
						/* �o�^�`�F�b�N�G���[ */
						sFncSyslog ( LOG_ERR, "EntryKekka()", "Touroku Check Error.");
						return(ret);
					}
					ZbmlFree(pKmkmst);
				}
			}
		}
	}

	/* �ƍ��E�֘A�`�F�b�N���[�v */
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			if( pKekka->syougoflg == '2' ) {
				kanrenChk(pSrc, iKcnt, i);
			}
			if( pKekka->syougoflg == '1' ) {
				kanrenChkYsn(pKekka);
			}
		}
	}

	/* ���ʃf�[�^INSERT�������[�v */
	for( i=0; i < iKcnt ; ++i ) {
		pKekka = pSrc + i;
		if (pKekka->knsflg != 'H') {
			/*	�����I�[�_�Ɏ��j�d�x�̃I�[�_�����邩���`�F�b�N���� */
			/*	���݂��� */
			/*		�������H���敪 "K" �F �p��Č� */
			/*	���݂��Ȃ� */
			/*		�������H���敪 "K" �F �����Č� */
			memset(&wOrder, 0, sizeof(wOrder));
			if( (ret1 = getOdrLast( pKekka, &wOrder )) < -1 ) {
				/* �c�a�G���[(���O) */
				return -1;
			}
			if( iKesseiflg ) {
				if( pKekka->knssu == 1 || pKekka->ksktkbn == 'S' ){
					/* 2.���їn���t���O��'2'�Ō����t���O'X'�������猟���t���O��'H'�ɕύX���� */
					if( pKekka->knsflg == 'X' ) {
						pKekka->kesseiflg = '2';
						pKekka->knsflg = 'H';
					}
					/* ���уt���O�͌����t���O"X","A","R"�ɑ΂��Ă��X�V���� */
					else if( pKekka->knsflg == 'A' || pKekka->knsflg == 'R' ) {
						pKekka->kesseiflg = '2';
					}
				}
			}
			/* DB�ɃC���T�[�g */
			do {
				ret = ZdbKekkaInsert(pKekka);
				if ((ret != HRC_SQL_NORMAL) && (ret != SQL_ERR_DUPLICATION)) {
					/* �C���T�[�g�G���[ */
					sprintf(errMsg, "Kekka Insert Errer(%d) : KNTNO[%s]:KNSGRP[%s]:KMKCD[%s]:KNSSU[%d]",
						ret, pKekka->kntno, pKekka->knsgrp, pKekka->kmkcd, pKekka->knssu);

					if(ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
					return(RET_STOP);
				}
				if (ret == SQL_ERR_DUPLICATION) {
					if( ((ret1 == 0) && (pKekka->ksktkbn == 'K')) || iFukusuflg == 1) {
						/* �����Č� �������Ȃ� */
						/* �ʌ���NO�̗D�挋�ʂ����݂��Ă���ꍇ�͉������Ȃ� */
					} else {
						/* �đ���w���L�聕WS�o�͂Ȃ� */
						/* ���݂��錋�ʂ��������āA���ׂĂ����񍐊���"M"�ł��A���ԕ񍐂̏�Ԃ�������A */
						/* �ė����̏������s��Ȃ��B������������ */
						num_irai = ZdbSelectMihoKekka(pKekka->knskisymd,pKekka->sriymd,
							pKekka->kntno, pKekka->knsgrp, pKekka->kmkcd );

						if(num_irai < 0)
						{
							/* ���񍐊������R�[�h�̌��� */
							sprintf(errMsg, "SQL CODE:%ld ZdbSelectMihoKekka",num_irai);
							if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
								sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
								return(RET_CONTINUITY);
							}
							sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
							return(RET_STOP);

						}
						else if( num_irai == 0 ) {
							/* �ė����O�̌����񐔂����ׂĒ��� */
							/* �t���O�ނ��ă`�F�b�N����2�ȏオ���݂��Ȃ��ꍇ */
							/* �i���`���l���Ɋւ��Ăُ͈킪�Ȃ��j�A�����t���O��'X'�ɕύX���� */
							/* �� �đ���w����̍ė����Ő���f�[�^���Č��ΏۂɂȂ����ׂ̑Ή� */
							if (pKekka->renjicflg < '2' && pKekka->soukn1flg < '2' &&
									pKekka->kesseiflg < '2' && pKekka->rirekiflg < '2' &&
									pKekka->syougoflg < '2' && pKekka->keisanflg < '2' &&
									pKekka->per100flg < '2' && pKekka->tousekflg < '2' &&
									pKekka->kisyakflg < '2' && pKekka->kouseiflg < '2' &&
									pKekka->syoungflg < '2' && pKekka->soukn2flg < '2' &&
									pKekka->fukaptflg < '2' && pKekka->yobiflg01 < '2' &&
									pKekka->tobiflg02 < '2' && pKekka->yobiflg03 < '2' &&
									pKekka->yobiflg04 < '2' && pKekka->yobiflg05 < '2') {
								pKekka->knsflg = 'X';
							}

						}
						else if(num_irai > 0)
						{
						/*	�d���G���[�����������ꍇ */
						/*	�y�X�V�d�l�z */
						/*		���ʏ󋵃R�[�h���P�i���ԁj */
						/*		���ʗD��t���O���u�����N */
						/*		�����t���O���l�i���񍐊����j */
						/*	���f�[�^�𖳌��ɂ��� */
						pKekka->kkajkcd    = '1' ;
						if( pKekka->kesseiflg == '2' )
							pKekka->kesseiflg = '1';
						pKekka->knsflg	   = 'M' ;
						pKekka->kkaysnflg  = ' ' ;
						}
					}
					/* �d���G���[�����������Ƃ��́A�����񐔂��C���N�������g����B */
					pKekka->knssu ++;
				}
			} while (ret == -803);
		}
	}

	/* �˗��������[�v */
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		/* �ʌ���NO�̗D�挋�ʂ����݂��Ă���ꍇ�� �˗����X�V���Ȃ� */
		if (pKekka->knsflg != 'H' && iFukusuflg != 1) {
			if (pKekka->irikbn != 'Y') {	/* �L�����u���[�V�����ȊO�̂Ƃ� */
				/* �˗��̌����񐔍X�V���[�� */
				/* �P�D���ʂ̃C���T�[�g�̍ۂ́A���ʂ̌����񐔂ɍ��킹�Ĉ˗��̌����񐔂����₷ */
				/*	   �����񐔂́A���ʂƓ���̂��̂��t�o�c�`�s�d����B */
				/* �Q�D"R"�i�Č��Ώہj�̏ꍇ�́A�P�̌����񐔂ɂ���Ɂ{�P���� */
				/*	   �i���[�N�V�[�g�쐬�����̂��߁j */
				/* �˗����̎擾 */
				Irai	sIrai;
				Irai	*pIrai;
				int 	cIrai;

				memset(&sIrai, 0, sizeof(sIrai));
				strncpy(sIrai.utkymd, pKekka->utkymd, sizeof(sIrai.utkymd)-1);
				strncpy(sIrai.irino, pKekka->irino, sizeof(sIrai.irino)-1);
				sIrai.zssdino = pKekka->zssdino;
				strncpy(sIrai.knsgrp, pKekka->knsgrp, sizeof(sIrai.knsgrp)-1);
				strncpy(sIrai.kmkcd, pKekka->kmkcd, sizeof(sIrai.kmkcd)-1);
				ret = ZdbIraiSelectKey(&sIrai, &pIrai, &cIrai);
				if(ret<0)
				{
					/* �˗�SELECT�G���[ */
					sprintf(errMsg,"SQL CODE:%d ZdbIraiSelectKey",ret);
					if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
						sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
					return(RET_STOP);
				}
				else if (cIrai == 0){
					sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				}
				else if (cIrai > 0) { /* �擾���� */
					/* �\���ߔ{���̃Z�b�g */
					Kskbrmst	sKskbrmst;
					Kskbrmst	*pKskbrmst;
					int 		cKskbrmst;

					/* ���͋@�敪��"YOUS"�ŋK��Z�x�͈͂Ƀq�b�g������A */
					/* ���̊�ߔ{�����˗��̗\���ߔ{���ɃZ�b�g���� */
					memset(&sKskbrmst, 0, sizeof(sKskbrmst));
					strncpy(sKskbrmst.bskkbn, "YOUS", sizeof(sKskbrmst.bskkbn)-1);
					strncpy(sKskbrmst.knsgrp, pKekka->knsgrp, sizeof(sKskbrmst.knsgrp)-1);
					strncpy(sKskbrmst.kmkcd, pKekka->kmkcd, sizeof(sKskbrmst.kmkcd)-1);
					ret = ZdbKskbrmstSelectChk(&sKskbrmst, &pKskbrmst, &cKskbrmst);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
						sprintf(errMsg,"SQL CODE:%d ZdbKskbrmstSelectChk",ret);
						if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
							sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
						return(RET_STOP);


					}
					if (ret != HRC_SQL_NOT_FOUND) {
						strncpy(pIrai->ytiksbr, pKskbrmst->ksbr, 15);
						ZbmlFree(pKskbrmst);
					}


					if(pKekka->knsflg == 'M'){
						/* �ė����̏ꍇ�͈˗��̌����񐔂Ɂ{�P����̂� */
						pIrai->knssu++;
					}
					else{
						/* ODRSSLF(�I�[�_�쐬�t���O)��'1'�ꍇ�͒N����WS�w�������̂ł����ł͂Ȃɂ����Ȃ� */
						if( pIrai->odrssflg == '1' )
						{
							/* �������Ȃ� */
						} else {
							/* �˗��̌����񐔂����ʂɍ��킹�� */
							/* �˗��̌����񐔂�(���ʂ̌����� + 1)�����ꂾ�����ꍇ�A�X�V���s��Ȃ��B �����t���O��"A"�ɍX�V���� */
							/* �˗��̌����񐔁��i���ʂ̌����񐔁{�P�j�������ꍇ�A�Č����o���Ȃ� */
							if(pKekka->knsflg=='R'&&pIrai->knssu>=(pKekka->knssu + 1) ){
								/* �Č��w�����s���Ȃ��B�������ɕς��� */
								/* �������Ȃ��i�˗��̌����񐔂�ς��Ȃ��j */
							}
							else{
								pIrai->knssu = pKekka->knssu;
							}
						}
					}
					if ((ret = ZdbIraiUpdate(pIrai)) != 0) {
						sprintf(errMsg,"SQL CODE:%d ZdbIraiUpdate",ret);
						/* �˗��A�b�v�f�[�g�G���[ */
						if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
							sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg ) ;
						return(RET_STOP);

					}
					ZbmlFree(pIrai);
				}

				/* ���ʂ̌����t���O��R��������A����ɂP�v���X���� */
				if (pKekka->knsflg == 'R')
				{
					Irai sIrai;

					memset(&sIrai, 0, sizeof(sIrai));
					strncpy(sIrai.utkymd, pKekka->utkymd, 10);
					strncpy(sIrai.irino, pKekka->irino, 11);
					sIrai.zssdino = pKekka->zssdino;
					strncpy(sIrai.knsgrp, pKekka->knsgrp, 16);
					strncpy(sIrai.kmkcd, pKekka->kmkcd, 7);

					/* ��߃t���O="2"�@���i����������͍đ���j�̏ꍇ */
					/*	 �����񐔁��Q */
					if( pKekka->kisyakflg == '2' &&
						( pKekka->knssu == 1 || pKekka->ksktkbn == 'S' ) ) {
						rKnssu = 2;
					} else {
						rKnssu = 1;
					}
					if ((ret = ZdbIraiUpdateSaiken(sIrai,rKnssu)) != 0L) {
						if(ret > 0 || ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
							sFncPutLog (TRCKIND_WARNING,__FILE__, "EntryKekka",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sprintf(errMsg,"DataBase Update Err SQL CODE:%d",ret);
						sFncSyslog ( LOG_ERR, "EntryKekka()", errMsg) ;
						return(RET_STOP);

					}
				}
			}
		}
	}
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FinsertDBCtrl()						*/
/*	�@�\�T�v  �F�R���g���[�����ʏ��̃C���T�[�g				*/
/*	��	  ��  �F							*/
/*	 ��P���� �Fbuff	���ʏ���CSV�`��1���R�[�h			*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int insertDBCtrl(char * buff)
{
	Ctrlkka 	* pKekka;
	char		** pFld;
	int 		cnt;
	int 		offset;
	int ret;
	struct tm		*ptm ;
	struct timeb	 timebuf ;
	char		errMsg[1024] = {0,};

	pKekka = malloc(sizeof(Ctrlkka));
	memset(pKekka, 0, sizeof(Ctrlkka));
	pFld = malloc(sizeof(char *)*200);
	/* �J���}��؂�̃��R�[�h�𕪊����ADB���R�[�h�̍\���̂ɐݒ肷��B */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 31) {
		/* �t�B�[���h������v���Ȃ� */
		sFncSyslog ( LOG_ERR, "insertDBCtrl()", "Ctrlkka CSV File Field Not Count." ) ;
		return -1;
	}

	/* �e�t�B�[���h���i�[����B */
	strncpy( pKekka->knskisymd , pFld[0] , sizeof( pKekka->knskisymd )-1);
	strncpy( pKekka->bskkbn , pFld[1] , sizeof( pKekka->bskkbn )-1);
	strncpy( pKekka->bsklne , pFld[2] , sizeof( pKekka->bsklne )-1);
	strncpy( pKekka->bskgok , pFld[3] , sizeof( pKekka->bskgok )-1);
	strncpy( pKekka->knsgrp , pFld[4] , sizeof( pKekka->knsgrp )-1);
	strncpy( pKekka->kmkcd , pFld[5] , sizeof( pKekka->kmkcd )-1);
	strncpy( pKekka->nbkmkcd , pFld[6] , sizeof( pKekka->nbkmkcd )-1);
	pKekka->ctrlno = atoi( pFld[7] );
	strncpy( pKekka->ctrlsbt , pFld[8] , sizeof( pKekka->ctrlsbt )-1);
	pKekka->ctrlsbteda = atoi( pFld[9] );
	strncpy( pKekka->ctrllbl , pFld[10] , sizeof( pKekka->ctrllbl )-1);
	pKekka->tstrflg = pFld[11][0];
	strncpy( pKekka->asyrckid , pFld[12] , sizeof( pKekka->asyrckid )-1);
	pKekka->asyrckpos = atoi( pFld[13] );
	pKekka->knsseq = atoi( pFld[14] );
	pKekka->bskseq = atoi( pFld[15] );
	pKekka->bthno = atoi( pFld[16] );
	pKekka->bthrckjbn = atoi( pFld[17] );
	strncpy( pKekka->syklotno , pFld[18] , sizeof( pKekka->syklotno )-1);
	strncpy( pKekka->sktti , pFld[19] , sizeof( pKekka->sktti )-1);
	strncpy( pKekka->knzti , pFld[20] , sizeof( pKekka->knzti )-1);
	pKekka->knztistflg = pFld[21][0];
	strncpy( pKekka->sktdh , pFld[22] , sizeof( pKekka->sktdh )-1);
	pKekka->ctrljti = atoi( pFld[23] );
	pKekka->chkzmflg = pFld[24][0];
	strncpy( pKekka->facter , pFld[25] , sizeof( pKekka->facter )-1);
	strncpy( pKekka->base , pFld[26] , sizeof( pKekka->base )-1);
	pKekka->kosijt = pFld[27][0];
	strncpy( pKekka->kositts , pFld[28] , sizeof( pKekka->kositts )-1);
	strncpy( pKekka->kosidh , pFld[29] , sizeof( pKekka->kosidh )-1);
	strncpy( pKekka->ksndh , pFld[30] , sizeof( pKekka->ksndh )-1);

	/* ���Z�l���R���g���[���}�X�^�̏����_�����ɍ��킹��B */
	Ctrlmst 	sCtrlmst;
	Ctrlmst 	*pCtrlmst;
	int 		cntCtrlmst;

	memset(&sCtrlmst, 0, sizeof(sCtrlmst));
	strncpy(sCtrlmst.bskkbn, pKekka->bskkbn, sizeof(sCtrlmst.bskkbn)-1);
	strncpy(sCtrlmst.nbkmkcd, pKekka->nbkmkcd, sizeof(sCtrlmst.nbkmkcd)-1);
	strncpy(sCtrlmst.ctrlsbt, pKekka->ctrlsbt, sizeof(sCtrlmst.ctrlsbt)-1);

	/* �V�X�e�����t�����擾 */
	ftime ( &timebuf ) ;
	ptm  = ( struct tm * ) localtime ( &( timebuf.time ) ) ;
	sprintf(sCtrlmst.kaiymd, "%04d-%02d-%02d", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday);

	ret = ZdbCtrlmstSelectKey(&sCtrlmst, &pCtrlmst, &cntCtrlmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"Err SQL CODE:%d ZdbCtrlmstSelectKey",ret);

		if(ret > 0 || ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
			sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBCtrl",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "insertDBCtrl()", errMsg) ;
		return(RET_STOP);

	}
	else if (ret != HRC_SQL_NOT_FOUND) {
		double		rawData;

		rawData = atof(pKekka->knzti);
		sprintf(pKekka->knzti, "%.*f", pCtrlmst->sstnksu, (rawData + 0.00001));

		ZbmlFree(pCtrlmst);
	}

	/* DB�ɃC���T�[�g */
	if ((ret = ZdbCtrlkkaInsert(pKekka)) != 0L) {
		/* �C���T�[�g�G���[ */
		sprintf(errMsg,"SQL CODE:%d ZdbCtrlkkaInsert",ret);
		/* �R���g���[�����ʂ̃C���T�[�g���s */
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBCtrl",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "insertDBCtrl()", errMsg) ;
		return(RET_STOP);
	}

	free(pKekka);
	free(pFld);

	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FinsertDBX_M()						*/
/*	�@�\�T�v  �FX-M���̃C���T�[�g 					*/
/*	��	  ��  �F							*/
/*	 ��P���� �Fbuff	���ʏ���CSV�`��1���R�[�h			*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int insertDBX_M(char * buff)
{
	Xbarm		* pXbarm;
	char		** pFld;
	int 		cnt;
	int 		offset;
	int 		ret;
	int 		chkflg;
	char		errMsg[1024] = {0,};

	pXbarm = malloc(sizeof(Xbarm));
	memset(pXbarm, 0, sizeof(Xbarm));
	pFld = malloc(sizeof(char *)*200);
	/* �J���}��؂�̃��R�[�h�𕪊����ADB���R�[�h�̍\���̂ɐݒ肷��B */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 19) {
		/* �t�B�[���h������v���Ȃ� */
		sFncSyslog ( LOG_ERR, "insertDBX_M()", "Xbarm CSV File Field Not Count." ) ;
		return -1;
	}

	/* X-M���ʂ���l�}�X�^�� sstn = 6 �ɌŒ�ɂ���(�I�����C���ŏ����_�ȉ�6���ŏo�͂��Ă����) */
	int         sstn = 6;
	/* �e�t�B�[���h���i�[����B */
	strncpy(pXbarm->knskisymd, pFld[0], 10);
	strncpy(pXbarm->bskkbn, pFld[1], 4);
	strncpy(pXbarm->bsklne, pFld[2], 4);
	strncpy(pXbarm->bskgok, pFld[3], 6);
	strncpy(pXbarm->knsgrp, pFld[4], 16);
	strncpy(pXbarm->kmkcd, pFld[5], 7);
	strncpy(pXbarm->nbkmkcd, pFld[6], 7);
	pXbarm->pltno = atoi(pFld[7]);
	pXbarm->knsseqst = atoi(pFld[8]);
	pXbarm->knsseqed = atoi(pFld[9]);
	pXbarm->bskseqst = atoi(pFld[10]);
	pXbarm->bskseqed = atoi(pFld[11]);
	pXbarm->pltseqst = atoi(pFld[12]);
	pXbarm->pltseqed = atoi(pFld[13]);
	pXbarm->pltsu = atoi(pFld[14]);
	char tmp[32];
	memset(tmp, 0, sizeof(tmp));
	sprintf(tmp, "%.*f", sstn, atof(pFld[15]));
	strncpy(pXbarm->xbarmkka, tmp, 24);

	pXbarm->xbarmjtkbn = pFld[16][0];
	pXbarm->xbarmjkflg = pFld[17][0];
	strncpy(pXbarm->ksndh, pFld[18], 26);
	/* �ʐݒ� */
	pXbarm->xbarmjtkbn = 'S';

	/* X-M�m��t���O�͐l���m�肵���ꍇ�̂�1�Ƃ��� */  
	pXbarm->xbarmjkflg = '0';

	/* ���ڃ}�X�^�[�ǂݏo�� */
	Kmkmst		sKmkmst;
	Kmkmst		*pKmkmst;
	int 		cntKmkmst;

	/* ���ڃ}�X�^�擾 */
	chkflg = 0;
	memset(&sKmkmst, 0, sizeof(Kmkmst));
	strncpy(sKmkmst.knsgrp, pXbarm->knsgrp, 16);
	strncpy(sKmkmst.kmkcd, pXbarm->kmkcd, 7);
	ret = ZdbKmkmstSelectKey(&sKmkmst, &pKmkmst, &cntKmkmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectKey",ret);
		/* �R���g���[�����ʂ̃C���T�[�g���s */
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBX_M",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "insertDBX_M()", errMsg) ;
		return(RET_STOP);
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		/* X-M�W�v�t���O('0':�W�v����A'1':�W�v���Ȃ�) */
		if (pKmkmst->xmskflg == '1') {
			/* �W�v���s��Ȃ� */
			chkflg = 2;
		}
		/* X-M�`�F�b�N�t���O('0':�ُ픻����s���A'1':�ُ픻����s��Ȃ�) */
		if (pKmkmst->xmchkflg == '1') {
			/* �ُ픻����s��Ȃ� */
			chkflg = 1;
		}
		ZbmlFree(pKmkmst);
	}

	/* X-M�W�v���s����X-M�`�F�b�N���s���ꍇ */
	if (chkflg == 0) {
		/* X_M�`�F�b�N�}�X�^�ǂݎ�� */
		Xbarmmst	sXmmst;
		Xbarmmst	*pXmmst;
		int 		cntXmmst;

		memset(&sXmmst, 0, sizeof(sXmmst));
		strncpy(sXmmst.knsgrp, pXbarm->knsgrp, 16);
		strncpy(sXmmst.kmkcd, pXbarm->kmkcd, 7);
		strncpy(sXmmst.kaiymd, pXbarm->knskisymd, sizeof(pXbarm->knskisymd)-1);
		ret = ZdbXbarmmstSelectKey(&sXmmst, &pXmmst, &cntXmmst);
		if (ret == HRC_SQL_NORMAL) {
			if (atof(pXbarm->xbarmkka) > atof(pXmmst->maxval)) {
				pXbarm->xbarmjtkbn = 'K';
			}
			if (atof(pXbarm->xbarmkka) < atof(pXmmst->minval)) {
				pXbarm->xbarmjtkbn = 'T'; /* 'L' -> 'T'�ɕύX */
			}
			ZbmlFree(pXmmst);
		}
		else {
			;
		}
	}

	/* X-M�`�F�b�N���s���ꍇ */
	if (chkflg < 2) {
		/* DB�ɃC���T�[�g */
		if ((ret = ZdbXbarmInsert(pXbarm)) != 0L) {
			/* �C���T�[�g�G���[ */
			sprintf(errMsg,"SQL CODE:%d ZdbXbarmInsert",ret);
			/* X_M���ʂ̃C���T�[�g���s */
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING,__FILE__, "insertDBX_M",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "insertDBX_M()", errMsg ) ;
			return(RET_STOP);

		}
	}
	free(pXbarm);
	free(pFld);

	return 0;
}

void sigcatch(int sig)
{
  EndFlg = 1;
  /* �V�O�i���n���h�����f�t�H���g�ɖ߂� */
  signal(sig,SIG_DFL);
}

/******************************************************************************/
/*	�� �� ���@�FsFncShmCrt()						*/
/*	�@�\�T�v�@�F���L����������						*/
/*	���@�@�́@�F								*/
/*�@ ��P���� �Fstruct appEnv * 	�v���O�������\����			*/
/*	�o�@�@�́@�F								*/
/*	���A���@�Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncShmCrt ( shm_Key )
int 	shm_Key;
{
	int 	*shmData ;

	/* �擾 */
	shm_Id = shmget ( (key_t)shm_Key, sizeof( int ), 0666 | IPC_CREAT ) ;
	if ( shm_Id < 0 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( LOG_ERR, "shmget()", "Cannot assign shared memory." ) ;
		return ( -1 ) ;
	}

	/* �A�^�b�` */
	shmData = ( int * ) shmat ( shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	/* �l�ݒ� */
	*shmData = 0 ;

	/* �f�^�b�` */
	if ( shmdt ( shmData ) == -1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*	�� �� ���@�FsFncShmGet()						*/
/*	�@�\�T�v�@�F���L�������擾						*/
/*	���@�@�́@�F								*/
/*�@ ��P���� �Fstruct appEnv * 	�v���O�������\����			*/
/*�@ ��Q���� �Fint *				�l				*/
/*	�o�@�@�́@�F								*/
/*	���A���@�Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncShmGet ( shm_Key, pshmData )
int 			shm_Key ;
int 			*pshmData ;
{
	int 	*shmData ;

	/* �A�^�b�` */
	shmData = ( int * ) shmat ( shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( LOG_ERR, "shmat()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}

	/* �l�ݒ� */
	*pshmData = *shmData ;

	/* �f�^�b�` */
	if ( shmdt ( shmData ) == -1 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( LOG_ERR, "shmdt()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*	�� �� ���@�FsFncShmDel()						*/
/*	�@�\�T�v�@�F���L�������폜						*/
/*	���@�@�́@�F								*/
/*�@ ��P���� �Fstruct appEnv * 	�v���O�������\����			*/
/*	�o�@�@�́@�F								*/
/*	���A���@�Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
static int
sFncShmDel ( shm_Key )
int 		shm_Key ;
{

	/*	�폜 */
	if ( shmctl ( shm_Id, IPC_RMID, NULL) < 0 ) {
		/* �ُ�I��	LOG */
		sFncSyslog ( LOG_ERR, "shmctl()", "Cannot operate shared memory." ) ;
		return ( -1 ) ;
	}
	return ( 0 ) ;
}

/******************************************************************************/
/*	�� �� ���@�F_sFncSyslog()						*/
/*	�@�\�T�v�@�F�V�X�e�����O�o��						*/
/*	���@�@�́@�F								*/
/*�@ ��P���� �Fint 		�v���C�I���e�B�[				*/
/*�@ ��Q���� �Fchar *		�֐���						*/
/*�@ ��R���� �Fchar *		���b�Z�[�W					*/
/*	�o�@�@�́@�F								*/
/*	���A���@�Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
static void
_sFncSyslog (int piPri, char * pcFncname,char * pcMsg ,char * pcErrCode, char * pcExeFlg, char * file, long lineno)
{
#if defined ( _SYSLOGOUT )
	if ( errno != 0 ) {
		syslog ( piPri, "Error: Function %s %s (errno=%d msg=%m)",
						pcFncname, pcMsg, errno ) ;
	} else {
		syslog ( piPri, "Error: Function %s %s (errno=%d)",
						pcFncname, pcMsg, errno ) ;
	}
#endif
	struct stcLogMember plm;

	memset(&plm, 0, sizeof(plm));
	plm.eTrcKind = TRCKIND_ERROR;
	plm.lPid = getpid() ;					/* �v���Z�XID */
	strncpy(plm.pcAppName, "MD105", 32);
	strncpy(plm.pcSrcName, file, 32);
	strncpy(plm.pcFncName, pcFncname, 32);
	plm.lLineNo = lineno;
	strncpy(plm.pcExeFlg, pcExeFlg, 2);
	strncpy(plm.pcErrCode, pcErrCode, 8);
	strncpy(plm.pcMsg, pcMsg, 1024);

	_ZbmlPutLog(&plm, file, lineno);
}
/******************************************************************************/
/*	�� �� ���@�FsFncPutlog()						*/
/*	�@�\�T�v�@�F�V�X�e�����O�o��						*/
/*	���@�@�́@�F								*/
/*�@ ��P���� �Fint 		�v���C�I���e�B�[				*/
/*�@ ��Q���� �Fchar *		�֐���						*/
/*�@ ��R���� �Fchar *		���b�Z�[�W					*/
/*	�o�@�@�́@�F								*/
/*	���A���@�Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
void
sFncPutLog(LOG_TRCKIND peTrcKind, char *pcSrcName, char *pcFncName, int plLineNo, char *
 pcExeFlg, char *pcErrCode, char *pcfmt, ... )
{
	va_list  ap ;
	struct stcLogMember plm;

	/***
	 ***	���O�����l�ݒ�
	 ***/
	memset(&plm, 0, sizeof(plm));
	plm.eTrcKind = peTrcKind ;
	strcpy ( plm.pcFncName, pcFncName ) ;
	strcpy ( plm.pcExeFlg,	pcExeFlg ) ;
	strcpy ( plm.pcErrCode, pcErrCode ) ;
	va_start ( ap, pcfmt ) ;
	vsprintf ( plm.pcMsg, pcfmt, ap ) ;
	va_end ( ap ) ;

	/***
	 ***	���O�o��
	 ***/
	_ZbmlPutLog ( &plm, pcSrcName, plLineNo) ;
	return ;

}

/* �w�蕶����̑O��̃X�y�[�X����菜���ĕ�������R�s�[���� */
void trim(char * dst, char *src) {
	int dstCnt;
	int srcCnt;
	int Flg;

	for(dstCnt = 0, srcCnt = 0, Flg = 0;
		src[srcCnt] != '\0';
		srcCnt ++) {
		if ((dstCnt == 0) && (src[srcCnt] == '\x20')) {
			continue;
		}
		dst[dstCnt++] = src[srcCnt];
		if (src[srcCnt] != '\x20') {
			Flg = dstCnt;
		}
	}
	dst[Flg] = '\0';
}

/******************************************************************************/
/*	�� �� ��  �FTourokuChk()						*/
/*	�@�\�T�v  �F���ʏ��o�^�`�F�b�N					*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
/* ���ʏ��o�^�`�F�b�N */
int TourokuChk(Kekka *pKekka, int *iKesseiflg)
{


	int 		ret = 0;
	Realchk 	*pReal;
	Kenorder	sKenorder;
	Kenorder	*pKenorder;
	int 		orderCnt;
	char		errMsg[1024] = {0,};

	/* ��l�}�X�^�̎擾 */
	Kjnmst		sKjnmst;
	Kjnmst		*pKjnmst;
	int 		cntKjnmst;

	memset(&sKjnmst, 0, sizeof(sKjnmst));
	strncpy(sKjnmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sKjnmst.kjno, pKekka->kjno, 9);

	/* ��l�}�X�^SELECT */
	ret = ZdbKjnmstSelectKey2(&sKjnmst, &pKjnmst, &cntKjnmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKjnmstSelectKey2",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "TourokuChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "TourokuChk()", errMsg ) ;
		return(RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		sFncPutLog (TRCKIND_DEBUG, __FILE__, "TourokuChk", __LINE__,
			 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, "ZdbKjnmstSelectKey2 Not Found ret:0") ;
		return 0;
	}

	/* �V�����ǉ��R�[�h filterChk2 */
	ret = filterChk2(pKekka, pKjnmst);
	if(RET_STOP == ret || ret == RET_CONTINUITY){
		ZbmlFree(pKjnmst);
		return ret;
	}

	/* ��l�`�F�b�N */
	if (kjnChk(pKekka, pKjnmst) != 0) {
		ZbmlFree(pKjnmst);
		return -3;
	}
	ZbmlFree(pKjnmst);

	/* �I�[�_�[&�����`�F�b�NSELECT */
	memset(&sKenorder, 0, sizeof(sKenorder));
	strncpy(sKenorder.knskisymd, pKekka->knskisymd, 10);
	strncpy(sKenorder.sriymd, pKekka->sriymd, 10);
	strncpy(sKenorder.kntno, pKekka->kntno, 13);
	strncpy(sKenorder.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKenorder.kmkcd, pKekka->kmkcd, 8);
	sKenorder.knssu = pKekka->knssu;
	sKenorder.knssueda = 0;

	ret = ZdbKenorderRealchkSelectKey(&sKenorder, &pKenorder, &pReal, &orderCnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKenorderRealchkSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "TourokuChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "TourokuChk()", errMsg ) ;
		return(RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		/* �Č������l�����A�����񐔂��P���傫���Ƃ��͌����񐔂��f�N�������g�� */
		/* ������x�A��������B */
		if (sKenorder.knssu > 1) {
			sKenorder.knssu--;
			ret = ZdbKenorderRealchkSelectKey(&sKenorder, &pKenorder, &pReal, &orderCnt);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				sprintf(errMsg,"SQL CODE:%d ZdbKenorderRealchkSelectKey",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING , __FILE__, "TourokuChk", __LINE__,
						 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "TourokuChk()", errMsg ) ;
				return(RET_STOP);
			}
			if (ret == HRC_SQL_NOT_FOUND) {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	/* �P�O�O���`�F�b�N */
	if (pReal[0].per100flg == '1') {
		/* 100���`�F�b�N */
		per100Chk(pKekka);
	}
	else {
		pKekka->per100flg = '0';				/* �P�O�O���`�F�b�N */
	}

	/* �ƍ��`�F�b�N */
	/*	�y�����z */
	/*	�I�[�_��񂪑��݂����i�I�[�_���E�񐔂ƌ��ʏ��̉񐔂ɍ��فj�A */
	/*	�����H���敪�j�i�Č��j�̏ꍇ�̂ݍs�� */
	if ( sKenorder.knssu != pKekka->knssu && pKekka->ksktkbn == 'K' ) {
		ret = shougoChk(pKekka, pKenorder, iKesseiflg);
		if(ret == RET_STOP || ret == RET_CONTINUITY)
			return ret;
	} else if ( sKenorder.knssu == pKekka->knssu && pKekka->ksktkbn == 'K' ) {
		pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
		pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
		pKekka->siyflg			= ' ';				/* �̗p�t���O */
		pKekka->knsflg			= 'A';				/* �����t���O */
	}

	/* ���͑O��`�F�b�N */
	if (pReal[0].tousekflg == '1') {
		ret = tousekiChk(pKekka);
		if(ret == RET_STOP || ret == RET_CONTINUITY)
			return ret;
	}
	else {
		pKekka->tousekflg = '0';
	}

	/* ���փ`�F�b�N(WS��) */
	if (pReal[0].soukn2flg == '1') {
		ret = soukanChk(pKekka, pKenorder);
		if(ret == RET_STOP || ret == RET_CONTINUITY)
			return ret;
	}
	else {
		pKekka->soukn2flg = '0';
	}


	/* �a�l�k�p�j�b�N�`�F�b�N */
	ret = BmlPanicChk(pKekka, pKenorder);
	if(RET_STOP == ret || ret == RET_CONTINUITY)
		return ret;

    /* �������p�j�b�N�`�F�b�N */
    ret = KnsPanicChk(pKekka, pKenorder);
    if(RET_STOP == ret || ret == RET_CONTINUITY)
        return ret;

	/* ���悻�낢�`�F�b�N(�ƍ��m�f�̂ݍs��) */
	ret = bungaChk(pKekka, iKesseiflg);
	if(RET_STOP == ret || ret == RET_CONTINUITY)
		return ret;

	ZbmlFree(pReal);
	ZbmlFree(pKenorder);

	return 0;
}
/******************************************************************************/
/*	�� �� ��  �Fkjnchk()							*/
/*	�@�\�T�v  �F��l�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					 0	����				*/
/*					-1	�ُ�				*/
/******************************************************************************/
int kjnChk(Kekka *pKekka, Kjnmst *pKjnmst)
{
	/* ��l����ُ�敪���`�F�b�N���A���ʈُ�敪��ݒ肷�� */
	char		tmp1[16];
	char		tmp2[16];
	double		rawData;
	char		wk_knskka[25];
	int 		ikzn;
	int 		iwkkzn;

	/* �ُ�l�敪�̏����� */
	pKekka->ijkbnm = pKekka->ijkbnf = pKekka->ijkbnn = ' ';
	ikzn = 0;

	trim(wk_knskka, pKekka->knskka2);

	/* ���ʃR�����g�̊�l���f��ǉ� */
	if( pKekka->knskka2kbn[0] == '0' && atoi(wk_knskka) < 500 ){ /* *500�ȉ��̌��ʃR�����g���H */
		/* ���ʃR�����g�̃`�F�b�N */
		if(CHK_Kkacmt(wk_knskka) == 0){
			/* �ُ�l�}�[�N����; */
			pKekka->ijkbnm = ' ';
			pKekka->ijkbnf = ' ';
			pKekka->ijkbnn = ' ';
		}
		else {
			/* �ُ�l�}�[�N�L��; */
			pKekka->ijkbnm = '*';
			pKekka->ijkbnf = '*';
			pKekka->ijkbnn = '*';
		}
		return 0;
	}

	/* �萫���ڂ̏ꍇ�A��l����̈ג萫�l�����Z�l�ɕϊ����� */
	if (pKekka->tstrflg == 'S') {
		/* �萫���� */
		/* ���ʃf�[�^�ɐ��l�ȊO�����邩�`�F�b�N */
		ikzn = CHG_Mojikjn(wk_knskka,pKekka->knskka2kbn[0]);
		if(ikzn == 0){
			/* ���Z�l��������Ȃ����� */
			/* ��l�}�X�^�Ɋ�l�ݒ肪����ꍇ"*"�A */
			/* ��l�}�X�^�Ɋ�l�ݒ肪�Ȃ��ꍇ" " */
			/* ��ݒ肷�� */

			/* �j�� */
			trim(tmp1, pKjnmst->kjnmlw);
			trim(tmp2, pKjnmst->kjnmhi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnm = ' ';
			}
			else {
				pKekka->ijkbnm = '*';
			}

			/* ���� */
			trim(tmp1, pKjnmst->kjnflw);
			trim(tmp2, pKjnmst->kjnfhi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnf = ' ';
			}
			else {
				pKekka->ijkbnf = '*';
			}

			/* �s�� */
			trim(tmp1, pKjnmst->kjnelw);
			trim(tmp2, pKjnmst->kjnehi);
			if (strlen(tmp1) == 0 && strlen(tmp2) == 0) {
				pKekka->ijkbnn = ' ';
			}
			else {
				pKekka->ijkbnn = '*';
			}
			/* �ُ�l�敪���ݒ肳�ꂽ�̂Ŕ����� */
			return 0;
		}

		/* ��l �� ���Z�l�ϊ��i�萫���ڂ̂݁j */
		/* �j��l�P */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm1,"%d",iwkkzn);
		}
		/* �j��l�Q */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwm2,"%d",iwkkzn);
		}
		/* �j��l�� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnmlw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmlw,"%d",iwkkzn);
		}
		/* �j��l���� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjm1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm1,"%d",iwkkzn);
		}
		/* �j���l�Q */
		iwkkzn =  CHG_Mojikjn(pKjnmst->him2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him2,"%d",iwkkzn);
		}
		/* �j���l�P */
		iwkkzn =  CHG_Mojikjn(pKjnmst->him1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->him1,"%d",iwkkzn);
		}
		/* �j��l�� */
		iwkkzn = CHG_Mojikjn(pKjnmst->kjnmhi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnmhi,"%d",iwkkzn);
		}
		/* �j��l���� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjm2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjm2,"%d",iwkkzn);
		}
		/* ����l�P */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf1,"%d",iwkkzn);
		}
		/* ����l�Q */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwf2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwf2,"%d",iwkkzn);
		}
		/* ����l�� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnflw,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnflw,"%d",iwkkzn);
		}
		/* ����l���� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnnaf1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnnaf1,"%d",iwkkzn);
		}
		/* �����l�Q */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hif2,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif2,"%d",iwkkzn);
		}
		/* �����l�P */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hif1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->hif1,"%d",iwkkzn);
		}
		/* ����l�� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnfhi,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->kjnfhi,"%d",iwkkzn);
		}
		/* ����l���� */
		iwkkzn = CHG_Mojikjn(pKjnmst->kjnnaf2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnnaf2,"%d",iwkkzn);
		}
		/* �s����l�P */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwe1,'X');
		if( iwkkzn != 0 ){
			sprintf(pKjnmst->lwe1,"%d",iwkkzn);
		}
		/* �s����l�Q */
		iwkkzn = CHG_Mojikjn(pKjnmst->lwe2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->lwe2,"%d",iwkkzn);
		}
		/* �s����l�� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnelw,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnelw,"%d",iwkkzn);
		}
		/* �s����l���� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kje1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje1,"%d",iwkkzn);
		}
		/* �s�����l�Q */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hie2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie2,"%d",iwkkzn);
		}
		/* �s�����l�P */
		iwkkzn =  CHG_Mojikjn(pKjnmst->hie1,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->hie1,"%d",iwkkzn);
		}
		/* �s����l�� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kjnehi,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kjnehi,"%d",iwkkzn);
		}
		/* �s����l���� */
		iwkkzn =  CHG_Mojikjn(pKjnmst->kje2,'X');
		if( iwkkzn != 0){
			sprintf(pKjnmst->kje2,"%d",iwkkzn);
		}
	}
#define chknum1(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 < atof(p2)))
#define chknum2(p1, p2) 	((strncmp(p2, "        ", 8) != 0) && (p1 > atof(p2)))

#define chknumi1(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 < atoi(p2)))
#define chknumi2(p1, p2)	((strncmp(p2, "        ", 8) != 0) && (p1 > atoi(p2)))

	if( ikzn == 0 ){
		//rawData = atof(pKekka->rawdata);
		//rawData = atof(pKekka->skkaka);
		rawData = atof(pKekka->knskka1);
		if (pKmkmst != NULL && pKmkmst->ltmmnflg == '1') {
			rawData = rawData - pow(10.0, pKjnmst->kjsstnksu);
		}

		/* ��ʍ��ڂ̔�r(float float) */
		/* �j���̃`�F�b�N */
		pKekka->ijkbnm = '5';
		if chknum1(rawData , pKjnmst->lwm1) {
			pKekka->ijkbnm = '1';
		}
		else if chknum1(rawData, pKjnmst->lwm2) {
			pKekka->ijkbnm = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnmlw) {
			pKekka->ijkbnm = '3';
		}
		else if chknum1(rawData, pKjnmst->kjm1) {
			pKekka->ijkbnm = '4';
		}
		else if chknum2(rawData, pKjnmst->him2) {
			pKekka->ijkbnm = '9';
		}
		else if chknum2(rawData, pKjnmst->him1) {
			pKekka->ijkbnm = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnmhi) {
			pKekka->ijkbnm = '7';
		}
		else if chknum2(rawData, pKjnmst->kjm2) {
			pKekka->ijkbnm = '6';
		}
		/* �����̃`�F�b�N */
		pKekka->ijkbnf = '5';
		if chknum1(rawData, pKjnmst->lwf1) {
			pKekka->ijkbnf = '1';
		}
		else if chknum1(rawData, pKjnmst->lwf2) {
			pKekka->ijkbnf = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnflw) {
			pKekka->ijkbnf = '3';
		}
		else if chknum1(rawData, pKjnmst->kjnnaf1) {
			pKekka->ijkbnf = '4';
		}
		else if chknum2(rawData, pKjnmst->hif2) {
			pKekka->ijkbnf = '9';
		}
		else if chknum2(rawData, pKjnmst->hif1) {
			pKekka->ijkbnf = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnfhi) {
			pKekka->ijkbnf = '7';
		}
		else if chknum2(rawData, pKjnmst->kjnnaf2) {
			pKekka->ijkbnf = '6';
		}
		/* �s���̃`�F�b�N */
		pKekka->ijkbnn = '5';
		if chknum1(rawData, pKjnmst->lwe1) {
			pKekka->ijkbnn = '1';
		}
		else if chknum1(rawData, pKjnmst->lwe2) {
			pKekka->ijkbnn = '2';
		}
		else if chknum1(rawData, pKjnmst->kjnelw) {
			pKekka->ijkbnn = '3';
		}
		else if chknum1(rawData, pKjnmst->kje1) {
			pKekka->ijkbnn = '4';
		}
		else if chknum2(rawData, pKjnmst->hie2) {
			pKekka->ijkbnn = '9';
		}
		else if chknum2(rawData, pKjnmst->hie1) {
			pKekka->ijkbnn = '8';
		}
		else if chknum2(rawData, pKjnmst->kjnehi) {
			pKekka->ijkbnn = '7';
		}
		else if chknum2(rawData, pKjnmst->kje2) {
			pKekka->ijkbnn = '6';
		}
	}
	else{
		/* �萫�l�̊��Z�����������̂ŁA */
		/* ���Z�l�����[�f�[�^�Ƃ��Ĉ��� */

		/* �萫���ڂ̔�r */
		/* �j���̃`�F�b�N */
		pKekka->ijkbnm = '5';
		if chknumi1(ikzn , pKjnmst->lwm1) {
			pKekka->ijkbnm = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwm2) {
			pKekka->ijkbnm = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnmlw) {
			pKekka->ijkbnm = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kjm1) {
			pKekka->ijkbnm = '4';
		}
		else if chknumi2(ikzn, pKjnmst->him2) {
			pKekka->ijkbnm = '9';
		}
		else if chknumi2(ikzn, pKjnmst->him1) {
			pKekka->ijkbnm = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnmhi) {
			pKekka->ijkbnm = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kjm2) {
			pKekka->ijkbnm = '6';
		}
		/* �����̃`�F�b�N */
		pKekka->ijkbnf = '5';
		if chknumi1(ikzn, pKjnmst->lwf1) {
			pKekka->ijkbnf = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwf2) {
			pKekka->ijkbnf = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnflw) {
			pKekka->ijkbnf = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kjnnaf1) {
			pKekka->ijkbnf = '4';
		}
		else if chknumi2(ikzn, pKjnmst->hif2) {
			pKekka->ijkbnf = '9';
		}
		else if chknumi2(ikzn, pKjnmst->hif1) {
			pKekka->ijkbnf = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnfhi) {
			pKekka->ijkbnf = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kjnnaf2) {
			pKekka->ijkbnf = '6';
		}
		/* �s���̃`�F�b�N */
		pKekka->ijkbnn = '5';
		if chknumi1(ikzn, pKjnmst->lwe1) {
			pKekka->ijkbnn = '1';
		}
		else if chknumi1(ikzn, pKjnmst->lwe2) {
			pKekka->ijkbnn = '2';
		}
		else if chknumi1(ikzn, pKjnmst->kjnelw) {
			pKekka->ijkbnn = '3';
		}
		else if chknumi1(ikzn, pKjnmst->kje1) {
			pKekka->ijkbnn = '4';
		}
		else if chknumi2(ikzn, pKjnmst->hie2) {
			pKekka->ijkbnn = '9';
		}
		else if chknumi2(ikzn, pKjnmst->hie1) {
			pKekka->ijkbnn = '8';
		}
		else if chknumi2(ikzn, pKjnmst->kjnehi) {
			pKekka->ijkbnn = '7';
		}
		else if chknumi2(ikzn, pKjnmst->kje2) {
			pKekka->ijkbnn = '6';
		}
	}
	return 0;
}


/******************************************************************************/
/*	�� �� ��  �FfilterChk2()						*/
/*	�@�\�T�v  �F�t�B���^�[�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
int filterChk2(Kekka *pKekka, Kjnmst *pKjnmst)
{
	Kkafltmst2	 *pKkafltmst2;
	Kkafltmst2	 sKkafltmst2;
	int 		ret;
	int 		Kkafltmstflg;
	int 		cnt;
	int 		lCnt;
	double		rawData;
	double		DataMax;
	double		DataMin;
	char		tmp[32];
	int 		mojiFlg = 0;
	char		errMsg[1024] = {0,};

	pKkafltmst2 = NULL;

	/* �t�B���^�[�}�X�^�[�ǂݏo�� */
	memset(&sKkafltmst2, 0, sizeof(sKkafltmst2));
	strncpy(sKkafltmst2.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKkafltmst2.kmkcd, pKekka->kmkcd, 7);
	strncpy(sKkafltmst2.sstcd, pKekka->sstcd, 7);
	cnt = 0;

	ret = ZdbKkafltmstSelectGRPKMKKey2(&sKkafltmst2, &pKkafltmst2, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbKkafltmstSelectGRPKMKKey2",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "filterChk2", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "filterChk2()", errMsg ) ;
		return(RET_STOP);
	}

	/* ���ʒl�̒l������𐔒l������ */
	memset(tmp, 0, sizeof(tmp));
	trim(tmp, pKekka->rawdata);
	if ((tmp[0] >= '0'&&tmp[0]<='9') || tmp[0]=='+' || tmp[0]=='-' || tmp[0] == '.' ) {
		rawData = atof(tmp);
	}
	else {
		/* �����̂Ƃ��̓t�B���^�[�������s��Ȃ� */
		cnt = 0;
		mojiFlg = 1;
		ZbmlFree(pKkafltmst2);
	}

	Kkafltmstflg = 0;
	if (cnt > 0) {
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			/* ����E�����̒l������𐔒l������ */
			memset(tmp, 0, sizeof(tmp));
			strncpy(tmp, pKkafltmst2[lCnt].minval, 12);
			DataMin = atof(tmp);

			memset(tmp, 0, sizeof(tmp));
			strncpy(tmp, pKkafltmst2[lCnt].maxval, 12);
			DataMax = atof(tmp);

			if ((DataMin <= rawData) && (rawData <= DataMax)) {
				strncpy(pKekka->knskka1, pKkafltmst2[lCnt].knskka1, 12);
				strncpy(pKekka->knskka2, pKkafltmst2[lCnt].knskka2, 24);
				strncpy(pKekka->knskka2kbn, pKkafltmst2[lCnt].knskka2kbn, 2);
				strncpy(pKekka->kkahskcd, pKkafltmst2[lCnt].kkahskcd, 3);
				strncpy(pKekka->skkka, pKkafltmst2[lCnt].hjkka, 24);	 /*  */
				if (pKjnmst->kjsstnksu == 9) {
					sprintf(tmp, "%.0f", (rawData + 0.00001));
				}
				else {
					sprintf(tmp, "%.*f", pKjnmst->kjsstnksu, (rawData + 0.00001));
				}
				strncpy(pKekka->hjkka, tmp, 24);
				Kkafltmstflg = 1;
				break;
			}
		}
		ZbmlFree(pKkafltmst2);
	}
	if ((cnt <= 0) || (Kkafltmstflg == 0)) {
		/* �t�B���^�[�}�X�^�[�ɑ��݂��Ȃ��Ƃ� */
		/* �t�B���^�[�}�X�^�[�̏��Ńq�b�g���Ȃ������B */
		if (mojiFlg == 1) {
			strncpy(pKekka->knskka2, tmp, 24);
			strncpy(pKekka->knskka2kbn, "X", 2);
		}
		else if (pKjnmst->kjsstnksu == 9) {
			/* �����_�������X�̎��͒��l */
			sprintf(tmp, "%.0f", (rawData + 0.00001));
			strncpy(pKekka->knskka2, tmp, 24);
			strncpy(pKekka->knskka2kbn, "X", 2);
		}
		else {
			sprintf(tmp, "%.*f", pKjnmst->kjsstnksu, (rawData + 0.00001));
			if (pKekka->tstrflg == 'S') {		/* �萫 */
				strncpy(pKekka->knskka2, tmp, 24);
				strncpy(pKekka->knskka2kbn, "X", 2);
			}
			else if (pKekka->tstrflg == 'R') {	/* ��� */
				memset(pKekka->knskka1, ' ', 12);
				strcpy(&(pKekka->knskka1[12-strlen(tmp)]), tmp);
				strncpy(tmp, pKekka->knskka1, 32);
			}
			else {								/* �s�� */
				strncpy(pKekka->knskka2, tmp, 24);
				strncpy(pKekka->knskka2kbn, "X", 2);
			}
		}
		trim(pKekka->hjkka, tmp);			/* ���l(��ʎ��E�l�ɂȂ��Ă�����̂����l�ɕϊ�) */
		strncpy(pKekka->skkka, tmp, 24);	/* ��ʎ��E�l�E����ȊO���l */
	}
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �Fper100Chk() 						*/
/*	�@�\�T�v  �F100%�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
int per100Chk(Kekka *pKekka)
{

/* ���Ή��̂��߁A�������Ȃ� */

	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FBmlPanicChk()						*/
/*	�@�\�T�v  �F�a�l�k�p�j�b�N�`�F�b�N					*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
int BmlPanicChk(Kekka *pKekka, Kenorder *pKenorder)
{
	Rngchkmst	sRngchkmst;
	Rngchkmst	*pRngchkmst;
	int 		cnt;
	int 		ret;
	double		rawData;
	char		cRawBuf[256];
	char		errMsg[1024] = {0,};

	/* ���f�[�^���Ȃ�(�X�y�[�Xor/)�̏ꍇ�Ȃɂ����Ȃ� */
	memset(cRawBuf, 0, sizeof(cRawBuf));
	trim(cRawBuf, pKekka->rawdata);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, 0, sizeof(Rngchkmst));
	/* �͈͋敪�������ɒǉ� */
	sRngchkmst.hnikbn = BML_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pKenorder->zrcd, "001", 3) == 0)
		|| (strncmp(pKenorder->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pKenorder->sbtkbn;
	/* �{�݃R�[�h�A���ʋ敪���w�肵�Č��� */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg) ;
		return(RET_STOP);

	}
	/* ������Ȃ������ꍇ�A�{�݃R�[�h���w��A���ʋ敪���I�[��(' ')�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
        sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "BmlPanicChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	/* ����Ɍ�����Ȃ������ꍇ�A���ʋ敪���w�肵�A�{�݃R�[�h���I�[��(0000000)�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pKenorder->sbtkbn;
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����ł�������Ȃ������ꍇ�A�{�݃R�[�h�A���ʋ敪���ɃI�[���w��Ō��� */
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "BmlPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "BmlPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->rawdata);
		pKekka->pncrgflg = '0';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ((atof(pRngchkmst[lCnt].hrng) >= rawData) &&
				(rawData >= atof(pRngchkmst[lCnt].lrng))) {
				pKekka->pncrgflg = '0';
			}
			else {
				pKekka->pncrgflg = '1';
				break;
			}
		}
	}
	ZbmlFree(pRngchkmst);
	return 0;
}

/******************************************************************************/
/*  �� �� ��  �FKnsPanicChk()                                                 */
/*  �@�\�T�v  �F�������p�j�b�N�`�F�b�N                                        */
/*  ��    ��  �F                                                              */
/*   ��P���� �FpKekka  ���ʏ��                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �Fint                                                           */
/*                   0  ����                                                  */
/*                  -1  �ُ�                                                  */
/******************************************************************************/
int KnsPanicChk(Kekka *pKekka, Kenorder *pKenorder)
{
	Rngchkmst   sRngchkmst;
	Rngchkmst   *pRngchkmst;
	int         cnt;
	int         ret;
	double      rawData;
	char        cRawBuf[256];
	char        errMsg[1024] = {0,};

	/* ���f�[�^���Ȃ�(�X�y�[�Xor/)�̏ꍇ�Ȃɂ����Ȃ� */
	memset(cRawBuf, 0, sizeof(cRawBuf));
	trim(cRawBuf, pKekka->rawdata);
	if( cRawBuf[0]	== '\0' || cRawBuf[0]  == '/' )
		return 0;

	memset(&sRngchkmst, 0, sizeof(Rngchkmst));
	/* �͈͋敪�������ɒǉ�(�������p�j�b�N�̂ݎ擾) */
	sRngchkmst.hnikbn = KNS_PANIC;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pKenorder->zrcd, "001", 3) == 0)
		|| (strncmp(pKenorder->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pKenorder->sbtkbn;
	/* �{�݃R�[�h�A���ʋ敪���w�肵�Č��� */
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg) ;
		return(RET_STOP);

	}
	/* ������Ȃ������ꍇ�A�{�݃R�[�h���w��A���ʋ敪���I�[��(' ')�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
        sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "KnsPanicChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	/* ����Ɍ�����Ȃ������ꍇ�A���ʋ敪���w�肵�A�{�݃R�[�h���I�[��(0000000)�Ŏw�肵�Č���*/
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pKenorder->sbtkbn;
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectKey2",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg) ;
			return(RET_STOP);
		}
	}
	/* ����ł�������Ȃ������ꍇ�A�{�݃R�[�h�A���ʋ敪���ɃI�[���w��Ō��� */
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "KnsPanicChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "KnsPanicChk()", errMsg ) ;
			return(RET_STOP);
		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		rawData = atof(pKekka->rawdata);
		pKekka->knspncrgflg = '0';
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			if ((atof(pRngchkmst[lCnt].hrng) >= rawData) &&
				(rawData >= atof(pRngchkmst[lCnt].lrng))) {
				pKekka->knspncrgflg = '0';
			}
			else {
				pKekka->knspncrgflg = '1';
				break;
			}
		}
	}
	ZbmlFree(pRngchkmst);
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FtousekiChk()						*/
/*	�@�\�T�v  �F���͑O��`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
int tousekiChk(Kekka *pKekka)
{
	Tschkmst	sTschkmst;
	Tschkmst	*pTschkmst;
	int 		cntTschkmst;
	int 		ret;
	Kekka		sKekka;
	Kekka		*spKekka;
	int 		cntKekka;
	int 		flg;
	double		rawData;
	int 		updateflg;
	char		errMsg[1024] = {0,};

	if ((strncmp(pKekka->tskflg, "�", 2) != 0) &&
		(strncmp(pKekka->tskflg, "�", 2) != 0)) {
		/* ���͍��ڂłȂ��B */
		pKekka->tousekflg = '1';
		return 0;
	}

	/* ���͂̑������ڂ𒲂ׂ�i���͑O��`�F�b�N�}�X�^�j */
	memset(&sTschkmst, 0, sizeof(Tschkmst));
	if (strncmp(pKekka->tskflg, "�", 2) == 0) {
		strncpy(sTschkmst.kmkcdzen, pKekka->kmkcd, 7);
		strncpy(sTschkmst.kmkcdgo, "       ", 7);
		flg = 0;
	}
	else {
		strncpy(sTschkmst.kmkcdzen, "       ", 7);
		strncpy(sTschkmst.kmkcdgo, pKekka->kmkcd, 7);
		flg = 1;
	}
	pTschkmst->tskchktyp = '2'; 	/* �V���O���E�}���`�n�̂��߃`�F�b�N�^�C�vA�Œ� */
	ret = ZdbTschkmstSelectKey2(&sTschkmst, &pTschkmst, &cntTschkmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		pKekka->tousekflg = '2';
		pKekka->knsflg = 'A';

		sprintf(errMsg,"SQL CODE:%d ZdbTschkmstSelectKey2",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "tousekiChk", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "tousekiChk()", errMsg ) ;
		return(RET_STOP);

		//return -1;
	}

	if (ret != HRC_SQL_NOT_FOUND) {
		/* �΂ɂȂ錟�����ʂ����� */
		memcpy(&sKekka, pKekka, sizeof(Kekka) );
		if (flg == 0) {
			strncpy(sKekka.kmkcd, pTschkmst->kmkcdgo, 8);
		}
		else {
			strncpy(sKekka.kmkcd, pTschkmst->kmkcdzen, 8);
		}
		ret = ZdbKekkaSelectIrai(&sKekka, &spKekka, &cntKekka);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sFncSyslog ( LOG_ERR, "tousekiChk()", "DataBase Tschkmst Select Error." ) ;
			pKekka->tousekflg = '2';
			pKekka->knsflg = 'A';

			sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectIrai",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "tousekiChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "tousekiChk()", errMsg) ;
			return(RET_STOP);

		}
		if (ret != HRC_SQL_NOT_FOUND) {
			/* �`�F�b�N�^�C�v�ɂ��A�������߂邩�A������߂ă`�F�b�N����B */
			pKekka->tousekflg = '1';
			updateflg = 0;
			if (pTschkmst->tskchktyp == '2') {
				/* �^�C�vA */
				if (flg == 0) {
					if ((atof(spKekka->rawdata) - atof(pKekka->rawdata)) >= 0) {
						pKekka->tousekflg = '2';
						spKekka->tousekflg = '2';
						pKekka->knsflg = 'A';
						spKekka->knsflg = 'A';
						updateflg = 1;
					}
				}
				else {
					if ((atof(pKekka->rawdata) - atof(spKekka->rawdata)) >= 0) {
						pKekka->tousekflg = '2';
						spKekka->tousekflg = '2';
						pKekka->knsflg = 'A';
						spKekka->knsflg = 'A';
						updateflg = 1;
					}
				}
			}
			else {
				/* �^�C�vB */
				if (flg == 0) {
					rawData = atof(spKekka->rawdata) / atof(pKekka->rawdata) *100;
				}
				else {
					rawData = atof(pKekka->rawdata) / atof(spKekka->rawdata) * 100;
				}
				if ((atof(pTschkmst->maxval) != 0) && (atof(pTschkmst->maxval) < rawData)) {
					pKekka->tousekflg = '2';
					spKekka->tousekflg = '2';
					pKekka->knsflg = 'A';
					spKekka->knsflg = 'A';
					updateflg = 1;
				}
				if ((atof(pTschkmst->minval) != 0) && (atof(pTschkmst->minval) > rawData)) {
					pKekka->tousekflg = '2';
					spKekka->tousekflg = '2';
					pKekka->knsflg = 'A';
					spKekka->knsflg = 'A';
					updateflg = 1;
				}
			}

			if (updateflg == 1) {
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING , __FILE__, "tousekiChk", __LINE__,
							 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog (LOG_ERR,"tousekiChk()",errMsg);
					return(RET_STOP);

				}
			}
		}
		else {
			/* ����̌��ʂ��Ȃ� */
			pKekka->knsflg = 'A';
		}
	}
	ZbmlFree(spKekka);
	ZbmlFree(pTschkmst);
	return 0;
}
/******************************************************************************/
/*	�� �� ��  �FbungaChk()							*/
/*	�@�\�T�v  �F���悻�낢�`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
int bungaChk(Kekka *pKekka, int *iKesseiflg)
{
	/* ���ڃ}�X�^�����āA������Ă��邩�m�F���� */
	Kmkmst		sKmkmst;
	Kmkmst		*pKmkmst;
	int 		cntKmkmst;
	int 		ret;
	Kekka		sKekka;
	Kekka		*spKekka;
	int 		cntKekka;
	int 		cnt;
	int 		lcnt;
	int 		flg;
	char		errMsg[1024] = {0,};

	/* �e���ڃR�[�h�擾 */
	memset(&sKmkmst, 0, sizeof(Kmkmst));
	strncpy(sKmkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sKmkmst.kmkcd, pKekka->kmkcd, 7);
	ret = ZdbKmkmstSelectKey(&sKmkmst, &pKmkmst, &cntKmkmst);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
				 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
		return(RET_STOP);

	}
	if (ret != HRC_SQL_NOT_FOUND) {
		memcpy(&sKmkmst, pKmkmst, sizeof(Kmkmst));
		ZbmlFree(pKmkmst);
		if (sKmkmst.fkbnkkb != '2') {
			/* ����q�łȂ��Ƃ��̓`�F�b�N���Ȃ� */
			return 0;
		}
		/* �����e���ڃR�[�h�̍��ڂ�T���o���B */
		ret = ZdbKmkmstSelectKey4(&sKmkmst, &pKmkmst, &cntKmkmst);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

			sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectKey4",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
					 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
			return(RET_STOP);
		}
		if (ret != HRC_SQL_NOT_FOUND){
			flg = 1;
			for (cnt = 0; cnt < cntKmkmst; cnt++) {
				if (strncmp(pKekka->kmkcd, pKmkmst[cnt].kmkcd, 7) == 0) {
					continue;
				}
				if (pKmkmst[cnt].fkbnkkb == '1') {
					/* ����̐e�̓`�F�b�N�ΏۊO */
					continue;
				}
				memcpy(&sKekka, pKekka, sizeof(Kekka) );
				strncpy(sKekka.kmkcd, pKmkmst[cnt].kmkcd, 8);
				ret = ZdbKekkaSelectKey2(&sKekka, &spKekka, &cntKekka);
				if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND))
				{

					sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKey2",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
							 EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}

					sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
					ZbmlFree(pKmkmst);
					return(RET_STOP);
				}
				if (ret == HRC_SQL_NOT_FOUND ||
						spKekka->syougoflg == '2' ) {
					flg = 0;
				}
				ZbmlFree(spKekka);
			}
			if (flg == 1) {
				/* ���ׂĂ̌��ʂ�������Ă���B */
				/* �񍐉\�Ƀt���O��ݒ� */
				for (cnt = 0; cnt < cntKmkmst; cnt++) {
					if (strncmp(pKekka->kmkcd, pKmkmst[cnt].kmkcd, 7) == 0) {
						continue;
					}
					memcpy(&sKekka, pKekka, sizeof(Kekka) );
					strncpy(sKekka.kmkcd, pKmkmst[cnt].kmkcd, 8);
					ret = ZdbKekkaSelectKey2(&sKekka, &spKekka, &cntKekka);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

						sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKey2",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}

						sFncSyslog(LOG_ERR,"bungaChk()",errMsg);
						ZbmlFree(pKmkmst);
						return(RET_STOP);
					}
					if (ret == HRC_SQL_NOT_FOUND) {
						for (lcnt = 0; lcnt < cntKekka; lcnt++) {
							ret = ZdbKekkaUpdate(&spKekka[lcnt]);
							if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
								sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
								if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
									sFncPutLog (TRCKIND_WARNING , __FILE__,
										"bungaChk", __LINE__,
										EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
									return(RET_CONTINUITY);
								}
								sFncSyslog ( LOG_ERR, "bungaChk()",errMsg ) ;
								ZbmlFree(pKmkmst);
								return(RET_STOP);



							}
						}
					}
					ZbmlFree(spKekka);
				}
				/* ����e�̌��ʃ��R�[�h���쐬����B */
				/* ���ڃR�[�h '0006485'�̕���e���R�[�h�̓C���T�[�g���Ȃ� */
				/* ���ڃR�[�h '0006485'�͕���e�̓��ʏ�������؍s��Ȃ� */
				if(memcmp(pKekka->oyakmkcd,"0006485",7) != 0) {
					memcpy(&sKekka, pKekka, sizeof(Kekka) );
					strncpy(sKekka.kmkcd, sKmkmst.oyakmkcd, 8);
					sKekka.knssu = 1;
					sKekka.knssueda = 0;
					/* �ЂƂ܂��C���T�[�g���A�d���G���[�͖�������B */
					ret = ZdbKekkaInsert2(&sKekka);
					if ((ret != HRC_SQL_NORMAL) && (ret != -803)) {

						sprintf(errMsg,"SQL CODE:%d ZdbKekkaInsert2",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}

						sFncSyslog ( LOG_ERR, "bungaChk()", errMsg ) ;
						ZbmlFree(pKmkmst);
						return(RET_STOP);
					}

					/* �o�^����Ă��郌�R�[�h��ǂݏo���B */
					ret = ZdbKekkaSelectKey(&sKekka, &spKekka, &cntKekka);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
						sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKey",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING , __FILE__, "bungaChk", __LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR,"bungaChk()",errMsg);
						ZbmlFree(pKmkmst);
						return(RET_STOP);
					}
					if (ret != HRC_SQL_NOT_FOUND) {
						spKekka->knsflg 		= 'X';				/* �����t���O */
						spKekka->kkajkcd		= '3';				/* ���ʏ󋵃R�[�h */
						spKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
						spKekka->siyflg 		= '1';				/* �̗p�t���O */

						/* ���͋@�敪����ݒ肷��B */
						strncpy(spKekka->bskkbn, pKekka->bskkbn, sizeof(spKekka->bskkbn)-1);			/* ���͋@�敪 */
						strncpy(spKekka->bsklne, pKekka->bsklne, sizeof(spKekka->bsklne)-1);			/* ���͋@���C�� */
						strncpy(spKekka->bskgok, pKekka->bskgok, sizeof(spKekka->bskgok)-1);			/* ���͋@���@ */
						spKekka->bskseq = pKekka->bskseq;												/* ���͋@�r�d�p */
						strncpy(spKekka->sktdh, pKekka->sktdh, sizeof(spKekka->sktdh)-1);				/* ������� */

						/* �V�K�ɍ쐬�������ʂ̓o�^�`�F�b�N���s���B */
						TourokuChk(spKekka, iKesseiflg);

						spKekka->ctrlno = pKekka->ctrlno;												/* CTRL No */
						strncpy(spKekka->knskka2, "0400", 24);
						strncpy(spKekka->knskka2kbn, "0", 2);
						strncpy(spKekka->hjkka, "*400", 24);
						/* upd 2007-01-16 Nagata �Ɖ�ʂ�"*400" �� �X�y�[�X�ɕύX */
						strncpy(spKekka->skkka, " ", 24);

						spKekka->ijkbnm = ' ';
						spKekka->ijkbnf = ' ';
						spKekka->ijkbnn = ' ';

						ret = ZdbKekkaUpdate(spKekka);
						if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
							sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
							if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
								sFncPutLog (TRCKIND_WARNING, __FILE__, "bungaChk",__LINE__,
									EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
								return(RET_CONTINUITY);
							}
							sFncSyslog ( LOG_ERR, "bungaChk()", errMsg) ;
							ZbmlFree(pKmkmst);
							ZbmlFree(spKekka);
							return(RET_STOP);
						}
						ZbmlFree(spKekka);
					}

				}
			}
			else {
				pKekka->knsflg = 'R';
				pKekka->bunkkuflg = '2';
			}
		}
		ZbmlFree(pKmkmst);
	}

	return 0;
}
/******************************************************************************/
/*	�� �� ��  �FshougoChk() 						*/
/*	�@�\�T�v  �F�ƍ��`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
int shougoChk(Kekka *pKekka, Kenorder *pKenorder, int *iKesseiflg)
{
	Rngchkmst	sRngchkmst;
	Rngchkmst	*pRngchkmst;
	Kekka		sKekka;
	Kekka		*spKekka;
	int 		cnt;
	int 		ret;
	double		rawData;
	double		rawDataZen;
	double		chk;
	int 		flg;
	double		hi_hrng;
	double		hi_lrng;
	char		Hzen_kyoyou;
	double		lo_hrng;
	double		lo_lrng;
	char		Lzen_kyoyou;
	double		et_hrng;
	double		et_lrng;
	char		Ezen_kyoyou;
	double		db_hrng;
	double		db_lrng;
	int 		h_hit;
	int 		l_hit;
	int 		e_hit;
	char		zen_kyoyou;
	char		sKisya[128];
	int 		iKisya;
	char		errMsg[1024] = {0,};

	int		errflg_cnt;

	if (pKekka->knssu == 1) {
		/* �Č��łȂ� */
		return 0;
	}

	if (cntKmkmst == 0) {
		flg = 0;	/* �}�X�^�������̂ŁA����D��ɐݒ� */
	}
	else {
		if (pKmkmst->sgchkflg == '2') {
			flg = 1;
		}
		else {
			flg = 0;
		}
	}

	memcpy(&sKekka, pKekka, sizeof(Kekka) );
	/***
	 ***	�ƍ��`�F�b�N�͌��ʗD��t���O��1:�D�挋�ʂ̃f�[�^�Ɣ�r����
	 ***/
	/* �����񐔂��f�N�������g */
	sKekka.knssu -= 1;
	ret = ZdbKekkaSelectKKAYSN(&sKekka, &spKekka, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKKAYSN",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* �����t���O */
		return(RET_STOP);

	}
	if (ret == HRC_SQL_NOT_FOUND || spKekka->knsflg == 'H') {
		/* �D�挋�ʂ��ۗ��������ꍇ�A�ƍ����|���Ă͂����Ȃ��B */
		/* �ƍ����s�킸�A��荞�ތ��ʂ�������('A')�Ƃ��� */
		pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
		pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
		pKekka->siyflg			= ' ';				/* �̗p�t���O */
		pKekka->knsflg			= 'A';				/* �����t���O */
		/* ���̏�Ԃ����񍐂܂ŋC�Â���Ȃ��ƌ����g���u��������邽�߁A */
		/* �\���t���O�P��"2"���Z�b�g����B */
		/* ���@���������A�\���t���O�P��"2"�͏ƍ��m�f��ʍs������ */
		pKekka->yobiflg01		= '2';				/* �\���t���O�P */
		return 0;
	}
	/* �D�挋�ʂ����ɕ񍐍ς݂������ꍇ�A�����t���O��"M"�ɂ��� */
	if(spKekka->knsflg == 'E'){
		pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
		pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
		pKekka->siyflg			= ' ';				/* �̗p�t���O */
		pKekka->knsflg			= 'M';				/* �����t���O */
		return 0;
	}

	/* �O�񌋉ʂ�tobiflg02��'1'�̏ꍇ���O��A�����rawdata�����ɒl�������Ă���ꍇ */
	if (spKekka->tobiflg02 == '1' && chkRawdata(spKekka->rawdata, pKekka->rawdata)) {
		ret = ZdbXbarmJkflgUpdateZenkai(spKekka, '1'); /* �O��v���b�gNO��XBARM�m��t���O��'1':�m��ς֍X�V */
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
            sprintf(errMsg,"SQL CODE:%d ZdbXbarmJkflgUpdateZenkai",ret);
            if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
                return(RET_CONTINUITY);
            }
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
            return(RET_STOP);
        			
		}
		ZbmlFree(spKekka);
		return 0;
	}

	iKisya = 0;
	memset(sKisya, 0, sizeof(sKisya));
	trim(sKisya, pKekka->jisksbr);
	if( sKisya[0] == '\0' ) {
		iKisya = 1;
	} else {
		if( (pKekka->jisksbr[0] == 'L') || (pKekka->jisksbr[0] == 'B') ) {
			memcpy(sKisya, &pKekka->jisksbr[1], 14);
			iKisya = atoi(sKisya);
		}
	}
	char	sChk[10], sChk1[10];
	memset(sChk, 0, sizeof(sChk));
	memset(sChk1, 0, sizeof(sChk1));
	trim(sChk, spKekka->nbdolbl);
	trim(sChk1, spKekka->ykdolbl);
	if( (sChk[0] != '\0') && (sChk1[0] != '\0') ) {
		*iKesseiflg = 0;
	}
	/* ����A�Č����ʂ̂ǂ��炩�Ƀu�����N�f�[�^�����݂�����m�f�Ƃ��� */
	if( (iKisya != 1) || (pKenorder->ksktkbn == 'K') || (pKenorder->ksktkbn == 'T')
	  || !chkRawdata( spKekka->rawdata, pKekka->rawdata ) ) {
		/* �Č��I�[�_�[�E�ǉ��Č��I�[�_�[�̂Ƃ��͏ƍ�NG�ɂ���B */
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* �����t���O */
		spKekka->syougoflg = '2';
		spKekka->knsflg = 'A';				/* �����t���O */
		/* ADD E.Osada �ƍ�NG�̏ꍇ�͗\���t���O�O�P��'2'�ɂ��� */
		pKekka->yobiflg01 = '2';
		spKekka->yobiflg01 = '2';
		if (flg == 1) { 					/* �Č��D�� */
			pKekka->kkajkcd 		= '3';				/* ���ʏ󋵃R�[�h */
			pKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
			pKekka->siyflg			= '1';				/* �̗p�t���O */
			spKekka->kkajkcd		= '1';				/* ���ʏ󋵃R�[�h */
			spKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
			spKekka->siyflg 		= ' ';				/* �̗p�t���O */
		}
		else {								/* ����D�� */
			pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
			pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
			pKekka->siyflg			= ' ';				/* �̗p�t���O */
			spKekka->kkajkcd		= '3';				/* ���ʏ󋵃R�[�h */
			spKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
			spKekka->siyflg 		= '1';				/* �̗p�t���O */
		}
		ret = ZdbKekkaUpdate(spKekka);
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			return(RET_STOP);

		}
		ZbmlFree(spKekka);
		return 0;
	}

	/* �O�񌋉ʂ̍Č��t���O�ő��ցE����E�P�O�O���̂����ꂩ���m�f��������ƍ��m�f�Ƃ��� */
	if ( (spKekka->soukn1flg == '2') || (spKekka->bunkkuflg == '2') ||
		 (spKekka->per100flg == '2') || (spKekka->soukn2flg == '2') ) {
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* �����t���O */
		spKekka->syougoflg = '2';
		spKekka->knsflg = 'A';				/* �����t���O */
		pKekka->yobiflg01 = '2';
		spKekka->yobiflg01 = '2';
		if (flg == 1) { 					/* �Č��D�� */
			pKekka->kkajkcd 		= '3';				/* ���ʏ󋵃R�[�h */
			pKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
			pKekka->siyflg			= '1';				/* �̗p�t���O */
			spKekka->kkajkcd		= '1';				/* ���ʏ󋵃R�[�h */
			spKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
			spKekka->siyflg 		= ' ';				/* �̗p�t���O */
		}
		else {								/* ����D�� */
			pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
			pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
			pKekka->siyflg			= ' ';				/* �̗p�t���O */
			spKekka->kkajkcd		= '3';				/* ���ʏ󋵃R�[�h */
			spKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
			spKekka->siyflg 		= '1';				/* �̗p�t���O */
		}
		ret = ZdbKekkaUpdate(spKekka);
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			return(RET_STOP);
		}
		ZbmlFree(spKekka);
		return 0;
	}

	/* �Č����ʂɕ��͋@�G���[�����݂����ꍇ�̏�����ǉ� */
	if( (strcmp(pKekka->bskerrsts, " ") != 0) && (strcmp(pKekka->bskerrsts, "0") != 0) ){
		/* �G���[�R�[�h 3,47,72 �̏ꍇ�͏ƍ��m�f�Ƃ���B�Č��ɂ͉񂳂��A��ʂŗp��Ń`�F�b�N */
		for(errflg_cnt=0; errflg_cnt < errsts_ng_cnt ;errflg_cnt++){
			if(strcmp(pKekka->bskerrsts, errsts_ng[errflg_cnt]) == 0){
				pKekka->syougoflg = '2';
				pKekka->knsflg  = 'A';              /* �����t���O */
				spKekka->syougoflg = '2';
				spKekka->knsflg = 'A';              /* �����t���O */
				pKekka->yobiflg01 = '2';
				spKekka->yobiflg01 = '2';

				if (flg == 1) {                     /* �Č��D�� */
					pKekka->kkajkcd         = '3';              /* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg       = '1';              /* ���ʗD��t���O */
					pKekka->siyflg          = '1';              /* �̗p�t���O */
					spKekka->kkajkcd        = '1';              /* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg      = ' ';              /* ���ʗD��t���O */
					spKekka->siyflg         = ' ';              /* �̗p�t���O */
				}
				else {                              /* ����D�� */
					pKekka->kkajkcd         = '1';              /* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg       = ' ';              /* ���ʗD��t���O */
					pKekka->siyflg          = ' ';              /* �̗p�t���O */
					spKekka->kkajkcd        = '3';              /* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg      = '1';              /* ���ʗD��t���O */
					spKekka->siyflg         = '1';              /* �̗p�t���O */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);
				}
				ZbmlFree(spKekka);
				return 0;
			}
		}
		
		/* ��L�ȊO�Ŏw�肳�ꂽ�G���[�R�[�h�Ɋւ��ẮA�ƍ��G���[�ɂ��āA�p��Č��ɉ� */
		for(errflg_cnt=0; errflg_cnt < errsts_sai_cnt ;errflg_cnt++){
			if(strcmp(pKekka->bskerrsts, errsts_sai[errflg_cnt]) == 0) {
				pKekka->syougoflg = '2';
				pKekka->knsflg  = 'R';              /* �����t���O */
				spKekka->syougoflg = '2';
				spKekka->knsflg = 'R';              /* �����t���O */

				if (flg == 1) {                     /* �Č��D�� */
					pKekka->kkajkcd         = '3';              /* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg       = '1';              /* ���ʗD��t���O */
					pKekka->siyflg          = '1';              /* �̗p�t���O */
					spKekka->kkajkcd        = '1';              /* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg      = ' ';              /* ���ʗD��t���O */
					spKekka->siyflg         = ' ';              /* �̗p�t���O */
				}
				else {                              /* ����D�� */
					pKekka->kkajkcd         = '1';              /* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg       = ' ';              /* ���ʗD��t���O */
					pKekka->siyflg          = ' ';              /* �̗p�t���O */
					spKekka->kkajkcd        = '3';              /* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg      = '1';              /* ���ʗD��t���O */
					spKekka->siyflg         = '1';              /* �̗p�t���O */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);
				}
				ZbmlFree(spKekka);
				return 0;
			}
		}
    }

	/* �O��l�̌����l���擾����B */
	rawDataZen = atof(spKekka->rawdata);

	memset(&sRngchkmst, 0, sizeof(Rngchkmst));
	sRngchkmst.hnikbn = SYOGO_CHK;
	strncpy(sRngchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sRngchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
	if ((strncmp(pKenorder->zrcd, "001", 3) == 0) || (strncmp(pKenorder->zrcd, "002", 3) == 0)) {
		strncpy(sRngchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sRngchkmst.zaicd, "000 ", 4);
	}
	sRngchkmst.sbt = pKenorder->sbtkbn;
	ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
		ZbmlFree(spKekka);
		pKekka->syougoflg = '2';
		pKekka->knsflg	= 'A';				/* �����t���O */
		return(RET_STOP);

	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, pKekka->sstcd, 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}

			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			pKekka->syougoflg = '2';
			pKekka->knsflg	= 'A';				/* �����t���O */
			return(RET_STOP);
		}
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = pKenorder->sbtkbn;
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			pKekka->syougoflg = '2';
			pKekka->knsflg	= 'A';				/* �����t���O */
			return(RET_STOP);

		}
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sRngchkmst.sstcd, "0000000", 7);
		sRngchkmst.sbt = ' ';
		ret = ZdbRngchkmstSelectHnikbn(pKekka->knskisymd, &sRngchkmst, &pRngchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbRngchkmstSelectHnikbn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			pKekka->syougoflg = '2';
			pKekka->knsflg  = 'A';              /* �����t���O */
			return(RET_STOP);

		}
	}
	if (ret != HRC_SQL_NOT_FOUND) {
		int 	lCnt;
		int 	cFlg = 0;
		h_hit = l_hit = e_hit = 0;
		rawData = atof(pKekka->rawdata);
		for (lCnt = 0; lCnt < cnt; lCnt++) {
			switch(pRngchkmst[lCnt].ssa) {
				case '1':
					hi_hrng = atof(pRngchkmst[lCnt].hrng);
					hi_lrng = atof(pRngchkmst[lCnt].lrng);
					Hzen_kyoyou = pRngchkmst[lCnt].zen_kyoyou;
					h_hit =1;
					break;
				case '2':
					lo_hrng = atof(pRngchkmst[lCnt].hrng);
					lo_lrng = atof(pRngchkmst[lCnt].lrng);
					Lzen_kyoyou = pRngchkmst[lCnt].zen_kyoyou;
					l_hit = 1;
					break;
				case '3':
					et_hrng = atof(pRngchkmst[lCnt].hrng);
					et_lrng = atof(pRngchkmst[lCnt].lrng);
					Ezen_kyoyou = pRngchkmst[lCnt].zen_kyoyou;
					e_hit = 1;
					break;
			}
		}
		cFlg = 1;
		if( spKekka->renjicflg == '3' && h_hit ) {
			db_hrng = hi_hrng;
			db_lrng = hi_lrng;
			zen_kyoyou = Hzen_kyoyou;
		} else if( spKekka->renjicflg == '4' && l_hit ) {
			db_hrng = lo_hrng;
			db_lrng = lo_lrng;
			zen_kyoyou = Lzen_kyoyou;
		} else if( spKekka->renjicflg != '3' && spKekka->renjicflg != '4'  &&
					e_hit ) {
			db_hrng = et_hrng;
			db_lrng = et_lrng;
			zen_kyoyou = Ezen_kyoyou;
		} else if( l_hit ) {
			db_hrng = lo_hrng;
			db_lrng = lo_lrng;
			zen_kyoyou = Lzen_kyoyou;
		} else {
			cFlg = 0;
		}
		if( cFlg ) {
			if (zen_kyoyou == '1') { /* % */
				chk = rawData / rawDataZen * 100;
			}
			else if (zen_kyoyou == '2') { /* �� */
				chk = fabs(rawDataZen - rawData);
			}
			else {
				chk = rawData;
			}
			if( ((rawData >= 0) || (rawDataZen >= 0)) && (db_hrng >= chk) &&
				(chk >= db_lrng) ) {
				pKekka->syougoflg = '1';
				spKekka->syougoflg = '1';
				/* kkacmt1�ɂ����ɓ����Ă���ꍇ��cmnt2�Ɉڍs���A"0101"��CMNT1�ɓ���� */
				if( pKekka->renjicflg > '1' ) {
					if( (pKekka->kkacmt1[0] == '\0') || (pKekka->kkacmt1[0] == ' ') ) {
						strncpy(pKekka->kkacmt1, "0101", 4);
					} else {
						if( memcmp(pKekka->kkacmt1, "0101", 4) ) {
							if( (pKekka->kkacmt2[0] == '\0') || (pKekka->kkacmt2[0] == ' ') ) {
								strncpy(pKekka->kkacmt2, "0101", 4);
							}
						}
					}
				}

				if( spKekka->renjicflg > '1' ) {
					if( (spKekka->kkacmt1[0] == '\0') || (spKekka->kkacmt1[0] == ' ') ) {
						strncpy(spKekka->kkacmt1, "0101", 4);
					} else {
						if( memcmp(spKekka->kkacmt1, "0101", 4) ) {
							if( (spKekka->kkacmt2[0] == '\0') || (spKekka->kkacmt2[0] == ' ') ) {
								strncpy(spKekka->kkacmt2, "0101", 4);
							}
						}
					}
				}
				/* ��F�����Ă��Ȃ�(�d�����̂�)�ꍇ�� 'H' */
				if( *iKesseiflg ) {
					pKekka->knsflg			= 'X';				/* �����t���O */
					spKekka->knsflg 		= 'H';				/* �����t���O */
				} else {
					pKekka->knsflg			= 'X';				/* �����t���O */
					spKekka->knsflg 		= 'X';				/* �����t���O */
				}
				if (flg == 1) {								/* �Č��D�� */
					pKekka->kkajkcd 		= '3';				/* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
					pKekka->siyflg			= '1';				/* �̗p�t���O */
					spKekka->kkajkcd		= '1';				/* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
					spKekka->siyflg 		= ' ';				/* �̗p�t���O */
				}
				else {									/* ����D�� */
					pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
					pKekka->siyflg			= ' ';				/* �̗p�t���O */
					spKekka->kkajkcd		= '3';				/* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
					spKekka->siyflg 		= '1';				/* �̗p�t���O */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);

				}
			}
			else {
				/* �ƍ�NG�͍Č��ΏۂƂ��� */
				pKekka->syougoflg = '2';
				pKekka->knsflg	= 'R';				// �����t���O
				spKekka->syougoflg = '2';
				spKekka->knsflg = 'R';				// �����t���O
				if (flg == 1) { 					/* �Č��D�� */
					pKekka->kkajkcd 		= '3';				/* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
					pKekka->siyflg			= '1';				/* �̗p�t���O */
					spKekka->kkajkcd		= '1';				/* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
					spKekka->siyflg 		= ' ';				/* �̗p�t���O */
				}
				else {								/* ����D�� */
					pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
					pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
					pKekka->siyflg			= ' ';				/* �̗p�t���O */
					spKekka->kkajkcd		= '3';				/* ���ʏ󋵃R�[�h */
					spKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
					spKekka->siyflg 		= '1';				/* �̗p�t���O */
				}
				ret = ZdbKekkaUpdate(spKekka);
				if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
					return(RET_STOP);
				}
			}
		}
		if (cFlg == 0) {
			/* �����W�Ȃǃt���O���ݒ肳��Ă��Ȃ����߁A�`�F�b�N�ł��Ȃ��B */
			/* ���̂��߁A�ƍ��G���[�Ƃ���B */
			if (flg == 1) { 					/* �Č��D�� */
				pKekka->kkajkcd 		= '3';				/* ���ʏ󋵃R�[�h */
				pKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
				pKekka->siyflg			= '1';				/* �̗p�t���O */
				spKekka->kkajkcd		= '1';				/* ���ʏ󋵃R�[�h */
				spKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
				spKekka->siyflg 		= ' ';				/* �̗p�t���O */
			}
			else {								/* ����D�� */
				pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
				pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
				pKekka->siyflg			= ' ';				/* �̗p�t���O */
				spKekka->kkajkcd		= '3';				/* ���ʏ󋵃R�[�h */
				spKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
				spKekka->siyflg 		= '1';				/* �̗p�t���O */
			}
			/* CHG E.Osada �}�X�^�ɂȂ��ꍇ�̓`�F�b�N�K�v�Ȃ��@����ɂ��� */
			pKekka->syougoflg		= '1';
			spKekka->syougoflg		= '1';
			if( *iKesseiflg ) {
				pKekka->knsflg			= 'X';				/* �����t���O */
				spKekka->knsflg 		= 'H';				/* �����t���O */
			} else {
				pKekka->knsflg			= 'X';				/* �����t���O */
				spKekka->knsflg 		= 'X';				/* �����t���O */
			}
			if( pKekka->renjicflg > '1' ) {
				if( (pKekka->kkacmt1[0] == '\0') || (pKekka->kkacmt1[0] == ' ') ) {
					strncpy(pKekka->kkacmt1, "0101", 4);
				} else {
					if( memcmp(pKekka->kkacmt1, "0101", 4) ) {
						if( (pKekka->kkacmt2[0] == '\0') || (pKekka->kkacmt2[0] == ' ') ) {
							strncpy(pKekka->kkacmt2, "0101", 4);
						}
					}
				}
			}
			if( spKekka->renjicflg > '1' ) {
				if( (spKekka->kkacmt1[0] == '\0') || (spKekka->kkacmt1[0] == ' ') ) {
					strncpy(spKekka->kkacmt1, "0101", 4);
				} else {
					if( memcmp(spKekka->kkacmt1, "0101", 4) ) {
						if( (spKekka->kkacmt2[0] == '\0') || (spKekka->kkacmt2[0] == ' ') ) {
							strncpy(spKekka->kkacmt2, "0101", 4);
						}
					}
				}
			}
			ret = ZdbKekkaUpdate(spKekka);
			if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
				sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
				return(RET_STOP);
			}
		}
	} else {
		/* �����W�`�F�b�N�Ƀ��R�[�h���̑��݂��Ȃ��ꍇ�̑Ή� */
		if (flg == 1) { 					/* �Č��D�� */
			pKekka->kkajkcd 		= '3';				/* ���ʏ󋵃R�[�h */
			pKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
			pKekka->siyflg			= '1';				/* �̗p�t���O */
			spKekka->kkajkcd		= '1';				/* ���ʏ󋵃R�[�h */
			spKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
			spKekka->siyflg 		= ' ';				/* �̗p�t���O */
		}
		else {								/* ����D�� */
			pKekka->kkajkcd 		= '1';				/* ���ʏ󋵃R�[�h */
			pKekka->kkaysnflg		= ' ';				/* ���ʗD��t���O */
			pKekka->siyflg			= ' ';				/* �̗p�t���O */
			spKekka->kkajkcd		= '3';				/* ���ʏ󋵃R�[�h */
			spKekka->kkaysnflg		= '1';				/* ���ʗD��t���O */
			spKekka->siyflg 		= '1';				/* �̗p�t���O */
		}
		/* �}�X�^�ɂȂ��ꍇ�̓`�F�b�N�K�v�Ȃ��@����ɂ��� */
		pKekka->syougoflg		= '1';
		spKekka->syougoflg		= '1';
		if( *iKesseiflg ) {
			pKekka->knsflg			= 'X';				/* �����t���O */
			spKekka->knsflg 		= 'H';				/* �����t���O */
		} else {
			pKekka->knsflg			= 'X';				/* �����t���O */
			spKekka->knsflg 		= 'X';				/* �����t���O */
		}
		if( pKekka->renjicflg > '1' ) {
			if( (pKekka->kkacmt1[0] == '\0') || (pKekka->kkacmt1[0] == ' ') ) {
				strncpy(pKekka->kkacmt1, "0101", 4);
			} else {
				if( memcmp(pKekka->kkacmt1, "0101", 4) ) {
					if( (pKekka->kkacmt2[0] == '\0') || (pKekka->kkacmt2[0] == ' ') ) {
						strncpy(pKekka->kkacmt2, "0101", 4);
					}
				}
			}
		}
		if( spKekka->renjicflg > '1' ) {
			if( (spKekka->kkacmt1[0] == '\0') || (spKekka->kkacmt1[0] == ' ') ) {
				strncpy(spKekka->kkacmt1, "0101", 4);
			} else {
				if( memcmp(spKekka->kkacmt1, "0101", 4) ) {
					if( (spKekka->kkacmt2[0] == '\0') || (spKekka->kkacmt2[0] == ' ') ) {
						strncpy(spKekka->kkacmt2, "0101", 4);
					}
				}
			}
		}
		ret = ZdbKekkaUpdate(spKekka);
		if (ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "shougoChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "shougoChk()", errMsg ) ;
			return(RET_STOP);

		}
	}

	ZbmlFree(spKekka);
	ZbmlFree(pRngchkmst);
	return 0;
}
/******************************************************************************/
/*	�� �� ��  �FsoukanChk() 						*/
/*	�@�\�T�v  �F���փ`�F�b�N(WS��)						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FpKekka	���ʏ��					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*			 0	����						*/
/*			-1	�ُ�						*/
/******************************************************************************/
int soukanChk(Kekka *pKekka, Kenorder *pKenorder)
{
	char		calBuff[256];
	Skchkmst	sSkchkmst;
	Skchkmst	*pSkchkmst;
	int 		cnt;
	int 		ret;
	double		rawData;
	Kmkmst		lKmkmst;
	Kmkmst		*plKmkmst;
	int 		iCnt;	/* ���[�v�J�E���^ */
	int 		setCnt;
	int 		tmpCnt;
	char		tmp[32];
	double		calNum;
	char		errMsg[1024] = {0,};

	char *pszExpandKSNSK = (char *) NULL; /* IF ���W�J��̌v�Z��              */
	double dTransferLimit;

	memset(&sSkchkmst, 0, sizeof(sSkchkmst));
	strncpy(sSkchkmst.knsgrp, pKekka->knsgrp, 16);
	strncpy(sSkchkmst.kmkcd, pKekka->kmkcd, 7);
	strncpy(sSkchkmst.sstcd, pKekka->sstcd, 7);
	if((strncmp(pKenorder->zrcd,"001",3)==0)||(strncmp(pKenorder->zrcd,"002",3) == 0)) {
		strncpy(sSkchkmst.zaicd, pKenorder->zrcd, 4);
	}
	else {
		strncpy(sSkchkmst.zaicd, "000 ", 4);
	}
	ret = ZdbSkchkmstSelectKey(&sSkchkmst, &pSkchkmst, &cnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {

		sprintf(errMsg,"SQL CODE:%d ZdbSkchkmstSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
		return (RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		strncpy(sSkchkmst.sstcd, "0000000", 7);
		ret = ZdbSkchkmstSelectKey(&sSkchkmst, &pSkchkmst, &cnt);
		if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
			sprintf(errMsg,"SQL CODE:%d ZdbSkchkmstSelectKey",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
			return (RET_STOP);
		}

		if(ret == HRC_SQL_NOT_FOUND){
			pKekka->soukn2flg = '1';
			if( pKekka->soukn1flg == '0' ) {
				pKekka->soukn1flg = '1';
			}
			return(RET_CONTINUITY);
		}
	}


	/* �����̍��ڃR�[�h�𐔒l�ɒu��������B */
	memset(calBuff, 0, sizeof(calBuff));
	for (iCnt = 0, setCnt = 0; iCnt < 128; iCnt++ ) {
		/* ���ڃR�[�h�̎n�܂�'['����������B */
		if (pSkchkmst->soukan[iCnt] = '[') {
			/* ���ڒl������ */
			memset(tmp, 0, sizeof(tmp));
			tmpCnt = 0;
			iCnt++;
			/* ���ڃR�[�h��]���i�I���ʒu��]��Null�܂Łj */
			while (pSkchkmst->soukan[iCnt] != ']' && pSkchkmst->soukan[iCnt] != '\0') {
				tmp[tmpCnt++] = pSkchkmst->soukan[iCnt++];
			}
			/* ���ʏ�񂩂�w��̍��ڃR�[�h���������A�u��������B */
			memset(&lKmkmst, 0, sizeof(lKmkmst));
			strncpy(lKmkmst.kmkcd, tmp, 7);
			ret = ZdbKmkmstSelectCD(&lKmkmst, &plKmkmst, &cnt);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				sprintf(errMsg,"SQL CODE:%d ZdbKmkmstSelectCD",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}

				sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
				return (RET_STOP);
			}
			if (ret != HRC_SQL_NOT_FOUND) {
				if (plKmkmst->kmksbt == '3') {
					Soukan		sSoukan;
					Soukan		*pSoukan;
					int 		cntSoukan;

					memset(&sSoukan, 0, sizeof(sSoukan));
					strncpy(sSoukan.utkymd, pKekka->utkymd, 11);
					strncpy(sSoukan.irino, pKekka->irino, 11);
					sSoukan.zssdino = pKekka->zssdino;
					strncpy(sSoukan.knsgrp, pKekka->knsgrp, 16);
					strncpy(sSoukan.kmkcd, pKekka->kmkcd, 7);
					ret = ZdbSoukanSelectKey(&sSoukan, &pSoukan, &cntSoukan);
					if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
						sprintf(errMsg,"SQL CODE:%d ZdbSoukanSelectKey",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING, __FILE__, "soukanChk",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "soukanChk()", errMsg ) ;
						ZbmlFree(plKmkmst);
						return (RET_STOP);
					}
					if (ret == HRC_SQL_NOT_FOUND) {
						pKekka->soukn2flg = '1';
						if( pKekka->soukn1flg == '0' ) {
							pKekka->soukn1flg = '1';
						}
						ZbmlFree(plKmkmst);
						return 0;
					}
					strncat(calBuff, pSoukan->rawdata, 21);
					setCnt = strlen(calBuff);
					ZbmlFree(pSoukan);
				}
				else {
					/* WS�Ԃ̑��֏��Ŗ����̂ŏ������Ȃ� */
					pKekka->soukn2flg = '1';
					if( pKekka->soukn1flg == '0' ) {
						pKekka->soukn1flg = '1';
					}
					ZbmlFree(plKmkmst);
					return 0;
				}
				ZbmlFree(plKmkmst);
			}
			else {
				pKekka->soukn2flg = '1';
				if( pKekka->soukn1flg == '0' ) {
					pKekka->soukn1flg = '1';
				}
				return 0;
			}
		}
		else if (KSNSK_SC == (int) pSkchkmst->soukan[iCnt]) {
			/* �g�� */
			/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ��� */
			memcpy((void *) gszTransfer, pKenorder->sc, FLDSIZE_SC);
			gszTransfer[FLDSIZE_SC] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);
		}
		else if (KSNSK_TJ == (int) pSkchkmst->soukan[iCnt]) {
			/* POW�Ƌ�ʂ��邽�߁A�O�̕�����O�Ŗ������`�F�b�N����B */
			if (pSkchkmst->soukan[iCnt-1] != 'o' || pSkchkmst->soukan[iCnt-1] != 'O') {
				/* �̏d */
				/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ��� */
				strncpy(gszTransfer, pKenorder->tj, FLDSIZE_TJ);
				gszTransfer[FLDSIZE_TJ] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				else {
					switch ((int) pKenorder->tjtni) {
					case _VALUE_TJTNI_KILLOGRAM:
						dTransferLimit = 
								atof(gszTransfer) * (double) 1000.0;
						if ((double) 0.0 < dTransferLimit &&
								(double) 100000.0 > dTransferLimit) {
							sprintf(gszTransfer, "%-lf", dTransferLimit);
							gszTransfer[FLDSIZE_TJ] = (char) '\0';
						}
						else {
							gszTransfer[0] = (char) '0';
							gszTransfer[1] = (char) '\0';
						}

					case _VALUE_TJTNI_GRAM:
						break;		/* NOP */
					default:
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (KSNSK_TNTME == (int) pSkchkmst->soukan[iCnt]) {
			/* �~�A���� */
			/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ��� */
			memcpy((void *) gszTransfer, pKenorder->sstme, FLDSIZE_TNTME);
			gszTransfer[FLDSIZE_TNTME] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);

		}
		else if (KSNSK_TNRYO == (int) pSkchkmst->soukan[iCnt]) {
			/* �~�A�� */
			/* ���p�\�Ȓl�ȊO���w�肳��Ă����ꍇ�A�l 0 ���w�肳�ꂽ���̂Ƃ��� */
			memcpy((void *) gszTransfer, pKenorder->tnryo, FLDSIZE_TNRYO);
			gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
			if (0 == _isnumeric(gszTransfer)) {
				gszTransfer[0] = (char) '0';
				gszTransfer[1] = (char) '\0';
			}
			else {
				switch ((int) pKenorder->tnryotni) {
				case _VALUE_TNRYO_LITER:
					dTransferLimit = atof(gszTransfer) * (double) 1000.0;
					if ((double) 0.0 < dTransferLimit &&
							(double) 100000.0 > dTransferLimit) {
						sprintf(gszTransfer, "%-lf", dTransferLimit);
						gszTransfer[FLDSIZE_TNRYO] = (char) '\0';
					}
					else {
						gszTransfer[0] = (char) '0';
						gszTransfer[1] = (char) '\0';
					}

				case _VALUE_TNRYO_MILLILITER:
					break;

				default:
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
			}
			strcat(calBuff, gszTransfer);
			setCnt = strlen(calBuff);

		}

		/* �v�Z���g���Ή� */
		else if (KSNSK_SBTKBN == (int) pSkchkmst->soukan[iCnt]) {
			/* ���ʋ敪 */
			if (_VALUE_SBTKBN_MALE == (int) pKenorder->sbtkbn ||
					_VALUE_SBTKBN_FEMALE == (int) pKenorder->sbtkbn) {
				strncat(calBuff, &(pKenorder->sbtkbn), sizeof(pKenorder->sbtkbn));
				setCnt = strlen(calBuff);
			}
			else {
				calBuff[setCnt++] = (char) _VALUE_SBTKBN_UNKNOWN;
				calBuff[setCnt] = (char) '\0';
				/* �W�J�s�� */
			}
		}
		else if (KSNSK_AGE == (int) pSkchkmst->soukan[iCnt]) {
			/* �N�� */
			if (_VALUE_AGEKBN_YEAR != (int) pKenorder->agekbn) {
				calBuff[setCnt++] = (char) '0';
				calBuff[setCnt] = (char) '\0';
				/* �W�J�s�� */
			}
			else {
				memcpy((void *) gszTransfer, pKenorder->age, FLDSIZE_AGE);
				gszTransfer[FLDSIZE_AGE] = (char) '\0';
				if (0 == _isnumeric(gszTransfer)) {
					gszTransfer[0] = (char) '0';
					gszTransfer[1] = (char) '\0';
				}
				strcat(calBuff, gszTransfer);
				setCnt = strlen(calBuff);
			}
		}
		else if (pSkchkmst->soukan[iCnt] = '\0') {
			break;
		}
		else {
			calBuff[setCnt++] = pSkchkmst->soukan[iCnt];
		}
	}

	/* �v�Z���Ɋ܂܂�� IF ���̓W�J */

	if (NULL != (void *) (pszExpandKSNSK = OperateKSNSK(calBuff))) {
		if ('\0' != (int) *pszExpandKSNSK) {
			strcpy(calBuff, pszExpandKSNSK);
		}
		free((void *) pszExpandKSNSK);
		pszExpandKSNSK = (char *) NULL;
	}


	/* ������̌v�Z�����v�Z����B */
	calNum = StringCal(calBuff);

	/* �s�����̐ݒ�ɏ]���A�l�𔻒肷��B */
	rawData = atof(pKekka->knskka1);
	switch (pSkchkmst->krknsgrp[0]) {
	case 0: /* = */
		if (rawData == calNum) {
			ret = 1;
		}
		break;
	case 1: /* != */
		if (rawData != calNum) {
			ret = 1;
		}
		break;
	case 2: /* >= */
		if (rawData >= calNum) {
			ret = 1;
		}
		break;
	case 3: /* <= */
		if (rawData <= calNum) {
			ret = 1;
		}
		break;
	case 4: /* > */
		if (rawData > calNum) {
			ret = 1;
		}
		break;
	case 5: /* < */
		if (rawData < calNum) {
			ret = 1;
		}
		break;
	}

	if (ret != 0) {
		pKekka->soukn2flg = '2';
		if( pKekka->soukn1flg == '0' ) {
			pKekka->soukn1flg = '2';
		}
	}
	else {
		pKekka->soukn2flg = '1';
		if( pKekka->soukn1flg == '0' ) {
			pKekka->soukn1flg = '1';
		}
	}

	ZbmlFree(pSkchkmst);
	return 0;
}
/******************************************************************************/
/*	�� �� ��  �FStringCal_sub() 						*/
/*	�@�\�T�v  �F�w�肳�ꂽ���Z�q�ƒl�Ŏl�����Z�s��				*/
/*	��	  ��  �F							*/
/*	 ��P���� �Fenzan	:	���Z�q					*/
/*	 ��Q���� �Fval1	:	�l�P					*/
/*	 ��R���� �Fval2	:	�l�Q					*/
/*	�o	  ��  �F							*/
/*	���A���  �Fdouble	�v�Z����					*/
/******************************************************************************/
double StringCal_sub(char enzan,double val1,double val2)
{
	switch ( enzan ) {
	case '+':
		return (val1 + val2);
		break;
	case '-':
		return (val1 - val2);
		break;
	case '/':
		if (val2 == 0.0) {
			return 0;
		}
		return (val1 / val2);
		break;
	case '*':
		return (val1 * val2);
		break;
	}
	return 0;
}

/******************************************************************************/
/*	�� �� ��  �FStringCal() 						*/
/*	�@�\�T�v  �F�n���ꂽ������̌v�Z�����s��				*/
/*	��	  ��  �F							*/
/*	 ��P���� �FCalStr	:	�v�Z������				*/
/*	�o	  ��  �F							*/
/*	���A���  �Fdouble	�v�Z����					*/
/*										*/
/*	���ӁF	�Ή����鉉�Z�q�́u+ - / *�v���\�ł���B			*/
/*		����ȊO��LOG�ALOG10�APOW��3�̌v�Z���s���B			*/
/*		�v�Z�̗D�揇�ʂ́A�l�����Z�̗D�揇�ʂɏ]��*��/���D�悳���B	*/
/******************************************************************************/
double StringCal(char *CalStr)
{
	char		StacEn;
	double		StacNum;
	int 		flg;
	int 		loopCnt, strCnt;
	double		ret;
	char		cStacNum[32];
	char		cStacNum2[32];
	char		cChk[16];
	int 		i, c;
	double		StacRet[10];
	char		StacEnc[10];
	char		StacFlg[10];
	int 		StacCnt;

	ret = 0.0;
	StacEn = '+';
	flg = FALSE;
	strCnt = 0;
	StacCnt = 0;
	for(loopCnt = 0; loopCnt < strlen(CalStr); loopCnt ++) {
		switch (CalStr[loopCnt]) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
			/* ���l�̎� */
			break;
		case '+': case '-': case '/': case '*':
			/* ���Z�q�̎� */
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

			if ((StacEn == '+' || StacEn == '-') && (CalStr[loopCnt] == '*' || CalStr[loopCnt] == '/')) {
				StacFlg[StacCnt] = StacEn;
				StacRet[StacCnt] = ret;
				StacEnc[StacCnt] = StacEn;
				StacCnt += 1;

				flg = FALSE;
				ret = StacNum;
				StacEn = CalStr[loopCnt];
				strCnt = loopCnt + 1;
			}
			else if ((StacEn == '*' || StacEn == '/') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else if ((StacCnt > 0) && (StacEnc[StacCnt-1] == '+' || StacEnc[StacCnt-1] == '-') &&
					 (StacFlg[StacCnt-1] != '(') && (CalStr[loopCnt] == '+' || CalStr[loopCnt] == '-')) {
				ret = StringCal_sub(StacEnc[StacCnt-1], StacRet[StacCnt-1], ret);
				StacCnt -= 1;
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}
			else {
				ret = StringCal_sub(StacEn, ret, StacNum);
				flg = FALSE;
				StacEn = CalStr[loopCnt];
			}

			strCnt = loopCnt + 1;
			break;
		case 'L': case 'l':
			/* LOG�y��LOG10�̎� */
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk , "LOG10") == 0) {
				for (c = 0, i = loopCnt + 6; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = log10(atof(cStacNum));
				flg = TRUE;
				loopCnt += i;
			}
			else if (strcmp(cChk , "LOG") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				StacNum = atof(cStacNum);
				StacNum = log(StacNum);
				flg = TRUE;
				loopCnt += i;
			}
			break;
		case 'P': case 'p':
			/* POW�̎� */
			for (c = 0, i = loopCnt; CalStr[i] != '(' && CalStr[i] != '\0'; c++, i++) {
				cChk[c] = toupper(CalStr[i]);
			}
			cChk[c] = '\0';
			if (strcmp(cChk, "POW") == 0) {
				for (c = 0, i = loopCnt + 4; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum[c] = CalStr[i];
				}
				cStacNum[c] = '\0';
				for (c = 0, i += 1; CalStr[i] != ':' && CalStr[i] != ')' && CalStr[i] != '\0'; c++, i++) {
					cStacNum2[c] = CalStr[i];
				}
				cStacNum2[c] = '\0';
				StacNum = pow(atof(cStacNum), atof(cStacNum2));
				flg = TRUE;
				loopCnt = i;
			}
			break;
		case '(':
			StacFlg[StacCnt] = '(';
			StacRet[StacCnt] = ret;
			StacEnc[StacCnt] = StacEn;
			StacCnt++;
			ret = 0.0;
			StacEn = '+';
			strCnt = loopCnt + 1;
			break;
		case ')':
			if (flg == FALSE) {
				if (strCnt >= loopCnt) {
					StacNum = 0.0;
				}
				else {
					for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
						cStacNum[c] = CalStr[i];
					}
					cStacNum[c] = '\0';
					StacNum = atof(cStacNum);
				}
			}

			StacNum = StringCal_sub(StacEn, ret, StacNum);
			flg = TRUE;

			StacCnt--;
			StacEn = StacEnc[StacCnt];
			ret = StacRet[StacCnt];
			strCnt = loopCnt + 1;
			break;
		}
	}
	if (flg == FALSE) {
		for (c = 0, i = strCnt; i < loopCnt; c++, i++) {
			cStacNum[c] = CalStr[i];
		}
		cStacNum[c] = '\0';
		StacNum = atof(cStacNum);
	}
	ret = StringCal_sub(StacEn, ret, StacNum);
	if (StacCnt > 0) {
		while (StacCnt > 0) {
			StacCnt -= 1;
			StacEn = StacEnc[StacCnt];
			StacNum = StacRet[StacCnt];
			ret = StringCal_sub(StacEn, StacNum, ret);
		}
	}
	return ret;
}

void LogFileOut(char * msg)
{
	FILE *fp;

	struct tm* tm;
	struct timeval tv;
	char cWrk[16];
	gettimeofday( &tv, NULL );
	sprintf( cWrk, "%06ld", tv.tv_usec );
	tm = localtime(&tv.tv_sec);
	sprintf(gFileMsgBuff, "%04d/%02d/%02d %02d:%02d:%02d.%c%c%c %s",
					tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
					tm->tm_hour, tm->tm_min, tm->tm_sec,
					cWrk[0], cWrk[1], cWrk[2],
					msg);

	if (gLogFile[0] == 0) return;

	fp = fopen(gLogFile,"a");
	if( fp == NULL ) {
		return;
	}
	fprintf(fp,"%s\n", gFileMsgBuff);
	fclose(fp);
}
int kanrenChk(Kekka *pKekka, int iTcnt, int iCrcnt)
{
	int i, iCnt, iKcnt, iKhit;
	Kekka *pKkaYkrn = NULL;
	Kekka wKekka;
	char		errMsg[1024] = {0,};
	int ret;

	for( iCnt=0; iCnt < gKrkCnt ;++iCnt ) {
		iKhit = 0;
		/* 1.�����̊֘A���ڃR�[�h���擾 */
		if( memcmp((gKrkmkmst+iCnt)->kmkcd, pKekka[iCrcnt].kmkcd, 7) )
			continue;

		/* 2.�֘A�捀�ڂ����� */
		for( i=0; i < iTcnt ;++i ) {
			if( i == iCrcnt ) {
				/* �������q�b�g �ǂݔ�΂� */
				continue;
			}
			if( !memcmp(pKekka[i].kmkcd, (gKrkmkmst+iCnt)->krkmkcd, 7) ) {
				/* �֘A���ڔ��� */
				/* ���聕�����̊֘A�t���O��'2' */
				pKekka[i].kanrenflg = pKekka[iCrcnt].kanrenflg = '2';
				/* �����̌����t���O��'R'�������瑊���'R'�ɂ��� */
				if( pKekka[iCrcnt].knsflg == 'R' ) {
					pKekka[i].knsflg = 'R';
				}
				/* ������'A'�ő��肪'R'�łȂ���Α����'A'�ɂ��� */
				if( pKekka[iCrcnt].knsflg == 'A' ) {
					if( pKekka[i].knsflg != 'R' ) {
						pKekka[i].knsflg = 'A';
					}
				}
				iKhit = 1;
			}
			/* 2.�֘A����UPDATE */
			if( iKhit ) {
				/* �֘A��̗D�挋�ʂ̌����t���O���ύX���� */
				/* 1. SELECT */
				if( pKkaYkrn != NULL ) {
					ZbmlFree(pKkaYkrn);
					pKkaYkrn = NULL;
				}
				iKcnt = 0;
				/* �����񐔃f�N�������g */
				memset(&wKekka, 0, sizeof(Kekka));
				memcpy(&wKekka, &pKekka[i], sizeof(Kekka));
				wKekka.knssu -= 1;
				if( (ret=ZdbKekkaSelectKKAYSN(&wKekka, &pKkaYkrn, &iKcnt)) < 0 ) {
					sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectKKAYSN",ret);
					if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
						sFncPutLog (TRCKIND_WARNING, __FILE__, "kanrenChk",__LINE__,
							EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
						ZbmlFree(pKkaYkrn);
						return(RET_CONTINUITY);
					}
					sFncSyslog ( LOG_ERR, "kanrenChk()", errMsg ) ;
					ZbmlFree(pKkaYkrn);
					return (RET_STOP);
				}
				if( iKcnt )
				{
					/* 2.�����e�k�f�Z�b�g */
					pKkaYkrn->knsflg = pKekka[i].knsflg;
					/* CHG 2006/08/05 Nagata */
					/* 	�֘A�G���[�̈��p�����A�D��̉񐔂ɑ΂��čs��Ȃ��B*/
					/* 	�i�ƍ��ōs�����֘A��O�̉񐔂ɔ��f�����Ȃ��j */
					/* 	�������A�����t���O�̔��f�͍s���B */

					/* 3.Update */
					if( ZdbKekkaUpdate(pKkaYkrn) < 0 ) {
						sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdate",ret);
						if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
							sFncPutLog (TRCKIND_WARNING, __FILE__, "kanrenChkYsn",__LINE__,
								EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
							ZbmlFree(pKkaYkrn);
							return(RET_CONTINUITY);
						}
						sFncSyslog ( LOG_ERR, "kanrenChk()", errMsg ) ;
						ZbmlFree(pKkaYkrn);
						return (RET_STOP);
					}
				}
			}
		}
	}
	return( 0 );
}
/*----------------------------------------------------------------------------*/
/* �ƍ��n�j���Ɋ֘A���ڂ̗D�挋�ʂ̌����t���O���X�V����                       */
/* �����F                                                                     */
/*		1)�v�Z����                                                            */
/*		2)�����t���O�� 'A'                                                    */
/*		3)�G���[�t���O '�A' �̂�(kanrenflg �� '2'�ŁA���̂ق��̃t���O'2'�ȊO) */
/*----------------------------------------------------------------------------*/
int kanrenChkYsn(Kekka *pKekka)
{
	int iCnt;
	Kekka *pKkaYkrn = NULL;
	Kekka wKekka;
	int 		ret;
	char		errMsg[1024] = {0,};

	for( iCnt=0; iCnt < gKrkCnt ;++iCnt ) {
		/* 1.�����̊֘A���ڃR�[�h���擾 */
		if( memcmp((gKrkmkmst+iCnt)->kmkcd, pKekka->kmkcd, 7) ) continue;

		/* 2.�֘A��̗D�挋�ʍX�V */
		memset(&wKekka, 0, sizeof(Kekka));
		memcpy(&wKekka, pKekka, sizeof(Kekka));
		wKekka.knssu -= 1;
		memcpy(wKekka.kmkcd, (gKrkmkmst+iCnt)->krkmkcd, 7);
		/* Update */
		ret = updKkaYsn( &wKekka );
		if( ret < 0 ) {
			sprintf(errMsg,"SQL CODE:%d updKkaYsn",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "kanrenChkYsn",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				ZbmlFree(pKkaYkrn);
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "kanrenChkYsn()", errMsg) ;
			ZbmlFree(pKkaYkrn);
			return (RET_STOP);

		}
	}
	return( 0 );
}

int GetKrkmkmst()
{
	char		errMsg[1024] = {0,};
	int 		ret;

	gKrkCnt = 0;
	ret=ZdbKrkmkmstSelectAll(&gKrkmkmst, &gKrkCnt);
	if(ret<0) {
		sprintf(errMsg,"SQL CODE:%d ZdbKrkmkmstSelectAll",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "GetKrkmkmst",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "GetKrkmkmst()", errMsg ) ;
		return(RET_STOP);
	}
	if(ret == HRC_SQL_NOT_FOUND){
		sFncSyslog ( LOG_ERR, "GetKrkmkmst()", errMsg ) ;
		return(RET_STOP);
	}

	return 0;
}

int getOdrLast(Kekka *pKekka, Kenorder *p_Order)
{
	long		lRet;
	Kenorder	sKenorder;
	Kenorder	*pKenorder = NULL;
	int 		orderCnt;
	char		errMsg[1024] = {0,};

	/* ���j�d�x�̃I�[�_�[�����擾 */
	memset(&sKenorder, 0, sizeof(sKenorder));
	memcpy(sKenorder.knskisymd, pKekka->knskisymd, sizeof(pKekka->knskisymd));
	memcpy(sKenorder.sriymd, pKekka->sriymd, sizeof(pKekka->sriymd));
	memcpy(sKenorder.kntno, pKekka->kntno, sizeof(pKekka->kntno));
	memcpy(sKenorder.knsgrp, pKekka->knsgrp, sizeof(pKekka->knsgrp));
	memcpy(sKenorder.kmkcd, pKekka->kmkcd, sizeof(pKekka->kmkcd));
	sKenorder.knssu = pKekka->knssu;
	sKenorder.knssueda = pKekka->knssueda;

	lRet = ZdbKenorderSelectKey(&sKenorder, &pKenorder, &orderCnt);
	if ((lRet != HRC_SQL_NORMAL) && (lRet != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%ld ZdbKenorderSelectKey",lRet);
		if(lRet == SQL_ERR_DUPLICATION || lRet == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "getOdrLast",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "getOdrLast()", errMsg ) ;
		return(RET_STOP);
	}
	if (orderCnt == 0) {
		/* ���݂��Ȃ� */
		return 0;
	} else {
		/* ���݂��� */
		if( pKenorder != NULL ) {
			memcpy(p_Order, pKenorder, sizeof(Kenorder));
			ZbmlFree(pKenorder);
		}
		return 1;
	}
}

/* �ƍ��`�F�b�N(rawdata���u�����N�̏ꍇNG) */
/*	 ����1 aRawdata1 ������1��ڃf�[�^ */
/*		 2 aRawdata2 ������2��ڃf�[�^ */
/*	 �ߒl  TRUE   OK */
/*		   FALSE  NG */
/* ����A�Č��A�ǂ��炩��raw�f�[�^���A�}�C�i�X��������ƍ�NG�Ƃ��� */
static int chkRawdata( char * aRawdata1, char * aRawdata2 )
{
	char	cRawBuf[256] ;

	/* ����f�[�^ */
	/* raw�f�[�^���u�����N */
	trim( cRawBuf, aRawdata1 );
	if	( cRawBuf[0] == '\0' || cRawBuf[0] == '/' ) {
		return FALSE;
	}
	/* raw�f�[�^���}�C�i�X */
	if( atof(cRawBuf) < 0.0 ){
		return FALSE;
	}

	/* �Č��f�[�^ */
	/* raw�f�[�^���u�����N */
	trim( cRawBuf, aRawdata2 );
	if	( cRawBuf[0] == '\0' || cRawBuf[0] == '/' ) {
		return FALSE;
	}

	/* raw�f�[�^���}�C�i�X */
	if( atof(cRawBuf) < 0.0 ){
		return FALSE;
	}

	return TRUE;
}

/******************************************************************************/
/*	�� �� ��  �FgetKekkaData()						*/
/*	�@�\�T�v  �F���ʃt�@�C�������A�ݒ�					*/
/*	��	  ��  �F							*/
/*	 ��P���� �Fbuff	:	�t�@�C�����R�[�h(CSV)			*/
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��			*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/******************************************************************************/
int getKekkaData(char * buff, Kekka *pKekka)
{
	char		** pFld;
	int 		cnt;
	int 		offset;
	
	char		cJisksbr[16];
	char		cRawdata[21];

	pFld = malloc(sizeof(char *)*200);
	/* �J���}��؂�̃��R�[�h�𕪊����ADB���R�[�h�̍\���̂ɐݒ肷��B */
	cnt = 0;
	offset = 0;;
	pFld[cnt] = &buff[cnt];
	cnt++;
	while (buff[offset] != '\0') {
		if (buff[offset] == ',') {
			pFld[cnt++] = &buff[offset+1];
			buff[offset] = '\0';
		}
		if (buff[offset] == '\n') {
			buff[offset] = '\0';
		}
		offset++;
	}

	if (cnt != 118) {
		/* �t�B�[���h������v���Ȃ� */
		sFncSyslog ( LOG_ERR, "getKekkaData()", "Kekka CSV File Field Not Count." ) ;
		return -1;
	}

	/* �e�t�B�[���h���i�[����B */
	strncpy( pKekka->knskisymd, pFld[0], sizeof( pKekka->knskisymd )-1);	/* �����J�n�� */
	strncpy( pKekka->sriymd, pFld[1], sizeof( pKekka->sriymd )-1);
	strncpy( pKekka->kntno, pFld[2], sizeof( pKekka->kntno )-1);
	pKekka->kntketflg = pFld[3][0];
	strncpy( pKekka->knsgrp, pFld[4], sizeof( pKekka->knsgrp )-1);
	strncpy( pKekka->kmkcd, pFld[5], sizeof( pKekka->kmkcd )-1);		/* ���ڃR�[�h */
	pKekka->knssu = atoi(pFld[6]);						/* ������ */
	pKekka->knssueda = atoi(pFld[7]);					/* �������} */
	pKekka->irihsmkbn = pFld[8][0];
	pKekka->irikbn = pFld[9][0];
	pKekka->ksktkbn = pFld[10][0];
	strncpy( pKekka->utkymd, pFld[11], sizeof( pKekka->utkymd )-1);
	strncpy( pKekka->irino, pFld[12], sizeof( pKekka->irino )-1);
	pKekka->iriketflg = pFld[13][0];
	pKekka->zssdino = atoi(pFld[14]);
	strncpy( pKekka->sstcd, pFld[15], sizeof( pKekka->sstcd )-1);
	strncpy( pKekka->trid, pFld[16], sizeof( pKekka->trid )-1);
	pKekka->trpos = atoi(pFld[17]);
	strncpy( pKekka->asyrckid, pFld[18], sizeof( pKekka->asyrckid )-1); 	/* ���b�NID */
	pKekka->asyrckpos = atoi(pFld[19]); 					/* �|�W�V���� */
	strncpy( pKekka->oyakmkcd, pFld[20], sizeof( pKekka->oyakmkcd )-1);
	strncpy( pKekka->seccd, pFld[21], sizeof( pKekka->seccd )-1);
	pKekka->bkfkkbn = pFld[22][0];
	strncpy( pKekka->smpcd, pFld[23], sizeof( pKekka->smpcd )-1);
	strncpy( pKekka->bskkbn, pFld[24], sizeof( pKekka->bskkbn )-1);
	strncpy( pKekka->bsklne, pFld[25], sizeof( pKekka->bsklne )-1);
	strncpy( pKekka->bskgok, pFld[26], sizeof( pKekka->bskgok )-1);
	pKekka->bskseq = atoi(pFld[27]);
	strncpy( pKekka->bskerrsts, pFld[28], sizeof( pKekka->bskerrsts )-1);
	strncpy( pKekka->sktdh, pFld[29], sizeof( pKekka->sktdh )-1);
	strncpy( pKekka->nbkmkcd, pFld[30], sizeof( pKekka->nbkmkcd )-1);
	pKekka->tstrflg = pFld[31][0];
	strncpy( pKekka->zrcd, pFld[32], sizeof( pKekka->zrcd )-1);
	strncpy( pKekka->ysnlbl, pFld[33], sizeof( pKekka->ysnlbl )-1);
	strncpy( pKekka->kjno, pFld[34], sizeof( pKekka->kjno )-1);
	pKekka->fkhkknohjkbn = pFld[35][0];
	strncpy( pKekka->tbkjno, pFld[36], sizeof( pKekka->tbkjno )-1);
	pKekka->tbkjflg = pFld[37][0];
	strncpy( pKekka->htkfkhms, pFld[38], sizeof( pKekka->htkfkhms )-1);
	pKekka->skflg = pFld[39][0];
	strncpy( pKekka->tskflg, pFld[40], sizeof( pKekka->tskflg )-1);
	strncpy( pKekka->tktflg, pFld[41], sizeof( pKekka->tktflg )-1);
	/* �Z�b�g�����ߔ{�����c�a�o�^�E�\�������ɕϊ����� */
	memset( cJisksbr, '\0', sizeof ( cJisksbr ) );
	trim ( cJisksbr, pFld[42] );
	if( strcmp( cJisksbr, KskbrB10CD ) == 0 ){
		memset( cJisksbr, ' ', sizeof ( cJisksbr ) - 1 );
		strncpy( cJisksbr, KskbrB10HY , strlen( KskbrB10HY ) );
	} else if ( strcmp( cJisksbr, KskbrB2CD ) == 0 ) {
		memset( cJisksbr, ' ', sizeof ( cJisksbr ) - 1 );
		strncpy( cJisksbr, KskbrB2HY , strlen( KskbrB2HY ) );
	} else {
		memset( cJisksbr, ' ', sizeof ( cJisksbr ) - 1 );
	}
	strncpy( pKekka->jisksbr, cJisksbr, sizeof( pKekka->jisksbr )-1);
	pKekka->kkflg = pFld[43][0];
	pKekka->kkiriflg = pFld[44][0];
	pKekka->kkirilotno = atoi(pFld[45]);
	pKekka->hsykflg = pFld[46][0];
	pKekka->hskflg = pFld[47][0];
	pKekka->hhkkflg = pFld[48][0];
	/* ���ʒl�� ? �̏ꍇ�� / �ɒu�������āABM8060 �̎��Ɠ��������������B*/
	memset( cRawdata, '\0', sizeof ( cRawdata ) );
	trim ( cRawdata, pFld[49] );
	if( cRawdata[0] == '?' ){
		strncpy( pKekka->rawdata, "////////", sizeof( pKekka->rawdata )-1);
	} else {
		/* RAWDATA �����l�߂œo�^���� */
		strncpy( pKekka->rawdata, pFld[49], sizeof( pKekka->rawdata )-1);
	}
	strncpy( pKekka->knskka1, pFld[50], sizeof( pKekka->knskka1 )-1);
	strncpy( pKekka->knskka2, pFld[51], sizeof( pKekka->knskka2 )-1);
	strncpy( pKekka->knskka2kbn, pFld[52], sizeof( pKekka->knskka2kbn )-1);
	strncpy( pKekka->kkahskcd, pFld[53], sizeof( pKekka->kkahskcd )-1);
	strncpy( pKekka->hjkka, pFld[54], sizeof( pKekka->hjkka )-1);
	strncpy( pKekka->sdi, pFld[55], sizeof( pKekka->sdi )-1);
	strncpy( pKekka->kkacmt1, pFld[56], sizeof( pKekka->kkacmt1 )-1);
	strncpy( pKekka->kkacmt2, pFld[57], sizeof( pKekka->kkacmt2 )-1);
	pKekka->kkajkcd = pFld[58][0];
	pKekka->pncrgflg = pFld[59][0];
	pKekka->knspncrgflg = pFld[60][0];
	pKekka->kkaksflg = pFld[61][0];
	pKekka->kkassflg = pFld[62][0];
	pKekka->ijkbnm = pFld[63][0];
	pKekka->ijkbnf = pFld[64][0];
	pKekka->ijkbnn = pFld[65][0];
	pKekka->tbijkbnm = pFld[66][0];
	pKekka->tbijkbnf = pFld[67][0];
	pKekka->tbijkbnn = pFld[68][0];
	strncpy( pKekka->nbdolbl, pFld[69], sizeof( pKekka->nbdolbl )-1);	/*���� */
	strncpy( pKekka->nbdoerr, pFld[70], sizeof( pKekka->nbdoerr )-1);
	strncpy( pKekka->ykdolbl, pFld[71], sizeof( pKekka->ykdolbl )-1);	/*�n�� */
	strncpy( pKekka->ykdoerr, pFld[72], sizeof( pKekka->ykdoerr )-1);
	strncpy( pKekka->etclbl, pFld[73], sizeof( pKekka->etclbl )-1); 	/* ���t */
	strncpy( pKekka->etcerr, pFld[74], sizeof( pKekka->etcerr )-1);
	pKekka->ctrlno = atoi(pFld[75]);
	pKekka->knsseq = atoi(pFld[76]);
	pKekka->bthno = atoi(pFld[77]);
	pKekka->pltno = atoi(pFld[78]);
	pKekka->pltseq = atoi(pFld[79]);
	strncpy( pKekka->dtnrtts, pFld[80], sizeof( pKekka->dtnrtts )-1);

	strncpy( pKekka->dtnrdh, pFld[81], sizeof( pKekka->dtnrdh )-1);
	strncpy( pKekka->knskrdh, pFld[82], sizeof( pKekka->knskrdh )-1);
	strncpy( pKekka->hkkdh, pFld[83], sizeof( pKekka->hkkdh )-1);
	strncpy( pKekka->hkkkbdh, pFld[84], sizeof( pKekka->hkkkbdh )-1);
	strncpy( pKekka->zkhkkyymd, pFld[85], sizeof( pKekka->zkhkkyymd )-1);

	strncpy( pKekka->zkhkkytme, pFld[86], sizeof( pKekka->zkhkkytme )-1);
	pKekka->frkkaflg = pFld[87][0];
	pKekka->gzbsflg = pFld[88][0];
	pKekka->hsiflg = pFld[89][0];
	pKekka->kkaysnflg = pFld[90][0];
	pKekka->tnyrkflg = pFld[91][0];
	pKekka->siyflg = pFld[92][0];
	pKekka->knsflg = pFld[93][0];
	pKekka->renjicflg = pFld[94][0];
	pKekka->soukn1flg = pFld[95][0];
	pKekka->kanrenflg = pFld[96][0];
	pKekka->bunkkuflg = pFld[97][0];
	pKekka->kesseiflg = pFld[98][0];
	pKekka->rirekiflg = pFld[99][0];
	pKekka->syougoflg = pFld[100][0];
	pKekka->keisanflg = pFld[101][0];
	pKekka->per100flg = pFld[102][0];
	pKekka->tousekflg = pFld[103][0];
	pKekka->kisyakflg = pFld[104][0];
	pKekka->kouseiflg = pFld[105][0];
	pKekka->syoungflg = pFld[106][0];
	pKekka->soukn2flg = pFld[107][0];
	pKekka->fukaptflg = pFld[108][0];
	pKekka->yobiflg01 = pFld[109][0];
	pKekka->tobiflg02 = pFld[110][0];
	pKekka->yobiflg03 = pFld[111][0];
	pKekka->yobiflg04 = pFld[112][0];
	pKekka->yobiflg05 = pFld[113][0];
	strncpy( pKekka->skrycda, pFld[114], sizeof( pKekka->skrycda )-1);
	strncpy( pKekka->skrycdb, pFld[115], sizeof( pKekka->skrycdb )-1);
	strncpy( pKekka->skrycdc, pFld[116], sizeof( pKekka->skrycdc )-1);
	strncpy( pKekka->ksndh, pFld[117], sizeof( pKekka->ksndh )-1);
	strncpy( pKekka->trkdh, "1000-01-01 00:00:01", sizeof( pKekka->trkdh )-1);
	strncpy( pKekka->skkka, pFld[54], sizeof( pKekka->skkka )-1);

	/* �������J�� */
	ZbmlFree( pFld );

	return( 0 );
}
/******************************************************************************/
/*	�� �� ��  �FNyubiYoketuChk()						*/
/*	�@�\�T�v  �F���сE�n���`�F�b�N						*/
/*	��	  ��  �F							*/
/*	 ��P���� �FchkPara :	�`�F�b�N�p�p�����[�^				*/
/*	 ��Q���� �FpKekka	:	���ʏ��\���̔z��			*/
/*	 ��R���� �FKekkaCnt:	���ʏ��\���̐�				*/
/*	 ��S���� �FlCnt	:	�������ʒu				*/
/*	 ��T���� �FfNyuYou :	���сE�n���t���O				*/
/*	�o	  ��  �F							*/
/*	���A���  �Fint 							*/
/*					0:�Č�����				*/
/*					1:�Č�����				*/
/******************************************************************************/
static int	NyubiYoketuChk(Kekka * pKekka, int KekkaCnt, int lCnt, int fNyuYou)
{
	int 		ret = 0;
	Realchk 	sReal;
	Realchk 	*pReal = NULL;
	int 		Realcnt;
	int 		iKnssu;

	/* �����`�F�b�N���̎擾 */
	memset(&sReal, 0, sizeof(sReal));
	strncpy(sReal.knskisymd, pKekka->knskisymd, 10);
	strncpy(sReal.sriymd, pKekka->sriymd, 10);
	strncpy(sReal.kntno, pKekka->kntno, 13);
	strncpy(sReal.knsgrp, pKekka->knsgrp, 16);
	strncpy(sReal.kmkcd, pKekka->kmkcd, 8);
	sReal.knssu = pKekka->knssu;
	sReal.knssueda = 0;
	char		errMsg[1024] = {0,};

	ret = ZdbRealchkSelectKey(&sReal, &pReal, &Realcnt);
	if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
		sprintf(errMsg,"SQL CODE:%d ZdbRealchkSelectKey",ret);
		if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "NyubiYoketuChk",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		sFncSyslog ( LOG_ERR, "NyubiYoketuChk()", errMsg ) ;
		return(RET_STOP);
	}
	if (ret == HRC_SQL_NOT_FOUND) {
		/* �Č������l�����A�����񐔂��P���傫���Ƃ��͌����񐔂��f�N�������g�� */
		/* ������x�A��������B */

		/* �ė����̍ۂɃ��A���`�F�b�N���擾�o���Ȃ��ꍇ�����邽�߁A */
		/* ������܂Ńf�N�������g��������i�����������񐔂��P�ɂȂ�����I���j */
		iKnssu = 0;
		for (iKnssu = sReal.knssu - 1 ; iKnssu > 0 ; iKnssu-- ) {
			sReal.knssu = iKnssu;
			ret = ZdbRealchkSelectKey(&sReal, &pReal, &Realcnt);
			if ((ret != HRC_SQL_NORMAL) && (ret != HRC_SQL_NOT_FOUND)) {
				sprintf(errMsg,"SQL CODE:%d ZdbRealchkSelectKey",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "NyubiYoketuChk",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "NyubiYoketuChk()", errMsg ) ;
				return(RET_STOP);
			}
			if (ret != HRC_SQL_NOT_FOUND) {
				/* �������� */
				break;
			}
		}
		if(ret == HRC_SQL_NOT_FOUND) {
			/* ���ǁA�Ō�܂ł݂���Ȃ����� */
			return 0;
		}
	}
	if (fNyuYou == 0) {
		/* ���сE�n���łȂ��Ƃ��͏������Ȃ� */
		return 0;
	}

	if (pReal->kesseipara[1] == '1') {
		switch (pReal->kesseipara[0]) {
		case '0':
			break;
		case '1':	/* ���т̂� */
			if (fNyuYou & 1) {
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					/* ���ʃR�����g�P�ɉ����Z�b�g����Ă��Ȃ�������0105������ */
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
					/* �����A���ʃR�����g�ɓ��уR�����g�������Ă�����Ȃɂ����Ȃ� */
				}
				else {
					/* ���ʃR�����g�P�ɃR�����g���Z�b�g����Ă�����A�P�̓��e���Q�Ɉڂ��A*/
					/* �P��0105������ */
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				ret = 1;
			}
			break;
		case '2':	/* �n���̂� */
			if (fNyuYou & 2) {
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
					/* �����A���ʃR�����g�ɗn���R�����g�������Ă�����Ȃɂ����Ȃ� */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				ret = 1;
			}
			break;
		case '3':	/* ���їD�� */
			if (fNyuYou & 2) {		/* �n�� */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
					/* �����A���ʃR�����g�ɗn���R�����g�������Ă�����Ȃɂ����Ȃ� */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				ret = 1;
			}
			if (fNyuYou & 1) {		/* ���� */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
					/* �����A���ʃR�����g�ɓ��уR�����g�������Ă�����Ȃɂ����Ȃ� */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				ret = 1;
			}
			break;
		case '4':	/*  �n���D�� */
			if (fNyuYou & 1) {		/* ���� */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, NyubiCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, NyubiCM, 4) == 0 ) {
					/* �����A���ʃR�����g�ɓ��уR�����g�������Ă�����Ȃɂ����Ȃ� */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, NyubiCM, 5);
				}
				ret = 1;
			}
			if (fNyuYou & 2) {			/* �n�� */
				if( (pKekka[lCnt].kkacmt1[0] == ' ') || (pKekka[lCnt].kkacmt1[0] == '\0') ) {
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				else if( memcmp(pKekka[lCnt].kkacmt1, YoketsuCM, 4 ) == 0 
						|| memcmp(pKekka[lCnt].kkacmt2, YoketsuCM, 4) == 0 ) {
					/* �����A���ʃR�����g�ɗn���R�����g�������Ă�����Ȃɂ����Ȃ� */
				}
				else {
					memset(pKekka[lCnt].kkacmt2, 0, sizeof(pKekka[lCnt].kkacmt2));
					strncpy( pKekka[lCnt].kkacmt2, pKekka[lCnt].kkacmt1, 5);
					memset(pKekka[lCnt].kkacmt1, 0, sizeof(pKekka[lCnt].kkacmt1));
					strncpy( pKekka[lCnt].kkacmt1, YoketsuCM, 5);
				}
				ret = 1;
			}
			break;
		}
	}
	ret = 0;
	pKekka[lCnt].kesseiflg = '1';

	if( pReal != NULL ) {
		ZbmlFree(pReal);
		pReal = NULL;
	}

	return ret;
}
static int	NyubiYoketu( Kekka * pKekka, int KekkaCnt)
{
	int 		ret = 0;
	double		rawData;
	char		tmp[22];
	int 		lCnt;

	ret = 0;
	for (lCnt = 0; lCnt < KekkaCnt; lCnt++ ) {
		/* ���ʒl�̒l������𐔒l������ */
		memset(tmp, 0, sizeof(tmp));
		strncpy(tmp, pKekka[lCnt].rawdata, 20);
		rawData = atof(tmp);

		/* ���у`�F�b�N */
		if (strncmp( pKekka[lCnt].kmkcd , NyubiCD, 7) == 0 ) {
			ret |= 0x10;
			memset( NyubiKekka, 0, sizeof(NyubiKekka)); 	/* Level */
			trim( NyubiKekka, pKekka[lCnt].rawdata );
			memset( NyubiSTS, 0, sizeof(NyubiSTS)); 		/* Status */
			strncpy( NyubiSTS, pKekka[lCnt].bskerrsts, 2);
			pKekka[lCnt].knsflg = 'H';
			if ( rawData > atof(NyubiCHK) ) {
				ret |= 0x01;
			}
		}
		/* �n���`�F�b�N */
		else if (strncmp( pKekka[lCnt].kmkcd , YoketsuCD, 7) == 0 ) {
			ret |= 0x20;
			memset( YoketsuKekka, 0, sizeof(YoketsuKekka));
			trim( YoketsuKekka, pKekka[lCnt].rawdata );
			memset( YoketsuSTS, 0, sizeof(YoketsuSTS));
			strncpy( YoketsuSTS, pKekka[lCnt].bskerrsts, 2);
			pKekka[lCnt].knsflg = 'H';
			if ( rawData > atof(YoketsuCHK) ) {
				ret |= 0x02;
			}
		}
		/* ���t�`�F�b�N */
		else if (strncmp( pKekka[lCnt].kmkcd , OudanCD, 7) == 0 ) {
			ret |= 0x40;
			memset( OudanKekka, 0, sizeof(OudanKekka));
			trim( OudanKekka, pKekka[lCnt].rawdata );
			memset( OudanSTS, 0, sizeof(OudanSTS));
			strncpy( OudanSTS, pKekka[lCnt].bskerrsts, 2);
			pKekka[lCnt].knsflg = 'H';
		}
	}
	return ret;
}

/* ������񏈗��ǉ� */
int kesseiCHK(Kekka *pSrc, int iKcnt)
{
	int 		i, KesFlg;
	Kekka		* pKekka, *spKekka = NULL;
	Kekka		KesKekka;
	int 		ret;
	int 		num_spKekka;
	char		sBuff[10];
	char		errMsg[1024] = {0,};

	KesFlg = 0;
	memset(&KesKekka, 0, sizeof(Kekka));
	for( i=0; i < iKcnt ;++i ) {
		pKekka = pSrc + i;
		if( i == 0 )
			memcpy(&KesKekka, pKekka, sizeof(Kekka));

		if( strncmp( pKekka->kmkcd, NyubiCD,   7 ) == 0 ) {
			if( KesFlg == 0 ) {
				KesFlg = 1;
			}
			/* ���уG���[�X�e�[�^�X�̎擾�ʒu�𕪐͋@�G���[�ɕύX */
			memcpy(KesKekka.nbdoerr, pKekka->bskerrsts, 2);
			/* CHG E.Osada 2006-09-16 */
			memset(sBuff, 0, sizeof(sBuff));
			trim(sBuff, pKekka->rawdata);
			if( strlen(sBuff) > 2 ) {
				memcpy(KesKekka.nbdolbl, "99", 2);
			} else {
				memcpy(KesKekka.nbdolbl, sBuff, 2);
			}
		}
		if( strncmp( pKekka->kmkcd, YoketsuCD, 7 ) == 0 ) {
			if( KesFlg == 0 ) {
				KesFlg = 1;
			}
			/* �G���[�X�e�[�^�X�̎擾�ʒu�𕪐͋@�G���[�ɕύX */
			memcpy(KesKekka.ykdoerr, pKekka->bskerrsts, 2);
			memset(sBuff, 0, sizeof(sBuff));
			trim(sBuff, pKekka->rawdata);
			if( strlen(sBuff) > 2 ) {
				memcpy(KesKekka.ykdolbl, "99", 2);
			} else {
				memcpy(KesKekka.ykdolbl, sBuff, 2);
			}
		}
		if( strncmp( pKekka->kmkcd, OudanCD, 7 ) == 0 ) {
			if( KesFlg == 0 ) {
				KesFlg = 1;
			}
			/* UPD 2006-09-05 Nagata */
			/* ���уG���[�X�e�[�^�X�̎擾�ʒu�𕪐͋@�G���[�ɕύX */
			memcpy(KesKekka.etcerr, pKekka->bskerrsts, 2);
			/* CHG E.Osada 2006-09-16 */
			memset(sBuff, 0, sizeof(sBuff));
			trim(sBuff, pKekka->rawdata);
			if( strlen(sBuff) > 2 ) {
				memcpy(KesKekka.etclbl, "99", 2);
			} else {
				memcpy(KesKekka.etclbl, sBuff, 2);
			}
		}
	}
	if( KesFlg )
	{
		/* ���ڃR�[�h���u���сv�������́u�n���v�̏ꍇ�A�֘A����Update */
		/* ���сA�n���x�X�V */
		ret = ZdbKekkaUpdateNbYk( &KesKekka );
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND) {

			sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdateNbYk",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
			return(RET_STOP);

		}
		if( spKekka != NULL ) {
			ZbmlFree( spKekka );
			spKekka = NULL;
		}
		/*  �֘A���ڂ̃f�[�^Select */
		ret = ZdbKekkaSelectRckPos( &KesKekka, &spKekka, &num_spKekka );
		if ( ret != HRC_SQL_NORMAL && ret != HRC_SQL_NOT_FOUND ) {
			sprintf(errMsg,"SQL CODE:%d ZdbKekkaSelectRckPos",ret);
			if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
				sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
					EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
				return(RET_CONTINUITY);
			}
			sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
			return(RET_STOP);
		}
		else if(ret == HRC_SQL_NOT_FOUND){
			sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
				EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
			return(RET_CONTINUITY);
		}
		/* ���сA�n���`�F�b�N */
		gfNyuYou = NyubiYoketu( pSrc, iKcnt );
		/* �֘A���ڃf�[�^�����[�v */
		for( i = 0; i < num_spKekka; i++ ) {
			ret = NyubiYoketuChk(spKekka+i, 1, 0, gfNyuYou);
			if (ret != 0) {
				/* �o�^�`�F�b�N�G���[ */
				sFncSyslog ( LOG_ERR, "kesseiCHK()", "kessei Check Error." ) ;
				return ret;
			}
			/* ���ʃR�����g1,2�X�V */
			/*  ADD E.Osada 2006-08-17 */
			(spKekka+i)->kesseiflg = '1';

			ret = ZdbKekkaUpdateCmt12( spKekka+i );
			if ( ret != HRC_SQL_NORMAL&& ret != HRC_SQL_NOT_FOUND ) {
			   sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdateCmt12",ret);
				if(ret == SQL_ERR_DUPLICATION || ret == SQL_ERR_LOCK){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
					/* �������J�� */
				if( spKekka != NULL ) {
						ZbmlFree( spKekka );
				}
				return(RET_STOP);

			}
			if( (spKekka+i)->knsflg == 'H' ) {
				/* �G���[���Ȃ��ꍇ�͌����t���O��'X' */
				(spKekka+i)->knsflg = 'X';
			}
			/* ADD 2006-08-31 Nagata �����t���O���X�V���� */
			ret = ZdbKekkaUpdateKnsFlg( spKekka+i );
			if(ret < 0){
				sprintf(errMsg,"SQL CODE:%d ZdbKekkaUpdateKnsFlg",ret);
				if(ret == SQL_ERR_LOCK || ret == SQL_ERR_DUPLICATION){
					sFncPutLog (TRCKIND_WARNING, __FILE__, "kesseiCHK",__LINE__,
						EXEFLG_NON, MYAPP_LOG_ERRCODE_NON, errMsg) ;
					return(RET_CONTINUITY);
				}
				sFncSyslog ( LOG_ERR, "kesseiCHK()", errMsg ) ;
				return(RET_STOP);
			}

		}
	}
	/* �������J�� */
	if( spKekka != NULL ) {
		ZbmlFree( spKekka );
	}
	return 0;
}

/**/
int CHG_Mojikjn(input,kbn)
/*****************************************************************************
*fc
	��l(������f�[�^)�̊��Z�l�擾
	�i�P�O�[�@�`�@�P�O�{�@�̐��l�ϊ��j
*rt
	���Z�l	 ... ��l(������f�[�^)�̊��Z�l
	BAD_DATA ... ��l(������f�[�^)�ɊY�����銷�Z�l���Ȃ�
*nt
*ag
*****************************************************************************/
char *input;
char kbn;
{
	int 	ret;
	int 	cnt;
	char	wk_input[20];

	ret = 0;

	trim(wk_input, input);

	if(wk_input[0] == '\0'){
		/* �X�y�[�X�Ȃ�I�� */
		return 0;
	}

	if( kbn == 'X' ){
		for(cnt = 1; KZN_Teisei[cnt] != NULL ; cnt++){
			if(memcmp(KZN_Teisei[cnt],"END",3) == 0){
				/* END�Ȃ甲���� */
				break;
			}
			if(memcmp(KZN_Teisei[cnt],wk_input,strlen(wk_input)) == 0){
				ret = cnt;
				break;
			}
		}
	}

	if( kbn == '0' ){
		for(cnt = 1; KZN_Coment[cnt] != NULL ; cnt++){
			if(memcmp(KZN_Coment[cnt],"END",3) == 0){
				/* END�Ȃ甲���� */
				break;
			}
			if(memcmp(KZN_Coment[cnt],wk_input,strlen(wk_input)) == 0){
				ret = cnt;
				break;
			}
		}
	}

	return ret;
}

/**/
int CHK_Kkacmt(input)
/*****************************************************************************
*fc
	�ُ�l�}�[�N������ʃR�����g�̃`�F�b�N
*rt
	0	   ... �ُ�l�}�[�N�Ȃ�
	1	   ... �ُ�l�}�[�N����
	���̑� ... �G���[
*nt
*ag
*****************************************************************************/
char *input;
{
	int 	cnt;
	char	wk_input[20];

	trim(wk_input, input);

	if(wk_input[0] == '\0'){
		/* �X�y�[�X�Ȃ�I�� */
		return -1;
	}

	for(cnt = 1; IJOU_KKACMT[cnt] != NULL ; cnt++){
		if(memcmp(IJOU_KKACMT[cnt],"END",3) == 0){
			/* END�Ȃ甲���� */
			break;
		}
		if(memcmp(IJOU_KKACMT[cnt],wk_input,strlen(wk_input)) == 0){
			/* �ُ�l�}�[�N�R�����g�ɊY���I�I */
			return 1;
		}
	}
	/* �Y���Ȃ� */
	return 0;
}

