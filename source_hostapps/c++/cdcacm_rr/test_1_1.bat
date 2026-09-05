@call env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=1 rlen=1 runs=100
@pause
