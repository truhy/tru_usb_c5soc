@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=verify timeout=3000 wlen=1048576 rlen=1048576 runs=100
@pause
