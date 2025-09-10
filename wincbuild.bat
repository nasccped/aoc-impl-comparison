@REM the only proposal of this file is to build the C code binary on
@REM Windows, since make only works well at UNIX-like systems

@echo off
setlocal enabledelayedexpansion

set "outdir=out"
set "CSOURCES="
for %%f in (c\*.c) do (
    set "CSOURCES=!CSOURCES! %%f"
)

if not exist "%outdir%" (
    mkdir "%outdir%"
    echo %outdir% created.
)

gcc -Wall -Wextra %CSOURCES% -o out/main
