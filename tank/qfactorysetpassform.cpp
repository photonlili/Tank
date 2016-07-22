#include "qfactorysetpassform.h"
#include "ui_qfactorysetpassform.h"
#include "qtankpublic.h"
#include "hnmsgbox.h"

QFactorySetPassForm::QFactorySetPassForm(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QFactorySetPassForm)
{
    ui->setupUi(this);

    //setAttribute(Qt::WA_DeleteOnClose, false);
    setWindowModality(Qt::WindowModal);//阻挡父亲窗口内其他控件，除非本dialog关闭 show的功能强大起来 可以使用输入法
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    connect(ui->btn_sure, SIGNAL(clicked()), this, SLOT(passYes()));
    connect(ui->btn_cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void QFactorySetPassForm::passYes()
{
    if("4006186188" == ui->lineEdit_facpassword->text())
        accept();
    else
        HNMsgBox::warning(this, tr("Password error"));;
}

QFactorySetPassForm::~QFactorySetPassForm()
{
    delete ui;
}

void QFactorySetPassForm::initAll()
{
    setResult(Working);
    setFocus(Qt::MouseFocusReason);
}

void QFactorySetPassForm::initLanguage()
{
    ui->retranslateUi(this);
}
