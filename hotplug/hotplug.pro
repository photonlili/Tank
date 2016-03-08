#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T12:54:54
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = hotplug
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QT_KIT = $$(QKIT)

message($${QT_KIT} $$(QKIT) DEFINED)

DEFINES += _TTY_POSIX_

equals(QT_KIT, MIPS32) {
    QT += multimedia
    DEFINES += __MIPS_LINUX__
} else {
    DEFINES += __LINUX64__
}

CONFIG(debug, debug|release) {
} else {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

INCLUDEPATH +=  .

target.path += /DWINFile

INSTALLS += target

CODECFORTR = UTF-8

SOURCES += main.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_linux.cpp \
    qhotplugwatcher.cpp \
    qhotplugapp.cpp

OTHER_FILES += \
    hotplug.pro.user

HEADERS += \
    qdevicewatcher.h \
    qdevicewatcher_p.h \
    qhotplugwatcher.h \
    qhotplugapp.h
