@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION

SET CMAKE_BUILD_TYPE=Debug
if "%1" == "r" (
    CMAKE_BUILD_TYPE=Release
)

rem cd into the folder with this script first
cd /d %~dp0
call winclean.cmd
call mingw_build.cmd %CMAKE_BUILD_TYPE%
EXIT /B %ERRORLEVEL%