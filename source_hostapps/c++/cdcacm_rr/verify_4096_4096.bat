@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=verify timeout=3000 wlen=4096 rlen=4096 runs=1
@pause
