@ECHO OFF

PUSHD $~dp0\..\

CALL vendor\premake\premake5.exe vs2022

POPD

PAUSE