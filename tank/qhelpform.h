#ifndef QHELPFORM_H
#define QHELPFORM_H

#include <QWidget>

namespace Ui {
class QHelpForm;
}

class QHelpForm : public QWidget
{
    Q_OBJECT

public:
    explicit QHelpForm(QWidget *parent = 0);
    ~QHelpForm();
    void initLanguage();

    void stop();

private slots:
private:
    Ui::QHelpForm *ui;
};

#endif // QHELPFORM_H
