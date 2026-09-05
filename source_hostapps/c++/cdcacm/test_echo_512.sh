#!/bin/bash

set -e
function cleanup {
	rc=$?
	# If error and shell is child level 1 then stay in shell
	if [ $rc -ne 0 ] && [ $SHLVL -eq 1 ]; then exec $SHELL; else exit $rc; fi
}
trap cleanup EXIT

source env-linux.sh
$TESTAPP cmd=echo path=$SERIALPATH len=512 runs=100
read -n 1 -s -r -p "Press any key to continue"
