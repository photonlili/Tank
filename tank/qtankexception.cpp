#include "qtankexception.h"
#include "ui_qtankexception.h"
#include "qtankpublic.h"
#include "qtankpeerport.h"

QTankException::QTankException(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QTankException)
{
    ui->setupUi(this);
    ui->widgetPic->setFixedSize(80, 80);
    ui->widgetPic->setPixmap("://theme/basic/bk_warning.png");
}

QTankException::~QTankException()
{
    delete ui;
}

void QTankException::newExcp(quint16 e)
{
    if( e == E_NOEXCEP)
    {
        ui->lwWarn->clear();
        return;
    }

    if( (e & E_DOOROPEN) == E_DOOROPEN)
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Oven door open"), ui->lwWarn);
        ui->lwWarn->addItem(item);
    }

    if( (e & E_CORRROR) == E_CORRROR)
    {
        QListWidgetItem* item = new QListWidgetItem(tr("COT Exception"), ui->lwWarn);
        ui->lwWarn->addItem(item);
    }

    if( (e & E_GUXIANERROR) == E_GUXIANERROR)
    {
        QListWidgetItem* item = new QListWidgetItem(tr("guangxianwenduchuanganqi error"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_SENSOR1ERR) == E_SENSOR1ERR)
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Optical fiber temperature sensor fault"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_SENSOR2ERR) == E_SENSOR2ERR)

    {
        QListWidgetItem* item = new QListWidgetItem(tr("Optical fiber temperature sensor fault 2"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_JIGUANG1) == E_JIGUANG1)

    {
        QListWidgetItem* item = new QListWidgetItem(tr("Infrared fault inner ring"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_JIGUANG2) == E_JIGUANG2)

    {
        QListWidgetItem* item = new QListWidgetItem(tr("The infrared failure outer ring"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_VOLERR) == E_VOLERR)

    {
        QListWidgetItem* item = new QListWidgetItem(tr("Abnormal voltage"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_POSION) == E_POSION)

    {
        QListWidgetItem* item = new QListWidgetItem(tr("Position sensor fault inner ring"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_MAINCOMM) == E_MAINCOMM)

    {
        QListWidgetItem* item = new QListWidgetItem(tr("Main communication failures"), ui->lwWarn);
        ui->lwWarn->addItem(item);

    }

    if( (e & E_RESET) == E_RESET)

    {
        QListWidgetItem* item = new QListWidgetItem(tr("Controler reset."), ui->lwWarn);
        ui->lwWarn->addItem(item);
    }

    //显示
    //保存到数据库
    return;
}

QTankException *HNSingleException(QWidget *parent)
{
    static QTankException* e = new QTankException(parent);
    return e;
}
