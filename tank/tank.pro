#-------------------------------------------------
#
# Project created by QtCreator 2015-06-18T16:26:39
#
#-------------------------------------------------

QT += core gui sql network

CONFIG += serialport

TARGET = tank
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

RESOURCES += \
    theme.qrc

TRANSLATIONS = language/zh_CN.ts \
    language/en_US.ts

CODECFORTR = UTF-8

SOURCES += main.cpp\
        mainwindow.cpp \
    frminput.cpp \
    simplefile.cpp \
    txtrecode.cpp \
    logindialog.cpp \
    qdispelform.cpp \
    qmlabel.cpp \
    qeditform.cpp \
    qsetform.cpp \
    qcustomplot.cpp \
    qctabwidget.cpp \
    qctabbar.cpp \
    qsearchlineedit.cpp \
    qrunplot.cpp \
    qopenlibrary.cpp \
    dmmu.c \
    qsystemform.cpp \
    qtankapp.cpp \
    qtankwindow.cpp \
    qmethodview.cpp \
    qmethodmodel.cpp \
    qstageview.cpp \
    qstagemodel.cpp \
    qmethodwidget.cpp \
    qstagewidget.cpp \
    qcheaderview.cpp \
    qctableview.cpp \
    qcstackedwidget.cpp \
    quserlibrarymodel.cpp \
    quserlibraryview.cpp \
    quserlibrarywidget.cpp \
    qpreviewui.cpp \
    qhelpform.cpp \
    quserform.cpp \
    qcloudform.cpp \
    qmplayerui.cpp \
    qdevicewatcher.cpp \
    qdevicewatcher_linux.cpp \
    qhotplugwatcher.cpp \
    qtankpublic.cpp \
    qmsgbox.cpp \
    qtankfiledialog.cpp \
    qmplayermodel.cpp \
    qfactorysetpassform.cpp \
    qtankdatabase.cpp \
    qclistview.cpp \
    qusersetview.cpp \
    qusersetwidget.cpp \
    qusersetmodel.cpp \
    qwifiwidget.cpp \
    qwifimodel.cpp \
    qwifiview.cpp \
    qwifipassform.cpp \
    qcradiobutton.cpp \
    qcpushbutton.cpp \
    qctreeview.cpp \
    qcsqltablemodel.cpp \
    qcstandarditemmodel.cpp \
    qcwidget.cpp \
    qtankclient.cpp \
    qtankserver.cpp \
    qtankmessage.cpp \
    qcloudmodel.cpp \
    qcloudtreeview.cpp \
    qcloudtreewidget.cpp \
    qwifimanager.cpp \
    qmethodform.cpp \
    qstageplot.cpp \
    qlibraryform.cpp \
    qcspinbox.cpp \
    qcpdocumentobject.cpp \
    qcprinter.cpp \
    qcomponent.cpp \
    qtankpeermessage.cpp \
    qnewuser.cpp \
    hncheckbox.cpp \
    qcdialog.cpp \
    hnmsgbox.cpp \
    qcdatetime.cpp \
    qreportviewdialog.cpp \
    qcloudlocalmodel.cpp \
    hntabwidget.cpp \
    qdebugwidget.cpp \
    hnsyseventmodel.cpp \
    qsyseventview.cpp \
    qsyseventwidget.cpp \
    qcloudlocaltreewidget.cpp \
    qserialwarning.cpp \
    qtankserialmessage.cpp \
    qtankpeerport.cpp \
    qtankserialport.cpp \
    qtankexception.cpp \
    qexceptionmodel.cpp \
    qexceptionview.cpp \
    qexceptionwidget.cpp \
    qprogresswindow.cpp \
    qtankcrosscenter.cpp \
    hnprogressbar.cpp \
    hnupgradewidget.cpp

