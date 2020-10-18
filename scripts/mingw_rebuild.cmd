@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION

SET CMAKE_BUILD_TYPE=Debug
if "%1" == "r" (
    CMAKE_BUILD_TYPE=Release
)

cd ..\build
call winclean.cmd
cd ..\scripts
call mingw_build.cmd %CMAKE_BUILD_TYPE%
EXIT /B %ERRORLEVEL%