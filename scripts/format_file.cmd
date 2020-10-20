@ECHO off
SETLOCAL ENABLEDELAYEDEXPANSION

SET EXT=%~x1

for %%f in (".c" ".cpp" ".h" ".hpp" ".cc") do (
    if /I "%EXT%"=="%%~f" GOTO MATCH
)

:NOMATCH
EXIT /B 0

:MATCH
clang-format -i %1
EXIT /B 0