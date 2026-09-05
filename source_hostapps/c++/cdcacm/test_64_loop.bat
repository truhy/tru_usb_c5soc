@ECHO OFF
CALL env-win.bat

SET cmd=%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=64 runs=1
SETLOCAL EnableDelayedExpansion
FOR /l %%x IN (1, 1, 100) DO (
ECHO %cmd%
%cmd%
IF !ERRORLEVEL! NEQ 0 GOTO :err_handler
)
ENDLOCAL

PAUSE

GOTO :end_of_script

:err_handler
:: If run from double-click
IF /I %0 EQU "%~dpnx0" PAUSE

:end_of_script
