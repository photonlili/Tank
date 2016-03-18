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
    void slotConnect();
    void slotDisConnect();
    void slotUpdateLabReport();
    void slotOpenProgress();
    void slotOpenDownProgress();
    void slotOpenOK();
    void slotOpenDownOK();
    void slotDelProgress();
    void slotDelOK();

private:
    Ui::QCloudForm *ui;
    QTankClient* m_cli;
    QProgressWindow* m_prog;
    QProgressWindow* m_progDown;
    QProgressWindow* m_progDel;
};

#endif // QCLOUDFORM_H
