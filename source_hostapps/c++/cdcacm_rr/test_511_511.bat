@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=511 rlen=511 runs=100
@pause
