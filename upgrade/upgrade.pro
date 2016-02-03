#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T15:42:20
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = upgrade
TEMPLATE = app


SOURCES += main.cpp\
        hnupgradewidget.cpp \
    qtankclient.cpp \
    qtankmessage.cpp \
    qtankpublic.cpp \
    qcomponent.cpp

HEADERS  += hnupgradewidget.h \
    qtankclient.h \
    qtankmessage.h \
    qtanklinux.h \
    qtankpublic.h \
    qtankgui.h \
    qcomponent.h \
    qtankdefine.h

FORMS    += hnupgradewidget.ui

OTHER_FILES += \
    upgrade.pro.user