HEADERS  += mainwindow.h \
    frminput.h \
    simplefile.h \
    txtrecode.h \
    logindialog.h \
    qdispelform.h \
    qmlabel.h \
    qeditform.h \
    qsetform.h \
    qcustomplot.h \
    qctabwidget.h \
    qctabbar.h \
    qsearchlineedit.h \
    qrunplot.h \
    qopenlibrary.h \
    dmmu.h \
    graphics.h \
    hal.h \
    jz_cim.h \
    qsystemform.h \
    qtankapp.h \
    qtankwindow.h \
    qmethodview.h \
    qmethodmodel.h \
    qstageview.h \
    qheaders.h \
    qtankdefine.h \
    qstagemodel.h \
    qtanklinux.h \
    qtankgui.h \
    qtankpublic.h \
    qmethodwidget.h \
    qstagewidget.h \
    qcheaderview.h \
    qctableview.h \
    qcstackedwidget.h \
    quserlibrarymodel.h \
    quserlibraryview.h \
    quserlibrarywidget.h \
    qpreviewui.h \
    qhelpform.h \
    quserform.h \
    qcloudform.h \
    qmplayerui.h \
    qdevicewatcher.h \
    qdevicewatcher_p.h \
    qhotplugwatcher.h \
    qmsgbox.h \
    qtankfiledialog.h \
    qmplayermodel.h \
    qfactorysetpassform.h \
    qtankdatabase.h \
    qclistview.h \
    qusersetview.h \
    qusersetwidget.h \
    qusersetmodel.h \
    qwifiwidget.h \
    qwifimodel.h \
    qwifiview.h \
    qwifipassform.h \
    qcradiobutton.h \
    qcpushbutton.h \
    qcomponent.h \
    qctreeview.h \
    qcsqltablemodel.h \
    qcstandarditemmodel.h \
    qcwidget.h \
    qtankclient.h \
    qtankserver.h \
    qtankmessage.h \
    qcloudmodel.h \
    qcloudtreeview.h \
    qcloudtreewidget.h \
    qwifimanager.h \
    qmethodform.h \
    qstageplot.h \
    qlibraryform.h \
    qcspinbox.h \
    qcpdocumentobject.h \
    qcprinter.h \
    qtankpeermessage.h \
    qnewuser.h \
    hncheckbox.h \
    qcdialog.h \
    hnmsgbox.h \
    qcdatetime.h \
    qreportviewdialog.h \
    qcloudlocalmodel.h \
    hntabwidget.h \
    qdebugwidget.h \
    hnsyseventmodel.h \
    qsyseventview.h \
    qsyseventwidget.h \
    qcloudlocaltreewidget.h \
    qserialwarning.h \
    qtankserialmessage.h \
    qtankpeerport.h \
    qtankserialport.h \
    qtankexception.h \
    qexceptionmodel.h \
    qexceptionview.h \
    qexceptionwidget.h \
    qprogresswindow.h \
    qtankcrosscenter.h \
    hnprogressbar.h \
    hnupgradewidget.h

FORMS    += mainwindow.ui \
    frminput.ui \
    logindialog.ui \
    qdispelform.ui \
    qeditform.ui \
    qsetform.ui \
    qctabwidget.ui \
    qrunplot.ui \
    qopenlibrary.ui \
    qsystemform.ui \
    qtankwindow.ui \
    qmethodview.ui \
    qstageview.ui \
    qmethodwidget.ui \
    qstagewidget.ui \
    qctableview.ui \
    quserlibraryview.ui \
    quserlibrarywidget.ui \
    qpreviewui.ui \
    qhelpform.ui \
    quserform.ui \
    qcloudform.ui \
    qmplayerui.ui \
    qmsgbox.ui \
    qtankfiledialog.ui \
    qfactorysetpassform.ui \
    qusersetview.ui \
    qclistview.ui \
    qusersetwidget.ui \
    qwifiwidget.ui \
    qwifiview.ui \
    qwifipassform.ui \
    qcradiobutton.ui \
    qcpushbutton.ui \
    qctreeview.ui \
    qcwidget.ui \
    qcloudtreeview.ui \
    qcloudtreewidget.ui \
    qpreviewwidget.ui \
    qcstackedwidget.ui \
    qmethodform.ui \
    qstageplot.ui \
    qlibraryform.ui \
    qcspinbox.ui \
    qnewuser.ui \
    hncheckbox.ui \
    qcdialog.ui \
    hnmsgbox.ui \
    qcdatetime.ui \
    qreportviewdialog.ui \
    hntabwidget.ui \
    qdebugwidget.ui \
    qsyseventview.ui \
    qsyseventwidget.ui \
    qcloudlocaltreewidget.ui \
    qserialwarning.ui \
    qtankexception.ui \
    qexceptionview.ui \
    qexceptionwidget.ui \
    qprogresswindow.ui \
    hnprogressbar.ui \
    hnupgradewidget.ui

OTHER_FILES += \
    tank.pro.user
