#ifndef QCLOUDFORM_H
#define QCLOUDFORM_H

#include <QWidget>
#include "hnclient.h"
#include "hnprogressdialog.h"

namespace Ui {
class HNCloudForm;
}

class HNCloudForm : public QWidget
{
    Q_OBJECT

public:
    explicit HNCloudForm(QWidget *parent = 0);
    ~HNCloudForm();

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
    Ui::HNCloudForm *ui;
    HNClient* m_cli;
    HNProgressDialog* m_prog;
    HNProgressDialog* m_progDown;
    HNProgressDialog* m_progDel;
};

#endif // QCLOUDFORM_H
