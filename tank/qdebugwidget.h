#ifndef QDEBUGWIDGET_H
#define QDEBUGWIDGET_H

#include <QWidget>

namespace Ui {
class QDebugWidget;
}

class QDebugWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QDebugWidget(QWidget *parent = 0);
    ~QDebugWidget();

public slots:
    void slotRecvMsg(QByteArray msg);
private:
    Ui::QDebugWidget *ui;
};

#endif // QDEBUGWIDGET_H
