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
    qtankclient.cpp \
    qtankmessage.cpp \
    qtankpublic.cpp \
    qcomponent.cpp \
    hnprogressbar.cpp \
    qcwidget.cpp \
    qtankapp.cpp \
    hnmsgbox.cpp \
    qcdialog.cpp \
    qcheaderview.cpp \
    qcpushbutton.cpp \
    qcstandarditemmodel.cpp \
    qctableview.cpp \
    qcloudform.cpp \
    qcloudlocalmodel.cpp \
    qcloudlocaltreewidget.cpp \
    qcloudmodel.cpp \
    qcloudtreeview.cpp \
    qcloudtreewidget.cpp \
    qcsqltablemodel.cpp \
    qctreeview.cpp \
    qprogresswindow.cpp \
    qreportviewdialog.cpp \
    qcpdocumentobject.cpp \
    qcprinter.cpp \
    qcustomplot.cpp \
    qserialwarning.cpp

HEADERS  += \
    qtankclient.h \
    qtankmessage.h \
    qtanklinux.h \
    qtankpublic.h \
    qtankgui.h \
    qcomponent.h \
    qtankdefine.h \
    hnprogressbar.h \
    qcwidget.h \
    qtankapp.h \
    hnmsgbox.h \
    qcdialog.h \
    qcheaderview.h \
    qcpushbutton.h \
    qcstandarditemmodel.h \
    qctableview.h \
    qcloudform.h \
    qcloudlocalmodel.h \
    qcloudlocaltreewidget.h \
    qcloudmodel.h \
    qcloudtreeview.h \
    qcloudtreewidget.h \
    qcsqltablemodel.h \
    qctreeview.h \
    qprogresswindow.h \
    qreportviewdialog.h \
    qheaders.h \
    qcpdocumentobject.h \
    qcprinter.h \
    qcustomplot.h \
    qversion.h \
    qserialwarning.h

FORMS    += \
    hnprogressbar.ui \
    qcwidget.ui \
    hnmsgbox.ui \
    qcdialog.ui \
    qcpushbutton.ui \
    qctableview.ui \
    qcloudform.ui \
    qcloudlocaltreewidget.ui \
    qcloudtreeview.ui \
    qcloudtreewidget.ui \
    qctreeview.ui \
    qprogresswindow.ui \
    qreportviewdialog.ui \
    qserialwarning.ui

OTHER_FILES += \
    upgrade.pro.user \
    theme.qrc.autosave \
    HNCloudServiceDemo.pro.user

RESOURCES += \
    theme.qrc
