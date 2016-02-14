#include "qcwidget.h"
#include "ui_qcwidget.h"
#include <QStylePainter>

QCWidget::QCWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCWidget)
{
    ui->setupUi(this);
}

QCWidget::~QCWidget()
{
    delete ui;
}

void QCWidget::setPixmap(QString pic)
{
    m_pic = pic;
}

void QCWidget::paintEvent(QPaintEvent *)
{
    QStylePainter p(this);
    if(m_pic.isEmpty())
        return;
    p.drawItemPixmap(rect(), Qt::AlignCenter, QIcon(m_pic).pixmap(rect().size(), QIcon::Normal, QIcon::On));
}
