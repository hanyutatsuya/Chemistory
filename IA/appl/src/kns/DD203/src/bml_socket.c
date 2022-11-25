/**********************************************************************
 *                                                                    
 *     �a�l�k�l���������V�X�e��
 *
 *     �V�X�e�����F������
 *     �t�@�C�����Fbml_socket.c
 *     �T�v      �Fsocket�֌W�֐�
 **********************************************************************/

/**********************************************************************
 *  Ver.     Date           Name           History
 * --------------------------------------------------------------------
 *  1.00     2005/06/01     E.Osada        Create
 **********************************************************************/

/* include                                                            */
/**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include "bml_socket.h"
/**********************************************************************/

/* Define Word                                                        */
/**********************************************************************/
/**********************************************************************/

/* Extern Data	                                                      */
/**********************************************************************/
/**********************************************************************/

/* Extern Function prototype                                          */
/**********************************************************************/
/**********************************************************************/

/* Global Data                                                        */
/**********************************************************************/
/**********************************************************************/

/**********************************************************************
 *
 *      socket�����̏�����(�T�[�o�v���Z�X)
 *
 *      �֐��F int tcp_init(port_no, lisn, errno);
 *      �����F int port_no;     �|�[�g�ԍ� (R)
 *             int lisn;     listen�T�C�Y (R)
 *             int *error;	�G���[�ԍ� (W)
 *      �߂�l�F
 *             >0               ����I��(socket�œ���FD)
 *             FAILURE          �����w��G���[
 *             ERR0_SOCKET      socket()���ُ�I��
 *             ERR0_SOCKOPT	setsockopt()���ُ�I��
 *             ERR0_BIND	bind()���ُ�I��
 *             ERR0_LISTEN	listen()���ُ�I��
 *             ERR0_FCNTL_GET	fcntl(F_GETFL)���ُ�I��
 *             ERR0_FCNTL_SET	fcntl(F_SETFL)���ُ�I��
 *
 *      �������e�F
 *            socket�ڑ����s�����߂̏����������s���B
 **********************************************************************/
int
tcp_init(int port_no, int lisn, int *error)
{
	struct	sockaddr_in	srv_addr;
	int	fd_socket;
	int	on;

	/*
	 * �����`�F�b�N
	 */
	if (port_no == 0) {
		return (FAILURE);
	}
	if (lisn < 0) {
		return (FAILURE);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	/* 
	 * �f�[�^�ݒ� 
	 */
	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port_no);
	srv_addr.sin_addr.s_addr = INADDR_ANY;

	/* 
	 * socket() -> setsockopt() -> bind() -> listen() �̎��s 
	 */
	if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		*error = errno;
		return (ERR0_SOCKET);
	}
	on = 1;
	if (setsockopt(fd_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) == -1) {
		close( fd_socket );
		*error = errno;
		return (ERR0_SOCKOPT);
	}
	if (bind(fd_socket, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr_in)) == -1) {
		close( fd_socket );
		*error = errno;
		return (ERR0_BIND);
	}
	if (listen(fd_socket, lisn) == -1) {
		close( fd_socket );
		*error = errno;
		return (ERR0_LISTEN);
	}

	return (fd_socket);
}

/**********************************************************************
 *
 *	accept�����̎��s(�T�[�o�v���Z�X�p)
 *
 *	�֐��F int acpt_open(fd_socket, cli_addr, error);
 *	�����F int fd_sokcet;                   �\�P�b�gFD (R)
 *	       struct sockaddr_in *cli_addr;    accept����sockaddr (W)
 *	       int *error;                      �G���[�ԍ� (W)
 *	�߂�l�F
 *	       >0               ����I��(accept�œ���FD)
 *	       FAILURE          �����w��G���[
 *	       ERR0_ACCEPT      accept()���ُ�I��
 *
 *	�������e�F
 *	       �N���C�A���g�Ƃ̐ڑ����s���B
 **********************************************************************/
