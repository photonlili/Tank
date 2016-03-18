#include "qtankapp.h"
#include "qtankgui.h"
#include "qtankpublic.h"
#include "qtankdefine.h"

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

    language = new QTranslator(this);
    setLanguage();

    QFile styleFile(":/theme/basic/basic.qss");
    styleFile.open(QIODevice::ReadOnly);
    QString styleString(styleFile.readAll());;
    setStyleSheet(styleString);
    styleFile.close();

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
