#include <QMouseEvent>
#include "qmlabel.h"

QMLabel::QMLabel(QWidget *parent):
    QLabel(parent)
{
}

QMLabel::~QMLabel()
{

}

void QMLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        Q_UNUSED(event);
        emit pressed();
    }
    QLabel::mousePressEvent(event);
}
