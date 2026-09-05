@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=verify timeout=3000 wlen=16384 rlen=16384 runs=100
@pause
