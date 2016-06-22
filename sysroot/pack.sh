#!/bin/sh

cp -f ../build-tank-mips_32-Release/tank ./HNApp/
rm -f upgrade.tar.gz
tar czvf upgrade.tar.gz etc/ HNApp/

