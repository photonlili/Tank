#!/bin/sh

cp -f ../Build/tank-MIPS32-Release/tank ./HNApp/
rm -f upgrade.tar.gz
tar czvf upgrade.tar.gz etc/ HNApp/

