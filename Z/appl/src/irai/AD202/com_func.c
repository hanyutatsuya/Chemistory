/******************************************************************************/
/*   �a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/*   �V�X�e�����F������V�X�e��                                               */
/*   �t�@�C�����Fcom_func.c                                                   */
/*   �T      �v�F���ҏ��W�J                                                 */
/*	 OS        �FSUSE LINUX Enterprise Server 9 (s390x)                       */
/*                 - Kernel 2.6.5-7.139-s390x (2).                            */
/*   ����      �FDB2/C                                                        */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/02/08     INTEC.INC      CREATE                             */
/*  1.01     2006/05/01     INTEC.INC      OS EUC->SJIS�Ή�                   */
/******************************************************************************/

/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include <sys/types.h>
#include <unistd.h>
#include "AD202.h"

/*:KH-------------------------------------------------------------------------*/
/*:K  �֐���   : EnvRef                                                       */
/*----------------------------------------------------------------------------*/
/*:A  �@�\�T�v : �����ϐ���W�J����                                         */
/*----------------------------------------------------------------------------*/
/*:I  ����     : char    *src_cp  : �W�J�O������                              */
/*:O  �o��     : ����             : ����                                      */
/*:R  �߂�l   : char *           : �W�J�㕶����                              */
/*:C  ���L���� :                                                              */
/*----------------------------------------------------------------------------*/
char    *EnvRef( src_cp )
char		*src_cp;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];	// �֐�����
static char	value[256];     			/* �W�J�㕶���� */
    char	*dst_cp;        			/* �W�J�㕶���� */
    char	buf[256];       			/* �����ϐ� */
    char	*env_cp;        			/* �����ϐ� */

	strcpy( func_nm, "EnvRef" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    dst_cp = value;
    while( *src_cp != 0 ) {
        if( *src_cp == '$' ) {
            env_cp = buf;
            *env_cp++ = *src_cp++;
            while( *src_cp != 0 
                && *src_cp != ' ' && *src_cp != '\t' 
                && *src_cp != '$' && *src_cp != '/' && *src_cp != '\\' ) {
                *env_cp++ = *src_cp++;
            }
            *env_cp = 0;
            if( (env_cp = getenv( &buf[1] )) == NULL ) {
                env_cp = buf;
            }
            while( *env_cp != 0 ) {
                *dst_cp++ = *env_cp++;
            }
        } else {
            *dst_cp++ = *src_cp++;
        }
    }
    *dst_cp = 0;

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return( value );
}
/*:KH-------------------------------------------------------------------------*/
/*:K  �֐���   : GetIniFile                                                     */
/*----------------------------------------------------------------------------*/
/*:A  �@�\�T�v : �ݒ�t�@�C������l���擾����                                 */
/*----------------------------------------------------------------------------*/
/*:I  ����     : char    *section : �Z�N�V������                              */
/*             : char    *key     : �L�[��                                    */
/*             : char    *profile : �ݒ�t�@�C����                            */
/*:O  �o��     : ����             : ����                                      */
/*:R  �߂�l   : char *           : �L�[�l�i������j                          */
/*:C  ���L���� :                                                              */
/*----------------------------------------------------------------------------*/
char	*GetIniFile( section, key, profile )
char		*section;
char		*key;
char		*profile;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		// �֐�����
static char	value[256];						/* ���ϐ��l */
    FILE	*fp;            				/* FILE�|�C���^ */
    char	buf[256];       				/* �Ǎ��݃o�b�t�@ */
    int		sec_len;        				/* �Z�N�V�������� */
    int		key_len;        				/* �L�[���� */
    int		value_len;      				/* �L�[�l�� */
    int		i;              				/* �Y���� */

	strcpy( func_nm, "GetIniFile" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

    /*==========================*/
    /*  �ݒ�t�@�C���̃I�[�v��  */
    /*==========================*/
    if(( fp = fopen( EnvRef( profile ), "rt" )) == NULL ) {
        printf( "FOPEN ERROR:%s\n", profile );
        return( NULL );
    }

    /*==================*/
    /*  �Z�N�V��������  */
    /*==================*/
    sec_len = strlen( section );
    key_len = 0;
    buf[sizeof( buf ) - 1] = 0;
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) {
            for( i++; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( strncmp( &buf[i], section, sec_len ) == 0 ) {
                for( i += sec_len; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                if( buf[i] == ']' ) {
                    /*================*/
                    /* ���������ꍇ */
                    /*================*/
                    key_len = strlen( key );
                    break;
                }
            }
        }
    }
    /*======================*/
    /* ������Ȃ������ꍇ */
    /*======================*/
    if( key_len <= 0 ) {
        fclose( fp );
        return( NULL );
    }

    /*============*/
    /*  �L�[����  */
    /*============*/
    while( fgets( buf, sizeof( buf ) - 1, fp ) != NULL ) {
        for( i = 0; i < sizeof( buf ); i++ ) {
            if( buf[i] != ' ' && buf[i] != '\t' ) break;
        }
        if( buf[i] == '[' ) break;
        if( strncmp( &buf[i], key, key_len ) == 0 ) {
            for( i += key_len; i < sizeof( buf ); i++ ) {
                if( buf[i] != ' ' && buf[i] != '\t' ) break;
            }
            if( buf[i] == '=' ) {
                /*================*/
                /* ���������ꍇ */
                /*================*/
                for( i++; i < sizeof( buf ); i++ ) {
                    if( buf[i] != ' ' && buf[i] != '\t' ) break;
                }
                strcpy( value, &buf[i] );
                value_len = strlen( value );
                if( value[value_len - 1] == '\n' ) {
                    value[value_len - 1] = 0;
                }
                fclose( fp );
                return( EnvRef( value ) );
            }
        }
    }
    /*======================*/
    /* ������Ȃ������ꍇ */
    /*======================*/
    fclose( fp );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
    return( NULL );
}

