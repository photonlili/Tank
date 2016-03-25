#ifndef QCLOUDMODEL_H
#define QCLOUDMODEL_H

#include "hnstandarditemmodel.h"
#include "hnclient.h"

class HNCloudModel : public HNStandardItemModel
{
    Q_OBJECT
public:
    explicit HNCloudModel(QObject *parent = 0, QTankClient* clientHandle = NULL);

signals:
    void sigDownSuccess();
    void sigQueryRootDirSuccess();
public slots:
    // 用户不可以创建文件夹
    void  queryRootDirs();
    // 查询文件
    void queryFiles(QString code = "001");
    void downFile(QString path, QString id, QString localname);
    void delFile(QString code, QString id);

private slots:
    void queryRootDirsResult();
    void queryFilesResult();
private:
    QStandardItem* findDirByCode(QString code);

private:
    QTankClient* m_client;
};

#endif // QCLOUDMODEL_H
