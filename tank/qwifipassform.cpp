#include "qwifipassform.h"
#include "ui_qwifipassform.h"

QWIFIPassForm::QWIFIPassForm(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QWIFIPassForm)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, false);
    setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭 show的功能强大起来 可以使用输入法
    ui->lineEdit_ssid_password->setEchoMode(QLineEdit::Password);
    ui->pushButton_ssid_connect->setEnabled(false);
    connect(ui->pushButton_ssid_connect, SIGNAL(clicked()), this, SLOT(connectClicked()));
    connect(ui->lineEdit_ssid_password, SIGNAL(textChanged(QString)), SLOT(btnEnabled(QString)));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

QWIFIPassForm::~QWIFIPassForm()
{
    delete ui;
}

void QWIFIPassForm::setWifiName(QString name)
{
    ui->label_ssid_name->setText(name);
}

void QWIFIPassForm::connectClicked()
{
    emit connectClicked(ui->lineEdit_ssid_password->text());
    accept();
}

void QWIFIPassForm::btnEnabled(QString pas)
{
    bool enable = pas.length()<8?false:true;
    ui->pushButton_ssid_connect->setEnabled(enable);
}
