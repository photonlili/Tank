#include "qtankexception.h"
#include "ui_qtankexception.h"
#include "qtankpublic.h"

QTankException::QTankException(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QTankException)
{
    ui->setupUi(this);
    ui->widgetPic->setFixedSize(80, 80);
    ui->widgetPic->setPixmap("://theme/basic/bk_warning.png");
    nCount = 0;
}

QTankException::~QTankException()
{
    delete ui;
}

int QTankException::newExcp(QString content)
{
    //显示
    QListWidgetItem* item = new QListWidgetItem(content, ui->lwWarn);
    int id = newId();
    item->setData(Qt::UserRole, id);
    ui->lwWarn->addItem(item);
    //保存到数据库
    return id;
}

void QTankException::delExcp(int id)
{
    //删除
    QListWidgetItem* item;
    for(int i = 0; i < ui->lwWarn->count(); i++)
    {
        item = ui->lwWarn->item(i);
        int uid = item->data(Qt::UserRole).toInt();
        pline() << uid << id;
        if(uid == id)
        {
            ui->lwWarn->removeItemWidget(item);
            delete item;
            break;
        }
    }
}

int QTankException::newId()
{
    if(ui->lwWarn->count() == 0)
        nCount = 1;
    else
        nCount ++;
    return nCount;
}


QTankException *HNSingleException(QWidget *parent)
{
    static QTankException* e = new QTankException(parent);
    return e;
}
