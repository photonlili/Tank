#include "qcspinbox.h"
#include "ui_qcspinbox.h"

QCSpinBox::QCSpinBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCSpinBox)
{
    ui->setupUi(this);

    m_value = 0;
    m_min = 0;
    m_max = 0;
    //设置value regexp
}

QCSpinBox::~QCSpinBox()
{
    delete ui;
}

void QCSpinBox::setRange(int min, int max)
{
    if(min > max)
        return;

    m_min = min;
    m_max = max;

    setText();
}

void QCSpinBox::setValue(int arg1)
{
    if(arg1 < m_min || arg1 > m_max)
        return;

    m_value = arg1;

    setText();
}

void QCSpinBox::on_btn_next_clicked()
{
    if(m_value == m_max)
        return;

    m_value ++;
    setText();
}

void QCSpinBox::on_btn_pre_clicked()
{
    if(m_value == m_min)
        return;

    m_value --;
    setText();
}

void QCSpinBox::on_le_value_textChanged(const QString &arg1)
{
    emit valueChanged(m_value);
}

void QCSpinBox::setText()
{
    QString value = QString("%1/%2").arg(m_value).arg(m_max-m_min+1);
    ui->le_value->setText(value);
}

void QCSpinBox::paintEvent(QPaintEvent *)
{
}
