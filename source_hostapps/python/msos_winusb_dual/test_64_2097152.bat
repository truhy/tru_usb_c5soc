@ECHO OFF

SET cmd=python msos_winusb_dual.py rate 64 2097152 64 2097152 16
ECHO %cmd%
%cmd%
IF %errorlevel% NEQ 0 GOTO :err_handler
PAUSE

GOTO :end_of_script

:err_handler
:: If run from double-click
IF /I %0 EQU "%~dpnx0" PAUSE

:end_of_script