int
acpt_open(int fd_socket, struct sockaddr_in *cli_addr, int *error)
{
	int	fd_accept;
	unsigned long	len;
	int	status;
	int	fc;

	/* 
	 * �����`�F�b�N
	 */
	if (fd_socket <= 0) {
		return (FAILURE);
	}
	*error = 0;
	memset(cli_addr, 0, sizeof(struct sockaddr_in));
	len = sizeof(struct sockaddr_in);

	/*
	 * accept() �̎��s
	 */
	for ( ; ; ) {
		if ((fd_accept = accept(fd_socket, (struct sockaddr *)cli_addr, &len)) != -1) {
			/* �m���u���b�L���O�̐ݒ� */
			if ((fc = fcntl(fd_accept, F_GETFL, 0)) == -1) {
				*error = errno;
				shutdown( fd_accept, 2 );
				close( fd_accept );
				return (ERR0_FCNTL_GET);
			}
			fc |= O_NONBLOCK;
			if (fcntl(fd_accept, F_SETFL, fc) == -1) {
				*error = errno;
				shutdown( fd_accept, 2 );
				close( fd_accept );
				return (ERR0_FCNTL_SET);
			}
			/*
			 * ����I�����́A��ʂɎ擾����FD��Ԃ�
			 */
			return (fd_accept);
		}
		if (errno != EINTR) {
			close ( fd_accept );
			*error = errno;
			return (ERR0_ACCEPT);
		}
	}
}

/**********************************************************************
 *
 *	connect�����̎��s(�N���C�A���g�v���Z�X�p)
 *
 *	�֐��F conct_open(ip_addr, timer, tmout, port_no);
 *	�����F char	*ip_addr;             �T�[�o��IP�A�h���X (R)
 *	       int port_no;               �|�[�g�ԍ� (R)
 *	       int timer;                 ���g���C�Ԋu(ms) (R)
 *	       int tmout;                 �^�C���A�E�g(s) (R)
 *	       int *error;                �G���[�ԍ� (W)
 *	�߂�l�F
 *	       >0               ����I��(connect�œ���FD)
 *	       FAILURE          �����w��G���[
 *	       ERR0_SOCKET      socket()���ُ�I��
 *	       ERR0_CONNECT     connect()���ُ�I��
 *	       ERR0_FCNTL_GET   fcntl(F_GETFL)���ُ�I��
 *	       ERR0_FCNTL_SET	fcntl(F_SETFL)���ُ�I��
 *	       ERR2_TIMEOUT     �^�C���A�E�g
 *	�������e�F
 *	       �T�[�o�Ƃ̐ڑ����s���B
 **********************************************************************/
