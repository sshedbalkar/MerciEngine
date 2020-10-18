@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION
:: usage:
::          mingw_build.cmd <config> <target>
::                  <config> - configuration to be used for build (default: Debug)
::                  <target> - target to be built (default: all)


if NOT "%1" == "" (set CMAKE_BUILD_TYPE=%1) else (set CMAKE_BUILD_TYPE=Debug)
if NOT "%2" == "" (set CMAKE_TARGET=%2) else (set CMAKE_TARGET=all)

SET CMAKE_BINARY_DIR=..\build\%CMAKE_BUILD_TYPE%
Call :TO_LOWER %CMAKE_BINARY_DIR% CMAKE_BINARY_DIR

echo build dir = %CMAKE_BINARY_DIR%

IF NOT EXIST "%CMAKE_BINARY_DIR%\Makefile" (
    cmake -H"." -B"%CMAKE_BINARY_DIR%" -DCMAKE_BUILD_TYPE=%CMAKE_BUILD_TYPE% -G"MinGW Makefiles"
    SET GENERATE_ERRORLEVEL=!ERRORLEVEL!
    IF NOT "!GENERATE_ERRORLEVEL!"=="0" (
        DEL /F /Q "%CMAKE_BINARY_DIR%\*.sln"
        EXIT /B !GENERATE_ERRORLEVEL!
    )
)
cmake --build %CMAKE_BINARY_DIR% --target %CMAKE_TARGET% --config "%CMAKE_BUILD_TYPE%"
SET BUILD_ERRORLEVEL=!ERRORLEVEL!
IF NOT "!BUILD_ERRORLEVEL!"=="0" (
    EXIT /B !BUILD_ERRORLEVEL!
)

echo Build successful!
:end
ENDLOCAL 
EXIT /B %ERRORLEVEL%

:TO_LOWER2
FOR %%B IN ("%~1") DO (
	FOR /F "delims=~" %%A IN ('ECHO %%Bˆ > ~%%B ˆ& DIR /L /B ~%%B') DO (
		SET LoCaseText=%%A
		DEL /Q ~%%B
	)
)
EXIT /B 0

:TO_LOWER
REM ***** Modify as necessary for the string source. *****
set "_STRING=%~1"
if not defined _STRING EXIT /B 0
REM ***** Modify as necessary for the string source. *****

set "_UCASE=ABCDEFGHIJKLMNOPQRSTUVWXYZ"
set "_LCASE=abcdefghijklmnopqrstuvwxyz"

for /l %%a in (0,1,25) do (
   call set "_FROM=%%_UCASE:~%%a,1%%
   call set "_TO=%%_LCASE:~%%a,1%%
   call set "_STRING=%%_STRING:!_FROM!=!_TO!%%
)

set %2=%_STRING%
EXIT /B 0