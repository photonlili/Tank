#!/bin/sh

if [ -d /mnt/usb_sda1 ]; then
	if [ -e /mnt/usb_sda1/upgrade.tar.gz ]; then
		/usr/bin/tar xzvf /mnt/usb_sda1/upgrade.tar.gz -C /
        /sbin/reboot
	fi
fi

