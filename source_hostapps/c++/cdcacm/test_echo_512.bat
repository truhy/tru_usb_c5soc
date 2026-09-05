@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=echo timeout=3000 len=512 runs=100
@pause
