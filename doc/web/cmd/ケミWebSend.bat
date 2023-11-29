@echo off

set basedir=%~dp0..

set cmddir=%basedir%\cmd\
set htmldir=%basedir%\..\..\public_html\
set ftplog=%basedir%\cmd\ftplog.txt

cd /d %htmldir%

ftp -s:%cmddir%Ftphtml.txt
ftp -s:%cmddir%Ftphtml91.txt

cd /d %~dp0
pause
exit /B 2
