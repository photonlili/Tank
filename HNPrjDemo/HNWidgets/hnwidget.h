#ifndef QPICWIDGET_H
#define QPICWIDGET_H

#include <QWidget>

namespace Ui {
class HNWidget;
}

class HNWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNWidget(QWidget *parent = 0);
    ~HNWidget();

    void setPixmap(QString pic = QString());

private:
    Ui::HNWidget *ui;
    QString m_pic;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // QPICWIDGET_H
