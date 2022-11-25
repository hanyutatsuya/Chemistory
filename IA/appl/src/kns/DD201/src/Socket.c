/**********************************************************************
 *                                                                    
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����FSocket.c
 *     �T�v      �F�\�P�b�g
 
 *                                                                    
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2006/01/31     A.Yamada       Create
 *  1.01     2006/09/27     S.Nagata       select �̃^�C�}�[�l��
 *                                          0��100msec�ɕύX
 **********************************************************************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

//#include "DD41399.h"
#include "Socket.h"

/**********************************************************************/
/*  �����֐��錾                                                      */
/**********************************************************************/
SOCKET			ClientInit(char *hostname, int port);
int				readAll(SOCKET, char *);
SOCKET			isSelect(SOCKET sd[], long sec);
int				writen(SOCKET, char *, long);
/**********************************************************************/
/*                                                                    */
/*   function name : ClientInit                                       */
/*                                                                    */
/*   purpose : �N���C�A���g�p�̃\�P�b�g��������                       */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
SOCKET ClientInit(char *hostname, int port)
{
	SOCKET			sd = SOCK_ERR;
	struct			sockaddr_in	destSockAddr;
	unsigned		long destAddr;
	int				status;
	char			ipAddr[20];
	struct hostent	*host;
	int i;

	/* create a socket */
    if ((sd = socket( AF_INET, SOCK_STREAM, 0 )) == -1) {
        return SOCK_ERR;
	}
//	printf("�\�P�b�g�ڑ�!!\n");

	// �h�o�A�h���X�𒼐ڗ^������@
	memset(&destSockAddr, 0, sizeof(struct sockaddr_in));
	if ((host = gethostbyname(hostname)) == NULL) {
		close(sd);
		return SOCK_ERR;
	}
	//loggingPrint(1, 1, NULL, "hostname<%s>\n", hostname);
	for(i = 0 ; host->h_addr_list[i] ; i++) {
		sprintf(ipAddr, "%d.%d.%d.%d" ,
			(unsigned char)*((host->h_addr_list[i])) ,
			(unsigned char)*((host->h_addr_list[i]) + 1) ,
			(unsigned char)*((host->h_addr_list[i]) + 2) ,
			(unsigned char)*((host->h_addr_list[i]) + 3)
		);
	}
	//loggingPrint(1, 1, NULL, "IPAddr<%s>\n", ipAddr);

	/*���z�X�g���̕\��*/
//	printf("Hostname  = %s\n", host->h_name);
//	printf("addrtype  = %d\n", host->h_addrtype);
//	printf("length    = %d\n", host->h_length);
//	printf("IP        = ");
//	dispip(host->h_addr);

	/* convert IP address into in_addr form*/
	destAddr=inet_addr(ipAddr);
	/* copy destAddr into sockaddr_in structure */
	memcpy(&destSockAddr.sin_addr, &destAddr, sizeof(long));
	/* specify the port portion of the address */
	destSockAddr.sin_port=htons((unsigned short)port);

	/* specify the address family as Internet */
	destSockAddr.sin_family=AF_INET;


	status=connect(sd, (struct sockaddr *)&destSockAddr, sizeof(struct sockaddr_in));
	if (status < 0) {
        close(sd);
//		printf("�R�l�N�g���s!!\n\n");
        return SOCK_ERR;
	}
//	printf("�R�l�N�g����!!\n\n");
	return sd;
}


