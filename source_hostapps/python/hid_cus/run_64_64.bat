@ECHO OFF

SET cmd=py hid_cus.py 64 64 10
ECHO %cmd%
%cmd%
IF %errorlevel% NEQ 0 GOTO :err_handler
PAUSE

GOTO :end_of_script

:err_handler
:: If run from double-click
IF /I %0 EQU "%~dpnx0" PAUSE

:end_of_script
