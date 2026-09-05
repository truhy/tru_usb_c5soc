@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=512 rlen=512 runs=100
@pause
