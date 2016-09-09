#include "qhelpform.h"
#include "ui_qhelpform.h"
#include <QDir>
#include "qtankpublic.h"

QHelpForm::QHelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QHelpForm)
{
    ui->setupUi(this);
}

QHelpForm::~QHelpForm()
{
    delete ui;
}

void QHelpForm::initLanguage()
{
    ui->retranslateUi(this);
}

void QHelpForm::stop()
{
    ui->widget_2->stop();
}

