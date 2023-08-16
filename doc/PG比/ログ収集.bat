@echo off
rem ****************************************************************************************
rem  【システム向】
rem                                   最新ソース取得/設定
rem 
rem ****************************************************************************************
set CpLog=CopyHistory.txt
set ErrLog=Err.txt
set SvPath=\\10.1.181.166\share\CL_BIN\
set SvManPath=\\10.1.181.166\share\CL_BIN\_Manage\
set SvCfgPath=%SvManPath%Config\%COMPUTERNAME%\
set Svlog=

echo ----------------------------------------------------------------------------
echo     アプリケーション最新版(差分)を取得しています。しばらくお待ち下さい。
echo     ■■■■    ■■        ■■    ■■■   ■■■■ ■■■■    
echo     ■■    ■   ■■      ■■    ■    ■  ■       ■■    ■  
echo     ■■    ■■   ■■  ■■     ■     ■  ■       ■■    ■■
echo     ■■    ■■      ■■       ■          ■■■■ ■■    ■■
echo     ■■    ■■      ■■       ■   ■■■ ■       ■■    ■■
echo     ■■    ■■   ■■  ■■     ■    ■   ■       ■■    ■■
echo     ■■    ■■ ■■      ■■    ■   ■   ■       ■■    ■■
echo     ■■    ■■■■        ■■    ■■■   ■■■■ ■■    ■■
echo ----------------------------------------------------------------------------


rem ●アプリケーション差分コピー
rem set ErrMsg=アプリケーション差分コピー失敗
rem @echo ******************************************************************************* >> %CpLog%
rem @echo ■起動日時： %DATE%-%TIME% >> %CpLog%
rem xcopy %SvPath%Bin .\Bin /i /r /h /e /d /z /k /y >> %CpLog%
rem if %errorlevel% GTR 0 goto ERROREND
rem -- xcopyオプション --------------------------------------------------------
rem /i =ディレクトリが無ければ作成しコピーする
rem /r =読取専用ファイルをコピーする
rem /h =隠しファイル属性とシステムファイル属性を持つファイルもコピーする
rem /e =空の場合でも全てのサブディレクトリをコピーする
rem /d =変更があったファイルのみコピーする
rem /z =再起動可能モード
rem /k =コピー元ファイルの読取専用属性もコピーする
rem /y =既にコピー先にあるファイルを上書きするかの確認を表示しない
rem 
rem -- replaceオプション ------------------------------------------------------
rem /a =置換先ディレクトリに新しいファイルを追加します
rem /r =読取専用のファイルも置換する
rem /u =置換元ファイルよりも古い置換先ファイルのみを置換する
rem ---------------------------------------------------------------------------


rem ●共通コンフィグ置換
rem set ErrMsg=共通コンフィグ置換失敗
rem replace %SvPath%Bin\Common.config .\Bin /r >> %CpLog%
rem if %errorlevel% GTR 0 goto ERROREND

rem ●端末別設定ファイル置換
rem if exist %SvCfgPath% (
rem 	rem ①クライアントコンフィグ置換  【必須】
rem 	set ErrMsg=クライアントコンフィグ置換失敗
rem 	replace %SvCfgPath%Client.config .\Bin /r >> %CpLog%
rem 	if %errorlevel% GTR 0 goto ERROREND
rem 
rem 	rem ②DB2設定ファイル置換         【任意】
rem 	rem   (環境変数が'\'付なのでReplaceは使用不可)
rem 	set ErrMsg=DB2設定ファイル置換失敗
rem 	if exist %SvCfgPath%db2cli.ini (
rem 		xcopy %SvCfgPath%db2cli.ini %DB2TEMPDIR%db2cli.ini /r /h /z /k /y >> %CpLog%
rem 		if %errorlevel% GTR 0 goto ERROREND
rem 	)
rem 
rem 	rem [環境]_IP.txt生成
rem 	set ErrMsg=IP情報ファイル作成失敗
rem 	ipconfig /all > %SvCfgPath%_IP.txt
rem 	if %errorlevel% GTR 0 goto ERROREND
rem 
rem ) else (
rem 	set ErrMsg=端末別設定フォルダ未設定
rem 	goto ERROREND
rem )
rem ●ログ操作実行
.\NGG35.exe
if %errorlevel% GTR 0 goto ERROREND

rem ●終了
@echo ○自動更新正常終了 >> %CpLog%
@echo %COMPUTERNAME%,%DATE%-%TIME% >> %SvManPath%%CpLog%
exit


rem ●異常終了
:ERROREND
	@echo %COMPUTERNAME%,%DATE%-%TIME%,%ErrMsg%,,, >> %SvManPath%%ErrLog%
	echo ■エラー内容■ %ErrMsg%
	echo ×エラー発生･･･原因を確認してください。 >> %CpLog%

exit
