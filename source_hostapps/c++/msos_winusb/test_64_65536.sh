#!/bin/bash

set -e
function cleanup {
	rc=$?
	# If error and shell is child level 1 then stay in shell
	if [ $rc -ne 0 ] && [ $SHLVL -eq 1 ]; then exec $SHELL; else exit $rc; fi
}
trap cleanup EXIT

./build/linux/Release/msos_winusb cmd=rate wlen=64 rlen=65536 runs=100 timeout=5000
read -n 1 -s -r -p "Press any key to continue"
