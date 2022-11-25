/**********************************************************************
 *
 *     �P�~�X�g���[�����V�X�e��
 *
 *     �V�X�e�����F�������t�@�C���R���o�[�g
 *     �t�@�C�����FRirekiConv.c
 *     �T�v      �F�����{�̌��ʏ��t�@�C�����P�~�X�g���[�̗����e�[�u����
 *                 �ϊ��ł���`���փR���o�[�g����B
 *
 **********************************************************************/
/* ���P �Ăяo�����ŏo�͌��ʂ����O�ɏo�͂��邽�߁Aprintf �ŕW���o�͂֏o�͂��� */
/* ���Q �����G���[���ɃG���[���b�Z�[�W�����[�����M���邽�߂ɁA�G���[�t�@�C�����쐬���� */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>

/********************************************************************************
*       �ʖ���`                                                                *
*********************************************************************************/
#define MY_COM_SIZE	sizeof  ( char )

#define DEF_STAMP "-00.00.00.000001"

#define RTN_OK 0
#define RTN_NG -1

#define FILE_KMKMST	"TMP_KMKMST.del"
#define FILE_CMTMST	"TMP_CMTMST.del"
#define FILE_ID		"A00"

/* ���Q */
#define LOG_DIR		"/apdata/aplog"
#define NAME_ERRLOG	"FATAL_"
/********************************************************************************
*       �����֐���`                                                            *
*********************************************************************************/
static int		mainFunction( char*, char*, char* ) ;
static int		SetKnsgrp( char *, char * ) ;
static int		ConvKekka( char *, char *, char, char *, char * ) ;
static int		ConvCmtKekka( char *, char * ) ;
static int		GetKmkFile( void ) ;
static int		GetCmtFile( void ) ;
static int		NameKeyMake( char *, char *, int ) ;
static char*	SetValue( char *, char *, int ) ;
static int		DateGetToday( char * ) ;
static void		StringTrim( char *, char * ) ;
static void		PutErrLog() ;

/********************************************************************************
*       �O���[�o���ϐ���`                                                      *
*********************************************************************************/
static void		*FILE_KMKMST_DATA ;		/* ���ڃ}�X�^�t�@�C���̃������|�C���^   */
static int		CNT_KMKMST ;			/* ���ڃ}�X�^�t�@�C���̎擾����         */
static void		*FILE_CMTMST_DATA ;		/* �R�����g�}�X�^�̃������|�C���^       */
static int		CNT_CMTMST ;			/* �R�����g�}�X�^�̎擾����             */
static char		WORK_DIR_PATH[512] ;	/* �����f�B���N�g��                     */

/********************************************************************************
*       �\���̒�`                                                              *
*********************************************************************************/
/* �����e�[�u����` */
typedef struct _rireki_table {
	char utkymd[10+1];
	char irino[11+1];
	char iriketflg[1+1];
	char zssdino[1+1];
	char knsgrp[16+1];
	char kmkcd[7+1];
	char sstcd[7+1];
	char krtno[40+1];
	char knjnmkey[60+1];
	char sbtkbn[1+1];
	char age[3+1];
	char agekbn[1+1];
	char bskkbn[4+1];
	char bsklne[4+1];
	char bskgok[6+1];
	char rawdata[20+1];
	char hjkka[24+1];
	char kkacmt1[5+1];
	char kkacmt2[5+1];
	char ijkbnm[1+1];
	char ijkbnf[1+1];
	char ijkbnn[1+1];
	char tbijkbnm[1+1];
	char tbijkbnf[1+1];
	char tbijkbnn[1+1];
	char ksbr[15+1];
	char nbdo[2+1];
	char ykdo[2+1];
	char hkkdh[26+1];
	char ksndh[26+1];
	char oyasstcd[7+1];
} RIREKI_TABLE ;

