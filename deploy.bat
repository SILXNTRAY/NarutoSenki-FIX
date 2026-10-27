@echo off

echo Building NarutoSenki Project ...

call ./build.bat

"tools/7z/7z.exe" a Build/NarutoSenki.zip ./Build/NarutoSenki
