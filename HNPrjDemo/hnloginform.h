#ifndef HNLOGINFORM_H
#define HNLOGINFORM_H

#include <QWidget>

namespace Ui {
class HNLoginForm;
}

class HNLoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit HNLoginForm(QWidget *parent = 0);
    ~HNLoginForm();

private:
    Ui::HNLoginForm *ui;
};

#endif // HNLOGINFORM_H
