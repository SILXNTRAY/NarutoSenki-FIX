@echo off

echo./*
echo. * Check VC++ environment...
echo. */
echo.

set VSTOOLS="%VS143COMNTOOLS%"
set VC_VER=143

set VSTOOLS=%VSTOOLS:"=%
set "VSTOOLS=%VSTOOLS:\=/%"

set VSVARS="%VSTOOLS%vsvars32.bat"
set MSBUILD="C:\Program Files\Microsoft Visual Studio\2022\Preview\Msbuild\Current\Bin\msbuild.exe"

if not defined VSVARS (
    echo Can't find VC2022 installed!
    goto ERROR
)

echo./*
echo. * Building cocos2d-x library binary, please wait a while...
echo. */
echo.

call %VSVARS%

%MSBUILD% cocos2d-win32.sln /p:Configuration="Release" /m

echo./*
echo. * Check the cocos2d-win32 application "NarutoSenki.exe" ...
echo. */
echo.

pushd ".\Release.win32\"

set CC_BIN=NarutoSenki.exe
set CC_RES=..\projects\NarutoSenki\Resources
set CC_LUA=..\projects\NarutoSenki\lua

echo./*
echo. * Copy resources
echo. */

if not exist ..\Build mkdir ..\Build
rm -rf ..\Build\NarutoSenki\Data
mkdir ..\Build\NarutoSenki\Data
rm -rf ..\Build\NarutoSenki\lua
mkdir ..\Build\NarutoSenki\lua
xcopy /E /Y /Q "%CC_RES%" ..\Build\NarutoSenki\Data
xcopy /E /Y /Q "%CC_LUA%" ..\Build\NarutoSenki\lua
xcopy /E /Y /Q .\*.dll ..\Build\NarutoSenki
xcopy /E /Y /Q .\*.exe ..\Build\NarutoSenki

if not exist "%CC_BIN%" (
    echo Can't find the binary "NarutoSenki.exe", is there build error?
    goto ERROR
)

popd
goto EOF

:ERROR
pause

:EOF
