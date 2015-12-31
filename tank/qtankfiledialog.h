#ifndef QTANKFILEDIALOG_H
#define QTANKFILEDIALOG_H

#include <QFileDialog>

namespace Ui {
class QTankFileDialog;
}

class QTankFileDialog : public QFileDialog
{
    Q_OBJECT

public:
    explicit QTankFileDialog(QWidget *parent = 0);
    ~QTankFileDialog();

private:
    Ui::QTankFileDialog *ui;
};

#endif // QTANKFILEDIALOG_H
