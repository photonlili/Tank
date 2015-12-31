#include "qhelpform.h"
#include "ui_qhelpform.h"
#include <QDir>
#include "qtankpublic.h"

QHelpForm::QHelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHelpForm)
{
    ui->setupUi(this);
    ui->lb_log->setFixedHeight(30);
}

QHelpForm::~QHelpForm()
{
    delete ui;
}

void QHelpForm::initLanguage()
{
    ui->retranslateUi(this);
}

