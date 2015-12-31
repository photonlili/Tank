#include "qmsgbox.h"
#include "ui_qmsgbox.h"

QMsgBox::QMsgBox(QWidget *parent) :
    QMessageBox(parent),
    ui(new Ui::QMsgBox)
{
    ui->setupUi(this);
}

QMsgBox::~QMsgBox()
{
    delete ui;
}

QMessageBox::StandardButton QMsgBox::warning(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
{
    information(parent, title, text, tr("Yes"));
}
