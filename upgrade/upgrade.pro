#-------------------------------------------------
#
# Project created by QtCreator 2016-01-28T15:42:20
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = upgrade
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

TRANSLATIONS = language/zh_CN.ts \
    language/en_US.ts

CODECFORTR = UTF-8

SOURCES += main.cpp\
        hnupgradewidget.cpp \
    qtankclient.cpp \
    qtankmessage.cpp \
    qtankpublic.cpp \
    qcomponent.cpp \
    hnprogressbar.cpp \
    qcwidget.cpp \
    qtankapp.cpp

HEADERS  += hnupgradewidget.h \
    qtankclient.h \
    qtankmessage.h \
    qtanklinux.h \
    qtankpublic.h \
    qtankgui.h \
    qcomponent.h \
    qtankdefine.h \
    hnprogressbar.h \
    qcwidget.h \
    qtankapp.h

FORMS    += hnupgradewidget.ui \
    hnprogressbar.ui \
    qcwidget.ui

OTHER_FILES += \
    upgrade.pro.user \
    theme.qrc.autosave

RESOURCES += \
    theme.qrc
