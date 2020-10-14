@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION
:: usage:
::          vs2015_x86_build.cmd <target> <config>
::                  <target> - target to be built (default: ALL_BUILD)
::                  <config> - configuration to be used for build (default: Debug)

if NOT "%1" == "" (SET CMAKE_TARGET=%1) else (SET CMAKE_TARGET=ALL_BUILD)
if NOT "%2" == "" (set CMAKE_BUILD_TYPE=%2) else (set CMAKE_BUILD_TYPE=Debug)
SET CMAKE_BINARY_DIR=vs2015_x86

IF NOT EXIST "%CMAKE_BINARY_DIR%\*.sln" (
    cmake -H"." -B"%CMAKE_BINARY_DIR%" -G"Visual Studio 14 2015"
    SET GENERATE_ERRORLEVEL=!ERRORLEVEL!
    IF NOT "!GENERATE_ERRORLEVEL!"=="0" (
        DEL /F /Q "%CMAKE_BINARY_DIR%\*.sln"
        EXIT /B !GENERATE_ERRORLEVEL!
    )
)
cmake --build "%CMAKE_BINARY_DIR%" --target "%CMAKE_TARGET%" --config "%CMAKE_BUILD_TYPE%"
SET BUILD_ERRORLEVEL=!ERRORLEVEL!
IF NOT "!BUILD_ERRORLEVEL!"=="0" (
    EXIT /B !BUILD_ERRORLEVEL!
)

ENDLOCAL 