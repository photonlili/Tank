#ifndef QCPUSHBUTTON_H
#define QCPUSHBUTTON_H

#include <QPushButton>
#include "qcomponent.h"

namespace Ui {
class QCPushButton;
}

class QCPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit QCPushButton(QWidget *parent = 0);
    ~QCPushButton();

    //QCPushButton [] = 不能正常运算 所以采用这种形式。
    TBtnIconTable& btnIcon() { return m_pixmap; }

private:
    Ui::QCPushButton *ui;
    int state;
    TBtnIconTable m_pixmap;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    // QWidget interface
protected:
    void enabledChange(bool);
};

#endif // QCPUSHBUTTON_H
