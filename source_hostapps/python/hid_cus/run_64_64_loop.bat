@ECHO OFF

SET cmd=py hid_cus.py 64 64 1

SETLOCAL EnableDelayedExpansion
FOR /l %%x IN (1, 1, 1000) DO (
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
