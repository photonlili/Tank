#ifndef QCLOUDFORM_H
#define QCLOUDFORM_H

#include <QWidget>
#include "hnclient.h"
#include "hnprogressdialog.h"

namespace Ui {
class HNCloudWidget;
}

class HNCloudWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HNCloudWidget(QWidget *parent = 0);
    ~HNCloudWidget();

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
    Ui::HNCloudWidget *ui;
    HNClient* m_cli;
    HNProgressDialog* m_prog;
    HNProgressDialog* m_progDown;
    HNProgressDialog* m_progDel;
};

#endif // QCLOUDFORM_H
