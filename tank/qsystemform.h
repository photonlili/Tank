#ifndef QSYSTEMFORM_H
#define QSYSTEMFORM_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class QSystemForm;
}

class QSystemForm : public QWidget
{
    Q_OBJECT

public:
    explicit QSystemForm(QWidget *parent = 0);
    ~QSystemForm();

private slots:
    void updateLabel();

private:
    Ui::QSystemForm *ui;

    QTimer* timer;
};

#endif // QSYSTEMFORM_H
