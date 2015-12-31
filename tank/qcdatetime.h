#ifndef QCDATETIME_H
#define QCDATETIME_H

#include <QWidget>

namespace Ui {
class QCDateTime;
}

class QCDateTime : public QWidget
{
    Q_OBJECT

public:
    explicit QCDateTime(QWidget *parent = 0);
    ~QCDateTime();

private:
    Ui::QCDateTime *ui;
};

#endif // QCDATETIME_H
