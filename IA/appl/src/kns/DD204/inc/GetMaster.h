/******************************************************************************/
/* �@�a�l�k�l���������V�X�e��                                                 */
/*                                                                            */
/* �@�V�X�e�����F������V�X�e��                                               */
/* �@�t�@�C�����FGetMaster.h                                                  */
/* �@�T�@�@�@�v�F�}�X�^���擾�w�b�_  	                                      */
/******************************************************************************/
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  1.00     2006/03/06     A.Yamada       �V�K�쐬                           */
/* -------------------------------------------------------------------------- */
/*  Ver.     ���t           ���O           �C�����e                           */
/* -------------------------------------------------------------------------- */
/*  2.00     2008/09/19     K.Ameno        X-M�Ή�����                        */
/******************************************************************************/
#ifndef _getmaster_h
#define _getmaster_h
/******************************************************************************/
/* �C���N���[�h�錾                                                           */
/******************************************************************************/
#include "DD204.h"

/**********************************************************************/
/*  �O���Q�Ɗ֐�                                                      */
/**********************************************************************/
extern int GetMaster(void);
extern int GetKmkcd( int,char*,char* );
extern int GetNbkmkcd( char*,char* );
extern int GetTstrflg( char*,char*,char* );
extern int GetKnsgrp( char*,char* );
extern int GetSmpcd( char*,char*,char* );
extern int GetOyakmkcd( char*,char*,char* );
extern int GetSeccd( char*,char*,char* );
extern int GetXmcount( char*,char*,int* );
extern int GetYkcd( char*,char* );

#define		MECHMST_FILE_NAME		"mechmst.del"
#define		KINKYU_FILE_NAME		"kinkyu.del"
#define		KMKMST_FILE_NAME		"kmkmst.del"
#define		CTRLMST_FILE_NAME		"ctrlmst.del"
#define		SYSKNRMST_FILE_NAME		"sysknrmst.del"
#define		KNSGMST_FILE_NAME		"knsgmst.del"
#define		KSKBRMST_FILE_NAME		"kskbrmst.del"
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� --> */
/*** X-M�����W�`�F�b�N�̂��ߒǉ� ***/
#define		XBARMMST_FILE_NAME		"xbarmmst.del"
/*** ���������W�`�F�b�N�̂��ߒǉ� ***/
#define		RNGCHKMST_FILE_NAME		"rngchkmst.del"
/*	2.00	2008/09/18		K.Ameno		   X-M�Ή����� <-- */

#endif /* GetMaster.h */
