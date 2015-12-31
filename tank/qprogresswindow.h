#ifndef QPROGRESSWINDOW_H
#define QPROGRESSWINDOW_H

#include "qcdialog.h"

namespace Ui {
class QProgressWindow;
}

class QProgressWindow : public QCDialog
{
    Q_OBJECT

public:
    explicit QProgressWindow(QWidget *parent = 0);
    ~QProgressWindow();

    void initAll();
public slots:
    void setValue(int value);
    void cancel();

signals:
    void canceled();
private:
    Ui::QProgressWindow *ui;
};

#endif // QPROGRESSWINDOW_H
