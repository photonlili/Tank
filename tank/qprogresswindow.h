#ifndef QPROGRESSWINDOW_H
#define QPROGRESSWINDOW_H

#include "qcdialog.h"
#include "hnprogressbar.h"

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

private:
    Ui::QProgressWindow *ui;
    HNProgressBar* bar;
};

#endif // QPROGRESSWINDOW_H