/**********************************************************************/
/*                                                                    */
/*   function name : readAll                                          */
/*                                                                    */
/*   purpose : �ڑ�����Ă���z�X�g����f�[�^����M����B             */
/*             �S�Ă̎�M�f�[�^��ǂݍ��ށB                           */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
#if(0)
int readAll(SOCKET fd, char *ptr)
{
	static char tmpbuf[1024];
	static int	tmplen = 0;
	static int	tmpcnt = 0;
	int len, ret;
	char wrkbuf;

	len = 0;
	ret = 0;
	wrkbuf = '\0';

	while(1) {
		if (tmplen == 0) {
//			if((ret=recv(fd, &wrkbuf, 1, 0)) == -1){
			if((ret=recv(fd, tmpbuf, 1024, 0)) == -1){
	//�G���[���O�o��
				return 0;
			}
			tmplen = ret;
			tmpcnt = 0;
printf( "buf0:%02x\n",tmpbuf[0] );
printf( "buf1:%02x\n",tmpbuf[1] );

		}
		if (tmpcnt == tmplen) {
			tmpcnt = 0;
			tmplen = 0;
			return len;
		}
		wrkbuf = tmpbuf[tmpcnt];
		tmpcnt ++;
//		if( ret == 0 )
//			return len;
		if( wrkbuf == EOT || wrkbuf == ENQ ||
			wrkbuf == ACK || wrkbuf == NAK ||
			wrkbuf == LF ) {
			ptr[len] = wrkbuf;
			len++;
			break;
		} else {
			ptr[len] = wrkbuf;
			len++;
//			fprintf( stderr, "[%c]\n",wrkbuf );

		}
	}

//	fprintf( stderr, "[%s]\n",ptr );

	return len;
}
#endif
int readAll(SOCKET fd, char *ptr)
{
	int len, ret;
	char wrkbuf;

	len = 0;
	ret = 0;
	wrkbuf = '\0';

	while(1) {
		if((ret=recv(fd, &wrkbuf, 1, 0)) == -1){
//�G���[���O�o��
			return 0;
		}
		if( ret == 0 )
			return len;
		if( wrkbuf == EOT || wrkbuf == ENQ ||
			wrkbuf == ACK || wrkbuf == NAK ||
			wrkbuf == DC1 || wrkbuf == LF ) {
			ptr[len] = wrkbuf;
			len++;
			if( len > MAX_RCV_NUM ) {
				sFncSyslog ( TRCKIND_ERROR, "StatusCtrl()", "��M�o�C�g�����ő�l�𒴂��Ă��܂��B" ) ;
				printf(" ��M�o�C�g�����ő�l�𒴂��Ă��܂��B\n" );
			}
			break;
		} else {
			ptr[len] = wrkbuf;
			len++;
			if( len > MAX_RCV_NUM ) {
				sFncSyslog ( TRCKIND_ERROR, "StatusCtrl()", "��M�o�C�g�����ő�l�𒴂��Ă��܂��B" ) ;
				printf(" ��M�o�C�g�����ő�l�𒴂��Ă��܂��B\n" );
				break;
			}
//			fprintf( stderr, "[%c]\n",wrkbuf );

		}
	}

//	fprintf( stderr, "[%s]\n",ptr );

	return len;
}


/**********************************************************************/
/*                                                                    */
/*   function name : writen                                           */
/*                                                                    */
/*   purpose : �ڑ�����Ă���z�X�g�Ƀf�[�^�𑗐M����B               */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
/* send data byte */
int writen(SOCKET fd, char *ptr, long nbytes) 
{
	int nleft, nwritten;
	int nleft_r;

	nleft = nbytes;
	nleft_r = nleft;
	while (nleft > 0) {
		nwritten=send(fd, ptr,nleft_r, NO_FLAGS_SET);
		if (nwritten<=0) {
//			loggingPrint(L_ERR, K_CAU, NULL, "writen write error<%d>\n", nwritten);
			return nwritten;      /* error */
		}
		nleft -= nwritten;
		ptr   += nwritten;
	}
	return(nbytes - nleft);
}
/**********************************************************************/
/*                                                                    */
/*   function name : isSelect                                         */
/*                                                                    */
/*   purpose : �ǂݍ��ݏ�Ԃƃ^�C�}�[���|����                         */
/*                                                                    */
/*   data : 2005.12.20                                                */
/*                                                                    */
/*   produce : A.Yamada                                               */
/*                             Copyright(C) 2005 ALL RIGHTS RESERVED  */
/**********************************************************************/
SOCKET isSelect(SOCKET sd[], long sec)
{
	fd_set			set;
	struct timeval	tm;
	int				i;

	FD_ZERO(&set);
	for(i=0; sd[i]!=0; i++) {
		FD_SET(sd[i], &set);
	}
	tm.tv_sec = sec;
    //upd 2006-09-25 Nagata select �̃^�C�}�[�l�� 0sec �� 100msec�ɕύX
    tm.tv_usec = 100;
    if((select(sd[i-1]+1, &set, 0, 0, &tm)) > 0) {
		for(i=0; sd[i]!=0; i++) {
    		if(FD_ISSET(sd[i], &set))
				 return sd[i];
		}
    } else {
        return 0;
	}
	return 0;
}
