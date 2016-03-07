#ifndef QCLOUDLOCALTREEWIDGET_H
#define QCLOUDLOCALTREEWIDGET_H

#include "qcloudtreeview.h"
#include "qcloudlocalmodel.h"

namespace Ui {
class QCloudLocalTreeWidget;
}

class QCloudLocalTreeWidget : public QCloudTreeView
{
    Q_OBJECT

public:
    explicit QCloudLocalTreeWidget(QWidget *parent = 0);
    ~QCloudLocalTreeWidget();

    QString currentUploadingFile();
public slots:
private slots:
    void currentRowChanged();
    void printFile();
    void uploadFile();

private:
    QString m_uploadFileName;
    QString m_localPath;
    Ui::QCloudLocalTreeWidget *ui;
    QCloudLocalModel* m_model;
};

#endif // QCLOUDLOCALTREEWIDGET_H
