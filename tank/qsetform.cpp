#include "qsetform.h"
#include "ui_qsetform.h"
#include "qctabbar.h"
#include <QDebug>
#include <QListView>
#include "QWSServer"
#include "QMouseDriverFactory"
#include "QRegExp"
#include "QRegExpValidator"
#include "QDateTime"
#include "QSettings"
#include "qtankpublic.h"
#include "qtanklinux.h"
#include "qtankdefine.h"
#include "qmsgbox.h"
#include "qwifipassform.h"
#include "HNEthManager.h"
#include "qtanklinux.h"
#include "qnewuser.h"
#include "hnmsgbox.h"
#include "qversion.h"
#include <QThread>
#include "qhotplugwatcher.h"

class QBackupThread : public QThread
{
public:
    explicit QBackupThread(QObject* parent = 0);

    void setProgressWidget(QProgressWindow* prog) { m_prog = prog; }
    // QThread interface
protected:
    void run();

private:
    QProgressWindow* m_prog;
};

void QBackupThread::run()
{
    QDir d(QHotplugWatcher::Instance()->devMountPath());
    if(!d.exists())
    {
        QMetaObject::invokeMethod(parent(), "slotInvokeWarning", Q_ARG(QString, tr("Please Check U Disk!")));
        return;
    }
#ifdef __MIPS_LINUX__
    QMetaObject::invokeMethod(m_prog, "setValue", Q_ARG(int, 16));
    system("rm -f /mnt/usb_sda1/backup.tar.gz");
    QMetaObject::invokeMethod(m_prog, "setValue", Q_ARG(int, 36));
    system("tar czvf /mnt/usb_sda1/backup.tar.gz /HNApp/tank");
    QMetaObject::invokeMethod(m_prog, "setValue", Q_ARG(int, 100));
    QMetaObject::invokeMethod(parent(), "slotInvokeWarning", Q_ARG(QString, tr("Backup success")));
#endif
}


QBackupThread::QBackupThread(QObject *parent) : QThread(parent)
{

}

QSetForm::QSetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSetForm)
{
    ui->setupUi(this);

    QLineEdit* lineEdit[4];
    lineEdit[0] = ui->lineEdit_ip;
    lineEdit[1] = ui->lineEdit_mask;
    lineEdit[2] = ui->lineEdit_gateway;
    lineEdit[3] = ui->lineEdit_dns;

    QRegExp regExp("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)");
    QRegExpValidator *pValidator = new QRegExpValidator(regExp, this);
    for(int i = 0; i < 4; i++)
    {
        lineEdit[i]->setValidator(pValidator);
        lineEdit[i]->setInputMask("000.000.000.000");
    }

    connect(ui->dateYear, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateTimeChanged(QDateTime)));
    connect(ui->dateTime, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(dateTimeChanged(QDateTime)));
    connect(ui->checkBox_userrights, SIGNAL(stateChanged(int)), this, SLOT(userRightsChanged(int)));
    connect(ui->chkDebug, SIGNAL(stateChanged(int)), this, SIGNAL(showDebugWindow(int)));
    connect(ui->radioButton_english, SIGNAL(toggled(bool)), this, SLOT(englishPressed(bool)));
    connect(ui->radioButton_chinese, SIGNAL(toggled(bool)), this, SLOT(chinesePressed(bool)));
    ui->tabWidget_set->tabBar()->installEventFilter(this);

    ui->lineEdit_set_password->setEchoMode(QLineEdit::Password);
    ui->comboBox_set_authority->setModel(ui->tableView_userlist->model()->relationModel(Auth_Authrity));
    ui->comboBox_set_authority->setModelColumn(ui->tableView_userlist->model()->relationModel(Auth_Authrity)->fieldIndex("Authority"));
    ui->tableView_userlist->addMap(ui->lineEdit_set_name, Auth_Name);
    ui->tableView_userlist->addMap(ui->lineEdit_set_password, Auth_Passwd);
    ui->tableView_userlist->addMap(ui->comboBox_set_authority, Auth_Authrity);
    ui->tableView_userlist->addMap(ui->le_creater, Auth_Creater);
    ui->tableView_userlist->addMap(ui->le_createtime, Auth_CreateTime);
    ui->tableView_userlist->addMap(ui->textEdit_set_comment, Auth_Comment);
    connect(ui->tableView_userlist->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(currentUserChanged()));
    connect(ui->pushButton_set_new, SIGNAL(clicked()), this, SLOT(newUser()));
    connect(ui->pushButton_set_del, SIGNAL(clicked()), this, SLOT(delUser()));
    connect(HNEthManager::Instance(), SIGNAL(sigConnected()), this, SLOT(netChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigDisConnected()), this, SLOT(netChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanConnected()), this, SLOT(netChanged()));
    connect(HNEthManager::Instance(), SIGNAL(sigLanDisConnected()), this, SLOT(netChanged()));

    m_facPass = new QFactorySetPassForm(this);
    ui->scb_bcklight->setRange(5, 255);
    ui->scb_bcklight->setValue(240);

    ui->label_setlanguage->setFixedHeight(30);
    ui->label_userrights->setFixedHeight(30);
    ui->label_settime->setFixedHeight(30);
    ui->label_steering->setFixedHeight(30);
    ui->radioButton_chinese->setFixedSize(100,30);
    ui->radioButton_english->setFixedSize(100,30);
    ui->widget_time->setFixedWidth(218);
    ui->widget_language->setFixedWidth(218);
    ui->widget_userrights->setFixedWidth(218);
    ui->widget_steering->setFixedWidth(218);
    ui->radioButton_turn0->setFixedSize(100,40);
    ui->radioButton_turn1->setFixedSize(100,40);
    ui->checkBox_userrights->setFixedSize(100, 40);

    ui->lb_serial->setFixedSize(300, 60);
    QPalette plt = ui->lb_serial->palette();
    ui->lb_serial->setAutoFillBackground(true);
    plt.setColor(QPalette::Window, QColor(Qt::black));
    plt.setColor(QPalette::WindowText, QColor(Qt::red));
    ui->lb_serial->setPalette(plt);

    QBackupThread* t = new QBackupThread(this);
    connect(ui->btnUpgrade, SIGNAL(clicked()), this, SIGNAL(sigUpgrade()));
    connect(ui->btnBackup, SIGNAL(clicked()), t, SLOT(start()));
    connect(QHotplugWatcher::Instance(), SIGNAL(storageChanged(int)), this, SLOT(slotStorageChanged(int)));

    prog = new QProgressWindow(this);
    prog->initAll();

    t->setProgressWidget(prog);

    com0 = HNPeerPort(this);
    connect(com0, SIGNAL(sigCaliAck(quint16,quint16,quint16,quint16)),
            this, SLOT(slotCalibrateAck(quint16,quint16,quint16,quint16)));
    ui->sbFiber->setRange(-128, 127);
    ui->sbSensor->setRange(-128, 127);
    ui->sbSensor2->setRange(-128, 127);
    ui->sbPress->setRange(-128, 127);

    ui->lb_log->setFixedHeight(30);

    timer = new QTimer(this);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotCalibrate()));

}

