#include "qtankapp.h"
#include "mainwindow.h"
#include "qtankgui.h"
#include "frminput.h"
#include "logindialog.h"
#include "qtankpublic.h"
#include "qsystemform.h"
#include "qtankwindow.h"
#include "qtankdefine.h"
#include "qhotplugwatcher.h"
#include "hnmsgbox.h"
#include "hanonkeyring.h"

QTankApp::QTankApp(int &argc, char **argv) : QApplication(argc, argv)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
#endif

    QApplication::setOrganizationName("Hanon");
    QApplication::setOrganizationDomain("hanon.com");  // 专为Mac OS X 准备的
    QApplication::setApplicationName("Tank");
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, CONFIG_PATH);
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, CONFIG_PATH);
    QSettings::setUserIniPath(CONFIG_PATH);
    QSettings::setSystemIniPath(CONFIG_PATH);

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QApplication::setGraphicsSystem("raster");
#endif

#ifdef __MIPS_LINUX__
    //QApplication::setOverrideCursor(Qt::ArrowCursor);
    QWSServer::setCursorVisible(false);
#endif

#ifdef __MIPS_LINUX__
    QString fontName;
    QFontDatabase db;
    int fontId = db.addApplicationFont("/usr/lib/fonts/heiti.ttf");
    fontName = db.applicationFontFamilies ( fontId ).at(0);
    pline() << fontName;
    QFont font(fontName, 14);
    QApplication::setFont(font);
#endif

    pline() << qApp->applicationDirPath();

    language = new QTranslator(this);

    setLanguage();

    //打开方法数据库
    managerDB = newDatabaseConn();
    setDatabaseName(managerDB, DB_MANAGER);

    //加载qss，几乎没有耗时，应该时打印图片引起的加载速度慢
    //pline() << QDateTime::currentDateTime();
    QFile styleFile(":/theme/basic/basic.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    setStyleSheet(styleString);
    styleFile.close();

#ifdef __MIPS_LINUX__
    frmInput::Instance()->Init("min", "control", "hanon", 14, 14);
#endif

    QHotplugWatcher* watcher = QHotplugWatcher::Instance();
    QObject::connect(watcher, SIGNAL(storageChanged(int)), this, SLOT(slotUPanAutoRun(int)));

    HanonKeyRingInstance(this);

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

}

QTankApp::~QTankApp() {}

void QTankApp::setLanguage()
{
    QSettings setting;  //  公司或组织名  // 应用程序名
    int eLanguage = Language_English;
    eLanguage = setting.value("Language").toInt();
    Language_English == eLanguage ?
                language->load("://language/en_US.qm") :
                language->load("://language/zh_CN.qm");
    installTranslator(language);
}

void QTankApp::slotUPanAutoRun(int status)
{
    if(QHotplugWatcher::E_ADD == status)
    {
#if 0
        /*作为保留意见，U盘调试能力，暂时还没遇到过，在出厂后如果也没遇到那么废弃*/
        QString mP = QHotplugWatcher::Instance()->upanMountPath();
        QString app = QString("%1/upgrade.sh").arg(mP);

        QFile file(app);
        if(!file.exists())
            return;

        if(QDialog::Rejected == HNMsgBox::question(0, tr("发现升级程序,是否升级？")))
            return;

        QString auth = QString("chmod +x %1/upgrade.sh").arg(mP);
        system(auth.toAscii().constData());

        QString cmd = QString("bash -c %1/upgrade.sh").arg(mP);
        system(cmd.toAscii().constData());
#else
        QString mP = QHotplugWatcher::Instance()->devMountPath();
        QString app = QString("%1/upgrade.tar.gz").arg(mP);

        QFile file(app);
        if(!file.exists())
            return;

        if(QDialog::Rejected == HNMsgBox::question(0, tr("发现升级包,是否升级？")))
            return;

        HNMsgBox box;
        box.information("正在升级...");

        QString cmd = QString("/usr/bin/tar xzvf %1/upgrade.tar.gz -C /").arg(mP);

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)

        system(cmd.toAscii().constData());;
#else
        system(cmd.toLocal8Bit().constData());
#endif
        box.information("正在重启...");

        system("reboot");
#endif

    }
}