int
conct_open(char *ip_addr, int port_no, int timer, int tout, int *error)
{
	struct sockaddr_in	srv_addr;
	struct timeval		tm_start;	/* �^�C���A�E�g�J�n���� */
	struct timeval		tm_r_start;	/* ���g���C�Ԋu�J�n���� */
	struct timeval		tm_end;		/* �������擾 */
	struct pollfd		pfd1;		/* ��FD�̐ؒf�Ď��ppollfd */
	int	fd_socket;			/* �\�P�b�gFD */
	int	status;				/* �G���[�X�e�[�^�X */
	int	p_sts1;				/* poll�X�e�[�^�X */
	int	fc;				/* fcntl�̃��[�h�擾/�ݒ� */

	/* 
	 * �����`�F�b�N 
	 */
	if (ip_addr == 0) {
		return (FAILURE);
	}
	if (port_no < 0) {
		return (FAILURE);
	}
	if (timer < 1) {
		return (FAILURE);
	}
	if (tout < 1) {
		return (FAILURE);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	memset(&srv_addr, 0, sizeof(struct sockaddr_in));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port_no);
	srv_addr.sin_addr.s_addr = inet_addr( ip_addr );

	gettimeofday(&tm_start, NULL);	/* ���ݎ����̎擾 */
	for ( ; ; ) {
		gettimeofday(&tm_r_start, NULL);	/* ���ݎ����̎擾 */
		/*
		 * socket()�̎��s
		 */
		if ((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			*error = errno;
			return (ERR0_SOCKET);
		}
		/* 
		 * �m���u���b�L���O���[�h�̐ݒ� 
		 */
		if ((fc = fcntl(fd_socket, F_GETFL, 0)) == -1) {
			*error = errno;
			status  = ERR0_FCNTL_GET;
			goto ERREND;
		}
		fc |= O_NONBLOCK;
		if (fcntl(fd_socket, F_SETFL, fc) == -1) {
			*error = errno;
			status = ERR0_FCNTL_SET;
			goto ERREND;
		}
		/*
		 * connect�����̎��s
		 */
		for ( ; ; ) {
			if (connect(fd_socket, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) == 0) {
				/*
				 * ����I���̏ꍇ�擾����FD����ʂɕԂ�
				 */
				return (fd_socket);
			}
			if (errno == EINTR) {
				continue;
			}
			*error = errno;
			pfd1.fd = fd_socket;
			pfd1.events = POLLOUT;
			if (errno == EINPROGRESS) {
				for ( ; ; ) {
					if ((p_sts1 = poll(&pfd1, 1, 200)) == -1) {
						if (errno == EINTR) {
							continue;
						} else {
							*error = errno;
							status = ERR0_POLL;
							goto ERREND;
						}
					} else if (p_sts1 == 0) {
						gettimeofday(&tm_end, NULL);
						if (tm_start.tv_sec + tout < tm_end.tv_sec) {
							status = ERR2_TIMEOUT;
							goto ERREND;
						}
						continue;
					} else if (p_sts1 == 1){
						if (pfd1.revents == POLLOUT) {
							break;
						}
					}
					status = ERR0_POLL;
					goto ERREND;
				}
			} else if (errno == EISCONN) {
				return (fd_socket);
			} else {
				status = ERR0_CONNECT;
				goto ERREND;
			}
		}
	}
ERREND:
	for ( ; ; ) {
		if (close(fd_socket) == -1) {
			if (errno == EINTR) {
				continue;
			} else {
				return (ERR0_CLOSE);
			}
		}
		break;
	}
	return (status);
}

/**********************************************************************
 *
 *	�P��FD��poll����
 *
 * 	�֐��F int sock_poll(fd, events);
 *	�����F int fd;               �C�x���g�҂����s��FD
 *	       short events;         �҂��̃C�x���g
 *	�߂�l�F
 *	       1               ����I��
 *	       ERR0_POLL       poll���ُ�I��
 *	       ERR2_TIMEOUT    �^�C���A�E�g
 *	�������e�F
 *
 **********************************************************************/
int
sock_poll(int fd, short events)
{
	int	status;
	int	loop;
	struct	pollfd	pfd;

	pfd.fd = fd;
	pfd.events = events;
	for ( ; ; ) {
		if ((status = poll(&pfd, 1, 200)) == -1) {
			if (errno == EINTR) {
				continue;
			}
			return (ERR0_POLL);
		} else if (status == 0) {
			return (ERR2_TIMEOUT);
		} else if (status == 1) {
			return (status);
		} else {
			return (ERR0_POLL);
		}
	}
}

/**********************************************************************
 *
 *	�f�[�^�̓Ǎ���
 *
 * 	�֐��F int sock_read(fd, ptr, size, tout, error);
 *	�����F int fd;               FD (R)
 *	       char *ptr;	     �Ǎ��݃o�b�t�@�A�h���X (W)
 *	       int size;             �Ǎ��݃T�C�Y (R)
 *	       int tout;	     �^�C���A�E�g(�b) (R)
 *	       int *error;           �G���[�ԍ� (W)
 *	�߂�l�F
 *	       SUCCESS               ����I��
 *	       FAILURE               �����w��G���[
 *	       ERR0_POLL             poll()���ُ�I��
 *	       ERR0_READ             read()���ُ�I��
 *	       ERR2_TIMEOUT          �������^�C���A�E�g
 *	       ERR2_MYCLOSE	     ���v���Z�X�ł�close()������
 *             ERR2_TOCLOSE          ���葤��close()������
 *	�������e�F
 *	       �ڑ��悩��f�[�^��ǂݍ���
 *	���ӎ����F
 *	       �߂�l��ERR2_MYCLOSE/ERR2_TOCLOSE�̏ꍇ�A��ʂŕK��close()
 *	       ���Ăяo���B
 **********************************************************************/
int
sock_read(int fd, char *ptr, int size, int tout, int *error)
{
	int	status;
	int	p_sts;
	int	fmode;
	struct timeval	tm_start;
	struct timeval	tm_end;

	/* �����`�F�b�N */
	if (fd < 0) {
		return (FAILURE);
	}
	if (ptr == NULL) {
		return (FAILURE);
	}
	if (tout < 1) {
		return (FAILURE);
	}
	if (size < 0) {
		return (FAILURE);
	}
	if (size == 0) {
		return (SUCCESS);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	gettimeofday(&tm_start, NULL);
	for ( ; ; ) {
		if ((p_sts = sock_poll(fd, POLLIN)) == ERR2_TIMEOUT) {
			gettimeofday(&tm_end, NULL);
			if (tm_start.tv_sec + tout < tm_end.tv_sec) {
				*error = errno;
				return (ERR2_TIMEOUT);
			} else {
				continue;
			}
		} else if (p_sts == ERR0_POLL) {
			*error = errno;
			return (ERR0_POLL);
		}
		if ((status = read(fd, ptr, size)) == -1) {
			if (errno == EINTR) {
				continue;
			}
			*error = errno;
			if (errno == EBADF) {
				return (ERR2_MYCLOSE);
			}
			if (errno == ECONNRESET) {
				return (ERR2_TOCLOSE);
			}
			return (ERR0_READ);
		}
		if (status == 0) {
			*error = errno;
			return (ERR2_TOCLOSE);
		}
		if (size - status == 0) {
			break;
		}
		ptr += status;
		size -= status;
	}
	return (SUCCESS);
}

/**********************************************************************
 *
 *	�f�[�^�̏�����
 *
 *	�֐��F int sock_write(fd, ptr, size, tout, error);
 *	�����F int fd;               FD	(R)
 *	       char *ptr;            �o�b�t�@�A�h���X (R)
 *	       int size;             �����݃T�C�Y (R)
 *	       int tout;             �^�C���A�E�g(�b)(R)
 *	       int *error;           �G���[�ԍ� (W)
 *	�߂�l�F
 *	       SUCCESS               ����I��
 *	       FAILURE               �����w��G���[
 *	       ERR0_POLL             poll()���ُ�I��
 *	       ERR0_WRITE            write()���ُ�I��
 *	       ERR1_0_WRITE          write()�̖߂�l���O
 *	       ERR2_TIMEOUT          �������^�C���A�E�g
 *	       ERR2_MYCLOSE          ���v���Z�X��close()������
 *	       ERR2_TOCLOSE          ���葤��close()������
 *	�������e�F
 *	       �ڑ���փf�[�^�������ށB
 *	���ӎ����F
 *	       �߂�l��ERR2_MYCLOSE/ERR2_TOCLOSE�̏ꍇ�A��ʂŕK��close()
 *	       ���Ăяo���B
 **********************************************************************/
int
sock_write(int fd, char *ptr, int size, int tout, int *error)
{
	int	status;
	int	p_sts;
	int	fmode;
	struct timeval	tm_start;
	struct timeval	tm_end;

	/* �����`�F�b�N */
	if (fd < 0) {
		return (FAILURE);
	}
	if (ptr == NULL) {
		return (FAILURE);
	}
	if (tout < 1) {
		return (FAILURE);
	}
	if (size < 0) {
		return (FAILURE);
	}
	if (size == 0) {
		return (SUCCESS);
	}
	if (error == NULL) {
		return (FAILURE);
	}
	*error = 0;

	gettimeofday(&tm_start, NULL);
	for ( ; ; ) {
		if ((p_sts = sock_poll(fd, POLLOUT)) == ERR2_TIMEOUT) {
			gettimeofday(&tm_end, NULL);
			if (tm_start.tv_sec + tout < tm_end.tv_sec) {
				*error = errno;
				return (ERR2_TIMEOUT);
			} else {
				continue;
			}
		} else if (p_sts == ERR0_POLL) {
			*error = errno;
			return (ERR0_POLL);
		}
		if ((status = write(fd, ptr, size)) == -1) {
			if (errno == EINTR) {
				continue;
			}
			*error = errno;
			if (errno == EBADF) {
				return (ERR2_MYCLOSE);
			}
			if (errno == EPIPE || errno == ECONNRESET) {
				return (ERR2_TOCLOSE);
			}
			return (ERR0_WRITE);
		}
		if (status == 0) {
			*error = errno;
			return (ERR1_0_WRITE);
		}
		if (size - status == 0) {
			break;
		}
		ptr += status;
		size -= status;
	}
	return (SUCCESS);
}