QSetForm::~QSetForm()
{
    delete ui;
}

void QSetForm::initAll()
{
    if(!HNEthManager::Instance()->dhcp())
    {
        QString ip, mask, gw, dns;
        HNEthManager::Instance()->getAddr(ip, mask, gw, dns);
        ui->lineEdit_ip->setText(ip);
        ui->lineEdit_mask->setText(mask);
        ui->lineEdit_gateway->setText(gw);
        ui->lineEdit_dns->setText(dns);
    }

    QDateTime dateTime = QDateTime::currentDateTime();
    ui->dateYear->setDate(dateTime.date());
    ui->dateTime->setTime(dateTime.time());
    //ui->dateTimeEdit->setDateTime(dateTime);

    QSettings setting;
    int bCheked = false;
    bCheked = setting.value("UserRights").toInt();
    ui->checkBox_userrights->setChecked(bCheked);
    bCheked = setting.value("/Network/EnableDHCP").toInt();
    ui->chk_dhcp->setChecked(bCheked);

    int eLanguage = Language_English;
    eLanguage = setting.value("Language").toInt();
    Language_English == eLanguage ? ui->radioButton_english->setChecked(true) :
                ui->radioButton_chinese->setChecked(true);

    int oneway = setting.value("OneWayTurn", 1).toInt();
    1 == oneway ? ui->radioButton_turn0->setChecked(true) :
                ui->radioButton_turn1->setChecked(true);

    ui->tableView_userlist->refresh();
    QSettings set;
    int id = set.value("DefaultLogin").toInt();
    ui->tableView_userlist->selectUser(id);

    QString sn = set.value("Device/DeviceNo").toString();

    ui->lb_serial_2->setText(sn);

    ui->lbVer->setText(VER_FILEVERSION_STR);

    quint8 sen1 = set.value("Machine/Fiber").toUInt();
    quint8 sen2 = set.value("Machine/Sen1").toUInt();
    quint8 sen3 = set.value("Machine/Sen2").toUInt();
    quint8 sen4 = set.value("Machine/Press").toUInt();
    ui->sbFiber->setValue(sen1);
    ui->sbSensor->setValue(sen2);
    ui->sbSensor2->setValue(sen3);
    ui->sbPress->setValue(sen4);

}

