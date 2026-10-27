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

%MSBUILD% cocos2d-win32.sln /p:Configuration="Debug" /m

echo./*
echo. * Check the cocos2d-win32 application "NarutoSenki.exe" ...
echo. */
echo.

pushd ".\Debug.win32\"

set CC_BIN=NarutoSenki.exe
set CC_RES=..\projects\NarutoSenki\Resources
set CC_LUA=..\projects\NarutoSenki\lua

rm -rf ..\projects\NarutoSenki\__BIN__\Data
mkdir ..\projects\NarutoSenki\__BIN__\Data
rm -rf ..\projects\NarutoSenki\__BIN__\lua
mkdir ..\projects\NarutoSenki\__BIN__\lua
xcopy /D /E /Y /Q "%CC_RES%" ..\projects\NarutoSenki\__BIN__\Data
xcopy /D /E /Y /Q "%CC_LUA%" ..\projects\NarutoSenki\__BIN__\lua
xcopy /E /Y /Q .\*.dll ..\projects\NarutoSenki\__BIN__
xcopy /E /Y /Q .\*.exe ..\projects\NarutoSenki\__BIN__

if not exist "%CC_BIN%" (
    echo Can't find the binary "NarutoSenki.exe", is there build error?
    goto ERROR
)

popd
goto EOF

:ERROR
pause

:EOF
