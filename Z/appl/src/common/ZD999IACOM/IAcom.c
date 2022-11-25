#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>

#define PORT   				(u_short)65402

#define COMMAND_PS              '0'
#define COMMAND_EXEC_LABO		'1'
#define COMMAND_EXEC_LABO_NYOU	'5'
#define COMMAND_EXEC_BM  	    '2'
#define COMMAND_KILL		    '3'
#define COMMAND_EXEC_BACK	    '4'
#define COMMAND_KILL_DM         'Q'

struct dataRec {
        char    command ;
        char    sts ;
        char    prmBuf[256] ;
} ;


#define MY_COM_SIZE	sizeof  ( char )

char    hostname[257];
char    command[257];
struct  hostent		*connect_host;
struct  sockaddr_in	 desthost;
int     s_listen;
char	Buf[257] ;
char	comBuf ;

int main ( argc, argv ) 
int		 argc ;
char	*argv[] ;
{

	struct dataRec	stDataRec ;
	int				exitSts ;

	/***
	 ***	�����`�F�b�N
	 ***/
	if ( argc < 3 ) {
		fprintf(stderr,"USEGE : IAps hostname command\n");
		exit ( 9 ) ;
	}

	/***
	 ***	�ڑ���z�X�g���ݒ�
	 ***/
	bzero(hostname,257);
	strcpy(hostname, argv[1]);

	/***
	 ***	�p�����[�^�ݒ�
	 ***/
	memset ( &stDataRec, '\0', sizeof ( stDataRec ) ) ;
	comBuf = argv[2][0] ;
	switch ( comBuf ) {
		case COMMAND_PS :
			stDataRec.command = comBuf ;
			break ;
		case COMMAND_EXEC_LABO :
			stDataRec.command = comBuf ;
			strcpy ( stDataRec.prmBuf, argv[3])  ;
			break ;
		case COMMAND_EXEC_LABO_NYOU :
			stDataRec.command = comBuf ;
			strcpy ( stDataRec.prmBuf, argv[3])  ;
			break ;
		case COMMAND_EXEC_BM :
			stDataRec.command = comBuf ;
			strcpy ( stDataRec.prmBuf, argv[3])  ;
			break ;
		case COMMAND_KILL:
			stDataRec.command = comBuf ;
			strcpy ( stDataRec.prmBuf, argv[3])  ;
			break ;
		case COMMAND_KILL_DM :
			stDataRec.command = comBuf ;
			break ;
		case COMMAND_EXEC_BACK :
			stDataRec.command = comBuf ;
			break ;
		default  :
		fprintf(stderr,"bad command!\n");
			exit ( 9 ) ;
	}

	/***
	 ***	�ڑ���h�o�A�h���X�擾
	 ***/
	if((connect_host = gethostbyname(hostname)) == NULL) {
		fprintf(stderr,"bad hostname!\n");
		exit ( 9 ) ;
	}

	/***
	 ***	��������\�P�b�g�^�\���̂ɃZ�b�g
	 ***/
	bzero((char *)&desthost,sizeof(desthost));
	desthost.sin_family  = AF_INET;
	desthost.sin_port    = htons(PORT);
	bcopy(connect_host->h_addr, (char *)&desthost.sin_addr, connect_host->h_length);

	/***
	 ***	�\�P�b�g���쐬
	 ***/
	if ((s_listen = socket(AF_INET, SOCK_STREAM,0)) < 0 ) {
		fprintf(stderr,"Socket for client failed.\n");
		exit ( 9 ) ;
	}

	/***
	 ***	�R�l�N�g
	 ***/
	if (connect(s_listen, (struct  sockaddr * )&desthost , sizeof(desthost) ) == -1) {
		fprintf(stderr,"Connect failed.\n");
		exit ( 9 ) ;
	}

	/***
	 ***	�����񑗐M
	 ***/
	write ( s_listen, &stDataRec, sizeof ( stDataRec )  ) ;

	/***
	 ***	��M
	 ***/
	switch ( comBuf ) {
		case COMMAND_PS :
			while (1 ) {
				memset ( Buf, '\0', sizeof ( Buf ) ) ;
				if ( read ( s_listen, Buf, sizeof ( Buf ) -1 ) <= 0 ) {
					break  ;
				}
				fprintf ( stdout, "%s", Buf ) ;
			}
			break ;
		case COMMAND_EXEC_LABO :
		case COMMAND_EXEC_LABO_NYOU :
		case COMMAND_EXEC_BM :
		case COMMAND_KILL:
		case COMMAND_KILL_DM :
			break ;
	}


	/***
	 ***	�\�P�b�g�ؒf
	 ***/
	close(s_listen);

	/***
	 ***	�I��
	 ***/
	exit ( 0 );
}