void QSetForm::userRightsChanged(int bChecked)
{
    QSettings setting;
    setting.setValue("UserRights", bChecked);
    setting.sync();
}

void QSetForm::englishPressed(bool bChecked)
{
    pline() << bChecked;
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue("Language", Language_English);
    setting.sync();
    emit changeLanguage();
}

void QSetForm::chinesePressed(bool bChecked)
{
    if(!bChecked)
        return;
    QSettings setting;
    setting.setValue("Language", Language_Chinese);
    setting.sync();
    emit changeLanguage();
}

void QSetForm::dateTimeChanged(QDateTime dt)
{
    QString date = "date -s \"";
    date += ui->dateYear->date().toString("yyyy-MM-dd");
    date += " ";
    date += ui->dateTime->time().toString("hh:mm:ss");
    date += "\"";
    system(date.toAscii());
    //ignore
    //time_t tt = (time_t)dt.toTime_t();
    //只有超级权限的用户才可以使用成功
    //int r = stime(&tt);
    //同步到硬件时钟
    system("hwclock -w");
}

void QSetForm::currentUserChanged()
{
    QString name = ui->tableView_userlist->currentUser();
    bool bchecked = false;

    //if(name == "Admin")
    bchecked = true;

    ui->comboBox_set_authority->setDisabled(bchecked);
    ui->lineEdit_set_name->setDisabled(bchecked);
    ui->lineEdit_set_password->setDisabled(bchecked);
    ui->le_creater->setDisabled(bchecked);
    ui->le_createtime->setDisabled(bchecked);
    ui->textEdit_set_comment->setDisabled(bchecked);
    ui->tableView_userlist->updateMap();
}

void QSetForm::newUser()
{
    static QNewUser* newUserForm = new QNewUser(this);

    if(gAuthority == 2)
    {
        HNMsgBox::warning(this, tr("You have no authority"));
        return;
    }

    newUserForm->initAll();
    int result = newUserForm->exec();
    if(QDialog::Rejected == result)
        return;

    QString name, pwd, confirm, auth, comment;
    newUserForm->userInfo(name, pwd, confirm, auth, comment);
    pline() << name << pwd << confirm << auth << comment;

    if(name.isEmpty())
    {
        //QMsgBox::warning(this, tr("Warning"), tr("Name couldn't be empty"));
        HNMsgBox::warning(this, tr("Name couldn't be empty"));
        return;
    }
    int count = 0;
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT COUNT(*) FROM User WHERE Name = '%1'").arg(name));
    if(query.next())
        count = query.record().value(0).toInt();
    query.finish();

    if(count > 0)
    {
        //QMsgBox::warning(this, tr("Warning"), tr("This user is existed"));
        HNMsgBox::warning(this, tr("This user is existed"));
        return;
    }
    if(confirm != pwd)
    {
        //QMsgBox::warning(this, tr("Warning"), tr("Password confirm is not equal to password"));
        HNMsgBox::warning(this, tr("Password confirm is not equal to password"));
        return;
    }

    ui->tableView_userlist->newUser(name, pwd, auth, comment);
}

void QSetForm::delUser()
{
    if(ui->tableView_userlist->currentUser() == "Admin")
    {
        //QMsgBox::warning(this, "Warning", "You can't delete default user");
        HNMsgBox::warning(this, tr("You can't delete default user"));
        return;
    }
    ui->tableView_userlist->delUser();
}

void QSetForm::saveUser()
{
    if(ui->lineEdit_set_name->text().isEmpty())
    {
        //QMsgBox::warning(this, tr("Warning"), tr("Name couldn't be empty"));
        HNMsgBox::warning(this, tr("Name couldn't be empty"));
        return;
    }
    QString name = ui->tableView_userlist->currentUser();
    if(name != ui->lineEdit_set_name->text())
    {
        int count = 0;
        QSqlQuery query(managerDB);
        query.exec(QString("SELECT COUNT(*) FROM User WHERE Name = '%1'").arg(ui->lineEdit_set_name->text()));
        if(query.next())
            count = query.record().value(0).toInt();
        query.finish();

        if(count > 0)
        {
            //QMsgBox::warning(this, "Warning", "This user is existed");
            HNMsgBox::warning(this, tr("This user is existed"));
            return;
        }
    }
    //if(ui->lineEdit_set_password->text() != ui->lineEdit_set_confirm->text())
    //{
    //    QMsgBox::warning(this, "Warning", "Password confirm is not equal to password");
    //    return;
    //}
    ui->tableView_userlist->saveMap();
    ui->tableView_userlist->selectUser(name);
    //QMsgBox::information(this, "Infomation", "Save success");
    HNMsgBox::warning(this, tr("Save success"));
}

