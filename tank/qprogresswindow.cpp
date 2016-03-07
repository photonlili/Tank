#include "qprogresswindow.h"
#include "ui_qprogresswindow.h"
#include "qtankpublic.h"

QProgressWindow::QProgressWindow(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QProgressWindow)
{
    ui->setupUi(this);
    bar = ui->widgetBar;
    connect(ui->btnCancel, SIGNAL(clicked()),
            this, SLOT(reject()));
}

QProgressWindow::~QProgressWindow()
{
    delete ui;
}

void QProgressWindow::initAll()
{
    bar->setRange(0, 100);
    bar->setValue(0);
}

void QProgressWindow::setValue(int value)
{
    bar->setValue(value);
}

