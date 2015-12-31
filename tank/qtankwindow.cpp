#include "qtankwindow.h"
#include "ui_qtankwindow.h"

QTankWindow::QTankWindow(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::QTankWindow)
{
    ui->setupUi(this);

#ifdef __MIPS_LINUX__
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
#endif
    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QSettings setting;
    int bOpenRights = false;
    bOpenRights = setting.value("UserRights").toInt();

    connect(ui->page_login, SIGNAL(signalStatus(int)), this, SLOT(slotStatus(int)));
    connect(ui->page_main, SIGNAL(signalLogout()), this, SLOT(slotLogout()));
    connect(ui->page_main, SIGNAL(changeLanguage()), ui->page_login, SLOT(initlanguage()));
    connect(ui->page_main, SIGNAL(changeLanguage()), this, SIGNAL(changeLanguage()));

    if(bOpenRights)
        slotStatus(Login_Request);
    else
    {
        QSqlQuery query(managerDB);
        QString id, admin, pwd;
        query.exec(QString("SELECT * FROM %1 WHERE Name = 'Admin'")
                   .arg(TABLE_USERINFO));
        if (query.next()) {
            id = query.value(Auth_Id).toString();
            admin = query.value(Auth_Name).toString();
            pwd = query.value(Auth_Passwd).toString();
        }

        QSettings set;
        QString did = set.value("DefaultLogin").toString();
        query.exec(QString("SELECT * FROM %1 WHERE id = '%2'")
                   .arg(TABLE_USERINFO).arg(did));

        if (query.next()) {
            gUserName = query.value(Auth_Name).toString();
            gPassword = query.value(Auth_Passwd).toString();
        }
        else
        {
            //如果没有部署配置文件 这些代码就必须有。
            set.setValue("DefaultLogin", id);
            set.sync();
            gUserName = admin;
            gPassword = pwd;
        }
        query.finish();
        slotStatus(Login_Success);
    }
}

QTankWindow::~QTankWindow()
{
    delete ui;
}

void QTankWindow::slotLogout()
{
    slotStatus(Login_Request);
}

void QTankWindow::slotSerialLock()
{
    ui->page_main->slotSerialLocked();
}

void QTankWindow::slotSerialUnLock()
{
    ui->page_main->slotSerialUnlocked();
}

void QTankWindow::slotStatus(int index)
{
    switch(index)
    {
    case Login_Request:
        {
            ui->page_login->initAll();
            setCurrentIndex(0);
        }
        break;
    case Login_Success:
        {
            ui->page_main->initAll();
            setCurrentIndex(1);
        }
        break;
    default:
        break;
    }
}