void QSetForm::netChanged()
{
    QString netName;
    if("Wired Lan" == HNEthManager::Instance()->currentNetName())
    {
        netName = tr("Current:Wired Lan");
        ui->tableView_Wifi->setEnabled(false);
    }
    else
    {
        netName = tr("Current:%1").arg(HNEthManager::Instance()->currentNetName());
        ui->tableView_Wifi->setEnabled(true);
    }
    ui->lb_curnet->setText(netName);
}

void QSetForm::timerSetTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    //ui->dateTimeEdit->setDateTime(dt);
}

void QSetForm::slotSerialLock()
{
    ui->tabWidget_set->setCurrentIndex(4);
    ui->stackedWidget->setCurrentIndex(1);
}

void QSetForm::slotSerialUnlock()
{
    ui->tabWidget_set->setCurrentIndex(0);
    ui->stackedWidget->setCurrentIndex(0);
}

void QSetForm::slotInvokeWarning(QString msg)
{
    HNMsgBox::warning(this, msg);
}

void QSetForm::slotStorageChanged(int stat)
{
    if(stat == QHotplugWatcher::E_ADD)
        ui->lbBackup->setText(tr("U disk ready!"));
    else if(stat == QHotplugWatcher::E_RM)
        ui->lbBackup->setText(tr("Please insert u disk."));
}

void QSetForm::slotCalibrate()
{
    quint8 sen1 = ui->sbFiber->value();
    quint8 sen2 = ui->sbSensor->value();
    quint8 sen3 = ui->sbSensor2->value();
    quint8 sen4 = ui->sbPress->value();
    com0->sendCalibrate(sen1, sen2, sen3, sen4, 0);
}

void QSetForm::slotCalibrateAck(quint16 a, quint16 a1, quint16 a2, quint16 a3)
{
    ui->lbFiber->setText(QString::number(a));
    ui->lbSensor->setText(QString::number(a1));
    ui->lbSensor2->setText(QString::number(a2));
    ui->lbPressure->setText(QString::number(a3));
}

void QSetForm::initLanguage()
{
    ui->retranslateUi(this);
    m_facPass->initLanguage();
    ui->tableView_userlist->initLanguage();

    QSettings set;

    QString sn = set.value("Device/DeviceNo").toString();

    ui->lb_serial_2->setText(sn);

    ui->lbVer->setText(VER_FILEVERSION_STR);

}

#define FAC_PAGE_NUMBER 6
#define CALI_PAGE_NUMBER 2

bool QSetForm::eventFilter(QObject * obj, QEvent * e)
{
    if(ui->tabWidget_set->tabBar() == obj && e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* me = (QMouseEvent*)e;
        if(m_facPass->isHidden() &&
                ui->tabWidget_set->currentIndex() != FAC_PAGE_NUMBER &&
                ui->tabWidget_set->tabBar()->tabRect(FAC_PAGE_NUMBER).contains(me->pos()))
        {
            if(gAuthority == 2)
            {
                HNMsgBox::warning(this, tr("You have no authority"));
                me->accept();
                return true;
            }

            m_facPass->initAll();
            moveCenter(m_facPass);
            m_facPass->exec();
            if(m_facPass->result() == QFactorySetPassForm::Rejected)
            {
                me->accept();
                return true;
            }
        }
        else if(ui->tabWidget_set->currentIndex() != CALI_PAGE_NUMBER &&
                ui->tabWidget_set->tabBar()->tabRect(CALI_PAGE_NUMBER).contains(me->pos()))
        {
            //qieru calibrate
            int r = HNMsgBox::question(this, tr("Start machine calibrate?"));
            if(r == HNMsgBox::Rejected)
            {
                return true;
            }
            timer->start(700);
        }
        else if(ui->tabWidget_set->currentIndex() == CALI_PAGE_NUMBER &&
                !ui->tabWidget_set->tabBar()->tabRect(CALI_PAGE_NUMBER).contains(me->pos()))
        {
            //qiechu calibrate
            timer->stop();
        }
        else
        {

        }
    }

    return QObject::eventFilter(obj, e);
}

