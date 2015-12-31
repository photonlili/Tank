#ifndef QMLABEL_H
#define QMLABEL_H

#include <QWidget>
#include <QLabel>

class QMLabel: public QLabel
{
    Q_OBJECT

public:
    explicit QMLabel(QWidget *parent = 0);
    ~QMLabel();

    void publicClicked()
    {
        emit pressed();
    }

signals:
    void pressed();
protected:
    virtual void mousePressEvent(QMouseEvent  *event);

};

#endif // QMLABEL_H
