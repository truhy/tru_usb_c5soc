@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=1048576 rlen=16384 runs=100
@pause
