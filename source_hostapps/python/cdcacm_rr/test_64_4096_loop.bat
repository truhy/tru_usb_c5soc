@ECHO OFF
CALL env_win.bat

SET cmd=py %PYSCRIPT% %SERIALPATH% rate 64 4096 1
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
