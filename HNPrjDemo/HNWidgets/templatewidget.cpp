#include "templatewidget.h"
#include "ui_templatewidget.h"

TemplateWidget::TemplateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemplateWidget)
{
    ui->setupUi(this);
}

TemplateWidget::~TemplateWidget()
{
    delete ui;
}
