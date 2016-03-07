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
export PATH=/DWINFile:$QTDIR/bin:$PATH
export QT_QWS_FONTDIR=$QTDIR/lib/fonts
#export QWS_MOUSE_PROTO=USB:/dev/input/mice
export QWS_MOUSE_PROTO=tslib:/dev/input/event0
#export QWS_MOUSE_PROTO="tslib:/dev/input/event0 interlliMouse:/dev/input/event1"
#export QWS_KEYBOARD=USB:/dev/input/event2
export QWS_DISPLAY=LinuxFb:/dev/fb0
#export QWS_SIATH=$QTDIR/lib:$LD_LIBRARY_PATH

if [ -d /mnt/usb_sda1 ]; then
	if [ -e /mnt/usb_sda1/upgrade.tar.gz ]; then
		tar xzvf /mnt/usb_sda1/upgrade.tar.gz -C /
	fi
fi

cd /DWINFile
/DWINFile/tank -qws &

