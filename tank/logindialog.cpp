#include "logindialog.h"
#include "ui_logindialog.h"
#include <QSqlQuery>
#include <QDebug>
#include "QFontDialog"
#include "QSqlResult"
#include "qmsgbox.h"
#include "hnmsgbox.h"

QLoginDialog::QLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QLoginDialog)
{
    ui->setupUi(this);

    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);

    connect(ui->pushButton_login, SIGNAL(clicked()), this, SLOT(login()));
}

QLoginDialog::~QLoginDialog()
{
    delete ui;
}

void QLoginDialog::initAll()
{
    ui->cbox_name->clear();
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT * FROM %1").arg(TABLE_USERINFO));

    while (query.next()) {
        ui->cbox_name->addItem(query.value(Auth_Name).toString());
    }
    query.finish();

}

void QLoginDialog::login()
{
    QSqlQuery query(managerDB);
    query.exec(QString("SELECT * FROM %1 WHERE Name = '%2'")
               .arg(TABLE_USERINFO).arg(ui->cbox_name->currentText()));

    if (query.next()) {
        gUserName = query.value(Auth_Name).toString();
        gPassword = query.value(Auth_Passwd).toString();
        if(!gPassword.isEmpty() && gPassword == ui->lineEdit_passwd->text())
        {
            qDebug("password ok");
            emit signalStatus(Login_Success);
        }
        else
        {
            HNMsgBox::warning(this, tr("Password error"));
            //QMsgBox::warning(this, tr("Warning"), tr("Password error"), QMessageBox::Yes);
            qDebug("password error");
        }
    }
    else
    {
        HNMsgBox::warning(this, tr("User name error"));
        //QMsgBox::warning(this, tr("Warning"), tr("User name error"), QMessageBox::Yes);
    }
    query.finish();
}

void QLoginDialog::initlanguage()
{
    ui->retranslateUi(this);
}
