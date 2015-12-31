#include "qcstackedwidget.h"

QCStackedWidget::QCStackedWidget(QWidget *parent) :
    QStackedWidget(parent)
{
}

QCStackedWidget::~QCStackedWidget()
{
}

void QCStackedWidget::repeat()
{
    int index = currentIndex() ? 0:1;
    setCurrentIndex(index);
}
