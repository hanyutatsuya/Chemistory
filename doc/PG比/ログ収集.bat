@echo off
rem ****************************************************************************************
rem  �y�V�X�e�����z
rem                                   �ŐV�\�[�X�擾/�ݒ�
rem 
rem ****************************************************************************************
set CpLog=CopyHistory.txt
set ErrLog=Err.txt
set SvPath=\\10.1.181.166\share\CL_BIN\
set SvManPath=\\10.1.181.166\share\CL_BIN\_Manage\
set SvCfgPath=%SvManPath%Config\%COMPUTERNAME%\
set Svlog=

echo ----------------------------------------------------------------------------
echo     �A�v���P�[�V�����ŐV��(����)���擾���Ă��܂��B���΂炭���҂��������B
echo     ��������    ����        ����    ������   �������� ��������    
echo     ����    ��   ����      ����    ��    ��  ��       ����    ��  
echo     ����    ����   ����  ����     ��     ��  ��       ����    ����
echo     ����    ����      ����       ��          �������� ����    ����
echo     ����    ����      ����       ��   ������ ��       ����    ����
echo     ����    ����   ����  ����     ��    ��   ��       ����    ����
echo     ����    ���� ����      ����    ��   ��   ��       ����    ����
echo     ����    ��������        ����    ������   �������� ����    ����
echo ----------------------------------------------------------------------------


rem ���A�v���P�[�V���������R�s�[
rem set ErrMsg=�A�v���P�[�V���������R�s�[���s
rem @echo ******************************************************************************* >> %CpLog%
rem @echo ���N�������F %DATE%-%TIME% >> %CpLog%
rem xcopy %SvPath%Bin .\Bin /i /r /h /e /d /z /k /y >> %CpLog%
rem if %errorlevel% GTR 0 goto ERROREND
rem -- xcopy�I�v�V���� --------------------------------------------------------
rem /i =�f�B���N�g����������΍쐬���R�s�[����
rem /r =�ǎ��p�t�@�C�����R�s�[����
rem /h =�B���t�@�C�������ƃV�X�e���t�@�C�����������t�@�C�����R�s�[����
rem /e =��̏ꍇ�ł��S�ẴT�u�f�B���N�g�����R�s�[����
rem /d =�ύX���������t�@�C���̂݃R�s�[����
rem /z =�ċN���\���[�h
rem /k =�R�s�[���t�@�C���̓ǎ��p�������R�s�[����
rem /y =���ɃR�s�[��ɂ���t�@�C�����㏑�����邩�̊m�F��\�����Ȃ�
rem 
rem -- replace�I�v�V���� ------------------------------------------------------
rem /a =�u����f�B���N�g���ɐV�����t�@�C����ǉ����܂�
rem /r =�ǎ��p�̃t�@�C�����u������
rem /u =�u�����t�@�C�������Â��u����t�@�C���݂̂�u������
rem ---------------------------------------------------------------------------


rem �����ʃR���t�B�O�u��
rem set ErrMsg=���ʃR���t�B�O�u�����s
rem replace %SvPath%Bin\Common.config .\Bin /r >> %CpLog%
rem if %errorlevel% GTR 0 goto ERROREND

rem ���[���ʐݒ�t�@�C���u��
rem if exist %SvCfgPath% (
rem 	rem �@�N���C�A���g�R���t�B�O�u��  �y�K�{�z
rem 	set ErrMsg=�N���C�A���g�R���t�B�O�u�����s
rem 	replace %SvCfgPath%Client.config .\Bin /r >> %CpLog%
rem 	if %errorlevel% GTR 0 goto ERROREND
rem 
rem 	rem �ADB2�ݒ�t�@�C���u��         �y�C�Ӂz
rem 	rem   (���ϐ���'\'�t�Ȃ̂�Replace�͎g�p�s��)
rem 	set ErrMsg=DB2�ݒ�t�@�C���u�����s
rem 	if exist %SvCfgPath%db2cli.ini (
rem 		xcopy %SvCfgPath%db2cli.ini %DB2TEMPDIR%db2cli.ini /r /h /z /k /y >> %CpLog%
rem 		if %errorlevel% GTR 0 goto ERROREND
rem 	)
rem 
rem 	rem [��]_IP.txt����
rem 	set ErrMsg=IP���t�@�C���쐬���s
rem 	ipconfig /all > %SvCfgPath%_IP.txt
rem 	if %errorlevel% GTR 0 goto ERROREND
rem 
rem ) else (
rem 	set ErrMsg=�[���ʐݒ�t�H���_���ݒ�
rem 	goto ERROREND
rem )
rem �����O������s
.\NGG35.exe
if %errorlevel% GTR 0 goto ERROREND

rem ���I��
@echo �������X�V����I�� >> %CpLog%
@echo %COMPUTERNAME%,%DATE%-%TIME% >> %SvManPath%%CpLog%
exit


rem ���ُ�I��
:ERROREND
	@echo %COMPUTERNAME%,%DATE%-%TIME%,%ErrMsg%,,, >> %SvManPath%%ErrLog%
	echo ���G���[���e�� %ErrMsg%
	echo �~�G���[��������������m�F���Ă��������B >> %CpLog%

exit
