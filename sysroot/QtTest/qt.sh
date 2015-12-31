#!/bin/bash

#tslib settings
export TSLIB_ROOT=/usr
export TSLIB_CONSOLEDEVICE=none
export TSLIB_FBDEVICE=/dev/fb0
export TSLIB_TSDEVICE=/dev/input/event0
export TSLIB_CONFFILE=/etc/ts.conf
export TSLIB_PLUGINDIR=$TSLIB_ROOT/lib/ts

#qt settings
export QTDIR=/usr
export QPEDIR=$QTDIR
export PATH=$QTDIR/bin:$PATH
export QT_QWS_FONTDIR=$QTDIR/lib/fonts
#export QWS_MOUSE_PROTO=USB:/dev/input/mice
export QWS_MOUSE_PROTO=tslib:/dev/input/event0
export QWS_DISPLAY=LinuxFb:/dev/fb0
#export QWS_SIZE=1024x600
export LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH

#/QtTest/DwinPicture -qws /QtTest/picture/

