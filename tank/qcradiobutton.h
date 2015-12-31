#ifndef QCRADIOBUTTON_H
#define QCRADIOBUTTON_H

#include <QRadioButton>
#include "qcomponent.h"

namespace Ui {
class QCRadioButton;
}

class QCRadioButton : public QRadioButton
{
    Q_OBJECT

public:
    explicit QCRadioButton(QWidget *parent = 0);
    ~QCRadioButton();

    void pixMap(QImage& m_icon, QImage& m_iconSel);
    void setPixmap(const QString& m_icon = QString(), const QString &m_iconSel = QString());
private:
    Ui::QCRadioButton *ui;
    TBtnIconTable m_icon;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QAbstractButton interface
protected:
    bool hitButton(const QPoint &pos) const;
};

#endif // QCRADIOBUTTON_H
