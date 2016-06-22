#include "wsndialog.h"
#include "ui_wsndialog.h"
#include "HNDefine.h"
#include "version.h"

WSNDialog::WSNDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WSNDialog)
{
    ui->setupUi(this);
}

WSNDialog::~WSNDialog()
{
    delete ui;
}

void WSNDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void WSNDialog::on_btnWrite_clicked()
{
    //在程序目录中执行
    QApplication::setOrganizationName(VER_COMPANYNAME_STR);
    QApplication::setOrganizationDomain(VER_COMPANYDOMAIN_STR);  // 专为Mac OS X 准备的


    QApplication::setApplicationName(ui->cbApp->currentText());

    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope, CONFIG_PATH);
    QSettings::setPath(QSettings::NativeFormat, QSettings::SystemScope, CONFIG_PATH);

    QSettings set;
    set.setValue("Device/DeviceNo", ui->leSerial->text().toAscii().toUpper());
    set.sync();
}
