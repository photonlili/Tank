#include "hnapp.h"
#include "hngui-qt.h"
#include "hngui.h"
#include "HNDefine.h"

HNApp::HNApp(int &argc, char **argv) : QApplication(argc, argv)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication::setOrganizationName(VER_COMPANYNAME_STR);
    QApplication::setOrganizationDomain(VER_COMPANYDOMAIN_STR);  // 专为Mac OS X 准备的
    QApplication::setApplicationName(VER_PRODUCTNAME_STR);
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, CONFIG_PATH);
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, CONFIG_PATH);

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

    QFile styleFile("://HNWidgets.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    setStyleSheet(styleString);
    styleFile.close();

#ifdef __MIPS_LINUX__
    HNInput::Instance()->Init("min", "control", "hanon", 14, 14);
#endif

    HNPluginWatcher* watcher = HNPluginWatcher::Instance();
    QObject::connect(watcher, SIGNAL(storageChanged(int)), this, SLOT(slotUPanAutoRun(int)));

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    //HNClient
    HNClientInstance(this);
    //HNEthManager
    HNEthManager::Instance(this);
    //HNServer
    //HNPeerPort
    //HNSerialPort
}

HNApp::~HNApp() {}

void HNApp::setLanguage()
{
    QSettings setting;  //  公司或组织名  // 应用程序名
    int eLanguage = Language_English;
    eLanguage = setting.value("Language").toInt();
    Language_English == eLanguage ?
                language->load("://language/en_US.qm") :
                language->load("://language/zh_CN.qm");
    installTranslator(language);
}

void HNApp::slotUPanAutoRun(int status)
{
    if(HNPluginWatcher::E_ADD == status)
    {
        QString mP = HNPluginWatcher::Instance()->devMountPath();
        QString auth = QString("chmod +x %1/autorun.sh").arg(mP);
        QString app = QString("%1/autorun.sh").arg(mP);
        QFile file(app);
        if(file.exists())
            if(QDialog::Rejected == HNMsgBox::tips(0, tr("Some app want to run in u disk!accepted?")))
                return;
        system(auth.toAscii().constData());
        QProcess* p = new QProcess(this);
        p->setWorkingDirectory(mP);
        p->start(app);
    }
}
