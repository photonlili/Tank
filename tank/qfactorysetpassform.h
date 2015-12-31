#ifndef QFACTORYSETPASSFORM_H
#define QFACTORYSETPASSFORM_H

#include "qcdialog.h"

namespace Ui {
class QFactorySetPassForm;
}

class QFactorySetPassForm : public QCDialog
{
    Q_OBJECT

public:
    enum QFactorySetPassFormCode
    {
        Working = 2,
    };

    explicit QFactorySetPassForm(QWidget *parent = 0);
    ~QFactorySetPassForm();

    void initAll();
    void initLanguage();

private slots:
    void passYes();
private:
    Ui::QFactorySetPassForm *ui;

    // QObject interface
};

#endif // QFACTORYSETPASSFORM_H
