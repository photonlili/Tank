#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T15:34:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(HNWidgets/HNWidgets.pri)

TARGET = HNPrjDemo
TEMPLATE = app

target.path += /HNApp

INSTALLS += target

TRANSLATIONS = HNLang/zh_CN.ts \
    HNLang/en_US.ts

CODECFORTR = UTF-8

RESOURCES +=

RC_FILE += \
    hnversion.rc


SOURCES += main.cpp\
    hnapp.cpp \
    hnloginform.cpp \
    hnmainform.cpp \
    hnwindow.cpp

HEADERS  += \
    hnapp.h \
    hnloginform.h \
    hnmainform.h \
    hnwindow.h \
    hnversion.h

FORMS    += \
    hnloginform.ui \
    hnmainform.ui \
    hnwindow.ui

OTHER_FILES += \
    HNPrjDemo.pro.user \
    hnversion.rc
