#include "qserialwarning.h"
#include "ui_qserialwarning.h"

QSerialWarning::QSerialWarning(QWidget *parent) :
    QCDialog(parent),
    ui(new Ui::QSerialWarning)
{
    ui->setupUi(this);

    QPalette plt = palette();
    plt.setColor(QPalette::Window, QColor(0,0,0,0));
    plt.setColor(QPalette::Shadow, QColor(0,0,0,0));
    setPalette(plt);

    setGeometry(0, 0, 0, 0);
}

QSerialWarning::~QSerialWarning()
{
    delete ui;
}
