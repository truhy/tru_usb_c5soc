@ECHO OFF
CALL env_win.bat

SET cmd=py %PYSCRIPT% %SERIALPATH% rate 16384 16384 100
ECHO %cmd%
%cmd%
IF %errorlevel% NEQ 0 GOTO :err_handler

PAUSE

GOTO :end_of_script

:err_handler
:: If run from double-click
IF /I %0 EQU "%~dpnx0" PAUSE

:end_of_script
