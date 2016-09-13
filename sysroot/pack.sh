#!/bin/sh

cp -f ../Build/tank-MIPS32-Release/tank ./Application/
rm -f upgrade.tar.gz
tar czvf upgrade.tar.gz etc/ Application/

