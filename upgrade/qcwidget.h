#ifndef QPICWIDGET_H
#define QPICWIDGET_H

#include <QWidget>

namespace Ui {
class QCWidget;
}

class QCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QCWidget(QWidget *parent = 0);
    ~QCWidget();

    void setPixmap(QString pic = QString());

private:
    Ui::QCWidget *ui;
    QString m_pic;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPICWIDGET_H
