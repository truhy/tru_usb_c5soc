@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=1 rlen=1 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=63 rlen=63 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=64 rlen=64 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=65 rlen=65 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=511 rlen=511 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=512 rlen=512 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=513 rlen=513 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=4095 rlen=4095 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=4096 rlen=4096 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=4097 rlen=4097 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=65535 rlen=16383 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=65536 rlen=16384 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=65537 rlen=16384 runs=100
%TESTAPP% path=%SERIALPATH% cmd=rate timeout=3000 wlen=2097152 rlen=16384 runs=100
@pause
