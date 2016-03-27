#!/bin/sh

install -m 644 -p include/* /usr/include/qt4/QtSerialPort/
install -m 644 -p serialport.prf /usr/share/qt4/mkspecs/features/
install -m 755 -p "libQtSerialPort.so.4.8.6" "/usr/lib/x86_64-linux-gnu/libQtSerialPort.so.4.8.6"
ln -f -s "libQtSerialPort.so.4.8.6" "/usr/lib/x86_64-linux-gnu/libQtSerialPort.so"
ln -f -s "libQtSerialPort.so.4.8.6" "/usr/lib/x86_64-linux-gnu/libQtSerialPort.so.4"
ln -f -s "libQtSerialPort.so.4.8.6" "/usr/lib/x86_64-linux-gnu/libQtSerialPort.so.4.8"
install -m 644 -p "libQtSerialPort.prl" "/usr/lib/x86_64-linux-gnu/libQtSerialPort.prl"

