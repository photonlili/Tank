#ifndef QWIFIWIDGET_H
#define QWIFIWIDGET_H

#include "qwifiview.h"
#include "qwifimodel.h"
#include "qtankgui.h"

namespace Ui {
class QWIFIWidget;
}

class QWIFIWidget : public QWIFIView
{
    Q_OBJECT

public:
    explicit QWIFIWidget(QWidget *parent = 0);
    ~QWIFIWidget();

    QString currentWIFIName();
    QString currentWIFIEncrypted();
    QString currentWIFIType();
    QString currentWIFIMAC();
    bool setCurrentWifi(QString bssid_mac, QString password = "");

private:
    Ui::QWIFIWidget *ui;
    QWIFIModel* m_model;
};

#endif // QWIFIWIDGET_H
