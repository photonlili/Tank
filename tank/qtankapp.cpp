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

QTankApp::QTankApp(int &argc, char **argv) : QApplication(argc, argv)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication::setOrganizationName("Hanon");
    QApplication::setOrganizationDomain("hanon.com");  // 专为Mac OS X 准备的
    QApplication::setApplicationName("Tank");
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

    QHotplugWatcher::Instance();

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
