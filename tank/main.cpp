#include "qtankwindow.h"
#include "qtankapp.h"
#include "qtankpublic.h"
#include "qtankgui.h"
#include "qtankserialport.h"
#include "qserialwarning.h"
#include "qtankexception.h"
#include "qtankcrosscenter.h"
#include "qtankserver.h"

int main(int argc, char *argv[])
{
    //日志功能
    qInstallMsgHandler(msgHandler);
    QDir dir("./log", "*.txt");
    if(dir.count() >= 30)
        dir.remove(dir[0]);
    dir.refresh();

    //创建应用实例
    QTankApp* theApp = new QTankApp(argc, argv);
    QTankWindow* theWindow  = new QTankWindow();
    QObject::connect(theWindow, SIGNAL(changeLanguage()), theApp, SLOT(setLanguage()));

    //显示应用
#ifdef __MIPS_LINUX__
    theWindow->showFullScreen();
#else
    theWindow->showNormal();
    moveRight(theWindow);
#endif

    //检查序列号
    QSettings set;
    QString serial = set.value("/Device/SerialNo.").toString();
    if(serial.isEmpty())
    {
        QSerialWarning war(theWindow);
        theWindow->slotSerialLock();
        QTankSerialPort* s2 = HNSerialPort(theWindow);
        QObject::connect(s2, SIGNAL(sigSerialUnlock()), theWindow, SLOT(slotSerialUnLock()));
        QObject::connect(s2, SIGNAL(sigSerialUnlock()), &war, SLOT(accept()));
        war.exec();
    }

    HNSingleServer(theApp);

    //消息循环
    return theApp->exec();
}
