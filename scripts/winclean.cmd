@echo off

rem push the current directory path on to the stack
pushd %cd%

rem get into the build dir
cd ..\build
:: Delete all the subdirectories that are not 'debug' or 'release'
for /D %%D in ("%cd%\*.*" "%cd%\debug\*.*" "%cd%\release\*.*") do (
    if /I not "%%~nxD"=="debug" if /I not "%%~nxD"=="release" (
    	2> nul rd /S /Q "%%~fD"
    )
)

:: Delete all files that are not '.cmd', '.sh', or '.gitignore'
for /R "%cd%" %%f in (*) do (if not "%%~xf"==".cmd" if not "%%~xf"==".sh" if not "%%~xf"==".gitignore" del "%%~f")

rem pop the original dir path off the stack
popd