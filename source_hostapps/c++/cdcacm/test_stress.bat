@CALL env-win.bat
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=1 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=63 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=64 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=65 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=511 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=512 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=513 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=4095 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=4096 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=4097 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=65535 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=65536 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=65537 runs=100
%TESTAPP% path=%SERIALPATH% cmd=tx timeout=3000 len=2097152 runs=100
@pause
