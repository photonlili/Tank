#include "qtankfiledialog.h"
#include "ui_qtankfiledialog.h"

QTankFileDialog::QTankFileDialog(QWidget *parent) :
    QFileDialog(parent),
    ui(new Ui::QTankFileDialog)
{
    ui->setupUi(this);
}

QTankFileDialog::~QTankFileDialog()
{
    delete ui;
}