/******************************************************************************/
/*  �� �� ��  �FDaemonCheckProc                                               */
/*  �@�\�T�v  �F�f�[�����d���N���`�F�b�N                                      */
/*  ��    ��  �F                                                              */
/*   ��P���� �Fint		argc	: �p�����^��                                  */
/*   ��Q���� �Fchar	*argv[]	: �p�����^���X�g                              */
/*  �o    ��  �F�Ȃ�                                                          */
/*  ���A���  �F INT                                                          */
/*               RTN_OK     : ����                                            */
/*               RTN_NG     : ���s                                            */
/******************************************************************************/
int		DaemonCheckProc( argc, argv )
int			argc;
char		*argv[];
{
	int		ret = RTN_OK;			/* ���A�l */
	int		cnt;					/* �J�E���g */
	char	func_nm[MYAPP_LEN_FNCNM+1];			/* �֐�����	 */
	char	buf[128];				/* �Ǎ��݃o�b�t�@ */
	char	cmd[128];				/* �R�}���h */
	char	tmp[80];				/* ��ƃt�@�C�� */
	FILE	*tfp;					/* FILE�|�C���^ */

	strcpy( func_nm, "DaemonCheckProc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* �R�}���h���s */
	sprintf( tmp, "/tmp/%s.%d.tmp", stcPRM.myp_exefile, getpid() );
	sprintf( cmd, "ps -e | grep %s | grep -v grep | wc > ", stcPRM.myp_exefile);
	strcat( cmd, tmp );
	system( cmd );

	// TRACE
	sprintf( G_msg, "�d���N���`�F�b�N�ŃR�}���h[%s]�����s", cmd );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	/* �N�����̓Ǎ��� */
	if( (tfp = fopen( tmp, "r" )) == NULL ) {
		// ERROR
		sprintf( G_msg, 
			"�d���N���`�F�b�N�R�}���h���ʃt�@�C�� �I�[�v���G���[", tmp );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

		return	RTN_NG;
	}
	if( fgets( buf, sizeof( buf ), tfp ) == NULL ) {
		strcpy( buf, "0");
		// ERROR
		sprintf( G_msg, 
			"�d���N���`�F�b�N�Ŏ��s�����R�}���h���ʂ��擾�ł��Ȃ�" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );
	}
	fclose( tfp );
	unlink( tmp );

	/* �N�����`�F�b�N */
	cnt = 0;
	sscanf( buf, "%d", &cnt );

	// TRACE
	sprintf( G_msg, "�d���N���`�F�b�N��%s"
		, (cnt>1)?"�d�����Ă���" :"�d�����Ă��Ȃ�" );
	LogOut( LT_TRC, LX_NON, LE_NON, G_msg, func_nm, __FILE__, __LINE__ );

	if( cnt > 1 ) {
		return( RTN_NG );
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return RTN_OK;
}

/******************************************************************************/
/*  �� �� ��  �Fsj2euc                                                        */
/*  �@�\�T�v  �FS-JIS => EUC �ϊ�                                             */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char	bufin[]		: ���͕����� (SJIS)                       */
/*   ��Q���� �F int	len			: �o�͕�����                            */
/*  �o    ��  �F                                                              */
/*   ��P���� �F char	bufot[]		: �o�͕����� (EUC)                        */
/*  ���A���  �F RTN_OK				: ����I��(�Ǎ��T�C�Y)                    */
/*               RTN_NG				: ���s                                    */
/******************************************************************************/
int     sj2euc( bufot, bufin, len )
char		bufot[];	
char		bufin[];	
int			len;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int	ret;
	size_t  w_szi;
	size_t  szi;
	size_t  szo;
	char	str_in[MYAPP_MAX_CHAR+1];
	char	str_ot[MYAPP_MAX_CHAR+1];
	char	*pstr_in = str_in;
	char	*pstr_ot = str_ot;
	
	strcpy( func_nm, "sj2euc" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// 1.01 SJIS ���Ŏ��s���邽�߃R�[�h�ϊ��͍s��Ȃ�
    memcpy( bufot, bufin, len - 1 );
    return( RTN_OK );

	szi = w_szi = strlen( bufin );
	szo = sizeof( str_ot ) - 1;
	memset( str_in, 0x00, sizeof( str_in ) );
	memset( str_ot, 0x00, sizeof( str_ot ) );
	memcpy( str_in, bufin, szi );
	ret = iconv( G_ic, &pstr_in, &szi, &pstr_ot, &szo );

	// ERROR
	if( ret == -1 ){
		sprintf( G_err, "%d", errno );
		sprintf( G_msg, "[%d]byte�������[%d]byte�ڃR�[�h�ϊ�����"
				"�G���[���������܂����B"
				,w_szi, w_szi - szi );
		EditCsvMsg( G_msg );
		LogOut( LT_TRC, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
	}
	memcpy( bufot, str_ot, len - 1 );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �Fto_csv                                                        */
/*  �@�\�T�v  �FCSV�`���̃f���~�b�^�t��                                       */
/*            �Fcol��rtrim��A'col'| �ƕҏW���� buf �Ɍq���Ė߂�              */
/*  ��    ��  �F                                                              */
/*   ��P���� �F char   delim[];  : �f���~�b�^                                */
/*   ��Q���� �F char   buf[];    : �t���捀��                                */
/*   ��R���� �F char   col[];    : �f���~�b�^�����ĕt�����鍀��            */
/*   ��S���� �F int    len;      : �t���捀�ڍő�T�C�Y                      */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK             : ����                                    */
/*               RTN_NG             : �G���[                                  */
/******************************************************************************/
int		to_csv( delim, len, msg, col )
char		*delim;
int			len;
char		*msg;
char		*col;
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int		wc, bwc;
	int		ret=RTN_OK;

	strcpy( func_nm, "to_csv" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	// rtrim( col )
	for( wc=strlen( col ); wc > 1; --wc ){
		if( col[wc - 1] != ' ' ){
			break;
		}
	}

	// ���O��MSG�̈���傫���ꍇ�͏����𔲂���
	bwc=strlen(msg);
	if( wc + bwc >= len -3 ){
		EditCsvMsg( G_msg );
		LogOut( LT_WRN, LX_NON, LE_NON, "csv�ҏW�ɂė̈�𒴂��܂����B"
				, func_nm, __FILE__, __LINE__ );
		return( RTN_NG );
	}

	// EDIT
	msg[bwc]='\'';
	memcpy(&msg[bwc+1],col,wc);
	msg[bwc+wc+1]='\'';

	if( &delim[0] != 0x00 ){
		msg[bwc+wc+2]=delim[0];
		msg[bwc+wc+3]='\0';
	} else {
		msg[bwc+wc+2]='\0';
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_OK );
}

/*****************************************************************
	����  :	�a��E����ϊ�

	�T�v  :	�a��琼��ɕϊ�����
		���ފǗ�Ͻ��Ɍ����̊Ǘ������Ă���
	���Ӂ@: �����ƕҏW�O�̔N���������������Ƃ��O��

	�\��  :	char	*Lwa_ymd( ymd10, gengou, ymd )
	����  :	(out)	char	ymd10[];	�ҏW��(YYYY/MM/DD)
		(in)	char	gengou[];	
			����
			' ':����
			 M :���� "1868/09/08", "1912/07/29"
			 T :�吳 "1912/07/30", "1926/12/24", "T"
			 S :���a "1926/12/25", "1989/01/07", "S"
	                 H :���� "1989/01/08", "9999/12/31", "H"
		(in)	char	ymd[];		�ҏW�O(YYYYMMDD)

	��-ݒl:	ymd10�̐擪���ڽ
		ymd10=NULL�̏ꍇ�͓����ر�̕�����擪���ڽ
*****************************************************************/
int		wa2ymd( ymd10, gengou, ymd )
char		ymd10[];					/* �ҏW��(YYYY/MM/DD)	*/
char		gengou[];					/* ����			*/
char		ymd[];						/* �ҏW�O(YYYYMMDD)	*/
{
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/
	int		ret;

	char	wk_ymd8[10];
	char	wk_yy[10];
	char	wk_mmdd[10];
	int	i,j,k;
	int	add_yy;

	/* �����ݒ�	*/
	strcpy( func_nm, "wa2ymd" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	/* ����Ȃ�Ώ����I�� */
	if( gengou[0] == ' ' ){
		sprintf( ymd10,	"%.4s-%.2s-%.2s",
			ymd, &ymd[4], &ymd[6] );
		return( RTN_OK );
	}

	/* ���t�̊l��	*/
	strcpy( wk_yy,   "0000" );
	strcpy( wk_mmdd, "0000" );
	j = k = strlen( wk_mmdd ) - 1;
	for( i = strlen( ymd ) - 1; i >=0 ; --i){
		if( ymd[i] >= '0' && ymd[i] <= '9' ){
			if( j >= 0 ){
				wk_mmdd[j] = ymd[i];
				--j;
				continue;
			}
			if( k >= 0 ){
				wk_yy[k] = ymd[i];
				--k;
				continue;
			} 
			break;
		}
	}
	/* �����̊J�n�N�������߂�	*/
		/* �{����DB���]�܂����B�Ƃ肠����ON */
		switch  ( gengou[0] ) {
			case 'M' :		/* ���� */
				add_yy = 1868;
				break;
			case 'T' :		/* �吳 */
				add_yy = 1912;
				break;
			case 'S' :		/* ���a */
				add_yy = 1926;
				break;
			case 'H' :		/* ���� */
				add_yy = 1989;
				break;
			default:
				break;
		}
		/* �J�n��������߂�	*/
		if( add_yy != 0 ){
			--add_yy;
		}
	sprintf( wk_ymd8, "%04d%s", atoi( wk_yy ) + add_yy, wk_mmdd );
	memset( ymd10, '\0', sizeof( ymd10 ));
	sprintf( ymd10,	"%.4s-%.2s-%.2s",
		wk_ymd8, &wk_ymd8[4], &wk_ymd8[6] );

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( ret );
}

/******************************************************************************/
/*  �� �� ��  �FValidDate                                                     */
/*  �@�\�T�v  �F���t�A�����@�Ó����`�F�b�N                                    */
/*  ��    ��  �F                                                              */
/*   ��P���� �F int	mode		: �ҏW����Ă�����t�֘A���ڂ̌^          */
/*   ��Q���� �F char	indate[]	: ���͓��t����                            */
/*  �o    ��  �F                                                              */
/*  ���A���  �F RTN_OK				: ����                                    */
/*               RTN_NG				: �G���[                                  */
/******************************************************************************/
int     ValidDate( mode, indate )
int			mode;
char		indate[];	
{
    static	int t[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int		y, m, d, h, mi, s;
    int		i;
	char	w_yyyy[5];
	char	w_mm[3];
	char	w_dd[3];
	char	w_hh[3];
	char	w_mi[3];
	char	w_ss[3];

	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/

	/* �����ݒ�	*/
	strcpy( func_nm, "ValidDate" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	strcpy( w_yyyy, "0000" );	y = strlen( w_yyyy ) - 1;
	strcpy( w_mm, 	"00" );		m = strlen( w_mm ) - 1;
	strcpy( w_dd, 	"00" );		d = strlen( w_dd ) - 1;
	strcpy( w_hh, 	"00" );		h = strlen( w_hh ) - 1;
	strcpy( w_mi, 	"00" );		mi = strlen( w_mi ) - 1;
	strcpy( w_ss, 	"00" );		s = strlen( w_ss ) - 1;

	// INPUT���t��N���������b�ɕ���
	for( i = strlen( indate ) - 1; i >=0 ; --i){
		if( indate[i] >= '0' && indate[i] <= '9' ){
			if(( mode == VALDATE_TIME )||( mode == VALDATE_TIMESTAMP )){
				// SS
            	if( s >= 0 ){
					w_ss[s] = indate[i];
					--s;
					continue;
				}
				// MINUTE
            	if( mi >= 0 ){
					w_mi[mi] = indate[i];
					--mi;
					continue;
				}
				// HOUR
            	if( h >= 0 ){
					w_hh[h] = indate[i];
					--h;
					continue;
				}
			}
			if(( mode == VALDATE_DATE )||( mode == VALDATE_TIMESTAMP )){
				// DAY
				if( d >= 0 ){
					w_dd[d] = indate[i];
					--d;
					continue;
				}
				// MONTH
				if( m >= 0 ){
					w_mm[m] = indate[i];
					--m;
					continue;
				}
				// YEAR
				if( y >= 0 ){
					w_yyyy[y] = indate[i];
					--y;
					continue;
				}
			}
        }
    }
	
	y = atoi( w_yyyy );
	m = atoi( w_mm );
	d = atoi( w_dd );
	h = atoi( w_hh );
	mi = atoi( w_mi );
	s = atoi( w_ss );

	// TIME
	if(( h > 24 ) || ( mi > 60 ) || ( s > 60 )){
		// �����G���[
		return( RTN_NG );
	}
	if( mode == VALDATE_TIME ){
		return( RTN_OK );
	}

	if( ( y >= 1 ) && ( y <= 9999 ) && ( m >= 1 ) && ( m <= 12 )
	 && ( d >= 1   ) &&( d <= t[ m - 1 ] )) {
		// OK
		return( RTN_OK );
	} else {
		// �[�N�`�F�b�N	
		// �P�j ������S�Ŋ���A����؂ꂽ�N�͉[�N�ł���
		// �Q�j �Ȃ��A�P�̏����𖞂����Ă��A�P�O�O�Ŋ���؂ꂽ�ꍇ�͉[�N������
		// �R�j �Ȃ��A�Q�̏����𖞂����Ă��A�S�O�O�Ŋ���؂ꂽ�ꍇ�͉[�N
		if(( m == 2 ) && ( y%4 == 0 )){ 			// �[�N���
			if(( y%100 != 0 ) || ( y%400 == 0 )){	// �[�N����
				if( d == 29 ){
					// OK
					return( RTN_OK );
				}
			}
		}
	}
	// ���t�G���[ 

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return( RTN_NG );
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmCrt()				 								  */
/*  �@�\�T�v�@�F���L����������								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *   	���L�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int		sFncShmCrt ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/

	/* �����ݒ�	*/
	strcpy( func_nm, "sFncShmCrt" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//	�擾
	stcShm->shm_Id = shmget ( (key_t)stcShm->shm_Key, 
					MYAPP_SHM_SIZE, 0666 | IPC_CREAT ) ;
	if ( stcShm->shm_Id < 0 ) {
		//	�ُ�I��	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "���L�������̑���(shmget)�Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "���L�������̑���(shmat)�Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	//	�l�ݒ�	
	*shmData = 0 ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "���L�������̑���(shmdt)�Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmGet()				 								  */
/*  �@�\�T�v�@�F���L�������擾								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *   	���L�������\����                          */
/*�@ ��Q���� �Fint *   				�l							 	      */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int		sFncShmGet ( stcShm, pshmData )
struct		SHM		*stcShm;
int			*pshmData ;
{
	int		*shmData ;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/

	/* �����ݒ�	*/
	strcpy( func_nm, "sFncShmGet" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//	�A�^�b�`	
	shmData = ( int * ) shmat ( stcShm->shm_Id, 0 , 0 ) ;
	if ( shmData == ( int * )-1 ) {
		//	�ُ�I��	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "���L�������̑���(shmat)�Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}

	//	�l�ݒ�	
	*pshmData = *shmData ;

	//	�f�^�b�`	
	if ( shmdt ( shmData ) == -1 ) {
		//	�ُ�I��	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "���L�������̑���(shmdt)�Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( RTN_OK ) ;
}

/******************************************************************************/
/*  �� �� ���@�FsFncShmDel()				 								  */
/*  �@�\�T�v�@�F���L�������폜								  	 			  */
/*  ���@�@�́@�F                                                              */
/*�@ ��P���� �Fstruct stcShm *   	���L�������\����                          */
/*  �o�@�@�́@�F                                                              */
/*  ���A���@�Fint															  */
/*					 0	����												  */
/*					-1	�ُ�												  */
/******************************************************************************/
int		sFncShmDel ( stcShm )
struct		SHM		*stcShm;
{
	int		*shmData ;
	char	func_nm[MYAPP_LEN_FNCNM+1];		/* �֐�����	*/

	/* �����ݒ�	*/
	strcpy( func_nm, "sFncShmDel" );
	LogOut( LT_STA, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );

	//	�폜	
	if ( shmctl ( stcShm->shm_Id, IPC_RMID, NULL) < 0 ) {
		//	�ُ�I��	LOG
		sprintf( G_err, "%d", errno );
		strcpy( G_msg, "���L�������̑���(shmctl)�Ɏ��s���܂����B" );
		EditCsvMsg( G_msg );
		LogOut( LT_ERR, LX_NON, G_err, G_msg, func_nm, __FILE__, __LINE__ );
		return ( RTN_NG ) ;
	}
	LogOut( LT_END, LX_NON, LE_NON, "", func_nm, __FILE__, __LINE__ );
	return ( RTN_OK ) ;
}
/** End of File ***************************************************************/
