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
    if(e&0x0000 == 1)
        //正常
    {
        ui->lwWarn->clear();
        return;
    }
    else if(e&0x0001 == 1)
        //炉门打开提示
    {

        QListWidgetItem* item = new QListWidgetItem(tr("Oven door open"), ui->lwWarn);
        ui->lwWarn->addItem(item);
    }
    else if(e&0x0002 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("COT Exception"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
    }
    else if(e&0x0004 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Optical fiber temperature sensor fault"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
    }
    else if(e&0x0008 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Optical fiber temperature sensor fault 2"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
    }
    else if(e&0x0010 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Infrared fault inner ring"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
    }
    else if(e&0x0020 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("The infrared failure outer ring"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
    }
    else if(e&0x0040 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Abnormal voltage"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
    }
    else if(e&0x0080 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Position sensor fault inner ring"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
    }
    else if(e&0x0100 == 1)
        //炉门打开提示
    {
        QListWidgetItem* item = new QListWidgetItem(tr("Main communication failures"), ui->lwWarn);
        ui->lwWarn->addItem(item);
        ;
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
