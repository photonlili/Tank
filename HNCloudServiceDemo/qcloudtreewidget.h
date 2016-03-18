#ifndef QCLOUDTREEWIDGET_H
#define QCLOUDTREEWIDGET_H

#include "qcloudtreeview.h"
#include "qcloudmodel.h"
#include "hnmsgbox.h"

namespace Ui {
class QCloudTreeWidget;
}

class QCloudTreeWidget : public QCloudTreeView
{
    Q_OBJECT

public:
    explicit QCloudTreeWidget(QWidget *parent = 0);
    ~QCloudTreeWidget();

    QString currentDownloadingFile();
    QString currentDownloadingFilelocalName();

public slots:
    void slotConnect();
    void slotDisConnect();

private slots:
    void slotConnected();
    void currentRowChanged();
    void downFile();
    void delFile();

private:
    Ui::QCloudTreeWidget *ui;
    QTankClient* m_client;
    QCloudModel* model;
    QString m_tmpfile, m_localfile;
    HNMsgBox* m_box;
};

#endif // QCLOUDTREEWIDGET_H