/* �����O���[�v�擾�p�t�@�C���\���� */
typedef struct _struct_kmkmst {
	char kmkcd[7+1];
	char knsgrp[16+1];
} STRUCT_KMKMST ;

/* �����O���[�v�擾�p�t�@�C���\���� */
typedef struct _struct_cmtmst {
	char cmcd[5+1];
	char kekka[12+1];
} STRUCT_CMTMST ;

/******************************************************************************/
/*  �� �� ��  �Fmain                                                          */
/*  �@�\�T�v  �F���C��                                                        */
/*   ��P���� �F��ƃf�B���N�g��                                              */
/******************************************************************************/
int main ( argc, argv ) 
int		 argc ;
char	*argv[] ;
{
	DIR				*Dirp;					/* �f�B���N�g���|�C���^ */
	struct dirent	*Direntp;				/* �f�B���N�g�\���� */
	char            FileName[1024];			/* �t�@�C���� (��Ɨp) */
	char			*FileDate;				/* �t�@�C���� ���t�i���g�p�j*/
	char			*FileLaboCode;			/* �t�@�C���� ���{�R�[�h */
	char			*FileExtention;			/* �t�@�C���� �T�e���C�g�h�c�{�g���q */
	char			*Empty;					/* �t�@�C���� ���[�m�F�p*/
	char            TargetFileName[1024];	/* �����Ώۃt�@�C�� */

	int				rtc;
	char			InFilePath[512];
	char			OutFilePath[512];

	/* �����`�F�b�N */
	if ( argc < 2 ) {
		printf("�������Ԉ���Ă��܂��B\n"); /* ���P */
		PutErrLog() ;
		return( RTN_NG ) ;
	}

	/* �����̎擾 */
	sprintf( WORK_DIR_PATH, "%s", argv[1]);

	/* �}�X�^�t�@�C���̓��e�擾 */
	rtc = GetKmkFile();
	if( rtc != RTN_OK ){
		PutErrLog() ;
		return( RTN_NG ) ;
	}
	rtc = GetCmtFile();
	if( rtc != RTN_OK ){
		PutErrLog() ;
		free( FILE_KMKMST_DATA ) ;
		return( RTN_NG ) ;
	}

	/* */
	Dirp = opendir( WORK_DIR_PATH ) ;
	while(( Direntp = readdir( Dirp )) != NULL ){
		sprintf( FileName, "%s", Direntp->d_name );
		sprintf( TargetFileName,"%s%s", FILE_ID, ".dat" );
		/* �t�@�C�������g���q���Z���ꍇ�̓X�L�b�v */
		if( strlen( FileName ) <= strlen( TargetFileName ) ) continue;
		/* �t�@�C�����𕪊� */
		FileDate = strtok( FileName, "_");
		if( FileDate == NULL ) continue; 
		FileLaboCode = strtok(NULL, "_");
		if( FileLaboCode == NULL ) continue; 
		FileExtention = strtok(NULL, "_");
		if( FileExtention == NULL ) continue; 
		Empty = strtok(NULL, "_");
		if( Empty != NULL ) continue;			/* �g���q�̌�ɉ����t�@�C���������݂��Ă���ꍇ�͂m�f */
		/* �g���q�� .dat �̃t�@�C���A���A���T�e���C�g�h�c�̃t�@�C���̂ݏ��� */
		if( strncmp( FileExtention , TargetFileName, strlen( TargetFileName ) ) == 0 ){
			sprintf(InFilePath, "%s/%s", WORK_DIR_PATH, Direntp->d_name ) ;
			sprintf(OutFilePath,"%s/CNV_%s", WORK_DIR_PATH, Direntp->d_name ) ;
			printf("�t�@�C���R���o�[�g�������J�n���܂��B [%s] -> [%s]\n", InFilePath, OutFilePath ) ; /* ���P */
			/* �t�@�C���� Insert �`���ɃR���o�[�g���� */
			rtc = mainFunction( InFilePath, OutFilePath, FileLaboCode ) ;
			if( rtc != RTN_OK ){
				printf("�t�@�C���R���o�[�g�Ɏ��s���܂����B[%s] -> [%s]\n", InFilePath, OutFilePath ) ; /* ���P */
				PutErrLog() ;
				free( FILE_KMKMST_DATA ) ;
				free( FILE_CMTMST_DATA ) ;
				closedir( Dirp ) ;
				return( RTN_NG ) ;
			}
			printf("�t�@�C���R���o�[�g�ɐ������܂����B[%s] -> [%s]\n", InFilePath, OutFilePath ) ; /* ���P */
		}
	}

	free( FILE_KMKMST_DATA ) ;
	free( FILE_CMTMST_DATA ) ;
	closedir( Dirp );
	return( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FmainFunction                                                  */
/*  �@�\�T�v  �F���C��                                                        */
/*   ��P���� �F�����t�@�C�����i�t���p�X�j                                    */
/*   ��Q���� �F�o�̓t�@�C�����i�t���p�X�j                                    */
/*   ��R���� �F���{�R�[�h                                                    */
/******************************************************************************/
int mainFunction( InFilePath, OutFilePath, LaboCode )
char *InFilePath;
char *OutFilePath;
char *LaboCode;
{
	char buf[1024];
	char field[1024];
	int  field_no; 
	char *p;
    FILE *in_fp = NULL;
    FILE *out_fp = NULL;

	char namekey[128];
	char knskka1[128];
	char knskka2[128];
	char kka2kbn[128]; 
	char kkahskcd[128];
	char hjkka[128];

	RIREKI_TABLE RirekiTable;

	/* �ϊ��Ώۃt�@�C�� OPEN */
	if(( in_fp = fopen(InFilePath, "r")) == NULL ){ 
		printf("�ϊ��Ώۃt�@�C���̃I�[�v���Ɏ��s���܂����B[%s]\n", InFilePath) ; /* ���P */
		return( RTN_NG );
	}
	/* �o�̓t�@�C�� OPEN */
	if ((out_fp = fopen(OutFilePath, "w")) == NULL){
		printf("�o�̓t�@�C���̃I�[�v���Ɏ��s���܂����B[%s]\n", OutFilePath) ; /* ���P */
		return( RTN_NG );
	}

	/* �ϊ��Ώۃt�@�C�� �s�������[�v */
    while (fgets(buf, sizeof(buf), in_fp)) {
		field_no = 0; 
        // �J�������ɐ؂�o���āA�\���̂ɓ����
        for (p = buf; *p; ) {
			p = SetValue(p, field, sizeof(field));
/*
			printf("SetValue OK [%s] [%d]\n", field, field_no); 
*/
			switch (field_no){
				case 0 :
					snprintf(RirekiTable.utkymd, 11, "%s", field);
					break ;
				case 1 :
					snprintf(RirekiTable.irino, 12, "%s", field);
					break ;
				case 2 :
					snprintf(RirekiTable.sstcd, 8, "%s", field);
					snprintf(RirekiTable.oyasstcd, 8, "%s", field);
					break ;
				case 3 :
					snprintf(RirekiTable.krtno, 41, "%s", field);
					break ;
				case 4 :
					NameKeyMake(namekey, field, strlen(field)); 
					snprintf(RirekiTable.knjnmkey, 61, "%s", namekey);
					break ;
				case 5 :
					snprintf(RirekiTable.sbtkbn, 2, "%s", field);
					break ;
				case 8 :
					snprintf(RirekiTable.age, 4, "%s", field);
					break ;
				case 9 :
					snprintf(RirekiTable.agekbn, 2, "%s", field);
					break ;
				case 11 :
					snprintf(RirekiTable.hkkdh, 11, "%s", field);
					break ;
				case 16 :
					snprintf(RirekiTable.kmkcd, 8, "%s", field);
					break ;
				case 17 :
					snprintf(knskka1, 13, "%s", field);
					break ;
				case 18 :
					snprintf(knskka2, 13, "%s", field);
					break ;
				case 19 :
					snprintf(kka2kbn, 2, "%s", field);
					break ;
				case 20 :
					snprintf(kkahskcd, 4, "%s", field);
					break ;
				case 21 :
					snprintf(RirekiTable.kkacmt1, 6, "%s", field);
					break ;
				case 22 :
					snprintf(RirekiTable.kkacmt2, 6, "%s", field);
					break ;
				case 23 :
					snprintf(RirekiTable.ijkbnm, 2, "%s", field);
					break ;
				case 24 :
					snprintf(RirekiTable.ijkbnf, 2, "%s", field);
					break ;
				case 25 :
					snprintf(RirekiTable.ijkbnn, 2, "%s", field);
					break ;
			}
			++field_no; 
        }
		/* ���ʂ̃R���p�[�g */
		ConvKekka(knskka1, knskka2, kka2kbn[0], kkahskcd, hjkka);
		snprintf(RirekiTable.hjkka, 25, "%s", hjkka);
		/* �f�t�H���g�l�̐ݒ� */
		snprintf(RirekiTable.knsgrp, 17, "%s", "                 ");
		SetKnsgrp(RirekiTable.kmkcd, RirekiTable.knsgrp);
		snprintf(RirekiTable.rawdata, 21, "%s", "                    ");
		snprintf(RirekiTable.iriketflg, 2, "%s", " ");
		snprintf(RirekiTable.zssdino, 2, "%s", "0");
		snprintf(RirekiTable.bskkbn, 5, "%s", LaboCode);
		snprintf(RirekiTable.bsklne, 5, "%s", "    ");
		snprintf(RirekiTable.bskgok, 7, "%s", "      ");
		snprintf(RirekiTable.tbijkbnm, 2, "%s", " ");
		snprintf(RirekiTable.tbijkbnf, 2, "%s", " ");
		snprintf(RirekiTable.tbijkbnn, 2, "%s", " ");
		snprintf(RirekiTable.ksbr, 16, "               ");
		snprintf(RirekiTable.nbdo, 3, "  ");
		snprintf(RirekiTable.ykdo, 3, "  ");
		DateGetToday(RirekiTable.ksndh);
/*		
		printf("\"%-10s\",\"%-11s\",\"%-1s\",%-1s,\"%-16s\",\"%-7s\",\"%-7s\",\"%-40s\",\"%-60s\",\"%-1s\",\"%-3s\",\"%-1s\",\"%-4s\",\"%-4s\",\"%-6s\",\"%-20s\",\"%-24s\",\"%-5s\",\"%-5s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-15s\",\"%-2s\",\"%-2s\",\"%-10s%-16s\",\"%-26s\",\"%-7s\"\n",
						RirekiTable.utkymd, RirekiTable.irino, RirekiTable.iriketflg, RirekiTable.zssdino, RirekiTable.knsgrp,
						RirekiTable.kmkcd, RirekiTable.sstcd, RirekiTable.krtno, RirekiTable.knjnmkey, RirekiTable.sbtkbn,
						RirekiTable.age, RirekiTable.agekbn, RirekiTable.bskkbn, RirekiTable.bsklne, RirekiTable.bskgok,
						RirekiTable.rawdata, RirekiTable.hjkka, RirekiTable.kkacmt1, RirekiTable.kkacmt2, RirekiTable.ijkbnm,
						RirekiTable.ijkbnf, RirekiTable.ijkbnn, RirekiTable.tbijkbnm, RirekiTable.tbijkbnf, RirekiTable.tbijkbnn,
						RirekiTable.ksbr, RirekiTable.nbdo, RirekiTable.ykdo, RirekiTable.hkkdh, DEF_STAMP, RirekiTable.ksndh,
						RirekiTable.oyasstcd);
*/
		/* �R���o�[�g���ʏo�� */
		fprintf(out_fp, "\"%-10s\",\"%-11s\",\"%-1s\",%-1s,\"%-16s\",\"%-7s\",\"%-7s\",\"%-40s\",\"%-60s\",\"%-1s\",\"%-3s\",\"%-1s\",\"%-4s\",\"%-4s\",\"%-6s\",\"%-20s\",\"%-24s\",\"%-5s\",\"%-5s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-1s\",\"%-15s\",\"%-2s\",\"%-2s\",\"%-10s%-16s\",\"%-26s\",\"%-7s\"\n",
						RirekiTable.utkymd, RirekiTable.irino, RirekiTable.iriketflg, RirekiTable.zssdino, RirekiTable.knsgrp,
						RirekiTable.kmkcd, RirekiTable.sstcd, RirekiTable.krtno, RirekiTable.knjnmkey, RirekiTable.sbtkbn,
						RirekiTable.age, RirekiTable.agekbn, RirekiTable.bskkbn, RirekiTable.bsklne, RirekiTable.bskgok,
						RirekiTable.rawdata, RirekiTable.hjkka, RirekiTable.kkacmt1, RirekiTable.kkacmt2, RirekiTable.ijkbnm,
						RirekiTable.ijkbnf, RirekiTable.ijkbnn, RirekiTable.tbijkbnm, RirekiTable.tbijkbnf, RirekiTable.tbijkbnn,
						RirekiTable.ksbr, RirekiTable.nbdo, RirekiTable.ykdo, RirekiTable.hkkdh, DEF_STAMP, RirekiTable.ksndh,
						RirekiTable.oyasstcd);

    }
    fclose(in_fp);
    fclose(out_fp);

    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FSetKnsgrp                                                     */
/*  �@�\�T�v  �F�����O���[�v��ݒ肷��                                        */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int SetKnsgrp(char *kmkcd, char *knsgrp)
{
	int				cnt ;
	STRUCT_KMKMST	*mp ;			/* �������[�|�C���^�[ */
		
	mp = ( STRUCT_KMKMST * )FILE_KMKMST_DATA;
	for( cnt=0 ; cnt<CNT_KMKMST ; cnt++ ){
        if( strcmp( kmkcd, mp[cnt].kmkcd ) == 0 ){
            snprintf( knsgrp, 18, "%s", mp[cnt].knsgrp ) ;
            break ;
        }
	}

	return( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FConvKekka                                                     */
/*  �@�\�T�v  �F�\�����ʂ̎擾                                                */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar    *knskka1;                                             */
/*   ��Q���� �Fchar    *knskka2;                                             */
/*   ��R���� �Fchar    kka2kbn;                                              */
/*   ��S���� �Fchar    *kkahskcd;                                            */
/*   ��T���� �Fchar    *hjkka;                                               */
/*  �o    ��  �F                                                              */
/*   ��T���� �Fchar    *hjkka;                                               */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int ConvKekka(char *knskka1, char *knskka2, char kka2kbn, char *kkahskcd, char *hjkka)
{
	char    buf_kka[256] ;
	char    buf_hsk[256] ;
	int     num_cmt ;

	memset( buf_kka, 0x00, sizeof( buf_kka )) ;
	memset( buf_hsk, 0x00, sizeof( buf_hsk )) ;
    if( kka2kbn == '0' ){
		/* ���ʂQ�敪���O�̏ꍇ�A�R�����g���� */
		StringTrim( buf_kka, knskka2 ) ;
		num_cmt = atoi( buf_kka ) ;
		snprintf( hjkka, 25, "*%d", num_cmt ) ;
		/* �R�����g�}�X�^�Ɍ��ʒl���ݒ肳��Ă���ꍇ�͂���ɒu�������� */
		/* �ݒ肳��Ă��Ȃ��ꍇ�͂��̂܂�                               */
		ConvCmtKekka( buf_kka, hjkka);
	} else {
		StringTrim( buf_kka, knskka1 ) ;
		snprintf( hjkka, 25, "%s", buf_kka ) ;
	}
    return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FConvCmtKekka                                                  */
/*  �@�\�T�v  �F�R�����g�}�X�^�Ɍ��ʒl���ݒ肳��Ă���ꍇ�͂���ɒu��������  */
/*              �ݒ肳��Ă��Ȃ��ꍇ�͂��̂܂�                                */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int ConvCmtKekka(char *cmcd, char *hjkka)
{
	int				cnt ;
	char			buf_kka[256] ;
	char 			buf_cmcd[256] ;
	STRUCT_CMTMST	*mp ;			/* �������[�|�C���^�[ */
		
	mp = ( STRUCT_CMTMST * )FILE_CMTMST_DATA;
	for( cnt=0 ; cnt<CNT_CMTMST ; cnt++ ){
		StringTrim( buf_cmcd, mp[cnt].cmcd ) ;
        if( strcmp( cmcd, buf_cmcd ) == 0 ){
			StringTrim( buf_kka, mp[cnt].kekka ) ;
            snprintf( hjkka, 25, "%s", buf_kka ) ;
            break ;
        }
	}

	return( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FGetKmkFile                                                    */
/*  �@�\�T�v  �F�����O���[�v�擾�p�t�@�C���̓��e�擾                          */
/*              �}�X�^�t�@�C���͓����ŏo�͂��Ă����                          */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int GetKmkFile()
{
	int				rtc;
	int				cnt;
	char			buf[1024];
	char			Path[1024];
	char			field[1024];
	int				field_no; 
	char			*p;
    FILE			*fp = NULL;
	STRUCT_KMKMST	*mp;        /* �������[�|�C���^�[ */

	sprintf( Path, "%s/%s", WORK_DIR_PATH, FILE_KMKMST ) ;
	fp = fopen( Path, "r");
	if( fp == NULL ) {
		printf("�����O���[�v�擾�p�t�@�C���̃I�[�v���Ɏ��s���܂����B[%s]\n", Path) ; /* ���P */
		return( RTN_NG );
	}

	CNT_KMKMST = 0;
	memset( buf,0,1024 );
	while( fgets( buf, 1024, fp ) != NULL ) {
		++CNT_KMKMST;
	}

	/* �������̈�̊m�� */
	FILE_KMKMST_DATA = ( STRUCT_KMKMST * )malloc(sizeof( STRUCT_KMKMST ) * CNT_KMKMST );
	if( FILE_KMKMST_DATA == NULL ){
		printf("�������̈�̊m�ۂɎ��s���܂����B[GetKmkFile]\n" ) ; /* ���P */
		fclose ( fp ) ;
		return( RTN_NG );
	}
	rewind(fp);

	memset(( char * )FILE_KMKMST_DATA,0x00, ( sizeof( STRUCT_KMKMST ) * CNT_KMKMST ));

	/* �������̐擪�|�C���^�[ */
	mp = ( STRUCT_KMKMST * )FILE_KMKMST_DATA;
	cnt = 0 ;
	/* �ϊ��Ώۃt�@�C�� �s�������[�v */
    while (fgets(buf, sizeof(buf), fp)) {
		field_no = 0; 
        /* �J�������ɐ؂�o���āA�\���̂ɓ���� */
        for (p = buf; *p; ) {
			p = SetValue(p, field, sizeof(field));
			switch (field_no){
				case 0 :
					snprintf(mp[cnt].kmkcd, 8, "%s", field) ;
					break ;
				case 1 :
					snprintf(mp[cnt].knsgrp, 17, "%s", field) ;
					break ;
			}
			field_no++;
		}
		cnt++;
	}
	fclose ( fp ) ;
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FGetCmtFile                                                    */
/*  �@�\�T�v  �F�R�����g�}�X�^�擾�p�t�@�C���̓��e�擾                        */
/*              �}�X�^�t�@�C���͓����ŏo�͂��Ă����                          */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int GetCmtFile()
{
	int				rtc;
	int				cnt;
	char			buf[1024];
	char			Path[1024];
	char			field[1024];
	int				field_no; 
	char			*p;
    FILE			*fp = NULL;
	STRUCT_CMTMST	*mp;        /* �������[�|�C���^�[ */

	sprintf( Path, "%s/%s", WORK_DIR_PATH, FILE_CMTMST ) ;
	fp = fopen( Path, "r") ;
	if( fp == NULL ) {
		printf("�R�����g�}�X�^�擾�p�t�@�C���̃I�[�v���Ɏ��s���܂����B[%s]\n", Path) ; /* ���P */
		return ( RTN_NG ) ;
	}

	CNT_CMTMST = 0;
	memset( buf,0,1024 );
	while( fgets( buf, 1024, fp ) != NULL ) {
		++CNT_CMTMST;
	}

	/* �������̈�̊m�� */
	FILE_CMTMST_DATA = ( STRUCT_CMTMST * )malloc(sizeof( STRUCT_CMTMST ) * CNT_CMTMST );
	if( FILE_CMTMST_DATA == NULL ){
		printf("�������̈�̊m�ۂɎ��s���܂����B[GetCmtFile]\n" ) ; /* ���P */
		fclose ( fp ) ;
		return( RTN_NG );
	}
	rewind(fp);

	memset(( char * )FILE_CMTMST_DATA,0x00, ( sizeof( STRUCT_CMTMST ) * CNT_CMTMST ));

	/* �������̐擪�|�C���^�[ */
	mp = ( STRUCT_CMTMST * )FILE_CMTMST_DATA;
	cnt = 0 ;
	/* �ϊ��Ώۃt�@�C�� �s�������[�v */
    while (fgets(buf, sizeof(buf), fp)) {
		field_no = 0; 
        /* �J�������ɐ؂�o���āA�\���̂ɓ���� */
        for (p = buf; *p; ) {
			p = SetValue(p, field, sizeof(field));
			switch (field_no){
				case 0 :
					snprintf(mp[cnt].cmcd, 6, "%s", field) ;
					break ;
				case 1 :
					snprintf(mp[cnt].kekka, 13, "%s", field) ;
					break ;
			}
			field_no++;
		}
		cnt++;
	}
	fclose ( fp ) ;
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ��  �FNameKeyMake                                                   */
/*  �@�\�T�v  �F���Җ��L�[�쐬                                                */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fchar    kan_name[]; : S-JIS ���҃J�i����                      */
/*   ��Q���� �Fint     len;        : S-JIS ���҃J�i����length                */
/*  �o    ��  �F                                                              */
/*   ��P���� �Fchar    name_key[]; : S-JIS ���Җ��L�[                        */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
int		NameKeyMake( name_key, kan_name, len )
char	name_key[];		/* [O] ���Җ��L�[ */
char	kan_name[];		/* [I] ���Җ� */
int		len;			/* [I] ���Җ�length */
{
	int				i,j;
	unsigned char	name[61];
	unsigned char	keyj[61];

	memset( keyj, 0x00, sizeof( keyj ));
	strncpy( name, kan_name, len );
	j = 0;
	for	(i=0;i<len;i++) {
		if( isdigit( name[i] )){
			;
		} else {
			keyj[j]  =  name[i];
			j++;
		}
	}

	strcpy( name_key, keyj );

	return( RTN_OK );
}

/******************************************************************************/
/*  �� �� ��  �FSetValue                                                      */
/*  �@�\�T�v  �F�b�r�u�̓Ǎ�                                                  */
/*              ��s�̒��̃f�[�^�� ,(�J���})�ŋ�؂�B�s�̏I��͉��s�B        */
/*              �f�[�^���J���}��_�u���N�H�[�g���܂ޏꍇ��                    */
/*              "(�_�u���N�H�[�g)�ň͂ށB                                     */
/*              �f�[�^�̒��̃_�u���N�H�[�g�͂����                            */
/*              �_�u���N�H�[�g2��("")�Œu��������B                           */
/******************************************************************************/
char *SetValue(char *p, char *field, int size) {
    if (*p == '"') {
        /* �����ł̃C���N�������g��
         * �Ō�̃C���N�������g�ł̓|�C���^���{�Q�ɂȂ�(�]�����ꂽ�ꍇ�̂�)
         * *p != '"'��0�ɂȂ����ꍇ�̂� *(++p) == '"'�����s�����
         * ����̓_�u���N�H�[�g�A���̎��̑΍�
         */
        while (*(++p) && *p != '\n' && (*p != '"' || *(++p) == '"')) {
            if (--size > 0) {
                *(field++) = *p;
            }
        }
    }
    // �����̕�����""�ň͂܂�Ă��Ȃ��������ʂ�悤�ɂȂ��Ă���
    for ( ; *p && *p != ',' && *p != '\n'; p++) {
        if (--size > 0) {
            *(field++) = *p;
        }
    }
    *field = '\0';
    return *p ? (p + 1) : p;
}

/******************************************************************************/
/*      �֐���          �FDateGetToday()                                      */
/*      �@�\�T�v        �F�V�X�e�����t���擾����                              */
/*      ����                                                                  */
/*       ��P����       �Fchar* date DB2�^�C���X�^���v�^�̓��t�̕�����        */
/*      �o��                                                                  */
/*       ��P����       �Fchar* date �V�X�e�����t(DB2�^�C���X�^���v�^)        */
/*       ����FTRUE                                                           */
/*       �ُ�FFALSE                                                          */
/******************************************************************************/
int DateGetToday(char *date)
{
	time_t now = time(NULL);
    struct tm *tm;

	time(&now);
    tm = localtime(&now);
	sprintf( date, "%4.4d-%2.2d-%2.2d-%2.2d.%2.2d.%2.2d.000000", 
					tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec ) ;

    return( RTN_OK );
}

/******************************************************************************/
/*      �֐���          �FStringTrim()                                        */
/*      �@�\�T�v        �F�w�蕶����̑O��̃X�y�[�X����菜����              */
/*                        ��������R�s�[����                                  */
/*      ����                                                                  */
/*       ��Q����       �Fchar* �g�����O�̕�����                              */
/*      �o��                                                                  */
/*       ��P����       �Fchar* �g������̕�����                              */
/******************************************************************************/
void StringTrim(char *dst, char *src) {
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

	return ;
}

/******************************************************************************/
/*  �� �� ��  �FPutErrLog                                                     */
/*  �@�\�T�v  �F�R�����g�}�X�^�擾�p�t�@�C���̓��e�擾                        */
/*  ��    ��  �F                                                              */
/*  �o    ��  �F                                                              */
/*  ���A���  �FRTN_OK       ����I��                                         */
/*            �FRTN_NG       �ُ�I��                                         */
/******************************************************************************/
void PutErrLog()
{
	int				rtc;
	char			Path[1024];
	char			*p;
    FILE			*fp = NULL;

	sprintf( Path, "%s/%sRirekiConv.log", LOG_DIR, NAME_ERRLOG ) ;
	fp = fopen( Path, "w") ;
	if( fp == NULL ) {
		printf("�G���[���M�p���O�t�@�C���̃I�[�v���Ɏ��s���܂����B[%s]\n", Path) ; /* ���P */
		return ;
	}

	fprintf( fp, "ERROR : �����t�@�C���̃R���o�[�g�����ŃG���[���������܂����B\n" ) ;

	fclose ( fp ) ;
	return ;
}
