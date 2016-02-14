#ifndef QCLOUDFORM_H
#define QCLOUDFORM_H

#include <QWidget>
#include "qtankclient.h"
#include "qprogresswindow.h"

namespace Ui {
class QCloudForm;
}

class QCloudForm : public QWidget
{
    Q_OBJECT

public:
    explicit QCloudForm(QWidget *parent = 0);
    ~QCloudForm();

    void chageLanguage();

signals:
public slots:
    void slotUpdateLabReport();
    void slotOpenProgress();
    void slotOpenDownProgress();
    void slotDelProgress();
    void slotDelOK();

private:
    Ui::QCloudForm *ui;
    QTankClient* m_Client;
    QProgressWindow* m_prog;
    QProgressWindow* m_progDown;
    QProgressWindow* m_progDel;
    QTankClient* m_cli;
};

#endif // QCLOUDFORM_H