void QSetForm::on_scb_bcklight_valueChanged(int value)
{
    char bcklight[20];
    bzero(bcklight, 20);
    sprintf(bcklight, "%d", value);
    int fd = ::open("/sys/devices/platform/pwm-backlight.0/backlight/pwm-backlight.0/brightness", O_RDWR|O_NONBLOCK);
    ::write(fd, bcklight, strlen(bcklight));
    ::close(fd);
}

void QSetForm::on_btn_calibrate_clicked()
{
    QDesktopWidget* desktop = qApp->desktop();
    desktop->hide();
    system("ts_calibrate");
    desktop->show();
}

void QSetForm::on_btn_saveip_clicked()
{
    HNEthManager::Instance()->configIPAddress(ui->lineEdit_ip->text(), ui->lineEdit_mask->text(),
                                              ui->lineEdit_gateway->text(), ui->lineEdit_dns->text());
}

void QSetForm::on_chk_dhcp_stateChanged(int bChecked)
{
    QSettings setting;
    setting.setValue("/Network/EnableDHCP", bChecked);
    setting.sync();

    // 2 -3, 0 -1 这里存在浮点运算错误
    //pline() << bChecked << ~bChecked;
    bool ret = bChecked?true:false;
    HNEthManager::Instance()->setDHCP(ret);

    ui->lineEdit_ip->setDisabled(bChecked);
    ui->lineEdit_mask->setDisabled(bChecked);
    ui->lineEdit_gateway->setDisabled(bChecked);
    ui->lineEdit_dns->setDisabled(bChecked);

    if(!ret)
    {
        QString ip,mask,gw,dns;
        HNEthManager::Instance()->getAddr(ip, mask, gw, dns);
        ui->lineEdit_ip->setText(ip);
        ui->lineEdit_mask->setText(mask);
        ui->lineEdit_gateway->setText(gw);
        ui->lineEdit_dns->setText(dns);
    }
    else
    {
        ui->lineEdit_ip->clear();
        ui->lineEdit_mask->clear();
        ui->lineEdit_gateway->clear();
        ui->lineEdit_dns->clear();
    }
}

void QSetForm::on_btnRestore_clicked()
{
    //恢复出厂设置
    QSettings set;

    //语言？
    set.setValue("Language", 0);
    //开机是否允许登陆？
    set.setValue("/Network/EnableDHCP", 0);
    //默认登陆用户
    set.setValue("DefaultLogin", 0);
    //网络设置
    set.setValue("DNS", "192.168.0.1");
    set.setValue("Gateway", "192.168.0.1");
    set.setValue("IP", "192.168.0.107");
    set.setValue("Mask", "255.255.255.0");
    //主题
    set.setValue(QString("%1/Theme").arg(gUserName), "blue");
    set.setValue(QString("%1/lastDB").arg(gUserName), "Hanon");

    //头像
    set.setValue(QString("%1/Pic").arg(gUserName), "user1");

    set.sync();
    HNMsgBox* box = new HNMsgBox(this);
    box->warning(tr("Restarting..."));

    system("reboot");
}

void QSetForm::on_btnCalibrate_clicked()
{
    timer->stop();

    quint8 sen1 = ui->sbFiber->value();
    quint8 sen2 = ui->sbSensor->value();
    quint8 sen3 = ui->sbSensor2->value();
    quint8 sen4 = ui->sbPress->value();
    com0->sendCalibrate(sen1, sen2, sen3, sen4, 1);

    QSettings set;
    set.setValue("Machine/Fiber", sen1);
    set.setValue("Machine/Sen1", sen2);
    set.setValue("Machine/Sen2", sen3);
    set.setValue("Machine/Press", sen4);
    set.sync();

    HNMsgBox::warning(this, tr("Params saved!"));
    timer->start(700);
}

void QSetForm::on_radioButton_turn0_toggled(bool checked)
{
    pline() << checked;
    if(!checked)
        return;
    QSettings setting;
    setting.setValue("OneWayTurn", 1);
    setting.sync();
}

void QSetForm::on_radioButton_turn1_toggled(bool checked)
{
    pline() << checked;
    if(!checked)
        return;
    QSettings setting;
    setting.setValue("OneWayTurn", 0);
    setting.sync();
}

void QSetForm::on_btnRecovery_clicked()
{
    QDir d(QHotplugWatcher::Instance()->devMountPath());
    if(!d.exists())
    {
        HNMsgBox::warning(this, tr("Please Check U Disk!"));
        return;
    }
    QString file = d.absoluteFilePath("upgrate.tar.gz");
    QFile f(file);
    if(!f.exists())
    {
        HNMsgBox::warning(this, tr("Please Check Upgrade package!"));
        return;
    }

    system("tar xzvf /mnt/usb_sda1/upgrade.tar.gz -C /");
}
