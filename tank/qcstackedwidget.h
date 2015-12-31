#ifndef QCSTACKEDWIDGET_H
#define QCSTACKEDWIDGET_H

#include <QStackedWidget>

class QCStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit QCStackedWidget(QWidget *parent = 0);
    ~QCStackedWidget();
public slots:
    void repeat();
};

#endif // QCSTACKEDWIDGET_H
