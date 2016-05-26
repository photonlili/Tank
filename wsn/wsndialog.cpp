#include "wsndialog.h"
#include "ui_wsndialog.h"

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
