#ifndef HNMAINFORM_H
#define HNMAINFORM_H

#include <QWidget>

namespace Ui {
class HNMainForm;
}

class HNMainForm : public QWidget
{
    Q_OBJECT

public:
    explicit HNMainForm(QWidget *parent = 0);
    ~HNMainForm();

private:
    Ui::HNMainForm *ui;
};

#endif // HNMAINFORM_H
